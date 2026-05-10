//Code generated using pvs2ir2c
#include "stringutils_c.h"



stringutils_array_0_t new_stringutils_array_0(uint32_t size){
        stringutils_array_0_t tmp = (stringutils_array_0_t) safe_malloc(sizeof(struct stringutils_array_0_s) + (size * sizeof(uint8_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_stringutils_array_0(stringutils_array_0_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_stringutils_array_0_ptr(pointer_t x, type_actual_t T){
        release_stringutils_array_0((stringutils_array_0_t)x);
}

stringutils_array_0_t copy_stringutils_array_0(stringutils_array_0_t x){
        stringutils_array_0_t tmp = new_stringutils_array_0(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = (uint8_t)x->elems[i];};
         return tmp;}

bool_t equal_stringutils_array_0(stringutils_array_0_t x, stringutils_array_0_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

char * json_stringutils_array_0(stringutils_array_0_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_uint8(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_stringutils_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_stringutils_array_0((stringutils_array_0_t)x, (stringutils_array_0_t)y);
}

char * json_stringutils_array_0_ptr(pointer_t x, type_actual_t T){
        return json_stringutils_array_0((stringutils_array_0_t)x);
}

actual_stringutils_array_0_t actual_stringutils_array_0(void){
        actual_stringutils_array_0_t new = (actual_stringutils_array_0_t)safe_malloc(sizeof(struct actual_stringutils_array_0_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_array_0_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_array_0_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_array_0_ptr);
 

 
        return new;
 }

stringutils_array_0_t update_stringutils_array_0(stringutils_array_0_t x, uint32_t i, uint8_t v){
        stringutils_array_0_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_stringutils_array_0(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}

stringutils_array_0_t upgrade_stringutils_array_0(stringutils_array_0_t x, uint32_t i, uint8_t v){
        stringutils_array_0_t y;
        uint32_t xmax = x->max;
         if (x->count == 1 && i < xmax){y = x;}
           else if (i >= xmax){uint32_t newmax = ((xmax < UINT32_MAX/2) ? ((i < 2 * (xmax + 1)) ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                y = safe_realloc(x, sizeof(struct stringutils_array_0_s) + (newmax * sizeof(uint8_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;}
           else {y = copy_stringutils_array_0(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}




stringutils_record_1_t new_stringutils_record_1(void){
        stringutils_record_1_t tmp = (stringutils_record_1_t) safe_malloc(sizeof(struct stringutils_record_1_s));
        tmp->count = 1;
        return tmp;}

void release_stringutils_record_1(stringutils_record_1_t x){
        x->count--;
        if (x->count <= 0){
         release_stringutils_array_0((stringutils_array_0_t)x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_stringutils_record_1_ptr(pointer_t x, type_actual_t T){
        release_stringutils_record_1((stringutils_record_1_t)x);
}

stringutils_record_1_t copy_stringutils_record_1(stringutils_record_1_t x){
        stringutils_record_1_t y = new_stringutils_record_1();
        y->length = (uint32_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_stringutils_record_1(stringutils_record_1_t x, stringutils_record_1_t y){
        bool_t tmp = true; tmp = tmp && x->length == y->length; tmp = tmp && equal_stringutils_array_0((stringutils_array_0_t)x->seq, (stringutils_array_0_t)y->seq);
        return tmp;}

char * json_stringutils_record_1(stringutils_record_1_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(18);
         sprintf(fld0, "\"length\" : ");
        tmp[0] = safe_strcat(fld0, json_uint32(x->length));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"seq\" : ");
        tmp[1] = safe_strcat(fld1, json_stringutils_array_0((stringutils_array_0_t)x->seq));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_stringutils_record_1_ptr(pointer_t x, pointer_t y, actual_stringutils_record_1_t T){
        return equal_stringutils_record_1((stringutils_record_1_t)x, (stringutils_record_1_t)y);
}

char * json_stringutils_record_1_ptr(pointer_t x, actual_stringutils_record_1_t T){
        return json_stringutils_record_1((stringutils_record_1_t)x);
}

actual_stringutils_record_1_t actual_stringutils_record_1(void){
        actual_stringutils_record_1_t new = (actual_stringutils_record_1_t)safe_malloc(sizeof(struct actual_stringutils_record_1_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_record_1_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_record_1_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_record_1_ptr);
 

 
        return new;
 }

stringutils_record_1_t update_stringutils_record_1_length(stringutils_record_1_t x, uint32_t v){
        stringutils_record_1_t y;
        if (x->count == 1){y = x;}
        else {y = copy_stringutils_record_1(x); x->count--;};
        y->length = (uint32_t)v;
        return y;}

stringutils_record_1_t update_stringutils_record_1_seq(stringutils_record_1_t x, stringutils_array_0_t v){
        stringutils_record_1_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_stringutils_array_0((stringutils_array_0_t)x->seq);};}
        else {y = copy_stringutils_record_1(x); x->count--; y->seq->count--;};
        y->seq = (stringutils_array_0_t)v;
        return y;}




stringutils_array_2_t new_stringutils_array_2(uint32_t size){
        stringutils_array_2_t tmp = (stringutils_array_2_t) safe_malloc(sizeof(struct stringutils_array_2_s) + (size * sizeof(mpq_ptr_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_stringutils_array_2(stringutils_array_2_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_stringutils_array_2_ptr(pointer_t x, type_actual_t T){
        release_stringutils_array_2((stringutils_array_2_t)x);
}

stringutils_array_2_t copy_stringutils_array_2(stringutils_array_2_t x){
        stringutils_array_2_t tmp = new_stringutils_array_2(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){ tmp->elems[i] = (mpq_ptr_t)safe_malloc(sizeof(mpq_t));
                mpq_init(tmp->elems[i]);
                if (i < x->size) mpq_set(tmp->elems[i], x->elems[i]);};
         return tmp;}

bool_t equal_stringutils_array_2(stringutils_array_2_t x, stringutils_array_2_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while  (i < x->size && tmp){tmp = (mpq_cmp(x->elems[i], y->elems[i]) == 0); i++;};
        return tmp;}

char * json_stringutils_array_2(stringutils_array_2_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_mpq(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_stringutils_array_2_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_stringutils_array_2((stringutils_array_2_t)x, (stringutils_array_2_t)y);
}

char * json_stringutils_array_2_ptr(pointer_t x, type_actual_t T){
        return json_stringutils_array_2((stringutils_array_2_t)x);
}

actual_stringutils_array_2_t actual_stringutils_array_2(void){
        actual_stringutils_array_2_t new = (actual_stringutils_array_2_t)safe_malloc(sizeof(struct actual_stringutils_array_2_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_array_2_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_array_2_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_array_2_ptr);
 

 
        return new;
 }

stringutils_array_2_t update_stringutils_array_2(stringutils_array_2_t x, uint32_t i, mpq_t v){
        stringutils_array_2_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_stringutils_array_2(x );
                x->count--;};
        mpq_set(y->elems[i], v);
        return y;}

stringutils_array_2_t upgrade_stringutils_array_2(stringutils_array_2_t x, uint32_t i, mpq_t v){
        stringutils_array_2_t y;
        uint32_t xmax = x->max;
         if (x->count == 1 && i < xmax){y = x;}
           else if (i >= xmax){uint32_t newmax = ((xmax < UINT32_MAX/2) ? ((i < 2 * (xmax + 1)) ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                y = safe_realloc(x, sizeof(struct stringutils_array_2_s) + (newmax * sizeof(mpq_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;}
           else {y = copy_stringutils_array_2(x );
                x->count--;};
        mpq_set(y->elems[i], v);
        return y;}




stringutils_record_3_t new_stringutils_record_3(void){
        stringutils_record_3_t tmp = (stringutils_record_3_t) safe_malloc(sizeof(struct stringutils_record_3_s));
        tmp->count = 1;
        return tmp;}

void release_stringutils_record_3(stringutils_record_3_t x){
        x->count--;
        if (x->count <= 0){
         release_stringutils_array_2((stringutils_array_2_t)x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_stringutils_record_3_ptr(pointer_t x, type_actual_t T){
        release_stringutils_record_3((stringutils_record_3_t)x);
}

stringutils_record_3_t copy_stringutils_record_3(stringutils_record_3_t x){
        stringutils_record_3_t y = new_stringutils_record_3();
        y->length = (uint8_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_stringutils_record_3(stringutils_record_3_t x, stringutils_record_3_t y){
        bool_t tmp = true; tmp = tmp && x->length == y->length; tmp = tmp && equal_stringutils_array_2((stringutils_array_2_t)x->seq, (stringutils_array_2_t)y->seq);
        return tmp;}

char * json_stringutils_record_3(stringutils_record_3_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(18);
         sprintf(fld0, "\"length\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->length));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"seq\" : ");
        tmp[1] = safe_strcat(fld1, json_stringutils_array_2((stringutils_array_2_t)x->seq));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_stringutils_record_3_ptr(pointer_t x, pointer_t y, actual_stringutils_record_3_t T){
        return equal_stringutils_record_3((stringutils_record_3_t)x, (stringutils_record_3_t)y);
}

char * json_stringutils_record_3_ptr(pointer_t x, actual_stringutils_record_3_t T){
        return json_stringutils_record_3((stringutils_record_3_t)x);
}

actual_stringutils_record_3_t actual_stringutils_record_3(void){
        actual_stringutils_record_3_t new = (actual_stringutils_record_3_t)safe_malloc(sizeof(struct actual_stringutils_record_3_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_record_3_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_record_3_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_record_3_ptr);
 

 
        return new;
 }

stringutils_record_3_t update_stringutils_record_3_length(stringutils_record_3_t x, uint8_t v){
        stringutils_record_3_t y;
        if (x->count == 1){y = x;}
        else {y = copy_stringutils_record_3(x); x->count--;};
        y->length = (uint8_t)v;
        return y;}

stringutils_record_3_t update_stringutils_record_3_seq(stringutils_record_3_t x, stringutils_array_2_t v){
        stringutils_record_3_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_stringutils_array_2((stringutils_array_2_t)x->seq);};}
        else {y = copy_stringutils_record_3(x); x->count--; y->seq->count--;};
        y->seq = (stringutils_array_2_t)v;
        return y;}




stringutils_array_4_t new_stringutils_array_4(uint32_t size){
        stringutils_array_4_t tmp = (stringutils_array_4_t) safe_malloc(sizeof(struct stringutils_array_4_s) + (size * sizeof(bytestrings__bytestring_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_stringutils_array_4(stringutils_array_4_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_bytestrings__bytestring((bytestrings__bytestring_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_stringutils_array_4_ptr(pointer_t x, type_actual_t T){
        release_stringutils_array_4((stringutils_array_4_t)x);
}

stringutils_array_4_t copy_stringutils_array_4(stringutils_array_4_t x){
        stringutils_array_4_t tmp = new_stringutils_array_4(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_stringutils_array_4(stringutils_array_4_t x, stringutils_array_4_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_bytestrings__bytestring(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_stringutils_array_4(stringutils_array_4_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_bytestrings__bytestring(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_stringutils_array_4_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_stringutils_array_4((stringutils_array_4_t)x, (stringutils_array_4_t)y);
}

char * json_stringutils_array_4_ptr(pointer_t x, type_actual_t T){
        return json_stringutils_array_4((stringutils_array_4_t)x);
}

actual_stringutils_array_4_t actual_stringutils_array_4(void){
        actual_stringutils_array_4_t new = (actual_stringutils_array_4_t)safe_malloc(sizeof(struct actual_stringutils_array_4_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_array_4_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_array_4_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_array_4_ptr);
 

 
        return new;
 }

stringutils_array_4_t update_stringutils_array_4(stringutils_array_4_t x, uint32_t i, bytestrings__bytestring_t v){
         stringutils_array_4_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_stringutils_array_4(x);
                      x->count--;};
        bytestrings__bytestring_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_bytestrings__bytestring((bytestrings__bytestring_t)yelems[i]);};
         yelems[i] = v;
         return y;}

stringutils_array_4_t upgrade_stringutils_array_4(stringutils_array_4_t x, uint32_t i, bytestrings__bytestring_t v){
         stringutils_array_4_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct stringutils_array_4_s) + (newmax * sizeof(bytestrings__bytestring_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_stringutils_array_4(x);
                            x->count--;};
        bytestrings__bytestring_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_bytestrings__bytestring((bytestrings__bytestring_t)yelems[i]);};
         yelems[i] = v;
         return y;}




stringutils_record_5_t new_stringutils_record_5(void){
        stringutils_record_5_t tmp = (stringutils_record_5_t) safe_malloc(sizeof(struct stringutils_record_5_s));
        tmp->count = 1;
        return tmp;}

void release_stringutils_record_5(stringutils_record_5_t x){
        x->count--;
        if (x->count <= 0){
         release_stringutils_array_4((stringutils_array_4_t)x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_stringutils_record_5_ptr(pointer_t x, type_actual_t T){
        release_stringutils_record_5((stringutils_record_5_t)x);
}

stringutils_record_5_t copy_stringutils_record_5(stringutils_record_5_t x){
        stringutils_record_5_t y = new_stringutils_record_5();
        y->length = (uint32_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_stringutils_record_5(stringutils_record_5_t x, stringutils_record_5_t y){
        bool_t tmp = true; tmp = tmp && x->length == y->length; tmp = tmp && equal_stringutils_array_4((stringutils_array_4_t)x->seq, (stringutils_array_4_t)y->seq);
        return tmp;}

char * json_stringutils_record_5(stringutils_record_5_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(18);
         sprintf(fld0, "\"length\" : ");
        tmp[0] = safe_strcat(fld0, json_uint32(x->length));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"seq\" : ");
        tmp[1] = safe_strcat(fld1, json_stringutils_array_4((stringutils_array_4_t)x->seq));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_stringutils_record_5_ptr(pointer_t x, pointer_t y, actual_stringutils_record_5_t T){
        return equal_stringutils_record_5((stringutils_record_5_t)x, (stringutils_record_5_t)y);
}

char * json_stringutils_record_5_ptr(pointer_t x, actual_stringutils_record_5_t T){
        return json_stringutils_record_5((stringutils_record_5_t)x);
}

actual_stringutils_record_5_t actual_stringutils_record_5(void){
        actual_stringutils_record_5_t new = (actual_stringutils_record_5_t)safe_malloc(sizeof(struct actual_stringutils_record_5_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_record_5_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_record_5_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_record_5_ptr);
 

 
        return new;
 }

stringutils_record_5_t update_stringutils_record_5_length(stringutils_record_5_t x, uint32_t v){
        stringutils_record_5_t y;
        if (x->count == 1){y = x;}
        else {y = copy_stringutils_record_5(x); x->count--;};
        y->length = (uint32_t)v;
        return y;}

stringutils_record_5_t update_stringutils_record_5_seq(stringutils_record_5_t x, stringutils_array_4_t v){
        stringutils_record_5_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_stringutils_array_4((stringutils_array_4_t)x->seq);};}
        else {y = copy_stringutils_record_5(x); x->count--; y->seq->count--;};
        y->seq = (stringutils_array_4_t)v;
        return y;}




stringutils_record_6_t new_stringutils_record_6(void){
        stringutils_record_6_t tmp = (stringutils_record_6_t) safe_malloc(sizeof(struct stringutils_record_6_s));
        tmp->count = 1;
        return tmp;}

void release_stringutils_record_6(stringutils_record_6_t x){
        x->count--;
        if (x->count <= 0){
         release_stringutils_array_4((stringutils_array_4_t)x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_stringutils_record_6_ptr(pointer_t x, type_actual_t T){
        release_stringutils_record_6((stringutils_record_6_t)x);
}

stringutils_record_6_t copy_stringutils_record_6(stringutils_record_6_t x){
        stringutils_record_6_t y = new_stringutils_record_6();
        y->length = (uint8_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_stringutils_record_6(stringutils_record_6_t x, stringutils_record_6_t y){
        bool_t tmp = true; tmp = tmp && x->length == y->length; tmp = tmp && equal_stringutils_array_4((stringutils_array_4_t)x->seq, (stringutils_array_4_t)y->seq);
        return tmp;}

char * json_stringutils_record_6(stringutils_record_6_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(18);
         sprintf(fld0, "\"length\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->length));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"seq\" : ");
        tmp[1] = safe_strcat(fld1, json_stringutils_array_4((stringutils_array_4_t)x->seq));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_stringutils_record_6_ptr(pointer_t x, pointer_t y, actual_stringutils_record_6_t T){
        return equal_stringutils_record_6((stringutils_record_6_t)x, (stringutils_record_6_t)y);
}

char * json_stringutils_record_6_ptr(pointer_t x, actual_stringutils_record_6_t T){
        return json_stringutils_record_6((stringutils_record_6_t)x);
}

actual_stringutils_record_6_t actual_stringutils_record_6(void){
        actual_stringutils_record_6_t new = (actual_stringutils_record_6_t)safe_malloc(sizeof(struct actual_stringutils_record_6_s));
        new->equal_ptr = (equal_ptr_t)(*equal_stringutils_record_6_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_stringutils_record_6_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_stringutils_record_6_ptr);
 

 
        return new;
 }

stringutils_record_6_t update_stringutils_record_6_length(stringutils_record_6_t x, uint8_t v){
        stringutils_record_6_t y;
        if (x->count == 1){y = x;}
        else {y = copy_stringutils_record_6(x); x->count--;};
        y->length = (uint8_t)v;
        return y;}

stringutils_record_6_t update_stringutils_record_6_seq(stringutils_record_6_t x, stringutils_array_4_t v){
        stringutils_record_6_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_stringutils_array_4((stringutils_array_4_t)x->seq);};}
        else {y = copy_stringutils_record_6(x); x->count--; y->seq->count--;};
        y->seq = (stringutils_array_4_t)v;
        return y;}


bool_t stringutils__digit(uint8_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)48;
        ivar_2 = (ivar_1 >= ivar_5);
        if (ivar_2){
             uint8_t ivar_8;
             ivar_8 = (uint8_t)57;
             result = (ivar_1 <= ivar_8);
        } else {
             result = (bool_t) false;};
        
        
        return result;
}

bool_t stringutils__any(uint8_t ivar_1){
        bool_t  result;

        result = (bool_t) true;
        
        
        return result;
}

bool_t stringutils__whitespace(uint8_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)32;
        ivar_2 = (ivar_1 == ivar_5);
        if (ivar_2){
             result = (bool_t) true;
        } else {
             bool_t ivar_7;
             uint8_t ivar_10;
             ivar_10 = (uint8_t)9;
             ivar_7 = (ivar_1 >= ivar_10);
             if (ivar_7){
           uint8_t ivar_13;
           ivar_13 = (uint8_t)13;
           result = (ivar_1 <= ivar_13);
             } else {
           result = (bool_t) false;};};
        
        
        return result;
}

bool_t stringutils__is_quote(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)34;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_backslash(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)92;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_slash(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)47;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_t(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)116;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_r(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)114;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_f(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)102;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_n(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)110;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_b(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)98;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_dot(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)46;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_eE(uint8_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)69;
        ivar_2 = (ivar_1 == ivar_5);
        if (ivar_2){
             result = (bool_t) true;
        } else {
             uint8_t ivar_8;
             ivar_8 = (uint8_t)101;
             result = (ivar_1 == ivar_8);};
        
        
        return result;
}

bool_t stringutils__is_plus(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)43;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_minus(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)45;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_u(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)117;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_e(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)101;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_a(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)97;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_l(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)108;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__is_s(uint8_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)115;
        result = (ivar_1 == ivar_3);
        
        
        return result;
}

bool_t stringutils__escapable(uint8_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        ivar_2 = (bool_t)stringutils__is_quote((uint8_t)ivar_1);
        if (ivar_2){
             result = (bool_t) true;
        } else {
             bool_t ivar_7;
             ivar_7 = (bool_t)stringutils__is_backslash((uint8_t)ivar_1);
             if (ivar_7){
           result = (bool_t) true;
             } else {
           bool_t ivar_12;
           ivar_12 = (bool_t)stringutils__is_slash((uint8_t)ivar_1);
           if (ivar_12){
           result = (bool_t) true;
           } else {
           bool_t ivar_17;
           ivar_17 = (bool_t)stringutils__is_b((uint8_t)ivar_1);
           if (ivar_17){
            result = (bool_t) true;
           } else {
            bool_t ivar_22;
            ivar_22 = (bool_t)stringutils__is_f((uint8_t)ivar_1);
            if (ivar_22){
             result = (bool_t) true;
            } else {
             bool_t ivar_27;
             ivar_27 = (bool_t)stringutils__is_n((uint8_t)ivar_1);
             if (ivar_27){
              result = (bool_t) true;
             } else {
              bool_t ivar_32;
              ivar_32 = (bool_t)stringutils__is_r((uint8_t)ivar_1);
              if (ivar_32){
               result = (bool_t) true;
              } else {
               result = (bool_t)stringutils__is_t((uint8_t)ivar_1);};};};};};};};
        
        
        return result;
}

uint8_t stringutils__escape_convert(uint8_t ivar_1){
        uint8_t  result;

        bool_t ivar_2;
        ivar_2 = (bool_t)stringutils__is_quote((uint8_t)ivar_1);
        if (ivar_2){
             result = (uint8_t)34;
        } else {
             bool_t ivar_6;
             ivar_6 = (bool_t)stringutils__is_backslash((uint8_t)ivar_1);
             if (ivar_6){
           result = (uint8_t)92;
             } else {
           bool_t ivar_10;
           ivar_10 = (bool_t)stringutils__is_slash((uint8_t)ivar_1);
           if (ivar_10){
           result = (uint8_t)47;
           } else {
           bool_t ivar_14;
           ivar_14 = (bool_t)stringutils__is_b((uint8_t)ivar_1);
           if (ivar_14){
            result = (uint8_t)8;
           } else {
            bool_t ivar_18;
            ivar_18 = (bool_t)stringutils__is_t((uint8_t)ivar_1);
            if (ivar_18){
             result = (uint8_t)9;
            } else {
             bool_t ivar_22;
             ivar_22 = (bool_t)stringutils__is_n((uint8_t)ivar_1);
             if (ivar_22){
              result = (uint8_t)10;
             } else {
              bool_t ivar_26;
              ivar_26 = (bool_t)stringutils__is_f((uint8_t)ivar_1);
              if (ivar_26){
               result = (uint8_t)12;
              } else {
               bool_t ivar_30;
               ivar_30 = (bool_t)stringutils__is_r((uint8_t)ivar_1);
               if (ivar_30){
                result = (uint8_t)13;
               } else {
                result = (uint8_t)0;};};};};};};};};
        
        
        return result;
}

bytestrings__bytestring_t stringutils__escape_char(uint8_t ivar_1){
        bytestrings__bytestring_t  result;

        bool_t ivar_2;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)34;
        ivar_2 = (ivar_1 == ivar_4);
        if (ivar_2){
             uint32_t ivar_6;
             ivar_6 = (uint32_t)2;
             stringutils_array_0_t ivar_10;
             uint8_t ivar_8;
             ivar_8 = (uint8_t)92;
             uint8_t ivar_9;
             ivar_9 = (uint8_t)34;
             ivar_10 = (stringutils_array_0_t)new_stringutils_array_0(2);
             ivar_10->elems[0]= ivar_8;
             ivar_10->elems[1]= ivar_9;
             stringutils_record_1_t tmp32317 = new_stringutils_record_1();;
             result = (bytestrings__bytestring_t)tmp32317;
             tmp32317->length = (uint32_t)ivar_6;
             tmp32317->seq = (stringutils_array_0_t)ivar_10;
        } else {
             bool_t ivar_11;
             uint8_t ivar_13;
             ivar_13 = (uint8_t)92;
             ivar_11 = (ivar_1 == ivar_13);
             if (ivar_11){
           uint32_t ivar_15;
           ivar_15 = (uint32_t)2;
           stringutils_array_0_t ivar_19;
           uint8_t ivar_17;
           ivar_17 = (uint8_t)92;
           uint8_t ivar_18;
           ivar_18 = (uint8_t)92;
           ivar_19 = (stringutils_array_0_t)new_stringutils_array_0(2);
           ivar_19->elems[0]= ivar_17;
           ivar_19->elems[1]= ivar_18;
           stringutils_record_1_t tmp32318 = new_stringutils_record_1();;
           result = (bytestrings__bytestring_t)tmp32318;
           tmp32318->length = (uint32_t)ivar_15;
           tmp32318->seq = (stringutils_array_0_t)ivar_19;
             } else {
           bool_t ivar_20;
           uint8_t ivar_22;
           ivar_22 = (uint8_t)8;
           ivar_20 = (ivar_1 == ivar_22);
           if (ivar_20){
           uint32_t ivar_24;
           ivar_24 = (uint32_t)2;
           stringutils_array_0_t ivar_28;
           uint8_t ivar_26;
           ivar_26 = (uint8_t)92;
           uint8_t ivar_27;
           ivar_27 = (uint8_t)98;
           ivar_28 = (stringutils_array_0_t)new_stringutils_array_0(2);
           ivar_28->elems[0]= ivar_26;
           ivar_28->elems[1]= ivar_27;
           stringutils_record_1_t tmp32319 = new_stringutils_record_1();;
           result = (bytestrings__bytestring_t)tmp32319;
           tmp32319->length = (uint32_t)ivar_24;
           tmp32319->seq = (stringutils_array_0_t)ivar_28;
           } else {
           bool_t ivar_29;
           uint8_t ivar_31;
           ivar_31 = (uint8_t)9;
           ivar_29 = (ivar_1 == ivar_31);
           if (ivar_29){
            uint32_t ivar_33;
            ivar_33 = (uint32_t)2;
            stringutils_array_0_t ivar_37;
            uint8_t ivar_35;
            ivar_35 = (uint8_t)92;
            uint8_t ivar_36;
            ivar_36 = (uint8_t)116;
            ivar_37 = (stringutils_array_0_t)new_stringutils_array_0(2);
            ivar_37->elems[0]= ivar_35;
            ivar_37->elems[1]= ivar_36;
            stringutils_record_1_t tmp32320 = new_stringutils_record_1();;
            result = (bytestrings__bytestring_t)tmp32320;
            tmp32320->length = (uint32_t)ivar_33;
            tmp32320->seq = (stringutils_array_0_t)ivar_37;
           } else {
            bool_t ivar_38;
            uint8_t ivar_40;
            ivar_40 = (uint8_t)10;
            ivar_38 = (ivar_1 == ivar_40);
            if (ivar_38){
             uint32_t ivar_42;
             ivar_42 = (uint32_t)2;
             stringutils_array_0_t ivar_46;
             uint8_t ivar_44;
             ivar_44 = (uint8_t)92;
             uint8_t ivar_45;
             ivar_45 = (uint8_t)110;
             ivar_46 = (stringutils_array_0_t)new_stringutils_array_0(2);
             ivar_46->elems[0]= ivar_44;
             ivar_46->elems[1]= ivar_45;
             stringutils_record_1_t tmp32321 = new_stringutils_record_1();;
             result = (bytestrings__bytestring_t)tmp32321;
             tmp32321->length = (uint32_t)ivar_42;
             tmp32321->seq = (stringutils_array_0_t)ivar_46;
            } else {
             bool_t ivar_47;
             uint8_t ivar_49;
             ivar_49 = (uint8_t)12;
             ivar_47 = (ivar_1 == ivar_49);
             if (ivar_47){
              uint32_t ivar_51;
              ivar_51 = (uint32_t)2;
              stringutils_array_0_t ivar_55;
              uint8_t ivar_53;
              ivar_53 = (uint8_t)92;
              uint8_t ivar_54;
              ivar_54 = (uint8_t)102;
              ivar_55 = (stringutils_array_0_t)new_stringutils_array_0(2);
              ivar_55->elems[0]= ivar_53;
              ivar_55->elems[1]= ivar_54;
              stringutils_record_1_t tmp32322 = new_stringutils_record_1();;
              result = (bytestrings__bytestring_t)tmp32322;
              tmp32322->length = (uint32_t)ivar_51;
              tmp32322->seq = (stringutils_array_0_t)ivar_55;
             } else {
              bool_t ivar_56;
              uint8_t ivar_58;
              ivar_58 = (uint8_t)13;
              ivar_56 = (ivar_1 == ivar_58);
              if (ivar_56){
               uint32_t ivar_60;
               ivar_60 = (uint32_t)2;
               stringutils_array_0_t ivar_64;
               uint8_t ivar_62;
               ivar_62 = (uint8_t)92;
               uint8_t ivar_63;
               ivar_63 = (uint8_t)114;
               ivar_64 = (stringutils_array_0_t)new_stringutils_array_0(2);
               ivar_64->elems[0]= ivar_62;
               ivar_64->elems[1]= ivar_63;
               stringutils_record_1_t tmp32323 = new_stringutils_record_1();;
               result = (bytestrings__bytestring_t)tmp32323;
               tmp32323->length = (uint32_t)ivar_60;
               tmp32323->seq = (stringutils_array_0_t)ivar_64;
              } else {
               uint32_t ivar_65;
               ivar_65 = (uint32_t)1;
               stringutils_array_0_t ivar_67;
               ivar_67 = (stringutils_array_0_t)new_stringutils_array_0(1);
               ivar_67->elems[0]= ivar_1;
               stringutils_record_1_t tmp32324 = new_stringutils_record_1();;
               result = (bytestrings__bytestring_t)tmp32324;
               tmp32324->length = (uint32_t)ivar_65;
               tmp32324->seq = (stringutils_array_0_t)ivar_67;};};};};};};};
        
        
        return result;
}

bytestrings__bytestring_t stringutils__escape_string_inner(bytestrings__bytestring_t ivar_1, uint32_t ivar_2, bytestrings__bytestring_t ivar_4){
        bytestrings__bytestring_t  result;

        bool_t ivar_5;
        uint32_t ivar_7;
        ivar_7 = (uint32_t)ivar_1->length;
        ivar_5 = (ivar_2 >= ivar_7);
        if (ivar_5){
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
             //copying to bytestrings__bytestring from bytestrings__bytestring;
             result = (bytestrings__bytestring_t)ivar_4;
             if (result != NULL) result->count++;
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_4);
        } else {
             uint32_t ivar_32;
             uint8_t ivar_14;
             ivar_14 = (uint8_t)1;
             ivar_32 = (uint32_t)(ivar_2 + ivar_14);
             bytestrings__bytestring_t ivar_34;
             bytestrings__bytestring_t ivar_29;
             uint8_t ivar_26;
             ivar_1->count++;
             ivar_26 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_2);
             ivar_29 = (bytestrings__bytestring_t)stringutils__escape_char((uint8_t)ivar_26);
             ivar_34 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_4, (bytestrings__bytestring_t)ivar_29);
             result = (bytestrings__bytestring_t)stringutils__escape_string_inner((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_32, (bytestrings__bytestring_t)ivar_34);};
        
        
        return result;
}

bytestrings__bytestring_t stringutils__escape_string(bytestrings__bytestring_t ivar_1){
        bytestrings__bytestring_t  result;

        uint8_t ivar_15;
        ivar_15 = (uint8_t)0;
        uint32_t ivar_11;
        //copying to uint32 from uint8;
        ivar_11 = (uint32_t)ivar_15;
        bytestrings__bytestring_t ivar_13;
        strings__string_t ivar_8;
        uint32_t len32328 = 0;
        uint32_t characters32329[0] = {};
        stringliteral_t string32327 = mk_string(0, characters32329);
        ivar_8 = (strings__string_t)strings__make_string(len32328, string32327);
        ivar_13 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_8);
        result = (bytestrings__bytestring_t)stringutils__escape_string_inner((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_11, (bytestrings__bytestring_t)ivar_13);
        
        
        return result;
}

bool_t stringutils__escape_string_test_empty(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32335 = 0;
        uint32_t characters32336[0] = {};
        stringliteral_t string32334 = mk_string(0, characters32336);
        ivar_7 = (strings__string_t)strings__make_string(len32335, string32334);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32338 = 0;
        uint32_t characters32339[0] = {};
        stringliteral_t string32337 = mk_string(0, characters32339);
        ivar_13 = (strings__string_t)strings__make_string(len32338, string32337);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_no_escape(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32345 = 5;
        uint32_t characters32346[5] = {104, 101, 108, 108, 111};
        stringliteral_t string32344 = mk_string(5, characters32346);
        ivar_7 = (strings__string_t)strings__make_string(len32345, string32344);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32348 = 5;
        uint32_t characters32349[5] = {104, 101, 108, 108, 111};
        stringliteral_t string32347 = mk_string(5, characters32349);
        ivar_13 = (strings__string_t)strings__make_string(len32348, string32347);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_quote(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 34);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32360 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32360;
        tmp32360->length = (uint8_t)ivar_4;
        tmp32360->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32361;
         //copying to uint32 from uint32;
         tmp32361 = (uint32_t)length3935;
         tmp32361 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32361);
         for (uint32_t index_31 = 0; index_31 < tmp32361; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32363 = 0;
        uint32_t characters32364[0] = {};
        stringliteral_t string32362 = mk_string(0, characters32364);
        ivar_18 = (strings__string_t)strings__make_string(len32363, string32362);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 34);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32365 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32365;
        tmp32365->length = (uint8_t)ivar_19;
        tmp32365->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32366;
         //copying to uint32 from uint32;
         tmp32366 = (uint32_t)length3935;
         tmp32366 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32366);
         for (uint32_t index_32 = 0; index_32 < tmp32366; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_backslash(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 92);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32377 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32377;
        tmp32377->length = (uint8_t)ivar_4;
        tmp32377->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32378;
         //copying to uint32 from uint32;
         tmp32378 = (uint32_t)length3935;
         tmp32378 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32378);
         for (uint32_t index_31 = 0; index_31 < tmp32378; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32380 = 0;
        uint32_t characters32381[0] = {};
        stringliteral_t string32379 = mk_string(0, characters32381);
        ivar_18 = (strings__string_t)strings__make_string(len32380, string32379);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 92);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32382 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32382;
        tmp32382->length = (uint8_t)ivar_19;
        tmp32382->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32383;
         //copying to uint32 from uint32;
         tmp32383 = (uint32_t)length3935;
         tmp32383 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32383);
         for (uint32_t index_32 = 0; index_32 < tmp32383; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_backspace(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 8);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32394 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32394;
        tmp32394->length = (uint8_t)ivar_4;
        tmp32394->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32395;
         //copying to uint32 from uint32;
         tmp32395 = (uint32_t)length3935;
         tmp32395 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32395);
         for (uint32_t index_31 = 0; index_31 < tmp32395; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32397 = 0;
        uint32_t characters32398[0] = {};
        stringliteral_t string32396 = mk_string(0, characters32398);
        ivar_18 = (strings__string_t)strings__make_string(len32397, string32396);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 98);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32399 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32399;
        tmp32399->length = (uint8_t)ivar_19;
        tmp32399->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32400;
         //copying to uint32 from uint32;
         tmp32400 = (uint32_t)length3935;
         tmp32400 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32400);
         for (uint32_t index_32 = 0; index_32 < tmp32400; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_tab(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 9);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32411 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32411;
        tmp32411->length = (uint8_t)ivar_4;
        tmp32411->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32412;
         //copying to uint32 from uint32;
         tmp32412 = (uint32_t)length3935;
         tmp32412 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32412);
         for (uint32_t index_31 = 0; index_31 < tmp32412; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32414 = 0;
        uint32_t characters32415[0] = {};
        stringliteral_t string32413 = mk_string(0, characters32415);
        ivar_18 = (strings__string_t)strings__make_string(len32414, string32413);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 116);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32416 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32416;
        tmp32416->length = (uint8_t)ivar_19;
        tmp32416->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32417;
         //copying to uint32 from uint32;
         tmp32417 = (uint32_t)length3935;
         tmp32417 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32417);
         for (uint32_t index_32 = 0; index_32 < tmp32417; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_newline(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 10);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32428 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32428;
        tmp32428->length = (uint8_t)ivar_4;
        tmp32428->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32429;
         //copying to uint32 from uint32;
         tmp32429 = (uint32_t)length3935;
         tmp32429 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32429);
         for (uint32_t index_31 = 0; index_31 < tmp32429; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32431 = 0;
        uint32_t characters32432[0] = {};
        stringliteral_t string32430 = mk_string(0, characters32432);
        ivar_18 = (strings__string_t)strings__make_string(len32431, string32430);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 110);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32433 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32433;
        tmp32433->length = (uint8_t)ivar_19;
        tmp32433->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32434;
         //copying to uint32 from uint32;
         tmp32434 = (uint32_t)length3935;
         tmp32434 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32434);
         for (uint32_t index_32 = 0; index_32 < tmp32434; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_formfeed(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 12);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32445 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32445;
        tmp32445->length = (uint8_t)ivar_4;
        tmp32445->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32446;
         //copying to uint32 from uint32;
         tmp32446 = (uint32_t)length3935;
         tmp32446 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32446);
         for (uint32_t index_31 = 0; index_31 < tmp32446; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32448 = 0;
        uint32_t characters32449[0] = {};
        stringliteral_t string32447 = mk_string(0, characters32449);
        ivar_18 = (strings__string_t)strings__make_string(len32448, string32447);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 102);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32450 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32450;
        tmp32450->length = (uint8_t)ivar_19;
        tmp32450->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32451;
         //copying to uint32 from uint32;
         tmp32451 = (uint32_t)length3935;
         tmp32451 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32451);
         for (uint32_t index_32 = 0; index_32 < tmp32451; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_carriage_return(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_12;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)1;
        stringutils_array_2_t ivar_7;
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 13);
        ivar_7 = (stringutils_array_2_t)new_stringutils_array_2(1);
        ivar_7->elems[0]= ivar_6;
        stringutils_record_3_t tmp32462 = new_stringutils_record_3();;
        ivar_12 = (stringutils_record_3_t)tmp32462;
        tmp32462->length = (uint8_t)ivar_4;
        tmp32462->seq = (stringutils_array_2_t)ivar_7;
        bytestrings__bytestring_t ivar_10;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_10 = new_stringutils_record_1();
         ivar_10->length = (uint32_t)ivar_12->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_10->length;
         uint32_t tmp32463;
         //copying to uint32 from uint32;
         tmp32463 = (uint32_t)length3935;
         tmp32463 += 0;
         ivar_10->seq = new_stringutils_array_0(tmp32463);
         for (uint32_t index_31 = 0; index_31 < tmp32463; index_31++){
                 ivar_10->seq->elems[index_31] = (uint8_t)mpq_get_ui(ivar_12->seq->elems[index_31]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_10->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_12);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_10);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_26;
        strings__string_t ivar_18;
        uint32_t len32465 = 0;
        uint32_t characters32466[0] = {};
        stringliteral_t string32464 = mk_string(0, characters32466);
        ivar_18 = (strings__string_t)strings__make_string(len32465, string32464);
        ivar_26 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_18);
        stringutils_record_3_t ivar_29;
        uint8_t ivar_19;
        ivar_19 = (uint8_t)2;
        stringutils_array_2_t ivar_23;
        mpq_ptr_t ivar_21;
        ivar_21 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_21);
        mpq_mk_set_ui(ivar_21, 92);
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 114);
        ivar_23 = (stringutils_array_2_t)new_stringutils_array_2(2);
        ivar_23->elems[0]= ivar_21;
        ivar_23->elems[1]= ivar_22;
        stringutils_record_3_t tmp32467 = new_stringutils_record_3();;
        ivar_29 = (stringutils_record_3_t)tmp32467;
        tmp32467->length = (uint8_t)ivar_19;
        tmp32467->seq = (stringutils_array_2_t)ivar_23;
        bytestrings__bytestring_t ivar_27;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_27 = new_stringutils_record_1();
         ivar_27->length = (uint32_t)ivar_29->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_27->length;
         uint32_t tmp32468;
         //copying to uint32 from uint32;
         tmp32468 = (uint32_t)length3935;
         tmp32468 += 0;
         ivar_27->seq = new_stringutils_array_0(tmp32468);
         for (uint32_t index_32 = 0; index_32 < tmp32468; index_32++){
                 ivar_27->seq->elems[index_32] = (uint8_t)mpq_get_ui(ivar_29->seq->elems[index_32]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_27->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_29);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_26, (bytestrings__bytestring_t)ivar_27);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_mixed_string(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_14;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)5;
        stringutils_array_2_t ivar_10;
        mpq_ptr_t ivar_5;
        ivar_5 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_5);
        mpq_mk_set_ui(ivar_5, 104);
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 105);
        mpq_ptr_t ivar_7;
        ivar_7 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_7);
        mpq_mk_set_ui(ivar_7, 10);
        mpq_ptr_t ivar_8;
        ivar_8 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_8);
        mpq_mk_set_ui(ivar_8, 92);
        mpq_ptr_t ivar_9;
        ivar_9 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_9);
        mpq_mk_set_ui(ivar_9, 34);
        ivar_10 = (stringutils_array_2_t)new_stringutils_array_2(5);
        ivar_10->elems[0]= ivar_5;
        ivar_10->elems[1]= ivar_6;
        ivar_10->elems[2]= ivar_7;
        ivar_10->elems[3]= ivar_8;
        ivar_10->elems[4]= ivar_9;
        stringutils_record_3_t tmp32479 = new_stringutils_record_3();;
        ivar_14 = (stringutils_record_3_t)tmp32479;
        tmp32479->length = (uint8_t)ivar_4;
        tmp32479->seq = (stringutils_array_2_t)ivar_10;
        bytestrings__bytestring_t ivar_12;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_12 = new_stringutils_record_1();
         ivar_12->length = (uint32_t)ivar_14->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_12->length;
         uint32_t tmp32480;
         //copying to uint32 from uint32;
         tmp32480 = (uint32_t)length3935;
         tmp32480 += 0;
         ivar_12->seq = new_stringutils_array_0(tmp32480);
         for (uint32_t index_37 = 0; index_37 < tmp32480; index_37++){
                 ivar_12->seq->elems[index_37] = (uint8_t)mpq_get_ui(ivar_14->seq->elems[index_37]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_12->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_14);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_12);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_32;
        strings__string_t ivar_20;
        uint32_t len32482 = 0;
        uint32_t characters32483[0] = {};
        stringliteral_t string32481 = mk_string(0, characters32483);
        ivar_20 = (strings__string_t)strings__make_string(len32482, string32481);
        ivar_32 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_20);
        stringutils_record_3_t ivar_35;
        uint8_t ivar_21;
        ivar_21 = (uint8_t)8;
        stringutils_array_2_t ivar_30;
        mpq_ptr_t ivar_22;
        ivar_22 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_22);
        mpq_mk_set_ui(ivar_22, 104);
        mpq_ptr_t ivar_23;
        ivar_23 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_23);
        mpq_mk_set_ui(ivar_23, 105);
        mpq_ptr_t ivar_24;
        ivar_24 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_24);
        mpq_mk_set_ui(ivar_24, 92);
        mpq_ptr_t ivar_25;
        ivar_25 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_25);
        mpq_mk_set_ui(ivar_25, 110);
        mpq_ptr_t ivar_26;
        ivar_26 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_26);
        mpq_mk_set_ui(ivar_26, 92);
        mpq_ptr_t ivar_27;
        ivar_27 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_27);
        mpq_mk_set_ui(ivar_27, 92);
        mpq_ptr_t ivar_28;
        ivar_28 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_28);
        mpq_mk_set_ui(ivar_28, 92);
        mpq_ptr_t ivar_29;
        ivar_29 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_29);
        mpq_mk_set_ui(ivar_29, 34);
        ivar_30 = (stringutils_array_2_t)new_stringutils_array_2(8);
        ivar_30->elems[0]= ivar_22;
        ivar_30->elems[1]= ivar_23;
        ivar_30->elems[2]= ivar_24;
        ivar_30->elems[3]= ivar_25;
        ivar_30->elems[4]= ivar_26;
        ivar_30->elems[5]= ivar_27;
        ivar_30->elems[6]= ivar_28;
        ivar_30->elems[7]= ivar_29;
        stringutils_record_3_t tmp32484 = new_stringutils_record_3();;
        ivar_35 = (stringutils_record_3_t)tmp32484;
        tmp32484->length = (uint8_t)ivar_21;
        tmp32484->seq = (stringutils_array_2_t)ivar_30;
        bytestrings__bytestring_t ivar_33;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_33 = new_stringutils_record_1();
         ivar_33->length = (uint32_t)ivar_35->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_33->length;
         uint32_t tmp32485;
         //copying to uint32 from uint32;
         tmp32485 = (uint32_t)length3935;
         tmp32485 += 0;
         ivar_33->seq = new_stringutils_array_0(tmp32485);
         for (uint32_t index_38 = 0; index_38 < tmp32485; index_38++){
                 ivar_33->seq->elems[index_38] = (uint8_t)mpq_get_ui(ivar_35->seq->elems[index_38]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_33->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_35);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_32, (bytestrings__bytestring_t)ivar_33);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__escape_string_test_all_special_chars(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        stringutils_record_3_t ivar_16;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)7;
        stringutils_array_2_t ivar_12;
        mpq_ptr_t ivar_5;
        ivar_5 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_5);
        mpq_mk_set_ui(ivar_5, 34);
        mpq_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_6);
        mpq_mk_set_ui(ivar_6, 8);
        mpq_ptr_t ivar_7;
        ivar_7 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_7);
        mpq_mk_set_ui(ivar_7, 9);
        mpq_ptr_t ivar_8;
        ivar_8 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_8);
        mpq_mk_set_ui(ivar_8, 10);
        mpq_ptr_t ivar_9;
        ivar_9 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_9);
        mpq_mk_set_ui(ivar_9, 12);
        mpq_ptr_t ivar_10;
        ivar_10 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_10);
        mpq_mk_set_ui(ivar_10, 13);
        mpq_ptr_t ivar_11;
        ivar_11 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_11);
        mpq_mk_set_ui(ivar_11, 92);
        ivar_12 = (stringutils_array_2_t)new_stringutils_array_2(7);
        ivar_12->elems[0]= ivar_5;
        ivar_12->elems[1]= ivar_6;
        ivar_12->elems[2]= ivar_7;
        ivar_12->elems[3]= ivar_8;
        ivar_12->elems[4]= ivar_9;
        ivar_12->elems[5]= ivar_10;
        ivar_12->elems[6]= ivar_11;
        stringutils_record_3_t tmp32496 = new_stringutils_record_3();;
        ivar_16 = (stringutils_record_3_t)tmp32496;
        tmp32496->length = (uint8_t)ivar_4;
        tmp32496->seq = (stringutils_array_2_t)ivar_12;
        bytestrings__bytestring_t ivar_14;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_14 = new_stringutils_record_1();
         ivar_14->length = (uint32_t)ivar_16->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_14->length;
         uint32_t tmp32497;
         //copying to uint32 from uint32;
         tmp32497 = (uint32_t)length3935;
         tmp32497 += 0;
         ivar_14->seq = new_stringutils_array_0(tmp32497);
         for (uint32_t index_47 = 0; index_47 < tmp32497; index_47++){
                 ivar_14->seq->elems[index_47] = (uint8_t)mpq_get_ui(ivar_16->seq->elems[index_47]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_14->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_16);
        ivar_1 = (bytestrings__bytestring_t)stringutils__escape_string((bytestrings__bytestring_t)ivar_14);
        bytestrings__bytestring_t ivar_2;
        bytestrings__bytestring_t ivar_42;
        strings__string_t ivar_22;
        uint32_t len32499 = 0;
        uint32_t characters32500[0] = {};
        stringliteral_t string32498 = mk_string(0, characters32500);
        ivar_22 = (strings__string_t)strings__make_string(len32499, string32498);
        ivar_42 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_22);
        stringutils_record_3_t ivar_45;
        uint8_t ivar_23;
        ivar_23 = (uint8_t)14;
        stringutils_array_2_t ivar_39;
        mpq_ptr_t ivar_25;
        ivar_25 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_25);
        mpq_mk_set_ui(ivar_25, 92);
        mpq_ptr_t ivar_26;
        ivar_26 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_26);
        mpq_mk_set_ui(ivar_26, 34);
        mpq_ptr_t ivar_27;
        ivar_27 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_27);
        mpq_mk_set_ui(ivar_27, 92);
        mpq_ptr_t ivar_28;
        ivar_28 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_28);
        mpq_mk_set_ui(ivar_28, 98);
        mpq_ptr_t ivar_29;
        ivar_29 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_29);
        mpq_mk_set_ui(ivar_29, 92);
        mpq_ptr_t ivar_30;
        ivar_30 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_30);
        mpq_mk_set_ui(ivar_30, 116);
        mpq_ptr_t ivar_31;
        ivar_31 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_31);
        mpq_mk_set_ui(ivar_31, 92);
        mpq_ptr_t ivar_32;
        ivar_32 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_32);
        mpq_mk_set_ui(ivar_32, 110);
        mpq_ptr_t ivar_33;
        ivar_33 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_33);
        mpq_mk_set_ui(ivar_33, 92);
        mpq_ptr_t ivar_34;
        ivar_34 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_34);
        mpq_mk_set_ui(ivar_34, 102);
        mpq_ptr_t ivar_35;
        ivar_35 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_35);
        mpq_mk_set_ui(ivar_35, 92);
        mpq_ptr_t ivar_36;
        ivar_36 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_36);
        mpq_mk_set_ui(ivar_36, 114);
        mpq_ptr_t ivar_37;
        ivar_37 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_37);
        mpq_mk_set_ui(ivar_37, 92);
        mpq_ptr_t ivar_38;
        ivar_38 = safe_malloc(sizeof(mpq_t));
        mpq_init(ivar_38);
        mpq_mk_set_ui(ivar_38, 92);
        ivar_39 = (stringutils_array_2_t)new_stringutils_array_2(14);
        ivar_39->elems[0]= ivar_25;
        ivar_39->elems[1]= ivar_26;
        ivar_39->elems[2]= ivar_27;
        ivar_39->elems[3]= ivar_28;
        ivar_39->elems[4]= ivar_29;
        ivar_39->elems[5]= ivar_30;
        ivar_39->elems[6]= ivar_31;
        ivar_39->elems[7]= ivar_32;
        ivar_39->elems[8]= ivar_33;
        ivar_39->elems[9]= ivar_34;
        ivar_39->elems[10]= ivar_35;
        ivar_39->elems[11]= ivar_36;
        ivar_39->elems[12]= ivar_37;
        ivar_39->elems[13]= ivar_38;
        stringutils_record_3_t tmp32501 = new_stringutils_record_3();;
        ivar_45 = (stringutils_record_3_t)tmp32501;
        tmp32501->length = (uint8_t)ivar_23;
        tmp32501->seq = (stringutils_array_2_t)ivar_39;
        bytestrings__bytestring_t ivar_43;
        //copying to bytestrings__bytestring from stringutils_record_3;
        {

         ivar_43 = new_stringutils_record_1();
         ivar_43->length = (uint32_t)ivar_45->length;
         uint32_t length3935;
         length3935 = (uint32_t)ivar_43->length;
         uint32_t tmp32502;
         //copying to uint32 from uint32;
         tmp32502 = (uint32_t)length3935;
         tmp32502 += 0;
         ivar_43->seq = new_stringutils_array_0(tmp32502);
         for (uint32_t index_48 = 0; index_48 < tmp32502; index_48++){
                 ivar_43->seq->elems[index_48] = (uint8_t)mpq_get_ui(ivar_45->seq->elems[index_48]);
         };
         stringutils_array_0_t seq3936;
         seq3936 = (stringutils_array_0_t)ivar_43->seq; };
        release_stringutils_record_3((stringutils_record_3_t)ivar_45);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_42, (bytestrings__bytestring_t)ivar_43);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

uint32_t stringutils__first_printable_inner(bytestrings__bytestring_t ivar_1, uint32_t ivar_2){
        uint32_t  result;

        bool_t ivar_9;
        uint32_t ivar_11;
        ivar_11 = (uint32_t)ivar_1->length;
        ivar_9 = (ivar_2 == ivar_11);
        if (ivar_9){
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
             //copying to uint32 from uint32;
             result = (uint32_t)ivar_2;
        } else {
             bool_t ivar_14;
             bool_t ivar_15;
             uint8_t ivar_24;
             ivar_1->count++;
             ivar_24 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_2);
             ivar_15 = (bool_t)stringutils__whitespace((uint8_t)ivar_24);
             ivar_14 = !ivar_15;
             if (ivar_14){
           release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
           //copying to uint32 from uint32;
           result = (uint32_t)ivar_2;
             } else {
           uint32_t ivar_33;
           uint8_t ivar_29;
           ivar_29 = (uint8_t)1;
           ivar_33 = (uint32_t)(ivar_2 + ivar_29);
           result = (uint32_t)stringutils__first_printable_inner((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_33);};};
        
        
        return result;
}

uint32_t stringutils__first_printable(bytestrings__bytestring_t ivar_1){
        uint32_t  result;

        uint8_t ivar_12;
        ivar_12 = (uint8_t)0;
        uint32_t ivar_8;
        //copying to uint32 from uint8;
        ivar_8 = (uint32_t)ivar_12;
        result = (uint32_t)stringutils__first_printable_inner((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_8);
        
        
        return result;
}

uint32_t stringutils__last_printable_inner(bytestrings__bytestring_t ivar_1, uint32_t ivar_2){
        uint32_t  result;

        bool_t ivar_9;
        uint8_t ivar_11;
        ivar_11 = (uint8_t)0;
        ivar_9 = (ivar_2 == ivar_11);
        if (ivar_9){
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
             result = (uint32_t)0;
        } else {
             bool_t ivar_13;
             bool_t ivar_14;
             uint8_t ivar_28;
             int32_t ivar_26;
             uint8_t ivar_19;
             ivar_19 = (uint8_t)1;
             ivar_26 = (int32_t)((uint64_t)ivar_2 - (uint64_t)ivar_19);
             uint32_t ivar_23;
             //copying to uint32 from int32;
             ivar_23 = (uint32_t)ivar_26;
             ivar_1->count++;
             ivar_28 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_23);
             ivar_14 = (bool_t)stringutils__whitespace((uint8_t)ivar_28);
             ivar_13 = !ivar_14;
             if (ivar_13){
           release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
           //copying to uint32 from uint32;
           result = (uint32_t)ivar_2;
             } else {
           int32_t ivar_41;
           uint8_t ivar_33;
           ivar_33 = (uint8_t)1;
           ivar_41 = (int32_t)((uint64_t)ivar_2 - (uint64_t)ivar_33);
           uint32_t ivar_37;
           //copying to uint32 from int32;
           ivar_37 = (uint32_t)ivar_41;
           result = (uint32_t)stringutils__last_printable_inner((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_37);};};
        
        
        return result;
}

uint32_t stringutils__last_printable(bytestrings__bytestring_t ivar_1){
        uint32_t  result;

        bool_t ivar_4;
        uint32_t ivar_5;
        ivar_5 = (uint32_t)ivar_1->length;
        uint8_t ivar_6;
        ivar_6 = (uint8_t)0;
        ivar_4 = (ivar_5 == ivar_6);
        if (ivar_4){
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
             result = (uint32_t)0;
        } else {
             uint32_t ivar_14;
             ivar_14 = (uint32_t)ivar_1->length;
             result = (uint32_t)stringutils__last_printable_inner((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_14);};
        
        
        return result;
}

bytestrings__bytestring_t stringutils__trim_str(bytestrings__bytestring_t ivar_1){
        bytestrings__bytestring_t  result;

        /* start_pos */ uint32_t ivar_2;
        ivar_1->count++;
        ivar_2 = (uint32_t)stringutils__first_printable((bytestrings__bytestring_t)ivar_1);
        /* end_pos */ uint32_t ivar_10;
        ivar_1->count++;
        ivar_10 = (uint32_t)stringutils__last_printable((bytestrings__bytestring_t)ivar_1);
        bool_t ivar_18;
        uint32_t ivar_19;
        ivar_19 = (uint32_t)ivar_1->length;
        uint8_t ivar_20;
        ivar_20 = (uint8_t)1;
        ivar_18 = (ivar_19 < ivar_20);
        if (ivar_18){
             //copying to bytestrings__bytestring from bytestrings__bytestring;
             result = (bytestrings__bytestring_t)ivar_1;
             if (result != NULL) result->count++;
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
        } else {
             result = (bytestrings__bytestring_t)bytestrings__substr((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_2, (uint32_t)ivar_10);};
        
        
        return result;
}

bool_t stringutils__trim_str_test0(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32508 = 5;
        uint32_t characters32509[5] = {32, 102, 111, 111, 32};
        stringliteral_t string32507 = mk_string(5, characters32509);
        ivar_7 = (strings__string_t)strings__make_string(len32508, string32507);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32511 = 3;
        uint32_t characters32512[3] = {102, 111, 111};
        stringliteral_t string32510 = mk_string(3, characters32512);
        ivar_13 = (strings__string_t)strings__make_string(len32511, string32510);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__trim_str_test1(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32518 = 1;
        uint32_t characters32519[1] = {32};
        stringliteral_t string32517 = mk_string(1, characters32519);
        ivar_7 = (strings__string_t)strings__make_string(len32518, string32517);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32521 = 0;
        uint32_t characters32522[0] = {};
        stringliteral_t string32520 = mk_string(0, characters32522);
        ivar_13 = (strings__string_t)strings__make_string(len32521, string32520);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__trim_str_test2(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32528 = 6;
        uint32_t characters32529[6] = {102, 32, 111, 32, 111, 32};
        stringliteral_t string32527 = mk_string(6, characters32529);
        ivar_7 = (strings__string_t)strings__make_string(len32528, string32527);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32531 = 5;
        uint32_t characters32532[5] = {102, 32, 111, 32, 111};
        stringliteral_t string32530 = mk_string(5, characters32532);
        ivar_13 = (strings__string_t)strings__make_string(len32531, string32530);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__trim_str_test3(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32538 = 0;
        uint32_t characters32539[0] = {};
        stringliteral_t string32537 = mk_string(0, characters32539);
        ivar_7 = (strings__string_t)strings__make_string(len32538, string32537);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32541 = 0;
        uint32_t characters32542[0] = {};
        stringliteral_t string32540 = mk_string(0, characters32542);
        ivar_13 = (strings__string_t)strings__make_string(len32541, string32540);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__trim_str_test4(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32548 = 4;
        uint32_t characters32549[4] = {32, 102, 111, 111};
        stringliteral_t string32547 = mk_string(4, characters32549);
        ivar_7 = (strings__string_t)strings__make_string(len32548, string32547);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32551 = 3;
        uint32_t characters32552[3] = {102, 111, 111};
        stringliteral_t string32550 = mk_string(3, characters32552);
        ivar_13 = (strings__string_t)strings__make_string(len32551, string32550);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__trim_str_test5(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32558 = 3;
        uint32_t characters32559[3] = {102, 111, 111};
        stringliteral_t string32557 = mk_string(3, characters32559);
        ivar_7 = (strings__string_t)strings__make_string(len32558, string32557);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32561 = 3;
        uint32_t characters32562[3] = {102, 111, 111};
        stringliteral_t string32560 = mk_string(3, characters32562);
        ivar_13 = (strings__string_t)strings__make_string(len32561, string32560);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__trim_str_test6(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_9;
        strings__string_t ivar_7;
        uint32_t len32568 = 1;
        uint32_t characters32569[1] = {49};
        stringliteral_t string32567 = mk_string(1, characters32569);
        ivar_7 = (strings__string_t)strings__make_string(len32568, string32567);
        ivar_9 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_7);
        ivar_1 = (bytestrings__bytestring_t)stringutils__trim_str((bytestrings__bytestring_t)ivar_9);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_13;
        uint32_t len32571 = 1;
        uint32_t characters32572[1] = {49};
        stringliteral_t string32570 = mk_string(1, characters32572);
        ivar_13 = (strings__string_t)strings__make_string(len32571, string32570);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_13);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bytestrings__bytestring_t stringutils__join_inner(bytestrings__bytestring_t ivar_1, stringutils_record_5_t ivar_2, uint32_t ivar_3, bytestrings__bytestring_t ivar_4){
        bytestrings__bytestring_t  result;

        bool_t ivar_5;
        uint32_t ivar_7;
        ivar_7 = (uint32_t)ivar_2->length;
        ivar_5 = (ivar_3 >= ivar_7);
        if (ivar_5){
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_1);
             release_stringutils_record_5((stringutils_record_5_t)ivar_2);
             //copying to bytestrings__bytestring from bytestrings__bytestring;
             result = (bytestrings__bytestring_t)ivar_4;
             if (result != NULL) result->count++;
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_4);
        } else {
             bool_t ivar_10;
             uint8_t ivar_12;
             ivar_12 = (uint8_t)0;
             ivar_10 = (ivar_3 == ivar_12);
             if (ivar_10){
           release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_4);
           uint32_t ivar_33;
           uint8_t ivar_19;
           ivar_19 = (uint8_t)1;
           ivar_33 = (uint32_t)(ivar_3 + ivar_19);
           bytestrings__bytestring_t ivar_34;
           stringutils_array_4_t ivar_23;
           stringutils_array_4_t ivar_28;
           ivar_28 = (stringutils_array_4_t)ivar_2->seq;
           ivar_28->count++;
           //copying to stringutils_array_4 from stringutils_array_4;
           ivar_23 = (stringutils_array_4_t)ivar_28;
           if (ivar_23 != NULL) ivar_23->count++;
           release_stringutils_array_4((stringutils_array_4_t)ivar_28);
           ivar_34 = (bytestrings__bytestring_t)ivar_23->elems[ivar_3];
           ivar_34->count++;
           release_stringutils_array_4((stringutils_array_4_t)ivar_23);
           result = (bytestrings__bytestring_t)stringutils__join_inner((bytestrings__bytestring_t)ivar_1, (stringutils_record_5_t)ivar_2, (uint32_t)ivar_33, (bytestrings__bytestring_t)ivar_34);
             } else {
           uint32_t ivar_64;
           uint8_t ivar_40;
           ivar_40 = (uint8_t)1;
           ivar_64 = (uint32_t)(ivar_3 + ivar_40);
           bytestrings__bytestring_t ivar_65;
           bytestrings__bytestring_t ivar_59;
           ivar_1->count++;
           ivar_59 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_4, (bytestrings__bytestring_t)ivar_1);
           bytestrings__bytestring_t ivar_60;
           stringutils_array_4_t ivar_51;
           stringutils_array_4_t ivar_56;
           ivar_56 = (stringutils_array_4_t)ivar_2->seq;
           ivar_56->count++;
           //copying to stringutils_array_4 from stringutils_array_4;
           ivar_51 = (stringutils_array_4_t)ivar_56;
           if (ivar_51 != NULL) ivar_51->count++;
           release_stringutils_array_4((stringutils_array_4_t)ivar_56);
           ivar_60 = (bytestrings__bytestring_t)ivar_51->elems[ivar_3];
           ivar_60->count++;
           release_stringutils_array_4((stringutils_array_4_t)ivar_51);
           ivar_65 = (bytestrings__bytestring_t)bytestrings__doubleplus((bytestrings__bytestring_t)ivar_59, (bytestrings__bytestring_t)ivar_60);
           result = (bytestrings__bytestring_t)stringutils__join_inner((bytestrings__bytestring_t)ivar_1, (stringutils_record_5_t)ivar_2, (uint32_t)ivar_64, (bytestrings__bytestring_t)ivar_65);};};
        
        
        return result;
}

bytestrings__bytestring_t stringutils__join(bytestrings__bytestring_t ivar_1, stringutils_record_5_t ivar_2){
        bytestrings__bytestring_t  result;

        uint8_t ivar_17;
        ivar_17 = (uint8_t)0;
        uint32_t ivar_14;
        //copying to uint32 from uint8;
        ivar_14 = (uint32_t)ivar_17;
        bytestrings__bytestring_t ivar_15;
        strings__string_t ivar_10;
        uint32_t len32600 = 0;
        uint32_t characters32601[0] = {};
        stringliteral_t string32599 = mk_string(0, characters32601);
        ivar_10 = (strings__string_t)strings__make_string(len32600, string32599);
        ivar_15 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_10);
        result = (bytestrings__bytestring_t)stringutils__join_inner((bytestrings__bytestring_t)ivar_1, (stringutils_record_5_t)ivar_2, (uint32_t)ivar_14, (bytestrings__bytestring_t)ivar_15);
        
        
        return result;
}

bool_t stringutils__join_test0(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        type_actual_t ivar_9;
        ivar_9 = (type_actual_t)actual_bytestrings__bytestring();
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_12;
        strings__string_t ivar_8;
        uint32_t len32613 = 1;
        uint32_t characters32614[1] = {44};
        stringliteral_t string32612 = mk_string(1, characters32614);
        ivar_8 = (strings__string_t)strings__make_string(len32613, string32612);
        ivar_12 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_8);
        stringutils_record_5_t ivar_13;
        ivar_13 = (stringutils_record_5_t)array_sequences__empty_aseq((type_actual_t)ivar_9);
        ivar_1 = (bytestrings__bytestring_t)stringutils__join((bytestrings__bytestring_t)ivar_12, (stringutils_record_5_t)ivar_13);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_17;
        uint32_t len32616 = 0;
        uint32_t characters32617[0] = {};
        stringliteral_t string32615 = mk_string(0, characters32617);
        ivar_17 = (strings__string_t)strings__make_string(len32616, string32615);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_17);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__join_test1(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_17;
        strings__string_t ivar_8;
        uint32_t len32631 = 1;
        uint32_t characters32632[1] = {44};
        stringliteral_t string32630 = mk_string(1, characters32632);
        ivar_8 = (strings__string_t)strings__make_string(len32631, string32630);
        ivar_17 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_8);
        stringutils_record_6_t ivar_20;
        uint8_t ivar_9;
        ivar_9 = (uint8_t)1;
        stringutils_array_4_t ivar_15;
        bytestrings__bytestring_t ivar_10;
        strings__string_t ivar_14;
        uint32_t len32634 = 1;
        uint32_t characters32635[1] = {97};
        stringliteral_t string32633 = mk_string(1, characters32635);
        ivar_14 = (strings__string_t)strings__make_string(len32634, string32633);
        ivar_10 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_14);
        ivar_15 = (stringutils_array_4_t)new_stringutils_array_4(1);
        ivar_15->elems[0]= ivar_10;
        stringutils_record_6_t tmp32636 = new_stringutils_record_6();;
        ivar_20 = (stringutils_record_6_t)tmp32636;
        tmp32636->length = (uint8_t)ivar_9;
        tmp32636->seq = (stringutils_array_4_t)ivar_15;
        stringutils_record_5_t ivar_18;
        //copying to stringutils_record_5 from stringutils_record_6;
        {

         ivar_18 = new_stringutils_record_5();
         ivar_18->length = (uint32_t)ivar_20->length;
         uint32_t length32626;
         length32626 = (uint32_t)ivar_18->length;
         ivar_18->seq = (stringutils_array_4_t)ivar_20->seq;
         if (ivar_18->seq != NULL) ivar_18->seq->count++;
         stringutils_array_4_t seq32627;
         seq32627 = (stringutils_array_4_t)ivar_18->seq; };
        release_stringutils_record_6((stringutils_record_6_t)ivar_20);
        ivar_1 = (bytestrings__bytestring_t)stringutils__join((bytestrings__bytestring_t)ivar_17, (stringutils_record_5_t)ivar_18);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_24;
        uint32_t len32638 = 1;
        uint32_t characters32639[1] = {97};
        stringliteral_t string32637 = mk_string(1, characters32639);
        ivar_24 = (strings__string_t)strings__make_string(len32638, string32637);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_24);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__join_test2(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_22;
        strings__string_t ivar_8;
        uint32_t len32655 = 1;
        uint32_t characters32656[1] = {44};
        stringliteral_t string32654 = mk_string(1, characters32656);
        ivar_8 = (strings__string_t)strings__make_string(len32655, string32654);
        ivar_22 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_8);
        stringutils_record_6_t ivar_25;
        uint8_t ivar_9;
        ivar_9 = (uint8_t)2;
        stringutils_array_4_t ivar_20;
        bytestrings__bytestring_t ivar_10;
        strings__string_t ivar_15;
        uint32_t len32658 = 1;
        uint32_t characters32659[1] = {97};
        stringliteral_t string32657 = mk_string(1, characters32659);
        ivar_15 = (strings__string_t)strings__make_string(len32658, string32657);
        ivar_10 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_15);
        bytestrings__bytestring_t ivar_11;
        strings__string_t ivar_19;
        uint32_t len32661 = 1;
        uint32_t characters32662[1] = {98};
        stringliteral_t string32660 = mk_string(1, characters32662);
        ivar_19 = (strings__string_t)strings__make_string(len32661, string32660);
        ivar_11 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_19);
        ivar_20 = (stringutils_array_4_t)new_stringutils_array_4(2);
        ivar_20->elems[0]= ivar_10;
        ivar_20->elems[1]= ivar_11;
        stringutils_record_6_t tmp32663 = new_stringutils_record_6();;
        ivar_25 = (stringutils_record_6_t)tmp32663;
        tmp32663->length = (uint8_t)ivar_9;
        tmp32663->seq = (stringutils_array_4_t)ivar_20;
        stringutils_record_5_t ivar_23;
        //copying to stringutils_record_5 from stringutils_record_6;
        {

         ivar_23 = new_stringutils_record_5();
         ivar_23->length = (uint32_t)ivar_25->length;
         uint32_t length32650;
         length32650 = (uint32_t)ivar_23->length;
         ivar_23->seq = (stringutils_array_4_t)ivar_25->seq;
         if (ivar_23->seq != NULL) ivar_23->seq->count++;
         stringutils_array_4_t seq32651;
         seq32651 = (stringutils_array_4_t)ivar_23->seq; };
        release_stringutils_record_6((stringutils_record_6_t)ivar_25);
        ivar_1 = (bytestrings__bytestring_t)stringutils__join((bytestrings__bytestring_t)ivar_22, (stringutils_record_5_t)ivar_23);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_29;
        uint32_t len32665 = 3;
        uint32_t characters32666[3] = {97, 44, 98};
        stringliteral_t string32664 = mk_string(3, characters32666);
        ivar_29 = (strings__string_t)strings__make_string(len32665, string32664);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_29);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}

