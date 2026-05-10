//Code generated using pvs2ir
#ifndef _arrayCount_h 
#define _arrayCount_h

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

#include "sets_c.h"


#include "exp2_c.h"


#include "integertypes_c.h"


//cc -O3 -Wall -o arrayCount -L /Users/e35480/git/PVS/lib/pvs2c/lib -I /Users/e35480/git/PVS/lib/pvs2c/include arrayCount_c.c <your main>.c  -lgmp -lpvs-prelude 

typedef pointer_t arrayCount__T_t;
//arr

struct arrayCount__arr_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         arrayCount__T_t elems[]; };
typedef struct arrayCount__arr_s * arrayCount__arr_t;

extern arrayCount__arr_t new_arrayCount__arr(uint32_t size);

extern void release_arrayCount__arr(arrayCount__arr_t x, type_actual_t arrayCount__T);

extern arrayCount__arr_t copy_arrayCount__arr(arrayCount__arr_t x);

extern bool_t equal_arrayCount__arr(arrayCount__arr_t x, arrayCount__arr_t y, type_actual_t arrayCount__T);
extern char * json_arrayCount__arr(arrayCount__arr_t x, type_actual_t arrayCount__T);

typedef struct actual_arrayCount__arr_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr; type_actual_t arrayCount__T;} * actual_arrayCount__arr_t;
extern void release_arrayCount__arr_ptr(pointer_t x, type_actual_t arrayCount__arr);

extern bool_t equal_arrayCount__arr_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_arrayCount__arr_ptr(pointer_t x, type_actual_t T);

actual_arrayCount__arr_t actual_arrayCount__arr(type_actual_t arrayCount__T);

 

extern arrayCount__arr_t update_arrayCount__arr(arrayCount__arr_t x, uint32_t i, arrayCount__T_t v, type_actual_t arrayCount__T);

extern arrayCount__arr_t upgrade_arrayCount__arr(arrayCount__arr_t x, uint32_t i, arrayCount__T_t v, type_actual_t arrayCount__T);


//count

struct arrayCount_funtype_1_s;
        typedef struct arrayCount_funtype_1_s * arrayCount_funtype_1_t;

struct arrayCount_funtype_1_ftbl_s {bool_t (* fptr)(struct arrayCount_funtype_1_s *, arrayCount__T_t);
        bool_t (* mptr)(struct arrayCount_funtype_1_s *, arrayCount__T_t);
        void (* rptr)(struct arrayCount_funtype_1_s *);
        struct arrayCount_funtype_1_s * (* cptr)(struct arrayCount_funtype_1_s *);};
typedef struct arrayCount_funtype_1_ftbl_s * arrayCount_funtype_1_ftbl_t;

struct arrayCount_funtype_1_hashentry_s {uint32_t keyhash; arrayCount__T_t key; bool_t value;}; 
typedef struct arrayCount_funtype_1_hashentry_s arrayCount_funtype_1_hashentry_t;

struct arrayCount_funtype_1_htbl_s {uint32_t size; uint32_t num_entries; arrayCount_funtype_1_hashentry_t * data;}; 
typedef struct arrayCount_funtype_1_htbl_s * arrayCount_funtype_1_htbl_t;

struct arrayCount_funtype_1_s {uint32_t count;
        arrayCount_funtype_1_ftbl_t ftbl;
        arrayCount_funtype_1_htbl_t htbl;};

extern void release_arrayCount_funtype_1(arrayCount_funtype_1_t x, type_actual_t arrayCount__T);

extern arrayCount_funtype_1_t copy_arrayCount_funtype_1(arrayCount_funtype_1_t x);

extern bool_t equal_arrayCount_funtype_1(arrayCount_funtype_1_t x, arrayCount_funtype_1_t y, type_actual_t arrayCount__T);

extern char* json_arrayCount_funtype_1(arrayCount_funtype_1_t x, type_actual_t arrayCount__T);


//count

struct arrayCount_funtype_2_s;
        typedef struct arrayCount_funtype_2_s * arrayCount_funtype_2_t;

struct arrayCount_funtype_2_ftbl_s {uint32_t (* fptr)(struct arrayCount_funtype_2_s *, arrayCount__arr_t);
        uint32_t (* mptr)(struct arrayCount_funtype_2_s *, arrayCount__arr_t);
        void (* rptr)(struct arrayCount_funtype_2_s *);
        struct arrayCount_funtype_2_s * (* cptr)(struct arrayCount_funtype_2_s *);};
typedef struct arrayCount_funtype_2_ftbl_s * arrayCount_funtype_2_ftbl_t;

struct arrayCount_funtype_2_hashentry_s {uint32_t keyhash; arrayCount__arr_t key; uint32_t value;}; 
typedef struct arrayCount_funtype_2_hashentry_s arrayCount_funtype_2_hashentry_t;

struct arrayCount_funtype_2_htbl_s {uint32_t size; uint32_t num_entries; arrayCount_funtype_2_hashentry_t * data;}; 
typedef struct arrayCount_funtype_2_htbl_s * arrayCount_funtype_2_htbl_t;

