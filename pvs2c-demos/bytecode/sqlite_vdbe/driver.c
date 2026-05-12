#include "sqlite_vdbe_tests_c.h"
#include "../../cavp_driver.h"

#include <sqlite3.h>

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  sqlite_vdbe__instruction_t *items;
  uint32_t length;
  uint32_t capacity;
} instruction_vec_t;

typedef struct {
  sqlite_vdbe__table_row_t *items;
  uint32_t length;
  uint32_t capacity;
} row_vec_t;

static void fail_sqlite(sqlite3 *db, const char *what) {
  fprintf(stderr, "FAIL sqlite %s: %s\n", what, sqlite3_errmsg(db));
  exit(2);
}

static int exec_sql(sqlite3 *db, const char *sql) {
  char *error = NULL;
  int rc = sqlite3_exec(db, sql, NULL, NULL, &error);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "FAIL sqlite exec: %s\n", error == NULL ? sqlite3_errmsg(db) : error);
    sqlite3_free(error);
    return 0;
  }
  return 1;
}

static void instruction_vec_push(instruction_vec_t *vec,
                                 sqlite_vdbe__instruction_t ins) {
  if (vec->length == vec->capacity) {
    uint32_t next = vec->capacity == 0 ? 16 : vec->capacity * 2;
    sqlite_vdbe__instruction_t *items =
        realloc(vec->items, next * sizeof(sqlite_vdbe__instruction_t));
    if (items == NULL) {
      fprintf(stderr, "FAIL allocate instruction vector\n");
      exit(2);
    }
    vec->items = items;
    vec->capacity = next;
  }
  vec->items[vec->length++] = ins;
}

static void row_vec_push(row_vec_t *vec, sqlite_vdbe__table_row_t row) {
  if (vec->length == vec->capacity) {
    uint32_t next = vec->capacity == 0 ? 8 : vec->capacity * 2;
    sqlite_vdbe__table_row_t *items =
        realloc(vec->items, next * sizeof(sqlite_vdbe__table_row_t));
    if (items == NULL) {
      fprintf(stderr, "FAIL allocate row vector\n");
      exit(2);
    }
    vec->items = items;
    vec->capacity = next;
  }
  vec->items[vec->length++] = row;
}

static int u32_column(sqlite3_stmt *stmt, int col, uint32_t *out) {
  sqlite3_int64 value = sqlite3_column_int64(stmt, col);
  if (value < 0 || value > UINT32_MAX) {
    return 0;
  }
  *out = (uint32_t)value;
  return 1;
}

static int map_opcode(const char *opcode, const char *p4, uint8_t *op, uint8_t *p4_tag) {
  *p4_tag = sqlite_vdbe__p4_none();
  if (strcmp(opcode, "Init") == 0) {
    *op = sqlite_vdbe__op_init();
  } else if (strcmp(opcode, "Add") == 0) {
    *op = sqlite_vdbe__op_add();
  } else if (strcmp(opcode, "Multiply") == 0) {
    *op = sqlite_vdbe__op_multiply();
  } else if (strcmp(opcode, "Integer") == 0) {
    *op = sqlite_vdbe__op_integer();
  } else if (strcmp(opcode, "Goto") == 0) {
    *op = sqlite_vdbe__op_goto();
  } else if (strcmp(opcode, "ResultRow") == 0) {
    *op = sqlite_vdbe__op_result_row();
  } else if (strcmp(opcode, "Halt") == 0) {
    *op = sqlite_vdbe__op_halt();
  } else if (strcmp(opcode, "Transaction") == 0) {
    *op = sqlite_vdbe__op_transaction();
  } else if (strcmp(opcode, "OpenRead") == 0) {
    *op = sqlite_vdbe__op_open_read();
  } else if (strcmp(opcode, "Rewind") == 0) {
    *op = sqlite_vdbe__op_rewind();
  } else if (strcmp(opcode, "Column") == 0) {
    *op = sqlite_vdbe__op_column();
  } else if (strcmp(opcode, "Function") == 0 &&
             (p4 == NULL || strcmp(p4, "abs(1)") == 0 || strcmp(p4, "1") == 0)) {
    *op = sqlite_vdbe__op_function();
    *p4_tag = sqlite_vdbe__p4_abs();
  } else if (strcmp(opcode, "Next") == 0) {
    *op = sqlite_vdbe__op_next();
  } else if (strcmp(opcode, "Le") == 0 &&
             (p4 == NULL || strcmp(p4, "BINARY-8") == 0 || strcmp(p4, "1") == 0)) {
    *op = sqlite_vdbe__op_le();
    *p4_tag = sqlite_vdbe__p4_binary();
  } else if (strcmp(opcode, "Explain") == 0) {
    *op = sqlite_vdbe__op_explain();
  } else {
    return 0;
  }
  return 1;
}

