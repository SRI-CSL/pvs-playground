//Code generated using pvs2ir
#ifndef _ltedpeg_h 
#define _ltedpeg_h

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

#include "lex2_c.h"


#include "bytestrings_c.h"


#include "real_defs_c.h"


#include "arrayCount_c.h"


#include "array_sequences_c.h"


#include "dpeg_c.h"


#include "ordstruct_adt_c.h"


#include "ordinals_c.h"


#include "exp2_c.h"


#include "integertypes_c.h"


//cc -O3 -Wall -o ltedpeg -L /Users/e35480/git/PVS/lib/pvs2c/lib -I /Users/e35480/git/PVS/lib/pvs2c/include arrayCount_c.c dpeg_c.c ltedpeg_c.c <your main>.c  -lgmp -lpvs-prelude 
//strings

struct ltedpeg__strings_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint8_t elems[]; };
typedef struct ltedpeg__strings_s * ltedpeg__strings_t;

extern ltedpeg__strings_t new_ltedpeg__strings(uint32_t size);

extern void release_ltedpeg__strings(ltedpeg__strings_t x);

extern ltedpeg__strings_t copy_ltedpeg__strings(ltedpeg__strings_t x);

extern bool_t equal_ltedpeg__strings(ltedpeg__strings_t x, ltedpeg__strings_t y);
extern char * json_ltedpeg__strings(ltedpeg__strings_t x);

typedef struct actual_ltedpeg__strings_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__strings_t;
extern void release_ltedpeg__strings_ptr(pointer_t x, type_actual_t ltedpeg__strings);

extern bool_t equal_ltedpeg__strings_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpeg__strings_ptr(pointer_t x, type_actual_t T);

actual_ltedpeg__strings_t actual_ltedpeg__strings(void);

 

extern ltedpeg__strings_t update_ltedpeg__strings(ltedpeg__strings_t x, uint32_t i, uint8_t v);

extern ltedpeg__strings_t upgrade_ltedpeg__strings(ltedpeg__strings_t x, uint32_t i, uint8_t v);


//ent

struct ltedpeg__ent_adt_s {
         uint32_t count; 
        uint8_t ltedpeg__ent_adt_index;};
typedef struct ltedpeg__ent_adt_s * ltedpeg__ent_adt_t;

extern ltedpeg__ent_adt_t new_ltedpeg__ent_adt(void);

extern void release_ltedpeg__ent_adt(ltedpeg__ent_adt_t x);

extern ltedpeg__ent_adt_t copy_ltedpeg__ent_adt(ltedpeg__ent_adt_t x);

extern bool_t equal_ltedpeg__ent_adt(ltedpeg__ent_adt_t x, ltedpeg__ent_adt_t y);
extern char * json_ltedpeg__ent_adt(ltedpeg__ent_adt_t x);

typedef struct actual_ltedpeg__ent_adt_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__ent_adt_t;
extern void release_ltedpeg__ent_adt_ptr(pointer_t x, type_actual_t ltedpeg__ent_adt);

extern bool_t equal_ltedpeg__ent_adt_ptr(pointer_t x, pointer_t y, actual_ltedpeg__ent_adt_t T);

extern char * json_ltedpeg__ent_adt_ptr(pointer_t x,  actual_ltedpeg__ent_adt_t T);

actual_ltedpeg__ent_adt_t actual_ltedpeg__ent_adt(void);

 

extern ltedpeg__ent_adt_t update_ltedpeg__ent_adt_ltedpeg__ent_adt_index(ltedpeg__ent_adt_t x, uint8_t v);


//fail

struct ltedpeg__fail_s {
        uint32_t count; 
        uint8_t ltedpeg__ent_adt_index;
        uint64_t dep;};
typedef struct ltedpeg__fail_s * ltedpeg__fail_t;

extern ltedpeg__fail_t new_ltedpeg__fail(void);

extern void release_ltedpeg__fail(ltedpeg__fail_t x);

extern ltedpeg__fail_t copy_ltedpeg__fail(ltedpeg__fail_t x);

extern bool_t equal_ltedpeg__fail(ltedpeg__fail_t x, ltedpeg__fail_t y);
extern char * json_ltedpeg__fail(ltedpeg__fail_t x);

typedef struct actual_ltedpeg__fail_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__fail_t;
extern void release_ltedpeg__fail_ptr(pointer_t x, type_actual_t ltedpeg__fail);

extern bool_t equal_ltedpeg__fail_ptr(pointer_t x, pointer_t y, actual_ltedpeg__fail_t T);

extern char * json_ltedpeg__fail_ptr(pointer_t x,  actual_ltedpeg__fail_t T);

actual_ltedpeg__fail_t actual_ltedpeg__fail(void);

 

extern ltedpeg__fail_t update_ltedpeg__fail_ltedpeg__ent_adt_index(ltedpeg__fail_t x, uint8_t v);

extern ltedpeg__fail_t update_ltedpeg__fail_dep(ltedpeg__fail_t x, uint64_t v);


//good

struct ltedpeg__good_s {
        uint32_t count; 
        uint8_t ltedpeg__ent_adt_index;
        uint64_t dep;
        uint32_t span;};
typedef struct ltedpeg__good_s * ltedpeg__good_t;

extern ltedpeg__good_t new_ltedpeg__good(void);

extern void release_ltedpeg__good(ltedpeg__good_t x);

extern ltedpeg__good_t copy_ltedpeg__good(ltedpeg__good_t x);

extern bool_t equal_ltedpeg__good(ltedpeg__good_t x, ltedpeg__good_t y);
extern char * json_ltedpeg__good(ltedpeg__good_t x);

typedef struct actual_ltedpeg__good_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__good_t;
extern void release_ltedpeg__good_ptr(pointer_t x, type_actual_t ltedpeg__good);

extern bool_t equal_ltedpeg__good_ptr(pointer_t x, pointer_t y, actual_ltedpeg__good_t T);

extern char * json_ltedpeg__good_ptr(pointer_t x,  actual_ltedpeg__good_t T);

actual_ltedpeg__good_t actual_ltedpeg__good(void);

 

extern ltedpeg__good_t update_ltedpeg__good_ltedpeg__ent_adt_index(ltedpeg__good_t x, uint8_t v);

extern ltedpeg__good_t update_ltedpeg__good_dep(ltedpeg__good_t x, uint64_t v);

extern ltedpeg__good_t update_ltedpeg__good_span(ltedpeg__good_t x, uint32_t v);


//push

struct ltedpeg__push_s {
        uint32_t count; 
        uint8_t ltedpeg__ent_adt_index;
        uint32_t pos;
        uint8_t nt;};
typedef struct ltedpeg__push_s * ltedpeg__push_t;

extern ltedpeg__push_t new_ltedpeg__push(void);

extern void release_ltedpeg__push(ltedpeg__push_t x);

extern ltedpeg__push_t copy_ltedpeg__push(ltedpeg__push_t x);

extern bool_t equal_ltedpeg__push(ltedpeg__push_t x, ltedpeg__push_t y);
extern char * json_ltedpeg__push(ltedpeg__push_t x);

typedef struct actual_ltedpeg__push_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__push_t;
extern void release_ltedpeg__push_ptr(pointer_t x, type_actual_t ltedpeg__push);

extern bool_t equal_ltedpeg__push_ptr(pointer_t x, pointer_t y, actual_ltedpeg__push_t T);

extern char * json_ltedpeg__push_ptr(pointer_t x,  actual_ltedpeg__push_t T);

actual_ltedpeg__push_t actual_ltedpeg__push(void);

 

extern ltedpeg__push_t update_ltedpeg__push_ltedpeg__ent_adt_index(ltedpeg__push_t x, uint8_t v);

extern ltedpeg__push_t update_ltedpeg__push_pos(ltedpeg__push_t x, uint32_t v);

extern ltedpeg__push_t update_ltedpeg__push_nt(ltedpeg__push_t x, uint8_t v);


//reduce_nat

struct ltedpeg_funtype_5_s;
        typedef struct ltedpeg_funtype_5_s * ltedpeg_funtype_5_t;

struct ltedpeg_funtype_5_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_5_s *, ltedpeg__ent_adt_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_5_s *, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_5_s *);
        struct ltedpeg_funtype_5_s * (* cptr)(struct ltedpeg_funtype_5_s *);};
typedef struct ltedpeg_funtype_5_ftbl_s * ltedpeg_funtype_5_ftbl_t;

struct ltedpeg_funtype_5_hashentry_s {uint32_t keyhash; ltedpeg__ent_adt_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_5_hashentry_s ltedpeg_funtype_5_hashentry_t;

struct ltedpeg_funtype_5_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_5_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_5_htbl_s * ltedpeg_funtype_5_htbl_t;

struct ltedpeg_funtype_5_s {uint32_t count;
        ltedpeg_funtype_5_ftbl_t ftbl;
        ltedpeg_funtype_5_htbl_t htbl;};

extern void release_ltedpeg_funtype_5(ltedpeg_funtype_5_t x);

extern ltedpeg_funtype_5_t copy_ltedpeg_funtype_5(ltedpeg_funtype_5_t x);

extern bool_t equal_ltedpeg_funtype_5(ltedpeg_funtype_5_t x, ltedpeg_funtype_5_t y);

extern char* json_ltedpeg_funtype_5(ltedpeg_funtype_5_t x);


//reduce_nat

struct ltedpeg_funtype_6_s;
        typedef struct ltedpeg_funtype_6_s * ltedpeg_funtype_6_t;

struct ltedpeg_funtype_6_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_6_s *, uint64_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_6_s *, uint64_t);
        void (* rptr)(struct ltedpeg_funtype_6_s *);
        struct ltedpeg_funtype_6_s * (* cptr)(struct ltedpeg_funtype_6_s *);};
typedef struct ltedpeg_funtype_6_ftbl_s * ltedpeg_funtype_6_ftbl_t;

struct ltedpeg_funtype_6_hashentry_s {uint32_t keyhash; uint64_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_6_hashentry_s ltedpeg_funtype_6_hashentry_t;

struct ltedpeg_funtype_6_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_6_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_6_htbl_s * ltedpeg_funtype_6_htbl_t;

struct ltedpeg_funtype_6_s {uint32_t count;
        ltedpeg_funtype_6_ftbl_t ftbl;
        ltedpeg_funtype_6_htbl_t htbl;};

extern void release_ltedpeg_funtype_6(ltedpeg_funtype_6_t x);

extern ltedpeg_funtype_6_t copy_ltedpeg_funtype_6(ltedpeg_funtype_6_t x);

extern uint32_t lookup_ltedpeg_funtype_6(ltedpeg_funtype_6_htbl_t htbl, uint64_t i, uint32_t ihash);

extern ltedpeg_funtype_6_t dupdate_ltedpeg_funtype_6(ltedpeg_funtype_6_t a, uint64_t i, mpz_ptr_t v);

extern ltedpeg_funtype_6_t update_ltedpeg_funtype_6(ltedpeg_funtype_6_t a, uint64_t i, mpz_ptr_t v);

extern bool_t equal_ltedpeg_funtype_6(ltedpeg_funtype_6_t x, ltedpeg_funtype_6_t y);

extern char* json_ltedpeg_funtype_6(ltedpeg_funtype_6_t x);


//reduce_nat

struct ltedpeg_record_7_s {
        uint32_t count; 
        uint64_t project_1;
        uint32_t project_2;};
typedef struct ltedpeg_record_7_s * ltedpeg_record_7_t;

extern ltedpeg_record_7_t new_ltedpeg_record_7(void);

extern void release_ltedpeg_record_7(ltedpeg_record_7_t x);

extern ltedpeg_record_7_t copy_ltedpeg_record_7(ltedpeg_record_7_t x);

extern bool_t equal_ltedpeg_record_7(ltedpeg_record_7_t x, ltedpeg_record_7_t y);
extern char * json_ltedpeg_record_7(ltedpeg_record_7_t x);

typedef struct actual_ltedpeg_record_7_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_7_t;
extern void release_ltedpeg_record_7_ptr(pointer_t x, type_actual_t ltedpeg_record_7);

extern bool_t equal_ltedpeg_record_7_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_7_t T);

extern char * json_ltedpeg_record_7_ptr(pointer_t x,  actual_ltedpeg_record_7_t T);

actual_ltedpeg_record_7_t actual_ltedpeg_record_7(void);

 

extern ltedpeg_record_7_t update_ltedpeg_record_7_project_1(ltedpeg_record_7_t x, uint64_t v);

extern ltedpeg_record_7_t update_ltedpeg_record_7_project_2(ltedpeg_record_7_t x, uint32_t v);


//reduce_nat

struct ltedpeg_funtype_8_s;
        typedef struct ltedpeg_funtype_8_s * ltedpeg_funtype_8_t;

struct ltedpeg_funtype_8_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_8_s *, ltedpeg_record_7_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_8_s *, uint64_t, uint32_t);
        void (* rptr)(struct ltedpeg_funtype_8_s *);
        struct ltedpeg_funtype_8_s * (* cptr)(struct ltedpeg_funtype_8_s *);};
typedef struct ltedpeg_funtype_8_ftbl_s * ltedpeg_funtype_8_ftbl_t;

struct ltedpeg_funtype_8_hashentry_s {uint32_t keyhash; ltedpeg_record_7_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_8_hashentry_s ltedpeg_funtype_8_hashentry_t;

struct ltedpeg_funtype_8_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_8_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_8_htbl_s * ltedpeg_funtype_8_htbl_t;

struct ltedpeg_funtype_8_s {uint32_t count;
        ltedpeg_funtype_8_ftbl_t ftbl;
        ltedpeg_funtype_8_htbl_t htbl;};

extern void release_ltedpeg_funtype_8(ltedpeg_funtype_8_t x);

extern ltedpeg_funtype_8_t copy_ltedpeg_funtype_8(ltedpeg_funtype_8_t x);

extern bool_t equal_ltedpeg_funtype_8(ltedpeg_funtype_8_t x, ltedpeg_funtype_8_t y);

extern char* json_ltedpeg_funtype_8(ltedpeg_funtype_8_t x);


//reduce_nat

struct ltedpeg_record_9_s {
        uint32_t count; 
        uint32_t project_1;
        uint8_t project_2;};
typedef struct ltedpeg_record_9_s * ltedpeg_record_9_t;

extern ltedpeg_record_9_t new_ltedpeg_record_9(void);

extern void release_ltedpeg_record_9(ltedpeg_record_9_t x);

extern ltedpeg_record_9_t copy_ltedpeg_record_9(ltedpeg_record_9_t x);

extern bool_t equal_ltedpeg_record_9(ltedpeg_record_9_t x, ltedpeg_record_9_t y);
extern char * json_ltedpeg_record_9(ltedpeg_record_9_t x);

typedef struct actual_ltedpeg_record_9_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_9_t;
extern void release_ltedpeg_record_9_ptr(pointer_t x, type_actual_t ltedpeg_record_9);

extern bool_t equal_ltedpeg_record_9_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_9_t T);

extern char * json_ltedpeg_record_9_ptr(pointer_t x,  actual_ltedpeg_record_9_t T);

actual_ltedpeg_record_9_t actual_ltedpeg_record_9(void);

 

extern ltedpeg_record_9_t update_ltedpeg_record_9_project_1(ltedpeg_record_9_t x, uint32_t v);

extern ltedpeg_record_9_t update_ltedpeg_record_9_project_2(ltedpeg_record_9_t x, uint8_t v);


//reduce_nat

struct ltedpeg_funtype_10_s;
        typedef struct ltedpeg_funtype_10_s * ltedpeg_funtype_10_t;

struct ltedpeg_funtype_10_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_10_s *, ltedpeg_record_9_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_10_s *, uint32_t, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_10_s *);
        struct ltedpeg_funtype_10_s * (* cptr)(struct ltedpeg_funtype_10_s *);};
typedef struct ltedpeg_funtype_10_ftbl_s * ltedpeg_funtype_10_ftbl_t;

struct ltedpeg_funtype_10_hashentry_s {uint32_t keyhash; ltedpeg_record_9_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_10_hashentry_s ltedpeg_funtype_10_hashentry_t;

struct ltedpeg_funtype_10_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_10_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_10_htbl_s * ltedpeg_funtype_10_htbl_t;

struct ltedpeg_funtype_10_s {uint32_t count;
        ltedpeg_funtype_10_ftbl_t ftbl;
        ltedpeg_funtype_10_htbl_t htbl;};

extern void release_ltedpeg_funtype_10(ltedpeg_funtype_10_t x);

extern ltedpeg_funtype_10_t copy_ltedpeg_funtype_10(ltedpeg_funtype_10_t x);

extern bool_t equal_ltedpeg_funtype_10(ltedpeg_funtype_10_t x, ltedpeg_funtype_10_t y);

extern char* json_ltedpeg_funtype_10(ltedpeg_funtype_10_t x);




struct ltedpeg_closure_11_s;
        typedef struct ltedpeg_closure_11_s * ltedpeg_closure_11_t;

struct ltedpeg_closure_11_s {uint32_t count;
         ltedpeg_funtype_5_ftbl_t ftbl;
         ltedpeg_funtype_5_htbl_t htbl;
        ltedpeg_funtype_6_t fvar_1;
        mpz_t fvar_2;
        ltedpeg_funtype_8_t fvar_3;
        ltedpeg_funtype_10_t fvar_4;
        mpz_t fvar_5;};

mpz_ptr_t f_ltedpeg_closure_11(struct ltedpeg_closure_11_s * closure, ltedpeg__ent_adt_t bvar);

mpz_ptr_t m_ltedpeg_closure_11(struct ltedpeg_closure_11_s * closure, ltedpeg__ent_adt_t bvar);

extern mpz_ptr_t h_ltedpeg_closure_11(ltedpeg__ent_adt_t ivar_11, ltedpeg_funtype_6_t ivar_1, mpz_ptr_t ivar_4, ltedpeg_funtype_8_t ivar_5, ltedpeg_funtype_10_t ivar_7, mpz_ptr_t ivar_3);

ltedpeg_closure_11_t new_ltedpeg_closure_11(void);

void release_ltedpeg_closure_11(ltedpeg_funtype_5_t closure);

ltedpeg_closure_11_t copy_ltedpeg_closure_11(ltedpeg_closure_11_t x);


//REDUCE_nat

struct ltedpeg_record_12_s {
        uint32_t count; 
        uint64_t project_1;
        ltedpeg__ent_adt_t project_2;};
typedef struct ltedpeg_record_12_s * ltedpeg_record_12_t;

extern ltedpeg_record_12_t new_ltedpeg_record_12(void);

extern void release_ltedpeg_record_12(ltedpeg_record_12_t x);

extern ltedpeg_record_12_t copy_ltedpeg_record_12(ltedpeg_record_12_t x);

extern bool_t equal_ltedpeg_record_12(ltedpeg_record_12_t x, ltedpeg_record_12_t y);
extern char * json_ltedpeg_record_12(ltedpeg_record_12_t x);

typedef struct actual_ltedpeg_record_12_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_12_t;
extern void release_ltedpeg_record_12_ptr(pointer_t x, type_actual_t ltedpeg_record_12);

extern bool_t equal_ltedpeg_record_12_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_12_t T);

extern char * json_ltedpeg_record_12_ptr(pointer_t x,  actual_ltedpeg_record_12_t T);

actual_ltedpeg_record_12_t actual_ltedpeg_record_12(void);

 

extern ltedpeg_record_12_t update_ltedpeg_record_12_project_1(ltedpeg_record_12_t x, uint64_t v);

extern ltedpeg_record_12_t update_ltedpeg_record_12_project_2(ltedpeg_record_12_t x, ltedpeg__ent_adt_t v);


//REDUCE_nat

struct ltedpeg_funtype_13_s;
        typedef struct ltedpeg_funtype_13_s * ltedpeg_funtype_13_t;

