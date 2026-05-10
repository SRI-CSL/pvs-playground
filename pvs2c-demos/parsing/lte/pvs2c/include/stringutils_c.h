//Code generated using pvs2ir
#ifndef _stringutils_h 
#define _stringutils_h

#include <stdio.h>

#include <stdlib.h>

#include <inttypes.h>

#include <stdbool.h>

#include <stdarg.h>

#include <string.h>

#include <fcntl.h>

#include <math.h>

#include <sys/mman.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <gmp.h>

#include "pvslib.h"

#include "array_sequences_c.h"


#include "strings_c.h"


#include "gen_strings_c.h"


#include "finite_sequences_c.h"


#include "list_adt_c.h"


#include "integertypes_c.h"


#include "exp2_c.h"


#include "bytestrings_c.h"


//cc -O3 -Wall -o stringutils -L /Users/e35480/git/PVS/lib/pvs2c/lib -I /Users/e35480/git/PVS/lib/pvs2c/include stringutils_c.c <your main>.c  -lgmp -lpvs-prelude 
//escape_char

struct stringutils_array_0_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint8_t elems[]; };
typedef struct stringutils_array_0_s * stringutils_array_0_t;

extern stringutils_array_0_t new_stringutils_array_0(uint32_t size);

extern void release_stringutils_array_0(stringutils_array_0_t x);

extern stringutils_array_0_t copy_stringutils_array_0(stringutils_array_0_t x);

extern bool_t equal_stringutils_array_0(stringutils_array_0_t x, stringutils_array_0_t y);
extern char * json_stringutils_array_0(stringutils_array_0_t x);

typedef struct actual_stringutils_array_0_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_array_0_t;
extern void release_stringutils_array_0_ptr(pointer_t x, type_actual_t stringutils_array_0);

extern bool_t equal_stringutils_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_stringutils_array_0_ptr(pointer_t x, type_actual_t T);

actual_stringutils_array_0_t actual_stringutils_array_0(void);

 

extern stringutils_array_0_t update_stringutils_array_0(stringutils_array_0_t x, uint32_t i, uint8_t v);

extern stringutils_array_0_t upgrade_stringutils_array_0(stringutils_array_0_t x, uint32_t i, uint8_t v);


//escape_char

struct stringutils_record_1_s {
        uint32_t count; 
        uint32_t length;
        stringutils_array_0_t seq;};
typedef struct stringutils_record_1_s * stringutils_record_1_t;

extern stringutils_record_1_t new_stringutils_record_1(void);

extern void release_stringutils_record_1(stringutils_record_1_t x);

extern stringutils_record_1_t copy_stringutils_record_1(stringutils_record_1_t x);

extern bool_t equal_stringutils_record_1(stringutils_record_1_t x, stringutils_record_1_t y);
extern char * json_stringutils_record_1(stringutils_record_1_t x);

typedef struct actual_stringutils_record_1_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_record_1_t;
extern void release_stringutils_record_1_ptr(pointer_t x, type_actual_t stringutils_record_1);

extern bool_t equal_stringutils_record_1_ptr(pointer_t x, pointer_t y, actual_stringutils_record_1_t T);

extern char * json_stringutils_record_1_ptr(pointer_t x,  actual_stringutils_record_1_t T);

actual_stringutils_record_1_t actual_stringutils_record_1(void);

 

extern stringutils_record_1_t update_stringutils_record_1_length(stringutils_record_1_t x, uint32_t v);

extern stringutils_record_1_t update_stringutils_record_1_seq(stringutils_record_1_t x, stringutils_array_0_t v);


//escape_string_test_quote

struct stringutils_array_2_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         mpq_ptr_t elems[]; };
typedef struct stringutils_array_2_s * stringutils_array_2_t;

extern stringutils_array_2_t new_stringutils_array_2(uint32_t size);

extern void release_stringutils_array_2(stringutils_array_2_t x);

extern stringutils_array_2_t copy_stringutils_array_2(stringutils_array_2_t x);

extern bool_t equal_stringutils_array_2(stringutils_array_2_t x, stringutils_array_2_t y);
extern char * json_stringutils_array_2(stringutils_array_2_t x);

typedef struct actual_stringutils_array_2_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_array_2_t;
extern void release_stringutils_array_2_ptr(pointer_t x, type_actual_t stringutils_array_2);

extern bool_t equal_stringutils_array_2_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_stringutils_array_2_ptr(pointer_t x, type_actual_t T);

actual_stringutils_array_2_t actual_stringutils_array_2(void);

 

extern stringutils_array_2_t update_stringutils_array_2(stringutils_array_2_t x, uint32_t i, mpq_t v);

