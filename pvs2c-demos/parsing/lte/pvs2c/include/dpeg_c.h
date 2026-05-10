//Code generated using pvs2ir
#ifndef _dpeg_h 
#define _dpeg_h

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

#include "strings_c.h"


#include "gen_strings_c.h"


#include "finite_sequences_c.h"


#include "list_adt_c.h"


#include "stringutils_c.h"


#include "lex2_c.h"


#include "array_sequences_c.h"


#include "bytestrings_c.h"


#include "ordstruct_adt_c.h"


#include "ordinals_c.h"


#include "exp2_c.h"


#include "integertypes_c.h"


//cc -O3 -Wall -o dpeg -L /Users/e35480/git/PVS/lib/pvs2c/lib -I /Users/e35480/git/PVS/lib/pvs2c/include stringutils_c.c dpeg_c.c <your main>.c  -lgmp -lpvs-prelude 
//result

struct dpeg__result_adt_s {
         uint32_t count; 
        uint8_t dpeg__result_adt_index;};
typedef struct dpeg__result_adt_s * dpeg__result_adt_t;

extern dpeg__result_adt_t new_dpeg__result_adt(void);

extern void release_dpeg__result_adt(dpeg__result_adt_t x);

extern dpeg__result_adt_t copy_dpeg__result_adt(dpeg__result_adt_t x);

extern bool_t equal_dpeg__result_adt(dpeg__result_adt_t x, dpeg__result_adt_t y);
extern char * json_dpeg__result_adt(dpeg__result_adt_t x);

typedef struct actual_dpeg__result_adt_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg__result_adt_t;
extern void release_dpeg__result_adt_ptr(pointer_t x, type_actual_t dpeg__result_adt);

extern bool_t equal_dpeg__result_adt_ptr(pointer_t x, pointer_t y, actual_dpeg__result_adt_t T);

extern char * json_dpeg__result_adt_ptr(pointer_t x,  actual_dpeg__result_adt_t T);

actual_dpeg__result_adt_t actual_dpeg__result_adt(void);

 

extern dpeg__result_adt_t update_dpeg__result_adt_dpeg__result_adt_index(dpeg__result_adt_t x, uint8_t v);


//success

struct dpeg__success_s {
        uint32_t count; 
        uint8_t dpeg__result_adt_index;
        uint32_t span;};
typedef struct dpeg__success_s * dpeg__success_t;

extern dpeg__success_t new_dpeg__success(void);

extern void release_dpeg__success(dpeg__success_t x);

extern dpeg__success_t copy_dpeg__success(dpeg__success_t x);

extern bool_t equal_dpeg__success(dpeg__success_t x, dpeg__success_t y);
extern char * json_dpeg__success(dpeg__success_t x);

typedef struct actual_dpeg__success_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg__success_t;
extern void release_dpeg__success_ptr(pointer_t x, type_actual_t dpeg__success);

extern bool_t equal_dpeg__success_ptr(pointer_t x, pointer_t y, actual_dpeg__success_t T);

extern char * json_dpeg__success_ptr(pointer_t x,  actual_dpeg__success_t T);

actual_dpeg__success_t actual_dpeg__success(void);

 

extern dpeg__success_t update_dpeg__success_dpeg__result_adt_index(dpeg__success_t x, uint8_t v);

extern dpeg__success_t update_dpeg__success_span(dpeg__success_t x, uint32_t v);


//reduce_nat

struct dpeg_funtype_2_s;
        typedef struct dpeg_funtype_2_s * dpeg_funtype_2_t;

struct dpeg_funtype_2_ftbl_s {mpz_ptr_t (* fptr)(struct dpeg_funtype_2_s *, dpeg__result_adt_t);
        mpz_ptr_t (* mptr)(struct dpeg_funtype_2_s *, dpeg__result_adt_t);
        void (* rptr)(struct dpeg_funtype_2_s *);
        struct dpeg_funtype_2_s * (* cptr)(struct dpeg_funtype_2_s *);};
typedef struct dpeg_funtype_2_ftbl_s * dpeg_funtype_2_ftbl_t;

struct dpeg_funtype_2_hashentry_s {uint32_t keyhash; dpeg__result_adt_t key; mpz_t value;}; 
typedef struct dpeg_funtype_2_hashentry_s dpeg_funtype_2_hashentry_t;

struct dpeg_funtype_2_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_2_hashentry_t * data;}; 
typedef struct dpeg_funtype_2_htbl_s * dpeg_funtype_2_htbl_t;

struct dpeg_funtype_2_s {uint32_t count;
        dpeg_funtype_2_ftbl_t ftbl;
        dpeg_funtype_2_htbl_t htbl;};

extern void release_dpeg_funtype_2(dpeg_funtype_2_t x);

extern dpeg_funtype_2_t copy_dpeg_funtype_2(dpeg_funtype_2_t x);

extern bool_t equal_dpeg_funtype_2(dpeg_funtype_2_t x, dpeg_funtype_2_t y);

extern char* json_dpeg_funtype_2(dpeg_funtype_2_t x);


//reduce_nat

struct dpeg_funtype_3_s;
        typedef struct dpeg_funtype_3_s * dpeg_funtype_3_t;

struct dpeg_funtype_3_ftbl_s {mpz_ptr_t (* fptr)(struct dpeg_funtype_3_s *, uint32_t);
        mpz_ptr_t (* mptr)(struct dpeg_funtype_3_s *, uint32_t);
        void (* rptr)(struct dpeg_funtype_3_s *);
        struct dpeg_funtype_3_s * (* cptr)(struct dpeg_funtype_3_s *);};
typedef struct dpeg_funtype_3_ftbl_s * dpeg_funtype_3_ftbl_t;

struct dpeg_funtype_3_hashentry_s {uint32_t keyhash; uint32_t key; mpz_t value;}; 
typedef struct dpeg_funtype_3_hashentry_s dpeg_funtype_3_hashentry_t;

struct dpeg_funtype_3_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_3_hashentry_t * data;}; 
typedef struct dpeg_funtype_3_htbl_s * dpeg_funtype_3_htbl_t;

struct dpeg_funtype_3_s {uint32_t count;
        dpeg_funtype_3_ftbl_t ftbl;
        dpeg_funtype_3_htbl_t htbl;};

extern void release_dpeg_funtype_3(dpeg_funtype_3_t x);

extern dpeg_funtype_3_t copy_dpeg_funtype_3(dpeg_funtype_3_t x);

extern uint32_t lookup_dpeg_funtype_3(dpeg_funtype_3_htbl_t htbl, uint32_t i, uint32_t ihash);

extern dpeg_funtype_3_t dupdate_dpeg_funtype_3(dpeg_funtype_3_t a, uint32_t i, mpz_ptr_t v);

extern dpeg_funtype_3_t update_dpeg_funtype_3(dpeg_funtype_3_t a, uint32_t i, mpz_ptr_t v);

extern bool_t equal_dpeg_funtype_3(dpeg_funtype_3_t x, dpeg_funtype_3_t y);

extern char* json_dpeg_funtype_3(dpeg_funtype_3_t x);




struct dpeg_closure_4_s;
        typedef struct dpeg_closure_4_s * dpeg_closure_4_t;

struct dpeg_closure_4_s {uint32_t count;
         dpeg_funtype_2_ftbl_t ftbl;
         dpeg_funtype_2_htbl_t htbl;
        mpz_t fvar_1;
        dpeg_funtype_3_t fvar_2;};

mpz_ptr_t f_dpeg_closure_4(struct dpeg_closure_4_s * closure, dpeg__result_adt_t bvar);

mpz_ptr_t m_dpeg_closure_4(struct dpeg_closure_4_s * closure, dpeg__result_adt_t bvar);

extern mpz_ptr_t h_dpeg_closure_4(dpeg__result_adt_t ivar_6, mpz_ptr_t ivar_1, dpeg_funtype_3_t ivar_2);

dpeg_closure_4_t new_dpeg_closure_4(void);

void release_dpeg_closure_4(dpeg_funtype_2_t closure);

dpeg_closure_4_t copy_dpeg_closure_4(dpeg_closure_4_t x);


//REDUCE_nat

struct dpeg_record_5_s {
        uint32_t count; 
        uint32_t project_1;
        dpeg__result_adt_t project_2;};
typedef struct dpeg_record_5_s * dpeg_record_5_t;

extern dpeg_record_5_t new_dpeg_record_5(void);

extern void release_dpeg_record_5(dpeg_record_5_t x);

extern dpeg_record_5_t copy_dpeg_record_5(dpeg_record_5_t x);

extern bool_t equal_dpeg_record_5(dpeg_record_5_t x, dpeg_record_5_t y);
extern char * json_dpeg_record_5(dpeg_record_5_t x);

typedef struct actual_dpeg_record_5_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg_record_5_t;
extern void release_dpeg_record_5_ptr(pointer_t x, type_actual_t dpeg_record_5);

extern bool_t equal_dpeg_record_5_ptr(pointer_t x, pointer_t y, actual_dpeg_record_5_t T);

extern char * json_dpeg_record_5_ptr(pointer_t x,  actual_dpeg_record_5_t T);

actual_dpeg_record_5_t actual_dpeg_record_5(void);

 

extern dpeg_record_5_t update_dpeg_record_5_project_1(dpeg_record_5_t x, uint32_t v);

extern dpeg_record_5_t update_dpeg_record_5_project_2(dpeg_record_5_t x, dpeg__result_adt_t v);


//REDUCE_nat

struct dpeg_funtype_6_s;
        typedef struct dpeg_funtype_6_s * dpeg_funtype_6_t;

struct dpeg_funtype_6_ftbl_s {mpz_ptr_t (* fptr)(struct dpeg_funtype_6_s *, dpeg_record_5_t);
        mpz_ptr_t (* mptr)(struct dpeg_funtype_6_s *, uint32_t, dpeg__result_adt_t);
        void (* rptr)(struct dpeg_funtype_6_s *);
        struct dpeg_funtype_6_s * (* cptr)(struct dpeg_funtype_6_s *);};
typedef struct dpeg_funtype_6_ftbl_s * dpeg_funtype_6_ftbl_t;

struct dpeg_funtype_6_hashentry_s {uint32_t keyhash; dpeg_record_5_t key; mpz_t value;}; 
typedef struct dpeg_funtype_6_hashentry_s dpeg_funtype_6_hashentry_t;

struct dpeg_funtype_6_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_6_hashentry_t * data;}; 
typedef struct dpeg_funtype_6_htbl_s * dpeg_funtype_6_htbl_t;

struct dpeg_funtype_6_s {uint32_t count;
        dpeg_funtype_6_ftbl_t ftbl;
        dpeg_funtype_6_htbl_t htbl;};

extern void release_dpeg_funtype_6(dpeg_funtype_6_t x);

extern dpeg_funtype_6_t copy_dpeg_funtype_6(dpeg_funtype_6_t x);

extern bool_t equal_dpeg_funtype_6(dpeg_funtype_6_t x, dpeg_funtype_6_t y);

extern char* json_dpeg_funtype_6(dpeg_funtype_6_t x);




struct dpeg_closure_7_s;
        typedef struct dpeg_closure_7_s * dpeg_closure_7_t;