struct ltedpeg_funtype_13_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_13_s *, ltedpeg_record_12_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_13_s *, uint64_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_13_s *);
        struct ltedpeg_funtype_13_s * (* cptr)(struct ltedpeg_funtype_13_s *);};
typedef struct ltedpeg_funtype_13_ftbl_s * ltedpeg_funtype_13_ftbl_t;

struct ltedpeg_funtype_13_hashentry_s {uint32_t keyhash; ltedpeg_record_12_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_13_hashentry_s ltedpeg_funtype_13_hashentry_t;

struct ltedpeg_funtype_13_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_13_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_13_htbl_s * ltedpeg_funtype_13_htbl_t;

struct ltedpeg_funtype_13_s {uint32_t count;
        ltedpeg_funtype_13_ftbl_t ftbl;
        ltedpeg_funtype_13_htbl_t htbl;};

extern void release_ltedpeg_funtype_13(ltedpeg_funtype_13_t x);

extern ltedpeg_funtype_13_t copy_ltedpeg_funtype_13(ltedpeg_funtype_13_t x);

extern bool_t equal_ltedpeg_funtype_13(ltedpeg_funtype_13_t x, ltedpeg_funtype_13_t y);

extern char* json_ltedpeg_funtype_13(ltedpeg_funtype_13_t x);


//REDUCE_nat

struct ltedpeg_record_14_s {
        uint32_t count; 
        uint64_t project_1;
        uint32_t project_2;
        ltedpeg__ent_adt_t project_3;};
typedef struct ltedpeg_record_14_s * ltedpeg_record_14_t;

extern ltedpeg_record_14_t new_ltedpeg_record_14(void);

extern void release_ltedpeg_record_14(ltedpeg_record_14_t x);

extern ltedpeg_record_14_t copy_ltedpeg_record_14(ltedpeg_record_14_t x);

extern bool_t equal_ltedpeg_record_14(ltedpeg_record_14_t x, ltedpeg_record_14_t y);
extern char * json_ltedpeg_record_14(ltedpeg_record_14_t x);

typedef struct actual_ltedpeg_record_14_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_14_t;
extern void release_ltedpeg_record_14_ptr(pointer_t x, type_actual_t ltedpeg_record_14);

extern bool_t equal_ltedpeg_record_14_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_14_t T);

extern char * json_ltedpeg_record_14_ptr(pointer_t x,  actual_ltedpeg_record_14_t T);

actual_ltedpeg_record_14_t actual_ltedpeg_record_14(void);

 

extern ltedpeg_record_14_t update_ltedpeg_record_14_project_1(ltedpeg_record_14_t x, uint64_t v);

extern ltedpeg_record_14_t update_ltedpeg_record_14_project_2(ltedpeg_record_14_t x, uint32_t v);

extern ltedpeg_record_14_t update_ltedpeg_record_14_project_3(ltedpeg_record_14_t x, ltedpeg__ent_adt_t v);


//REDUCE_nat

struct ltedpeg_funtype_15_s;
        typedef struct ltedpeg_funtype_15_s * ltedpeg_funtype_15_t;

struct ltedpeg_funtype_15_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_15_s *, ltedpeg_record_14_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_15_s *, uint64_t, uint32_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_15_s *);
        struct ltedpeg_funtype_15_s * (* cptr)(struct ltedpeg_funtype_15_s *);};
typedef struct ltedpeg_funtype_15_ftbl_s * ltedpeg_funtype_15_ftbl_t;

struct ltedpeg_funtype_15_hashentry_s {uint32_t keyhash; ltedpeg_record_14_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_15_hashentry_s ltedpeg_funtype_15_hashentry_t;

struct ltedpeg_funtype_15_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_15_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_15_htbl_s * ltedpeg_funtype_15_htbl_t;

struct ltedpeg_funtype_15_s {uint32_t count;
        ltedpeg_funtype_15_ftbl_t ftbl;
        ltedpeg_funtype_15_htbl_t htbl;};

extern void release_ltedpeg_funtype_15(ltedpeg_funtype_15_t x);

extern ltedpeg_funtype_15_t copy_ltedpeg_funtype_15(ltedpeg_funtype_15_t x);

extern bool_t equal_ltedpeg_funtype_15(ltedpeg_funtype_15_t x, ltedpeg_funtype_15_t y);

extern char* json_ltedpeg_funtype_15(ltedpeg_funtype_15_t x);


//REDUCE_nat

struct ltedpeg_record_16_s {
        uint32_t count; 
        uint32_t project_1;
        uint8_t project_2;
        ltedpeg__ent_adt_t project_3;};
typedef struct ltedpeg_record_16_s * ltedpeg_record_16_t;

extern ltedpeg_record_16_t new_ltedpeg_record_16(void);

extern void release_ltedpeg_record_16(ltedpeg_record_16_t x);

extern ltedpeg_record_16_t copy_ltedpeg_record_16(ltedpeg_record_16_t x);

extern bool_t equal_ltedpeg_record_16(ltedpeg_record_16_t x, ltedpeg_record_16_t y);
extern char * json_ltedpeg_record_16(ltedpeg_record_16_t x);

typedef struct actual_ltedpeg_record_16_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_16_t;
extern void release_ltedpeg_record_16_ptr(pointer_t x, type_actual_t ltedpeg_record_16);

extern bool_t equal_ltedpeg_record_16_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_16_t T);

extern char * json_ltedpeg_record_16_ptr(pointer_t x,  actual_ltedpeg_record_16_t T);

actual_ltedpeg_record_16_t actual_ltedpeg_record_16(void);

 

extern ltedpeg_record_16_t update_ltedpeg_record_16_project_1(ltedpeg_record_16_t x, uint32_t v);

extern ltedpeg_record_16_t update_ltedpeg_record_16_project_2(ltedpeg_record_16_t x, uint8_t v);

extern ltedpeg_record_16_t update_ltedpeg_record_16_project_3(ltedpeg_record_16_t x, ltedpeg__ent_adt_t v);


//REDUCE_nat

struct ltedpeg_funtype_17_s;
        typedef struct ltedpeg_funtype_17_s * ltedpeg_funtype_17_t;

struct ltedpeg_funtype_17_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_17_s *, ltedpeg_record_16_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_17_s *, uint32_t, uint8_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_17_s *);
        struct ltedpeg_funtype_17_s * (* cptr)(struct ltedpeg_funtype_17_s *);};
typedef struct ltedpeg_funtype_17_ftbl_s * ltedpeg_funtype_17_ftbl_t;

struct ltedpeg_funtype_17_hashentry_s {uint32_t keyhash; ltedpeg_record_16_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_17_hashentry_s ltedpeg_funtype_17_hashentry_t;

struct ltedpeg_funtype_17_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_17_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_17_htbl_s * ltedpeg_funtype_17_htbl_t;

struct ltedpeg_funtype_17_s {uint32_t count;
        ltedpeg_funtype_17_ftbl_t ftbl;
        ltedpeg_funtype_17_htbl_t htbl;};

extern void release_ltedpeg_funtype_17(ltedpeg_funtype_17_t x);

extern ltedpeg_funtype_17_t copy_ltedpeg_funtype_17(ltedpeg_funtype_17_t x);

extern bool_t equal_ltedpeg_funtype_17(ltedpeg_funtype_17_t x, ltedpeg_funtype_17_t y);

extern char* json_ltedpeg_funtype_17(ltedpeg_funtype_17_t x);




struct ltedpeg_closure_18_s;
        typedef struct ltedpeg_closure_18_s * ltedpeg_closure_18_t;

struct ltedpeg_closure_18_s {uint32_t count;
         ltedpeg_funtype_5_ftbl_t ftbl;
         ltedpeg_funtype_5_htbl_t htbl;
        ltedpeg_funtype_13_t fvar_1;
        ltedpeg_funtype_5_t fvar_2;
        ltedpeg_funtype_15_t fvar_3;
        ltedpeg_funtype_17_t fvar_4;
        ltedpeg_funtype_5_t fvar_5;};

mpz_ptr_t f_ltedpeg_closure_18(struct ltedpeg_closure_18_s * closure, ltedpeg__ent_adt_t bvar);

mpz_ptr_t m_ltedpeg_closure_18(struct ltedpeg_closure_18_s * closure, ltedpeg__ent_adt_t bvar);

extern mpz_ptr_t h_ltedpeg_closure_18(ltedpeg__ent_adt_t ivar_13, ltedpeg_funtype_13_t ivar_1, ltedpeg_funtype_5_t ivar_5, ltedpeg_funtype_15_t ivar_7, ltedpeg_funtype_17_t ivar_9, ltedpeg_funtype_5_t ivar_3);

ltedpeg_closure_18_t new_ltedpeg_closure_18(void);

void release_ltedpeg_closure_18(ltedpeg_funtype_5_t closure);

ltedpeg_closure_18_t copy_ltedpeg_closure_18(ltedpeg_closure_18_t x);


//reduce_ordinal

struct ltedpeg_funtype_19_s;
        typedef struct ltedpeg_funtype_19_s * ltedpeg_funtype_19_t;

struct ltedpeg_funtype_19_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_19_s *, ltedpeg__ent_adt_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_19_s *, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_19_s *);
        struct ltedpeg_funtype_19_s * (* cptr)(struct ltedpeg_funtype_19_s *);};
typedef struct ltedpeg_funtype_19_ftbl_s * ltedpeg_funtype_19_ftbl_t;

struct ltedpeg_funtype_19_hashentry_s {uint32_t keyhash; ltedpeg__ent_adt_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_19_hashentry_s ltedpeg_funtype_19_hashentry_t;

struct ltedpeg_funtype_19_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_19_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_19_htbl_s * ltedpeg_funtype_19_htbl_t;

struct ltedpeg_funtype_19_s {uint32_t count;
        ltedpeg_funtype_19_ftbl_t ftbl;
        ltedpeg_funtype_19_htbl_t htbl;};

extern void release_ltedpeg_funtype_19(ltedpeg_funtype_19_t x);

extern ltedpeg_funtype_19_t copy_ltedpeg_funtype_19(ltedpeg_funtype_19_t x);

extern bool_t equal_ltedpeg_funtype_19(ltedpeg_funtype_19_t x, ltedpeg_funtype_19_t y);

extern char* json_ltedpeg_funtype_19(ltedpeg_funtype_19_t x);


//reduce_ordinal

struct ltedpeg_funtype_20_s;
        typedef struct ltedpeg_funtype_20_s * ltedpeg_funtype_20_t;

struct ltedpeg_funtype_20_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_20_s *, uint64_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_20_s *, uint64_t);
        void (* rptr)(struct ltedpeg_funtype_20_s *);
        struct ltedpeg_funtype_20_s * (* cptr)(struct ltedpeg_funtype_20_s *);};
typedef struct ltedpeg_funtype_20_ftbl_s * ltedpeg_funtype_20_ftbl_t;

struct ltedpeg_funtype_20_hashentry_s {uint32_t keyhash; uint64_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_20_hashentry_s ltedpeg_funtype_20_hashentry_t;

struct ltedpeg_funtype_20_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_20_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_20_htbl_s * ltedpeg_funtype_20_htbl_t;

struct ltedpeg_funtype_20_s {uint32_t count;
        ltedpeg_funtype_20_ftbl_t ftbl;
        ltedpeg_funtype_20_htbl_t htbl;};

extern void release_ltedpeg_funtype_20(ltedpeg_funtype_20_t x);

extern ltedpeg_funtype_20_t copy_ltedpeg_funtype_20(ltedpeg_funtype_20_t x);

extern uint32_t lookup_ltedpeg_funtype_20(ltedpeg_funtype_20_htbl_t htbl, uint64_t i, uint32_t ihash);

extern ltedpeg_funtype_20_t dupdate_ltedpeg_funtype_20(ltedpeg_funtype_20_t a, uint64_t i, ordstruct_adt__ordstruct_adt_t v);

extern ltedpeg_funtype_20_t update_ltedpeg_funtype_20(ltedpeg_funtype_20_t a, uint64_t i, ordstruct_adt__ordstruct_adt_t v);

extern bool_t equal_ltedpeg_funtype_20(ltedpeg_funtype_20_t x, ltedpeg_funtype_20_t y);

extern char* json_ltedpeg_funtype_20(ltedpeg_funtype_20_t x);


//reduce_ordinal

struct ltedpeg_funtype_21_s;
        typedef struct ltedpeg_funtype_21_s * ltedpeg_funtype_21_t;

struct ltedpeg_funtype_21_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_21_s *, ltedpeg_record_7_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_21_s *, uint64_t, uint32_t);
        void (* rptr)(struct ltedpeg_funtype_21_s *);
        struct ltedpeg_funtype_21_s * (* cptr)(struct ltedpeg_funtype_21_s *);};
typedef struct ltedpeg_funtype_21_ftbl_s * ltedpeg_funtype_21_ftbl_t;

struct ltedpeg_funtype_21_hashentry_s {uint32_t keyhash; ltedpeg_record_7_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_21_hashentry_s ltedpeg_funtype_21_hashentry_t;

struct ltedpeg_funtype_21_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_21_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_21_htbl_s * ltedpeg_funtype_21_htbl_t;

struct ltedpeg_funtype_21_s {uint32_t count;
        ltedpeg_funtype_21_ftbl_t ftbl;
        ltedpeg_funtype_21_htbl_t htbl;};

extern void release_ltedpeg_funtype_21(ltedpeg_funtype_21_t x);

extern ltedpeg_funtype_21_t copy_ltedpeg_funtype_21(ltedpeg_funtype_21_t x);

extern bool_t equal_ltedpeg_funtype_21(ltedpeg_funtype_21_t x, ltedpeg_funtype_21_t y);

extern char* json_ltedpeg_funtype_21(ltedpeg_funtype_21_t x);


//reduce_ordinal

struct ltedpeg_funtype_22_s;
        typedef struct ltedpeg_funtype_22_s * ltedpeg_funtype_22_t;

struct ltedpeg_funtype_22_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_22_s *, ltedpeg_record_9_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_22_s *, uint32_t, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_22_s *);
        struct ltedpeg_funtype_22_s * (* cptr)(struct ltedpeg_funtype_22_s *);};
typedef struct ltedpeg_funtype_22_ftbl_s * ltedpeg_funtype_22_ftbl_t;

struct ltedpeg_funtype_22_hashentry_s {uint32_t keyhash; ltedpeg_record_9_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_22_hashentry_s ltedpeg_funtype_22_hashentry_t;

struct ltedpeg_funtype_22_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_22_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_22_htbl_s * ltedpeg_funtype_22_htbl_t;

struct ltedpeg_funtype_22_s {uint32_t count;
        ltedpeg_funtype_22_ftbl_t ftbl;
        ltedpeg_funtype_22_htbl_t htbl;};

extern void release_ltedpeg_funtype_22(ltedpeg_funtype_22_t x);

extern ltedpeg_funtype_22_t copy_ltedpeg_funtype_22(ltedpeg_funtype_22_t x);

extern bool_t equal_ltedpeg_funtype_22(ltedpeg_funtype_22_t x, ltedpeg_funtype_22_t y);

extern char* json_ltedpeg_funtype_22(ltedpeg_funtype_22_t x);




struct ltedpeg_closure_23_s;
        typedef struct ltedpeg_closure_23_s * ltedpeg_closure_23_t;

struct ltedpeg_closure_23_s {uint32_t count;
         ltedpeg_funtype_19_ftbl_t ftbl;
         ltedpeg_funtype_19_htbl_t htbl;
        ltedpeg_funtype_20_t fvar_1;
        ordstruct_adt__ordstruct_adt_t fvar_2;
        ltedpeg_funtype_21_t fvar_3;
        ltedpeg_funtype_22_t fvar_4;
        ordstruct_adt__ordstruct_adt_t fvar_5;};

ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_23(struct ltedpeg_closure_23_s * closure, ltedpeg__ent_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_23(struct ltedpeg_closure_23_s * closure, ltedpeg__ent_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_23(ltedpeg__ent_adt_t ivar_11, ltedpeg_funtype_20_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_4, ltedpeg_funtype_21_t ivar_5, ltedpeg_funtype_22_t ivar_7, ordstruct_adt__ordstruct_adt_t ivar_3);

ltedpeg_closure_23_t new_ltedpeg_closure_23(void);

void release_ltedpeg_closure_23(ltedpeg_funtype_19_t closure);

ltedpeg_closure_23_t copy_ltedpeg_closure_23(ltedpeg_closure_23_t x);


//REDUCE_ordinal

struct ltedpeg_funtype_24_s;
        typedef struct ltedpeg_funtype_24_s * ltedpeg_funtype_24_t;

struct ltedpeg_funtype_24_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_24_s *, ltedpeg_record_12_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_24_s *, uint64_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_24_s *);
        struct ltedpeg_funtype_24_s * (* cptr)(struct ltedpeg_funtype_24_s *);};
typedef struct ltedpeg_funtype_24_ftbl_s * ltedpeg_funtype_24_ftbl_t;

struct ltedpeg_funtype_24_hashentry_s {uint32_t keyhash; ltedpeg_record_12_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_24_hashentry_s ltedpeg_funtype_24_hashentry_t;

struct ltedpeg_funtype_24_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_24_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_24_htbl_s * ltedpeg_funtype_24_htbl_t;

struct ltedpeg_funtype_24_s {uint32_t count;
        ltedpeg_funtype_24_ftbl_t ftbl;
        ltedpeg_funtype_24_htbl_t htbl;};

extern void release_ltedpeg_funtype_24(ltedpeg_funtype_24_t x);

extern ltedpeg_funtype_24_t copy_ltedpeg_funtype_24(ltedpeg_funtype_24_t x);

extern bool_t equal_ltedpeg_funtype_24(ltedpeg_funtype_24_t x, ltedpeg_funtype_24_t y);

extern char* json_ltedpeg_funtype_24(ltedpeg_funtype_24_t x);


//REDUCE_ordinal

struct ltedpeg_funtype_25_s;
        typedef struct ltedpeg_funtype_25_s * ltedpeg_funtype_25_t;

struct ltedpeg_funtype_25_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_25_s *, ltedpeg_record_14_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_25_s *, uint64_t, uint32_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_25_s *);
        struct ltedpeg_funtype_25_s * (* cptr)(struct ltedpeg_funtype_25_s *);};
typedef struct ltedpeg_funtype_25_ftbl_s * ltedpeg_funtype_25_ftbl_t;

struct ltedpeg_funtype_25_hashentry_s {uint32_t keyhash; ltedpeg_record_14_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_25_hashentry_s ltedpeg_funtype_25_hashentry_t;

struct ltedpeg_funtype_25_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_25_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_25_htbl_s * ltedpeg_funtype_25_htbl_t;

struct ltedpeg_funtype_25_s {uint32_t count;
        ltedpeg_funtype_25_ftbl_t ftbl;
        ltedpeg_funtype_25_htbl_t htbl;};

extern void release_ltedpeg_funtype_25(ltedpeg_funtype_25_t x);

extern ltedpeg_funtype_25_t copy_ltedpeg_funtype_25(ltedpeg_funtype_25_t x);

extern bool_t equal_ltedpeg_funtype_25(ltedpeg_funtype_25_t x, ltedpeg_funtype_25_t y);

extern char* json_ltedpeg_funtype_25(ltedpeg_funtype_25_t x);


//REDUCE_ordinal

struct ltedpeg_funtype_26_s;
        typedef struct ltedpeg_funtype_26_s * ltedpeg_funtype_26_t;

struct ltedpeg_funtype_26_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_26_s *, ltedpeg_record_16_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_26_s *, uint32_t, uint8_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_26_s *);
        struct ltedpeg_funtype_26_s * (* cptr)(struct ltedpeg_funtype_26_s *);};