extern stringutils_array_2_t upgrade_stringutils_array_2(stringutils_array_2_t x, uint32_t i, mpq_t v);


//escape_string_test_quote

struct stringutils_record_3_s {
        uint32_t count; 
        uint8_t length;
        stringutils_array_2_t seq;};
typedef struct stringutils_record_3_s * stringutils_record_3_t;

extern stringutils_record_3_t new_stringutils_record_3(void);

extern void release_stringutils_record_3(stringutils_record_3_t x);

extern stringutils_record_3_t copy_stringutils_record_3(stringutils_record_3_t x);

extern bool_t equal_stringutils_record_3(stringutils_record_3_t x, stringutils_record_3_t y);
extern char * json_stringutils_record_3(stringutils_record_3_t x);

typedef struct actual_stringutils_record_3_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_record_3_t;
extern void release_stringutils_record_3_ptr(pointer_t x, type_actual_t stringutils_record_3);

extern bool_t equal_stringutils_record_3_ptr(pointer_t x, pointer_t y, actual_stringutils_record_3_t T);

extern char * json_stringutils_record_3_ptr(pointer_t x,  actual_stringutils_record_3_t T);

actual_stringutils_record_3_t actual_stringutils_record_3(void);

 

extern stringutils_record_3_t update_stringutils_record_3_length(stringutils_record_3_t x, uint8_t v);

extern stringutils_record_3_t update_stringutils_record_3_seq(stringutils_record_3_t x, stringutils_array_2_t v);


//join_inner

struct stringutils_array_4_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         bytestrings__bytestring_t elems[]; };
typedef struct stringutils_array_4_s * stringutils_array_4_t;

extern stringutils_array_4_t new_stringutils_array_4(uint32_t size);

extern void release_stringutils_array_4(stringutils_array_4_t x);

extern stringutils_array_4_t copy_stringutils_array_4(stringutils_array_4_t x);

extern bool_t equal_stringutils_array_4(stringutils_array_4_t x, stringutils_array_4_t y);
extern char * json_stringutils_array_4(stringutils_array_4_t x);

typedef struct actual_stringutils_array_4_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_array_4_t;
extern void release_stringutils_array_4_ptr(pointer_t x, type_actual_t stringutils_array_4);

extern bool_t equal_stringutils_array_4_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_stringutils_array_4_ptr(pointer_t x, type_actual_t T);

actual_stringutils_array_4_t actual_stringutils_array_4(void);

 

extern stringutils_array_4_t update_stringutils_array_4(stringutils_array_4_t x, uint32_t i, bytestrings__bytestring_t v);

extern stringutils_array_4_t upgrade_stringutils_array_4(stringutils_array_4_t x, uint32_t i, bytestrings__bytestring_t v);


//join_inner

struct stringutils_record_5_s {
        uint32_t count; 
        uint32_t length;
        stringutils_array_4_t seq;};
typedef struct stringutils_record_5_s * stringutils_record_5_t;

extern stringutils_record_5_t new_stringutils_record_5(void);

extern void release_stringutils_record_5(stringutils_record_5_t x);

extern stringutils_record_5_t copy_stringutils_record_5(stringutils_record_5_t x);

extern bool_t equal_stringutils_record_5(stringutils_record_5_t x, stringutils_record_5_t y);
extern char * json_stringutils_record_5(stringutils_record_5_t x);

typedef struct actual_stringutils_record_5_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_record_5_t;
extern void release_stringutils_record_5_ptr(pointer_t x, type_actual_t stringutils_record_5);

extern bool_t equal_stringutils_record_5_ptr(pointer_t x, pointer_t y, actual_stringutils_record_5_t T);

extern char * json_stringutils_record_5_ptr(pointer_t x,  actual_stringutils_record_5_t T);

actual_stringutils_record_5_t actual_stringutils_record_5(void);

 

extern stringutils_record_5_t update_stringutils_record_5_length(stringutils_record_5_t x, uint32_t v);

extern stringutils_record_5_t update_stringutils_record_5_seq(stringutils_record_5_t x, stringutils_array_4_t v);


//join_test1

struct stringutils_record_6_s {
        uint32_t count; 
        uint8_t length;
        stringutils_array_4_t seq;};
typedef struct stringutils_record_6_s * stringutils_record_6_t;

extern stringutils_record_6_t new_stringutils_record_6(void);

extern void release_stringutils_record_6(stringutils_record_6_t x);

extern stringutils_record_6_t copy_stringutils_record_6(stringutils_record_6_t x);

extern bool_t equal_stringutils_record_6(stringutils_record_6_t x, stringutils_record_6_t y);
extern char * json_stringutils_record_6(stringutils_record_6_t x);