struct dpeg_closure_7_s {uint32_t count;
         dpeg_funtype_2_ftbl_t ftbl;
         dpeg_funtype_2_htbl_t htbl;
        dpeg_funtype_6_t fvar_1;
        dpeg_funtype_2_t fvar_2;};

mpz_ptr_t f_dpeg_closure_7(struct dpeg_closure_7_s * closure, dpeg__result_adt_t bvar);

mpz_ptr_t m_dpeg_closure_7(struct dpeg_closure_7_s * closure, dpeg__result_adt_t bvar);

extern mpz_ptr_t h_dpeg_closure_7(dpeg__result_adt_t ivar_7, dpeg_funtype_6_t ivar_3, dpeg_funtype_2_t ivar_1);

dpeg_closure_7_t new_dpeg_closure_7(void);

void release_dpeg_closure_7(dpeg_funtype_2_t closure);

dpeg_closure_7_t copy_dpeg_closure_7(dpeg_closure_7_t x);


//reduce_ordinal

struct dpeg_funtype_8_s;
        typedef struct dpeg_funtype_8_s * dpeg_funtype_8_t;

struct dpeg_funtype_8_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct dpeg_funtype_8_s *, dpeg__result_adt_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct dpeg_funtype_8_s *, dpeg__result_adt_t);
        void (* rptr)(struct dpeg_funtype_8_s *);
        struct dpeg_funtype_8_s * (* cptr)(struct dpeg_funtype_8_s *);};
typedef struct dpeg_funtype_8_ftbl_s * dpeg_funtype_8_ftbl_t;

struct dpeg_funtype_8_hashentry_s {uint32_t keyhash; dpeg__result_adt_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct dpeg_funtype_8_hashentry_s dpeg_funtype_8_hashentry_t;

struct dpeg_funtype_8_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_8_hashentry_t * data;}; 
typedef struct dpeg_funtype_8_htbl_s * dpeg_funtype_8_htbl_t;

struct dpeg_funtype_8_s {uint32_t count;
        dpeg_funtype_8_ftbl_t ftbl;
        dpeg_funtype_8_htbl_t htbl;};

extern void release_dpeg_funtype_8(dpeg_funtype_8_t x);

extern dpeg_funtype_8_t copy_dpeg_funtype_8(dpeg_funtype_8_t x);

extern bool_t equal_dpeg_funtype_8(dpeg_funtype_8_t x, dpeg_funtype_8_t y);

extern char* json_dpeg_funtype_8(dpeg_funtype_8_t x);


//reduce_ordinal

struct dpeg_funtype_9_s;
        typedef struct dpeg_funtype_9_s * dpeg_funtype_9_t;

struct dpeg_funtype_9_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct dpeg_funtype_9_s *, uint32_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct dpeg_funtype_9_s *, uint32_t);
        void (* rptr)(struct dpeg_funtype_9_s *);
        struct dpeg_funtype_9_s * (* cptr)(struct dpeg_funtype_9_s *);};
typedef struct dpeg_funtype_9_ftbl_s * dpeg_funtype_9_ftbl_t;

struct dpeg_funtype_9_hashentry_s {uint32_t keyhash; uint32_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct dpeg_funtype_9_hashentry_s dpeg_funtype_9_hashentry_t;

struct dpeg_funtype_9_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_9_hashentry_t * data;}; 
typedef struct dpeg_funtype_9_htbl_s * dpeg_funtype_9_htbl_t;

struct dpeg_funtype_9_s {uint32_t count;
        dpeg_funtype_9_ftbl_t ftbl;
        dpeg_funtype_9_htbl_t htbl;};

extern void release_dpeg_funtype_9(dpeg_funtype_9_t x);

extern dpeg_funtype_9_t copy_dpeg_funtype_9(dpeg_funtype_9_t x);

extern uint32_t lookup_dpeg_funtype_9(dpeg_funtype_9_htbl_t htbl, uint32_t i, uint32_t ihash);

extern dpeg_funtype_9_t dupdate_dpeg_funtype_9(dpeg_funtype_9_t a, uint32_t i, ordstruct_adt__ordstruct_adt_t v);

extern dpeg_funtype_9_t update_dpeg_funtype_9(dpeg_funtype_9_t a, uint32_t i, ordstruct_adt__ordstruct_adt_t v);

extern bool_t equal_dpeg_funtype_9(dpeg_funtype_9_t x, dpeg_funtype_9_t y);

extern char* json_dpeg_funtype_9(dpeg_funtype_9_t x);




struct dpeg_closure_10_s;
        typedef struct dpeg_closure_10_s * dpeg_closure_10_t;

struct dpeg_closure_10_s {uint32_t count;
         dpeg_funtype_8_ftbl_t ftbl;
         dpeg_funtype_8_htbl_t htbl;
        ordstruct_adt__ordstruct_adt_t fvar_1;
        dpeg_funtype_9_t fvar_2;};

ordstruct_adt__ordstruct_adt_t f_dpeg_closure_10(struct dpeg_closure_10_s * closure, dpeg__result_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_dpeg_closure_10(struct dpeg_closure_10_s * closure, dpeg__result_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_dpeg_closure_10(dpeg__result_adt_t ivar_6, ordstruct_adt__ordstruct_adt_t ivar_1, dpeg_funtype_9_t ivar_2);

dpeg_closure_10_t new_dpeg_closure_10(void);

void release_dpeg_closure_10(dpeg_funtype_8_t closure);

dpeg_closure_10_t copy_dpeg_closure_10(dpeg_closure_10_t x);


//REDUCE_ordinal

struct dpeg_funtype_11_s;
        typedef struct dpeg_funtype_11_s * dpeg_funtype_11_t;

struct dpeg_funtype_11_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct dpeg_funtype_11_s *, dpeg_record_5_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct dpeg_funtype_11_s *, uint32_t, dpeg__result_adt_t);
        void (* rptr)(struct dpeg_funtype_11_s *);
        struct dpeg_funtype_11_s * (* cptr)(struct dpeg_funtype_11_s *);};
typedef struct dpeg_funtype_11_ftbl_s * dpeg_funtype_11_ftbl_t;

struct dpeg_funtype_11_hashentry_s {uint32_t keyhash; dpeg_record_5_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct dpeg_funtype_11_hashentry_s dpeg_funtype_11_hashentry_t;

struct dpeg_funtype_11_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_11_hashentry_t * data;}; 
typedef struct dpeg_funtype_11_htbl_s * dpeg_funtype_11_htbl_t;

struct dpeg_funtype_11_s {uint32_t count;
        dpeg_funtype_11_ftbl_t ftbl;
        dpeg_funtype_11_htbl_t htbl;};

extern void release_dpeg_funtype_11(dpeg_funtype_11_t x);

extern dpeg_funtype_11_t copy_dpeg_funtype_11(dpeg_funtype_11_t x);

extern bool_t equal_dpeg_funtype_11(dpeg_funtype_11_t x, dpeg_funtype_11_t y);

extern char* json_dpeg_funtype_11(dpeg_funtype_11_t x);




struct dpeg_closure_12_s;
        typedef struct dpeg_closure_12_s * dpeg_closure_12_t;

struct dpeg_closure_12_s {uint32_t count;
         dpeg_funtype_8_ftbl_t ftbl;
         dpeg_funtype_8_htbl_t htbl;
        dpeg_funtype_11_t fvar_1;
        dpeg_funtype_8_t fvar_2;};