typedef struct ltedpeg_funtype_26_ftbl_s * ltedpeg_funtype_26_ftbl_t;

struct ltedpeg_funtype_26_hashentry_s {uint32_t keyhash; ltedpeg_record_16_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_26_hashentry_s ltedpeg_funtype_26_hashentry_t;

struct ltedpeg_funtype_26_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_26_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_26_htbl_s * ltedpeg_funtype_26_htbl_t;

struct ltedpeg_funtype_26_s {uint32_t count;
        ltedpeg_funtype_26_ftbl_t ftbl;
        ltedpeg_funtype_26_htbl_t htbl;};

extern void release_ltedpeg_funtype_26(ltedpeg_funtype_26_t x);

extern ltedpeg_funtype_26_t copy_ltedpeg_funtype_26(ltedpeg_funtype_26_t x);

extern bool_t equal_ltedpeg_funtype_26(ltedpeg_funtype_26_t x, ltedpeg_funtype_26_t y);

extern char* json_ltedpeg_funtype_26(ltedpeg_funtype_26_t x);




struct ltedpeg_closure_27_s;
        typedef struct ltedpeg_closure_27_s * ltedpeg_closure_27_t;

struct ltedpeg_closure_27_s {uint32_t count;
         ltedpeg_funtype_19_ftbl_t ftbl;
         ltedpeg_funtype_19_htbl_t htbl;
        ltedpeg_funtype_24_t fvar_1;
        ltedpeg_funtype_19_t fvar_2;
        ltedpeg_funtype_25_t fvar_3;
        ltedpeg_funtype_26_t fvar_4;
        ltedpeg_funtype_19_t fvar_5;};

ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_27(struct ltedpeg_closure_27_s * closure, ltedpeg__ent_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_27(struct ltedpeg_closure_27_s * closure, ltedpeg__ent_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_27(ltedpeg__ent_adt_t ivar_13, ltedpeg_funtype_24_t ivar_1, ltedpeg_funtype_19_t ivar_5, ltedpeg_funtype_25_t ivar_7, ltedpeg_funtype_26_t ivar_9, ltedpeg_funtype_19_t ivar_3);

ltedpeg_closure_27_t new_ltedpeg_closure_27(void);

void release_ltedpeg_closure_27(ltedpeg_funtype_19_t closure);

ltedpeg_closure_27_t copy_ltedpeg_closure_27(ltedpeg_closure_27_t x);


//prepeg

struct ltedpeg__prepeg_adt_s {
         uint32_t count; 
        uint8_t ltedpeg__prepeg_adt_index;};
typedef struct ltedpeg__prepeg_adt_s * ltedpeg__prepeg_adt_t;

extern ltedpeg__prepeg_adt_t new_ltedpeg__prepeg_adt(void);

extern void release_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x);

extern ltedpeg__prepeg_adt_t copy_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x);

extern bool_t equal_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x, ltedpeg__prepeg_adt_t y);
extern char * json_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x);

typedef struct actual_ltedpeg__prepeg_adt_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__prepeg_adt_t;
extern void release_ltedpeg__prepeg_adt_ptr(pointer_t x, type_actual_t ltedpeg__prepeg_adt);

extern bool_t equal_ltedpeg__prepeg_adt_ptr(pointer_t x, pointer_t y, actual_ltedpeg__prepeg_adt_t T);

extern char * json_ltedpeg__prepeg_adt_ptr(pointer_t x,  actual_ltedpeg__prepeg_adt_t T);

actual_ltedpeg__prepeg_adt_t actual_ltedpeg__prepeg_adt(void);

 

extern ltedpeg__prepeg_adt_t update_ltedpeg__prepeg_adt_ltedpeg__prepeg_adt_index(ltedpeg__prepeg_adt_t x, uint8_t v);


//any

struct ltedpeg__any_s {
        uint32_t count; 
        uint8_t ltedpeg__prepeg_adt_index;
        dpeg__dpeg_grammar_t dpg;};
typedef struct ltedpeg__any_s * ltedpeg__any_t;

extern ltedpeg__any_t new_ltedpeg__any(void);

extern void release_ltedpeg__any(ltedpeg__any_t x);

extern ltedpeg__any_t copy_ltedpeg__any(ltedpeg__any_t x);

extern bool_t equal_ltedpeg__any(ltedpeg__any_t x, ltedpeg__any_t y);
extern char * json_ltedpeg__any(ltedpeg__any_t x);

typedef struct actual_ltedpeg__any_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__any_t;
extern void release_ltedpeg__any_ptr(pointer_t x, type_actual_t ltedpeg__any);

extern bool_t equal_ltedpeg__any_ptr(pointer_t x, pointer_t y, actual_ltedpeg__any_t T);

extern char * json_ltedpeg__any_ptr(pointer_t x,  actual_ltedpeg__any_t T);

actual_ltedpeg__any_t actual_ltedpeg__any(void);

 

extern ltedpeg__any_t update_ltedpeg__any_ltedpeg__prepeg_adt_index(ltedpeg__any_t x, uint8_t v);

extern ltedpeg__any_t update_ltedpeg__any_dpg(ltedpeg__any_t x, dpeg__dpeg_grammar_t v);


//terminal

struct ltedpeg__terminal_s {
        uint32_t count; 
        uint8_t ltedpeg__prepeg_adt_index;
        uint8_t a;};
typedef struct ltedpeg__terminal_s * ltedpeg__terminal_t;

extern ltedpeg__terminal_t new_ltedpeg__terminal(void);

extern void release_ltedpeg__terminal(ltedpeg__terminal_t x);

extern ltedpeg__terminal_t copy_ltedpeg__terminal(ltedpeg__terminal_t x);

extern bool_t equal_ltedpeg__terminal(ltedpeg__terminal_t x, ltedpeg__terminal_t y);
extern char * json_ltedpeg__terminal(ltedpeg__terminal_t x);

typedef struct actual_ltedpeg__terminal_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__terminal_t;
extern void release_ltedpeg__terminal_ptr(pointer_t x, type_actual_t ltedpeg__terminal);

extern bool_t equal_ltedpeg__terminal_ptr(pointer_t x, pointer_t y, actual_ltedpeg__terminal_t T);

extern char * json_ltedpeg__terminal_ptr(pointer_t x,  actual_ltedpeg__terminal_t T);

actual_ltedpeg__terminal_t actual_ltedpeg__terminal(void);

 

extern ltedpeg__terminal_t update_ltedpeg__terminal_ltedpeg__prepeg_adt_index(ltedpeg__terminal_t x, uint8_t v);

extern ltedpeg__terminal_t update_ltedpeg__terminal_a(ltedpeg__terminal_t x, uint8_t v);


//lte

struct ltedpeg__lte_s {
        uint32_t count; 
        uint8_t ltedpeg__prepeg_adt_index;
        uint8_t fst;
        uint8_t lthen;
        uint8_t lelse;};
typedef struct ltedpeg__lte_s * ltedpeg__lte_t;

extern ltedpeg__lte_t new_ltedpeg__lte(void);

extern void release_ltedpeg__lte(ltedpeg__lte_t x);

extern ltedpeg__lte_t copy_ltedpeg__lte(ltedpeg__lte_t x);

extern bool_t equal_ltedpeg__lte(ltedpeg__lte_t x, ltedpeg__lte_t y);
extern char * json_ltedpeg__lte(ltedpeg__lte_t x);

typedef struct actual_ltedpeg__lte_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__lte_t;
extern void release_ltedpeg__lte_ptr(pointer_t x, type_actual_t ltedpeg__lte);

extern bool_t equal_ltedpeg__lte_ptr(pointer_t x, pointer_t y, actual_ltedpeg__lte_t T);

extern char * json_ltedpeg__lte_ptr(pointer_t x,  actual_ltedpeg__lte_t T);

actual_ltedpeg__lte_t actual_ltedpeg__lte(void);

 

extern ltedpeg__lte_t update_ltedpeg__lte_ltedpeg__prepeg_adt_index(ltedpeg__lte_t x, uint8_t v);

extern ltedpeg__lte_t update_ltedpeg__lte_fst(ltedpeg__lte_t x, uint8_t v);

extern ltedpeg__lte_t update_ltedpeg__lte_lthen(ltedpeg__lte_t x, uint8_t v);

extern ltedpeg__lte_t update_ltedpeg__lte_lelse(ltedpeg__lte_t x, uint8_t v);


//reduce_nat

struct ltedpeg_funtype_32_s;
        typedef struct ltedpeg_funtype_32_s * ltedpeg_funtype_32_t;

struct ltedpeg_funtype_32_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_32_s *, ltedpeg__prepeg_adt_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_32_s *, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_32_s *);
        struct ltedpeg_funtype_32_s * (* cptr)(struct ltedpeg_funtype_32_s *);};
typedef struct ltedpeg_funtype_32_ftbl_s * ltedpeg_funtype_32_ftbl_t;

struct ltedpeg_funtype_32_hashentry_s {uint32_t keyhash; ltedpeg__prepeg_adt_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_32_hashentry_s ltedpeg_funtype_32_hashentry_t;

struct ltedpeg_funtype_32_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_32_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_32_htbl_s * ltedpeg_funtype_32_htbl_t;

struct ltedpeg_funtype_32_s {uint32_t count;
        ltedpeg_funtype_32_ftbl_t ftbl;
        ltedpeg_funtype_32_htbl_t htbl;};

extern void release_ltedpeg_funtype_32(ltedpeg_funtype_32_t x);

extern ltedpeg_funtype_32_t copy_ltedpeg_funtype_32(ltedpeg_funtype_32_t x);

extern bool_t equal_ltedpeg_funtype_32(ltedpeg_funtype_32_t x, ltedpeg_funtype_32_t y);

extern char* json_ltedpeg_funtype_32(ltedpeg_funtype_32_t x);


//reduce_nat

struct ltedpeg_funtype_33_s;
        typedef struct ltedpeg_funtype_33_s * ltedpeg_funtype_33_t;

struct ltedpeg_funtype_33_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_33_s *, dpeg__dpeg_grammar_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_33_s *, dpeg__dpeg_grammar_t);
        void (* rptr)(struct ltedpeg_funtype_33_s *);
        struct ltedpeg_funtype_33_s * (* cptr)(struct ltedpeg_funtype_33_s *);};
typedef struct ltedpeg_funtype_33_ftbl_s * ltedpeg_funtype_33_ftbl_t;

struct ltedpeg_funtype_33_hashentry_s {uint32_t keyhash; dpeg__dpeg_grammar_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_33_hashentry_s ltedpeg_funtype_33_hashentry_t;

struct ltedpeg_funtype_33_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_33_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_33_htbl_s * ltedpeg_funtype_33_htbl_t;

struct ltedpeg_funtype_33_s {uint32_t count;
        ltedpeg_funtype_33_ftbl_t ftbl;
        ltedpeg_funtype_33_htbl_t htbl;};

extern void release_ltedpeg_funtype_33(ltedpeg_funtype_33_t x);

extern ltedpeg_funtype_33_t copy_ltedpeg_funtype_33(ltedpeg_funtype_33_t x);

extern bool_t equal_ltedpeg_funtype_33(ltedpeg_funtype_33_t x, ltedpeg_funtype_33_t y);

extern char* json_ltedpeg_funtype_33(ltedpeg_funtype_33_t x);


//reduce_nat

struct ltedpeg_funtype_34_s;
        typedef struct ltedpeg_funtype_34_s * ltedpeg_funtype_34_t;

struct ltedpeg_funtype_34_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_34_s *, uint8_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_34_s *, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_34_s *);
        struct ltedpeg_funtype_34_s * (* cptr)(struct ltedpeg_funtype_34_s *);};
typedef struct ltedpeg_funtype_34_ftbl_s * ltedpeg_funtype_34_ftbl_t;

struct ltedpeg_funtype_34_hashentry_s {uint32_t keyhash; uint8_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_34_hashentry_s ltedpeg_funtype_34_hashentry_t;

struct ltedpeg_funtype_34_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_34_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_34_htbl_s * ltedpeg_funtype_34_htbl_t;

struct ltedpeg_funtype_34_s {uint32_t count;
        ltedpeg_funtype_34_ftbl_t ftbl;
        ltedpeg_funtype_34_htbl_t htbl;};

extern void release_ltedpeg_funtype_34(ltedpeg_funtype_34_t x);

extern ltedpeg_funtype_34_t copy_ltedpeg_funtype_34(ltedpeg_funtype_34_t x);

extern uint32_t lookup_ltedpeg_funtype_34(ltedpeg_funtype_34_htbl_t htbl, uint8_t i, uint32_t ihash);

extern ltedpeg_funtype_34_t dupdate_ltedpeg_funtype_34(ltedpeg_funtype_34_t a, uint8_t i, mpz_ptr_t v);

extern ltedpeg_funtype_34_t update_ltedpeg_funtype_34(ltedpeg_funtype_34_t a, uint8_t i, mpz_ptr_t v);

extern bool_t equal_ltedpeg_funtype_34(ltedpeg_funtype_34_t x, ltedpeg_funtype_34_t y);

extern char* json_ltedpeg_funtype_34(ltedpeg_funtype_34_t x);


//reduce_nat

struct ltedpeg_record_35_s {
        uint32_t count; 
        uint8_t project_1;
        uint8_t project_2;
        uint8_t project_3;};
typedef struct ltedpeg_record_35_s * ltedpeg_record_35_t;

extern ltedpeg_record_35_t new_ltedpeg_record_35(void);

extern void release_ltedpeg_record_35(ltedpeg_record_35_t x);

extern ltedpeg_record_35_t copy_ltedpeg_record_35(ltedpeg_record_35_t x);

extern bool_t equal_ltedpeg_record_35(ltedpeg_record_35_t x, ltedpeg_record_35_t y);
extern char * json_ltedpeg_record_35(ltedpeg_record_35_t x);

typedef struct actual_ltedpeg_record_35_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_35_t;
extern void release_ltedpeg_record_35_ptr(pointer_t x, type_actual_t ltedpeg_record_35);

extern bool_t equal_ltedpeg_record_35_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_35_t T);

extern char * json_ltedpeg_record_35_ptr(pointer_t x,  actual_ltedpeg_record_35_t T);

actual_ltedpeg_record_35_t actual_ltedpeg_record_35(void);

 

extern ltedpeg_record_35_t update_ltedpeg_record_35_project_1(ltedpeg_record_35_t x, uint8_t v);

extern ltedpeg_record_35_t update_ltedpeg_record_35_project_2(ltedpeg_record_35_t x, uint8_t v);

extern ltedpeg_record_35_t update_ltedpeg_record_35_project_3(ltedpeg_record_35_t x, uint8_t v);


//reduce_nat

struct ltedpeg_funtype_36_s;
        typedef struct ltedpeg_funtype_36_s * ltedpeg_funtype_36_t;

struct ltedpeg_funtype_36_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_36_s *, ltedpeg_record_35_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_36_s *, uint8_t, uint8_t, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_36_s *);
        struct ltedpeg_funtype_36_s * (* cptr)(struct ltedpeg_funtype_36_s *);};
typedef struct ltedpeg_funtype_36_ftbl_s * ltedpeg_funtype_36_ftbl_t;

struct ltedpeg_funtype_36_hashentry_s {uint32_t keyhash; ltedpeg_record_35_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_36_hashentry_s ltedpeg_funtype_36_hashentry_t;

struct ltedpeg_funtype_36_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_36_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_36_htbl_s * ltedpeg_funtype_36_htbl_t;

struct ltedpeg_funtype_36_s {uint32_t count;
        ltedpeg_funtype_36_ftbl_t ftbl;
        ltedpeg_funtype_36_htbl_t htbl;};

extern void release_ltedpeg_funtype_36(ltedpeg_funtype_36_t x);

extern ltedpeg_funtype_36_t copy_ltedpeg_funtype_36(ltedpeg_funtype_36_t x);

extern bool_t equal_ltedpeg_funtype_36(ltedpeg_funtype_36_t x, ltedpeg_funtype_36_t y);

extern char* json_ltedpeg_funtype_36(ltedpeg_funtype_36_t x);




struct ltedpeg_closure_37_s;
        typedef struct ltedpeg_closure_37_s * ltedpeg_closure_37_t;

struct ltedpeg_closure_37_s {uint32_t count;
         ltedpeg_funtype_32_ftbl_t ftbl;
         ltedpeg_funtype_32_htbl_t htbl;
        mpz_t fvar_1;
        ltedpeg_funtype_33_t fvar_2;
        ltedpeg_funtype_34_t fvar_3;
        ltedpeg_funtype_36_t fvar_4;
        mpz_t fvar_5;};

mpz_ptr_t f_ltedpeg_closure_37(struct ltedpeg_closure_37_s * closure, ltedpeg__prepeg_adt_t bvar);

mpz_ptr_t m_ltedpeg_closure_37(struct ltedpeg_closure_37_s * closure, ltedpeg__prepeg_adt_t bvar);

extern mpz_ptr_t h_ltedpeg_closure_37(ltedpeg__prepeg_adt_t ivar_11, mpz_ptr_t ivar_1, ltedpeg_funtype_33_t ivar_3, ltedpeg_funtype_34_t ivar_5, ltedpeg_funtype_36_t ivar_7, mpz_ptr_t ivar_2);

ltedpeg_closure_37_t new_ltedpeg_closure_37(void);

void release_ltedpeg_closure_37(ltedpeg_funtype_32_t closure);

ltedpeg_closure_37_t copy_ltedpeg_closure_37(ltedpeg_closure_37_t x);


//REDUCE_nat

struct ltedpeg_record_38_s {
        uint32_t count; 
        dpeg__dpeg_grammar_t project_1;
        ltedpeg__prepeg_adt_t project_2;};
typedef struct ltedpeg_record_38_s * ltedpeg_record_38_t;

extern ltedpeg_record_38_t new_ltedpeg_record_38(void);

extern void release_ltedpeg_record_38(ltedpeg_record_38_t x);

extern ltedpeg_record_38_t copy_ltedpeg_record_38(ltedpeg_record_38_t x);

extern bool_t equal_ltedpeg_record_38(ltedpeg_record_38_t x, ltedpeg_record_38_t y);
extern char * json_ltedpeg_record_38(ltedpeg_record_38_t x);

typedef struct actual_ltedpeg_record_38_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_38_t;
extern void release_ltedpeg_record_38_ptr(pointer_t x, type_actual_t ltedpeg_record_38);

extern bool_t equal_ltedpeg_record_38_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_38_t T);

extern char * json_ltedpeg_record_38_ptr(pointer_t x,  actual_ltedpeg_record_38_t T);

actual_ltedpeg_record_38_t actual_ltedpeg_record_38(void);

 

extern ltedpeg_record_38_t update_ltedpeg_record_38_project_1(ltedpeg_record_38_t x, dpeg__dpeg_grammar_t v);

extern ltedpeg_record_38_t update_ltedpeg_record_38_project_2(ltedpeg_record_38_t x, ltedpeg__prepeg_adt_t v);


//REDUCE_nat

struct ltedpeg_funtype_39_s;
        typedef struct ltedpeg_funtype_39_s * ltedpeg_funtype_39_t;

struct ltedpeg_funtype_39_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_39_s *, ltedpeg_record_38_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_39_s *, dpeg__dpeg_grammar_t, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_39_s *);
        struct ltedpeg_funtype_39_s * (* cptr)(struct ltedpeg_funtype_39_s *);};
typedef struct ltedpeg_funtype_39_ftbl_s * ltedpeg_funtype_39_ftbl_t;