typedef struct actual_stringutils_record_6_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_stringutils_record_6_t;
extern void release_stringutils_record_6_ptr(pointer_t x, type_actual_t stringutils_record_6);

extern bool_t equal_stringutils_record_6_ptr(pointer_t x, pointer_t y, actual_stringutils_record_6_t T);

extern char * json_stringutils_record_6_ptr(pointer_t x,  actual_stringutils_record_6_t T);

actual_stringutils_record_6_t actual_stringutils_record_6(void);

 

extern stringutils_record_6_t update_stringutils_record_6_length(stringutils_record_6_t x, uint8_t v);

extern stringutils_record_6_t update_stringutils_record_6_seq(stringutils_record_6_t x, stringutils_array_4_t v);



extern bool_t stringutils__digit(uint8_t ivar_1);

extern bool_t stringutils__any(uint8_t ivar_1);

extern bool_t stringutils__whitespace(uint8_t ivar_1);

extern bool_t stringutils__is_quote(uint8_t ivar_1);

extern bool_t stringutils__is_backslash(uint8_t ivar_1);

extern bool_t stringutils__is_slash(uint8_t ivar_1);

extern bool_t stringutils__is_t(uint8_t ivar_1);

extern bool_t stringutils__is_r(uint8_t ivar_1);

extern bool_t stringutils__is_f(uint8_t ivar_1);

extern bool_t stringutils__is_n(uint8_t ivar_1);

extern bool_t stringutils__is_b(uint8_t ivar_1);

extern bool_t stringutils__is_dot(uint8_t ivar_1);

extern bool_t stringutils__is_eE(uint8_t ivar_1);

extern bool_t stringutils__is_plus(uint8_t ivar_1);

extern bool_t stringutils__is_minus(uint8_t ivar_1);

extern bool_t stringutils__is_u(uint8_t ivar_1);

extern bool_t stringutils__is_e(uint8_t ivar_1);

extern bool_t stringutils__is_a(uint8_t ivar_1);

extern bool_t stringutils__is_l(uint8_t ivar_1);

extern bool_t stringutils__is_s(uint8_t ivar_1);

extern bool_t stringutils__escapable(uint8_t ivar_1);

extern uint8_t stringutils__escape_convert(uint8_t ivar_1);

extern bytestrings__bytestring_t stringutils__escape_char(uint8_t ivar_1);

extern bytestrings__bytestring_t stringutils__escape_string_inner(bytestrings__bytestring_t ivar_1, uint32_t ivar_2, bytestrings__bytestring_t ivar_4);

extern bytestrings__bytestring_t stringutils__escape_string(bytestrings__bytestring_t ivar_1);

extern bool_t stringutils__escape_string_test_empty(void);

extern bool_t stringutils__escape_string_test_no_escape(void);

extern bool_t stringutils__escape_string_test_quote(void);

extern bool_t stringutils__escape_string_test_backslash(void);

extern bool_t stringutils__escape_string_test_backspace(void);

extern bool_t stringutils__escape_string_test_tab(void);

extern bool_t stringutils__escape_string_test_newline(void);

extern bool_t stringutils__escape_string_test_formfeed(void);

extern bool_t stringutils__escape_string_test_carriage_return(void);

extern bool_t stringutils__escape_string_test_mixed_string(void);

extern bool_t stringutils__escape_string_test_all_special_chars(void);

extern uint32_t stringutils__first_printable_inner(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern uint32_t stringutils__first_printable(bytestrings__bytestring_t ivar_1);

extern uint32_t stringutils__last_printable_inner(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern uint32_t stringutils__last_printable(bytestrings__bytestring_t ivar_1);

extern bytestrings__bytestring_t stringutils__trim_str(bytestrings__bytestring_t ivar_1);

extern bool_t stringutils__trim_str_test0(void);

extern bool_t stringutils__trim_str_test1(void);

extern bool_t stringutils__trim_str_test2(void);

extern bool_t stringutils__trim_str_test3(void);

extern bool_t stringutils__trim_str_test4(void);

extern bool_t stringutils__trim_str_test5(void);

extern bool_t stringutils__trim_str_test6(void);

extern bytestrings__bytestring_t stringutils__join_inner(bytestrings__bytestring_t ivar_1, stringutils_record_5_t ivar_2, uint32_t ivar_3, bytestrings__bytestring_t ivar_4);

extern bytestrings__bytestring_t stringutils__join(bytestrings__bytestring_t ivar_1, stringutils_record_5_t ivar_2);

extern bool_t stringutils__join_test0(void);

extern bool_t stringutils__join_test1(void);

extern bool_t stringutils__join_test2(void);

extern bool_t stringutils__join_test3(void);
#endif