static sqlite_vdbe__program_t build_program_from_explain(sqlite3 *db, const char *sql) {
  size_t explain_len = strlen("EXPLAIN ") + strlen(sql) + 1;
  char *explain_sql = malloc(explain_len);
  if (explain_sql == NULL) {
    fprintf(stderr, "FAIL allocate EXPLAIN SQL\n");
    exit(2);
  }
  snprintf(explain_sql, explain_len, "EXPLAIN %s", sql);

  sqlite3_stmt *stmt = NULL;
  int rc = sqlite3_prepare_v2(db, explain_sql, -1, &stmt, NULL);
  free(explain_sql);
  if (rc != SQLITE_OK) {
    fail_sqlite(db, "prepare EXPLAIN");
  }

  instruction_vec_t vec = {0};
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    const char *opcode = (const char *)sqlite3_column_text(stmt, 1);
    const char *p4 = (const char *)sqlite3_column_text(stmt, 5);
    uint32_t p1 = 0;
    uint32_t p2 = 0;
    uint32_t p3 = 0;
    uint32_t p5 = 0;
    uint8_t op = 0;
    uint8_t p4_tag = 0;
    if (opcode == NULL || !u32_column(stmt, 2, &p1) ||
        !u32_column(stmt, 3, &p2) || !u32_column(stmt, 4, &p3) ||
        !u32_column(stmt, 6, &p5) || !map_opcode(opcode, p4, &op, &p4_tag)) {
      fprintf(stderr, "FAIL unsupported EXPLAIN row opcode=%s p4=%s\n",
              opcode == NULL ? "<null>" : opcode,
              p4 == NULL ? "" : p4);
      sqlite3_finalize(stmt);
      free(vec.items);
      return NULL;
    }
    instruction_vec_push(&vec, sqlite_vdbe__instr(op, p1, p2, p3, p4_tag, p5));
  }
  if (rc != SQLITE_DONE) {
    fail_sqlite(db, "step EXPLAIN");
  }
  sqlite3_finalize(stmt);

  sqlite_vdbe_array_1_t seq = new_sqlite_vdbe_array_1(vec.length);
  for (uint32_t i = 0; i < vec.length; i++) {
    seq->elems[i] = vec.items[i];
  }
  free(vec.items);

  sqlite_vdbe__program_t program = new_sqlite_vdbe__program();
  program->length = vec.length;
  program->seq = seq;
  return program;
}

static sqlite_vdbe__database_t snapshot_table(sqlite3 *db) {
  sqlite3_stmt *stmt = NULL;
  int rc = sqlite3_prepare_v2(db, "SELECT x, name FROM t ORDER BY rowid", -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fail_sqlite(db, "prepare snapshot");
  }

  row_vec_t vec = {0};
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    sqlite3_int64 x64 = sqlite3_column_int64(stmt, 0);
    const unsigned char *name = sqlite3_column_text(stmt, 1);
    int name_len = sqlite3_column_bytes(stmt, 1);
    if (x64 < INT32_MIN || x64 > INT32_MAX || name == NULL || name_len < 0) {
      fprintf(stderr, "FAIL snapshot row outside PVS subset\n");
      sqlite3_finalize(stmt);
      free(vec.items);
      return NULL;
    }
    sqlite_vdbe__sql_value_adt_t x = con_sqlite_vdbe__sql_int((int32_t)x64);
    sqlite_vdbe__sql_value_adt_t text =
        con_sqlite_vdbe__sql_text(cavp_make_bytestring(name, (uint32_t)name_len));
    row_vec_push(&vec, sqlite_vdbe__row2(x, text));
  }
  if (rc != SQLITE_DONE) {
    fail_sqlite(db, "step snapshot");
  }
  sqlite3_finalize(stmt);

  sqlite_vdbe_array_25_t rows = new_sqlite_vdbe_array_25(vec.length);
  for (uint32_t i = 0; i < vec.length; i++) {
    rows->elems[i] = vec.items[i];
  }
  free(vec.items);

  sqlite_vdbe__table_data_t table = new_sqlite_vdbe__table_data();
  table->length = vec.length;
  table->seq = rows;

  sqlite_vdbe__database_t database = new_sqlite_vdbe__database();
  database->main_table = table;
  return database;
}

static sqlite_vdbe__exec_result_t pvs_sqlite_step(sqlite3 *db, const char *sql) {
  sqlite_vdbe__program_t program = build_program_from_explain(db, sql);
  if (program == NULL) {
    return NULL;
  }
  sqlite_vdbe__database_t database = snapshot_table(db);
  if (database == NULL) {
    return NULL;
  }
  return sqlite_vdbe__run(database, program, 256);
}

static void print_value(sqlite_vdbe__sql_value_adt_t value) {
  switch (value->sqlite_vdbe__sql_value_adt_index) {
    case 0:
      printf("NULL");
      break;
    case 1:
      printf("%d", ((sqlite_vdbe__sql_int_t)value)->ival);
      break;
    case 2:
      cavp_print_ascii_bytestring(((sqlite_vdbe__sql_text_t)value)->tval);
      break;
    case 3:
      printf("<blob:%u>", ((sqlite_vdbe__sql_blob_t)value)->bval->length);
      break;
    default:
      printf("<bad-value>");
      break;
  }
}

