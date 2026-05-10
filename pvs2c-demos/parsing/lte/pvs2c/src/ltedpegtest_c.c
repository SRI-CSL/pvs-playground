//Code generated using pvs2ir2c
#include "ltedpegtest_c.h"



ltedpegtest_array_0_t new_ltedpegtest_array_0(uint32_t size){
        ltedpegtest_array_0_t tmp = (ltedpegtest_array_0_t) safe_malloc(sizeof(struct ltedpegtest_array_0_s) + (size * sizeof(ltedpeg__prepeg_adt_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_ltedpegtest_array_0(ltedpegtest_array_0_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_ltedpegtest_array_0_ptr(pointer_t x, type_actual_t T){
        release_ltedpegtest_array_0((ltedpegtest_array_0_t)x);
}

ltedpegtest_array_0_t copy_ltedpegtest_array_0(ltedpegtest_array_0_t x){
        ltedpegtest_array_0_t tmp = new_ltedpegtest_array_0(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_ltedpegtest_array_0(ltedpegtest_array_0_t x, ltedpegtest_array_0_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_ltedpeg__prepeg_adt(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_ltedpegtest_array_0(ltedpegtest_array_0_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_ltedpeg__prepeg_adt(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpegtest_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpegtest_array_0((ltedpegtest_array_0_t)x, (ltedpegtest_array_0_t)y);
}

char * json_ltedpegtest_array_0_ptr(pointer_t x, type_actual_t T){
        return json_ltedpegtest_array_0((ltedpegtest_array_0_t)x);
}

actual_ltedpegtest_array_0_t actual_ltedpegtest_array_0(void){
        actual_ltedpegtest_array_0_t new = (actual_ltedpegtest_array_0_t)safe_malloc(sizeof(struct actual_ltedpegtest_array_0_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpegtest_array_0_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpegtest_array_0_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpegtest_array_0_ptr);
 

 
        return new;
 }

ltedpegtest_array_0_t update_ltedpegtest_array_0(ltedpegtest_array_0_t x, uint32_t i, ltedpeg__prepeg_adt_t v){
         ltedpegtest_array_0_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_ltedpegtest_array_0(x);
                      x->count--;};
        ltedpeg__prepeg_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}

ltedpegtest_array_0_t upgrade_ltedpegtest_array_0(ltedpegtest_array_0_t x, uint32_t i, ltedpeg__prepeg_adt_t v){
         ltedpegtest_array_0_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct ltedpegtest_array_0_s) + (newmax * sizeof(ltedpeg__prepeg_adt_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_ltedpegtest_array_0(x);
                            x->count--;};
        ltedpeg__prepeg_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}



void release_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpegtest_funtype_1_t copy_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpegtest_funtype_1(ltedpegtest_funtype_1_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpegtest_funtype_1_hashentry_t data = htbl->data[hashindex];
        bool_t keyzero;


        keyzero = (data.key == 0);
        bool_t keymatch;

        keymatch = (data.key == i);
        while ((!keyzero || data.keyhash != 0) &&
                 (data.keyhash != ihash || !keymatch)){
                hashindex++;
                hashindex = hashindex & mask;
                data = htbl->data[hashindex];


                keyzero = (data.key == 0);


                keymatch = (data.key == i);
                }
        return hashindex;
        }

ltedpegtest_funtype_1_t dupdate_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t a, uint8_t i, ltedpeg__ent_adt_t v){
        ltedpegtest_funtype_1_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpegtest_funtype_1_htbl_t)safe_malloc(sizeof(struct ltedpegtest_funtype_1_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpegtest_funtype_1_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpegtest_funtype_1_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpegtest_funtype_1_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpegtest_funtype_1_hashentry_t * new_data = (ltedpegtest_funtype_1_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpegtest_funtype_1_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = (uint8_t)0; 
                        new_data[j].keyhash = 0;}
                for (uint32_t j = 0; j < size; j++){//transfer entries
                        uint32_t keyhash = data[j].keyhash;
                        bool_t keyzero;
                        keyzero = (data[j].key == 0);

                        if (!keyzero || keyhash != 0){
                                uint32_t new_loc = keyhash ^ new_mask;
                                bool_t newkeyzero;
                                newkeyzero = (new_data[new_loc].key == 0);

                                while (!newkeyzero || new_data[new_loc].keyhash != 0){
                                        new_loc++;
                                        new_loc = new_loc ^ new_mask;

                                        newkeyzero = (new_data[new_loc].key == 0);

                                }
                                new_data[new_loc].key = (uint8_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (ltedpeg__ent_adt_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                for (uint32_t j=0; j < size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)data[j].value);};
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_ltedpegtest_funtype_1(htbl, i, ihash);
        ltedpegtest_funtype_1_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (ltedpeg__ent_adt_t)v; htbl->num_entries++;}
            else {ltedpeg__ent_adt_t tempvalue;tempvalue = (ltedpeg__ent_adt_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (ltedpeg__ent_adt_t)v;if (v != NULL) v->count++;if (tempvalue != NULL)release_ltedpeg__ent_adt(tempvalue);};
        return a;

}

ltedpegtest_funtype_1_t update_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t a, uint8_t i, ltedpeg__ent_adt_t v){
        if (a->count == 1){
                return dupdate_ltedpegtest_funtype_1(a, i, v);
            } else {
                ltedpegtest_funtype_1_t x = copy_ltedpegtest_funtype_1(a);
                a->count--;
                return dupdate_ltedpegtest_funtype_1(x, i, v);
            }}

bool_t equal_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x, ltedpegtest_funtype_1_t y){
        return false;}

char* json_ltedpegtest_funtype_1(ltedpegtest_funtype_1_t x){char * result = safe_malloc(31); sprintf(result, "%s", "\"ltedpegtest_funtype_1\""); return result;}


ltedpeg__ent_adt_t f_ltedpegtest_closure_2(struct ltedpegtest_closure_2_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        ltedpegtest_funtype_1_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_ltedpegtest_funtype_1(htbl, bvar, hash);
        ltedpegtest_funtype_1_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
                ltedpeg__ent_adt_t result;
                release_ltedpegtest_funtype_1((ltedpegtest_funtype_1_t)closure);
                result = (ltedpeg__ent_adt_t)entry.value;
                return result;}
        else {

            release_ltedpegtest_funtype_1((ltedpegtest_funtype_1_t)closure);
            ltedpeg__ent_adt_t result;
            result = (ltedpeg__ent_adt_t)h_ltedpegtest_closure_2(bvar);
            return result;};
        }

      else {
        release_ltedpegtest_funtype_1((ltedpegtest_funtype_1_t)closure);
        ltedpeg__ent_adt_t result;
        result = (ltedpeg__ent_adt_t)h_ltedpegtest_closure_2(bvar);
        return result;}
}

ltedpeg__ent_adt_t m_ltedpegtest_closure_2(struct ltedpegtest_closure_2_s * closure, uint8_t bvar){
        release_ltedpegtest_funtype_1((ltedpegtest_funtype_1_t)closure);
        return h_ltedpegtest_closure_2(bvar);}

ltedpeg__ent_adt_t h_ltedpegtest_closure_2(uint8_t ivar_40){
        ltedpeg__ent_adt_t result;

        result = (ltedpeg__ent_adt_t)con_ltedpeg__pending();
        if (result != NULL) result->count++;
        return result;
}

ltedpegtest_closure_2_t new_ltedpegtest_closure_2(void){
        static struct ltedpegtest_funtype_1_ftbl_s ftbl = {.fptr = (ltedpeg__ent_adt_t (*)(ltedpegtest_funtype_1_t, uint8_t))&f_ltedpegtest_closure_2, .mptr = (ltedpeg__ent_adt_t (*)(ltedpegtest_funtype_1_t, uint8_t))&m_ltedpegtest_closure_2, .rptr =  (void (*)(ltedpegtest_funtype_1_t))&release_ltedpegtest_closure_2, .cptr = (ltedpegtest_funtype_1_t (*)(ltedpegtest_funtype_1_t))&copy_ltedpegtest_closure_2};
        ltedpegtest_closure_2_t tmp = (ltedpegtest_closure_2_t) safe_malloc(sizeof(struct ltedpegtest_closure_2_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpegtest_closure_2(ltedpegtest_funtype_1_t closure){
        ltedpegtest_closure_2_t x = (ltedpegtest_closure_2_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpegtest_closure_2_t copy_ltedpegtest_closure_2(ltedpegtest_closure_2_t x){
        ltedpegtest_closure_2_t y = new_ltedpegtest_closure_2();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            ltedpegtest_funtype_1_htbl_t new_htbl = (ltedpegtest_funtype_1_htbl_t) safe_malloc(sizeof(struct ltedpegtest_funtype_1_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpegtest_funtype_1_hashentry_t * new_data = (ltedpegtest_funtype_1_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpegtest_funtype_1_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (uint8_t)x->htbl->data[j].key;
                  new_data[j].value = (ltedpeg__ent_adt_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpegtest_array_3_t new_ltedpegtest_array_3(uint32_t size){
        ltedpegtest_array_3_t tmp = (ltedpegtest_array_3_t) safe_malloc(sizeof(struct ltedpegtest_array_3_s) + (size * sizeof(ltedpeg__ent_adt_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_ltedpegtest_array_3(ltedpegtest_array_3_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_ltedpegtest_array_3_ptr(pointer_t x, type_actual_t T){
        release_ltedpegtest_array_3((ltedpegtest_array_3_t)x);
}

ltedpegtest_array_3_t copy_ltedpegtest_array_3(ltedpegtest_array_3_t x){
        ltedpegtest_array_3_t tmp = new_ltedpegtest_array_3(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_ltedpegtest_array_3(ltedpegtest_array_3_t x, ltedpegtest_array_3_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_ltedpeg__ent_adt(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_ltedpegtest_array_3(ltedpegtest_array_3_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_ltedpeg__ent_adt(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpegtest_array_3_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpegtest_array_3((ltedpegtest_array_3_t)x, (ltedpegtest_array_3_t)y);
}

char * json_ltedpegtest_array_3_ptr(pointer_t x, type_actual_t T){
        return json_ltedpegtest_array_3((ltedpegtest_array_3_t)x);
}

actual_ltedpegtest_array_3_t actual_ltedpegtest_array_3(void){
        actual_ltedpegtest_array_3_t new = (actual_ltedpegtest_array_3_t)safe_malloc(sizeof(struct actual_ltedpegtest_array_3_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpegtest_array_3_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpegtest_array_3_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpegtest_array_3_ptr);
 

 
        return new;
 }

ltedpegtest_array_3_t update_ltedpegtest_array_3(ltedpegtest_array_3_t x, uint32_t i, ltedpeg__ent_adt_t v){
         ltedpegtest_array_3_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_ltedpegtest_array_3(x);
                      x->count--;};
        ltedpeg__ent_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}

ltedpegtest_array_3_t upgrade_ltedpegtest_array_3(ltedpegtest_array_3_t x, uint32_t i, ltedpeg__ent_adt_t v){
         ltedpegtest_array_3_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct ltedpegtest_array_3_s) + (newmax * sizeof(ltedpeg__ent_adt_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_ltedpegtest_array_3(x);
                            x->count--;};
        ltedpeg__ent_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}




ltedpegtest_array_4_t new_ltedpegtest_array_4(uint32_t size){
        ltedpegtest_array_4_t tmp = (ltedpegtest_array_4_t) safe_malloc(sizeof(struct ltedpegtest_array_4_s) + (size * sizeof(ltedpegtest_array_3_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_ltedpegtest_array_4(ltedpegtest_array_4_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_ltedpegtest_array_3((ltedpegtest_array_3_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_ltedpegtest_array_4_ptr(pointer_t x, type_actual_t T){
        release_ltedpegtest_array_4((ltedpegtest_array_4_t)x);
}

ltedpegtest_array_4_t copy_ltedpegtest_array_4(ltedpegtest_array_4_t x){
        ltedpegtest_array_4_t tmp = new_ltedpegtest_array_4(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_ltedpegtest_array_4(ltedpegtest_array_4_t x, ltedpegtest_array_4_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_ltedpegtest_array_3(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_ltedpegtest_array_4(ltedpegtest_array_4_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_ltedpegtest_array_3(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpegtest_array_4_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpegtest_array_4((ltedpegtest_array_4_t)x, (ltedpegtest_array_4_t)y);
}

char * json_ltedpegtest_array_4_ptr(pointer_t x, type_actual_t T){
        return json_ltedpegtest_array_4((ltedpegtest_array_4_t)x);
}

actual_ltedpegtest_array_4_t actual_ltedpegtest_array_4(void){
        actual_ltedpegtest_array_4_t new = (actual_ltedpegtest_array_4_t)safe_malloc(sizeof(struct actual_ltedpegtest_array_4_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpegtest_array_4_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpegtest_array_4_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpegtest_array_4_ptr);
 

 
        return new;
 }

ltedpegtest_array_4_t update_ltedpegtest_array_4(ltedpegtest_array_4_t x, uint32_t i, ltedpegtest_array_3_t v){
         ltedpegtest_array_4_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_ltedpegtest_array_4(x);
                      x->count--;};
        ltedpegtest_array_3_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_ltedpegtest_array_3((ltedpegtest_array_3_t)yelems[i]);};
         yelems[i] = v;
         return y;}

ltedpegtest_array_4_t upgrade_ltedpegtest_array_4(ltedpegtest_array_4_t x, uint32_t i, ltedpegtest_array_3_t v){
         ltedpegtest_array_4_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct ltedpegtest_array_4_s) + (newmax * sizeof(ltedpegtest_array_3_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_ltedpegtest_array_4(x);
                            x->count--;};
        ltedpegtest_array_3_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_ltedpegtest_array_3((ltedpegtest_array_3_t)yelems[i]);};
         yelems[i] = v;
         return y;}




ltedpegtest_record_5_t new_ltedpegtest_record_5(void){
        ltedpegtest_record_5_t tmp = (ltedpegtest_record_5_t) safe_malloc(sizeof(struct ltedpegtest_record_5_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpegtest_record_5(ltedpegtest_record_5_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpegtest_array_4((ltedpegtest_array_4_t)x->scaf);
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpegtest_record_5_ptr(pointer_t x, type_actual_t T){
        release_ltedpegtest_record_5((ltedpegtest_record_5_t)x);
}

ltedpegtest_record_5_t copy_ltedpegtest_record_5(ltedpegtest_record_5_t x){
        ltedpegtest_record_5_t y = new_ltedpegtest_record_5();
        y->scaf = x->scaf;
        if (y->scaf != NULL){y->scaf->count++;};
        y->depth = (uint64_t)x->depth;
        y->stack = x->stack;
        if (y->stack != NULL){y->stack->count++;};
        y->lflag = (bool_t)x->lflag;
        y->count = 1;
        return y;}

bool_t equal_ltedpegtest_record_5(ltedpegtest_record_5_t x, ltedpegtest_record_5_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpegtest_array_4((ltedpegtest_array_4_t)x->scaf, (ltedpegtest_array_4_t)y->scaf); tmp = tmp && x->depth == y->depth; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack, (ltedpeg__ent_adt_t)y->stack); tmp = tmp && x->lflag == y->lflag;
        return tmp;}

char * json_ltedpegtest_record_5(ltedpegtest_record_5_t x){
        char * tmp[4]; 
        char * fld0 = safe_malloc(16);
         sprintf(fld0, "\"scaf\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpegtest_array_4((ltedpegtest_array_4_t)x->scaf));
        char * fld1 = safe_malloc(17);
         sprintf(fld1, "\"depth\" : ");
        tmp[1] = safe_strcat(fld1, json_uint64(x->depth));
        char * fld2 = safe_malloc(17);
         sprintf(fld2, "\"stack\" : ");
        tmp[2] = safe_strcat(fld2, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack));
        char * fld3 = safe_malloc(17);
         sprintf(fld3, "\"lflag\" : ");
        tmp[3] = safe_strcat(fld3, json_bool(x->lflag));
         char * result = json_list_with_sep(tmp, 4,  '{', ',', '}');
         for (uint32_t i = 0; i < 4; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpegtest_record_5_ptr(pointer_t x, pointer_t y, actual_ltedpegtest_record_5_t T){
        return equal_ltedpegtest_record_5((ltedpegtest_record_5_t)x, (ltedpegtest_record_5_t)y);
}

char * json_ltedpegtest_record_5_ptr(pointer_t x, actual_ltedpegtest_record_5_t T){
        return json_ltedpegtest_record_5((ltedpegtest_record_5_t)x);
}

actual_ltedpegtest_record_5_t actual_ltedpegtest_record_5(void){
        actual_ltedpegtest_record_5_t new = (actual_ltedpegtest_record_5_t)safe_malloc(sizeof(struct actual_ltedpegtest_record_5_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpegtest_record_5_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpegtest_record_5_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpegtest_record_5_ptr);
 

 
        return new;
 }

ltedpegtest_record_5_t update_ltedpegtest_record_5_scaf(ltedpegtest_record_5_t x, ltedpegtest_array_4_t v){
        ltedpegtest_record_5_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->scaf != NULL){release_ltedpegtest_array_4((ltedpegtest_array_4_t)x->scaf);};}
        else {y = copy_ltedpegtest_record_5(x); x->count--; y->scaf->count--;};
        y->scaf = (ltedpegtest_array_4_t)v;
        return y;}

ltedpegtest_record_5_t update_ltedpegtest_record_5_depth(ltedpegtest_record_5_t x, uint64_t v){
        ltedpegtest_record_5_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpegtest_record_5(x); x->count--;};
        y->depth = (uint64_t)v;
        return y;}

ltedpegtest_record_5_t update_ltedpegtest_record_5_stack(ltedpegtest_record_5_t x, ltedpeg__ent_adt_t v){
        ltedpegtest_record_5_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->stack != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack);};}
        else {y = copy_ltedpegtest_record_5(x); x->count--; y->stack->count--;};
        y->stack = (ltedpeg__ent_adt_t)v;
        return y;}

ltedpegtest_record_5_t update_ltedpegtest_record_5_lflag(ltedpegtest_record_5_t x, bool_t v){
        ltedpegtest_record_5_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpegtest_record_5(x); x->count--;};
        y->lflag = (bool_t)v;
        return y;}


ltedpeg__prepeg_adt_t ltedpegtest__djson(uint8_t ivar_1){
        ltedpeg__prepeg_adt_t  result;

        bool_t ivar_2;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)0;
        ivar_2 = (ivar_1 == ivar_4);
        if (ivar_2){
             uint8_t ivar_10;
             ivar_10 = (uint8_t)3;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)1;
             uint8_t ivar_12;
             ivar_12 = (uint8_t)33;
             result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_10, (uint8_t)ivar_11, (uint8_t)ivar_12);
        } else {
             bool_t ivar_13;
             uint8_t ivar_15;
             ivar_15 = (uint8_t)1;
             ivar_13 = (ivar_1 == ivar_15);
             if (ivar_13){
           uint8_t ivar_21;
           ivar_21 = (uint8_t)16;
           uint8_t ivar_22;
           ivar_22 = (uint8_t)33;
           uint8_t ivar_23;
           ivar_23 = (uint8_t)2;
           result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_21, (uint8_t)ivar_22, (uint8_t)ivar_23);
             } else {
           bool_t ivar_24;
           uint8_t ivar_26;
           ivar_26 = (uint8_t)2;
           ivar_24 = (ivar_1 == ivar_26);
           if (ivar_24){
           uint8_t ivar_32;
           ivar_32 = (uint8_t)24;
           uint8_t ivar_33;
           ivar_33 = (uint8_t)5;
           uint8_t ivar_34;
           ivar_34 = (uint8_t)7;
           result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_32, (uint8_t)ivar_33, (uint8_t)ivar_34);
           } else {
           bool_t ivar_35;
           uint8_t ivar_37;
           ivar_37 = (uint8_t)3;
           ivar_35 = (ivar_1 == ivar_37);
           if (ivar_35){
            uint8_t ivar_43;
            ivar_43 = (uint8_t)4;
            uint8_t ivar_44;
            ivar_44 = (uint8_t)33;
            uint8_t ivar_45;
            ivar_45 = (uint8_t)33;
            result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_43, (uint8_t)ivar_44, (uint8_t)ivar_45);
           } else {
            bool_t ivar_46;
            uint8_t ivar_48;
            ivar_48 = (uint8_t)4;
            ivar_46 = (ivar_1 == ivar_48);
            if (ivar_46){
             dpeg__dpeg_grammar_t ivar_52;
             ivar_52 = (dpeg__dpeg_grammar_t)dpeg__wspace_grammar();
             if (ivar_52 != NULL) ivar_52->count++;
             result = (ltedpeg__prepeg_adt_t)con_ltedpeg__any((dpeg__dpeg_grammar_t)ivar_52);
            } else {
             bool_t ivar_53;
             uint8_t ivar_55;
             ivar_55 = (uint8_t)5;
             ivar_53 = (ivar_1 == ivar_55);
             if (ivar_53){
              uint8_t ivar_61;
              ivar_61 = (uint8_t)25;
              uint8_t ivar_62;
              ivar_62 = (uint8_t)33;
              uint8_t ivar_63;
              ivar_63 = (uint8_t)6;
              result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_61, (uint8_t)ivar_62, (uint8_t)ivar_63);
             } else {
              bool_t ivar_64;
              uint8_t ivar_66;
              ivar_66 = (uint8_t)6;
              ivar_64 = (ivar_1 == ivar_66);
              if (ivar_64){
               uint8_t ivar_72;
               ivar_72 = (uint8_t)8;
               uint8_t ivar_73;
               ivar_73 = (uint8_t)10;
               uint8_t ivar_74;
               ivar_74 = (uint8_t)32;
               result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_72, (uint8_t)ivar_73, (uint8_t)ivar_74);
              } else {
               bool_t ivar_75;
               uint8_t ivar_77;
               ivar_77 = (uint8_t)7;
               ivar_75 = (ivar_1 == ivar_77);
               if (ivar_75){
                uint8_t ivar_83;
                ivar_83 = (uint8_t)8;
                uint8_t ivar_84;
                ivar_84 = (uint8_t)33;
                uint8_t ivar_85;
                ivar_85 = (uint8_t)9;
                result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_83, (uint8_t)ivar_84, (uint8_t)ivar_85);
               } else {
                bool_t ivar_86;
                uint8_t ivar_88;
                ivar_88 = (uint8_t)8;
                ivar_86 = (ivar_1 == ivar_88);
                if (ivar_86){
                 dpeg__dpeg_grammar_t ivar_92;
                 ivar_92 = (dpeg__dpeg_grammar_t)dpeg__string_grammar();
                 if (ivar_92 != NULL) ivar_92->count++;
                 result = (ltedpeg__prepeg_adt_t)con_ltedpeg__any((dpeg__dpeg_grammar_t)ivar_92);
                } else {
                 bool_t ivar_93;
                 uint8_t ivar_95;
                 ivar_95 = (uint8_t)9;
                 ivar_93 = (ivar_1 == ivar_95);
                 if (ivar_93){
                  uint8_t ivar_101;
                  ivar_101 = (uint8_t)26;
                  uint8_t ivar_102;
                  ivar_102 = (uint8_t)13;
                  uint8_t ivar_103;
                  ivar_103 = (uint8_t)33;
                  result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_101, (uint8_t)ivar_102, (uint8_t)ivar_103);
                 } else {
                  bool_t ivar_104;
                  uint8_t ivar_106;
                  ivar_106 = (uint8_t)10;
                  ivar_104 = (ivar_1 == ivar_106);
                  if (ivar_104){
                   uint8_t ivar_112;
                   ivar_112 = (uint8_t)29;
                   uint8_t ivar_113;
                   ivar_113 = (uint8_t)11;
                   uint8_t ivar_114;
                   ivar_114 = (uint8_t)32;
                   result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_112, (uint8_t)ivar_113, (uint8_t)ivar_114);
                  } else {
                   bool_t ivar_115;
                   uint8_t ivar_117;
                   ivar_117 = (uint8_t)11;
                   ivar_115 = (ivar_1 == ivar_117);
                   if (ivar_115){
                    uint8_t ivar_123;
                    ivar_123 = (uint8_t)1;
                    uint8_t ivar_124;
                    ivar_124 = (uint8_t)12;
                    uint8_t ivar_125;
                    ivar_125 = (uint8_t)32;
                    result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_123, (uint8_t)ivar_124, (uint8_t)ivar_125);
                   } else {
                    bool_t ivar_126;
                    uint8_t ivar_128;
                    ivar_128 = (uint8_t)12;
                    ivar_126 = (ivar_1 == ivar_128);
                    if (ivar_126){
                     uint8_t ivar_134;
                     ivar_134 = (uint8_t)28;
                     uint8_t ivar_135;
                     ivar_135 = (uint8_t)5;
                     uint8_t ivar_136;
                     ivar_136 = (uint8_t)25;
                     result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_134, (uint8_t)ivar_135, (uint8_t)ivar_136);
                    } else {
                     bool_t ivar_137;
                     uint8_t ivar_139;
                     ivar_139 = (uint8_t)13;
                     ivar_137 = (ivar_1 == ivar_139);
                     if (ivar_137){
                      uint8_t ivar_145;
                      ivar_145 = (uint8_t)27;
                      uint8_t ivar_146;
                      ivar_146 = (uint8_t)33;
                      uint8_t ivar_147;
                      ivar_147 = (uint8_t)15;
                      result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_145, (uint8_t)ivar_146, (uint8_t)ivar_147);
                     } else {
                      bool_t ivar_148;
                      uint8_t ivar_150;
                      ivar_150 = (uint8_t)14;
                      ivar_148 = (ivar_1 == ivar_150);
                      if (ivar_148){
                       uint8_t ivar_156;
                       ivar_156 = (uint8_t)28;
                       uint8_t ivar_157;
                       ivar_157 = (uint8_t)15;
                       uint8_t ivar_158;
                       ivar_158 = (uint8_t)27;
                       result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_156, (uint8_t)ivar_157, (uint8_t)ivar_158);
                      } else {
                       bool_t ivar_159;
                       uint8_t ivar_161;
                       ivar_161 = (uint8_t)15;
                       ivar_159 = (ivar_1 == ivar_161);
                       if (ivar_159){
                        uint8_t ivar_167;
                        ivar_167 = (uint8_t)1;
                        uint8_t ivar_168;
                        ivar_168 = (uint8_t)14;
                        uint8_t ivar_169;
                        ivar_169 = (uint8_t)32;
                        result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_167, (uint8_t)ivar_168, (uint8_t)ivar_169);
                       } else {
                        bool_t ivar_170;
                        uint8_t ivar_172;
                        ivar_172 = (uint8_t)16;
                        ivar_170 = (ivar_1 == ivar_172);
                        if (ivar_170){
                         uint8_t ivar_178;
                         ivar_178 = (uint8_t)30;
                         uint8_t ivar_179;
                         ivar_179 = (uint8_t)33;
                         uint8_t ivar_180;
                         ivar_180 = (uint8_t)31;
                         result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_178, (uint8_t)ivar_179, (uint8_t)ivar_180);
                        } else {
                         bool_t ivar_181;
                         uint8_t ivar_183;
                         ivar_183 = (uint8_t)17;
                         ivar_181 = (ivar_1 == ivar_183);
                         if (ivar_181){
                          uint8_t ivar_187;
                          ivar_187 = (uint8_t)123;
                          result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_187);
                         } else {
                          bool_t ivar_188;
                          uint8_t ivar_190;
                          ivar_190 = (uint8_t)18;
                          ivar_188 = (ivar_1 == ivar_190);
                          if (ivar_188){
                           uint8_t ivar_194;
                           ivar_194 = (uint8_t)125;
                           result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_194);
                          } else {
                           bool_t ivar_195;
                           uint8_t ivar_197;
                           ivar_197 = (uint8_t)19;
                           ivar_195 = (ivar_1 == ivar_197);
                           if (ivar_195){
                            uint8_t ivar_201;
                            ivar_201 = (uint8_t)91;
                            result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_201);
                           } else {
                            bool_t ivar_202;
                            uint8_t ivar_204;
                            ivar_204 = (uint8_t)20;
                            ivar_202 = (ivar_1 == ivar_204);
                            if (ivar_202){
                             uint8_t ivar_208;
                             ivar_208 = (uint8_t)93;
                             result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_208);
                            } else {
                             bool_t ivar_209;
                             uint8_t ivar_211;
                             ivar_211 = (uint8_t)21;
                             ivar_209 = (ivar_1 == ivar_211);
                             if (ivar_209){
                              uint8_t ivar_215;
                              ivar_215 = (uint8_t)34;
                              result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_215);
                             } else {
                              bool_t ivar_216;
                              uint8_t ivar_218;
                              ivar_218 = (uint8_t)22;
                              ivar_216 = (ivar_1 == ivar_218);
                              if (ivar_216){
                               uint8_t ivar_222;
                               ivar_222 = (uint8_t)44;
                               result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_222);
                              } else {
                               bool_t ivar_223;
                               uint8_t ivar_225;
                               ivar_225 = (uint8_t)23;
                               ivar_223 = (ivar_1 == ivar_225);
                               if (ivar_223){
                                uint8_t ivar_229;
                                ivar_229 = (uint8_t)58;
                                result = (ltedpeg__prepeg_adt_t)con_ltedpeg__terminal((uint8_t)ivar_229);
                               } else {
                                bool_t ivar_230;
                                uint8_t ivar_232;
                                ivar_232 = (uint8_t)24;
                                ivar_230 = (ivar_1 == ivar_232);
                                if (ivar_230){
                                 uint8_t ivar_238;
                                 ivar_238 = (uint8_t)17;
                                 uint8_t ivar_239;
                                 ivar_239 = (uint8_t)3;
                                 uint8_t ivar_240;
                                 ivar_240 = (uint8_t)32;
                                 result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_238, (uint8_t)ivar_239, (uint8_t)ivar_240);
                                } else {
                                 bool_t ivar_241;
                                 uint8_t ivar_243;
                                 ivar_243 = (uint8_t)25;
                                 ivar_241 = (ivar_1 == ivar_243);
                                 if (ivar_241){
                                  uint8_t ivar_249;
                                  ivar_249 = (uint8_t)18;
                                  uint8_t ivar_250;
                                  ivar_250 = (uint8_t)3;
                                  uint8_t ivar_251;
                                  ivar_251 = (uint8_t)32;
                                  result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_249, (uint8_t)ivar_250, (uint8_t)ivar_251);
                                 } else {
                                  bool_t ivar_252;
                                  uint8_t ivar_254;
                                  ivar_254 = (uint8_t)26;
                                  ivar_252 = (ivar_1 == ivar_254);
                                  if (ivar_252){
                                   uint8_t ivar_260;
                                   ivar_260 = (uint8_t)19;
                                   uint8_t ivar_261;
                                   ivar_261 = (uint8_t)3;
                                   uint8_t ivar_262;
                                   ivar_262 = (uint8_t)32;
                                   result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_260, (uint8_t)ivar_261, (uint8_t)ivar_262);
                                  } else {
                                   bool_t ivar_263;
                                   uint8_t ivar_265;
                                   ivar_265 = (uint8_t)27;
                                   ivar_263 = (ivar_1 == ivar_265);
                                   if (ivar_263){
                                    uint8_t ivar_271;
                                    ivar_271 = (uint8_t)20;
                                    uint8_t ivar_272;
                                    ivar_272 = (uint8_t)3;
                                    uint8_t ivar_273;
                                    ivar_273 = (uint8_t)32;
                                    result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_271, (uint8_t)ivar_272, (uint8_t)ivar_273);
                                   } else {
                                    bool_t ivar_274;
                                    uint8_t ivar_276;
                                    ivar_276 = (uint8_t)28;
                                    ivar_274 = (ivar_1 == ivar_276);
                                    if (ivar_274){
                                     uint8_t ivar_282;
                                     ivar_282 = (uint8_t)22;
                                     uint8_t ivar_283;
                                     ivar_283 = (uint8_t)3;
                                     uint8_t ivar_284;
                                     ivar_284 = (uint8_t)32;
                                     result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_282, (uint8_t)ivar_283, (uint8_t)ivar_284);
                                    } else {
                                     bool_t ivar_285;
                                     uint8_t ivar_287;
                                     ivar_287 = (uint8_t)29;
                                     ivar_285 = (ivar_1 == ivar_287);
                                     if (ivar_285){
                                      uint8_t ivar_293;
                                      ivar_293 = (uint8_t)23;
                                      uint8_t ivar_294;
                                      ivar_294 = (uint8_t)3;
                                      uint8_t ivar_295;
                                      ivar_295 = (uint8_t)32;
                                      result = (ltedpeg__prepeg_adt_t)con_ltedpeg__lte((uint8_t)ivar_293, (uint8_t)ivar_294, (uint8_t)ivar_295);
                                     } else {
                                      bool_t ivar_296;
                                      uint8_t ivar_298;
                                      ivar_298 = (uint8_t)30;
                                      ivar_296 = (ivar_1 == ivar_298);
                                      if (ivar_296){
                                       dpeg__dpeg_grammar_t ivar_302;
                                       ivar_302 = (dpeg__dpeg_grammar_t)dpeg__numeral_grammar();
                                       if (ivar_302 != NULL) ivar_302->count++;
                                       result = (ltedpeg__prepeg_adt_t)con_ltedpeg__any((dpeg__dpeg_grammar_t)ivar_302);
                                      } else {
                                       bool_t ivar_303;
                                       uint8_t ivar_305;
                                       ivar_305 = (uint8_t)31;
                                       ivar_303 = (ivar_1 == ivar_305);
                                       if (ivar_303){
                                        dpeg__dpeg_grammar_t ivar_309;
                                        ivar_309 = (dpeg__dpeg_grammar_t)dpeg__key_grammar();
                                        if (ivar_309 != NULL) ivar_309->count++;
                                        result = (ltedpeg__prepeg_adt_t)con_ltedpeg__any((dpeg__dpeg_grammar_t)ivar_309);
                                       } else {
                                        bool_t ivar_310;
                                        uint8_t ivar_312;
                                        ivar_312 = (uint8_t)32;
                                        ivar_310 = (ivar_1 == ivar_312);
                                        if (ivar_310){
                                         result = (ltedpeg__prepeg_adt_t)con_ltedpeg__failure();
                                         if (result != NULL) result->count++;
                                        } else {
                                         result = (ltedpeg__prepeg_adt_t)con_ltedpeg__epsilon();
                                         if (result != NULL) result->count++;};};};};};};};};};};};};};};};};};};};};};};};};};};};};};};};};};
        
        
        return result;
}

ltedpegtest_array_0_t ltedpegtest__djsontable(void){
        ltedpegtest_array_0_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        /* tbl */ ltedpegtest_array_0_t ivar_1;
        ivar_1 = new_ltedpegtest_array_0(255);
        uint8_t ivar_3;
        for (uint32_t index33880 = 0; index33880 < 255; index33880++){
             ivar_3 = (uint8_t)index33880;
             ivar_1->elems[index33880] = (ltedpeg__prepeg_adt_t)ltedpegtest__djson((uint8_t)ivar_3);
        };
        //copying to ltedpegtest_array_0 from ltedpegtest_array_0;
        result = (ltedpegtest_array_0_t)ivar_1;
        if (result != NULL) result->count++;
        release_ltedpegtest_array_0((ltedpegtest_array_0_t)ivar_1);
        defined = true;};
        
        
        return result;
}

ltedpeg__ent_adt_t ltedpegtest__jsonpureparsefile(bytestrings__bytestring_t ivar_1){
        ltedpeg__ent_adt_t  result;

        /* lf */ file__lifted_file_adt_t ivar_2;
        ivar_2 = (file__lifted_file_adt_t)file__open((bytestrings__bytestring_t)ivar_1);
        bool_t ivar_6;
        ivar_2->count++;
        ivar_6 = (bool_t)rec_file__passp((file__lifted_file_adt_t)ivar_2);
        if (ivar_6){
             /* f */ file__file_t ivar_10;
             ivar_10 = (file__file_t)acc_file__lifted_file_adt_contents((file__lifted_file_adt_t)ivar_2);
             /* fs */ uint32_t ivar_14;
             ivar_10->count++;
             ivar_14 = (uint32_t)file__file_size((file__file_t)ivar_10);
             /* fstr */ bytestrings__bytestring_t ivar_18;
             uint8_t ivar_36;
             ivar_36 = (uint8_t)0;
             uint32_t ivar_24;
             //copying to uint32 from uint8;
             ivar_24 = (uint32_t)ivar_36;
             ivar_18 = (bytestrings__bytestring_t)file__getbytestring((file__file_t)ivar_10, (uint32_t)ivar_24, (uint32_t)ivar_14);
             /* pend */ ltedpegtest_funtype_1_t ivar_37;
             ltedpegtest_closure_2_t cl33901;
             cl33901 = new_ltedpegtest_closure_2();
             ivar_37 = (ltedpegtest_funtype_1_t)cl33901;
             /* St */ ltedpegtest_record_5_t ivar_41;
             ltedpegtest_array_4_t ivar_74;
             uint8_t ivar_65;
             ivar_65 = (uint8_t)0;
             uint32_t ivar_69;
             ivar_69 = (uint32_t)0;
             ltedpeg__ent_adt_t ivar_54;
             uint8_t ivar_61;
             ivar_61 = (uint8_t)0;
             uint32_t ivar_58;
             //copying to uint32 from uint8;
             ivar_58 = (uint32_t)ivar_61;
             uint8_t ivar_59;
             ivar_59 = (uint8_t)ltedpeg__num_non_terminals();
             ivar_54 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_58, (uint8_t)ivar_59);
             ltedpegtest_array_4_t ivar_62;
             uint32_t size33904;
             size33904 = (uint32_t)ivar_18->length;
             size33904 += 1;
             ivar_62 = new_ltedpegtest_array_4(size33904);
             uint32_t ivar_49;
             for (uint32_t index33902 = 0; index33902 < size33904; index33902++){
           ivar_49 = (uint32_t)index33902;
           ltedpegtest_array_3_t ivar_51;
           //copying to ltedpegtest_array_3 from ltedpegtest_funtype_1;
           uint32_t tmp33903;
           tmp33903 = (uint32_t)255;
           ivar_51 = new_ltedpegtest_array_3(tmp33903);
           for (uint32_t index_129 = 0; index_129 < tmp33903; index_129++){
           ivar_51->elems[index_129] = (ltedpeg__ent_adt_t)ivar_37->ftbl->fptr(ivar_37, index_129);
           if (ivar_51->elems[index_129] != NULL) ivar_51->elems[index_129]->count++;
           };
           //copying to ltedpegtest_array_3 from ltedpegtest_array_3;
           ivar_62->elems[index33902] = (ltedpegtest_array_3_t)ivar_51;
           if (ivar_62->elems[index33902] != NULL) ivar_62->elems[index33902]->count++;
           release_ltedpegtest_array_3((ltedpegtest_array_3_t)ivar_51);
             };
             release_ltedpegtest_funtype_1((ltedpegtest_funtype_1_t)ivar_37);
             ltedpegtest_array_4_t ivar_73;
             ltedpegtest_array_3_t ivar_63;
             ivar_63 = (ltedpegtest_array_3_t)ivar_62->elems[ivar_69];
             ivar_63->count++;
             ltedpegtest_array_4_t ivar_70;
             ltedpegtest_array_3_t ivar_72;
             ivar_72 = NULL;
             ivar_70 = (ltedpegtest_array_4_t)update_ltedpegtest_array_4(ivar_62, ivar_69, ivar_72);
             if (ivar_72 != NULL) ivar_72->count--;
             ltedpegtest_array_3_t ivar_71;
             ltedpegtest_array_3_t ivar_66;
             ltedpeg__ent_adt_t ivar_68;
             ivar_68 = NULL;
             ivar_66 = (ltedpegtest_array_3_t)update_ltedpegtest_array_3(ivar_63, ivar_65, ivar_68);
             if (ivar_68 != NULL) ivar_68->count--;
             ivar_71 = (ltedpegtest_array_3_t)update_ltedpegtest_array_3(ivar_66, ivar_65, ivar_54);
             if (ivar_54 != NULL) ivar_54->count--;
             ivar_73 = (ltedpegtest_array_4_t)update_ltedpegtest_array_4(ivar_70, ivar_69, ivar_71);
             if (ivar_71 != NULL) ivar_71->count--;
             //copying to ltedpegtest_array_4 from ltedpegtest_array_4;
             ivar_74 = (ltedpegtest_array_4_t)ivar_73;
             if (ivar_74 != NULL) ivar_74->count++;
             release_ltedpegtest_array_4((ltedpegtest_array_4_t)ivar_73);
             uint64_t ivar_77;
             ivar_77 = (uint64_t)1;
             ltedpeg__ent_adt_t ivar_85;
             uint8_t ivar_84;
             ivar_84 = (uint8_t)0;
             uint32_t ivar_81;
             //copying to uint32 from uint8;
             ivar_81 = (uint32_t)ivar_84;
             uint8_t ivar_82;
             ivar_82 = (uint8_t)0;
             ivar_85 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_81, (uint8_t)ivar_82);
             bool_t ivar_86;
             ivar_86 = (bool_t) false;
             ltedpegtest_record_5_t tmp33905 = new_ltedpegtest_record_5();;
             ivar_41 = (ltedpegtest_record_5_t)tmp33905;
             tmp33905->scaf = (ltedpegtest_array_4_t)ivar_74;
             tmp33905->depth = (uint64_t)ivar_77;
             tmp33905->stack = (ltedpeg__ent_adt_t)ivar_85;
             tmp33905->lflag = (bool_t)ivar_86;
             ltedpegtest_array_3_t ivar_89;
             ltedpegtest_array_4_t ivar_94;
             ltedpegtest_record_5_t ivar_117;
             ltedpeg__lang_spec_t ivar_103;
             ivar_103 = (ltedpeg__lang_spec_t)ltedpegtest__djsontable();
             if (ivar_103 != NULL) ivar_103->count++;
             uint8_t ivar_112;
             ivar_112 = (uint8_t)0;
             uint32_t ivar_105;
             //copying to uint32 from uint8;
             ivar_105 = (uint32_t)ivar_112;
             uint8_t ivar_107;
             ivar_107 = (uint8_t)0;
             ivar_117 = (ltedpegtest_record_5_t)ltedpeg__parse((ltedpeg__lang_spec_t)ivar_103, (bytestrings__bytestring_t)ivar_18, (uint32_t)ivar_105, (uint8_t)ivar_107, (ltedpeg__state_t)ivar_41);
             ltedpegtest_array_4_t ivar_121;
             ivar_121 = (ltedpegtest_array_4_t)ivar_117->scaf;
             ivar_121->count++;
             release_ltedpegtest_record_5((ltedpegtest_record_5_t)ivar_117);
             //copying to ltedpegtest_array_4 from ltedpegtest_array_4;
             ivar_94 = (ltedpegtest_array_4_t)ivar_121;
             if (ivar_94 != NULL) ivar_94->count++;
             release_ltedpegtest_array_4((ltedpegtest_array_4_t)ivar_121);
             uint32_t ivar_122;
             ivar_122 = (uint32_t)0;
             ltedpegtest_array_3_t ivar_91;
             ivar_91 = (ltedpegtest_array_3_t)ivar_94->elems[ivar_122];
             ivar_91->count++;
             release_ltedpegtest_array_4((ltedpegtest_array_4_t)ivar_94);
             //copying to ltedpegtest_array_3 from ltedpegtest_array_3;
             ivar_89 = (ltedpegtest_array_3_t)ivar_91;
             if (ivar_89 != NULL) ivar_89->count++;
             release_ltedpegtest_array_3((ltedpegtest_array_3_t)ivar_91);
             uint8_t ivar_123;
             ivar_123 = (uint8_t)0;
             result = (ltedpeg__ent_adt_t)ivar_89->elems[ivar_123];
             result->count++;
             release_ltedpegtest_array_3((ltedpegtest_array_3_t)ivar_89);
        } else {
             release_file__lifted_file_adt((file__lifted_file_adt_t)ivar_2);
             uint8_t ivar_128;
             ivar_128 = (uint8_t)0;
             uint64_t ivar_126;
             //copying to uint64 from uint8;
             ivar_126 = (uint64_t)ivar_128;
             result = (ltedpeg__ent_adt_t)con_ltedpeg__fail((uint64_t)ivar_126);};
        
        
        return result;
}

bool_t ltedpegtest__jsonpureparsefile_test1(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        ltedpeg__ent_adt_t ivar_10;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len33909 = 10;
        uint32_t characters33910[10] = {116, 101, 115, 116, 49, 46, 106, 115, 111, 110};
        stringliteral_t string33908 = mk_string(10, characters33910);
        ivar_6 = (strings__string_t)strings__make_string(len33909, string33908);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_10 = (ltedpeg__ent_adt_t)ltedpegtest__jsonpureparsefile((bytestrings__bytestring_t)ivar_8);
        result = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_10);
        defined = true;};
        
        
        return result;
}

bool_t ltedpegtest__jsonpureparsefile_test2(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        ltedpeg__ent_adt_t ivar_10;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len33914 = 10;
        uint32_t characters33915[10] = {116, 101, 115, 116, 50, 46, 106, 115, 111, 110};
        stringliteral_t string33913 = mk_string(10, characters33915);
        ivar_6 = (strings__string_t)strings__make_string(len33914, string33913);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_10 = (ltedpeg__ent_adt_t)ltedpegtest__jsonpureparsefile((bytestrings__bytestring_t)ivar_8);
        result = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_10);
        defined = true;};
        
        
        return result;
}

bool_t ltedpegtest__jsonpureparsefile_test3(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        ltedpeg__ent_adt_t ivar_10;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len33919 = 10;
        uint32_t characters33920[10] = {116, 101, 115, 116, 51, 46, 106, 115, 111, 110};
        stringliteral_t string33918 = mk_string(10, characters33920);
        ivar_6 = (strings__string_t)strings__make_string(len33919, string33918);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_10 = (ltedpeg__ent_adt_t)ltedpegtest__jsonpureparsefile((bytestrings__bytestring_t)ivar_8);
        result = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_10);
        defined = true;};
        
        
        return result;
}

