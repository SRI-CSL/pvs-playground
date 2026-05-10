//Code generated using pvs2ir
#ifndef _ltedpegtest_h 
#define _ltedpegtest_h

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


#include "bytestrings_c.h"


#include "exp2_c.h"


#include "file_c.h"


#include "integertypes_c.h"


#include "array_sequences_c.h"


#include "dpeg_c.h"


#include "ltedpeg_c.h"


//cc -O3 -Wall -o ltedpegtest -L /Users/e35480/git/PVS/lib/pvs2c/lib -I /Users/e35480/git/PVS/lib/pvs2c/include dpeg_c.c ltedpeg_c.c ltedpegtest_c.c <your main>.c  -lgmp -lpvs-prelude 
//djsontable

struct ltedpegtest_array_0_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         ltedpeg__prepeg_adt_t elems[]; };
typedef struct ltedpegtest_array_0_s * ltedpegtest_array_0_t;

extern ltedpegtest_array_0_t new_ltedpegtest_array_0(uint32_t size);

extern void release_ltedpegtest_array_0(ltedpegtest_array_0_t x);

extern ltedpegtest_array_0_t copy_ltedpegtest_array_0(ltedpegtest_array_0_t x);

extern bool_t equal_ltedpegtest_array_0(ltedpegtest_array_0_t x, ltedpegtest_array_0_t y);
extern char * json_ltedpegtest_array_0(ltedpegtest_array_0_t x);

typedef struct actual_ltedpegtest_array_0_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpegtest_array_0_t;
extern void release_ltedpegtest_array_0_ptr(pointer_t x, type_actual_t ltedpegtest_array_0);

extern bool_t equal_ltedpegtest_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpegtest_array_0_ptr(pointer_t x, type_actual_t T);

actual_ltedpegtest_array_0_t actual_ltedpegtest_array_0(void);

 

extern ltedpegtest_array_0_t update_ltedpegtest_array_0(ltedpegtest_array_0_t x, uint32_t i, ltedpeg__prepeg_adt_t v);

extern ltedpegtest_array_0_t upgrade_ltedpegtest_array_0(ltedpegtest_array_0_t x, uint32_t i, ltedpeg__prepeg_adt_t v);


//jsonpureparsefile

struct ltedpegtest_funtype_1_s;
        typedef struct ltedpegtest_funtype_1_s * ltedpegtest_funtype_1_t;

struct ltedpegtest_funtype_1_ftbl_s {ltedpeg__ent_adt_t (* fptr)(struct ltedpegtest_funtype_1_s *, uint8_t);
        ltedpeg__ent_adt_t (* mptr)(struct ltedpegtest_funtype_1_s *, uint8_t);
        void (* rptr)(struct ltedpegtest_funtype_1_s *);
        struct ltedpegtest_funtype_1_s * (* cptr)(struct ltedpegtest_funtype_1_s *);};
typedef struct ltedpegtest_funtype_1_ftbl_s * ltedpegtest_funtype_1_ftbl_t;

struct ltedpegtest_funtype_1_hashentry_s {uint32_t keyhash; uint8_t key; ltedpeg__ent_adt_t value;}; 
typedef struct ltedpegtest_funtype_1_hashentry_s ltedpegtest_funtype_1_hashentry_t;

struct ltedpegtest_funtype_1_htbl_s {uint32_t size; uint32_t num_entries; ltedpegtest_funtype_1_hashentry_t * data;}; 
typedef struct ltedpegtest_funtype_1_htbl_s * ltedpegtest_funtype_1_htbl_t;

struct ltedpegtest_funtype_1_s {uint32_t count;
        ltedpegtest_funtype_1_ftbl_t ftbl;
        ltedpegtest_funtype_1_htbl_t htbl;};

extern void release_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x);

extern ltedpegtest_funtype_1_t copy_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x);

extern uint32_t lookup_ltedpegtest_funtype_1(ltedpegtest_funtype_1_htbl_t htbl, uint8_t i, uint32_t ihash);

extern ltedpegtest_funtype_1_t dupdate_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t a, uint8_t i, ltedpeg__ent_adt_t v);

extern ltedpegtest_funtype_1_t update_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t a, uint8_t i, ltedpeg__ent_adt_t v);

extern bool_t equal_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x, ltedpegtest_funtype_1_t y);

extern char* json_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x);




struct ltedpegtest_closure_2_s;
        typedef struct ltedpegtest_closure_2_s * ltedpegtest_closure_2_t;

struct ltedpegtest_closure_2_s {uint32_t count;
         ltedpegtest_funtype_1_ftbl_t ftbl;
         ltedpegtest_funtype_1_htbl_t htbl;};

ltedpeg__ent_adt_t f_ltedpegtest_closure_2(struct ltedpegtest_closure_2_s * closure, uint8_t bvar);

ltedpeg__ent_adt_t m_ltedpegtest_closure_2(struct ltedpegtest_closure_2_s * closure, uint8_t bvar);

extern ltedpeg__ent_adt_t h_ltedpegtest_closure_2(uint8_t ivar_40);

ltedpegtest_closure_2_t new_ltedpegtest_closure_2(void);

void release_ltedpegtest_closure_2(ltedpegtest_funtype_1_t closure);

ltedpegtest_closure_2_t copy_ltedpegtest_closure_2(ltedpegtest_closure_2_t x);


//jsonpureparsefile

struct ltedpegtest_array_3_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         ltedpeg__ent_adt_t elems[]; };
typedef struct ltedpegtest_array_3_s * ltedpegtest_array_3_t;