static void print_result(sqlite_vdbe__exec_result_t result) {
  for (uint32_t r = 0; r < result->row_count; r++) {
    sqlite_vdbe__table_row_t row = result->rows->elems[r];
    printf("[");
    for (uint32_t c = 0; c < row->column_count; c++) {
      if (c > 0) {
        printf(", ");
      }
      print_value(row->cells->elems[c]);
    }
    printf("]");
  }
}

static int pvs_value_matches_sqlite(sqlite3_stmt *stmt,
                                    int col,
                                    sqlite_vdbe__sql_value_adt_t value) {
  int sqlite_type = sqlite3_column_type(stmt, col);
  switch (value->sqlite_vdbe__sql_value_adt_index) {
    case 0:
      return sqlite_type == SQLITE_NULL;
    case 1:
      return sqlite_type == SQLITE_INTEGER &&
             sqlite3_column_int64(stmt, col) == ((sqlite_vdbe__sql_int_t)value)->ival;
    case 2: {
      const unsigned char *text = sqlite3_column_text(stmt, col);
      int text_len = sqlite3_column_bytes(stmt, col);
      bytestrings__bytestring_t expected = ((sqlite_vdbe__sql_text_t)value)->tval;
      return sqlite_type == SQLITE_TEXT && text != NULL && text_len >= 0 &&
             expected->length == (uint32_t)text_len &&
             memcmp(expected->seq->elems, text, (size_t)text_len) == 0;
    }
    case 3: {
      const void *blob = sqlite3_column_blob(stmt, col);
      int blob_len = sqlite3_column_bytes(stmt, col);
      bytestrings__bytestring_t expected = ((sqlite_vdbe__sql_blob_t)value)->bval;
      return sqlite_type == SQLITE_BLOB && blob != NULL && blob_len >= 0 &&
             expected->length == (uint32_t)blob_len &&
             memcmp(expected->seq->elems, blob, (size_t)blob_len) == 0;
    }
    default:
      return 0;
  }
}

static int compare_native_results(sqlite3 *db,
                                  const char *sql,
                                  sqlite_vdbe__exec_result_t expected) {
  sqlite3_stmt *stmt = NULL;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fail_sqlite(db, "prepare native comparison");
  }
  uint32_t row_index = 0;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    if (row_index >= expected->row_count) {
      sqlite3_finalize(stmt);
      return 0;
    }
    sqlite_vdbe__table_row_t row = expected->rows->elems[row_index];
    if (sqlite3_column_count(stmt) != row->column_count) {
      sqlite3_finalize(stmt);
      return 0;
    }
    for (uint32_t col = 0; col < row->column_count; col++) {
      if (!pvs_value_matches_sqlite(stmt, (int)col, row->cells->elems[col])) {
        sqlite3_finalize(stmt);
        return 0;
      }
    }
    row_index++;
  }
  if (rc != SQLITE_DONE) {
    fail_sqlite(db, "step native comparison");
  }
  sqlite3_finalize(stmt);
  return row_index == expected->row_count;
}

static int check_dynamic(sqlite3 *db, const char *sql, uint32_t expected_rows) {
  sqlite_vdbe__exec_result_t result = pvs_sqlite_step(db, sql);
  if (result == NULL) {
    return 1;
  }

  int ok = result->status == sqlite_vdbe__halt_status() &&
           result->row_count == expected_rows &&
           compare_native_results(db, sql, result);
  printf("%s pvs-sqlite %s => ", ok ? "PASS" : "FAIL", sql);
  print_result(result);
  printf("\n");
  if (!ok) {
    printf("  status=%u rows=%u expected status=%u rows=%u\n",
           result->status,
           result->row_count,
           sqlite_vdbe__halt_status(),
           expected_rows);
  }
  release_sqlite_vdbe__exec_result(result);
  return ok ? 0 : 1;
}

static int check_static_pvs_tests(void) {
  int ok = sqlite_vdbe_tests__test_arithmetic() &&
           sqlite_vdbe_tests__test_abs_scan() &&
           sqlite_vdbe_tests__test_filtered_scan() &&
           sqlite_vdbe_tests__test_closed_cursor_traps() &&
           sqlite_vdbe_tests__test_uninitialized_result_traps();
  printf("%s generated PVS test entry points\n", ok ? "PASS" : "FAIL");
  return ok ? 0 : 1;
}

int main(void) {
  sqlite3 *db = NULL;
  if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
    fail_sqlite(db, "open");
  }
  if (!exec_sql(db,
                "CREATE TABLE t(x INTEGER, name TEXT);"
                "INSERT INTO t VALUES (-7, 'neg');"
                "INSERT INTO t VALUES (3, 'small');"
                "INSERT INTO t VALUES (11, 'big');")) {
    sqlite3_close(db);
    return 2;
  }

  int failures = 0;
  failures += check_static_pvs_tests();
  failures += check_dynamic(db, "SELECT 1 + 2 * 3", 1);
  failures += check_dynamic(db, "SELECT abs(x) FROM t", 3);
  failures += check_dynamic(db, "SELECT x, name FROM t WHERE x > 5", 1);

  sqlite3_close(db);
  return failures == 0 ? 0 : 1;
}