struct ltedpeg_funtype_39_hashentry_s {uint32_t keyhash; ltedpeg_record_38_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_39_hashentry_s ltedpeg_funtype_39_hashentry_t;

struct ltedpeg_funtype_39_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_39_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_39_htbl_s * ltedpeg_funtype_39_htbl_t;

struct ltedpeg_funtype_39_s {uint32_t count;
        ltedpeg_funtype_39_ftbl_t ftbl;
        ltedpeg_funtype_39_htbl_t htbl;};

extern void release_ltedpeg_funtype_39(ltedpeg_funtype_39_t x);

extern ltedpeg_funtype_39_t copy_ltedpeg_funtype_39(ltedpeg_funtype_39_t x);

extern bool_t equal_ltedpeg_funtype_39(ltedpeg_funtype_39_t x, ltedpeg_funtype_39_t y);

extern char* json_ltedpeg_funtype_39(ltedpeg_funtype_39_t x);


//REDUCE_nat

struct ltedpeg_record_40_s {
        uint32_t count; 
        uint8_t project_1;
        ltedpeg__prepeg_adt_t project_2;};
typedef struct ltedpeg_record_40_s * ltedpeg_record_40_t;

extern ltedpeg_record_40_t new_ltedpeg_record_40(void);

extern void release_ltedpeg_record_40(ltedpeg_record_40_t x);

extern ltedpeg_record_40_t copy_ltedpeg_record_40(ltedpeg_record_40_t x);

extern bool_t equal_ltedpeg_record_40(ltedpeg_record_40_t x, ltedpeg_record_40_t y);
extern char * json_ltedpeg_record_40(ltedpeg_record_40_t x);

typedef struct actual_ltedpeg_record_40_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_40_t;
extern void release_ltedpeg_record_40_ptr(pointer_t x, type_actual_t ltedpeg_record_40);

extern bool_t equal_ltedpeg_record_40_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_40_t T);

extern char * json_ltedpeg_record_40_ptr(pointer_t x,  actual_ltedpeg_record_40_t T);

actual_ltedpeg_record_40_t actual_ltedpeg_record_40(void);

 

extern ltedpeg_record_40_t update_ltedpeg_record_40_project_1(ltedpeg_record_40_t x, uint8_t v);

extern ltedpeg_record_40_t update_ltedpeg_record_40_project_2(ltedpeg_record_40_t x, ltedpeg__prepeg_adt_t v);


//REDUCE_nat

struct ltedpeg_funtype_41_s;
        typedef struct ltedpeg_funtype_41_s * ltedpeg_funtype_41_t;

struct ltedpeg_funtype_41_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_41_s *, ltedpeg_record_40_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_41_s *, uint8_t, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_41_s *);
        struct ltedpeg_funtype_41_s * (* cptr)(struct ltedpeg_funtype_41_s *);};
typedef struct ltedpeg_funtype_41_ftbl_s * ltedpeg_funtype_41_ftbl_t;

struct ltedpeg_funtype_41_hashentry_s {uint32_t keyhash; ltedpeg_record_40_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_41_hashentry_s ltedpeg_funtype_41_hashentry_t;

struct ltedpeg_funtype_41_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_41_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_41_htbl_s * ltedpeg_funtype_41_htbl_t;

struct ltedpeg_funtype_41_s {uint32_t count;
        ltedpeg_funtype_41_ftbl_t ftbl;
        ltedpeg_funtype_41_htbl_t htbl;};

extern void release_ltedpeg_funtype_41(ltedpeg_funtype_41_t x);

extern ltedpeg_funtype_41_t copy_ltedpeg_funtype_41(ltedpeg_funtype_41_t x);

extern bool_t equal_ltedpeg_funtype_41(ltedpeg_funtype_41_t x, ltedpeg_funtype_41_t y);

extern char* json_ltedpeg_funtype_41(ltedpeg_funtype_41_t x);


//REDUCE_nat

struct ltedpeg_record_42_s {
        uint32_t count; 
        uint8_t project_1;
        uint8_t project_2;
        uint8_t project_3;
        ltedpeg__prepeg_adt_t project_4;};
typedef struct ltedpeg_record_42_s * ltedpeg_record_42_t;

extern ltedpeg_record_42_t new_ltedpeg_record_42(void);

extern void release_ltedpeg_record_42(ltedpeg_record_42_t x);

extern ltedpeg_record_42_t copy_ltedpeg_record_42(ltedpeg_record_42_t x);

extern bool_t equal_ltedpeg_record_42(ltedpeg_record_42_t x, ltedpeg_record_42_t y);
extern char * json_ltedpeg_record_42(ltedpeg_record_42_t x);

typedef struct actual_ltedpeg_record_42_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_42_t;
extern void release_ltedpeg_record_42_ptr(pointer_t x, type_actual_t ltedpeg_record_42);

extern bool_t equal_ltedpeg_record_42_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_42_t T);

extern char * json_ltedpeg_record_42_ptr(pointer_t x,  actual_ltedpeg_record_42_t T);

actual_ltedpeg_record_42_t actual_ltedpeg_record_42(void);

 

extern ltedpeg_record_42_t update_ltedpeg_record_42_project_1(ltedpeg_record_42_t x, uint8_t v);

extern ltedpeg_record_42_t update_ltedpeg_record_42_project_2(ltedpeg_record_42_t x, uint8_t v);

extern ltedpeg_record_42_t update_ltedpeg_record_42_project_3(ltedpeg_record_42_t x, uint8_t v);

extern ltedpeg_record_42_t update_ltedpeg_record_42_project_4(ltedpeg_record_42_t x, ltedpeg__prepeg_adt_t v);


//REDUCE_nat

struct ltedpeg_funtype_43_s;
        typedef struct ltedpeg_funtype_43_s * ltedpeg_funtype_43_t;

struct ltedpeg_funtype_43_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_43_s *, ltedpeg_record_42_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_43_s *, uint8_t, uint8_t, uint8_t, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_43_s *);
        struct ltedpeg_funtype_43_s * (* cptr)(struct ltedpeg_funtype_43_s *);};
typedef struct ltedpeg_funtype_43_ftbl_s * ltedpeg_funtype_43_ftbl_t;

struct ltedpeg_funtype_43_hashentry_s {uint32_t keyhash; ltedpeg_record_42_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_43_hashentry_s ltedpeg_funtype_43_hashentry_t;

struct ltedpeg_funtype_43_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_43_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_43_htbl_s * ltedpeg_funtype_43_htbl_t;

struct ltedpeg_funtype_43_s {uint32_t count;
        ltedpeg_funtype_43_ftbl_t ftbl;
        ltedpeg_funtype_43_htbl_t htbl;};

extern void release_ltedpeg_funtype_43(ltedpeg_funtype_43_t x);

extern ltedpeg_funtype_43_t copy_ltedpeg_funtype_43(ltedpeg_funtype_43_t x);

extern bool_t equal_ltedpeg_funtype_43(ltedpeg_funtype_43_t x, ltedpeg_funtype_43_t y);

extern char* json_ltedpeg_funtype_43(ltedpeg_funtype_43_t x);




struct ltedpeg_closure_44_s;
        typedef struct ltedpeg_closure_44_s * ltedpeg_closure_44_t;

struct ltedpeg_closure_44_s {uint32_t count;
         ltedpeg_funtype_32_ftbl_t ftbl;
         ltedpeg_funtype_32_htbl_t htbl;
        ltedpeg_funtype_32_t fvar_1;
        ltedpeg_funtype_39_t fvar_2;
        ltedpeg_funtype_41_t fvar_3;
        ltedpeg_funtype_43_t fvar_4;
        ltedpeg_funtype_32_t fvar_5;};

mpz_ptr_t f_ltedpeg_closure_44(struct ltedpeg_closure_44_s * closure, ltedpeg__prepeg_adt_t bvar);

mpz_ptr_t m_ltedpeg_closure_44(struct ltedpeg_closure_44_s * closure, ltedpeg__prepeg_adt_t bvar);

extern mpz_ptr_t h_ltedpeg_closure_44(ltedpeg__prepeg_adt_t ivar_13, ltedpeg_funtype_32_t ivar_1, ltedpeg_funtype_39_t ivar_5, ltedpeg_funtype_41_t ivar_7, ltedpeg_funtype_43_t ivar_9, ltedpeg_funtype_32_t ivar_3);

ltedpeg_closure_44_t new_ltedpeg_closure_44(void);

void release_ltedpeg_closure_44(ltedpeg_funtype_32_t closure);

ltedpeg_closure_44_t copy_ltedpeg_closure_44(ltedpeg_closure_44_t x);


//reduce_ordinal

struct ltedpeg_funtype_45_s;
        typedef struct ltedpeg_funtype_45_s * ltedpeg_funtype_45_t;

struct ltedpeg_funtype_45_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_45_s *, ltedpeg__prepeg_adt_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_45_s *, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_45_s *);
        struct ltedpeg_funtype_45_s * (* cptr)(struct ltedpeg_funtype_45_s *);};
typedef struct ltedpeg_funtype_45_ftbl_s * ltedpeg_funtype_45_ftbl_t;

struct ltedpeg_funtype_45_hashentry_s {uint32_t keyhash; ltedpeg__prepeg_adt_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_45_hashentry_s ltedpeg_funtype_45_hashentry_t;

struct ltedpeg_funtype_45_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_45_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_45_htbl_s * ltedpeg_funtype_45_htbl_t;

struct ltedpeg_funtype_45_s {uint32_t count;
        ltedpeg_funtype_45_ftbl_t ftbl;
        ltedpeg_funtype_45_htbl_t htbl;};

extern void release_ltedpeg_funtype_45(ltedpeg_funtype_45_t x);

extern ltedpeg_funtype_45_t copy_ltedpeg_funtype_45(ltedpeg_funtype_45_t x);

extern bool_t equal_ltedpeg_funtype_45(ltedpeg_funtype_45_t x, ltedpeg_funtype_45_t y);

extern char* json_ltedpeg_funtype_45(ltedpeg_funtype_45_t x);


//reduce_ordinal

struct ltedpeg_funtype_46_s;
        typedef struct ltedpeg_funtype_46_s * ltedpeg_funtype_46_t;

struct ltedpeg_funtype_46_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_46_s *, dpeg__dpeg_grammar_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_46_s *, dpeg__dpeg_grammar_t);
        void (* rptr)(struct ltedpeg_funtype_46_s *);
        struct ltedpeg_funtype_46_s * (* cptr)(struct ltedpeg_funtype_46_s *);};
typedef struct ltedpeg_funtype_46_ftbl_s * ltedpeg_funtype_46_ftbl_t;

struct ltedpeg_funtype_46_hashentry_s {uint32_t keyhash; dpeg__dpeg_grammar_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_46_hashentry_s ltedpeg_funtype_46_hashentry_t;

struct ltedpeg_funtype_46_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_46_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_46_htbl_s * ltedpeg_funtype_46_htbl_t;

struct ltedpeg_funtype_46_s {uint32_t count;
        ltedpeg_funtype_46_ftbl_t ftbl;
        ltedpeg_funtype_46_htbl_t htbl;};

extern void release_ltedpeg_funtype_46(ltedpeg_funtype_46_t x);

extern ltedpeg_funtype_46_t copy_ltedpeg_funtype_46(ltedpeg_funtype_46_t x);

extern bool_t equal_ltedpeg_funtype_46(ltedpeg_funtype_46_t x, ltedpeg_funtype_46_t y);

extern char* json_ltedpeg_funtype_46(ltedpeg_funtype_46_t x);


//reduce_ordinal

struct ltedpeg_funtype_47_s;
        typedef struct ltedpeg_funtype_47_s * ltedpeg_funtype_47_t;

struct ltedpeg_funtype_47_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_47_s *, uint8_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_47_s *, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_47_s *);
        struct ltedpeg_funtype_47_s * (* cptr)(struct ltedpeg_funtype_47_s *);};
typedef struct ltedpeg_funtype_47_ftbl_s * ltedpeg_funtype_47_ftbl_t;

struct ltedpeg_funtype_47_hashentry_s {uint32_t keyhash; uint8_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_47_hashentry_s ltedpeg_funtype_47_hashentry_t;

struct ltedpeg_funtype_47_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_47_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_47_htbl_s * ltedpeg_funtype_47_htbl_t;

struct ltedpeg_funtype_47_s {uint32_t count;
        ltedpeg_funtype_47_ftbl_t ftbl;
        ltedpeg_funtype_47_htbl_t htbl;};

extern void release_ltedpeg_funtype_47(ltedpeg_funtype_47_t x);

extern ltedpeg_funtype_47_t copy_ltedpeg_funtype_47(ltedpeg_funtype_47_t x);

extern uint32_t lookup_ltedpeg_funtype_47(ltedpeg_funtype_47_htbl_t htbl, uint8_t i, uint32_t ihash);

extern ltedpeg_funtype_47_t dupdate_ltedpeg_funtype_47(ltedpeg_funtype_47_t a, uint8_t i, ordstruct_adt__ordstruct_adt_t v);

extern ltedpeg_funtype_47_t update_ltedpeg_funtype_47(ltedpeg_funtype_47_t a, uint8_t i, ordstruct_adt__ordstruct_adt_t v);

extern bool_t equal_ltedpeg_funtype_47(ltedpeg_funtype_47_t x, ltedpeg_funtype_47_t y);

extern char* json_ltedpeg_funtype_47(ltedpeg_funtype_47_t x);


//reduce_ordinal

struct ltedpeg_funtype_48_s;
        typedef struct ltedpeg_funtype_48_s * ltedpeg_funtype_48_t;

struct ltedpeg_funtype_48_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_48_s *, ltedpeg_record_35_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_48_s *, uint8_t, uint8_t, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_48_s *);
        struct ltedpeg_funtype_48_s * (* cptr)(struct ltedpeg_funtype_48_s *);};
typedef struct ltedpeg_funtype_48_ftbl_s * ltedpeg_funtype_48_ftbl_t;

struct ltedpeg_funtype_48_hashentry_s {uint32_t keyhash; ltedpeg_record_35_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_48_hashentry_s ltedpeg_funtype_48_hashentry_t;

struct ltedpeg_funtype_48_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_48_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_48_htbl_s * ltedpeg_funtype_48_htbl_t;

struct ltedpeg_funtype_48_s {uint32_t count;
        ltedpeg_funtype_48_ftbl_t ftbl;
        ltedpeg_funtype_48_htbl_t htbl;};

extern void release_ltedpeg_funtype_48(ltedpeg_funtype_48_t x);

extern ltedpeg_funtype_48_t copy_ltedpeg_funtype_48(ltedpeg_funtype_48_t x);

extern bool_t equal_ltedpeg_funtype_48(ltedpeg_funtype_48_t x, ltedpeg_funtype_48_t y);

extern char* json_ltedpeg_funtype_48(ltedpeg_funtype_48_t x);




struct ltedpeg_closure_49_s;
        typedef struct ltedpeg_closure_49_s * ltedpeg_closure_49_t;

struct ltedpeg_closure_49_s {uint32_t count;
         ltedpeg_funtype_45_ftbl_t ftbl;
         ltedpeg_funtype_45_htbl_t htbl;
        ordstruct_adt__ordstruct_adt_t fvar_1;
        ltedpeg_funtype_46_t fvar_2;
        ltedpeg_funtype_47_t fvar_3;
        ltedpeg_funtype_48_t fvar_4;
        ordstruct_adt__ordstruct_adt_t fvar_5;};

ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_49(struct ltedpeg_closure_49_s * closure, ltedpeg__prepeg_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_49(struct ltedpeg_closure_49_s * closure, ltedpeg__prepeg_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_49(ltedpeg__prepeg_adt_t ivar_11, ordstruct_adt__ordstruct_adt_t ivar_1, ltedpeg_funtype_46_t ivar_3, ltedpeg_funtype_47_t ivar_5, ltedpeg_funtype_48_t ivar_7, ordstruct_adt__ordstruct_adt_t ivar_2);

ltedpeg_closure_49_t new_ltedpeg_closure_49(void);

void release_ltedpeg_closure_49(ltedpeg_funtype_45_t closure);

ltedpeg_closure_49_t copy_ltedpeg_closure_49(ltedpeg_closure_49_t x);


//REDUCE_ordinal

struct ltedpeg_funtype_50_s;
        typedef struct ltedpeg_funtype_50_s * ltedpeg_funtype_50_t;

struct ltedpeg_funtype_50_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_50_s *, ltedpeg_record_38_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_50_s *, dpeg__dpeg_grammar_t, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_50_s *);
        struct ltedpeg_funtype_50_s * (* cptr)(struct ltedpeg_funtype_50_s *);};
typedef struct ltedpeg_funtype_50_ftbl_s * ltedpeg_funtype_50_ftbl_t;

struct ltedpeg_funtype_50_hashentry_s {uint32_t keyhash; ltedpeg_record_38_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_50_hashentry_s ltedpeg_funtype_50_hashentry_t;

struct ltedpeg_funtype_50_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_50_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_50_htbl_s * ltedpeg_funtype_50_htbl_t;

struct ltedpeg_funtype_50_s {uint32_t count;
        ltedpeg_funtype_50_ftbl_t ftbl;
        ltedpeg_funtype_50_htbl_t htbl;};

extern void release_ltedpeg_funtype_50(ltedpeg_funtype_50_t x);

extern ltedpeg_funtype_50_t copy_ltedpeg_funtype_50(ltedpeg_funtype_50_t x);

extern bool_t equal_ltedpeg_funtype_50(ltedpeg_funtype_50_t x, ltedpeg_funtype_50_t y);

extern char* json_ltedpeg_funtype_50(ltedpeg_funtype_50_t x);


//REDUCE_ordinal

struct ltedpeg_funtype_51_s;
        typedef struct ltedpeg_funtype_51_s * ltedpeg_funtype_51_t;

struct ltedpeg_funtype_51_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_51_s *, ltedpeg_record_40_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_51_s *, uint8_t, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_51_s *);
        struct ltedpeg_funtype_51_s * (* cptr)(struct ltedpeg_funtype_51_s *);};
typedef struct ltedpeg_funtype_51_ftbl_s * ltedpeg_funtype_51_ftbl_t;

struct ltedpeg_funtype_51_hashentry_s {uint32_t keyhash; ltedpeg_record_40_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_51_hashentry_s ltedpeg_funtype_51_hashentry_t;

struct ltedpeg_funtype_51_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_51_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_51_htbl_s * ltedpeg_funtype_51_htbl_t;

struct ltedpeg_funtype_51_s {uint32_t count;
        ltedpeg_funtype_51_ftbl_t ftbl;
        ltedpeg_funtype_51_htbl_t htbl;};

extern void release_ltedpeg_funtype_51(ltedpeg_funtype_51_t x);

extern ltedpeg_funtype_51_t copy_ltedpeg_funtype_51(ltedpeg_funtype_51_t x);

extern bool_t equal_ltedpeg_funtype_51(ltedpeg_funtype_51_t x, ltedpeg_funtype_51_t y);

extern char* json_ltedpeg_funtype_51(ltedpeg_funtype_51_t x);


//REDUCE_ordinal

struct ltedpeg_funtype_52_s;
        typedef struct ltedpeg_funtype_52_s * ltedpeg_funtype_52_t;

struct ltedpeg_funtype_52_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_52_s *, ltedpeg_record_42_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_52_s *, uint8_t, uint8_t, uint8_t, ltedpeg__prepeg_adt_t);
        void (* rptr)(struct ltedpeg_funtype_52_s *);
        struct ltedpeg_funtype_52_s * (* cptr)(struct ltedpeg_funtype_52_s *);};
typedef struct ltedpeg_funtype_52_ftbl_s * ltedpeg_funtype_52_ftbl_t;