ordstruct_adt__ordstruct_adt_t f_dpeg_closure_12(struct dpeg_closure_12_s * closure, dpeg__result_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_dpeg_closure_12(struct dpeg_closure_12_s * closure, dpeg__result_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_dpeg_closure_12(dpeg__result_adt_t ivar_7, dpeg_funtype_11_t ivar_3, dpeg_funtype_8_t ivar_1);

dpeg_closure_12_t new_dpeg_closure_12(void);

void release_dpeg_closure_12(dpeg_funtype_8_t closure);

dpeg_closure_12_t copy_dpeg_closure_12(dpeg_closure_12_t x);


//guard

struct dpeg_record_13_s {
        uint32_t count; 
        bytestrings__bytestring_t project_1;
        uint32_t project_2;};
typedef struct dpeg_record_13_s * dpeg_record_13_t;

extern dpeg_record_13_t new_dpeg_record_13(void);

extern void release_dpeg_record_13(dpeg_record_13_t x);

extern dpeg_record_13_t copy_dpeg_record_13(dpeg_record_13_t x);

extern bool_t equal_dpeg_record_13(dpeg_record_13_t x, dpeg_record_13_t y);
extern char * json_dpeg_record_13(dpeg_record_13_t x);

typedef struct actual_dpeg_record_13_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg_record_13_t;
extern void release_dpeg_record_13_ptr(pointer_t x, type_actual_t dpeg_record_13);

extern bool_t equal_dpeg_record_13_ptr(pointer_t x, pointer_t y, actual_dpeg_record_13_t T);

extern char * json_dpeg_record_13_ptr(pointer_t x,  actual_dpeg_record_13_t T);

actual_dpeg_record_13_t actual_dpeg_record_13(void);

 

extern dpeg_record_13_t update_dpeg_record_13_project_1(dpeg_record_13_t x, bytestrings__bytestring_t v);

extern dpeg_record_13_t update_dpeg_record_13_project_2(dpeg_record_13_t x, uint32_t v);


//guard

struct dpeg__guard_s;
        typedef struct dpeg__guard_s * dpeg__guard_t;

struct dpeg__guard_ftbl_s {uint32_t (* fptr)(struct dpeg__guard_s *, dpeg_record_13_t);
        uint32_t (* mptr)(struct dpeg__guard_s *, bytestrings__bytestring_t, uint32_t);
        void (* rptr)(struct dpeg__guard_s *);
        struct dpeg__guard_s * (* cptr)(struct dpeg__guard_s *);};
typedef struct dpeg__guard_ftbl_s * dpeg__guard_ftbl_t;

struct dpeg__guard_hashentry_s {uint32_t keyhash; dpeg_record_13_t key; uint32_t value;}; 
typedef struct dpeg__guard_hashentry_s dpeg__guard_hashentry_t;

struct dpeg__guard_htbl_s {uint32_t size; uint32_t num_entries; dpeg__guard_hashentry_t * data;}; 
typedef struct dpeg__guard_htbl_s * dpeg__guard_htbl_t;

struct dpeg__guard_s {uint32_t count;
        dpeg__guard_ftbl_t ftbl;
        dpeg__guard_htbl_t htbl;};

extern void release_dpeg__guard(dpeg__guard_t x);

extern dpeg__guard_t copy_dpeg__guard(dpeg__guard_t x);

extern bool_t equal_dpeg__guard(dpeg__guard_t x, dpeg__guard_t y);

extern char* json_dpeg__guard(dpeg__guard_t x);


//dpeg_expr

struct dpeg__dpeg_expr_adt_s {
         uint32_t count; 
        uint8_t dpeg__dpeg_expr_adt_index;};
typedef struct dpeg__dpeg_expr_adt_s * dpeg__dpeg_expr_adt_t;

extern dpeg__dpeg_expr_adt_t new_dpeg__dpeg_expr_adt(void);

extern void release_dpeg__dpeg_expr_adt(dpeg__dpeg_expr_adt_t x);

extern dpeg__dpeg_expr_adt_t copy_dpeg__dpeg_expr_adt(dpeg__dpeg_expr_adt_t x);

extern bool_t equal_dpeg__dpeg_expr_adt(dpeg__dpeg_expr_adt_t x, dpeg__dpeg_expr_adt_t y);
extern char * json_dpeg__dpeg_expr_adt(dpeg__dpeg_expr_adt_t x);

typedef struct actual_dpeg__dpeg_expr_adt_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg__dpeg_expr_adt_t;
extern void release_dpeg__dpeg_expr_adt_ptr(pointer_t x, type_actual_t dpeg__dpeg_expr_adt);

extern bool_t equal_dpeg__dpeg_expr_adt_ptr(pointer_t x, pointer_t y, actual_dpeg__dpeg_expr_adt_t T);

extern char * json_dpeg__dpeg_expr_adt_ptr(pointer_t x,  actual_dpeg__dpeg_expr_adt_t T);

actual_dpeg__dpeg_expr_adt_t actual_dpeg__dpeg_expr_adt(void);

 

extern dpeg__dpeg_expr_adt_t update_dpeg__dpeg_expr_adt_dpeg__dpeg_expr_adt_index(dpeg__dpeg_expr_adt_t x, uint8_t v);


//glte

struct dpeg__glte_s {
        uint32_t count; 
        uint8_t dpeg__dpeg_expr_adt_index;
        dpeg__guard_t p;
        uint32_t b;
        uint32_t c;};
typedef struct dpeg__glte_s * dpeg__glte_t;

extern dpeg__glte_t new_dpeg__glte(void);

extern void release_dpeg__glte(dpeg__glte_t x);

extern dpeg__glte_t copy_dpeg__glte(dpeg__glte_t x);

extern bool_t equal_dpeg__glte(dpeg__glte_t x, dpeg__glte_t y);
extern char * json_dpeg__glte(dpeg__glte_t x);

typedef struct actual_dpeg__glte_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg__glte_t;
extern void release_dpeg__glte_ptr(pointer_t x, type_actual_t dpeg__glte);

extern bool_t equal_dpeg__glte_ptr(pointer_t x, pointer_t y, actual_dpeg__glte_t T);

extern char * json_dpeg__glte_ptr(pointer_t x,  actual_dpeg__glte_t T);

actual_dpeg__glte_t actual_dpeg__glte(void);

 

extern dpeg__glte_t update_dpeg__glte_dpeg__dpeg_expr_adt_index(dpeg__glte_t x, uint8_t v);

extern dpeg__glte_t update_dpeg__glte_p(dpeg__glte_t x, dpeg__guard_t v);

extern dpeg__glte_t update_dpeg__glte_b(dpeg__glte_t x, uint32_t v);

extern dpeg__glte_t update_dpeg__glte_c(dpeg__glte_t x, uint32_t v);


//reduce_nat

struct dpeg_funtype_17_s;
        typedef struct dpeg_funtype_17_s * dpeg_funtype_17_t;

struct dpeg_funtype_17_ftbl_s {mpz_ptr_t (* fptr)(struct dpeg_funtype_17_s *, dpeg__dpeg_expr_adt_t);
        mpz_ptr_t (* mptr)(struct dpeg_funtype_17_s *, dpeg__dpeg_expr_adt_t);
        void (* rptr)(struct dpeg_funtype_17_s *);
        struct dpeg_funtype_17_s * (* cptr)(struct dpeg_funtype_17_s *);};
typedef struct dpeg_funtype_17_ftbl_s * dpeg_funtype_17_ftbl_t;

struct dpeg_funtype_17_hashentry_s {uint32_t keyhash; dpeg__dpeg_expr_adt_t key; mpz_t value;}; 
typedef struct dpeg_funtype_17_hashentry_s dpeg_funtype_17_hashentry_t;

struct dpeg_funtype_17_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_17_hashentry_t * data;}; 
typedef struct dpeg_funtype_17_htbl_s * dpeg_funtype_17_htbl_t;

struct dpeg_funtype_17_s {uint32_t count;
        dpeg_funtype_17_ftbl_t ftbl;
        dpeg_funtype_17_htbl_t htbl;};

extern void release_dpeg_funtype_17(dpeg_funtype_17_t x);

extern dpeg_funtype_17_t copy_dpeg_funtype_17(dpeg_funtype_17_t x);

extern bool_t equal_dpeg_funtype_17(dpeg_funtype_17_t x, dpeg_funtype_17_t y);

extern char* json_dpeg_funtype_17(dpeg_funtype_17_t x);


//reduce_nat

struct dpeg_record_18_s {
        uint32_t count; 
        dpeg__guard_t project_1;
        uint32_t project_2;
        uint32_t project_3;};
typedef struct dpeg_record_18_s * dpeg_record_18_t;

extern dpeg_record_18_t new_dpeg_record_18(void);

extern void release_dpeg_record_18(dpeg_record_18_t x);

extern dpeg_record_18_t copy_dpeg_record_18(dpeg_record_18_t x);

extern bool_t equal_dpeg_record_18(dpeg_record_18_t x, dpeg_record_18_t y);
extern char * json_dpeg_record_18(dpeg_record_18_t x);

typedef struct actual_dpeg_record_18_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg_record_18_t;
extern void release_dpeg_record_18_ptr(pointer_t x, type_actual_t dpeg_record_18);

extern bool_t equal_dpeg_record_18_ptr(pointer_t x, pointer_t y, actual_dpeg_record_18_t T);

extern char * json_dpeg_record_18_ptr(pointer_t x,  actual_dpeg_record_18_t T);

actual_dpeg_record_18_t actual_dpeg_record_18(void);

 

extern dpeg_record_18_t update_dpeg_record_18_project_1(dpeg_record_18_t x, dpeg__guard_t v);

extern dpeg_record_18_t update_dpeg_record_18_project_2(dpeg_record_18_t x, uint32_t v);

extern dpeg_record_18_t update_dpeg_record_18_project_3(dpeg_record_18_t x, uint32_t v);


//reduce_nat

struct dpeg_funtype_19_s;
        typedef struct dpeg_funtype_19_s * dpeg_funtype_19_t;

struct dpeg_funtype_19_ftbl_s {mpz_ptr_t (* fptr)(struct dpeg_funtype_19_s *, dpeg_record_18_t);
        mpz_ptr_t (* mptr)(struct dpeg_funtype_19_s *, dpeg__guard_t, uint32_t, uint32_t);
        void (* rptr)(struct dpeg_funtype_19_s *);
        struct dpeg_funtype_19_s * (* cptr)(struct dpeg_funtype_19_s *);};
typedef struct dpeg_funtype_19_ftbl_s * dpeg_funtype_19_ftbl_t;

struct dpeg_funtype_19_hashentry_s {uint32_t keyhash; dpeg_record_18_t key; mpz_t value;}; 
typedef struct dpeg_funtype_19_hashentry_s dpeg_funtype_19_hashentry_t;

struct dpeg_funtype_19_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_19_hashentry_t * data;}; 
typedef struct dpeg_funtype_19_htbl_s * dpeg_funtype_19_htbl_t;

struct dpeg_funtype_19_s {uint32_t count;
        dpeg_funtype_19_ftbl_t ftbl;
        dpeg_funtype_19_htbl_t htbl;};

extern void release_dpeg_funtype_19(dpeg_funtype_19_t x);

extern dpeg_funtype_19_t copy_dpeg_funtype_19(dpeg_funtype_19_t x);

extern bool_t equal_dpeg_funtype_19(dpeg_funtype_19_t x, dpeg_funtype_19_t y);

extern char* json_dpeg_funtype_19(dpeg_funtype_19_t x);




struct dpeg_closure_20_s;
        typedef struct dpeg_closure_20_s * dpeg_closure_20_t;

struct dpeg_closure_20_s {uint32_t count;
         dpeg_funtype_17_ftbl_t ftbl;
         dpeg_funtype_17_htbl_t htbl;
        mpz_t fvar_1;
        dpeg_funtype_19_t fvar_2;
        mpz_t fvar_3;};

mpz_ptr_t f_dpeg_closure_20(struct dpeg_closure_20_s * closure, dpeg__dpeg_expr_adt_t bvar);

mpz_ptr_t m_dpeg_closure_20(struct dpeg_closure_20_s * closure, dpeg__dpeg_expr_adt_t bvar);

extern mpz_ptr_t h_dpeg_closure_20(dpeg__dpeg_expr_adt_t ivar_7, mpz_ptr_t ivar_1, dpeg_funtype_19_t ivar_3, mpz_ptr_t ivar_2);

dpeg_closure_20_t new_dpeg_closure_20(void);

void release_dpeg_closure_20(dpeg_funtype_17_t closure);

dpeg_closure_20_t copy_dpeg_closure_20(dpeg_closure_20_t x);


//REDUCE_nat

struct dpeg_record_21_s {
        uint32_t count; 
        dpeg__guard_t project_1;
        uint32_t project_2;
        uint32_t project_3;
        dpeg__dpeg_expr_adt_t project_4;};
typedef struct dpeg_record_21_s * dpeg_record_21_t;

extern dpeg_record_21_t new_dpeg_record_21(void);

extern void release_dpeg_record_21(dpeg_record_21_t x);

extern dpeg_record_21_t copy_dpeg_record_21(dpeg_record_21_t x);

extern bool_t equal_dpeg_record_21(dpeg_record_21_t x, dpeg_record_21_t y);
extern char * json_dpeg_record_21(dpeg_record_21_t x);

typedef struct actual_dpeg_record_21_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg_record_21_t;
extern void release_dpeg_record_21_ptr(pointer_t x, type_actual_t dpeg_record_21);

extern bool_t equal_dpeg_record_21_ptr(pointer_t x, pointer_t y, actual_dpeg_record_21_t T);

extern char * json_dpeg_record_21_ptr(pointer_t x,  actual_dpeg_record_21_t T);

actual_dpeg_record_21_t actual_dpeg_record_21(void);

 

extern dpeg_record_21_t update_dpeg_record_21_project_1(dpeg_record_21_t x, dpeg__guard_t v);

extern dpeg_record_21_t update_dpeg_record_21_project_2(dpeg_record_21_t x, uint32_t v);

extern dpeg_record_21_t update_dpeg_record_21_project_3(dpeg_record_21_t x, uint32_t v);

extern dpeg_record_21_t update_dpeg_record_21_project_4(dpeg_record_21_t x, dpeg__dpeg_expr_adt_t v);


//REDUCE_nat

struct dpeg_funtype_22_s;
        typedef struct dpeg_funtype_22_s * dpeg_funtype_22_t;

struct dpeg_funtype_22_ftbl_s {mpz_ptr_t (* fptr)(struct dpeg_funtype_22_s *, dpeg_record_21_t);
        mpz_ptr_t (* mptr)(struct dpeg_funtype_22_s *, dpeg__guard_t, uint32_t, uint32_t, dpeg__dpeg_expr_adt_t);
        void (* rptr)(struct dpeg_funtype_22_s *);
        struct dpeg_funtype_22_s * (* cptr)(struct dpeg_funtype_22_s *);};
typedef struct dpeg_funtype_22_ftbl_s * dpeg_funtype_22_ftbl_t;