bool_t ltedpegtest__jsonpureparsefile_test_irModel(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        ltedpeg__ent_adt_t ivar_10;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len33924 = 12;
        uint32_t characters33925[12] = {105, 114, 77, 111, 100, 101, 108, 46, 106, 115, 111, 110};
        stringliteral_t string33923 = mk_string(12, characters33925);
        ivar_6 = (strings__string_t)strings__make_string(len33924, string33923);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_10 = (ltedpeg__ent_adt_t)ltedpegtest__jsonpureparsefile((bytestrings__bytestring_t)ivar_8);
        result = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_10);
        defined = true;};
        
        
        return result;
}

bool_t ltedpegtest__jsonpureparsefile_test_prelude(void){
        bool_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        ltedpeg__ent_adt_t ivar_10;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len33929 = 18;
        uint32_t characters33930[18] = {112, 114, 101, 108, 117, 100, 101, 46, 99, 97, 99, 104, 101, 46, 106, 115, 111, 110};
        stringliteral_t string33928 = mk_string(18, characters33930);
        ivar_6 = (strings__string_t)strings__make_string(len33929, string33928);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_10 = (ltedpeg__ent_adt_t)ltedpegtest__jsonpureparsefile((bytestrings__bytestring_t)ivar_8);
        result = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_10);
        defined = true;};
        
        
        return result;
}