struct ltedpeg_funtype_52_hashentry_s {uint32_t keyhash; ltedpeg_record_42_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_52_hashentry_s ltedpeg_funtype_52_hashentry_t;

struct ltedpeg_funtype_52_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_52_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_52_htbl_s * ltedpeg_funtype_52_htbl_t;

struct ltedpeg_funtype_52_s {uint32_t count;
        ltedpeg_funtype_52_ftbl_t ftbl;
        ltedpeg_funtype_52_htbl_t htbl;};

extern void release_ltedpeg_funtype_52(ltedpeg_funtype_52_t x);

extern ltedpeg_funtype_52_t copy_ltedpeg_funtype_52(ltedpeg_funtype_52_t x);

extern bool_t equal_ltedpeg_funtype_52(ltedpeg_funtype_52_t x, ltedpeg_funtype_52_t y);

extern char* json_ltedpeg_funtype_52(ltedpeg_funtype_52_t x);




struct ltedpeg_closure_53_s;
        typedef struct ltedpeg_closure_53_s * ltedpeg_closure_53_t;

struct ltedpeg_closure_53_s {uint32_t count;
         ltedpeg_funtype_45_ftbl_t ftbl;
         ltedpeg_funtype_45_htbl_t htbl;
        ltedpeg_funtype_45_t fvar_1;
        ltedpeg_funtype_50_t fvar_2;
        ltedpeg_funtype_51_t fvar_3;
        ltedpeg_funtype_52_t fvar_4;
        ltedpeg_funtype_45_t fvar_5;};

ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_53(struct ltedpeg_closure_53_s * closure, ltedpeg__prepeg_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_53(struct ltedpeg_closure_53_s * closure, ltedpeg__prepeg_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_53(ltedpeg__prepeg_adt_t ivar_13, ltedpeg_funtype_45_t ivar_1, ltedpeg_funtype_50_t ivar_5, ltedpeg_funtype_51_t ivar_7, ltedpeg_funtype_52_t ivar_9, ltedpeg_funtype_45_t ivar_3);

ltedpeg_closure_53_t new_ltedpeg_closure_53(void);

void release_ltedpeg_closure_53(ltedpeg_funtype_45_t closure);

ltedpeg_closure_53_t copy_ltedpeg_closure_53(ltedpeg_closure_53_t x);


//good_good_entry?

struct ltedpeg_funtype_54_s;
        typedef struct ltedpeg_funtype_54_s * ltedpeg_funtype_54_t;

struct ltedpeg_funtype_54_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_54_s *, ltedpeg__ent_adt_t);
        bool_t (* mptr)(struct ltedpeg_funtype_54_s *, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_54_s *);
        struct ltedpeg_funtype_54_s * (* cptr)(struct ltedpeg_funtype_54_s *);};
typedef struct ltedpeg_funtype_54_ftbl_s * ltedpeg_funtype_54_ftbl_t;

struct ltedpeg_funtype_54_hashentry_s {uint32_t keyhash; ltedpeg__ent_adt_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_54_hashentry_s ltedpeg_funtype_54_hashentry_t;

struct ltedpeg_funtype_54_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_54_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_54_htbl_s * ltedpeg_funtype_54_htbl_t;

struct ltedpeg_funtype_54_s {uint32_t count;
        ltedpeg_funtype_54_ftbl_t ftbl;
        ltedpeg_funtype_54_htbl_t htbl;};

extern void release_ltedpeg_funtype_54(ltedpeg_funtype_54_t x);

extern ltedpeg_funtype_54_t copy_ltedpeg_funtype_54(ltedpeg_funtype_54_t x);

extern bool_t equal_ltedpeg_funtype_54(ltedpeg_funtype_54_t x, ltedpeg_funtype_54_t y);

extern char* json_ltedpeg_funtype_54(ltedpeg_funtype_54_t x);




struct ltedpeg_closure_55_s;
        typedef struct ltedpeg_closure_55_s * ltedpeg_closure_55_t;

struct ltedpeg_closure_55_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;
        uint32_t fvar_1;
        uint32_t fvar_2;};

bool_t f_ltedpeg_closure_55(struct ltedpeg_closure_55_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_55(struct ltedpeg_closure_55_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_55(ltedpeg__ent_adt_t ivar_5, uint32_t ivar_1, uint32_t ivar_2);

ltedpeg_closure_55_t new_ltedpeg_closure_55(void);

void release_ltedpeg_closure_55(ltedpeg_funtype_54_t closure);

ltedpeg_closure_55_t copy_ltedpeg_closure_55(ltedpeg_closure_55_t x);




struct ltedpeg_closure_56_s;
        typedef struct ltedpeg_closure_56_s * ltedpeg_closure_56_t;

struct ltedpeg_closure_56_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;
        uint32_t fvar_1;};

bool_t f_ltedpeg_closure_56(struct ltedpeg_closure_56_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_56(struct ltedpeg_closure_56_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_56(ltedpeg__ent_adt_t ivar_4, uint32_t ivar_1);

ltedpeg_closure_56_t new_ltedpeg_closure_56(void);

void release_ltedpeg_closure_56(ltedpeg_funtype_54_t closure);

ltedpeg_closure_56_t copy_ltedpeg_closure_56(ltedpeg_closure_56_t x);




struct ltedpeg_closure_57_s;
        typedef struct ltedpeg_closure_57_s * ltedpeg_closure_57_t;

struct ltedpeg_closure_57_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;
        uint32_t fvar_1;};

bool_t f_ltedpeg_closure_57(struct ltedpeg_closure_57_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_57(struct ltedpeg_closure_57_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_57(ltedpeg__ent_adt_t ivar_4, uint32_t ivar_1);

ltedpeg_closure_57_t new_ltedpeg_closure_57(void);

void release_ltedpeg_closure_57(ltedpeg_funtype_54_t closure);

ltedpeg_closure_57_t copy_ltedpeg_closure_57(ltedpeg_closure_57_t x);




struct ltedpeg_closure_58_s;
        typedef struct ltedpeg_closure_58_s * ltedpeg_closure_58_t;

struct ltedpeg_closure_58_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;
        uint32_t fvar_1;
        uint32_t fvar_2;};

bool_t f_ltedpeg_closure_58(struct ltedpeg_closure_58_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_58(struct ltedpeg_closure_58_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_58(ltedpeg__ent_adt_t ivar_5, uint32_t ivar_1, uint32_t ivar_2);

ltedpeg_closure_58_t new_ltedpeg_closure_58(void);

void release_ltedpeg_closure_58(ltedpeg_funtype_54_t closure);

ltedpeg_closure_58_t copy_ltedpeg_closure_58(ltedpeg_closure_58_t x);


//scaffold

struct ltedpeg_array_59_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         ltedpeg__ent_adt_t elems[]; };
typedef struct ltedpeg_array_59_s * ltedpeg_array_59_t;

extern ltedpeg_array_59_t new_ltedpeg_array_59(uint32_t size);

extern void release_ltedpeg_array_59(ltedpeg_array_59_t x);

extern ltedpeg_array_59_t copy_ltedpeg_array_59(ltedpeg_array_59_t x);

extern bool_t equal_ltedpeg_array_59(ltedpeg_array_59_t x, ltedpeg_array_59_t y);
extern char * json_ltedpeg_array_59(ltedpeg_array_59_t x);

typedef struct actual_ltedpeg_array_59_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_array_59_t;
extern void release_ltedpeg_array_59_ptr(pointer_t x, type_actual_t ltedpeg_array_59);

extern bool_t equal_ltedpeg_array_59_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpeg_array_59_ptr(pointer_t x, type_actual_t T);

actual_ltedpeg_array_59_t actual_ltedpeg_array_59(void);

 

extern ltedpeg_array_59_t update_ltedpeg_array_59(ltedpeg_array_59_t x, uint32_t i, ltedpeg__ent_adt_t v);

extern ltedpeg_array_59_t upgrade_ltedpeg_array_59(ltedpeg_array_59_t x, uint32_t i, ltedpeg__ent_adt_t v);


//scaffold

struct ltedpeg__scaffold_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         ltedpeg_array_59_t elems[]; };
typedef struct ltedpeg__scaffold_s * ltedpeg__scaffold_t;

extern ltedpeg__scaffold_t new_ltedpeg__scaffold(uint32_t size);

extern void release_ltedpeg__scaffold(ltedpeg__scaffold_t x);

extern ltedpeg__scaffold_t copy_ltedpeg__scaffold(ltedpeg__scaffold_t x);

extern bool_t equal_ltedpeg__scaffold(ltedpeg__scaffold_t x, ltedpeg__scaffold_t y);
extern char * json_ltedpeg__scaffold(ltedpeg__scaffold_t x);

typedef struct actual_ltedpeg__scaffold_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__scaffold_t;
extern void release_ltedpeg__scaffold_ptr(pointer_t x, type_actual_t ltedpeg__scaffold);

extern bool_t equal_ltedpeg__scaffold_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpeg__scaffold_ptr(pointer_t x, type_actual_t T);

actual_ltedpeg__scaffold_t actual_ltedpeg__scaffold(void);

 

extern ltedpeg__scaffold_t update_ltedpeg__scaffold(ltedpeg__scaffold_t x, uint32_t i, ltedpeg_array_59_t v);

extern ltedpeg__scaffold_t upgrade_ltedpeg__scaffold(ltedpeg__scaffold_t x, uint32_t i, ltedpeg_array_59_t v);


//lang_spec

struct ltedpeg__lang_spec_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         ltedpeg__prepeg_adt_t elems[]; };
typedef struct ltedpeg__lang_spec_s * ltedpeg__lang_spec_t;

extern ltedpeg__lang_spec_t new_ltedpeg__lang_spec(uint32_t size);

extern void release_ltedpeg__lang_spec(ltedpeg__lang_spec_t x);

extern ltedpeg__lang_spec_t copy_ltedpeg__lang_spec(ltedpeg__lang_spec_t x);

extern bool_t equal_ltedpeg__lang_spec(ltedpeg__lang_spec_t x, ltedpeg__lang_spec_t y);
extern char * json_ltedpeg__lang_spec(ltedpeg__lang_spec_t x);

typedef struct actual_ltedpeg__lang_spec_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__lang_spec_t;
extern void release_ltedpeg__lang_spec_ptr(pointer_t x, type_actual_t ltedpeg__lang_spec);

extern bool_t equal_ltedpeg__lang_spec_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpeg__lang_spec_ptr(pointer_t x, type_actual_t T);

actual_ltedpeg__lang_spec_t actual_ltedpeg__lang_spec(void);

 

extern ltedpeg__lang_spec_t update_ltedpeg__lang_spec(ltedpeg__lang_spec_t x, uint32_t i, ltedpeg__prepeg_adt_t v);

extern ltedpeg__lang_spec_t upgrade_ltedpeg__lang_spec(ltedpeg__lang_spec_t x, uint32_t i, ltedpeg__prepeg_adt_t v);


//instack

struct ltedpeg_funtype_62_s;
        typedef struct ltedpeg_funtype_62_s * ltedpeg_funtype_62_t;

struct ltedpeg_funtype_62_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_62_s *, ltedpeg_record_9_t);
        bool_t (* mptr)(struct ltedpeg_funtype_62_s *, uint32_t, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_62_s *);
        struct ltedpeg_funtype_62_s * (* cptr)(struct ltedpeg_funtype_62_s *);};
typedef struct ltedpeg_funtype_62_ftbl_s * ltedpeg_funtype_62_ftbl_t;

struct ltedpeg_funtype_62_hashentry_s {uint32_t keyhash; ltedpeg_record_9_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_62_hashentry_s ltedpeg_funtype_62_hashentry_t;

struct ltedpeg_funtype_62_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_62_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_62_htbl_s * ltedpeg_funtype_62_htbl_t;

struct ltedpeg_funtype_62_s {uint32_t count;
        ltedpeg_funtype_62_ftbl_t ftbl;
        ltedpeg_funtype_62_htbl_t htbl;};

extern void release_ltedpeg_funtype_62(ltedpeg_funtype_62_t x);

extern ltedpeg_funtype_62_t copy_ltedpeg_funtype_62(ltedpeg_funtype_62_t x);

extern bool_t equal_ltedpeg_funtype_62(ltedpeg_funtype_62_t x, ltedpeg_funtype_62_t y);

extern char* json_ltedpeg_funtype_62(ltedpeg_funtype_62_t x);




struct ltedpeg_closure_63_s;
        typedef struct ltedpeg_closure_63_s * ltedpeg_closure_63_t;

struct ltedpeg_closure_63_s {uint32_t count;
         ltedpeg_funtype_62_ftbl_t ftbl;
         ltedpeg_funtype_62_htbl_t htbl;
        ltedpeg__scaffold_t fvar_1;};

bool_t f_ltedpeg_closure_63(struct ltedpeg_closure_63_s * closure, ltedpeg_record_9_t bvar);

bool_t m_ltedpeg_closure_63(struct ltedpeg_closure_63_s * closure, uint32_t bvar_1, uint8_t bvar_2);

extern bool_t h_ltedpeg_closure_63(uint32_t ivar_7, uint8_t ivar_8, ltedpeg__scaffold_t ivar_2);

ltedpeg_closure_63_t new_ltedpeg_closure_63(void);

void release_ltedpeg_closure_63(ltedpeg_funtype_62_t closure);

ltedpeg_closure_63_t copy_ltedpeg_closure_63(ltedpeg_closure_63_t x);


//successor

struct ltedpeg_record_64_s {
        uint32_t count; 
        ltedpeg__ent_adt_t project_1;
        ltedpeg__ent_adt_t project_2;};
typedef struct ltedpeg_record_64_s * ltedpeg_record_64_t;

extern ltedpeg_record_64_t new_ltedpeg_record_64(void);

extern void release_ltedpeg_record_64(ltedpeg_record_64_t x);

extern ltedpeg_record_64_t copy_ltedpeg_record_64(ltedpeg_record_64_t x);

extern bool_t equal_ltedpeg_record_64(ltedpeg_record_64_t x, ltedpeg_record_64_t y);
extern char * json_ltedpeg_record_64(ltedpeg_record_64_t x);

typedef struct actual_ltedpeg_record_64_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_64_t;
extern void release_ltedpeg_record_64_ptr(pointer_t x, type_actual_t ltedpeg_record_64);

extern bool_t equal_ltedpeg_record_64_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_64_t T);

extern char * json_ltedpeg_record_64_ptr(pointer_t x,  actual_ltedpeg_record_64_t T);

actual_ltedpeg_record_64_t actual_ltedpeg_record_64(void);

 

extern ltedpeg_record_64_t update_ltedpeg_record_64_project_1(ltedpeg_record_64_t x, ltedpeg__ent_adt_t v);

extern ltedpeg_record_64_t update_ltedpeg_record_64_project_2(ltedpeg_record_64_t x, ltedpeg__ent_adt_t v);


//successor

struct ltedpeg_funtype_65_s;
        typedef struct ltedpeg_funtype_65_s * ltedpeg_funtype_65_t;

struct ltedpeg_funtype_65_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_65_s *, ltedpeg_record_64_t);
        bool_t (* mptr)(struct ltedpeg_funtype_65_s *, ltedpeg__ent_adt_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_65_s *);
        struct ltedpeg_funtype_65_s * (* cptr)(struct ltedpeg_funtype_65_s *);};
typedef struct ltedpeg_funtype_65_ftbl_s * ltedpeg_funtype_65_ftbl_t;

struct ltedpeg_funtype_65_hashentry_s {uint32_t keyhash; ltedpeg_record_64_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_65_hashentry_s ltedpeg_funtype_65_hashentry_t;

struct ltedpeg_funtype_65_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_65_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_65_htbl_s * ltedpeg_funtype_65_htbl_t;

struct ltedpeg_funtype_65_s {uint32_t count;
        ltedpeg_funtype_65_ftbl_t ftbl;
        ltedpeg_funtype_65_htbl_t htbl;};

extern void release_ltedpeg_funtype_65(ltedpeg_funtype_65_t x);

extern ltedpeg_funtype_65_t copy_ltedpeg_funtype_65(ltedpeg_funtype_65_t x);

extern bool_t equal_ltedpeg_funtype_65(ltedpeg_funtype_65_t x, ltedpeg_funtype_65_t y);

extern char* json_ltedpeg_funtype_65(ltedpeg_funtype_65_t x);




struct ltedpeg_closure_66_s;
        typedef struct ltedpeg_closure_66_s * ltedpeg_closure_66_t;

struct ltedpeg_closure_66_s {uint32_t count;
         ltedpeg_funtype_65_ftbl_t ftbl;
         ltedpeg_funtype_65_htbl_t htbl;
        ltedpeg__lang_spec_t fvar_1;
        ltedpeg__scaffold_t fvar_2;};

bool_t f_ltedpeg_closure_66(struct ltedpeg_closure_66_s * closure, ltedpeg_record_64_t bvar);

bool_t m_ltedpeg_closure_66(struct ltedpeg_closure_66_s * closure, ltedpeg__ent_adt_t bvar_1, ltedpeg__ent_adt_t bvar_2);

extern bool_t h_ltedpeg_closure_66(ltedpeg__ent_adt_t ivar_8, ltedpeg__ent_adt_t ivar_9, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_3);

ltedpeg_closure_66_t new_ltedpeg_closure_66(void);

void release_ltedpeg_closure_66(ltedpeg_funtype_65_t closure);

ltedpeg_closure_66_t copy_ltedpeg_closure_66(ltedpeg_closure_66_t x);


//sigma

struct ltedpeg_funtype_67_s;
        typedef struct ltedpeg_funtype_67_s * ltedpeg_funtype_67_t;

struct ltedpeg_funtype_67_ftbl_s {mpz_ptr_t (* fptr)(struct ltedpeg_funtype_67_s *, uint32_t);
        mpz_ptr_t (* mptr)(struct ltedpeg_funtype_67_s *, uint32_t);
        void (* rptr)(struct ltedpeg_funtype_67_s *);
        struct ltedpeg_funtype_67_s * (* cptr)(struct ltedpeg_funtype_67_s *);};
typedef struct ltedpeg_funtype_67_ftbl_s * ltedpeg_funtype_67_ftbl_t;

struct ltedpeg_funtype_67_hashentry_s {uint32_t keyhash; uint32_t key; mpz_t value;}; 
typedef struct ltedpeg_funtype_67_hashentry_s ltedpeg_funtype_67_hashentry_t;

struct ltedpeg_funtype_67_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_67_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_67_htbl_s * ltedpeg_funtype_67_htbl_t;

struct ltedpeg_funtype_67_s {uint32_t count;
        ltedpeg_funtype_67_ftbl_t ftbl;
        ltedpeg_funtype_67_htbl_t htbl;};

extern void release_ltedpeg_funtype_67(ltedpeg_funtype_67_t x);

extern ltedpeg_funtype_67_t copy_ltedpeg_funtype_67(ltedpeg_funtype_67_t x);

extern uint32_t lookup_ltedpeg_funtype_67(ltedpeg_funtype_67_htbl_t htbl, uint32_t i, uint32_t ihash);

extern ltedpeg_funtype_67_t dupdate_ltedpeg_funtype_67(ltedpeg_funtype_67_t a, uint32_t i, mpz_ptr_t v);

extern ltedpeg_funtype_67_t update_ltedpeg_funtype_67(ltedpeg_funtype_67_t a, uint32_t i, mpz_ptr_t v);

extern bool_t equal_ltedpeg_funtype_67(ltedpeg_funtype_67_t x, ltedpeg_funtype_67_t y);

extern char* json_ltedpeg_funtype_67(ltedpeg_funtype_67_t x);


//sigma

struct ltedpeg_array_68_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         mpz_ptr_t elems[]; };
typedef struct ltedpeg_array_68_s * ltedpeg_array_68_t;

extern ltedpeg_array_68_t new_ltedpeg_array_68(uint32_t size);

extern void release_ltedpeg_array_68(ltedpeg_array_68_t x);

extern ltedpeg_array_68_t copy_ltedpeg_array_68(ltedpeg_array_68_t x);

extern bool_t equal_ltedpeg_array_68(ltedpeg_array_68_t x, ltedpeg_array_68_t y);
extern char * json_ltedpeg_array_68(ltedpeg_array_68_t x);