struct dpeg_funtype_22_hashentry_s {uint32_t keyhash; dpeg_record_21_t key; mpz_t value;}; 
typedef struct dpeg_funtype_22_hashentry_s dpeg_funtype_22_hashentry_t;

struct dpeg_funtype_22_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_22_hashentry_t * data;}; 
typedef struct dpeg_funtype_22_htbl_s * dpeg_funtype_22_htbl_t;

struct dpeg_funtype_22_s {uint32_t count;
        dpeg_funtype_22_ftbl_t ftbl;
        dpeg_funtype_22_htbl_t htbl;};

extern void release_dpeg_funtype_22(dpeg_funtype_22_t x);

extern dpeg_funtype_22_t copy_dpeg_funtype_22(dpeg_funtype_22_t x);

extern bool_t equal_dpeg_funtype_22(dpeg_funtype_22_t x, dpeg_funtype_22_t y);

extern char* json_dpeg_funtype_22(dpeg_funtype_22_t x);




struct dpeg_closure_23_s;
        typedef struct dpeg_closure_23_s * dpeg_closure_23_t;

struct dpeg_closure_23_s {uint32_t count;
         dpeg_funtype_17_ftbl_t ftbl;
         dpeg_funtype_17_htbl_t htbl;
        dpeg_funtype_17_t fvar_1;
        dpeg_funtype_17_t fvar_2;
        dpeg_funtype_22_t fvar_3;};

mpz_ptr_t f_dpeg_closure_23(struct dpeg_closure_23_s * closure, dpeg__dpeg_expr_adt_t bvar);

mpz_ptr_t m_dpeg_closure_23(struct dpeg_closure_23_s * closure, dpeg__dpeg_expr_adt_t bvar);

extern mpz_ptr_t h_dpeg_closure_23(dpeg__dpeg_expr_adt_t ivar_9, dpeg_funtype_17_t ivar_1, dpeg_funtype_17_t ivar_3, dpeg_funtype_22_t ivar_5);

dpeg_closure_23_t new_dpeg_closure_23(void);

void release_dpeg_closure_23(dpeg_funtype_17_t closure);

dpeg_closure_23_t copy_dpeg_closure_23(dpeg_closure_23_t x);


//reduce_ordinal

struct dpeg_funtype_24_s;
        typedef struct dpeg_funtype_24_s * dpeg_funtype_24_t;

struct dpeg_funtype_24_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct dpeg_funtype_24_s *, dpeg__dpeg_expr_adt_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct dpeg_funtype_24_s *, dpeg__dpeg_expr_adt_t);
        void (* rptr)(struct dpeg_funtype_24_s *);
        struct dpeg_funtype_24_s * (* cptr)(struct dpeg_funtype_24_s *);};
typedef struct dpeg_funtype_24_ftbl_s * dpeg_funtype_24_ftbl_t;

struct dpeg_funtype_24_hashentry_s {uint32_t keyhash; dpeg__dpeg_expr_adt_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct dpeg_funtype_24_hashentry_s dpeg_funtype_24_hashentry_t;

struct dpeg_funtype_24_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_24_hashentry_t * data;}; 
typedef struct dpeg_funtype_24_htbl_s * dpeg_funtype_24_htbl_t;

struct dpeg_funtype_24_s {uint32_t count;
        dpeg_funtype_24_ftbl_t ftbl;
        dpeg_funtype_24_htbl_t htbl;};

extern void release_dpeg_funtype_24(dpeg_funtype_24_t x);

extern dpeg_funtype_24_t copy_dpeg_funtype_24(dpeg_funtype_24_t x);

extern bool_t equal_dpeg_funtype_24(dpeg_funtype_24_t x, dpeg_funtype_24_t y);

extern char* json_dpeg_funtype_24(dpeg_funtype_24_t x);


//reduce_ordinal

struct dpeg_funtype_25_s;
        typedef struct dpeg_funtype_25_s * dpeg_funtype_25_t;

struct dpeg_funtype_25_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct dpeg_funtype_25_s *, dpeg_record_18_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct dpeg_funtype_25_s *, dpeg__guard_t, uint32_t, uint32_t);
        void (* rptr)(struct dpeg_funtype_25_s *);
        struct dpeg_funtype_25_s * (* cptr)(struct dpeg_funtype_25_s *);};
typedef struct dpeg_funtype_25_ftbl_s * dpeg_funtype_25_ftbl_t;

struct dpeg_funtype_25_hashentry_s {uint32_t keyhash; dpeg_record_18_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct dpeg_funtype_25_hashentry_s dpeg_funtype_25_hashentry_t;

struct dpeg_funtype_25_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_25_hashentry_t * data;}; 
typedef struct dpeg_funtype_25_htbl_s * dpeg_funtype_25_htbl_t;

struct dpeg_funtype_25_s {uint32_t count;
        dpeg_funtype_25_ftbl_t ftbl;
        dpeg_funtype_25_htbl_t htbl;};

extern void release_dpeg_funtype_25(dpeg_funtype_25_t x);

extern dpeg_funtype_25_t copy_dpeg_funtype_25(dpeg_funtype_25_t x);

extern bool_t equal_dpeg_funtype_25(dpeg_funtype_25_t x, dpeg_funtype_25_t y);

extern char* json_dpeg_funtype_25(dpeg_funtype_25_t x);




struct dpeg_closure_26_s;
        typedef struct dpeg_closure_26_s * dpeg_closure_26_t;

struct dpeg_closure_26_s {uint32_t count;
         dpeg_funtype_24_ftbl_t ftbl;
         dpeg_funtype_24_htbl_t htbl;
        ordstruct_adt__ordstruct_adt_t fvar_1;
        dpeg_funtype_25_t fvar_2;
        ordstruct_adt__ordstruct_adt_t fvar_3;};

ordstruct_adt__ordstruct_adt_t f_dpeg_closure_26(struct dpeg_closure_26_s * closure, dpeg__dpeg_expr_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_dpeg_closure_26(struct dpeg_closure_26_s * closure, dpeg__dpeg_expr_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_dpeg_closure_26(dpeg__dpeg_expr_adt_t ivar_7, ordstruct_adt__ordstruct_adt_t ivar_1, dpeg_funtype_25_t ivar_3, ordstruct_adt__ordstruct_adt_t ivar_2);

dpeg_closure_26_t new_dpeg_closure_26(void);

void release_dpeg_closure_26(dpeg_funtype_24_t closure);

dpeg_closure_26_t copy_dpeg_closure_26(dpeg_closure_26_t x);


//REDUCE_ordinal

struct dpeg_funtype_27_s;
        typedef struct dpeg_funtype_27_s * dpeg_funtype_27_t;

struct dpeg_funtype_27_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct dpeg_funtype_27_s *, dpeg_record_21_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct dpeg_funtype_27_s *, dpeg__guard_t, uint32_t, uint32_t, dpeg__dpeg_expr_adt_t);
        void (* rptr)(struct dpeg_funtype_27_s *);
        struct dpeg_funtype_27_s * (* cptr)(struct dpeg_funtype_27_s *);};
typedef struct dpeg_funtype_27_ftbl_s * dpeg_funtype_27_ftbl_t;

struct dpeg_funtype_27_hashentry_s {uint32_t keyhash; dpeg_record_21_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct dpeg_funtype_27_hashentry_s dpeg_funtype_27_hashentry_t;

struct dpeg_funtype_27_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_27_hashentry_t * data;}; 
typedef struct dpeg_funtype_27_htbl_s * dpeg_funtype_27_htbl_t;

struct dpeg_funtype_27_s {uint32_t count;
        dpeg_funtype_27_ftbl_t ftbl;
        dpeg_funtype_27_htbl_t htbl;};

extern void release_dpeg_funtype_27(dpeg_funtype_27_t x);

extern dpeg_funtype_27_t copy_dpeg_funtype_27(dpeg_funtype_27_t x);

extern bool_t equal_dpeg_funtype_27(dpeg_funtype_27_t x, dpeg_funtype_27_t y);

extern char* json_dpeg_funtype_27(dpeg_funtype_27_t x);




struct dpeg_closure_28_s;
        typedef struct dpeg_closure_28_s * dpeg_closure_28_t;

struct dpeg_closure_28_s {uint32_t count;
         dpeg_funtype_24_ftbl_t ftbl;
         dpeg_funtype_24_htbl_t htbl;
        dpeg_funtype_24_t fvar_1;
        dpeg_funtype_24_t fvar_2;
        dpeg_funtype_27_t fvar_3;};

ordstruct_adt__ordstruct_adt_t f_dpeg_closure_28(struct dpeg_closure_28_s * closure, dpeg__dpeg_expr_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_dpeg_closure_28(struct dpeg_closure_28_s * closure, dpeg__dpeg_expr_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_dpeg_closure_28(dpeg__dpeg_expr_adt_t ivar_9, dpeg_funtype_24_t ivar_1, dpeg_funtype_24_t ivar_3, dpeg_funtype_27_t ivar_5);

dpeg_closure_28_t new_dpeg_closure_28(void);

void release_dpeg_closure_28(dpeg_funtype_24_t closure);

dpeg_closure_28_t copy_dpeg_closure_28(dpeg_closure_28_t x);


//dpeg_grammar

struct dpeg_array_29_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         dpeg__dpeg_expr_adt_t elems[]; };
typedef struct dpeg_array_29_s * dpeg_array_29_t;

extern dpeg_array_29_t new_dpeg_array_29(uint32_t size);

extern void release_dpeg_array_29(dpeg_array_29_t x);

extern dpeg_array_29_t copy_dpeg_array_29(dpeg_array_29_t x);

extern bool_t equal_dpeg_array_29(dpeg_array_29_t x, dpeg_array_29_t y);
extern char * json_dpeg_array_29(dpeg_array_29_t x);

typedef struct actual_dpeg_array_29_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg_array_29_t;
extern void release_dpeg_array_29_ptr(pointer_t x, type_actual_t dpeg_array_29);

extern bool_t equal_dpeg_array_29_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_dpeg_array_29_ptr(pointer_t x, type_actual_t T);

actual_dpeg_array_29_t actual_dpeg_array_29(void);

 

extern dpeg_array_29_t update_dpeg_array_29(dpeg_array_29_t x, uint32_t i, dpeg__dpeg_expr_adt_t v);

extern dpeg_array_29_t upgrade_dpeg_array_29(dpeg_array_29_t x, uint32_t i, dpeg__dpeg_expr_adt_t v);


//dpeg_grammar

struct dpeg__dpeg_grammar_s {
        uint32_t count; 
        uint32_t length;
        dpeg_array_29_t seq;};
typedef struct dpeg__dpeg_grammar_s * dpeg__dpeg_grammar_t;

extern dpeg__dpeg_grammar_t new_dpeg__dpeg_grammar(void);

extern void release_dpeg__dpeg_grammar(dpeg__dpeg_grammar_t x);

extern dpeg__dpeg_grammar_t copy_dpeg__dpeg_grammar(dpeg__dpeg_grammar_t x);

extern bool_t equal_dpeg__dpeg_grammar(dpeg__dpeg_grammar_t x, dpeg__dpeg_grammar_t y);
extern char * json_dpeg__dpeg_grammar(dpeg__dpeg_grammar_t x);

typedef struct actual_dpeg__dpeg_grammar_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg__dpeg_grammar_t;
extern void release_dpeg__dpeg_grammar_ptr(pointer_t x, type_actual_t dpeg__dpeg_grammar);

extern bool_t equal_dpeg__dpeg_grammar_ptr(pointer_t x, pointer_t y, actual_dpeg__dpeg_grammar_t T);

extern char * json_dpeg__dpeg_grammar_ptr(pointer_t x,  actual_dpeg__dpeg_grammar_t T);

actual_dpeg__dpeg_grammar_t actual_dpeg__dpeg_grammar(void);

 

extern dpeg__dpeg_grammar_t update_dpeg__dpeg_grammar_length(dpeg__dpeg_grammar_t x, uint32_t v);

extern dpeg__dpeg_grammar_t update_dpeg__dpeg_grammar_seq(dpeg__dpeg_grammar_t x, dpeg_array_29_t v);


//matches

struct dpeg_funtype_31_s;
        typedef struct dpeg_funtype_31_s * dpeg_funtype_31_t;

struct dpeg_funtype_31_ftbl_s {dpeg__result_adt_t (* fptr)(struct dpeg_funtype_31_s *, dpeg_record_13_t);
        dpeg__result_adt_t (* mptr)(struct dpeg_funtype_31_s *, bytestrings__bytestring_t, uint32_t);
        void (* rptr)(struct dpeg_funtype_31_s *);
        struct dpeg_funtype_31_s * (* cptr)(struct dpeg_funtype_31_s *);};
typedef struct dpeg_funtype_31_ftbl_s * dpeg_funtype_31_ftbl_t;

struct dpeg_funtype_31_hashentry_s {uint32_t keyhash; dpeg_record_13_t key; dpeg__result_adt_t value;}; 
typedef struct dpeg_funtype_31_hashentry_s dpeg_funtype_31_hashentry_t;

struct dpeg_funtype_31_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_31_hashentry_t * data;}; 
typedef struct dpeg_funtype_31_htbl_s * dpeg_funtype_31_htbl_t;