extern ltedpegtest_array_3_t new_ltedpegtest_array_3(uint32_t size);

extern void release_ltedpegtest_array_3(ltedpegtest_array_3_t x);

extern ltedpegtest_array_3_t copy_ltedpegtest_array_3(ltedpegtest_array_3_t x);

extern bool_t equal_ltedpegtest_array_3(ltedpegtest_array_3_t x, ltedpegtest_array_3_t y);
extern char * json_ltedpegtest_array_3(ltedpegtest_array_3_t x);

typedef struct actual_ltedpegtest_array_3_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpegtest_array_3_t;
extern void release_ltedpegtest_array_3_ptr(pointer_t x, type_actual_t ltedpegtest_array_3);

extern bool_t equal_ltedpegtest_array_3_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpegtest_array_3_ptr(pointer_t x, type_actual_t T);

actual_ltedpegtest_array_3_t actual_ltedpegtest_array_3(void);

 

extern ltedpegtest_array_3_t update_ltedpegtest_array_3(ltedpegtest_array_3_t x, uint32_t i, ltedpeg__ent_adt_t v);

extern ltedpegtest_array_3_t upgrade_ltedpegtest_array_3(ltedpegtest_array_3_t x, uint32_t i, ltedpeg__ent_adt_t v);


//jsonpureparsefile

struct ltedpegtest_array_4_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         ltedpegtest_array_3_t elems[]; };
typedef struct ltedpegtest_array_4_s * ltedpegtest_array_4_t;

extern ltedpegtest_array_4_t new_ltedpegtest_array_4(uint32_t size);

extern void release_ltedpegtest_array_4(ltedpegtest_array_4_t x);

extern ltedpegtest_array_4_t copy_ltedpegtest_array_4(ltedpegtest_array_4_t x);

extern bool_t equal_ltedpegtest_array_4(ltedpegtest_array_4_t x, ltedpegtest_array_4_t y);
extern char * json_ltedpegtest_array_4(ltedpegtest_array_4_t x);

typedef struct actual_ltedpegtest_array_4_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpegtest_array_4_t;
extern void release_ltedpegtest_array_4_ptr(pointer_t x, type_actual_t ltedpegtest_array_4);

extern bool_t equal_ltedpegtest_array_4_ptr(pointer_t x, pointer_t y, type_actual_t T);

extern char * json_ltedpegtest_array_4_ptr(pointer_t x, type_actual_t T);

actual_ltedpegtest_array_4_t actual_ltedpegtest_array_4(void);

 

extern ltedpegtest_array_4_t update_ltedpegtest_array_4(ltedpegtest_array_4_t x, uint32_t i, ltedpegtest_array_3_t v);

extern ltedpegtest_array_4_t upgrade_ltedpegtest_array_4(ltedpegtest_array_4_t x, uint32_t i, ltedpegtest_array_3_t v);


//jsonpureparsefile

struct ltedpegtest_record_5_s {
        uint32_t count; 
        ltedpegtest_array_4_t scaf;
        uint64_t depth;
        ltedpeg__ent_adt_t stack;
        bool_t lflag;};
typedef struct ltedpegtest_record_5_s * ltedpegtest_record_5_t;

extern ltedpegtest_record_5_t new_ltedpegtest_record_5(void);

extern void release_ltedpegtest_record_5(ltedpegtest_record_5_t x);

extern ltedpegtest_record_5_t copy_ltedpegtest_record_5(ltedpegtest_record_5_t x);

extern bool_t equal_ltedpegtest_record_5(ltedpegtest_record_5_t x, ltedpegtest_record_5_t y);
extern char * json_ltedpegtest_record_5(ltedpegtest_record_5_t x);

typedef struct actual_ltedpegtest_record_5_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; json_ptr_t json_ptr;} * actual_ltedpegtest_record_5_t;
extern void release_ltedpegtest_record_5_ptr(pointer_t x, type_actual_t ltedpegtest_record_5);

extern bool_t equal_ltedpegtest_record_5_ptr(pointer_t x, pointer_t y, actual_ltedpegtest_record_5_t T);

extern char * json_ltedpegtest_record_5_ptr(pointer_t x,  actual_ltedpegtest_record_5_t T);

actual_ltedpegtest_record_5_t actual_ltedpegtest_record_5(void);

 

extern ltedpegtest_record_5_t update_ltedpegtest_record_5_scaf(ltedpegtest_record_5_t x, ltedpegtest_array_4_t v);

extern ltedpegtest_record_5_t update_ltedpegtest_record_5_depth(ltedpegtest_record_5_t x, uint64_t v);

extern ltedpegtest_record_5_t update_ltedpegtest_record_5_stack(ltedpegtest_record_5_t x, ltedpeg__ent_adt_t v);

extern ltedpegtest_record_5_t update_ltedpegtest_record_5_lflag(ltedpegtest_record_5_t x, bool_t v);



extern ltedpeg__prepeg_adt_t ltedpegtest__djson(uint8_t ivar_1);

extern ltedpegtest_array_0_t ltedpegtest__djsontable(void);

extern ltedpeg__ent_adt_t ltedpegtest__jsonpureparsefile(bytestrings__bytestring_t ivar_1);

extern bool_t ltedpegtest__jsonpureparsefile_test1(void);

extern bool_t ltedpegtest__jsonpureparsefile_test2(void);

extern bool_t ltedpegtest__jsonpureparsefile_test3(void);

extern bool_t ltedpegtest__jsonpureparsefile_test_irModel(void);

extern bool_t ltedpegtest__jsonpureparsefile_test_prelude(void);
#endif
