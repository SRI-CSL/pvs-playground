//Code generated using pvs2ir2c
#include "arrayCount_c.h"



arrayCount__arr_t new_arrayCount__arr(uint32_t size){
        arrayCount__arr_t tmp = (arrayCount__arr_t) safe_malloc(sizeof(struct arrayCount__arr_s) + (size * sizeof(arrayCount__T_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_arrayCount__arr(arrayCount__arr_t x, type_actual_t arrayCount__T){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){arrayCount__T->release_ptr(x->elems[i], arrayCount__T);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_arrayCount__arr_ptr(pointer_t x, type_actual_t T){
        actual_arrayCount__arr_t actual = (actual_arrayCount__arr_t)T;
        type_actual_t arrayCount__T = actual->arrayCount__T;
        release_arrayCount__arr((arrayCount__arr_t)x, arrayCount__T);
}

arrayCount__arr_t copy_arrayCount__arr(arrayCount__arr_t x){
        arrayCount__arr_t tmp = new_arrayCount__arr(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_arrayCount__arr(arrayCount__arr_t x, arrayCount__arr_t y, type_actual_t arrayCount__T){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = arrayCount__T->equal_ptr(x->elems[i], y->elems[i], arrayCount__T); i++;};
        return tmp;}

char * json_arrayCount__arr(arrayCount__arr_t x, type_actual_t arrayCount__T){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = arrayCount__T->json_ptr(x->elems[i], arrayCount__T);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_arrayCount__arr_ptr(pointer_t x, pointer_t y, type_actual_t T){
        actual_arrayCount__arr_t actual = (actual_arrayCount__arr_t)T;
        type_actual_t arrayCount__T = actual->arrayCount__T;
        return equal_arrayCount__arr((arrayCount__arr_t)x, (arrayCount__arr_t)y, arrayCount__T);
}

char * json_arrayCount__arr_ptr(pointer_t x, type_actual_t T){
        actual_arrayCount__arr_t actual = (actual_arrayCount__arr_t)T;
        type_actual_t arrayCount__T = actual->arrayCount__T;
        return json_arrayCount__arr((arrayCount__arr_t)x, arrayCount__T);
}

actual_arrayCount__arr_t actual_arrayCount__arr(type_actual_t arrayCount__T){
        actual_arrayCount__arr_t new = (actual_arrayCount__arr_t)safe_malloc(sizeof(struct actual_arrayCount__arr_s));
        new->equal_ptr = (equal_ptr_t)(*equal_arrayCount__arr_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_arrayCount__arr_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_arrayCount__arr_ptr);
 

        new->arrayCount__T = arrayCount__T;
 
        return new;
 }

arrayCount__arr_t update_arrayCount__arr(arrayCount__arr_t x, uint32_t i, arrayCount__T_t v, type_actual_t arrayCount__T){
         arrayCount__arr_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_arrayCount__arr(x);
                      x->count--;};
        arrayCount__T_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){arrayCount__T->release_ptr(yelems[i], arrayCount__T);};
         yelems[i] = v;
         return y;}

arrayCount__arr_t upgrade_arrayCount__arr(arrayCount__arr_t x, uint32_t i, arrayCount__T_t v, type_actual_t arrayCount__T){
         arrayCount__arr_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct arrayCount__arr_s) + (newmax * sizeof(arrayCount__T_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_arrayCount__arr(x);
                            x->count--;};
        arrayCount__T_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){arrayCount__T->release_ptr(yelems[i], arrayCount__T);};
         yelems[i] = v;
         return y;}



void release_arrayCount_funtype_1(arrayCount_funtype_1_t x, type_actual_t arrayCount__T){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

arrayCount_funtype_1_t copy_arrayCount_funtype_1(arrayCount_funtype_1_t x){return x->ftbl->cptr(x);}

bool_t equal_arrayCount_funtype_1(arrayCount_funtype_1_t x, arrayCount_funtype_1_t y, type_actual_t arrayCount__T){
        return false;}

char* json_arrayCount_funtype_1(arrayCount_funtype_1_t x, type_actual_t arrayCount__T){char * result = safe_malloc(30); sprintf(result, "%s", "\"arrayCount_funtype_1\""); return result;}

void release_arrayCount_funtype_2(arrayCount_funtype_2_t x, type_actual_t arrayCount__T){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

arrayCount_funtype_2_t copy_arrayCount_funtype_2(arrayCount_funtype_2_t x){return x->ftbl->cptr(x);}

bool_t equal_arrayCount_funtype_2(arrayCount_funtype_2_t x, arrayCount_funtype_2_t y, type_actual_t arrayCount__T){
        return false;}

char* json_arrayCount_funtype_2(arrayCount_funtype_2_t x, type_actual_t arrayCount__T){char * result = safe_malloc(30); sprintf(result, "%s", "\"arrayCount_funtype_2\""); return result;}

void release_arrayCount_funtype_3(arrayCount_funtype_3_t x, type_actual_t arrayCount__T){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

arrayCount_funtype_3_t copy_arrayCount_funtype_3(arrayCount_funtype_3_t x){return x->ftbl->cptr(x);}

bool_t equal_arrayCount_funtype_3(arrayCount_funtype_3_t x, arrayCount_funtype_3_t y, type_actual_t arrayCount__T){
        return false;}

char* json_arrayCount_funtype_3(arrayCount_funtype_3_t x, type_actual_t arrayCount__T){char * result = safe_malloc(30); sprintf(result, "%s", "\"arrayCount_funtype_3\""); return result;}


arrayCount_funtype_2_t f_arrayCount_closure_4(struct arrayCount_closure_4_s * closure, arrayCount_funtype_1_t bvar, type_actual_t arrayCount__T){
        release_arrayCount_funtype_3((arrayCount_funtype_3_t)closure, arrayCount__T);
        arrayCount_funtype_2_t result;
        result = (arrayCount_funtype_2_t)h_arrayCount_closure_4(bvar, arrayCount__T);
        return result;
}

arrayCount_funtype_2_t m_arrayCount_closure_4(struct arrayCount_closure_4_s * closure, arrayCount_funtype_1_t bvar, type_actual_t arrayCount__T){
        release_arrayCount_funtype_3((arrayCount_funtype_3_t)closure, arrayCount__T);
        return h_arrayCount_closure_4(bvar, arrayCount__T);}

arrayCount_funtype_2_t h_arrayCount_closure_4(arrayCount_funtype_1_t ivar_7, type_actual_t arrayCount__T){
        arrayCount_funtype_2_t result;

        arrayCount_closure_5_t cl32299;
        cl32299 = new_arrayCount_closure_5();
        result = (arrayCount_funtype_2_t)cl32299;
        return result;
}

arrayCount_closure_4_t new_arrayCount_closure_4(void){
        static struct arrayCount_funtype_3_ftbl_s ftbl = {.fptr = (arrayCount_funtype_2_t (*)(arrayCount_funtype_3_t, arrayCount_funtype_1_t))&f_arrayCount_closure_4, .mptr = (arrayCount_funtype_2_t (*)(arrayCount_funtype_3_t, arrayCount_funtype_1_t))&m_arrayCount_closure_4, .rptr =  (void (*)(arrayCount_funtype_3_t))&release_arrayCount_closure_4, .cptr = (arrayCount_funtype_3_t (*)(arrayCount_funtype_3_t))&copy_arrayCount_closure_4};
        arrayCount_closure_4_t tmp = (arrayCount_closure_4_t) safe_malloc(sizeof(struct arrayCount_closure_4_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_arrayCount_closure_4(arrayCount_funtype_3_t closure, type_actual_t arrayCount__T){
        arrayCount_closure_4_t x = (arrayCount_closure_4_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_arrayCount_funtype_1((arrayCount_funtype_1_t)x->htbl->data[j].key, arrayCount__T); release_arrayCount_funtype_2((arrayCount_funtype_2_t)x->htbl->data[j].value, arrayCount__T);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

arrayCount_closure_4_t copy_arrayCount_closure_4(arrayCount_closure_4_t x){
        arrayCount_closure_4_t y = new_arrayCount_closure_4();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            arrayCount_funtype_3_htbl_t new_htbl = (arrayCount_funtype_3_htbl_t) safe_malloc(sizeof(struct arrayCount_funtype_3_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            arrayCount_funtype_3_hashentry_t * new_data = (arrayCount_funtype_3_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct arrayCount_funtype_3_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (arrayCount_funtype_1_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (arrayCount_funtype_2_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint32_t f_arrayCount_closure_5(struct arrayCount_closure_5_s * closure, arrayCount__arr_t bvar, type_actual_t arrayCount__T){
        release_arrayCount_funtype_2((arrayCount_funtype_2_t)closure, arrayCount__T);
        uint32_t result;
        result = (uint32_t)h_arrayCount_closure_5(bvar, arrayCount__T);
        return result;
}

uint32_t m_arrayCount_closure_5(struct arrayCount_closure_5_s * closure, arrayCount__arr_t bvar, type_actual_t arrayCount__T){
        release_arrayCount_funtype_2((arrayCount_funtype_2_t)closure, arrayCount__T);
        return h_arrayCount_closure_5(bvar, arrayCount__T);}

uint32_t h_arrayCount_closure_5(arrayCount__arr_t ivar_11, type_actual_t arrayCount__T){
        uint32_t result;

        pvs2cerror("Non-executable theory: finite_sets", PVS2C_EXIT_ERROR);
        return result;
}

arrayCount_closure_5_t new_arrayCount_closure_5(void){
        static struct arrayCount_funtype_2_ftbl_s ftbl = {.fptr = (uint32_t (*)(arrayCount_funtype_2_t, arrayCount__arr_t))&f_arrayCount_closure_5, .mptr = (uint32_t (*)(arrayCount_funtype_2_t, arrayCount__arr_t))&m_arrayCount_closure_5, .rptr =  (void (*)(arrayCount_funtype_2_t))&release_arrayCount_closure_5, .cptr = (arrayCount_funtype_2_t (*)(arrayCount_funtype_2_t))&copy_arrayCount_closure_5};
        arrayCount_closure_5_t tmp = (arrayCount_closure_5_t) safe_malloc(sizeof(struct arrayCount_closure_5_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_arrayCount_closure_5(arrayCount_funtype_2_t closure, type_actual_t arrayCount__T){
        arrayCount_closure_5_t x = (arrayCount_closure_5_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_arrayCount__arr((arrayCount__arr_t)x->htbl->data[j].key, arrayCount__T);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

arrayCount_closure_5_t copy_arrayCount_closure_5(arrayCount_closure_5_t x){
        arrayCount_closure_5_t y = new_arrayCount_closure_5();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            arrayCount_funtype_2_htbl_t new_htbl = (arrayCount_funtype_2_htbl_t) safe_malloc(sizeof(struct arrayCount_funtype_2_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            arrayCount_funtype_2_hashentry_t * new_data = (arrayCount_funtype_2_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct arrayCount_funtype_2_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (arrayCount__arr_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (uint32_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}
arrayCount_funtype_3_t arrayCount__count(type_actual_t arrayCount__T, uint32_t ivar_1){
        arrayCount_funtype_3_t  result;

        arrayCount_closure_4_t cl32300;
        cl32300 = new_arrayCount_closure_4();
        result = (arrayCount_funtype_3_t)cl32300;
        
        
        return result;
}