bool_t stringutils__join_test3(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_27;
        strings__string_t ivar_8;
        uint32_t len32684 = 2;
        uint32_t characters32685[2] = {44, 32};
        stringliteral_t string32683 = mk_string(2, characters32685);
        ivar_8 = (strings__string_t)strings__make_string(len32684, string32683);
        ivar_27 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_8);
        stringutils_record_6_t ivar_30;
        uint8_t ivar_9;
        ivar_9 = (uint8_t)3;
        stringutils_array_4_t ivar_25;
        bytestrings__bytestring_t ivar_10;
        strings__string_t ivar_16;
        uint32_t len32687 = 1;
        uint32_t characters32688[1] = {97};
        stringliteral_t string32686 = mk_string(1, characters32688);
        ivar_16 = (strings__string_t)strings__make_string(len32687, string32686);
        ivar_10 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_16);
        bytestrings__bytestring_t ivar_11;
        strings__string_t ivar_20;
        uint32_t len32690 = 1;
        uint32_t characters32691[1] = {98};
        stringliteral_t string32689 = mk_string(1, characters32691);
        ivar_20 = (strings__string_t)strings__make_string(len32690, string32689);
        ivar_11 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_20);
        bytestrings__bytestring_t ivar_12;
        strings__string_t ivar_24;
        uint32_t len32693 = 1;
        uint32_t characters32694[1] = {99};
        stringliteral_t string32692 = mk_string(1, characters32694);
        ivar_24 = (strings__string_t)strings__make_string(len32693, string32692);
        ivar_12 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_24);
        ivar_25 = (stringutils_array_4_t)new_stringutils_array_4(3);
        ivar_25->elems[0]= ivar_10;
        ivar_25->elems[1]= ivar_11;
        ivar_25->elems[2]= ivar_12;
        stringutils_record_6_t tmp32695 = new_stringutils_record_6();;
        ivar_30 = (stringutils_record_6_t)tmp32695;
        tmp32695->length = (uint8_t)ivar_9;
        tmp32695->seq = (stringutils_array_4_t)ivar_25;
        stringutils_record_5_t ivar_28;
        //copying to stringutils_record_5 from stringutils_record_6;
        {

         ivar_28 = new_stringutils_record_5();
         ivar_28->length = (uint32_t)ivar_30->length;
         uint32_t length32679;
         length32679 = (uint32_t)ivar_28->length;
         ivar_28->seq = (stringutils_array_4_t)ivar_30->seq;
         if (ivar_28->seq != NULL) ivar_28->seq->count++;
         stringutils_array_4_t seq32680;
         seq32680 = (stringutils_array_4_t)ivar_28->seq; };
        release_stringutils_record_6((stringutils_record_6_t)ivar_30);
        ivar_1 = (bytestrings__bytestring_t)stringutils__join((bytestrings__bytestring_t)ivar_27, (stringutils_record_5_t)ivar_28);
        bytestrings__bytestring_t ivar_2;
        strings__string_t ivar_34;
        uint32_t len32697 = 7;
        uint32_t characters32698[7] = {97, 44, 32, 98, 44, 32, 99};
        stringliteral_t string32696 = mk_string(7, characters32698);
        ivar_34 = (strings__string_t)strings__make_string(len32697, string32696);
        ivar_2 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_34);
        result = (bool_t) equal_bytestrings__bytestring(ivar_1, ivar_2);
        defined = true;};
        
        
        return result;
}