typedef struct actual_ltedpeg_array_68_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_array_68_t;
extern void release_ltedpeg_array_68_ptr(pointer_t x, type_actual_t ltedpeg_array_68);

extern bool_t equal_ltedpeg_array_68_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpeg_array_68_ptr(pointer_t x, type_actual_t T);

actual_ltedpeg_array_68_t actual_ltedpeg_array_68(void);

 

extern ltedpeg_array_68_t update_ltedpeg_array_68(ltedpeg_array_68_t x, uint32_t i, mpz_t v);

extern ltedpeg_array_68_t upgrade_ltedpeg_array_68(ltedpeg_array_68_t x, uint32_t i, mpz_t v);




struct ltedpeg_closure_69_s;
        typedef struct ltedpeg_closure_69_s * ltedpeg_closure_69_t;

struct ltedpeg_closure_69_s {uint32_t count;
         ltedpeg_funtype_67_ftbl_t ftbl;
         ltedpeg_funtype_67_htbl_t htbl;
        ltedpeg_array_68_t fvar_1;
        uint32_t fvar_2;};

mpz_ptr_t f_ltedpeg_closure_69(struct ltedpeg_closure_69_s * closure, uint32_t bvar);

mpz_ptr_t m_ltedpeg_closure_69(struct ltedpeg_closure_69_s * closure, uint32_t bvar);

extern mpz_ptr_t h_ltedpeg_closure_69(uint32_t ivar_5, ltedpeg_array_68_t ivar_2, uint32_t ivar_1);

ltedpeg_closure_69_t new_ltedpeg_closure_69(void);

void release_ltedpeg_closure_69(ltedpeg_funtype_67_t closure);

ltedpeg_closure_69_t copy_ltedpeg_closure_69(ltedpeg_closure_69_t x);


//scafcount

struct ltedpeg_funtype_70_s;
        typedef struct ltedpeg_funtype_70_s * ltedpeg_funtype_70_t;

struct ltedpeg_funtype_70_ftbl_s {uint8_t (* fptr)(struct ltedpeg_funtype_70_s *, uint32_t);
        uint8_t (* mptr)(struct ltedpeg_funtype_70_s *, uint32_t);
        void (* rptr)(struct ltedpeg_funtype_70_s *);
        struct ltedpeg_funtype_70_s * (* cptr)(struct ltedpeg_funtype_70_s *);};
typedef struct ltedpeg_funtype_70_ftbl_s * ltedpeg_funtype_70_ftbl_t;

struct ltedpeg_funtype_70_hashentry_s {uint32_t keyhash; uint32_t key; uint8_t value;}; 
typedef struct ltedpeg_funtype_70_hashentry_s ltedpeg_funtype_70_hashentry_t;

struct ltedpeg_funtype_70_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_70_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_70_htbl_s * ltedpeg_funtype_70_htbl_t;

struct ltedpeg_funtype_70_s {uint32_t count;
        ltedpeg_funtype_70_ftbl_t ftbl;
        ltedpeg_funtype_70_htbl_t htbl;};

extern void release_ltedpeg_funtype_70(ltedpeg_funtype_70_t x);

extern ltedpeg_funtype_70_t copy_ltedpeg_funtype_70(ltedpeg_funtype_70_t x);

extern uint32_t lookup_ltedpeg_funtype_70(ltedpeg_funtype_70_htbl_t htbl, uint32_t i, uint32_t ihash);

extern ltedpeg_funtype_70_t dupdate_ltedpeg_funtype_70(ltedpeg_funtype_70_t a, uint32_t i, uint8_t v);

extern ltedpeg_funtype_70_t update_ltedpeg_funtype_70(ltedpeg_funtype_70_t a, uint32_t i, uint8_t v);

extern bool_t equal_ltedpeg_funtype_70(ltedpeg_funtype_70_t x, ltedpeg_funtype_70_t y);

extern char* json_ltedpeg_funtype_70(ltedpeg_funtype_70_t x);




struct ltedpeg_closure_71_s;
        typedef struct ltedpeg_closure_71_s * ltedpeg_closure_71_t;

struct ltedpeg_closure_71_s {uint32_t count;
         ltedpeg_funtype_70_ftbl_t ftbl;
         ltedpeg_funtype_70_htbl_t htbl;
        ltedpeg__scaffold_t fvar_1;
        type_actual_t fvar_2;
        ltedpeg_funtype_54_t fvar_3;};

uint8_t f_ltedpeg_closure_71(struct ltedpeg_closure_71_s * closure, uint32_t bvar);

uint8_t m_ltedpeg_closure_71(struct ltedpeg_closure_71_s * closure, uint32_t bvar);

extern uint8_t h_ltedpeg_closure_71(uint32_t ivar_14, ltedpeg__scaffold_t ivar_2, type_actual_t ivar_37, ltedpeg_funtype_54_t ivar_4);

ltedpeg_closure_71_t new_ltedpeg_closure_71(void);

void release_ltedpeg_closure_71(ltedpeg_funtype_70_t closure);

ltedpeg_closure_71_t copy_ltedpeg_closure_71(ltedpeg_closure_71_t x);


//scafcount

struct ltedpeg_funtype_72_s;
        typedef struct ltedpeg_funtype_72_s * ltedpeg_funtype_72_t;

struct ltedpeg_funtype_72_ftbl_s {uint8_t (* fptr)(struct ltedpeg_funtype_72_s *, ltedpeg_array_59_t);
        uint8_t (* mptr)(struct ltedpeg_funtype_72_s *, ltedpeg_array_59_t);
        void (* rptr)(struct ltedpeg_funtype_72_s *);
        struct ltedpeg_funtype_72_s * (* cptr)(struct ltedpeg_funtype_72_s *);};
typedef struct ltedpeg_funtype_72_ftbl_s * ltedpeg_funtype_72_ftbl_t;

struct ltedpeg_funtype_72_hashentry_s {uint32_t keyhash; ltedpeg_array_59_t key; uint8_t value;}; 
typedef struct ltedpeg_funtype_72_hashentry_s ltedpeg_funtype_72_hashentry_t;

struct ltedpeg_funtype_72_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_72_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_72_htbl_s * ltedpeg_funtype_72_htbl_t;

struct ltedpeg_funtype_72_s {uint32_t count;
        ltedpeg_funtype_72_ftbl_t ftbl;
        ltedpeg_funtype_72_htbl_t htbl;};

extern void release_ltedpeg_funtype_72(ltedpeg_funtype_72_t x);

extern ltedpeg_funtype_72_t copy_ltedpeg_funtype_72(ltedpeg_funtype_72_t x);

extern bool_t equal_ltedpeg_funtype_72(ltedpeg_funtype_72_t x, ltedpeg_funtype_72_t y);

extern char* json_ltedpeg_funtype_72(ltedpeg_funtype_72_t x);


//scafcount

struct ltedpeg_funtype_73_s;
        typedef struct ltedpeg_funtype_73_s * ltedpeg_funtype_73_t;

struct ltedpeg_funtype_73_ftbl_s {uint32_t (* fptr)(struct ltedpeg_funtype_73_s *, ltedpeg_array_59_t);
        uint32_t (* mptr)(struct ltedpeg_funtype_73_s *, ltedpeg_array_59_t);
        void (* rptr)(struct ltedpeg_funtype_73_s *);
        struct ltedpeg_funtype_73_s * (* cptr)(struct ltedpeg_funtype_73_s *);};
typedef struct ltedpeg_funtype_73_ftbl_s * ltedpeg_funtype_73_ftbl_t;

struct ltedpeg_funtype_73_hashentry_s {uint32_t keyhash; ltedpeg_array_59_t key; uint32_t value;}; 
typedef struct ltedpeg_funtype_73_hashentry_s ltedpeg_funtype_73_hashentry_t;

struct ltedpeg_funtype_73_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_73_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_73_htbl_s * ltedpeg_funtype_73_htbl_t;

struct ltedpeg_funtype_73_s {uint32_t count;
        ltedpeg_funtype_73_ftbl_t ftbl;
        ltedpeg_funtype_73_htbl_t htbl;};

extern void release_ltedpeg_funtype_73(ltedpeg_funtype_73_t x);

extern ltedpeg_funtype_73_t copy_ltedpeg_funtype_73(ltedpeg_funtype_73_t x);

extern bool_t equal_ltedpeg_funtype_73(ltedpeg_funtype_73_t x, ltedpeg_funtype_73_t y);

extern char* json_ltedpeg_funtype_73(ltedpeg_funtype_73_t x);


//scafcount

struct ltedpeg_funtype_74_s;
        typedef struct ltedpeg_funtype_74_s * ltedpeg_funtype_74_t;

struct ltedpeg_funtype_74_ftbl_s {ltedpeg_funtype_73_t (* fptr)(struct ltedpeg_funtype_74_s *, ltedpeg_funtype_54_t);
        ltedpeg_funtype_73_t (* mptr)(struct ltedpeg_funtype_74_s *, ltedpeg_funtype_54_t);
        void (* rptr)(struct ltedpeg_funtype_74_s *);
        struct ltedpeg_funtype_74_s * (* cptr)(struct ltedpeg_funtype_74_s *);};
typedef struct ltedpeg_funtype_74_ftbl_s * ltedpeg_funtype_74_ftbl_t;

struct ltedpeg_funtype_74_hashentry_s {uint32_t keyhash; ltedpeg_funtype_54_t key; ltedpeg_funtype_73_t value;}; 
typedef struct ltedpeg_funtype_74_hashentry_s ltedpeg_funtype_74_hashentry_t;

struct ltedpeg_funtype_74_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_74_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_74_htbl_s * ltedpeg_funtype_74_htbl_t;

struct ltedpeg_funtype_74_s {uint32_t count;
        ltedpeg_funtype_74_ftbl_t ftbl;
        ltedpeg_funtype_74_htbl_t htbl;};

extern void release_ltedpeg_funtype_74(ltedpeg_funtype_74_t x);

extern ltedpeg_funtype_74_t copy_ltedpeg_funtype_74(ltedpeg_funtype_74_t x);

extern bool_t equal_ltedpeg_funtype_74(ltedpeg_funtype_74_t x, ltedpeg_funtype_74_t y);

extern char* json_ltedpeg_funtype_74(ltedpeg_funtype_74_t x);




struct ltedpeg_closure_75_s;
        typedef struct ltedpeg_closure_75_s * ltedpeg_closure_75_t;

struct ltedpeg_closure_75_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;};

bool_t f_ltedpeg_closure_75(struct ltedpeg_closure_75_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_75(struct ltedpeg_closure_75_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_75(ltedpeg__ent_adt_t ivar_19);

ltedpeg_closure_75_t new_ltedpeg_closure_75(void);

void release_ltedpeg_closure_75(ltedpeg_funtype_54_t closure);

ltedpeg_closure_75_t copy_ltedpeg_closure_75(ltedpeg_closure_75_t x);




struct ltedpeg_closure_76_s;
        typedef struct ltedpeg_closure_76_s * ltedpeg_closure_76_t;

struct ltedpeg_closure_76_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;};

bool_t f_ltedpeg_closure_76(struct ltedpeg_closure_76_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_76(struct ltedpeg_closure_76_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_76(ltedpeg__ent_adt_t ivar_9);

ltedpeg_closure_76_t new_ltedpeg_closure_76(void);

void release_ltedpeg_closure_76(ltedpeg_funtype_54_t closure);

ltedpeg_closure_76_t copy_ltedpeg_closure_76(ltedpeg_closure_76_t x);


//good_depth?

struct ltedpeg_funtype_77_s;
        typedef struct ltedpeg_funtype_77_s * ltedpeg_funtype_77_t;

struct ltedpeg_funtype_77_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_77_s *, uint64_t);
        bool_t (* mptr)(struct ltedpeg_funtype_77_s *, uint64_t);
        void (* rptr)(struct ltedpeg_funtype_77_s *);
        struct ltedpeg_funtype_77_s * (* cptr)(struct ltedpeg_funtype_77_s *);};
typedef struct ltedpeg_funtype_77_ftbl_s * ltedpeg_funtype_77_ftbl_t;

struct ltedpeg_funtype_77_hashentry_s {uint32_t keyhash; uint64_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_77_hashentry_s ltedpeg_funtype_77_hashentry_t;

struct ltedpeg_funtype_77_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_77_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_77_htbl_s * ltedpeg_funtype_77_htbl_t;

struct ltedpeg_funtype_77_s {uint32_t count;
        ltedpeg_funtype_77_ftbl_t ftbl;
        ltedpeg_funtype_77_htbl_t htbl;};

extern void release_ltedpeg_funtype_77(ltedpeg_funtype_77_t x);

extern ltedpeg_funtype_77_t copy_ltedpeg_funtype_77(ltedpeg_funtype_77_t x);

extern uint32_t lookup_ltedpeg_funtype_77(ltedpeg_funtype_77_htbl_t htbl, uint64_t i, uint32_t ihash);

extern ltedpeg_funtype_77_t dupdate_ltedpeg_funtype_77(ltedpeg_funtype_77_t a, uint64_t i, bool_t v);

extern ltedpeg_funtype_77_t update_ltedpeg_funtype_77(ltedpeg_funtype_77_t a, uint64_t i, bool_t v);

extern bool_t equal_ltedpeg_funtype_77(ltedpeg_funtype_77_t x, ltedpeg_funtype_77_t y);

extern char* json_ltedpeg_funtype_77(ltedpeg_funtype_77_t x);




struct ltedpeg_closure_78_s;
        typedef struct ltedpeg_closure_78_s * ltedpeg_closure_78_t;

struct ltedpeg_closure_78_s {uint32_t count;
         ltedpeg_funtype_77_ftbl_t ftbl;
         ltedpeg_funtype_77_htbl_t htbl;
        uint32_t fvar_1;
        ltedpeg__scaffold_t fvar_2;};

bool_t f_ltedpeg_closure_78(struct ltedpeg_closure_78_s * closure, uint64_t bvar);

bool_t m_ltedpeg_closure_78(struct ltedpeg_closure_78_s * closure, uint64_t bvar);

extern bool_t h_ltedpeg_closure_78(uint64_t ivar_6, uint32_t ivar_1, ltedpeg__scaffold_t ivar_2);

ltedpeg_closure_78_t new_ltedpeg_closure_78(void);

void release_ltedpeg_closure_78(ltedpeg_funtype_77_t closure);

ltedpeg_closure_78_t copy_ltedpeg_closure_78(ltedpeg_closure_78_t x);




struct ltedpeg_closure_79_s;
        typedef struct ltedpeg_closure_79_s * ltedpeg_closure_79_t;

struct ltedpeg_closure_79_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;
        uint64_t fvar_1;
        uint32_t fvar_2;
        ltedpeg__lang_spec_t fvar_3;
        ltedpeg__scaffold_t fvar_4;};

bool_t f_ltedpeg_closure_79(struct ltedpeg_closure_79_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_79(struct ltedpeg_closure_79_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_79(ltedpeg__ent_adt_t ivar_8, uint64_t ivar_3, uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_4);

ltedpeg_closure_79_t new_ltedpeg_closure_79(void);

void release_ltedpeg_closure_79(ltedpeg_funtype_54_t closure);

ltedpeg_closure_79_t copy_ltedpeg_closure_79(ltedpeg_closure_79_t x);




struct ltedpeg_closure_80_s;
        typedef struct ltedpeg_closure_80_s * ltedpeg_closure_80_t;

struct ltedpeg_closure_80_s {uint32_t count;
         ltedpeg_funtype_65_ftbl_t ftbl;
         ltedpeg_funtype_65_htbl_t htbl;
        ltedpeg__scaffold_t fvar_1;
        ltedpeg__lang_spec_t fvar_2;
        uint32_t fvar_3;
        uint64_t fvar_4;};

bool_t f_ltedpeg_closure_80(struct ltedpeg_closure_80_s * closure, ltedpeg_record_64_t bvar);

bool_t m_ltedpeg_closure_80(struct ltedpeg_closure_80_s * closure, ltedpeg__ent_adt_t bvar_1, ltedpeg__ent_adt_t bvar_2);

extern bool_t h_ltedpeg_closure_80(ltedpeg__ent_adt_t ivar_9, ltedpeg__ent_adt_t ivar_10, ltedpeg__scaffold_t ivar_4, ltedpeg__lang_spec_t ivar_2, uint32_t ivar_1, uint64_t ivar_3);

ltedpeg_closure_80_t new_ltedpeg_closure_80(void);

void release_ltedpeg_closure_80(ltedpeg_funtype_65_t closure);

ltedpeg_closure_80_t copy_ltedpeg_closure_80(ltedpeg_closure_80_t x);




struct ltedpeg_closure_81_s;
        typedef struct ltedpeg_closure_81_s * ltedpeg_closure_81_t;

struct ltedpeg_closure_81_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;
        ltedpeg__scaffold_t fvar_1;
        ltedpeg__lang_spec_t fvar_2;
        uint32_t fvar_3;
        uint64_t fvar_4;};

bool_t f_ltedpeg_closure_81(struct ltedpeg_closure_81_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_81(struct ltedpeg_closure_81_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_81(ltedpeg__ent_adt_t ivar_8, ltedpeg__scaffold_t ivar_4, ltedpeg__lang_spec_t ivar_2, uint32_t ivar_1, uint64_t ivar_3);

ltedpeg_closure_81_t new_ltedpeg_closure_81(void);

void release_ltedpeg_closure_81(ltedpeg_funtype_54_t closure);

ltedpeg_closure_81_t copy_ltedpeg_closure_81(ltedpeg_closure_81_t x);


//good_fail?

struct ltedpeg_record_82_s {
        uint32_t count; 
        ltedpeg__scaffold_t project_1;
        uint32_t project_2;
        uint8_t project_3;
        uint64_t project_4;};
typedef struct ltedpeg_record_82_s * ltedpeg_record_82_t;

extern ltedpeg_record_82_t new_ltedpeg_record_82(void);

extern void release_ltedpeg_record_82(ltedpeg_record_82_t x);

extern ltedpeg_record_82_t copy_ltedpeg_record_82(ltedpeg_record_82_t x);

extern bool_t equal_ltedpeg_record_82(ltedpeg_record_82_t x, ltedpeg_record_82_t y);
extern char * json_ltedpeg_record_82(ltedpeg_record_82_t x);

typedef struct actual_ltedpeg_record_82_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_82_t;
extern void release_ltedpeg_record_82_ptr(pointer_t x, type_actual_t ltedpeg_record_82);

extern bool_t equal_ltedpeg_record_82_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_82_t T);

extern char * json_ltedpeg_record_82_ptr(pointer_t x,  actual_ltedpeg_record_82_t T);

actual_ltedpeg_record_82_t actual_ltedpeg_record_82(void);

 

extern ltedpeg_record_82_t update_ltedpeg_record_82_project_1(ltedpeg_record_82_t x, ltedpeg__scaffold_t v);

extern ltedpeg_record_82_t update_ltedpeg_record_82_project_2(ltedpeg_record_82_t x, uint32_t v);

extern ltedpeg_record_82_t update_ltedpeg_record_82_project_3(ltedpeg_record_82_t x, uint8_t v);

extern ltedpeg_record_82_t update_ltedpeg_record_82_project_4(ltedpeg_record_82_t x, uint64_t v);


//good_fail?

struct ltedpeg_funtype_83_s;
        typedef struct ltedpeg_funtype_83_s * ltedpeg_funtype_83_t;

struct ltedpeg_funtype_83_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_83_s *, ltedpeg_record_82_t);
        bool_t (* mptr)(struct ltedpeg_funtype_83_s *, ltedpeg__scaffold_t, uint32_t, uint8_t, uint64_t);
        void (* rptr)(struct ltedpeg_funtype_83_s *);
        struct ltedpeg_funtype_83_s * (* cptr)(struct ltedpeg_funtype_83_s *);};
typedef struct ltedpeg_funtype_83_ftbl_s * ltedpeg_funtype_83_ftbl_t;

struct ltedpeg_funtype_83_hashentry_s {uint32_t keyhash; ltedpeg_record_82_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_83_hashentry_s ltedpeg_funtype_83_hashentry_t;

struct ltedpeg_funtype_83_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_83_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_83_htbl_s * ltedpeg_funtype_83_htbl_t;

struct ltedpeg_funtype_83_s {uint32_t count;
        ltedpeg_funtype_83_ftbl_t ftbl;
        ltedpeg_funtype_83_htbl_t htbl;};

extern void release_ltedpeg_funtype_83(ltedpeg_funtype_83_t x);

extern ltedpeg_funtype_83_t copy_ltedpeg_funtype_83(ltedpeg_funtype_83_t x);

extern bool_t equal_ltedpeg_funtype_83(ltedpeg_funtype_83_t x, ltedpeg_funtype_83_t y);

extern char* json_ltedpeg_funtype_83(ltedpeg_funtype_83_t x);




struct ltedpeg_closure_84_s;
        typedef struct ltedpeg_closure_84_s * ltedpeg_closure_84_t;

struct ltedpeg_closure_84_s {uint32_t count;
         ltedpeg_funtype_83_ftbl_t ftbl;
         ltedpeg_funtype_83_htbl_t htbl;
        ltedpeg__lang_spec_t fvar_1;
        bytestrings__bytestring_t fvar_2;};

bool_t f_ltedpeg_closure_84(struct ltedpeg_closure_84_s * closure, ltedpeg_record_82_t bvar);

bool_t m_ltedpeg_closure_84(struct ltedpeg_closure_84_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, uint64_t bvar_4);

extern bool_t h_ltedpeg_closure_84(ltedpeg__scaffold_t ivar_14, uint32_t ivar_17, uint8_t ivar_19, uint64_t ivar_20, ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2);

ltedpeg_closure_84_t new_ltedpeg_closure_84(void);

void release_ltedpeg_closure_84(ltedpeg_funtype_83_t closure);

ltedpeg_closure_84_t copy_ltedpeg_closure_84(ltedpeg_closure_84_t x);


//good_loop?

struct ltedpeg_record_85_s {
        uint32_t count; 
        ltedpeg__scaffold_t project_1;
        uint32_t project_2;
        uint8_t project_3;};
typedef struct ltedpeg_record_85_s * ltedpeg_record_85_t;

extern ltedpeg_record_85_t new_ltedpeg_record_85(void);

extern void release_ltedpeg_record_85(ltedpeg_record_85_t x);

extern ltedpeg_record_85_t copy_ltedpeg_record_85(ltedpeg_record_85_t x);

extern bool_t equal_ltedpeg_record_85(ltedpeg_record_85_t x, ltedpeg_record_85_t y);
extern char * json_ltedpeg_record_85(ltedpeg_record_85_t x);

typedef struct actual_ltedpeg_record_85_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_85_t;
extern void release_ltedpeg_record_85_ptr(pointer_t x, type_actual_t ltedpeg_record_85);

extern bool_t equal_ltedpeg_record_85_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_85_t T);

extern char * json_ltedpeg_record_85_ptr(pointer_t x,  actual_ltedpeg_record_85_t T);

actual_ltedpeg_record_85_t actual_ltedpeg_record_85(void);

 

extern ltedpeg_record_85_t update_ltedpeg_record_85_project_1(ltedpeg_record_85_t x, ltedpeg__scaffold_t v);

extern ltedpeg_record_85_t update_ltedpeg_record_85_project_2(ltedpeg_record_85_t x, uint32_t v);

extern ltedpeg_record_85_t update_ltedpeg_record_85_project_3(ltedpeg_record_85_t x, uint8_t v);


//good_loop?

struct ltedpeg_funtype_86_s;
        typedef struct ltedpeg_funtype_86_s * ltedpeg_funtype_86_t;

struct ltedpeg_funtype_86_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_86_s *, ltedpeg_record_85_t);
        bool_t (* mptr)(struct ltedpeg_funtype_86_s *, ltedpeg__scaffold_t, uint32_t, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_86_s *);
        struct ltedpeg_funtype_86_s * (* cptr)(struct ltedpeg_funtype_86_s *);};
