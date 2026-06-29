PVS_HOME ?= $(HOME)/git/PVS
PVS := $(PVS_HOME)/pvs

NO_GENERATED_MK_GOALS := clean typecheck pvs2c refresh-explain
INCLUDE_GENERATED_MK := $(if $(MAKECMDGOALS),$(filter-out $(NO_GENERATED_MK_GOALS),$(MAKECMDGOALS)),all)

DEMO := sqlite_vdbe
TC_THEORY := sqlite_vdbe_tests
MAIN_THEORY := sqlite_vdbe_tests

CC ?= cc
CFLAGS ?= -O2 -w -foptimize-sibling-calls -fPIC
CPPFLAGS += -I$(PVS_HOME)/lib/pvs2c/include -Ipvs2c/include -include ../../pvs2c_compat.h
LDFLAGS += -L$(PVS_HOME)/lib/pvs2c/lib
LDLIBS += $(PVS_HOME)/lib/pvs2c/lib/libpvs-prelude.a -lgmp -lm -lsqlite3

BUILD_DIR := build
BINDIR := pvs2c/bin
SRCDIR := pvs2c/src
BIN := $(BUILD_DIR)/$(DEMO)-driver
TYPECHECK_LOG := $(BUILD_DIR)/typecheck.log
TYPECHECK_STATUS := $(BUILD_DIR)/typecheck.status
PVS2C_LOG := $(BUILD_DIR)/pvs2c.log
PVS2C_STAMP := $(BUILD_DIR)/pvs2c.stamp
GENERATED_HEADER := pvs2c/include/$(MAIN_THEORY)_c.h
GENERATED_MK := pvs2c/include/$(MAIN_THEORY).mk
GENERATED_TEST_BIN := $(BINDIR)/$(MAIN_THEORY)
PVS_SOURCES := $(wildcard *.pvs)
MAKE_DEPS := Makefile
EXPLAIN_FIXTURES := examples/select_arith.explain examples/select_abs.explain examples/select_filter.explain
GENERATED_LIB_OBJS = $(filter-out $(SRCDIR)/$(MAIN_THEORY).o,$(OBJS_$(MAIN_THEORY)))

PVS_TYPECHECK_EXPR := (progn (setq *suppress-output* nil) (tc "$(TC_THEORY)" t) (finish-output) (uiop:quit))
PVS2C_EXPR := (progn (setq *suppress-output* t) (pvs2c-theory "$(MAIN_THEORY)" t) (finish-output) (uiop:quit))

ifneq ($(INCLUDE_GENERATED_MK),)
-include $(GENERATED_MK)
endif

.PHONY: all run typecheck pvs2c refresh-explain clean

all: $(GENERATED_HEADER)
	@$(MAKE) --no-print-directory $(BIN)

run: $(GENERATED_HEADER)
	@$(MAKE) --no-print-directory $(GENERATED_TEST_BIN)
	@$(MAKE) --no-print-directory $(BIN)
	@./$(GENERATED_TEST_BIN)
	@./$(BIN)

typecheck: $(TYPECHECK_LOG)

pvs2c: $(GENERATED_HEADER)

refresh-explain:
	@sqlite3 :memory: < examples/select_arith.sql > examples/select_arith.explain
	@sqlite3 :memory: < examples/select_abs.sql > examples/select_abs.explain
	@sqlite3 :memory: < examples/select_filter.sql > examples/select_filter.explain

$(BUILD_DIR) $(BINDIR):
	@mkdir -p $@

$(TYPECHECK_LOG): $(PVS_SOURCES) $(MAKE_DEPS) | $(BUILD_DIR)
	@echo "[$(DEMO)] Typechecking $(TC_THEORY)"
	@echo "[$(DEMO)]   PVS: $(PVS)"
	@echo "[$(DEMO)]   log: $@"
	@rm -f $(TYPECHECK_STATUS)
	@{ $(PVS) -raw -E '$(PVS_TYPECHECK_EXPR)' < /dev/null 2>&1; echo $$? > $(TYPECHECK_STATUS); } | tee $@
	@status=$$(cat $(TYPECHECK_STATUS)); \
	rm -f $(TYPECHECK_STATUS); \
	if [ "$$status" -ne 0 ]; then \
	  echo "[$(DEMO)] Typecheck command failed; see $@"; \
	  exit $$status; \
	fi
	@if grep -q "^In file " $@; then \
	  echo "[$(DEMO)] Typecheck reported errors; see $@"; \
	  exit 1; \
	fi
	@echo "[$(DEMO)] Typecheck complete"

$(PVS2C_STAMP): $(PVS_SOURCES) $(MAKE_DEPS) $(TYPECHECK_LOG) | $(BUILD_DIR)
	@echo "[$(DEMO)] Generating C for $(MAIN_THEORY)"
	@echo "[$(DEMO)]   PVS: $(PVS)"
	@echo "[$(DEMO)]   log: $(PVS2C_LOG)"
	@if ! $(PVS) -raw -E '$(PVS2C_EXPR)' < /dev/null > $(PVS2C_LOG) 2>&1; then \
	  echo "[$(DEMO)] PVS2C command failed; see $(PVS2C_LOG)"; \
	  cat $(PVS2C_LOG); \
	  exit 1; \
	fi
	@if grep -q "^In file " $(PVS2C_LOG); then \
	  echo "[$(DEMO)] PVS2C reported errors; see $(PVS2C_LOG)"; \
	  cat $(PVS2C_LOG); \
	  exit 1; \
	fi
	@test -f $(GENERATED_HEADER)
	@test -f $(GENERATED_MK)
	@touch $@
	@echo "[$(DEMO)] Generated $(GENERATED_HEADER)"

$(GENERATED_HEADER) $(GENERATED_MK): $(PVS2C_STAMP)
	@:

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(GENERATED_HEADER)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN): driver.c $(GENERATED_TEST_BIN) $(EXPLAIN_FIXTURES) ../../pvs2c_compat.h | $(BUILD_DIR)
	@echo "[$(DEMO)] Building driver"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(GENERATED_LIB_OBJS) driver.c -o $@ $(LDLIBS)

clean:
	@rm -rf $(BUILD_DIR) pvs2c pvsbin .pvscontext Makefile.bak