struct dpeg_funtype_31_s {uint32_t count;
        dpeg_funtype_31_ftbl_t ftbl;
        dpeg_funtype_31_htbl_t htbl;};

extern void release_dpeg_funtype_31(dpeg_funtype_31_t x);

extern dpeg_funtype_31_t copy_dpeg_funtype_31(dpeg_funtype_31_t x);

extern bool_t equal_dpeg_funtype_31(dpeg_funtype_31_t x, dpeg_funtype_31_t y);

extern char* json_dpeg_funtype_31(dpeg_funtype_31_t x);




struct dpeg_closure_32_s;
        typedef struct dpeg_closure_32_s * dpeg_closure_32_t;

struct dpeg_closure_32_s {uint32_t count;
         dpeg_funtype_31_ftbl_t ftbl;
         dpeg_funtype_31_htbl_t htbl;
        uint32_t fvar_1;
        dpeg__dpeg_grammar_t fvar_2;};

dpeg__result_adt_t f_dpeg_closure_32(struct dpeg_closure_32_s * closure, dpeg_record_13_t bvar);

dpeg__result_adt_t m_dpeg_closure_32(struct dpeg_closure_32_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern dpeg__result_adt_t h_dpeg_closure_32(bytestrings__bytestring_t ivar_9, uint32_t ivar_10, uint32_t ivar_2, dpeg__dpeg_grammar_t ivar_1);

dpeg_closure_32_t new_dpeg_closure_32(void);

void release_dpeg_closure_32(dpeg_funtype_31_t closure);

dpeg_closure_32_t copy_dpeg_closure_32(dpeg_closure_32_t x);


//zreachable

struct dpeg_funtype_33_s;
        typedef struct dpeg_funtype_33_s * dpeg_funtype_33_t;

struct dpeg_funtype_33_ftbl_s {bool_t (* fptr)(struct dpeg_funtype_33_s *, uint32_t);
        bool_t (* mptr)(struct dpeg_funtype_33_s *, uint32_t);
        void (* rptr)(struct dpeg_funtype_33_s *);
        struct dpeg_funtype_33_s * (* cptr)(struct dpeg_funtype_33_s *);};
typedef struct dpeg_funtype_33_ftbl_s * dpeg_funtype_33_ftbl_t;

struct dpeg_funtype_33_hashentry_s {uint32_t keyhash; uint32_t key; bool_t value;}; 
typedef struct dpeg_funtype_33_hashentry_s dpeg_funtype_33_hashentry_t;

struct dpeg_funtype_33_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_33_hashentry_t * data;}; 
typedef struct dpeg_funtype_33_htbl_s * dpeg_funtype_33_htbl_t;

struct dpeg_funtype_33_s {uint32_t count;
        dpeg_funtype_33_ftbl_t ftbl;
        dpeg_funtype_33_htbl_t htbl;};

extern void release_dpeg_funtype_33(dpeg_funtype_33_t x);

extern dpeg_funtype_33_t copy_dpeg_funtype_33(dpeg_funtype_33_t x);

extern uint32_t lookup_dpeg_funtype_33(dpeg_funtype_33_htbl_t htbl, uint32_t i, uint32_t ihash);

extern dpeg_funtype_33_t dupdate_dpeg_funtype_33(dpeg_funtype_33_t a, uint32_t i, bool_t v);

extern dpeg_funtype_33_t update_dpeg_funtype_33(dpeg_funtype_33_t a, uint32_t i, bool_t v);

extern bool_t equal_dpeg_funtype_33(dpeg_funtype_33_t x, dpeg_funtype_33_t y);

extern char* json_dpeg_funtype_33(dpeg_funtype_33_t x);




struct dpeg_closure_34_s;
        typedef struct dpeg_closure_34_s * dpeg_closure_34_t;

struct dpeg_closure_34_s {uint32_t count;
         dpeg_funtype_33_ftbl_t ftbl;
         dpeg_funtype_33_htbl_t htbl;
        uint32_t fvar_1;
        dpeg__dpeg_grammar_t fvar_2;};

bool_t f_dpeg_closure_34(struct dpeg_closure_34_s * closure, uint32_t bvar);

bool_t m_dpeg_closure_34(struct dpeg_closure_34_s * closure, uint32_t bvar);

extern bool_t h_dpeg_closure_34(uint32_t ivar_8, uint32_t ivar_2, dpeg__dpeg_grammar_t ivar_1);

dpeg_closure_34_t new_dpeg_closure_34(void);

void release_dpeg_closure_34(dpeg_funtype_33_t closure);

dpeg_closure_34_t copy_dpeg_closure_34(dpeg_closure_34_t x);


//mk_guard

struct dpeg_funtype_35_s;
        typedef struct dpeg_funtype_35_s * dpeg_funtype_35_t;

struct dpeg_funtype_35_ftbl_s {uint8_t (* fptr)(struct dpeg_funtype_35_s *, dpeg_record_13_t);
        uint8_t (* mptr)(struct dpeg_funtype_35_s *, bytestrings__bytestring_t, uint32_t);
        void (* rptr)(struct dpeg_funtype_35_s *);
        struct dpeg_funtype_35_s * (* cptr)(struct dpeg_funtype_35_s *);};
typedef struct dpeg_funtype_35_ftbl_s * dpeg_funtype_35_ftbl_t;

struct dpeg_funtype_35_hashentry_s {uint32_t keyhash; dpeg_record_13_t key; uint8_t value;}; 
typedef struct dpeg_funtype_35_hashentry_s dpeg_funtype_35_hashentry_t;

struct dpeg_funtype_35_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_35_hashentry_t * data;}; 
typedef struct dpeg_funtype_35_htbl_s * dpeg_funtype_35_htbl_t;

struct dpeg_funtype_35_s {uint32_t count;
        dpeg_funtype_35_ftbl_t ftbl;
        dpeg_funtype_35_htbl_t htbl;};

extern void release_dpeg_funtype_35(dpeg_funtype_35_t x);

extern dpeg_funtype_35_t copy_dpeg_funtype_35(dpeg_funtype_35_t x);

extern bool_t equal_dpeg_funtype_35(dpeg_funtype_35_t x, dpeg_funtype_35_t y);

extern char* json_dpeg_funtype_35(dpeg_funtype_35_t x);


//mk_guard

struct dpeg_funtype_36_s;
        typedef struct dpeg_funtype_36_s * dpeg_funtype_36_t;

struct dpeg_funtype_36_ftbl_s {bool_t (* fptr)(struct dpeg_funtype_36_s *, uint8_t);
        bool_t (* mptr)(struct dpeg_funtype_36_s *, uint8_t);
        void (* rptr)(struct dpeg_funtype_36_s *);
        struct dpeg_funtype_36_s * (* cptr)(struct dpeg_funtype_36_s *);};
typedef struct dpeg_funtype_36_ftbl_s * dpeg_funtype_36_ftbl_t;

struct dpeg_funtype_36_hashentry_s {uint32_t keyhash; uint8_t key; bool_t value;}; 
typedef struct dpeg_funtype_36_hashentry_s dpeg_funtype_36_hashentry_t;

struct dpeg_funtype_36_htbl_s {uint32_t size; uint32_t num_entries; dpeg_funtype_36_hashentry_t * data;}; 
typedef struct dpeg_funtype_36_htbl_s * dpeg_funtype_36_htbl_t;

struct dpeg_funtype_36_s {uint32_t count;
        dpeg_funtype_36_ftbl_t ftbl;
        dpeg_funtype_36_htbl_t htbl;};

extern void release_dpeg_funtype_36(dpeg_funtype_36_t x);

extern dpeg_funtype_36_t copy_dpeg_funtype_36(dpeg_funtype_36_t x);

extern uint32_t lookup_dpeg_funtype_36(dpeg_funtype_36_htbl_t htbl, uint8_t i, uint32_t ihash);

extern dpeg_funtype_36_t dupdate_dpeg_funtype_36(dpeg_funtype_36_t a, uint8_t i, bool_t v);

extern dpeg_funtype_36_t update_dpeg_funtype_36(dpeg_funtype_36_t a, uint8_t i, bool_t v);

extern bool_t equal_dpeg_funtype_36(dpeg_funtype_36_t x, dpeg_funtype_36_t y);

extern char* json_dpeg_funtype_36(dpeg_funtype_36_t x);




struct dpeg_closure_37_s;
        typedef struct dpeg_closure_37_s * dpeg_closure_37_t;

struct dpeg_closure_37_s {uint32_t count;
         dpeg_funtype_35_ftbl_t ftbl;
         dpeg_funtype_35_htbl_t htbl;
        dpeg_funtype_36_t fvar_1;};

uint8_t f_dpeg_closure_37(struct dpeg_closure_37_s * closure, dpeg_record_13_t bvar);

uint8_t m_dpeg_closure_37(struct dpeg_closure_37_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint8_t h_dpeg_closure_37(bytestrings__bytestring_t ivar_8, uint32_t ivar_9, dpeg_funtype_36_t ivar_1);

dpeg_closure_37_t new_dpeg_closure_37(void);

void release_dpeg_closure_37(dpeg_funtype_35_t closure);

dpeg_closure_37_t copy_dpeg_closure_37(dpeg_closure_37_t x);


//mk_guard

struct dpeg_array_38_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint8_t elems[]; };
typedef struct dpeg_array_38_s * dpeg_array_38_t;