typedef struct ltedpeg_funtype_86_ftbl_s * ltedpeg_funtype_86_ftbl_t;

struct ltedpeg_funtype_86_hashentry_s {uint32_t keyhash; ltedpeg_record_85_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_86_hashentry_s ltedpeg_funtype_86_hashentry_t;

struct ltedpeg_funtype_86_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_86_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_86_htbl_s * ltedpeg_funtype_86_htbl_t;

struct ltedpeg_funtype_86_s {uint32_t count;
        ltedpeg_funtype_86_ftbl_t ftbl;
        ltedpeg_funtype_86_htbl_t htbl;};

extern void release_ltedpeg_funtype_86(ltedpeg_funtype_86_t x);

extern ltedpeg_funtype_86_t copy_ltedpeg_funtype_86(ltedpeg_funtype_86_t x);

extern bool_t equal_ltedpeg_funtype_86(ltedpeg_funtype_86_t x, ltedpeg_funtype_86_t y);

extern char* json_ltedpeg_funtype_86(ltedpeg_funtype_86_t x);




struct ltedpeg_closure_87_s;
        typedef struct ltedpeg_closure_87_s * ltedpeg_closure_87_t;

struct ltedpeg_closure_87_s {uint32_t count;
         ltedpeg_funtype_86_ftbl_t ftbl;
         ltedpeg_funtype_86_htbl_t htbl;
        ltedpeg__lang_spec_t fvar_1;};

bool_t f_ltedpeg_closure_87(struct ltedpeg_closure_87_s * closure, ltedpeg_record_85_t bvar);

bool_t m_ltedpeg_closure_87(struct ltedpeg_closure_87_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3);

extern bool_t h_ltedpeg_closure_87(ltedpeg__scaffold_t ivar_9, uint32_t ivar_11, uint8_t ivar_12, ltedpeg__lang_spec_t ivar_2);

ltedpeg_closure_87_t new_ltedpeg_closure_87(void);

void release_ltedpeg_closure_87(ltedpeg_funtype_86_t closure);

ltedpeg_closure_87_t copy_ltedpeg_closure_87(ltedpeg_closure_87_t x);


//good_good?

struct ltedpeg_record_88_s {
        uint32_t count; 
        ltedpeg__scaffold_t project_1;
        uint32_t project_2;
        uint8_t project_3;
        uint64_t project_4;
        mpz_t project_5;};
typedef struct ltedpeg_record_88_s * ltedpeg_record_88_t;

extern ltedpeg_record_88_t new_ltedpeg_record_88(void);

extern void release_ltedpeg_record_88(ltedpeg_record_88_t x);

extern ltedpeg_record_88_t copy_ltedpeg_record_88(ltedpeg_record_88_t x);

extern bool_t equal_ltedpeg_record_88(ltedpeg_record_88_t x, ltedpeg_record_88_t y);
extern char * json_ltedpeg_record_88(ltedpeg_record_88_t x);

typedef struct actual_ltedpeg_record_88_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_88_t;
extern void release_ltedpeg_record_88_ptr(pointer_t x, type_actual_t ltedpeg_record_88);

extern bool_t equal_ltedpeg_record_88_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_88_t T);

extern char * json_ltedpeg_record_88_ptr(pointer_t x,  actual_ltedpeg_record_88_t T);

actual_ltedpeg_record_88_t actual_ltedpeg_record_88(void);

 

extern ltedpeg_record_88_t update_ltedpeg_record_88_project_1(ltedpeg_record_88_t x, ltedpeg__scaffold_t v);

extern ltedpeg_record_88_t update_ltedpeg_record_88_project_2(ltedpeg_record_88_t x, uint32_t v);

extern ltedpeg_record_88_t update_ltedpeg_record_88_project_3(ltedpeg_record_88_t x, uint8_t v);

extern ltedpeg_record_88_t update_ltedpeg_record_88_project_4(ltedpeg_record_88_t x, uint64_t v);

extern ltedpeg_record_88_t update_ltedpeg_record_88_project_5(ltedpeg_record_88_t x, mpz_ptr_t v);


//good_good?

struct ltedpeg_funtype_89_s;
        typedef struct ltedpeg_funtype_89_s * ltedpeg_funtype_89_t;

struct ltedpeg_funtype_89_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_89_s *, ltedpeg_record_88_t);
        bool_t (* mptr)(struct ltedpeg_funtype_89_s *, ltedpeg__scaffold_t, uint32_t, uint8_t, uint64_t, mpz_ptr_t);
        void (* rptr)(struct ltedpeg_funtype_89_s *);
        struct ltedpeg_funtype_89_s * (* cptr)(struct ltedpeg_funtype_89_s *);};
typedef struct ltedpeg_funtype_89_ftbl_s * ltedpeg_funtype_89_ftbl_t;

struct ltedpeg_funtype_89_hashentry_s {uint32_t keyhash; ltedpeg_record_88_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_89_hashentry_s ltedpeg_funtype_89_hashentry_t;

struct ltedpeg_funtype_89_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_89_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_89_htbl_s * ltedpeg_funtype_89_htbl_t;

struct ltedpeg_funtype_89_s {uint32_t count;
        ltedpeg_funtype_89_ftbl_t ftbl;
        ltedpeg_funtype_89_htbl_t htbl;};

extern void release_ltedpeg_funtype_89(ltedpeg_funtype_89_t x);

extern ltedpeg_funtype_89_t copy_ltedpeg_funtype_89(ltedpeg_funtype_89_t x);

extern bool_t equal_ltedpeg_funtype_89(ltedpeg_funtype_89_t x, ltedpeg_funtype_89_t y);

extern char* json_ltedpeg_funtype_89(ltedpeg_funtype_89_t x);




struct ltedpeg_closure_90_s;
        typedef struct ltedpeg_closure_90_s * ltedpeg_closure_90_t;

struct ltedpeg_closure_90_s {uint32_t count;
         ltedpeg_funtype_89_ftbl_t ftbl;
         ltedpeg_funtype_89_htbl_t htbl;
        ltedpeg__lang_spec_t fvar_1;
        bytestrings__bytestring_t fvar_2;};

bool_t f_ltedpeg_closure_90(struct ltedpeg_closure_90_s * closure, ltedpeg_record_88_t bvar);

bool_t m_ltedpeg_closure_90(struct ltedpeg_closure_90_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, uint64_t bvar_4, mpz_ptr_t bvar_5);

extern bool_t h_ltedpeg_closure_90(ltedpeg__scaffold_t ivar_23, uint32_t ivar_26, uint8_t ivar_28, uint64_t ivar_29, mpz_ptr_t ivar_30, ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2);

ltedpeg_closure_90_t new_ltedpeg_closure_90(void);

void release_ltedpeg_closure_90(ltedpeg_funtype_89_t closure);

ltedpeg_closure_90_t copy_ltedpeg_closure_90(ltedpeg_closure_90_t x);


//good_entry?

struct ltedpeg_record_91_s {
        uint32_t count; 
        ltedpeg__scaffold_t project_1;
        uint32_t project_2;
        uint8_t project_3;
        ltedpeg__ent_adt_t project_4;};
typedef struct ltedpeg_record_91_s * ltedpeg_record_91_t;

extern ltedpeg_record_91_t new_ltedpeg_record_91(void);

extern void release_ltedpeg_record_91(ltedpeg_record_91_t x);

extern ltedpeg_record_91_t copy_ltedpeg_record_91(ltedpeg_record_91_t x);

extern bool_t equal_ltedpeg_record_91(ltedpeg_record_91_t x, ltedpeg_record_91_t y);
extern char * json_ltedpeg_record_91(ltedpeg_record_91_t x);

typedef struct actual_ltedpeg_record_91_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg_record_91_t;
extern void release_ltedpeg_record_91_ptr(pointer_t x, type_actual_t ltedpeg_record_91);

extern bool_t equal_ltedpeg_record_91_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_91_t T);

extern char * json_ltedpeg_record_91_ptr(pointer_t x,  actual_ltedpeg_record_91_t T);

actual_ltedpeg_record_91_t actual_ltedpeg_record_91(void);

 

extern ltedpeg_record_91_t update_ltedpeg_record_91_project_1(ltedpeg_record_91_t x, ltedpeg__scaffold_t v);

extern ltedpeg_record_91_t update_ltedpeg_record_91_project_2(ltedpeg_record_91_t x, uint32_t v);

extern ltedpeg_record_91_t update_ltedpeg_record_91_project_3(ltedpeg_record_91_t x, uint8_t v);

extern ltedpeg_record_91_t update_ltedpeg_record_91_project_4(ltedpeg_record_91_t x, ltedpeg__ent_adt_t v);


//good_entry?

struct ltedpeg_funtype_92_s;
        typedef struct ltedpeg_funtype_92_s * ltedpeg_funtype_92_t;

struct ltedpeg_funtype_92_ftbl_s {bool_t (* fptr)(struct ltedpeg_funtype_92_s *, ltedpeg_record_91_t);
        bool_t (* mptr)(struct ltedpeg_funtype_92_s *, ltedpeg__scaffold_t, uint32_t, uint8_t, ltedpeg__ent_adt_t);
        void (* rptr)(struct ltedpeg_funtype_92_s *);
        struct ltedpeg_funtype_92_s * (* cptr)(struct ltedpeg_funtype_92_s *);};
typedef struct ltedpeg_funtype_92_ftbl_s * ltedpeg_funtype_92_ftbl_t;

struct ltedpeg_funtype_92_hashentry_s {uint32_t keyhash; ltedpeg_record_91_t key; bool_t value;}; 
typedef struct ltedpeg_funtype_92_hashentry_s ltedpeg_funtype_92_hashentry_t;

struct ltedpeg_funtype_92_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_92_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_92_htbl_s * ltedpeg_funtype_92_htbl_t;

struct ltedpeg_funtype_92_s {uint32_t count;
        ltedpeg_funtype_92_ftbl_t ftbl;
        ltedpeg_funtype_92_htbl_t htbl;};

extern void release_ltedpeg_funtype_92(ltedpeg_funtype_92_t x);

extern ltedpeg_funtype_92_t copy_ltedpeg_funtype_92(ltedpeg_funtype_92_t x);

extern bool_t equal_ltedpeg_funtype_92(ltedpeg_funtype_92_t x, ltedpeg_funtype_92_t y);

extern char* json_ltedpeg_funtype_92(ltedpeg_funtype_92_t x);




struct ltedpeg_closure_93_s;
        typedef struct ltedpeg_closure_93_s * ltedpeg_closure_93_t;

struct ltedpeg_closure_93_s {uint32_t count;
         ltedpeg_funtype_92_ftbl_t ftbl;
         ltedpeg_funtype_92_htbl_t htbl;
        bytestrings__bytestring_t fvar_1;
        ltedpeg__lang_spec_t fvar_2;};

bool_t f_ltedpeg_closure_93(struct ltedpeg_closure_93_s * closure, ltedpeg_record_91_t bvar);

bool_t m_ltedpeg_closure_93(struct ltedpeg_closure_93_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, ltedpeg__ent_adt_t bvar_4);

extern bool_t h_ltedpeg_closure_93(ltedpeg__scaffold_t ivar_14, uint32_t ivar_17, uint8_t ivar_19, ltedpeg__ent_adt_t ivar_20, bytestrings__bytestring_t ivar_2, ltedpeg__lang_spec_t ivar_1);

ltedpeg_closure_93_t new_ltedpeg_closure_93(void);

void release_ltedpeg_closure_93(ltedpeg_funtype_92_t closure);

ltedpeg_closure_93_t copy_ltedpeg_closure_93(ltedpeg_closure_93_t x);




struct ltedpeg_closure_94_s;
        typedef struct ltedpeg_closure_94_s * ltedpeg_closure_94_t;

struct ltedpeg_closure_94_s {uint32_t count;
         ltedpeg_funtype_92_ftbl_t ftbl;
         ltedpeg_funtype_92_htbl_t htbl;
        bytestrings__bytestring_t fvar_1;
        ltedpeg__lang_spec_t fvar_2;};

bool_t f_ltedpeg_closure_94(struct ltedpeg_closure_94_s * closure, ltedpeg_record_91_t bvar);

bool_t m_ltedpeg_closure_94(struct ltedpeg_closure_94_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, ltedpeg__ent_adt_t bvar_4);

extern bool_t h_ltedpeg_closure_94(ltedpeg__scaffold_t ivar_14, uint32_t ivar_17, uint8_t ivar_19, ltedpeg__ent_adt_t ivar_20, bytestrings__bytestring_t ivar_2, ltedpeg__lang_spec_t ivar_1);

ltedpeg_closure_94_t new_ltedpeg_closure_94(void);

void release_ltedpeg_closure_94(ltedpeg_funtype_92_t closure);

ltedpeg_closure_94_t copy_ltedpeg_closure_94(ltedpeg_closure_94_t x);




struct ltedpeg_closure_95_s;
        typedef struct ltedpeg_closure_95_s * ltedpeg_closure_95_t;

struct ltedpeg_closure_95_s {uint32_t count;
         ltedpeg_funtype_62_ftbl_t ftbl;
         ltedpeg_funtype_62_htbl_t htbl;
        ltedpeg__scaffold_t fvar_1;};

bool_t f_ltedpeg_closure_95(struct ltedpeg_closure_95_s * closure, ltedpeg_record_9_t bvar);

bool_t m_ltedpeg_closure_95(struct ltedpeg_closure_95_s * closure, uint32_t bvar_1, uint8_t bvar_2);

extern bool_t h_ltedpeg_closure_95(uint32_t ivar_7, uint8_t ivar_8, ltedpeg__scaffold_t ivar_2);

ltedpeg_closure_95_t new_ltedpeg_closure_95(void);

void release_ltedpeg_closure_95(ltedpeg_funtype_62_t closure);

ltedpeg_closure_95_t copy_ltedpeg_closure_95(ltedpeg_closure_95_t x);


//state

struct ltedpeg__state_s {
        uint32_t count; 
        ltedpeg__scaffold_t scaf;
        uint64_t depth;
        ltedpeg__ent_adt_t stack;
        bool_t lflag;};
typedef struct ltedpeg__state_s * ltedpeg__state_t;

extern ltedpeg__state_t new_ltedpeg__state(void);

extern void release_ltedpeg__state(ltedpeg__state_t x);

extern ltedpeg__state_t copy_ltedpeg__state(ltedpeg__state_t x);

extern bool_t equal_ltedpeg__state(ltedpeg__state_t x, ltedpeg__state_t y);
extern char * json_ltedpeg__state(ltedpeg__state_t x);

typedef struct actual_ltedpeg__state_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpeg__state_t;
extern void release_ltedpeg__state_ptr(pointer_t x, type_actual_t ltedpeg__state);

extern bool_t equal_ltedpeg__state_ptr(pointer_t x, pointer_t y, actual_ltedpeg__state_t T);

extern char * json_ltedpeg__state_ptr(pointer_t x,  actual_ltedpeg__state_t T);

actual_ltedpeg__state_t actual_ltedpeg__state(void);

 

extern ltedpeg__state_t update_ltedpeg__state_scaf(ltedpeg__state_t x, ltedpeg__scaffold_t v);

extern ltedpeg__state_t update_ltedpeg__state_depth(ltedpeg__state_t x, uint64_t v);

extern ltedpeg__state_t update_ltedpeg__state_stack(ltedpeg__state_t x, ltedpeg__ent_adt_t v);

extern ltedpeg__state_t update_ltedpeg__state_lflag(ltedpeg__state_t x, bool_t v);