struct arrayCount_funtype_2_s {uint32_t count;
        arrayCount_funtype_2_ftbl_t ftbl;
        arrayCount_funtype_2_htbl_t htbl;};

extern void release_arrayCount_funtype_2(arrayCount_funtype_2_t x, type_actual_t arrayCount__T);

extern arrayCount_funtype_2_t copy_arrayCount_funtype_2(arrayCount_funtype_2_t x);

extern bool_t equal_arrayCount_funtype_2(arrayCount_funtype_2_t x, arrayCount_funtype_2_t y, type_actual_t arrayCount__T);

extern char* json_arrayCount_funtype_2(arrayCount_funtype_2_t x, type_actual_t arrayCount__T);


//count

struct arrayCount_funtype_3_s;
        typedef struct arrayCount_funtype_3_s * arrayCount_funtype_3_t;

struct arrayCount_funtype_3_ftbl_s {arrayCount_funtype_2_t (* fptr)(struct arrayCount_funtype_3_s *, arrayCount_funtype_1_t);
        arrayCount_funtype_2_t (* mptr)(struct arrayCount_funtype_3_s *, arrayCount_funtype_1_t);
        void (* rptr)(struct arrayCount_funtype_3_s *);
        struct arrayCount_funtype_3_s * (* cptr)(struct arrayCount_funtype_3_s *);};
typedef struct arrayCount_funtype_3_ftbl_s * arrayCount_funtype_3_ftbl_t;

struct arrayCount_funtype_3_hashentry_s {uint32_t keyhash; arrayCount_funtype_1_t key; arrayCount_funtype_2_t value;}; 
typedef struct arrayCount_funtype_3_hashentry_s arrayCount_funtype_3_hashentry_t;

struct arrayCount_funtype_3_htbl_s {uint32_t size; uint32_t num_entries; arrayCount_funtype_3_hashentry_t * data;}; 
typedef struct arrayCount_funtype_3_htbl_s * arrayCount_funtype_3_htbl_t;

struct arrayCount_funtype_3_s {uint32_t count;
        arrayCount_funtype_3_ftbl_t ftbl;
        arrayCount_funtype_3_htbl_t htbl;};

extern void release_arrayCount_funtype_3(arrayCount_funtype_3_t x, type_actual_t arrayCount__T);

extern arrayCount_funtype_3_t copy_arrayCount_funtype_3(arrayCount_funtype_3_t x);

extern bool_t equal_arrayCount_funtype_3(arrayCount_funtype_3_t x, arrayCount_funtype_3_t y, type_actual_t arrayCount__T);

extern char* json_arrayCount_funtype_3(arrayCount_funtype_3_t x, type_actual_t arrayCount__T);




struct arrayCount_closure_4_s;
        typedef struct arrayCount_closure_4_s * arrayCount_closure_4_t;

struct arrayCount_closure_4_s {uint32_t count;
         arrayCount_funtype_3_ftbl_t ftbl;
         arrayCount_funtype_3_htbl_t htbl; type_actual_t arrayCount__T;};

arrayCount_funtype_2_t f_arrayCount_closure_4(struct arrayCount_closure_4_s * closure, arrayCount_funtype_1_t bvar, type_actual_t arrayCount__T);

arrayCount_funtype_2_t m_arrayCount_closure_4(struct arrayCount_closure_4_s * closure, arrayCount_funtype_1_t bvar, type_actual_t arrayCount__T);

extern arrayCount_funtype_2_t h_arrayCount_closure_4(arrayCount_funtype_1_t ivar_7, type_actual_t arrayCount__T);

arrayCount_closure_4_t new_arrayCount_closure_4(void);

void release_arrayCount_closure_4(arrayCount_funtype_3_t closure, type_actual_t arrayCount__T);

arrayCount_closure_4_t copy_arrayCount_closure_4(arrayCount_closure_4_t x);




struct arrayCount_closure_5_s;
        typedef struct arrayCount_closure_5_s * arrayCount_closure_5_t;

struct arrayCount_closure_5_s {uint32_t count;
         arrayCount_funtype_2_ftbl_t ftbl;
         arrayCount_funtype_2_htbl_t htbl; type_actual_t arrayCount__T;};

uint32_t f_arrayCount_closure_5(struct arrayCount_closure_5_s * closure, arrayCount__arr_t bvar, type_actual_t arrayCount__T);

uint32_t m_arrayCount_closure_5(struct arrayCount_closure_5_s * closure, arrayCount__arr_t bvar, type_actual_t arrayCount__T);

extern uint32_t h_arrayCount_closure_5(arrayCount__arr_t ivar_11, type_actual_t arrayCount__T);

arrayCount_closure_5_t new_arrayCount_closure_5(void);

void release_arrayCount_closure_5(arrayCount_funtype_2_t closure, type_actual_t arrayCount__T);

arrayCount_closure_5_t copy_arrayCount_closure_5(arrayCount_closure_5_t x);



extern arrayCount_funtype_3_t arrayCount__count(type_actual_t arrayCount__T, uint32_t ivar_1);
#endif