extern dpeg_array_38_t new_dpeg_array_38(uint32_t size);

extern void release_dpeg_array_38(dpeg_array_38_t x);

extern dpeg_array_38_t copy_dpeg_array_38(dpeg_array_38_t x);

extern bool_t equal_dpeg_array_38(dpeg_array_38_t x, dpeg_array_38_t y);
extern char * json_dpeg_array_38(dpeg_array_38_t x);

typedef struct actual_dpeg_array_38_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_dpeg_array_38_t;
extern void release_dpeg_array_38_ptr(pointer_t x, type_actual_t dpeg_array_38);

extern bool_t equal_dpeg_array_38_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_dpeg_array_38_ptr(pointer_t x, type_actual_t T);

actual_dpeg_array_38_t actual_dpeg_array_38(void);

 

extern dpeg_array_38_t update_dpeg_array_38(dpeg_array_38_t x, uint32_t i, uint8_t v);

extern dpeg_array_38_t upgrade_dpeg_array_38(dpeg_array_38_t x, uint32_t i, uint8_t v);




struct dpeg_closure_39_s;
        typedef struct dpeg_closure_39_s * dpeg_closure_39_t;

struct dpeg_closure_39_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_39(struct dpeg_closure_39_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_39(struct dpeg_closure_39_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_39(uint8_t ivar_12);

dpeg_closure_39_t new_dpeg_closure_39(void);

void release_dpeg_closure_39(dpeg_funtype_36_t closure);

dpeg_closure_39_t copy_dpeg_closure_39(dpeg_closure_39_t x);




struct dpeg_closure_40_s;
        typedef struct dpeg_closure_40_s * dpeg_closure_40_t;

struct dpeg_closure_40_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_40(struct dpeg_closure_40_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_40(struct dpeg_closure_40_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_40(bytestrings__bytestring_t ivar_41, uint32_t ivar_42, dpeg_funtype_35_t ivar_37);

dpeg_closure_40_t new_dpeg_closure_40(void);

void release_dpeg_closure_40(dpeg__guard_t closure);

dpeg_closure_40_t copy_dpeg_closure_40(dpeg_closure_40_t x);




struct dpeg_closure_41_s;
        typedef struct dpeg_closure_41_s * dpeg_closure_41_t;

struct dpeg_closure_41_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_41(struct dpeg_closure_41_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_41(struct dpeg_closure_41_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_41(uint8_t ivar_22);

dpeg_closure_41_t new_dpeg_closure_41(void);

void release_dpeg_closure_41(dpeg_funtype_36_t closure);

dpeg_closure_41_t copy_dpeg_closure_41(dpeg_closure_41_t x);




struct dpeg_closure_42_s;
        typedef struct dpeg_closure_42_s * dpeg_closure_42_t;

struct dpeg_closure_42_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_42(struct dpeg_closure_42_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_42(struct dpeg_closure_42_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_42(bytestrings__bytestring_t ivar_51, uint32_t ivar_52, dpeg_funtype_35_t ivar_47);

dpeg_closure_42_t new_dpeg_closure_42(void);

void release_dpeg_closure_42(dpeg__guard_t closure);

dpeg_closure_42_t copy_dpeg_closure_42(dpeg_closure_42_t x);




struct dpeg_closure_43_s;
        typedef struct dpeg_closure_43_s * dpeg_closure_43_t;

struct dpeg_closure_43_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_43(struct dpeg_closure_43_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_43(struct dpeg_closure_43_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_43(uint8_t ivar_61);

dpeg_closure_43_t new_dpeg_closure_43(void);

void release_dpeg_closure_43(dpeg_funtype_36_t closure);

dpeg_closure_43_t copy_dpeg_closure_43(dpeg_closure_43_t x);




struct dpeg_closure_44_s;
        typedef struct dpeg_closure_44_s * dpeg_closure_44_t;

struct dpeg_closure_44_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_44(struct dpeg_closure_44_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_44(struct dpeg_closure_44_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_44(bytestrings__bytestring_t ivar_90, uint32_t ivar_91, dpeg_funtype_35_t ivar_86);

dpeg_closure_44_t new_dpeg_closure_44(void);

void release_dpeg_closure_44(dpeg__guard_t closure);

dpeg_closure_44_t copy_dpeg_closure_44(dpeg_closure_44_t x);




struct dpeg_closure_45_s;
        typedef struct dpeg_closure_45_s * dpeg_closure_45_t;

struct dpeg_closure_45_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_45(struct dpeg_closure_45_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_45(struct dpeg_closure_45_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_45(uint8_t ivar_100);

dpeg_closure_45_t new_dpeg_closure_45(void);

void release_dpeg_closure_45(dpeg_funtype_36_t closure);

dpeg_closure_45_t copy_dpeg_closure_45(dpeg_closure_45_t x);




struct dpeg_closure_46_s;
        typedef struct dpeg_closure_46_s * dpeg_closure_46_t;

struct dpeg_closure_46_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_46(struct dpeg_closure_46_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_46(struct dpeg_closure_46_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_46(bytestrings__bytestring_t ivar_129, uint32_t ivar_130, dpeg_funtype_35_t ivar_125);

dpeg_closure_46_t new_dpeg_closure_46(void);

void release_dpeg_closure_46(dpeg__guard_t closure);

dpeg_closure_46_t copy_dpeg_closure_46(dpeg_closure_46_t x);




struct dpeg_closure_47_s;
        typedef struct dpeg_closure_47_s * dpeg_closure_47_t;

struct dpeg_closure_47_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_47(struct dpeg_closure_47_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_47(struct dpeg_closure_47_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_47(uint8_t ivar_139);

dpeg_closure_47_t new_dpeg_closure_47(void);

void release_dpeg_closure_47(dpeg_funtype_36_t closure);

dpeg_closure_47_t copy_dpeg_closure_47(dpeg_closure_47_t x);




struct dpeg_closure_48_s;
        typedef struct dpeg_closure_48_s * dpeg_closure_48_t;

struct dpeg_closure_48_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_48(struct dpeg_closure_48_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_48(struct dpeg_closure_48_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_48(bytestrings__bytestring_t ivar_168, uint32_t ivar_169, dpeg_funtype_35_t ivar_164);

dpeg_closure_48_t new_dpeg_closure_48(void);

void release_dpeg_closure_48(dpeg__guard_t closure);

dpeg_closure_48_t copy_dpeg_closure_48(dpeg_closure_48_t x);




struct dpeg_closure_49_s;
        typedef struct dpeg_closure_49_s * dpeg_closure_49_t;

struct dpeg_closure_49_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_49(struct dpeg_closure_49_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_49(struct dpeg_closure_49_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_49(uint8_t ivar_178);

dpeg_closure_49_t new_dpeg_closure_49(void);

void release_dpeg_closure_49(dpeg_funtype_36_t closure);

dpeg_closure_49_t copy_dpeg_closure_49(dpeg_closure_49_t x);




struct dpeg_closure_50_s;
        typedef struct dpeg_closure_50_s * dpeg_closure_50_t;

struct dpeg_closure_50_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_50(struct dpeg_closure_50_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_50(struct dpeg_closure_50_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_50(bytestrings__bytestring_t ivar_207, uint32_t ivar_208, dpeg_funtype_35_t ivar_203);

dpeg_closure_50_t new_dpeg_closure_50(void);

void release_dpeg_closure_50(dpeg__guard_t closure);

dpeg_closure_50_t copy_dpeg_closure_50(dpeg_closure_50_t x);




struct dpeg_closure_51_s;
        typedef struct dpeg_closure_51_s * dpeg_closure_51_t;

struct dpeg_closure_51_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_51(struct dpeg_closure_51_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_51(struct dpeg_closure_51_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_51(uint8_t ivar_217);

dpeg_closure_51_t new_dpeg_closure_51(void);

void release_dpeg_closure_51(dpeg_funtype_36_t closure);

dpeg_closure_51_t copy_dpeg_closure_51(dpeg_closure_51_t x);




struct dpeg_closure_52_s;
        typedef struct dpeg_closure_52_s * dpeg_closure_52_t;

struct dpeg_closure_52_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_52(struct dpeg_closure_52_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_52(struct dpeg_closure_52_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_52(bytestrings__bytestring_t ivar_246, uint32_t ivar_247, dpeg_funtype_35_t ivar_242);

dpeg_closure_52_t new_dpeg_closure_52(void);

void release_dpeg_closure_52(dpeg__guard_t closure);

dpeg_closure_52_t copy_dpeg_closure_52(dpeg_closure_52_t x);




struct dpeg_closure_53_s;
        typedef struct dpeg_closure_53_s * dpeg_closure_53_t;

struct dpeg_closure_53_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_53(struct dpeg_closure_53_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_53(struct dpeg_closure_53_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_53(uint8_t ivar_256);

dpeg_closure_53_t new_dpeg_closure_53(void);

void release_dpeg_closure_53(dpeg_funtype_36_t closure);

dpeg_closure_53_t copy_dpeg_closure_53(dpeg_closure_53_t x);




struct dpeg_closure_54_s;
        typedef struct dpeg_closure_54_s * dpeg_closure_54_t;

struct dpeg_closure_54_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_54(struct dpeg_closure_54_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_54(struct dpeg_closure_54_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_54(bytestrings__bytestring_t ivar_285, uint32_t ivar_286, dpeg_funtype_35_t ivar_281);

dpeg_closure_54_t new_dpeg_closure_54(void);

void release_dpeg_closure_54(dpeg__guard_t closure);

dpeg_closure_54_t copy_dpeg_closure_54(dpeg_closure_54_t x);




struct dpeg_closure_55_s;
        typedef struct dpeg_closure_55_s * dpeg_closure_55_t;

struct dpeg_closure_55_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_55(struct dpeg_closure_55_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_55(struct dpeg_closure_55_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_55(uint8_t ivar_295);

dpeg_closure_55_t new_dpeg_closure_55(void);

void release_dpeg_closure_55(dpeg_funtype_36_t closure);

dpeg_closure_55_t copy_dpeg_closure_55(dpeg_closure_55_t x);




struct dpeg_closure_56_s;
        typedef struct dpeg_closure_56_s * dpeg_closure_56_t;

struct dpeg_closure_56_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_56(struct dpeg_closure_56_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_56(struct dpeg_closure_56_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_56(bytestrings__bytestring_t ivar_324, uint32_t ivar_325, dpeg_funtype_35_t ivar_320);

dpeg_closure_56_t new_dpeg_closure_56(void);

void release_dpeg_closure_56(dpeg__guard_t closure);

dpeg_closure_56_t copy_dpeg_closure_56(dpeg_closure_56_t x);




struct dpeg_closure_57_s;
        typedef struct dpeg_closure_57_s * dpeg_closure_57_t;

struct dpeg_closure_57_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_57(struct dpeg_closure_57_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_57(struct dpeg_closure_57_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_57(uint8_t ivar_334);

dpeg_closure_57_t new_dpeg_closure_57(void);

void release_dpeg_closure_57(dpeg_funtype_36_t closure);

dpeg_closure_57_t copy_dpeg_closure_57(dpeg_closure_57_t x);




struct dpeg_closure_58_s;
        typedef struct dpeg_closure_58_s * dpeg_closure_58_t;

struct dpeg_closure_58_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_58(struct dpeg_closure_58_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_58(struct dpeg_closure_58_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_58(bytestrings__bytestring_t ivar_363, uint32_t ivar_364, dpeg_funtype_35_t ivar_359);

dpeg_closure_58_t new_dpeg_closure_58(void);

void release_dpeg_closure_58(dpeg__guard_t closure);

dpeg_closure_58_t copy_dpeg_closure_58(dpeg_closure_58_t x);




struct dpeg_closure_59_s;
        typedef struct dpeg_closure_59_s * dpeg_closure_59_t;

struct dpeg_closure_59_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_59(struct dpeg_closure_59_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_59(struct dpeg_closure_59_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_59(uint8_t ivar_373);

dpeg_closure_59_t new_dpeg_closure_59(void);

void release_dpeg_closure_59(dpeg_funtype_36_t closure);

dpeg_closure_59_t copy_dpeg_closure_59(dpeg_closure_59_t x);




struct dpeg_closure_60_s;
        typedef struct dpeg_closure_60_s * dpeg_closure_60_t;

struct dpeg_closure_60_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_60(struct dpeg_closure_60_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_60(struct dpeg_closure_60_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_60(bytestrings__bytestring_t ivar_402, uint32_t ivar_403, dpeg_funtype_35_t ivar_398);

dpeg_closure_60_t new_dpeg_closure_60(void);

void release_dpeg_closure_60(dpeg__guard_t closure);

dpeg_closure_60_t copy_dpeg_closure_60(dpeg_closure_60_t x);




struct dpeg_closure_61_s;
        typedef struct dpeg_closure_61_s * dpeg_closure_61_t;

struct dpeg_closure_61_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_61(struct dpeg_closure_61_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_61(struct dpeg_closure_61_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_61(uint8_t ivar_412);

dpeg_closure_61_t new_dpeg_closure_61(void);

void release_dpeg_closure_61(dpeg_funtype_36_t closure);

dpeg_closure_61_t copy_dpeg_closure_61(dpeg_closure_61_t x);




struct dpeg_closure_62_s;
        typedef struct dpeg_closure_62_s * dpeg_closure_62_t;

struct dpeg_closure_62_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_62(struct dpeg_closure_62_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_62(struct dpeg_closure_62_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_62(bytestrings__bytestring_t ivar_441, uint32_t ivar_442, dpeg_funtype_35_t ivar_437);

dpeg_closure_62_t new_dpeg_closure_62(void);

void release_dpeg_closure_62(dpeg__guard_t closure);

dpeg_closure_62_t copy_dpeg_closure_62(dpeg_closure_62_t x);




struct dpeg_closure_63_s;
        typedef struct dpeg_closure_63_s * dpeg_closure_63_t;

struct dpeg_closure_63_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_63(struct dpeg_closure_63_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_63(struct dpeg_closure_63_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_63(uint8_t ivar_15);

dpeg_closure_63_t new_dpeg_closure_63(void);

void release_dpeg_closure_63(dpeg_funtype_36_t closure);

dpeg_closure_63_t copy_dpeg_closure_63(dpeg_closure_63_t x);




struct dpeg_closure_64_s;
        typedef struct dpeg_closure_64_s * dpeg_closure_64_t;

struct dpeg_closure_64_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_64(struct dpeg_closure_64_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_64(struct dpeg_closure_64_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_64(bytestrings__bytestring_t ivar_44, uint32_t ivar_45, dpeg_funtype_35_t ivar_40);

dpeg_closure_64_t new_dpeg_closure_64(void);

void release_dpeg_closure_64(dpeg__guard_t closure);

dpeg_closure_64_t copy_dpeg_closure_64(dpeg_closure_64_t x);




struct dpeg_closure_65_s;
        typedef struct dpeg_closure_65_s * dpeg_closure_65_t;

struct dpeg_closure_65_s {uint32_t count;
         dpeg_funtype_35_ftbl_t ftbl;
         dpeg_funtype_35_htbl_t htbl;};

uint8_t f_dpeg_closure_65(struct dpeg_closure_65_s * closure, dpeg_record_13_t bvar);

uint8_t m_dpeg_closure_65(struct dpeg_closure_65_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint8_t h_dpeg_closure_65(bytestrings__bytestring_t ivar_52, uint32_t ivar_53);

dpeg_closure_65_t new_dpeg_closure_65(void);

void release_dpeg_closure_65(dpeg_funtype_35_t closure);

dpeg_closure_65_t copy_dpeg_closure_65(dpeg_closure_65_t x);




struct dpeg_closure_66_s;
        typedef struct dpeg_closure_66_s * dpeg_closure_66_t;

struct dpeg_closure_66_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_66(struct dpeg_closure_66_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_66(struct dpeg_closure_66_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_66(bytestrings__bytestring_t ivar_77, uint32_t ivar_78, dpeg_funtype_35_t ivar_73);

dpeg_closure_66_t new_dpeg_closure_66(void);

void release_dpeg_closure_66(dpeg__guard_t closure);

dpeg_closure_66_t copy_dpeg_closure_66(dpeg_closure_66_t x);




struct dpeg_closure_67_s;
        typedef struct dpeg_closure_67_s * dpeg_closure_67_t;

struct dpeg_closure_67_s {uint32_t count;
         dpeg_funtype_35_ftbl_t ftbl;
         dpeg_funtype_35_htbl_t htbl;};

uint8_t f_dpeg_closure_67(struct dpeg_closure_67_s * closure, dpeg_record_13_t bvar);

uint8_t m_dpeg_closure_67(struct dpeg_closure_67_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint8_t h_dpeg_closure_67(bytestrings__bytestring_t ivar_85, uint32_t ivar_86);

dpeg_closure_67_t new_dpeg_closure_67(void);

void release_dpeg_closure_67(dpeg_funtype_35_t closure);

dpeg_closure_67_t copy_dpeg_closure_67(dpeg_closure_67_t x);




struct dpeg_closure_68_s;
        typedef struct dpeg_closure_68_s * dpeg_closure_68_t;

struct dpeg_closure_68_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_68(struct dpeg_closure_68_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_68(struct dpeg_closure_68_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_68(bytestrings__bytestring_t ivar_110, uint32_t ivar_111, dpeg_funtype_35_t ivar_106);

dpeg_closure_68_t new_dpeg_closure_68(void);

void release_dpeg_closure_68(dpeg__guard_t closure);

dpeg_closure_68_t copy_dpeg_closure_68(dpeg_closure_68_t x);




struct dpeg_closure_69_s;
        typedef struct dpeg_closure_69_s * dpeg_closure_69_t;

struct dpeg_closure_69_s {uint32_t count;
         dpeg_funtype_35_ftbl_t ftbl;
         dpeg_funtype_35_htbl_t htbl;};

uint8_t f_dpeg_closure_69(struct dpeg_closure_69_s * closure, dpeg_record_13_t bvar);

uint8_t m_dpeg_closure_69(struct dpeg_closure_69_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint8_t h_dpeg_closure_69(bytestrings__bytestring_t ivar_118, uint32_t ivar_119);

dpeg_closure_69_t new_dpeg_closure_69(void);

void release_dpeg_closure_69(dpeg_funtype_35_t closure);

dpeg_closure_69_t copy_dpeg_closure_69(dpeg_closure_69_t x);




struct dpeg_closure_70_s;
        typedef struct dpeg_closure_70_s * dpeg_closure_70_t;

struct dpeg_closure_70_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_70(struct dpeg_closure_70_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_70(struct dpeg_closure_70_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_70(bytestrings__bytestring_t ivar_143, uint32_t ivar_144, dpeg_funtype_35_t ivar_139);

dpeg_closure_70_t new_dpeg_closure_70(void);

void release_dpeg_closure_70(dpeg__guard_t closure);

dpeg_closure_70_t copy_dpeg_closure_70(dpeg_closure_70_t x);




struct dpeg_closure_71_s;
        typedef struct dpeg_closure_71_s * dpeg_closure_71_t;

struct dpeg_closure_71_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_71(struct dpeg_closure_71_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_71(struct dpeg_closure_71_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_71(uint8_t ivar_17);

dpeg_closure_71_t new_dpeg_closure_71(void);

void release_dpeg_closure_71(dpeg_funtype_36_t closure);

dpeg_closure_71_t copy_dpeg_closure_71(dpeg_closure_71_t x);




struct dpeg_closure_72_s;
        typedef struct dpeg_closure_72_s * dpeg_closure_72_t;

struct dpeg_closure_72_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_72(struct dpeg_closure_72_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_72(struct dpeg_closure_72_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_72(bytestrings__bytestring_t ivar_46, uint32_t ivar_47, dpeg_funtype_35_t ivar_42);

dpeg_closure_72_t new_dpeg_closure_72(void);

void release_dpeg_closure_72(dpeg__guard_t closure);

dpeg_closure_72_t copy_dpeg_closure_72(dpeg_closure_72_t x);




struct dpeg_closure_73_s;
        typedef struct dpeg_closure_73_s * dpeg_closure_73_t;

struct dpeg_closure_73_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_73(struct dpeg_closure_73_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_73(struct dpeg_closure_73_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_73(uint8_t ivar_56);

dpeg_closure_73_t new_dpeg_closure_73(void);

void release_dpeg_closure_73(dpeg_funtype_36_t closure);

dpeg_closure_73_t copy_dpeg_closure_73(dpeg_closure_73_t x);




struct dpeg_closure_74_s;
        typedef struct dpeg_closure_74_s * dpeg_closure_74_t;

struct dpeg_closure_74_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_74(struct dpeg_closure_74_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_74(struct dpeg_closure_74_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_74(bytestrings__bytestring_t ivar_85, uint32_t ivar_86, dpeg_funtype_35_t ivar_81);

dpeg_closure_74_t new_dpeg_closure_74(void);

void release_dpeg_closure_74(dpeg__guard_t closure);

dpeg_closure_74_t copy_dpeg_closure_74(dpeg_closure_74_t x);




struct dpeg_closure_75_s;
        typedef struct dpeg_closure_75_s * dpeg_closure_75_t;

struct dpeg_closure_75_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_75(struct dpeg_closure_75_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_75(struct dpeg_closure_75_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_75(uint8_t ivar_95);

dpeg_closure_75_t new_dpeg_closure_75(void);

void release_dpeg_closure_75(dpeg_funtype_36_t closure);

dpeg_closure_75_t copy_dpeg_closure_75(dpeg_closure_75_t x);




struct dpeg_closure_76_s;
        typedef struct dpeg_closure_76_s * dpeg_closure_76_t;

struct dpeg_closure_76_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_76(struct dpeg_closure_76_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_76(struct dpeg_closure_76_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_76(bytestrings__bytestring_t ivar_124, uint32_t ivar_125, dpeg_funtype_35_t ivar_120);

dpeg_closure_76_t new_dpeg_closure_76(void);

void release_dpeg_closure_76(dpeg__guard_t closure);

dpeg_closure_76_t copy_dpeg_closure_76(dpeg_closure_76_t x);




struct dpeg_closure_77_s;
        typedef struct dpeg_closure_77_s * dpeg_closure_77_t;

struct dpeg_closure_77_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_77(struct dpeg_closure_77_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_77(struct dpeg_closure_77_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_77(uint8_t ivar_134);

dpeg_closure_77_t new_dpeg_closure_77(void);

void release_dpeg_closure_77(dpeg_funtype_36_t closure);

dpeg_closure_77_t copy_dpeg_closure_77(dpeg_closure_77_t x);




struct dpeg_closure_78_s;
        typedef struct dpeg_closure_78_s * dpeg_closure_78_t;

struct dpeg_closure_78_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_78(struct dpeg_closure_78_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_78(struct dpeg_closure_78_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_78(bytestrings__bytestring_t ivar_163, uint32_t ivar_164, dpeg_funtype_35_t ivar_159);

dpeg_closure_78_t new_dpeg_closure_78(void);

void release_dpeg_closure_78(dpeg__guard_t closure);

dpeg_closure_78_t copy_dpeg_closure_78(dpeg_closure_78_t x);




struct dpeg_closure_79_s;
        typedef struct dpeg_closure_79_s * dpeg_closure_79_t;

struct dpeg_closure_79_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_79(struct dpeg_closure_79_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_79(struct dpeg_closure_79_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_79(uint8_t ivar_173);

dpeg_closure_79_t new_dpeg_closure_79(void);

void release_dpeg_closure_79(dpeg_funtype_36_t closure);

dpeg_closure_79_t copy_dpeg_closure_79(dpeg_closure_79_t x);




struct dpeg_closure_80_s;
        typedef struct dpeg_closure_80_s * dpeg_closure_80_t;

struct dpeg_closure_80_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_80(struct dpeg_closure_80_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_80(struct dpeg_closure_80_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_80(bytestrings__bytestring_t ivar_202, uint32_t ivar_203, dpeg_funtype_35_t ivar_198);

dpeg_closure_80_t new_dpeg_closure_80(void);

void release_dpeg_closure_80(dpeg__guard_t closure);

dpeg_closure_80_t copy_dpeg_closure_80(dpeg_closure_80_t x);




struct dpeg_closure_81_s;
        typedef struct dpeg_closure_81_s * dpeg_closure_81_t;

struct dpeg_closure_81_s {uint32_t count;
         dpeg_funtype_36_ftbl_t ftbl;
         dpeg_funtype_36_htbl_t htbl;};

bool_t f_dpeg_closure_81(struct dpeg_closure_81_s * closure, uint8_t bvar);

bool_t m_dpeg_closure_81(struct dpeg_closure_81_s * closure, uint8_t bvar);

extern bool_t h_dpeg_closure_81(uint8_t ivar_212);

dpeg_closure_81_t new_dpeg_closure_81(void);

void release_dpeg_closure_81(dpeg_funtype_36_t closure);

dpeg_closure_81_t copy_dpeg_closure_81(dpeg_closure_81_t x);




struct dpeg_closure_82_s;
        typedef struct dpeg_closure_82_s * dpeg_closure_82_t;

struct dpeg_closure_82_s {uint32_t count;
         dpeg__guard_ftbl_t ftbl;
         dpeg__guard_htbl_t htbl;
        dpeg_funtype_35_t fvar_1;};

uint32_t f_dpeg_closure_82(struct dpeg_closure_82_s * closure, dpeg_record_13_t bvar);

uint32_t m_dpeg_closure_82(struct dpeg_closure_82_s * closure, bytestrings__bytestring_t bvar_1, uint32_t bvar_2);

extern uint32_t h_dpeg_closure_82(bytestrings__bytestring_t ivar_241, uint32_t ivar_242, dpeg_funtype_35_t ivar_237);

dpeg_closure_82_t new_dpeg_closure_82(void);

void release_dpeg_closure_82(dpeg__guard_t closure);

dpeg_closure_82_t copy_dpeg_closure_82(dpeg_closure_82_t x);



extern bool_t rec_dpeg__failurep(dpeg__result_adt_t ivar_1);

extern bool_t rec_dpeg__successp(dpeg__result_adt_t ivar_1);

extern dpeg__success_t update_dpeg__result_adt_span(dpeg__result_adt_t ivar_1, uint32_t ivar_3);

extern uint32_t acc_dpeg__result_adt_span(dpeg__result_adt_t ivar_1);

extern dpeg__result_adt_t con_dpeg__failure(void);

extern dpeg__result_adt_t con_dpeg__success(uint32_t ivar_2);

extern uint8_t dpeg__ord_1(dpeg__result_adt_t ivar_1);

extern bool_t dpeg__subterm_1(dpeg__result_adt_t ivar_1, dpeg__result_adt_t ivar_2);

extern bool_t dpeg__doublelessp_1(dpeg__result_adt_t ivar_1, dpeg__result_adt_t ivar_2);

extern dpeg_funtype_2_t dpeg__reduce_nat_1(mpz_ptr_t ivar_1, dpeg_funtype_3_t ivar_2);

extern dpeg_funtype_2_t dpeg__REDUCE_nat_1(dpeg_funtype_2_t ivar_1, dpeg_funtype_6_t ivar_3);

extern dpeg_funtype_8_t dpeg__reduce_ordinal_1(ordstruct_adt__ordstruct_adt_t ivar_1, dpeg_funtype_9_t ivar_2);

extern dpeg_funtype_8_t dpeg__REDUCE_ordinal_1(dpeg_funtype_8_t ivar_1, dpeg_funtype_11_t ivar_3);

extern bool_t rec_dpeg__failp(dpeg__dpeg_expr_adt_t ivar_1);

extern bool_t rec_dpeg__skipp(dpeg__dpeg_expr_adt_t ivar_1);

extern bool_t rec_dpeg__gltep(dpeg__dpeg_expr_adt_t ivar_1);

extern dpeg__glte_t update_dpeg__dpeg_expr_adt_p(dpeg__dpeg_expr_adt_t ivar_1, dpeg__guard_t ivar_3);

extern dpeg__guard_t acc_dpeg__dpeg_expr_adt_p(dpeg__dpeg_expr_adt_t ivar_1);

extern dpeg__glte_t update_dpeg__dpeg_expr_adt_b(dpeg__dpeg_expr_adt_t ivar_1, uint32_t ivar_3);

extern uint32_t acc_dpeg__dpeg_expr_adt_b(dpeg__dpeg_expr_adt_t ivar_1);

extern dpeg__glte_t update_dpeg__dpeg_expr_adt_c(dpeg__dpeg_expr_adt_t ivar_1, uint32_t ivar_3);

extern uint32_t acc_dpeg__dpeg_expr_adt_c(dpeg__dpeg_expr_adt_t ivar_1);

extern dpeg__dpeg_expr_adt_t con_dpeg__fail(void);

extern dpeg__dpeg_expr_adt_t con_dpeg__skip(void);

extern dpeg__dpeg_expr_adt_t con_dpeg__glte(dpeg__guard_t ivar_2, uint32_t ivar_3, uint32_t ivar_4);

extern uint8_t dpeg__ord_2(dpeg__dpeg_expr_adt_t ivar_1);

extern bool_t dpeg__subterm_2(dpeg__dpeg_expr_adt_t ivar_1, dpeg__dpeg_expr_adt_t ivar_2);

extern bool_t dpeg__doublelessp_2(dpeg__dpeg_expr_adt_t ivar_1, dpeg__dpeg_expr_adt_t ivar_2);

extern dpeg_funtype_17_t dpeg__reduce_nat_2(mpz_ptr_t ivar_1, mpz_ptr_t ivar_2, dpeg_funtype_19_t ivar_3);

extern dpeg_funtype_17_t dpeg__REDUCE_nat_2(dpeg_funtype_17_t ivar_1, dpeg_funtype_17_t ivar_3, dpeg_funtype_22_t ivar_5);

extern dpeg_funtype_24_t dpeg__reduce_ordinal_2(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2, dpeg_funtype_25_t ivar_3);

extern dpeg_funtype_24_t dpeg__REDUCE_ordinal_2(dpeg_funtype_24_t ivar_1, dpeg_funtype_24_t ivar_3, dpeg_funtype_27_t ivar_5);

extern dpeg_funtype_31_t dpeg__matches(dpeg__dpeg_grammar_t ivar_1, uint32_t ivar_2);

extern dpeg__result_adt_t dpeg__result_sofar(uint32_t ivar_1, dpeg__result_adt_t ivar_2);

extern mpz_ptr_t dpeg__encode_result(uint32_t ivar_1, dpeg__result_adt_t ivar_2);

extern dpeg__result_adt_t dpeg__decode_result(uint32_t ivar_1);

extern uint32_t dpeg__dpeg_parse(dpeg__dpeg_grammar_t ivar_1, uint32_t ivar_2, bytestrings__bytestring_t ivar_4, uint32_t ivar_5, uint32_t ivar_7);

extern dpeg_funtype_33_t dpeg__zreachable(dpeg__dpeg_grammar_t ivar_1, uint32_t ivar_2);

extern bool_t dpeg__skipzreachable(dpeg__dpeg_grammar_t ivar_1, uint32_t ivar_2);

extern dpeg_funtype_35_t dpeg__mk_guard(dpeg_funtype_36_t ivar_1);

extern dpeg__dpeg_grammar_t dpeg__wspace_grammar(void);

extern bool_t dpeg__test_wspace1(void);

extern bool_t dpeg__test_wspace2(void);

extern bool_t dpeg__test_wspace3(void);

extern bool_t dpeg__test_wspace4(void);

extern bool_t dpeg__is_plus_minus(uint8_t ivar_1);

extern dpeg__dpeg_grammar_t dpeg__numeral_grammar(void);

extern bool_t dpeg__test_numeral1(void);

extern bool_t dpeg__test_numeral2(void);

extern bool_t dpeg__test_numeral3(void);

extern bool_t dpeg__test_numeral4(void);

extern bool_t dpeg__test_numeral5(void);

extern bool_t dpeg__test_numeral6(void);

extern bool_t dpeg__test_numeral7(void);

extern bool_t dpeg__test_numeral8(void);

extern uint8_t dpeg__key_true_guard(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern uint8_t dpeg__key_false_guard(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern uint8_t dpeg__key_null_guard(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern dpeg__dpeg_grammar_t dpeg__key_grammar(void);

extern bool_t dpeg__test_key1(void);

extern bool_t dpeg__test_key2(void);

extern bool_t dpeg__test_key3(void);

extern bool_t dpeg__test_key4(void);

extern bool_t dpeg__test_key5(void);

extern uint8_t dpeg__ebackslash(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern uint8_t dpeg__equote(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern dpeg__dpeg_grammar_t dpeg__string_grammar(void);

extern bool_t dpeg__test_string1(void);

extern bool_t dpeg__test_string1_1(void);

extern bool_t dpeg__test_string2(void);

extern bool_t dpeg__test_string3(void);

extern bool_t dpeg__test_string3_1(void);

extern bool_t dpeg__test_string4(void);

extern bool_t dpeg__test_string4_1(void);

extern bool_t dpeg__test_string5(void);

extern bool_t dpeg__test_string5_1(void);

extern bool_t dpeg__test_string6(void);

extern bool_t dpeg__test_string6_1(void);
#endif