//step

struct ltedpeg_funtype_97_s;
        typedef struct ltedpeg_funtype_97_s * ltedpeg_funtype_97_t;

struct ltedpeg_funtype_97_ftbl_s {ltedpeg__state_t (* fptr)(struct ltedpeg_funtype_97_s *, ltedpeg__state_t);
        ltedpeg__state_t (* mptr)(struct ltedpeg_funtype_97_s *, ltedpeg__state_t);
        void (* rptr)(struct ltedpeg_funtype_97_s *);
        struct ltedpeg_funtype_97_s * (* cptr)(struct ltedpeg_funtype_97_s *);};
typedef struct ltedpeg_funtype_97_ftbl_s * ltedpeg_funtype_97_ftbl_t;

struct ltedpeg_funtype_97_hashentry_s {uint32_t keyhash; ltedpeg__state_t key; ltedpeg__state_t value;}; 
typedef struct ltedpeg_funtype_97_hashentry_s ltedpeg_funtype_97_hashentry_t;

struct ltedpeg_funtype_97_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_97_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_97_htbl_s * ltedpeg_funtype_97_htbl_t;

struct ltedpeg_funtype_97_s {uint32_t count;
        ltedpeg_funtype_97_ftbl_t ftbl;
        ltedpeg_funtype_97_htbl_t htbl;};

extern void release_ltedpeg_funtype_97(ltedpeg_funtype_97_t x);

extern ltedpeg_funtype_97_t copy_ltedpeg_funtype_97(ltedpeg_funtype_97_t x);

extern bool_t equal_ltedpeg_funtype_97(ltedpeg_funtype_97_t x, ltedpeg_funtype_97_t y);

extern char* json_ltedpeg_funtype_97(ltedpeg_funtype_97_t x);




struct ltedpeg_closure_98_s;
        typedef struct ltedpeg_closure_98_s * ltedpeg_closure_98_t;

struct ltedpeg_closure_98_s {uint32_t count;
         ltedpeg_funtype_97_ftbl_t ftbl;
         ltedpeg_funtype_97_htbl_t htbl;
        bytestrings__bytestring_t fvar_1;
        ltedpeg__lang_spec_t fvar_2;};

ltedpeg__state_t f_ltedpeg_closure_98(struct ltedpeg_closure_98_s * closure, ltedpeg__state_t bvar);

ltedpeg__state_t m_ltedpeg_closure_98(struct ltedpeg_closure_98_s * closure, ltedpeg__state_t bvar);

extern ltedpeg__state_t h_ltedpeg_closure_98(ltedpeg__state_t ivar_14, bytestrings__bytestring_t ivar_2, ltedpeg__lang_spec_t ivar_1);

ltedpeg_closure_98_t new_ltedpeg_closure_98(void);

void release_ltedpeg_closure_98(ltedpeg_funtype_97_t closure);

ltedpeg_closure_98_t copy_ltedpeg_closure_98(ltedpeg_closure_98_t x);


//size

struct ltedpeg_funtype_99_s;
        typedef struct ltedpeg_funtype_99_s * ltedpeg_funtype_99_t;

struct ltedpeg_funtype_99_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct ltedpeg_funtype_99_s *, ltedpeg__state_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct ltedpeg_funtype_99_s *, ltedpeg__state_t);
        void (* rptr)(struct ltedpeg_funtype_99_s *);
        struct ltedpeg_funtype_99_s * (* cptr)(struct ltedpeg_funtype_99_s *);};
typedef struct ltedpeg_funtype_99_ftbl_s * ltedpeg_funtype_99_ftbl_t;

struct ltedpeg_funtype_99_hashentry_s {uint32_t keyhash; ltedpeg__state_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct ltedpeg_funtype_99_hashentry_s ltedpeg_funtype_99_hashentry_t;

struct ltedpeg_funtype_99_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_99_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_99_htbl_s * ltedpeg_funtype_99_htbl_t;

struct ltedpeg_funtype_99_s {uint32_t count;
        ltedpeg_funtype_99_ftbl_t ftbl;
        ltedpeg_funtype_99_htbl_t htbl;};

extern void release_ltedpeg_funtype_99(ltedpeg_funtype_99_t x);

extern ltedpeg_funtype_99_t copy_ltedpeg_funtype_99(ltedpeg_funtype_99_t x);

extern bool_t equal_ltedpeg_funtype_99(ltedpeg_funtype_99_t x, ltedpeg_funtype_99_t y);

extern char* json_ltedpeg_funtype_99(ltedpeg_funtype_99_t x);




struct ltedpeg_closure_100_s;
        typedef struct ltedpeg_closure_100_s * ltedpeg_closure_100_t;

struct ltedpeg_closure_100_s {uint32_t count;
         ltedpeg_funtype_99_ftbl_t ftbl;
         ltedpeg_funtype_99_htbl_t htbl;
        bytestrings__bytestring_t fvar_1;};

ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_100(struct ltedpeg_closure_100_s * closure, ltedpeg__state_t bvar);

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_100(struct ltedpeg_closure_100_s * closure, ltedpeg__state_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_100(ltedpeg__state_t ivar_12, bytestrings__bytestring_t ivar_2);

ltedpeg_closure_100_t new_ltedpeg_closure_100(void);

void release_ltedpeg_closure_100(ltedpeg_funtype_99_t closure);

ltedpeg_closure_100_t copy_ltedpeg_closure_100(ltedpeg_closure_100_t x);




struct ltedpeg_closure_101_s;
        typedef struct ltedpeg_closure_101_s * ltedpeg_closure_101_t;

struct ltedpeg_closure_101_s {uint32_t count;
         ltedpeg_funtype_54_ftbl_t ftbl;
         ltedpeg_funtype_54_htbl_t htbl;};

bool_t f_ltedpeg_closure_101(struct ltedpeg_closure_101_s * closure, ltedpeg__ent_adt_t bvar);

bool_t m_ltedpeg_closure_101(struct ltedpeg_closure_101_s * closure, ltedpeg__ent_adt_t bvar);

extern bool_t h_ltedpeg_closure_101(ltedpeg__ent_adt_t ivar_28);

ltedpeg_closure_101_t new_ltedpeg_closure_101(void);

void release_ltedpeg_closure_101(ltedpeg_funtype_54_t closure);

ltedpeg_closure_101_t copy_ltedpeg_closure_101(ltedpeg_closure_101_t x);


//doparse

struct ltedpeg_funtype_102_s;
        typedef struct ltedpeg_funtype_102_s * ltedpeg_funtype_102_t;

struct ltedpeg_funtype_102_ftbl_s {ltedpeg__ent_adt_t (* fptr)(struct ltedpeg_funtype_102_s *, uint8_t);
        ltedpeg__ent_adt_t (* mptr)(struct ltedpeg_funtype_102_s *, uint8_t);
        void (* rptr)(struct ltedpeg_funtype_102_s *);
        struct ltedpeg_funtype_102_s * (* cptr)(struct ltedpeg_funtype_102_s *);};
typedef struct ltedpeg_funtype_102_ftbl_s * ltedpeg_funtype_102_ftbl_t;

struct ltedpeg_funtype_102_hashentry_s {uint32_t keyhash; uint8_t key; ltedpeg__ent_adt_t value;}; 
typedef struct ltedpeg_funtype_102_hashentry_s ltedpeg_funtype_102_hashentry_t;

struct ltedpeg_funtype_102_htbl_s {uint32_t size; uint32_t num_entries; ltedpeg_funtype_102_hashentry_t * data;}; 
typedef struct ltedpeg_funtype_102_htbl_s * ltedpeg_funtype_102_htbl_t;

struct ltedpeg_funtype_102_s {uint32_t count;
        ltedpeg_funtype_102_ftbl_t ftbl;
        ltedpeg_funtype_102_htbl_t htbl;};

extern void release_ltedpeg_funtype_102(ltedpeg_funtype_102_t x);

extern ltedpeg_funtype_102_t copy_ltedpeg_funtype_102(ltedpeg_funtype_102_t x);

extern uint32_t lookup_ltedpeg_funtype_102(ltedpeg_funtype_102_htbl_t htbl, uint8_t i, uint32_t ihash);

extern ltedpeg_funtype_102_t dupdate_ltedpeg_funtype_102(ltedpeg_funtype_102_t a, uint8_t i, ltedpeg__ent_adt_t v);

extern ltedpeg_funtype_102_t update_ltedpeg_funtype_102(ltedpeg_funtype_102_t a, uint8_t i, ltedpeg__ent_adt_t v);

extern bool_t equal_ltedpeg_funtype_102(ltedpeg_funtype_102_t x, ltedpeg_funtype_102_t y);

extern char* json_ltedpeg_funtype_102(ltedpeg_funtype_102_t x);




struct ltedpeg_closure_103_s;
        typedef struct ltedpeg_closure_103_s * ltedpeg_closure_103_t;

struct ltedpeg_closure_103_s {uint32_t count;
         ltedpeg_funtype_102_ftbl_t ftbl;
         ltedpeg_funtype_102_htbl_t htbl;};

ltedpeg__ent_adt_t f_ltedpeg_closure_103(struct ltedpeg_closure_103_s * closure, uint8_t bvar);

ltedpeg__ent_adt_t m_ltedpeg_closure_103(struct ltedpeg_closure_103_s * closure, uint8_t bvar);

extern ltedpeg__ent_adt_t h_ltedpeg_closure_103(uint8_t ivar_7);

ltedpeg_closure_103_t new_ltedpeg_closure_103(void);

void release_ltedpeg_closure_103(ltedpeg_funtype_102_t closure);

ltedpeg_closure_103_t copy_ltedpeg_closure_103(ltedpeg_closure_103_t x);



extern uint8_t ltedpeg__num_non_terminals(void);

extern bool_t rec_ltedpeg__failp(ltedpeg__ent_adt_t ivar_1);

extern bool_t rec_ltedpeg__pendingp(ltedpeg__ent_adt_t ivar_1);

extern bool_t rec_ltedpeg__loopp(ltedpeg__ent_adt_t ivar_1);

extern bool_t rec_ltedpeg__goodp(ltedpeg__ent_adt_t ivar_1);

extern bool_t rec_ltedpeg__pushp(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg__ent_adt_t update_ltedpeg__ent_adt_dep(ltedpeg__ent_adt_t ivar_1, uint64_t ivar_7);

extern uint64_t ltedpeg__ent_adt_dep(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg__good_t update_ltedpeg__ent_adt_span(ltedpeg__ent_adt_t ivar_1, uint32_t ivar_3);

extern uint32_t acc_ltedpeg__ent_adt_span(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg__push_t update_ltedpeg__ent_adt_pos(ltedpeg__ent_adt_t ivar_1, uint32_t ivar_3);

extern uint32_t acc_ltedpeg__ent_adt_pos(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg__push_t update_ltedpeg__ent_adt_nt(ltedpeg__ent_adt_t ivar_1, uint8_t ivar_3);

extern uint8_t acc_ltedpeg__ent_adt_nt(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg__ent_adt_t con_ltedpeg__fail(uint64_t ivar_2);

extern ltedpeg__ent_adt_t con_ltedpeg__pending(void);

extern ltedpeg__ent_adt_t con_ltedpeg__loop(void);

extern ltedpeg__ent_adt_t con_ltedpeg__good(uint64_t ivar_2, uint32_t ivar_3);

extern ltedpeg__ent_adt_t con_ltedpeg__push(uint32_t ivar_2, uint8_t ivar_3);

extern uint8_t ltedpeg__ord_1(ltedpeg__ent_adt_t ivar_1);

extern bool_t ltedpeg__subterm_1(ltedpeg__ent_adt_t ivar_1, ltedpeg__ent_adt_t ivar_2);

extern bool_t ltedpeg__doublelessp_1(ltedpeg__ent_adt_t ivar_1, ltedpeg__ent_adt_t ivar_2);

extern ltedpeg_funtype_5_t ltedpeg__reduce_nat_1(ltedpeg_funtype_6_t ivar_1, mpz_ptr_t ivar_3, mpz_ptr_t ivar_4, ltedpeg_funtype_8_t ivar_5, ltedpeg_funtype_10_t ivar_7);

extern ltedpeg_funtype_5_t ltedpeg__REDUCE_nat_1(ltedpeg_funtype_13_t ivar_1, ltedpeg_funtype_5_t ivar_3, ltedpeg_funtype_5_t ivar_5, ltedpeg_funtype_15_t ivar_7, ltedpeg_funtype_17_t ivar_9);

extern ltedpeg_funtype_19_t ltedpeg__reduce_ordinal_1(ltedpeg_funtype_20_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_3, ordstruct_adt__ordstruct_adt_t ivar_4, ltedpeg_funtype_21_t ivar_5, ltedpeg_funtype_22_t ivar_7);

extern ltedpeg_funtype_19_t ltedpeg__REDUCE_ordinal_1(ltedpeg_funtype_24_t ivar_1, ltedpeg_funtype_19_t ivar_3, ltedpeg_funtype_19_t ivar_5, ltedpeg_funtype_25_t ivar_7, ltedpeg_funtype_26_t ivar_9);

extern bool_t rec_ltedpeg__epsilonp(ltedpeg__prepeg_adt_t ivar_1);

extern bool_t rec_ltedpeg__failurep(ltedpeg__prepeg_adt_t ivar_1);

extern bool_t rec_ltedpeg__anyp(ltedpeg__prepeg_adt_t ivar_1);

extern bool_t rec_ltedpeg__terminalp(ltedpeg__prepeg_adt_t ivar_1);

extern bool_t rec_ltedpeg__ltep(ltedpeg__prepeg_adt_t ivar_1);

extern ltedpeg__any_t update_ltedpeg__prepeg_adt_dpg(ltedpeg__prepeg_adt_t ivar_1, dpeg__dpeg_grammar_t ivar_3);

extern dpeg__dpeg_grammar_t acc_ltedpeg__prepeg_adt_dpg(ltedpeg__prepeg_adt_t ivar_1);

extern ltedpeg__terminal_t update_ltedpeg__prepeg_adt_a(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3);

extern uint8_t acc_ltedpeg__prepeg_adt_a(ltedpeg__prepeg_adt_t ivar_1);

extern ltedpeg__lte_t update_ltedpeg__prepeg_adt_fst(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3);

extern uint8_t acc_ltedpeg__prepeg_adt_fst(ltedpeg__prepeg_adt_t ivar_1);

extern ltedpeg__lte_t update_ltedpeg__prepeg_adt_lthen(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3);

extern uint8_t acc_ltedpeg__prepeg_adt_lthen(ltedpeg__prepeg_adt_t ivar_1);

extern ltedpeg__lte_t update_ltedpeg__prepeg_adt_lelse(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3);

extern uint8_t acc_ltedpeg__prepeg_adt_lelse(ltedpeg__prepeg_adt_t ivar_1);

extern ltedpeg__prepeg_adt_t con_ltedpeg__epsilon(void);

extern ltedpeg__prepeg_adt_t con_ltedpeg__failure(void);

extern ltedpeg__prepeg_adt_t con_ltedpeg__any(dpeg__dpeg_grammar_t ivar_2);

extern ltedpeg__prepeg_adt_t con_ltedpeg__terminal(uint8_t ivar_2);

extern ltedpeg__prepeg_adt_t con_ltedpeg__lte(uint8_t ivar_2, uint8_t ivar_3, uint8_t ivar_4);

extern uint8_t ltedpeg__ord_2(ltedpeg__prepeg_adt_t ivar_1);

extern bool_t ltedpeg__subterm_2(ltedpeg__prepeg_adt_t ivar_1, ltedpeg__prepeg_adt_t ivar_2);

extern bool_t ltedpeg__doublelessp_2(ltedpeg__prepeg_adt_t ivar_1, ltedpeg__prepeg_adt_t ivar_2);

extern ltedpeg_funtype_32_t ltedpeg__reduce_nat_2(mpz_ptr_t ivar_1, mpz_ptr_t ivar_2, ltedpeg_funtype_33_t ivar_3, ltedpeg_funtype_34_t ivar_5, ltedpeg_funtype_36_t ivar_7);

extern ltedpeg_funtype_32_t ltedpeg__REDUCE_nat_2(ltedpeg_funtype_32_t ivar_1, ltedpeg_funtype_32_t ivar_3, ltedpeg_funtype_39_t ivar_5, ltedpeg_funtype_41_t ivar_7, ltedpeg_funtype_43_t ivar_9);

extern ltedpeg_funtype_45_t ltedpeg__reduce_ordinal_2(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2, ltedpeg_funtype_46_t ivar_3, ltedpeg_funtype_47_t ivar_5, ltedpeg_funtype_48_t ivar_7);

extern ltedpeg_funtype_45_t ltedpeg__REDUCE_ordinal_2(ltedpeg_funtype_45_t ivar_1, ltedpeg_funtype_45_t ivar_3, ltedpeg_funtype_50_t ivar_5, ltedpeg_funtype_51_t ivar_7, ltedpeg_funtype_52_t ivar_9);

extern ltedpeg_funtype_54_t ltedpeg__good_good_entryp(uint32_t ivar_1, uint32_t ivar_2);

extern ltedpeg_funtype_54_t ltedpeg__good_push_entryp(uint32_t ivar_1);

extern ltedpeg_funtype_54_t ltedpeg__fine_push_entryp(uint32_t ivar_1);

extern ltedpeg_funtype_54_t ltedpeg__nice_entryp(uint32_t ivar_1, uint32_t ivar_2);

extern bool_t ltedpeg__loop_or_pushp(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg_funtype_62_t ltedpeg__instack(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2);

extern ltedpeg_funtype_65_t ltedpeg__successor(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_3);

extern ltedpeg_funtype_67_t ltedpeg__sigma(uint32_t ivar_1, ltedpeg_array_68_t ivar_2);

extern uint64_t ltedpeg__scafcount(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2, ltedpeg_funtype_54_t ivar_4, uint32_t ivar_6);

extern uint64_t ltedpeg__pushcount(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2);

extern bool_t ltedpeg__good_or_failp(ltedpeg__ent_adt_t ivar_1);

extern uint64_t ltedpeg__gfcount(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2);

extern ltedpeg_funtype_77_t ltedpeg__good_depthp(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2);

extern ltedpeg_funtype_54_t ltedpeg__good_stackp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, uint64_t ivar_3, ltedpeg__scaffold_t ivar_4);

extern ltedpeg_funtype_65_t ltedpeg__mem_stackp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, uint64_t ivar_3, ltedpeg__scaffold_t ivar_4);

extern bool_t ltedpeg__push_or_pendingp(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg_funtype_54_t ltedpeg__fine_stackp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, uint64_t ivar_3, ltedpeg__scaffold_t ivar_4);

extern bool_t ltedpeg__loop_readyp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_3, uint32_t ivar_5, uint8_t ivar_6);

extern ltedpeg_funtype_83_t ltedpeg__good_failp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2);

extern ltedpeg_funtype_86_t ltedpeg__good_loopp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2);

extern ltedpeg_funtype_89_t ltedpeg__good_goodp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2);

extern ltedpeg_funtype_92_t ltedpeg__good_entryp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2);

extern ltedpeg_funtype_92_t ltedpeg__fine_entryp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2);

extern ltedpeg_funtype_62_t ltedpeg__good_rootp(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2);

extern bool_t ltedpeg__emptyp(ltedpeg__ent_adt_t ivar_1);

extern ltedpeg_funtype_97_t ltedpeg__step(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3, uint8_t ivar_5);

extern ltedpeg_funtype_99_t ltedpeg__size(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3, uint8_t ivar_5);

extern ltedpeg__state_t ltedpeg__parse(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3, uint8_t ivar_5, ltedpeg__state_t ivar_6);

extern ltedpeg__ent_adt_t ltedpeg__doparse(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint8_t ivar_3);
#endif
