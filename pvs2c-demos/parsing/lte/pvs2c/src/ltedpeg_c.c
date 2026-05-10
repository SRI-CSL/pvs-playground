//Code generated using pvs2ir2c
#include "ltedpeg_c.h"



ltedpeg__strings_t new_ltedpeg__strings(uint32_t size){
        ltedpeg__strings_t tmp = (ltedpeg__strings_t) safe_malloc(sizeof(struct ltedpeg__strings_s) + (size * sizeof(uint8_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_ltedpeg__strings(ltedpeg__strings_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_ltedpeg__strings_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__strings((ltedpeg__strings_t)x);
}

ltedpeg__strings_t copy_ltedpeg__strings(ltedpeg__strings_t x){
        ltedpeg__strings_t tmp = new_ltedpeg__strings(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = (uint8_t)x->elems[i];};
         return tmp;}

bool_t equal_ltedpeg__strings(ltedpeg__strings_t x, ltedpeg__strings_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

char * json_ltedpeg__strings(ltedpeg__strings_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_uint8(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpeg__strings_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpeg__strings((ltedpeg__strings_t)x, (ltedpeg__strings_t)y);
}

char * json_ltedpeg__strings_ptr(pointer_t x, type_actual_t T){
        return json_ltedpeg__strings((ltedpeg__strings_t)x);
}

actual_ltedpeg__strings_t actual_ltedpeg__strings(void){
        actual_ltedpeg__strings_t new = (actual_ltedpeg__strings_t)safe_malloc(sizeof(struct actual_ltedpeg__strings_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__strings_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__strings_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__strings_ptr);
 

 
        return new;
 }

ltedpeg__strings_t update_ltedpeg__strings(ltedpeg__strings_t x, uint32_t i, uint8_t v){
        ltedpeg__strings_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_ltedpeg__strings(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}

ltedpeg__strings_t upgrade_ltedpeg__strings(ltedpeg__strings_t x, uint32_t i, uint8_t v){
        ltedpeg__strings_t y;
        uint32_t xmax = x->max;
         if (x->count == 1 && i < xmax){y = x;}
           else if (i >= xmax){uint32_t newmax = ((xmax < UINT32_MAX/2) ? ((i < 2 * (xmax + 1)) ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                y = safe_realloc(x, sizeof(struct ltedpeg__strings_s) + (newmax * sizeof(uint8_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;}
           else {y = copy_ltedpeg__strings(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}




ltedpeg__ent_adt_t new_ltedpeg__ent_adt(void){
        ltedpeg__ent_adt_t tmp = (ltedpeg__ent_adt_t) safe_malloc(sizeof(struct ltedpeg__ent_adt_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__ent_adt(ltedpeg__ent_adt_t x){
switch (x->ltedpeg__ent_adt_index) {
case 0:  release_ltedpeg__fail((ltedpeg__fail_t)x); break;
case 3:  release_ltedpeg__good((ltedpeg__good_t)x); break;
case 4:  release_ltedpeg__push((ltedpeg__push_t)x); break;
}}

void release_ltedpeg__ent_adt_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x);
}

ltedpeg__ent_adt_t copy_ltedpeg__ent_adt(ltedpeg__ent_adt_t x){
        ltedpeg__ent_adt_t y = new_ltedpeg__ent_adt();
        y->ltedpeg__ent_adt_index = (uint8_t)x->ltedpeg__ent_adt_index;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__ent_adt(ltedpeg__ent_adt_t x, ltedpeg__ent_adt_t y){
        bool_t tmp = x->ltedpeg__ent_adt_index == y->ltedpeg__ent_adt_index;
        switch  (x->ltedpeg__ent_adt_index) {
                case 0: tmp = tmp && equal_ltedpeg__fail((ltedpeg__fail_t)x, (ltedpeg__fail_t)y); break;
                case 3: tmp = tmp && equal_ltedpeg__good((ltedpeg__good_t)x, (ltedpeg__good_t)y); break;
                case 4: tmp = tmp && equal_ltedpeg__push((ltedpeg__push_t)x, (ltedpeg__push_t)y); break;
        }
        return tmp;
}

char * json_ltedpeg__ent_adt(ltedpeg__ent_adt_t x){
        char * tmp = safe_malloc(24); sprintf(tmp, "{ \"constructor\": %u,", x->ltedpeg__ent_adt_index); tmp = safe_strcat(tmp, " \"value\": ");
        switch  (x->ltedpeg__ent_adt_index) {
                case 0: tmp = safe_strcat(tmp, json_ltedpeg__fail((ltedpeg__fail_t)x)); break;
                case 3: tmp = safe_strcat(tmp, json_ltedpeg__good((ltedpeg__good_t)x)); break;
                case 4: tmp = safe_strcat(tmp, json_ltedpeg__push((ltedpeg__push_t)x)); break;
                default: tmp = safe_strcat(tmp, "null");
        };
        tmp = safe_strcat(tmp, " }");
        return tmp;
}

bool_t equal_ltedpeg__ent_adt_ptr(pointer_t x, pointer_t y, actual_ltedpeg__ent_adt_t T){
        return equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x, (ltedpeg__ent_adt_t)y);
}

char * json_ltedpeg__ent_adt_ptr(pointer_t x, actual_ltedpeg__ent_adt_t T){
        return json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x);
}

actual_ltedpeg__ent_adt_t actual_ltedpeg__ent_adt(void){
        actual_ltedpeg__ent_adt_t new = (actual_ltedpeg__ent_adt_t)safe_malloc(sizeof(struct actual_ltedpeg__ent_adt_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__ent_adt_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__ent_adt_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__ent_adt_ptr);
 

 
        return new;
 }

ltedpeg__ent_adt_t update_ltedpeg__ent_adt_ltedpeg__ent_adt_index(ltedpeg__ent_adt_t x, uint8_t v){
        ltedpeg__ent_adt_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__ent_adt(x); x->count--;};
        y->ltedpeg__ent_adt_index = (uint8_t)v;
        return y;}




ltedpeg__fail_t new_ltedpeg__fail(void){
        ltedpeg__fail_t tmp = (ltedpeg__fail_t) safe_malloc(sizeof(struct ltedpeg__fail_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__fail(ltedpeg__fail_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__fail_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__fail((ltedpeg__fail_t)x);
}

ltedpeg__fail_t copy_ltedpeg__fail(ltedpeg__fail_t x){
        ltedpeg__fail_t y = new_ltedpeg__fail();
        y->ltedpeg__ent_adt_index = (uint8_t)x->ltedpeg__ent_adt_index;
        y->dep = (uint64_t)x->dep;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__fail(ltedpeg__fail_t x, ltedpeg__fail_t y){
        bool_t tmp = true; tmp = tmp && x->ltedpeg__ent_adt_index == y->ltedpeg__ent_adt_index; tmp = tmp && x->dep == y->dep;
        return tmp;}

char * json_ltedpeg__fail(ltedpeg__fail_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(34);
         sprintf(fld0, "\"ltedpeg__ent_adt_index\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->ltedpeg__ent_adt_index));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"dep\" : ");
        tmp[1] = safe_strcat(fld1, json_uint64(x->dep));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg__fail_ptr(pointer_t x, pointer_t y, actual_ltedpeg__fail_t T){
        return equal_ltedpeg__fail((ltedpeg__fail_t)x, (ltedpeg__fail_t)y);
}

char * json_ltedpeg__fail_ptr(pointer_t x, actual_ltedpeg__fail_t T){
        return json_ltedpeg__fail((ltedpeg__fail_t)x);
}

actual_ltedpeg__fail_t actual_ltedpeg__fail(void){
        actual_ltedpeg__fail_t new = (actual_ltedpeg__fail_t)safe_malloc(sizeof(struct actual_ltedpeg__fail_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__fail_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__fail_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__fail_ptr);
 

 
        return new;
 }

ltedpeg__fail_t update_ltedpeg__fail_ltedpeg__ent_adt_index(ltedpeg__fail_t x, uint8_t v){
        ltedpeg__fail_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__fail(x); x->count--;};
        y->ltedpeg__ent_adt_index = (uint8_t)v;
        return y;}

ltedpeg__fail_t update_ltedpeg__fail_dep(ltedpeg__fail_t x, uint64_t v){
        ltedpeg__fail_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__fail(x); x->count--;};
        y->dep = (uint64_t)v;
        return y;}




ltedpeg__good_t new_ltedpeg__good(void){
        ltedpeg__good_t tmp = (ltedpeg__good_t) safe_malloc(sizeof(struct ltedpeg__good_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__good(ltedpeg__good_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__good_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__good((ltedpeg__good_t)x);
}

ltedpeg__good_t copy_ltedpeg__good(ltedpeg__good_t x){
        ltedpeg__good_t y = new_ltedpeg__good();
        y->ltedpeg__ent_adt_index = (uint8_t)x->ltedpeg__ent_adt_index;
        y->dep = (uint64_t)x->dep;
        y->span = (uint32_t)x->span;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__good(ltedpeg__good_t x, ltedpeg__good_t y){
        bool_t tmp = true; tmp = tmp && x->ltedpeg__ent_adt_index == y->ltedpeg__ent_adt_index; tmp = tmp && x->dep == y->dep; tmp = tmp && x->span == y->span;
        return tmp;}

char * json_ltedpeg__good(ltedpeg__good_t x){
        char * tmp[3]; 
        char * fld0 = safe_malloc(34);
         sprintf(fld0, "\"ltedpeg__ent_adt_index\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->ltedpeg__ent_adt_index));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"dep\" : ");
        tmp[1] = safe_strcat(fld1, json_uint64(x->dep));
        char * fld2 = safe_malloc(16);
         sprintf(fld2, "\"span\" : ");
        tmp[2] = safe_strcat(fld2, json_uint32(x->span));
         char * result = json_list_with_sep(tmp, 3,  '{', ',', '}');
         for (uint32_t i = 0; i < 3; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg__good_ptr(pointer_t x, pointer_t y, actual_ltedpeg__good_t T){
        return equal_ltedpeg__good((ltedpeg__good_t)x, (ltedpeg__good_t)y);
}

char * json_ltedpeg__good_ptr(pointer_t x, actual_ltedpeg__good_t T){
        return json_ltedpeg__good((ltedpeg__good_t)x);
}

actual_ltedpeg__good_t actual_ltedpeg__good(void){
        actual_ltedpeg__good_t new = (actual_ltedpeg__good_t)safe_malloc(sizeof(struct actual_ltedpeg__good_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__good_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__good_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__good_ptr);
 

 
        return new;
 }

ltedpeg__good_t update_ltedpeg__good_ltedpeg__ent_adt_index(ltedpeg__good_t x, uint8_t v){
        ltedpeg__good_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__good(x); x->count--;};
        y->ltedpeg__ent_adt_index = (uint8_t)v;
        return y;}

ltedpeg__good_t update_ltedpeg__good_dep(ltedpeg__good_t x, uint64_t v){
        ltedpeg__good_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__good(x); x->count--;};
        y->dep = (uint64_t)v;
        return y;}

ltedpeg__good_t update_ltedpeg__good_span(ltedpeg__good_t x, uint32_t v){
        ltedpeg__good_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__good(x); x->count--;};
        y->span = (uint32_t)v;
        return y;}




ltedpeg__push_t new_ltedpeg__push(void){
        ltedpeg__push_t tmp = (ltedpeg__push_t) safe_malloc(sizeof(struct ltedpeg__push_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__push(ltedpeg__push_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__push_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__push((ltedpeg__push_t)x);
}

ltedpeg__push_t copy_ltedpeg__push(ltedpeg__push_t x){
        ltedpeg__push_t y = new_ltedpeg__push();
        y->ltedpeg__ent_adt_index = (uint8_t)x->ltedpeg__ent_adt_index;
        y->pos = (uint32_t)x->pos;
        y->nt = (uint8_t)x->nt;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__push(ltedpeg__push_t x, ltedpeg__push_t y){
        bool_t tmp = true; tmp = tmp && x->ltedpeg__ent_adt_index == y->ltedpeg__ent_adt_index; tmp = tmp && x->pos == y->pos; tmp = tmp && x->nt == y->nt;
        return tmp;}

char * json_ltedpeg__push(ltedpeg__push_t x){
        char * tmp[3]; 
        char * fld0 = safe_malloc(34);
         sprintf(fld0, "\"ltedpeg__ent_adt_index\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->ltedpeg__ent_adt_index));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"pos\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->pos));
        char * fld2 = safe_malloc(14);
         sprintf(fld2, "\"nt\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->nt));
         char * result = json_list_with_sep(tmp, 3,  '{', ',', '}');
         for (uint32_t i = 0; i < 3; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg__push_ptr(pointer_t x, pointer_t y, actual_ltedpeg__push_t T){
        return equal_ltedpeg__push((ltedpeg__push_t)x, (ltedpeg__push_t)y);
}

char * json_ltedpeg__push_ptr(pointer_t x, actual_ltedpeg__push_t T){
        return json_ltedpeg__push((ltedpeg__push_t)x);
}

actual_ltedpeg__push_t actual_ltedpeg__push(void){
        actual_ltedpeg__push_t new = (actual_ltedpeg__push_t)safe_malloc(sizeof(struct actual_ltedpeg__push_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__push_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__push_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__push_ptr);
 

 
        return new;
 }

ltedpeg__push_t update_ltedpeg__push_ltedpeg__ent_adt_index(ltedpeg__push_t x, uint8_t v){
        ltedpeg__push_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__push(x); x->count--;};
        y->ltedpeg__ent_adt_index = (uint8_t)v;
        return y;}

ltedpeg__push_t update_ltedpeg__push_pos(ltedpeg__push_t x, uint32_t v){
        ltedpeg__push_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__push(x); x->count--;};
        y->pos = (uint32_t)v;
        return y;}

ltedpeg__push_t update_ltedpeg__push_nt(ltedpeg__push_t x, uint8_t v){
        ltedpeg__push_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__push(x); x->count--;};
        y->nt = (uint8_t)v;
        return y;}



void release_ltedpeg_funtype_5(ltedpeg_funtype_5_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_5_t copy_ltedpeg_funtype_5(ltedpeg_funtype_5_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_5(ltedpeg_funtype_5_t x, ltedpeg_funtype_5_t y){
        return false;}

char* json_ltedpeg_funtype_5(ltedpeg_funtype_5_t x){char * result = safe_malloc(27); sprintf(result, "%s", "\"ltedpeg_funtype_5\""); return result;}

void release_ltedpeg_funtype_6(ltedpeg_funtype_6_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_6_t copy_ltedpeg_funtype_6(ltedpeg_funtype_6_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_6(ltedpeg_funtype_6_htbl_t htbl, uint64_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_6_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_6_t dupdate_ltedpeg_funtype_6(ltedpeg_funtype_6_t a, uint64_t i, mpz_ptr_t v){
        ltedpeg_funtype_6_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_6_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_6_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_6_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_6_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint64_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_6_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_6_hashentry_t * new_data = (ltedpeg_funtype_6_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_6_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = (uint64_t)0; 
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
                                new_data[new_loc].key = (uint64_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                mpz_set(new_data[new_loc].value, data[j].value);
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                for (uint32_t j=0; j < size; j++){mpz_clear(data[j].value);};
                safe_free(data);}
        uint32_t ihash = uint64_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_6(htbl, i, ihash);
        ltedpeg_funtype_6_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint64_t)i; htbl->data[hashindex].keyhash = ihash; mpz_set(htbl->data[hashindex].value, v); htbl->num_entries++;}
            else {mpz_set(htbl->data[hashindex].value, v);};
        return a;

}

ltedpeg_funtype_6_t update_ltedpeg_funtype_6(ltedpeg_funtype_6_t a, uint64_t i, mpz_ptr_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_6(a, i, v);
            } else {
                ltedpeg_funtype_6_t x = copy_ltedpeg_funtype_6(a);
                a->count--;
                return dupdate_ltedpeg_funtype_6(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_6(ltedpeg_funtype_6_t x, ltedpeg_funtype_6_t y){
        return false;}

char* json_ltedpeg_funtype_6(ltedpeg_funtype_6_t x){char * result = safe_malloc(27); sprintf(result, "%s", "\"ltedpeg_funtype_6\""); return result;}


ltedpeg_record_7_t new_ltedpeg_record_7(void){
        ltedpeg_record_7_t tmp = (ltedpeg_record_7_t) safe_malloc(sizeof(struct ltedpeg_record_7_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_7(ltedpeg_record_7_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_7_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_7((ltedpeg_record_7_t)x);
}

ltedpeg_record_7_t copy_ltedpeg_record_7(ltedpeg_record_7_t x){
        ltedpeg_record_7_t y = new_ltedpeg_record_7();
        y->project_1 = (uint64_t)x->project_1;
        y->project_2 = (uint32_t)x->project_2;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_7(ltedpeg_record_7_t x, ltedpeg_record_7_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && x->project_2 == y->project_2;
        return tmp;}

char * json_ltedpeg_record_7(ltedpeg_record_7_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint64(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->project_2));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_7_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_7_t T){
        return equal_ltedpeg_record_7((ltedpeg_record_7_t)x, (ltedpeg_record_7_t)y);
}

char * json_ltedpeg_record_7_ptr(pointer_t x, actual_ltedpeg_record_7_t T){
        return json_ltedpeg_record_7((ltedpeg_record_7_t)x);
}

actual_ltedpeg_record_7_t actual_ltedpeg_record_7(void){
        actual_ltedpeg_record_7_t new = (actual_ltedpeg_record_7_t)safe_malloc(sizeof(struct actual_ltedpeg_record_7_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_7_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_7_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_7_ptr);
 

 
        return new;
 }

ltedpeg_record_7_t update_ltedpeg_record_7_project_1(ltedpeg_record_7_t x, uint64_t v){
        ltedpeg_record_7_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_7(x); x->count--;};
        y->project_1 = (uint64_t)v;
        return y;}

ltedpeg_record_7_t update_ltedpeg_record_7_project_2(ltedpeg_record_7_t x, uint32_t v){
        ltedpeg_record_7_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_7(x); x->count--;};
        y->project_2 = (uint32_t)v;
        return y;}



void release_ltedpeg_funtype_8(ltedpeg_funtype_8_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_8_t copy_ltedpeg_funtype_8(ltedpeg_funtype_8_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_8(ltedpeg_funtype_8_t x, ltedpeg_funtype_8_t y){
        return false;}

char* json_ltedpeg_funtype_8(ltedpeg_funtype_8_t x){char * result = safe_malloc(27); sprintf(result, "%s", "\"ltedpeg_funtype_8\""); return result;}


ltedpeg_record_9_t new_ltedpeg_record_9(void){
        ltedpeg_record_9_t tmp = (ltedpeg_record_9_t) safe_malloc(sizeof(struct ltedpeg_record_9_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_9(ltedpeg_record_9_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_9_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_9((ltedpeg_record_9_t)x);
}

ltedpeg_record_9_t copy_ltedpeg_record_9(ltedpeg_record_9_t x){
        ltedpeg_record_9_t y = new_ltedpeg_record_9();
        y->project_1 = (uint32_t)x->project_1;
        y->project_2 = (uint8_t)x->project_2;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_9(ltedpeg_record_9_t x, ltedpeg_record_9_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && x->project_2 == y->project_2;
        return tmp;}

char * json_ltedpeg_record_9(ltedpeg_record_9_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint32(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint8(x->project_2));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_9_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_9_t T){
        return equal_ltedpeg_record_9((ltedpeg_record_9_t)x, (ltedpeg_record_9_t)y);
}

char * json_ltedpeg_record_9_ptr(pointer_t x, actual_ltedpeg_record_9_t T){
        return json_ltedpeg_record_9((ltedpeg_record_9_t)x);
}

actual_ltedpeg_record_9_t actual_ltedpeg_record_9(void){
        actual_ltedpeg_record_9_t new = (actual_ltedpeg_record_9_t)safe_malloc(sizeof(struct actual_ltedpeg_record_9_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_9_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_9_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_9_ptr);
 

 
        return new;
 }

ltedpeg_record_9_t update_ltedpeg_record_9_project_1(ltedpeg_record_9_t x, uint32_t v){
        ltedpeg_record_9_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_9(x); x->count--;};
        y->project_1 = (uint32_t)v;
        return y;}

ltedpeg_record_9_t update_ltedpeg_record_9_project_2(ltedpeg_record_9_t x, uint8_t v){
        ltedpeg_record_9_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_9(x); x->count--;};
        y->project_2 = (uint8_t)v;
        return y;}



void release_ltedpeg_funtype_10(ltedpeg_funtype_10_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_10_t copy_ltedpeg_funtype_10(ltedpeg_funtype_10_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_10(ltedpeg_funtype_10_t x, ltedpeg_funtype_10_t y){
        return false;}

char* json_ltedpeg_funtype_10(ltedpeg_funtype_10_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_10\""); return result;}


mpz_ptr_t f_ltedpeg_closure_11(struct ltedpeg_closure_11_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_6_t fvar_1 = closure->fvar_1;
        mpz_ptr_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_8_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_10_t fvar_4 = closure->fvar_4;
        mpz_ptr_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_3->count++;
        fvar_4->count++;
        release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)closure);
        mpz_ptr_t result;
        result = (mpz_ptr_t)h_ltedpeg_closure_11(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

mpz_ptr_t m_ltedpeg_closure_11(struct ltedpeg_closure_11_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_6_t fvar_1 = closure->fvar_1;
        mpz_ptr_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_8_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_10_t fvar_4 = closure->fvar_4;
        mpz_ptr_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_3->count++;
        fvar_4->count++;
        release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)closure);
        return h_ltedpeg_closure_11(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

mpz_ptr_t h_ltedpeg_closure_11(ltedpeg__ent_adt_t ivar_11, ltedpeg_funtype_6_t ivar_1, mpz_ptr_t ivar_4, ltedpeg_funtype_8_t ivar_5, ltedpeg_funtype_10_t ivar_7, mpz_ptr_t ivar_3){
        mpz_ptr_t result;

        bool_t ivar_40;
        ivar_11->count++;
        ivar_40 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_11);
        if (ivar_40){
             uint64_t ivar_30;
             ivar_30 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_11);
             ivar_1->count++;
             mpz_mk_set(result, ivar_1->ftbl->fptr(ivar_1, ivar_30));
        } else {
             bool_t ivar_44;
             ivar_11->count++;
             ivar_44 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_11);
             if (ivar_44){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_11);
           //copying to mpz from mpz;
           mpz_mk_set(result, ivar_3);
             } else {
           bool_t ivar_48;
           ivar_11->count++;
           ivar_48 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_11);
           if (ivar_48){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_11);
           //copying to mpz from mpz;
           mpz_mk_set(result, ivar_4);
           } else {
           bool_t ivar_68;
           ivar_11->count++;
           ivar_68 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_11);
           if (ivar_68){
            uint64_t ivar_52;
            ivar_11->count++;
            ivar_52 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_11);
            uint32_t ivar_53;
            ivar_53 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_11);
            ivar_5->count++;
            mpz_mk_set(result, ivar_5->ftbl->mptr(ivar_5, ivar_52, ivar_53));
           } else {
            uint32_t ivar_72;
            ivar_11->count++;
            ivar_72 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_11);
            uint8_t ivar_73;
            ivar_73 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_11);
            ivar_7->count++;
            mpz_mk_set(result, ivar_7->ftbl->mptr(ivar_7, ivar_72, ivar_73));};};};};
        return result;
}

ltedpeg_closure_11_t new_ltedpeg_closure_11(void){
        static struct ltedpeg_funtype_5_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ltedpeg_funtype_5_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_11, .mptr = (mpz_ptr_t (*)(ltedpeg_funtype_5_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_11, .rptr =  (void (*)(ltedpeg_funtype_5_t))&release_ltedpeg_closure_11, .cptr = (ltedpeg_funtype_5_t (*)(ltedpeg_funtype_5_t))&copy_ltedpeg_closure_11};
        ltedpeg_closure_11_t tmp = (ltedpeg_closure_11_t) safe_malloc(sizeof(struct ltedpeg_closure_11_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_2);
        mpz_init(tmp->fvar_5);
        return tmp;}

void release_ltedpeg_closure_11(ltedpeg_funtype_5_t closure){
        ltedpeg_closure_11_t x = (ltedpeg_closure_11_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_funtype_6((ltedpeg_funtype_6_t)x->fvar_1);
         mpz_clear(x->fvar_2);
         release_ltedpeg_funtype_8((ltedpeg_funtype_8_t)x->fvar_3);
         release_ltedpeg_funtype_10((ltedpeg_funtype_10_t)x->fvar_4);
         mpz_clear(x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_11_t copy_ltedpeg_closure_11(ltedpeg_closure_11_t x){
        ltedpeg_closure_11_t y = new_ltedpeg_closure_11();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        mpz_set(y->fvar_2, x->fvar_2);
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        mpz_set(y->fvar_5, x->fvar_5);
        if (x->htbl != NULL){
            ltedpeg_funtype_5_htbl_t new_htbl = (ltedpeg_funtype_5_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_5_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_5_hashentry_t * new_data = (ltedpeg_funtype_5_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_5_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  mpz_init(new_data[j].value); mpz_set(new_data[j].value, x->htbl->data[j].value);;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_12_t new_ltedpeg_record_12(void){
        ltedpeg_record_12_t tmp = (ltedpeg_record_12_t) safe_malloc(sizeof(struct ltedpeg_record_12_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_12(ltedpeg_record_12_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_12_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_12((ltedpeg_record_12_t)x);
}

ltedpeg_record_12_t copy_ltedpeg_record_12(ltedpeg_record_12_t x){
        ltedpeg_record_12_t y = new_ltedpeg_record_12();
        y->project_1 = (uint64_t)x->project_1;
        y->project_2 = x->project_2;
        if (y->project_2 != NULL){y->project_2->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_12(ltedpeg_record_12_t x, ltedpeg_record_12_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2, (ltedpeg__ent_adt_t)y->project_2);
        return tmp;}

char * json_ltedpeg_record_12(ltedpeg_record_12_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint64(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_12_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_12_t T){
        return equal_ltedpeg_record_12((ltedpeg_record_12_t)x, (ltedpeg_record_12_t)y);
}

char * json_ltedpeg_record_12_ptr(pointer_t x, actual_ltedpeg_record_12_t T){
        return json_ltedpeg_record_12((ltedpeg_record_12_t)x);
}

actual_ltedpeg_record_12_t actual_ltedpeg_record_12(void){
        actual_ltedpeg_record_12_t new = (actual_ltedpeg_record_12_t)safe_malloc(sizeof(struct actual_ltedpeg_record_12_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_12_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_12_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_12_ptr);
 

 
        return new;
 }

ltedpeg_record_12_t update_ltedpeg_record_12_project_1(ltedpeg_record_12_t x, uint64_t v){
        ltedpeg_record_12_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_12(x); x->count--;};
        y->project_1 = (uint64_t)v;
        return y;}

ltedpeg_record_12_t update_ltedpeg_record_12_project_2(ltedpeg_record_12_t x, ltedpeg__ent_adt_t v){
        ltedpeg_record_12_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_2 != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2);};}
        else {y = copy_ltedpeg_record_12(x); x->count--; y->project_2->count--;};
        y->project_2 = (ltedpeg__ent_adt_t)v;
        return y;}



void release_ltedpeg_funtype_13(ltedpeg_funtype_13_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_13_t copy_ltedpeg_funtype_13(ltedpeg_funtype_13_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_13(ltedpeg_funtype_13_t x, ltedpeg_funtype_13_t y){
        return false;}

char* json_ltedpeg_funtype_13(ltedpeg_funtype_13_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_13\""); return result;}


ltedpeg_record_14_t new_ltedpeg_record_14(void){
        ltedpeg_record_14_t tmp = (ltedpeg_record_14_t) safe_malloc(sizeof(struct ltedpeg_record_14_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_14(ltedpeg_record_14_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_14_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_14((ltedpeg_record_14_t)x);
}

ltedpeg_record_14_t copy_ltedpeg_record_14(ltedpeg_record_14_t x){
        ltedpeg_record_14_t y = new_ltedpeg_record_14();
        y->project_1 = (uint64_t)x->project_1;
        y->project_2 = (uint32_t)x->project_2;
        y->project_3 = x->project_3;
        if (y->project_3 != NULL){y->project_3->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_14(ltedpeg_record_14_t x, ltedpeg_record_14_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && x->project_2 == y->project_2; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3, (ltedpeg__ent_adt_t)y->project_3);
        return tmp;}

char * json_ltedpeg_record_14(ltedpeg_record_14_t x){
        char * tmp[3]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint64(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3));
         char * result = json_list_with_sep(tmp, 3,  '{', ',', '}');
         for (uint32_t i = 0; i < 3; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_14_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_14_t T){
        return equal_ltedpeg_record_14((ltedpeg_record_14_t)x, (ltedpeg_record_14_t)y);
}

char * json_ltedpeg_record_14_ptr(pointer_t x, actual_ltedpeg_record_14_t T){
        return json_ltedpeg_record_14((ltedpeg_record_14_t)x);
}

actual_ltedpeg_record_14_t actual_ltedpeg_record_14(void){
        actual_ltedpeg_record_14_t new = (actual_ltedpeg_record_14_t)safe_malloc(sizeof(struct actual_ltedpeg_record_14_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_14_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_14_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_14_ptr);
 

 
        return new;
 }

ltedpeg_record_14_t update_ltedpeg_record_14_project_1(ltedpeg_record_14_t x, uint64_t v){
        ltedpeg_record_14_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_14(x); x->count--;};
        y->project_1 = (uint64_t)v;
        return y;}

ltedpeg_record_14_t update_ltedpeg_record_14_project_2(ltedpeg_record_14_t x, uint32_t v){
        ltedpeg_record_14_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_14(x); x->count--;};
        y->project_2 = (uint32_t)v;
        return y;}

ltedpeg_record_14_t update_ltedpeg_record_14_project_3(ltedpeg_record_14_t x, ltedpeg__ent_adt_t v){
        ltedpeg_record_14_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_3 != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3);};}
        else {y = copy_ltedpeg_record_14(x); x->count--; y->project_3->count--;};
        y->project_3 = (ltedpeg__ent_adt_t)v;
        return y;}



void release_ltedpeg_funtype_15(ltedpeg_funtype_15_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_15_t copy_ltedpeg_funtype_15(ltedpeg_funtype_15_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_15(ltedpeg_funtype_15_t x, ltedpeg_funtype_15_t y){
        return false;}

char* json_ltedpeg_funtype_15(ltedpeg_funtype_15_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_15\""); return result;}


ltedpeg_record_16_t new_ltedpeg_record_16(void){
        ltedpeg_record_16_t tmp = (ltedpeg_record_16_t) safe_malloc(sizeof(struct ltedpeg_record_16_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_16(ltedpeg_record_16_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_16_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_16((ltedpeg_record_16_t)x);
}

ltedpeg_record_16_t copy_ltedpeg_record_16(ltedpeg_record_16_t x){
        ltedpeg_record_16_t y = new_ltedpeg_record_16();
        y->project_1 = (uint32_t)x->project_1;
        y->project_2 = (uint8_t)x->project_2;
        y->project_3 = x->project_3;
        if (y->project_3 != NULL){y->project_3->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_16(ltedpeg_record_16_t x, ltedpeg_record_16_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && x->project_2 == y->project_2; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3, (ltedpeg__ent_adt_t)y->project_3);
        return tmp;}

char * json_ltedpeg_record_16(ltedpeg_record_16_t x){
        char * tmp[3]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint32(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint8(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3));
         char * result = json_list_with_sep(tmp, 3,  '{', ',', '}');
         for (uint32_t i = 0; i < 3; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_16_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_16_t T){
        return equal_ltedpeg_record_16((ltedpeg_record_16_t)x, (ltedpeg_record_16_t)y);
}

char * json_ltedpeg_record_16_ptr(pointer_t x, actual_ltedpeg_record_16_t T){
        return json_ltedpeg_record_16((ltedpeg_record_16_t)x);
}

actual_ltedpeg_record_16_t actual_ltedpeg_record_16(void){
        actual_ltedpeg_record_16_t new = (actual_ltedpeg_record_16_t)safe_malloc(sizeof(struct actual_ltedpeg_record_16_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_16_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_16_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_16_ptr);
 

 
        return new;
 }

ltedpeg_record_16_t update_ltedpeg_record_16_project_1(ltedpeg_record_16_t x, uint32_t v){
        ltedpeg_record_16_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_16(x); x->count--;};
        y->project_1 = (uint32_t)v;
        return y;}

ltedpeg_record_16_t update_ltedpeg_record_16_project_2(ltedpeg_record_16_t x, uint8_t v){
        ltedpeg_record_16_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_16(x); x->count--;};
        y->project_2 = (uint8_t)v;
        return y;}

ltedpeg_record_16_t update_ltedpeg_record_16_project_3(ltedpeg_record_16_t x, ltedpeg__ent_adt_t v){
        ltedpeg_record_16_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_3 != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_3);};}
        else {y = copy_ltedpeg_record_16(x); x->count--; y->project_3->count--;};
        y->project_3 = (ltedpeg__ent_adt_t)v;
        return y;}



void release_ltedpeg_funtype_17(ltedpeg_funtype_17_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_17_t copy_ltedpeg_funtype_17(ltedpeg_funtype_17_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_17(ltedpeg_funtype_17_t x, ltedpeg_funtype_17_t y){
        return false;}

char* json_ltedpeg_funtype_17(ltedpeg_funtype_17_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_17\""); return result;}


mpz_ptr_t f_ltedpeg_closure_18(struct ltedpeg_closure_18_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_13_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_5_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_15_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_17_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_5_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)closure);
        mpz_ptr_t result;
        result = (mpz_ptr_t)h_ltedpeg_closure_18(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

mpz_ptr_t m_ltedpeg_closure_18(struct ltedpeg_closure_18_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_13_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_5_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_15_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_17_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_5_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)closure);
        return h_ltedpeg_closure_18(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

mpz_ptr_t h_ltedpeg_closure_18(ltedpeg__ent_adt_t ivar_13, ltedpeg_funtype_13_t ivar_1, ltedpeg_funtype_5_t ivar_5, ltedpeg_funtype_15_t ivar_7, ltedpeg_funtype_17_t ivar_9, ltedpeg_funtype_5_t ivar_3){
        mpz_ptr_t result;

        bool_t ivar_46;
        ivar_13->count++;
        ivar_46 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_13);
        if (ivar_46){
             uint64_t ivar_34;
             ivar_13->count++;
             ivar_34 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_13);
             ivar_1->count++;
             mpz_mk_set(result, ivar_1->ftbl->mptr(ivar_1, ivar_34, ivar_13));
        } else {
             bool_t ivar_56;
             ivar_13->count++;
             ivar_56 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_13);
             if (ivar_56){
           ivar_3->count++;
           mpz_mk_set(result, ivar_3->ftbl->fptr(ivar_3, ivar_13));
             } else {
           bool_t ivar_66;
           ivar_13->count++;
           ivar_66 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_13);
           if (ivar_66){
           ivar_5->count++;
           mpz_mk_set(result, ivar_5->ftbl->fptr(ivar_5, ivar_13));
           } else {
           bool_t ivar_88;
           ivar_13->count++;
           ivar_88 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_13);
           if (ivar_88){
            uint64_t ivar_70;
            ivar_13->count++;
            ivar_70 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_13);
            uint32_t ivar_71;
            ivar_13->count++;
            ivar_71 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_13);
            ivar_7->count++;
            mpz_mk_set(result, ivar_7->ftbl->mptr(ivar_7, ivar_70, ivar_71, ivar_13));
           } else {
            uint32_t ivar_92;
            ivar_13->count++;
            ivar_92 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_13);
            uint8_t ivar_93;
            ivar_13->count++;
            ivar_93 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_13);
            ivar_9->count++;
            mpz_mk_set(result, ivar_9->ftbl->mptr(ivar_9, ivar_92, ivar_93, ivar_13));};};};};
        return result;
}

ltedpeg_closure_18_t new_ltedpeg_closure_18(void){
        static struct ltedpeg_funtype_5_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ltedpeg_funtype_5_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_18, .mptr = (mpz_ptr_t (*)(ltedpeg_funtype_5_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_18, .rptr =  (void (*)(ltedpeg_funtype_5_t))&release_ltedpeg_closure_18, .cptr = (ltedpeg_funtype_5_t (*)(ltedpeg_funtype_5_t))&copy_ltedpeg_closure_18};
        ltedpeg_closure_18_t tmp = (ltedpeg_closure_18_t) safe_malloc(sizeof(struct ltedpeg_closure_18_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_18(ltedpeg_funtype_5_t closure){
        ltedpeg_closure_18_t x = (ltedpeg_closure_18_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_funtype_13((ltedpeg_funtype_13_t)x->fvar_1);
         release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)x->fvar_2);
         release_ltedpeg_funtype_15((ltedpeg_funtype_15_t)x->fvar_3);
         release_ltedpeg_funtype_17((ltedpeg_funtype_17_t)x->fvar_4);
         release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_18_t copy_ltedpeg_closure_18(ltedpeg_closure_18_t x){
        ltedpeg_closure_18_t y = new_ltedpeg_closure_18();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        y->fvar_5 = x->fvar_5; x->fvar_5->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_5_htbl_t new_htbl = (ltedpeg_funtype_5_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_5_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_5_hashentry_t * new_data = (ltedpeg_funtype_5_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_5_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  mpz_init(new_data[j].value); mpz_set(new_data[j].value, x->htbl->data[j].value);;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_19(ltedpeg_funtype_19_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_19_t copy_ltedpeg_funtype_19(ltedpeg_funtype_19_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_19(ltedpeg_funtype_19_t x, ltedpeg_funtype_19_t y){
        return false;}

char* json_ltedpeg_funtype_19(ltedpeg_funtype_19_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_19\""); return result;}

void release_ltedpeg_funtype_20(ltedpeg_funtype_20_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_20_t copy_ltedpeg_funtype_20(ltedpeg_funtype_20_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_20(ltedpeg_funtype_20_htbl_t htbl, uint64_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_20_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_20_t dupdate_ltedpeg_funtype_20(ltedpeg_funtype_20_t a, uint64_t i, ordstruct_adt__ordstruct_adt_t v){
        ltedpeg_funtype_20_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_20_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_20_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_20_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_20_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint64_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_20_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_20_hashentry_t * new_data = (ltedpeg_funtype_20_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_20_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = (uint64_t)0; 
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
                                new_data[new_loc].key = (uint64_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (ordstruct_adt__ordstruct_adt_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                for (uint32_t j=0; j < size; j++){release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)data[j].value);};
                safe_free(data);}
        uint32_t ihash = uint64_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_20(htbl, i, ihash);
        ltedpeg_funtype_20_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint64_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (ordstruct_adt__ordstruct_adt_t)v; htbl->num_entries++;}
            else {ordstruct_adt__ordstruct_adt_t tempvalue;tempvalue = (ordstruct_adt__ordstruct_adt_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (ordstruct_adt__ordstruct_adt_t)v;if (v != NULL) v->count++;if (tempvalue != NULL)release_ordstruct_adt__ordstruct_adt(tempvalue);};
        return a;

}

ltedpeg_funtype_20_t update_ltedpeg_funtype_20(ltedpeg_funtype_20_t a, uint64_t i, ordstruct_adt__ordstruct_adt_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_20(a, i, v);
            } else {
                ltedpeg_funtype_20_t x = copy_ltedpeg_funtype_20(a);
                a->count--;
                return dupdate_ltedpeg_funtype_20(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_20(ltedpeg_funtype_20_t x, ltedpeg_funtype_20_t y){
        return false;}

char* json_ltedpeg_funtype_20(ltedpeg_funtype_20_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_20\""); return result;}

void release_ltedpeg_funtype_21(ltedpeg_funtype_21_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_21_t copy_ltedpeg_funtype_21(ltedpeg_funtype_21_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_21(ltedpeg_funtype_21_t x, ltedpeg_funtype_21_t y){
        return false;}

char* json_ltedpeg_funtype_21(ltedpeg_funtype_21_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_21\""); return result;}

void release_ltedpeg_funtype_22(ltedpeg_funtype_22_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_22_t copy_ltedpeg_funtype_22(ltedpeg_funtype_22_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_22(ltedpeg_funtype_22_t x, ltedpeg_funtype_22_t y){
        return false;}

char* json_ltedpeg_funtype_22(ltedpeg_funtype_22_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_22\""); return result;}


ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_23(struct ltedpeg_closure_23_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_20_t fvar_1 = closure->fvar_1;
        ordstruct_adt__ordstruct_adt_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_21_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_22_t fvar_4 = closure->fvar_4;
        ordstruct_adt__ordstruct_adt_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)closure);
        ordstruct_adt__ordstruct_adt_t result;
        result = (ordstruct_adt__ordstruct_adt_t)h_ltedpeg_closure_23(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_23(struct ltedpeg_closure_23_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_20_t fvar_1 = closure->fvar_1;
        ordstruct_adt__ordstruct_adt_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_21_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_22_t fvar_4 = closure->fvar_4;
        ordstruct_adt__ordstruct_adt_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)closure);
        return h_ltedpeg_closure_23(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_23(ltedpeg__ent_adt_t ivar_11, ltedpeg_funtype_20_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_4, ltedpeg_funtype_21_t ivar_5, ltedpeg_funtype_22_t ivar_7, ordstruct_adt__ordstruct_adt_t ivar_3){
        ordstruct_adt__ordstruct_adt_t result;

        bool_t ivar_40;
        ivar_11->count++;
        ivar_40 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_11);
        if (ivar_40){
             uint64_t ivar_30;
             ivar_30 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_11);
             ivar_1->count++;
             result = (ordstruct_adt__ordstruct_adt_t)ivar_1->ftbl->fptr(ivar_1, ivar_30);
        } else {
             bool_t ivar_44;
             ivar_11->count++;
             ivar_44 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_11);
             if (ivar_44){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_11);
           //copying to ordstruct_adt__ordstruct_adt from ordstruct_adt__ordstruct_adt;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_3;
           if (result != NULL) result->count++;
             } else {
           bool_t ivar_48;
           ivar_11->count++;
           ivar_48 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_11);
           if (ivar_48){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_11);
           //copying to ordstruct_adt__ordstruct_adt from ordstruct_adt__ordstruct_adt;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_4;
           if (result != NULL) result->count++;
           } else {
           bool_t ivar_68;
           ivar_11->count++;
           ivar_68 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_11);
           if (ivar_68){
            uint64_t ivar_52;
            ivar_11->count++;
            ivar_52 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_11);
            uint32_t ivar_53;
            ivar_53 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_11);
            ivar_5->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_5->ftbl->mptr(ivar_5, ivar_52, ivar_53);
           } else {
            uint32_t ivar_72;
            ivar_11->count++;
            ivar_72 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_11);
            uint8_t ivar_73;
            ivar_73 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_11);
            ivar_7->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_7->ftbl->mptr(ivar_7, ivar_72, ivar_73);};};};};
        return result;
}

ltedpeg_closure_23_t new_ltedpeg_closure_23(void){
        static struct ltedpeg_funtype_19_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_19_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_23, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_19_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_23, .rptr =  (void (*)(ltedpeg_funtype_19_t))&release_ltedpeg_closure_23, .cptr = (ltedpeg_funtype_19_t (*)(ltedpeg_funtype_19_t))&copy_ltedpeg_closure_23};
        ltedpeg_closure_23_t tmp = (ltedpeg_closure_23_t) safe_malloc(sizeof(struct ltedpeg_closure_23_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_23(ltedpeg_funtype_19_t closure){
        ltedpeg_closure_23_t x = (ltedpeg_closure_23_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_funtype_20((ltedpeg_funtype_20_t)x->fvar_1);
         release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->fvar_2);
         release_ltedpeg_funtype_21((ltedpeg_funtype_21_t)x->fvar_3);
         release_ltedpeg_funtype_22((ltedpeg_funtype_22_t)x->fvar_4);
         release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key); release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_23_t copy_ltedpeg_closure_23(ltedpeg_closure_23_t x){
        ltedpeg_closure_23_t y = new_ltedpeg_closure_23();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        y->fvar_5 = x->fvar_5; x->fvar_5->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_19_htbl_t new_htbl = (ltedpeg_funtype_19_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_19_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_19_hashentry_t * new_data = (ltedpeg_funtype_19_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_19_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_24(ltedpeg_funtype_24_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_24_t copy_ltedpeg_funtype_24(ltedpeg_funtype_24_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_24(ltedpeg_funtype_24_t x, ltedpeg_funtype_24_t y){
        return false;}

char* json_ltedpeg_funtype_24(ltedpeg_funtype_24_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_24\""); return result;}

void release_ltedpeg_funtype_25(ltedpeg_funtype_25_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_25_t copy_ltedpeg_funtype_25(ltedpeg_funtype_25_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_25(ltedpeg_funtype_25_t x, ltedpeg_funtype_25_t y){
        return false;}

char* json_ltedpeg_funtype_25(ltedpeg_funtype_25_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_25\""); return result;}

void release_ltedpeg_funtype_26(ltedpeg_funtype_26_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_26_t copy_ltedpeg_funtype_26(ltedpeg_funtype_26_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_26(ltedpeg_funtype_26_t x, ltedpeg_funtype_26_t y){
        return false;}

char* json_ltedpeg_funtype_26(ltedpeg_funtype_26_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_26\""); return result;}


ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_27(struct ltedpeg_closure_27_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_24_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_19_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_25_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_26_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_19_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)closure);
        ordstruct_adt__ordstruct_adt_t result;
        result = (ordstruct_adt__ordstruct_adt_t)h_ltedpeg_closure_27(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_27(struct ltedpeg_closure_27_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg_funtype_24_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_19_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_25_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_26_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_19_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)closure);
        return h_ltedpeg_closure_27(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_27(ltedpeg__ent_adt_t ivar_13, ltedpeg_funtype_24_t ivar_1, ltedpeg_funtype_19_t ivar_5, ltedpeg_funtype_25_t ivar_7, ltedpeg_funtype_26_t ivar_9, ltedpeg_funtype_19_t ivar_3){
        ordstruct_adt__ordstruct_adt_t result;

        bool_t ivar_46;
        ivar_13->count++;
        ivar_46 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_13);
        if (ivar_46){
             uint64_t ivar_34;
             ivar_13->count++;
             ivar_34 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_13);
             ivar_1->count++;
             result = (ordstruct_adt__ordstruct_adt_t)ivar_1->ftbl->mptr(ivar_1, ivar_34, ivar_13);
        } else {
             bool_t ivar_56;
             ivar_13->count++;
             ivar_56 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_13);
             if (ivar_56){
           ivar_3->count++;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_3->ftbl->fptr(ivar_3, ivar_13);
             } else {
           bool_t ivar_66;
           ivar_13->count++;
           ivar_66 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_13);
           if (ivar_66){
           ivar_5->count++;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_5->ftbl->fptr(ivar_5, ivar_13);
           } else {
           bool_t ivar_88;
           ivar_13->count++;
           ivar_88 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_13);
           if (ivar_88){
            uint64_t ivar_70;
            ivar_13->count++;
            ivar_70 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_13);
            uint32_t ivar_71;
            ivar_13->count++;
            ivar_71 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_13);
            ivar_7->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_7->ftbl->mptr(ivar_7, ivar_70, ivar_71, ivar_13);
           } else {
            uint32_t ivar_92;
            ivar_13->count++;
            ivar_92 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_13);
            uint8_t ivar_93;
            ivar_13->count++;
            ivar_93 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_13);
            ivar_9->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_9->ftbl->mptr(ivar_9, ivar_92, ivar_93, ivar_13);};};};};
        return result;
}

ltedpeg_closure_27_t new_ltedpeg_closure_27(void){
        static struct ltedpeg_funtype_19_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_19_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_27, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_19_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_27, .rptr =  (void (*)(ltedpeg_funtype_19_t))&release_ltedpeg_closure_27, .cptr = (ltedpeg_funtype_19_t (*)(ltedpeg_funtype_19_t))&copy_ltedpeg_closure_27};
        ltedpeg_closure_27_t tmp = (ltedpeg_closure_27_t) safe_malloc(sizeof(struct ltedpeg_closure_27_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_27(ltedpeg_funtype_19_t closure){
        ltedpeg_closure_27_t x = (ltedpeg_closure_27_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_funtype_24((ltedpeg_funtype_24_t)x->fvar_1);
         release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)x->fvar_2);
         release_ltedpeg_funtype_25((ltedpeg_funtype_25_t)x->fvar_3);
         release_ltedpeg_funtype_26((ltedpeg_funtype_26_t)x->fvar_4);
         release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key); release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_27_t copy_ltedpeg_closure_27(ltedpeg_closure_27_t x){
        ltedpeg_closure_27_t y = new_ltedpeg_closure_27();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        y->fvar_5 = x->fvar_5; x->fvar_5->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_19_htbl_t new_htbl = (ltedpeg_funtype_19_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_19_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_19_hashentry_t * new_data = (ltedpeg_funtype_19_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_19_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg__prepeg_adt_t new_ltedpeg__prepeg_adt(void){
        ltedpeg__prepeg_adt_t tmp = (ltedpeg__prepeg_adt_t) safe_malloc(sizeof(struct ltedpeg__prepeg_adt_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x){
switch (x->ltedpeg__prepeg_adt_index) {
case 2:  release_ltedpeg__any((ltedpeg__any_t)x); break;
case 3:  release_ltedpeg__terminal((ltedpeg__terminal_t)x); break;
case 4:  release_ltedpeg__lte((ltedpeg__lte_t)x); break;
}}

void release_ltedpeg__prepeg_adt_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x);
}

ltedpeg__prepeg_adt_t copy_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x){
        ltedpeg__prepeg_adt_t y = new_ltedpeg__prepeg_adt();
        y->ltedpeg__prepeg_adt_index = (uint8_t)x->ltedpeg__prepeg_adt_index;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x, ltedpeg__prepeg_adt_t y){
        bool_t tmp = x->ltedpeg__prepeg_adt_index == y->ltedpeg__prepeg_adt_index;
        switch  (x->ltedpeg__prepeg_adt_index) {
                case 2: tmp = tmp && equal_ltedpeg__any((ltedpeg__any_t)x, (ltedpeg__any_t)y); break;
                case 3: tmp = tmp && equal_ltedpeg__terminal((ltedpeg__terminal_t)x, (ltedpeg__terminal_t)y); break;
                case 4: tmp = tmp && equal_ltedpeg__lte((ltedpeg__lte_t)x, (ltedpeg__lte_t)y); break;
        }
        return tmp;
}

char * json_ltedpeg__prepeg_adt(ltedpeg__prepeg_adt_t x){
        char * tmp = safe_malloc(24); sprintf(tmp, "{ \"constructor\": %u,", x->ltedpeg__prepeg_adt_index); tmp = safe_strcat(tmp, " \"value\": ");
        switch  (x->ltedpeg__prepeg_adt_index) {
                case 2: tmp = safe_strcat(tmp, json_ltedpeg__any((ltedpeg__any_t)x)); break;
                case 3: tmp = safe_strcat(tmp, json_ltedpeg__terminal((ltedpeg__terminal_t)x)); break;
                case 4: tmp = safe_strcat(tmp, json_ltedpeg__lte((ltedpeg__lte_t)x)); break;
                default: tmp = safe_strcat(tmp, "null");
        };
        tmp = safe_strcat(tmp, " }");
        return tmp;
}

bool_t equal_ltedpeg__prepeg_adt_ptr(pointer_t x, pointer_t y, actual_ltedpeg__prepeg_adt_t T){
        return equal_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x, (ltedpeg__prepeg_adt_t)y);
}

char * json_ltedpeg__prepeg_adt_ptr(pointer_t x, actual_ltedpeg__prepeg_adt_t T){
        return json_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x);
}

actual_ltedpeg__prepeg_adt_t actual_ltedpeg__prepeg_adt(void){
        actual_ltedpeg__prepeg_adt_t new = (actual_ltedpeg__prepeg_adt_t)safe_malloc(sizeof(struct actual_ltedpeg__prepeg_adt_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__prepeg_adt_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__prepeg_adt_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__prepeg_adt_ptr);
 

 
        return new;
 }

ltedpeg__prepeg_adt_t update_ltedpeg__prepeg_adt_ltedpeg__prepeg_adt_index(ltedpeg__prepeg_adt_t x, uint8_t v){
        ltedpeg__prepeg_adt_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__prepeg_adt(x); x->count--;};
        y->ltedpeg__prepeg_adt_index = (uint8_t)v;
        return y;}




ltedpeg__any_t new_ltedpeg__any(void){
        ltedpeg__any_t tmp = (ltedpeg__any_t) safe_malloc(sizeof(struct ltedpeg__any_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__any(ltedpeg__any_t x){
        x->count--;
        if (x->count <= 0){
         release_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->dpg);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__any_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__any((ltedpeg__any_t)x);
}

ltedpeg__any_t copy_ltedpeg__any(ltedpeg__any_t x){
        ltedpeg__any_t y = new_ltedpeg__any();
        y->ltedpeg__prepeg_adt_index = (uint8_t)x->ltedpeg__prepeg_adt_index;
        y->dpg = x->dpg;
        if (y->dpg != NULL){y->dpg->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__any(ltedpeg__any_t x, ltedpeg__any_t y){
        bool_t tmp = true; tmp = tmp && x->ltedpeg__prepeg_adt_index == y->ltedpeg__prepeg_adt_index; tmp = tmp && equal_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->dpg, (dpeg__dpeg_grammar_t)y->dpg);
        return tmp;}

char * json_ltedpeg__any(ltedpeg__any_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(37);
         sprintf(fld0, "\"ltedpeg__prepeg_adt_index\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->ltedpeg__prepeg_adt_index));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"dpg\" : ");
        tmp[1] = safe_strcat(fld1, json_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->dpg));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg__any_ptr(pointer_t x, pointer_t y, actual_ltedpeg__any_t T){
        return equal_ltedpeg__any((ltedpeg__any_t)x, (ltedpeg__any_t)y);
}

char * json_ltedpeg__any_ptr(pointer_t x, actual_ltedpeg__any_t T){
        return json_ltedpeg__any((ltedpeg__any_t)x);
}

actual_ltedpeg__any_t actual_ltedpeg__any(void){
        actual_ltedpeg__any_t new = (actual_ltedpeg__any_t)safe_malloc(sizeof(struct actual_ltedpeg__any_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__any_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__any_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__any_ptr);
 

 
        return new;
 }

ltedpeg__any_t update_ltedpeg__any_ltedpeg__prepeg_adt_index(ltedpeg__any_t x, uint8_t v){
        ltedpeg__any_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__any(x); x->count--;};
        y->ltedpeg__prepeg_adt_index = (uint8_t)v;
        return y;}

ltedpeg__any_t update_ltedpeg__any_dpg(ltedpeg__any_t x, dpeg__dpeg_grammar_t v){
        ltedpeg__any_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->dpg != NULL){release_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->dpg);};}
        else {y = copy_ltedpeg__any(x); x->count--; y->dpg->count--;};
        y->dpg = (dpeg__dpeg_grammar_t)v;
        return y;}




ltedpeg__terminal_t new_ltedpeg__terminal(void){
        ltedpeg__terminal_t tmp = (ltedpeg__terminal_t) safe_malloc(sizeof(struct ltedpeg__terminal_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__terminal(ltedpeg__terminal_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__terminal_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__terminal((ltedpeg__terminal_t)x);
}

ltedpeg__terminal_t copy_ltedpeg__terminal(ltedpeg__terminal_t x){
        ltedpeg__terminal_t y = new_ltedpeg__terminal();
        y->ltedpeg__prepeg_adt_index = (uint8_t)x->ltedpeg__prepeg_adt_index;
        y->a = (uint8_t)x->a;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__terminal(ltedpeg__terminal_t x, ltedpeg__terminal_t y){
        bool_t tmp = true; tmp = tmp && x->ltedpeg__prepeg_adt_index == y->ltedpeg__prepeg_adt_index; tmp = tmp && x->a == y->a;
        return tmp;}

char * json_ltedpeg__terminal(ltedpeg__terminal_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(37);
         sprintf(fld0, "\"ltedpeg__prepeg_adt_index\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->ltedpeg__prepeg_adt_index));
        char * fld1 = safe_malloc(13);
         sprintf(fld1, "\"a\" : ");
        tmp[1] = safe_strcat(fld1, json_uint8(x->a));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg__terminal_ptr(pointer_t x, pointer_t y, actual_ltedpeg__terminal_t T){
        return equal_ltedpeg__terminal((ltedpeg__terminal_t)x, (ltedpeg__terminal_t)y);
}

char * json_ltedpeg__terminal_ptr(pointer_t x, actual_ltedpeg__terminal_t T){
        return json_ltedpeg__terminal((ltedpeg__terminal_t)x);
}

actual_ltedpeg__terminal_t actual_ltedpeg__terminal(void){
        actual_ltedpeg__terminal_t new = (actual_ltedpeg__terminal_t)safe_malloc(sizeof(struct actual_ltedpeg__terminal_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__terminal_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__terminal_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__terminal_ptr);
 

 
        return new;
 }

ltedpeg__terminal_t update_ltedpeg__terminal_ltedpeg__prepeg_adt_index(ltedpeg__terminal_t x, uint8_t v){
        ltedpeg__terminal_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__terminal(x); x->count--;};
        y->ltedpeg__prepeg_adt_index = (uint8_t)v;
        return y;}

ltedpeg__terminal_t update_ltedpeg__terminal_a(ltedpeg__terminal_t x, uint8_t v){
        ltedpeg__terminal_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__terminal(x); x->count--;};
        y->a = (uint8_t)v;
        return y;}




ltedpeg__lte_t new_ltedpeg__lte(void){
        ltedpeg__lte_t tmp = (ltedpeg__lte_t) safe_malloc(sizeof(struct ltedpeg__lte_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__lte(ltedpeg__lte_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__lte_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__lte((ltedpeg__lte_t)x);
}

ltedpeg__lte_t copy_ltedpeg__lte(ltedpeg__lte_t x){
        ltedpeg__lte_t y = new_ltedpeg__lte();
        y->ltedpeg__prepeg_adt_index = (uint8_t)x->ltedpeg__prepeg_adt_index;
        y->fst = (uint8_t)x->fst;
        y->lthen = (uint8_t)x->lthen;
        y->lelse = (uint8_t)x->lelse;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__lte(ltedpeg__lte_t x, ltedpeg__lte_t y){
        bool_t tmp = true; tmp = tmp && x->ltedpeg__prepeg_adt_index == y->ltedpeg__prepeg_adt_index; tmp = tmp && x->fst == y->fst; tmp = tmp && x->lthen == y->lthen; tmp = tmp && x->lelse == y->lelse;
        return tmp;}

char * json_ltedpeg__lte(ltedpeg__lte_t x){
        char * tmp[4]; 
        char * fld0 = safe_malloc(37);
         sprintf(fld0, "\"ltedpeg__prepeg_adt_index\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->ltedpeg__prepeg_adt_index));
        char * fld1 = safe_malloc(15);
         sprintf(fld1, "\"fst\" : ");
        tmp[1] = safe_strcat(fld1, json_uint8(x->fst));
        char * fld2 = safe_malloc(17);
         sprintf(fld2, "\"lthen\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->lthen));
        char * fld3 = safe_malloc(17);
         sprintf(fld3, "\"lelse\" : ");
        tmp[3] = safe_strcat(fld3, json_uint8(x->lelse));
         char * result = json_list_with_sep(tmp, 4,  '{', ',', '}');
         for (uint32_t i = 0; i < 4; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg__lte_ptr(pointer_t x, pointer_t y, actual_ltedpeg__lte_t T){
        return equal_ltedpeg__lte((ltedpeg__lte_t)x, (ltedpeg__lte_t)y);
}

char * json_ltedpeg__lte_ptr(pointer_t x, actual_ltedpeg__lte_t T){
        return json_ltedpeg__lte((ltedpeg__lte_t)x);
}

actual_ltedpeg__lte_t actual_ltedpeg__lte(void){
        actual_ltedpeg__lte_t new = (actual_ltedpeg__lte_t)safe_malloc(sizeof(struct actual_ltedpeg__lte_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__lte_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__lte_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__lte_ptr);
 

 
        return new;
 }

ltedpeg__lte_t update_ltedpeg__lte_ltedpeg__prepeg_adt_index(ltedpeg__lte_t x, uint8_t v){
        ltedpeg__lte_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__lte(x); x->count--;};
        y->ltedpeg__prepeg_adt_index = (uint8_t)v;
        return y;}

ltedpeg__lte_t update_ltedpeg__lte_fst(ltedpeg__lte_t x, uint8_t v){
        ltedpeg__lte_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__lte(x); x->count--;};
        y->fst = (uint8_t)v;
        return y;}

ltedpeg__lte_t update_ltedpeg__lte_lthen(ltedpeg__lte_t x, uint8_t v){
        ltedpeg__lte_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__lte(x); x->count--;};
        y->lthen = (uint8_t)v;
        return y;}

ltedpeg__lte_t update_ltedpeg__lte_lelse(ltedpeg__lte_t x, uint8_t v){
        ltedpeg__lte_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__lte(x); x->count--;};
        y->lelse = (uint8_t)v;
        return y;}



void release_ltedpeg_funtype_32(ltedpeg_funtype_32_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_32_t copy_ltedpeg_funtype_32(ltedpeg_funtype_32_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_32(ltedpeg_funtype_32_t x, ltedpeg_funtype_32_t y){
        return false;}

char* json_ltedpeg_funtype_32(ltedpeg_funtype_32_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_32\""); return result;}

void release_ltedpeg_funtype_33(ltedpeg_funtype_33_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_33_t copy_ltedpeg_funtype_33(ltedpeg_funtype_33_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_33(ltedpeg_funtype_33_t x, ltedpeg_funtype_33_t y){
        return false;}

char* json_ltedpeg_funtype_33(ltedpeg_funtype_33_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_33\""); return result;}

void release_ltedpeg_funtype_34(ltedpeg_funtype_34_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_34_t copy_ltedpeg_funtype_34(ltedpeg_funtype_34_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_34(ltedpeg_funtype_34_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_34_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_34_t dupdate_ltedpeg_funtype_34(ltedpeg_funtype_34_t a, uint8_t i, mpz_ptr_t v){
        ltedpeg_funtype_34_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_34_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_34_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_34_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_34_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_34_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_34_hashentry_t * new_data = (ltedpeg_funtype_34_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_34_hashentry_s));
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
                                mpz_set(new_data[new_loc].value, data[j].value);
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                for (uint32_t j=0; j < size; j++){mpz_clear(data[j].value);};
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_34(htbl, i, ihash);
        ltedpeg_funtype_34_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; mpz_set(htbl->data[hashindex].value, v); htbl->num_entries++;}
            else {mpz_set(htbl->data[hashindex].value, v);};
        return a;

}

ltedpeg_funtype_34_t update_ltedpeg_funtype_34(ltedpeg_funtype_34_t a, uint8_t i, mpz_ptr_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_34(a, i, v);
            } else {
                ltedpeg_funtype_34_t x = copy_ltedpeg_funtype_34(a);
                a->count--;
                return dupdate_ltedpeg_funtype_34(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_34(ltedpeg_funtype_34_t x, ltedpeg_funtype_34_t y){
        return false;}

char* json_ltedpeg_funtype_34(ltedpeg_funtype_34_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_34\""); return result;}


ltedpeg_record_35_t new_ltedpeg_record_35(void){
        ltedpeg_record_35_t tmp = (ltedpeg_record_35_t) safe_malloc(sizeof(struct ltedpeg_record_35_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_35(ltedpeg_record_35_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_35_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_35((ltedpeg_record_35_t)x);
}

ltedpeg_record_35_t copy_ltedpeg_record_35(ltedpeg_record_35_t x){
        ltedpeg_record_35_t y = new_ltedpeg_record_35();
        y->project_1 = (uint8_t)x->project_1;
        y->project_2 = (uint8_t)x->project_2;
        y->project_3 = (uint8_t)x->project_3;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_35(ltedpeg_record_35_t x, ltedpeg_record_35_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && x->project_2 == y->project_2; tmp = tmp && x->project_3 == y->project_3;
        return tmp;}

char * json_ltedpeg_record_35(ltedpeg_record_35_t x){
        char * tmp[3]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint8(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->project_3));
         char * result = json_list_with_sep(tmp, 3,  '{', ',', '}');
         for (uint32_t i = 0; i < 3; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_35_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_35_t T){
        return equal_ltedpeg_record_35((ltedpeg_record_35_t)x, (ltedpeg_record_35_t)y);
}

char * json_ltedpeg_record_35_ptr(pointer_t x, actual_ltedpeg_record_35_t T){
        return json_ltedpeg_record_35((ltedpeg_record_35_t)x);
}

actual_ltedpeg_record_35_t actual_ltedpeg_record_35(void){
        actual_ltedpeg_record_35_t new = (actual_ltedpeg_record_35_t)safe_malloc(sizeof(struct actual_ltedpeg_record_35_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_35_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_35_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_35_ptr);
 

 
        return new;
 }

ltedpeg_record_35_t update_ltedpeg_record_35_project_1(ltedpeg_record_35_t x, uint8_t v){
        ltedpeg_record_35_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_35(x); x->count--;};
        y->project_1 = (uint8_t)v;
        return y;}

ltedpeg_record_35_t update_ltedpeg_record_35_project_2(ltedpeg_record_35_t x, uint8_t v){
        ltedpeg_record_35_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_35(x); x->count--;};
        y->project_2 = (uint8_t)v;
        return y;}

ltedpeg_record_35_t update_ltedpeg_record_35_project_3(ltedpeg_record_35_t x, uint8_t v){
        ltedpeg_record_35_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_35(x); x->count--;};
        y->project_3 = (uint8_t)v;
        return y;}



void release_ltedpeg_funtype_36(ltedpeg_funtype_36_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_36_t copy_ltedpeg_funtype_36(ltedpeg_funtype_36_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_36(ltedpeg_funtype_36_t x, ltedpeg_funtype_36_t y){
        return false;}

char* json_ltedpeg_funtype_36(ltedpeg_funtype_36_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_36\""); return result;}


mpz_ptr_t f_ltedpeg_closure_37(struct ltedpeg_closure_37_s * closure, ltedpeg__prepeg_adt_t bvar){
        mpz_ptr_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_33_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_34_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_36_t fvar_4 = closure->fvar_4;
        mpz_ptr_t fvar_5 = closure->fvar_5;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)closure);
        mpz_ptr_t result;
        result = (mpz_ptr_t)h_ltedpeg_closure_37(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

mpz_ptr_t m_ltedpeg_closure_37(struct ltedpeg_closure_37_s * closure, ltedpeg__prepeg_adt_t bvar){
        mpz_ptr_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_33_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_34_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_36_t fvar_4 = closure->fvar_4;
        mpz_ptr_t fvar_5 = closure->fvar_5;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)closure);
        return h_ltedpeg_closure_37(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

mpz_ptr_t h_ltedpeg_closure_37(ltedpeg__prepeg_adt_t ivar_11, mpz_ptr_t ivar_1, ltedpeg_funtype_33_t ivar_3, ltedpeg_funtype_34_t ivar_5, ltedpeg_funtype_36_t ivar_7, mpz_ptr_t ivar_2){
        mpz_ptr_t result;

        bool_t ivar_30;
        ivar_11->count++;
        ivar_30 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_11);
        if (ivar_30){
             release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_11);
             //copying to mpz from mpz;
             mpz_mk_set(result, ivar_1);
        } else {
             bool_t ivar_34;
             ivar_11->count++;
             ivar_34 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_11);
             if (ivar_34){
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_11);
           //copying to mpz from mpz;
           mpz_mk_set(result, ivar_2);
             } else {
           bool_t ivar_48;
           ivar_11->count++;
           ivar_48 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_11);
           if (ivar_48){
           dpeg__dpeg_grammar_t ivar_38;
           ivar_38 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_11);
           ivar_3->count++;
           mpz_mk_set(result, ivar_3->ftbl->fptr(ivar_3, ivar_38));
           } else {
           bool_t ivar_62;
           ivar_11->count++;
           ivar_62 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_11);
           if (ivar_62){
            uint8_t ivar_52;
            ivar_52 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_11);
            ivar_5->count++;
            mpz_mk_set(result, ivar_5->ftbl->fptr(ivar_5, ivar_52));
           } else {
            uint8_t ivar_66;
            ivar_11->count++;
            ivar_66 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_11);
            uint8_t ivar_67;
            ivar_11->count++;
            ivar_67 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_11);
            uint8_t ivar_68;
            ivar_68 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_11);
            ivar_7->count++;
            mpz_mk_set(result, ivar_7->ftbl->mptr(ivar_7, ivar_66, ivar_67, ivar_68));};};};};
        return result;
}

ltedpeg_closure_37_t new_ltedpeg_closure_37(void){
        static struct ltedpeg_funtype_32_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ltedpeg_funtype_32_t, ltedpeg__prepeg_adt_t))&f_ltedpeg_closure_37, .mptr = (mpz_ptr_t (*)(ltedpeg_funtype_32_t, ltedpeg__prepeg_adt_t))&m_ltedpeg_closure_37, .rptr =  (void (*)(ltedpeg_funtype_32_t))&release_ltedpeg_closure_37, .cptr = (ltedpeg_funtype_32_t (*)(ltedpeg_funtype_32_t))&copy_ltedpeg_closure_37};
        ltedpeg_closure_37_t tmp = (ltedpeg_closure_37_t) safe_malloc(sizeof(struct ltedpeg_closure_37_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_1);
        mpz_init(tmp->fvar_5);
        return tmp;}

void release_ltedpeg_closure_37(ltedpeg_funtype_32_t closure){
        ltedpeg_closure_37_t x = (ltedpeg_closure_37_t)closure;
        x->count--;
        if (x->count <= 0){
         mpz_clear(x->fvar_1);
         release_ltedpeg_funtype_33((ltedpeg_funtype_33_t)x->fvar_2);
         release_ltedpeg_funtype_34((ltedpeg_funtype_34_t)x->fvar_3);
         release_ltedpeg_funtype_36((ltedpeg_funtype_36_t)x->fvar_4);
         mpz_clear(x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_37_t copy_ltedpeg_closure_37(ltedpeg_closure_37_t x){
        ltedpeg_closure_37_t y = new_ltedpeg_closure_37();
        y->ftbl = x->ftbl;

        mpz_set(y->fvar_1, x->fvar_1);
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        mpz_set(y->fvar_5, x->fvar_5);
        if (x->htbl != NULL){
            ltedpeg_funtype_32_htbl_t new_htbl = (ltedpeg_funtype_32_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_32_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_32_hashentry_t * new_data = (ltedpeg_funtype_32_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_32_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__prepeg_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  mpz_init(new_data[j].value); mpz_set(new_data[j].value, x->htbl->data[j].value);;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_38_t new_ltedpeg_record_38(void){
        ltedpeg_record_38_t tmp = (ltedpeg_record_38_t) safe_malloc(sizeof(struct ltedpeg_record_38_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_38(ltedpeg_record_38_t x){
        x->count--;
        if (x->count <= 0){
         release_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->project_1);
         release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_38_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_38((ltedpeg_record_38_t)x);
}

ltedpeg_record_38_t copy_ltedpeg_record_38(ltedpeg_record_38_t x){
        ltedpeg_record_38_t y = new_ltedpeg_record_38();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = x->project_2;
        if (y->project_2 != NULL){y->project_2->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_38(ltedpeg_record_38_t x, ltedpeg_record_38_t y){
        bool_t tmp = true; tmp = tmp && equal_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->project_1, (dpeg__dpeg_grammar_t)y->project_1); tmp = tmp && equal_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2, (ltedpeg__prepeg_adt_t)y->project_2);
        return tmp;}

char * json_ltedpeg_record_38(ltedpeg_record_38_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_38_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_38_t T){
        return equal_ltedpeg_record_38((ltedpeg_record_38_t)x, (ltedpeg_record_38_t)y);
}

char * json_ltedpeg_record_38_ptr(pointer_t x, actual_ltedpeg_record_38_t T){
        return json_ltedpeg_record_38((ltedpeg_record_38_t)x);
}

actual_ltedpeg_record_38_t actual_ltedpeg_record_38(void){
        actual_ltedpeg_record_38_t new = (actual_ltedpeg_record_38_t)safe_malloc(sizeof(struct actual_ltedpeg_record_38_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_38_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_38_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_38_ptr);
 

 
        return new;
 }

ltedpeg_record_38_t update_ltedpeg_record_38_project_1(ltedpeg_record_38_t x, dpeg__dpeg_grammar_t v){
        ltedpeg_record_38_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_dpeg__dpeg_grammar((dpeg__dpeg_grammar_t)x->project_1);};}
        else {y = copy_ltedpeg_record_38(x); x->count--; y->project_1->count--;};
        y->project_1 = (dpeg__dpeg_grammar_t)v;
        return y;}

ltedpeg_record_38_t update_ltedpeg_record_38_project_2(ltedpeg_record_38_t x, ltedpeg__prepeg_adt_t v){
        ltedpeg_record_38_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_2 != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2);};}
        else {y = copy_ltedpeg_record_38(x); x->count--; y->project_2->count--;};
        y->project_2 = (ltedpeg__prepeg_adt_t)v;
        return y;}



void release_ltedpeg_funtype_39(ltedpeg_funtype_39_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_39_t copy_ltedpeg_funtype_39(ltedpeg_funtype_39_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_39(ltedpeg_funtype_39_t x, ltedpeg_funtype_39_t y){
        return false;}

char* json_ltedpeg_funtype_39(ltedpeg_funtype_39_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_39\""); return result;}


ltedpeg_record_40_t new_ltedpeg_record_40(void){
        ltedpeg_record_40_t tmp = (ltedpeg_record_40_t) safe_malloc(sizeof(struct ltedpeg_record_40_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_40(ltedpeg_record_40_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_40_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_40((ltedpeg_record_40_t)x);
}

ltedpeg_record_40_t copy_ltedpeg_record_40(ltedpeg_record_40_t x){
        ltedpeg_record_40_t y = new_ltedpeg_record_40();
        y->project_1 = (uint8_t)x->project_1;
        y->project_2 = x->project_2;
        if (y->project_2 != NULL){y->project_2->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_40(ltedpeg_record_40_t x, ltedpeg_record_40_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && equal_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2, (ltedpeg__prepeg_adt_t)y->project_2);
        return tmp;}

char * json_ltedpeg_record_40(ltedpeg_record_40_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_40_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_40_t T){
        return equal_ltedpeg_record_40((ltedpeg_record_40_t)x, (ltedpeg_record_40_t)y);
}

char * json_ltedpeg_record_40_ptr(pointer_t x, actual_ltedpeg_record_40_t T){
        return json_ltedpeg_record_40((ltedpeg_record_40_t)x);
}

actual_ltedpeg_record_40_t actual_ltedpeg_record_40(void){
        actual_ltedpeg_record_40_t new = (actual_ltedpeg_record_40_t)safe_malloc(sizeof(struct actual_ltedpeg_record_40_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_40_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_40_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_40_ptr);
 

 
        return new;
 }

ltedpeg_record_40_t update_ltedpeg_record_40_project_1(ltedpeg_record_40_t x, uint8_t v){
        ltedpeg_record_40_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_40(x); x->count--;};
        y->project_1 = (uint8_t)v;
        return y;}

ltedpeg_record_40_t update_ltedpeg_record_40_project_2(ltedpeg_record_40_t x, ltedpeg__prepeg_adt_t v){
        ltedpeg_record_40_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_2 != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_2);};}
        else {y = copy_ltedpeg_record_40(x); x->count--; y->project_2->count--;};
        y->project_2 = (ltedpeg__prepeg_adt_t)v;
        return y;}



void release_ltedpeg_funtype_41(ltedpeg_funtype_41_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_41_t copy_ltedpeg_funtype_41(ltedpeg_funtype_41_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_41(ltedpeg_funtype_41_t x, ltedpeg_funtype_41_t y){
        return false;}

char* json_ltedpeg_funtype_41(ltedpeg_funtype_41_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_41\""); return result;}


ltedpeg_record_42_t new_ltedpeg_record_42(void){
        ltedpeg_record_42_t tmp = (ltedpeg_record_42_t) safe_malloc(sizeof(struct ltedpeg_record_42_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_42(ltedpeg_record_42_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_4);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_42_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_42((ltedpeg_record_42_t)x);
}

ltedpeg_record_42_t copy_ltedpeg_record_42(ltedpeg_record_42_t x){
        ltedpeg_record_42_t y = new_ltedpeg_record_42();
        y->project_1 = (uint8_t)x->project_1;
        y->project_2 = (uint8_t)x->project_2;
        y->project_3 = (uint8_t)x->project_3;
        y->project_4 = x->project_4;
        if (y->project_4 != NULL){y->project_4->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_42(ltedpeg_record_42_t x, ltedpeg_record_42_t y){
        bool_t tmp = true; tmp = tmp && x->project_1 == y->project_1; tmp = tmp && x->project_2 == y->project_2; tmp = tmp && x->project_3 == y->project_3; tmp = tmp && equal_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_4, (ltedpeg__prepeg_adt_t)y->project_4);
        return tmp;}

char * json_ltedpeg_record_42(ltedpeg_record_42_t x){
        char * tmp[4]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_uint8(x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint8(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->project_3));
        char * fld3 = safe_malloc(21);
         sprintf(fld3, "\"project_4\" : ");
        tmp[3] = safe_strcat(fld3, json_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_4));
         char * result = json_list_with_sep(tmp, 4,  '{', ',', '}');
         for (uint32_t i = 0; i < 4; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_42_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_42_t T){
        return equal_ltedpeg_record_42((ltedpeg_record_42_t)x, (ltedpeg_record_42_t)y);
}

char * json_ltedpeg_record_42_ptr(pointer_t x, actual_ltedpeg_record_42_t T){
        return json_ltedpeg_record_42((ltedpeg_record_42_t)x);
}

actual_ltedpeg_record_42_t actual_ltedpeg_record_42(void){
        actual_ltedpeg_record_42_t new = (actual_ltedpeg_record_42_t)safe_malloc(sizeof(struct actual_ltedpeg_record_42_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_42_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_42_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_42_ptr);
 

 
        return new;
 }

ltedpeg_record_42_t update_ltedpeg_record_42_project_1(ltedpeg_record_42_t x, uint8_t v){
        ltedpeg_record_42_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_42(x); x->count--;};
        y->project_1 = (uint8_t)v;
        return y;}

ltedpeg_record_42_t update_ltedpeg_record_42_project_2(ltedpeg_record_42_t x, uint8_t v){
        ltedpeg_record_42_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_42(x); x->count--;};
        y->project_2 = (uint8_t)v;
        return y;}

ltedpeg_record_42_t update_ltedpeg_record_42_project_3(ltedpeg_record_42_t x, uint8_t v){
        ltedpeg_record_42_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_42(x); x->count--;};
        y->project_3 = (uint8_t)v;
        return y;}

ltedpeg_record_42_t update_ltedpeg_record_42_project_4(ltedpeg_record_42_t x, ltedpeg__prepeg_adt_t v){
        ltedpeg_record_42_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_4 != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->project_4);};}
        else {y = copy_ltedpeg_record_42(x); x->count--; y->project_4->count--;};
        y->project_4 = (ltedpeg__prepeg_adt_t)v;
        return y;}



void release_ltedpeg_funtype_43(ltedpeg_funtype_43_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_43_t copy_ltedpeg_funtype_43(ltedpeg_funtype_43_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_43(ltedpeg_funtype_43_t x, ltedpeg_funtype_43_t y){
        return false;}

char* json_ltedpeg_funtype_43(ltedpeg_funtype_43_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_43\""); return result;}


mpz_ptr_t f_ltedpeg_closure_44(struct ltedpeg_closure_44_s * closure, ltedpeg__prepeg_adt_t bvar){
        ltedpeg_funtype_32_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_39_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_41_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_43_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_32_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)closure);
        mpz_ptr_t result;
        result = (mpz_ptr_t)h_ltedpeg_closure_44(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

mpz_ptr_t m_ltedpeg_closure_44(struct ltedpeg_closure_44_s * closure, ltedpeg__prepeg_adt_t bvar){
        ltedpeg_funtype_32_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_39_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_41_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_43_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_32_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)closure);
        return h_ltedpeg_closure_44(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

mpz_ptr_t h_ltedpeg_closure_44(ltedpeg__prepeg_adt_t ivar_13, ltedpeg_funtype_32_t ivar_1, ltedpeg_funtype_39_t ivar_5, ltedpeg_funtype_41_t ivar_7, ltedpeg_funtype_43_t ivar_9, ltedpeg_funtype_32_t ivar_3){
        mpz_ptr_t result;

        bool_t ivar_40;
        ivar_13->count++;
        ivar_40 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_13);
        if (ivar_40){
             ivar_1->count++;
             mpz_mk_set(result, ivar_1->ftbl->fptr(ivar_1, ivar_13));
        } else {
             bool_t ivar_50;
             ivar_13->count++;
             ivar_50 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_13);
             if (ivar_50){
           ivar_3->count++;
           mpz_mk_set(result, ivar_3->ftbl->fptr(ivar_3, ivar_13));
             } else {
           bool_t ivar_66;
           ivar_13->count++;
           ivar_66 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_13);
           if (ivar_66){
           dpeg__dpeg_grammar_t ivar_54;
           ivar_13->count++;
           ivar_54 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_13);
           ivar_5->count++;
           mpz_mk_set(result, ivar_5->ftbl->mptr(ivar_5, ivar_54, ivar_13));
           } else {
           bool_t ivar_82;
           ivar_13->count++;
           ivar_82 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_13);
           if (ivar_82){
            uint8_t ivar_70;
            ivar_13->count++;
            ivar_70 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_13);
            ivar_7->count++;
            mpz_mk_set(result, ivar_7->ftbl->mptr(ivar_7, ivar_70, ivar_13));
           } else {
            uint8_t ivar_86;
            ivar_13->count++;
            ivar_86 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_13);
            uint8_t ivar_87;
            ivar_13->count++;
            ivar_87 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_13);
            uint8_t ivar_88;
            ivar_13->count++;
            ivar_88 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_13);
            ivar_9->count++;
            mpz_mk_set(result, ivar_9->ftbl->mptr(ivar_9, ivar_86, ivar_87, ivar_88, ivar_13));};};};};
        return result;
}

ltedpeg_closure_44_t new_ltedpeg_closure_44(void){
        static struct ltedpeg_funtype_32_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ltedpeg_funtype_32_t, ltedpeg__prepeg_adt_t))&f_ltedpeg_closure_44, .mptr = (mpz_ptr_t (*)(ltedpeg_funtype_32_t, ltedpeg__prepeg_adt_t))&m_ltedpeg_closure_44, .rptr =  (void (*)(ltedpeg_funtype_32_t))&release_ltedpeg_closure_44, .cptr = (ltedpeg_funtype_32_t (*)(ltedpeg_funtype_32_t))&copy_ltedpeg_closure_44};
        ltedpeg_closure_44_t tmp = (ltedpeg_closure_44_t) safe_malloc(sizeof(struct ltedpeg_closure_44_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_44(ltedpeg_funtype_32_t closure){
        ltedpeg_closure_44_t x = (ltedpeg_closure_44_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)x->fvar_1);
         release_ltedpeg_funtype_39((ltedpeg_funtype_39_t)x->fvar_2);
         release_ltedpeg_funtype_41((ltedpeg_funtype_41_t)x->fvar_3);
         release_ltedpeg_funtype_43((ltedpeg_funtype_43_t)x->fvar_4);
         release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_44_t copy_ltedpeg_closure_44(ltedpeg_closure_44_t x){
        ltedpeg_closure_44_t y = new_ltedpeg_closure_44();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        y->fvar_5 = x->fvar_5; x->fvar_5->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_32_htbl_t new_htbl = (ltedpeg_funtype_32_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_32_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_32_hashentry_t * new_data = (ltedpeg_funtype_32_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_32_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__prepeg_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  mpz_init(new_data[j].value); mpz_set(new_data[j].value, x->htbl->data[j].value);;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_45(ltedpeg_funtype_45_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_45_t copy_ltedpeg_funtype_45(ltedpeg_funtype_45_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_45(ltedpeg_funtype_45_t x, ltedpeg_funtype_45_t y){
        return false;}

char* json_ltedpeg_funtype_45(ltedpeg_funtype_45_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_45\""); return result;}

void release_ltedpeg_funtype_46(ltedpeg_funtype_46_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_46_t copy_ltedpeg_funtype_46(ltedpeg_funtype_46_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_46(ltedpeg_funtype_46_t x, ltedpeg_funtype_46_t y){
        return false;}

char* json_ltedpeg_funtype_46(ltedpeg_funtype_46_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_46\""); return result;}

void release_ltedpeg_funtype_47(ltedpeg_funtype_47_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_47_t copy_ltedpeg_funtype_47(ltedpeg_funtype_47_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_47(ltedpeg_funtype_47_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_47_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_47_t dupdate_ltedpeg_funtype_47(ltedpeg_funtype_47_t a, uint8_t i, ordstruct_adt__ordstruct_adt_t v){
        ltedpeg_funtype_47_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_47_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_47_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_47_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_47_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_47_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_47_hashentry_t * new_data = (ltedpeg_funtype_47_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_47_hashentry_s));
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
                                new_data[new_loc].value = (ordstruct_adt__ordstruct_adt_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                for (uint32_t j=0; j < size; j++){release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)data[j].value);};
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_47(htbl, i, ihash);
        ltedpeg_funtype_47_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (ordstruct_adt__ordstruct_adt_t)v; htbl->num_entries++;}
            else {ordstruct_adt__ordstruct_adt_t tempvalue;tempvalue = (ordstruct_adt__ordstruct_adt_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (ordstruct_adt__ordstruct_adt_t)v;if (v != NULL) v->count++;if (tempvalue != NULL)release_ordstruct_adt__ordstruct_adt(tempvalue);};
        return a;

}

ltedpeg_funtype_47_t update_ltedpeg_funtype_47(ltedpeg_funtype_47_t a, uint8_t i, ordstruct_adt__ordstruct_adt_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_47(a, i, v);
            } else {
                ltedpeg_funtype_47_t x = copy_ltedpeg_funtype_47(a);
                a->count--;
                return dupdate_ltedpeg_funtype_47(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_47(ltedpeg_funtype_47_t x, ltedpeg_funtype_47_t y){
        return false;}

char* json_ltedpeg_funtype_47(ltedpeg_funtype_47_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_47\""); return result;}

void release_ltedpeg_funtype_48(ltedpeg_funtype_48_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_48_t copy_ltedpeg_funtype_48(ltedpeg_funtype_48_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_48(ltedpeg_funtype_48_t x, ltedpeg_funtype_48_t y){
        return false;}

char* json_ltedpeg_funtype_48(ltedpeg_funtype_48_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_48\""); return result;}


ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_49(struct ltedpeg_closure_49_s * closure, ltedpeg__prepeg_adt_t bvar){
        ordstruct_adt__ordstruct_adt_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_46_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_47_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_48_t fvar_4 = closure->fvar_4;
        ordstruct_adt__ordstruct_adt_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)closure);
        ordstruct_adt__ordstruct_adt_t result;
        result = (ordstruct_adt__ordstruct_adt_t)h_ltedpeg_closure_49(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_49(struct ltedpeg_closure_49_s * closure, ltedpeg__prepeg_adt_t bvar){
        ordstruct_adt__ordstruct_adt_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_46_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_47_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_48_t fvar_4 = closure->fvar_4;
        ordstruct_adt__ordstruct_adt_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)closure);
        return h_ltedpeg_closure_49(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_49(ltedpeg__prepeg_adt_t ivar_11, ordstruct_adt__ordstruct_adt_t ivar_1, ltedpeg_funtype_46_t ivar_3, ltedpeg_funtype_47_t ivar_5, ltedpeg_funtype_48_t ivar_7, ordstruct_adt__ordstruct_adt_t ivar_2){
        ordstruct_adt__ordstruct_adt_t result;

        bool_t ivar_30;
        ivar_11->count++;
        ivar_30 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_11);
        if (ivar_30){
             release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_11);
             //copying to ordstruct_adt__ordstruct_adt from ordstruct_adt__ordstruct_adt;
             result = (ordstruct_adt__ordstruct_adt_t)ivar_1;
             if (result != NULL) result->count++;
        } else {
             bool_t ivar_34;
             ivar_11->count++;
             ivar_34 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_11);
             if (ivar_34){
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_11);
           //copying to ordstruct_adt__ordstruct_adt from ordstruct_adt__ordstruct_adt;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_2;
           if (result != NULL) result->count++;
             } else {
           bool_t ivar_48;
           ivar_11->count++;
           ivar_48 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_11);
           if (ivar_48){
           dpeg__dpeg_grammar_t ivar_38;
           ivar_38 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_11);
           ivar_3->count++;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_3->ftbl->fptr(ivar_3, ivar_38);
           } else {
           bool_t ivar_62;
           ivar_11->count++;
           ivar_62 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_11);
           if (ivar_62){
            uint8_t ivar_52;
            ivar_52 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_11);
            ivar_5->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_5->ftbl->fptr(ivar_5, ivar_52);
           } else {
            uint8_t ivar_66;
            ivar_11->count++;
            ivar_66 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_11);
            uint8_t ivar_67;
            ivar_11->count++;
            ivar_67 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_11);
            uint8_t ivar_68;
            ivar_68 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_11);
            ivar_7->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_7->ftbl->mptr(ivar_7, ivar_66, ivar_67, ivar_68);};};};};
        return result;
}

ltedpeg_closure_49_t new_ltedpeg_closure_49(void){
        static struct ltedpeg_funtype_45_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_45_t, ltedpeg__prepeg_adt_t))&f_ltedpeg_closure_49, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_45_t, ltedpeg__prepeg_adt_t))&m_ltedpeg_closure_49, .rptr =  (void (*)(ltedpeg_funtype_45_t))&release_ltedpeg_closure_49, .cptr = (ltedpeg_funtype_45_t (*)(ltedpeg_funtype_45_t))&copy_ltedpeg_closure_49};
        ltedpeg_closure_49_t tmp = (ltedpeg_closure_49_t) safe_malloc(sizeof(struct ltedpeg_closure_49_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_49(ltedpeg_funtype_45_t closure){
        ltedpeg_closure_49_t x = (ltedpeg_closure_49_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->fvar_1);
         release_ltedpeg_funtype_46((ltedpeg_funtype_46_t)x->fvar_2);
         release_ltedpeg_funtype_47((ltedpeg_funtype_47_t)x->fvar_3);
         release_ltedpeg_funtype_48((ltedpeg_funtype_48_t)x->fvar_4);
         release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->htbl->data[j].key); release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_49_t copy_ltedpeg_closure_49(ltedpeg_closure_49_t x){
        ltedpeg_closure_49_t y = new_ltedpeg_closure_49();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        y->fvar_5 = x->fvar_5; x->fvar_5->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_45_htbl_t new_htbl = (ltedpeg_funtype_45_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_45_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_45_hashentry_t * new_data = (ltedpeg_funtype_45_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_45_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__prepeg_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_50(ltedpeg_funtype_50_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_50_t copy_ltedpeg_funtype_50(ltedpeg_funtype_50_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_50(ltedpeg_funtype_50_t x, ltedpeg_funtype_50_t y){
        return false;}

char* json_ltedpeg_funtype_50(ltedpeg_funtype_50_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_50\""); return result;}

void release_ltedpeg_funtype_51(ltedpeg_funtype_51_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_51_t copy_ltedpeg_funtype_51(ltedpeg_funtype_51_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_51(ltedpeg_funtype_51_t x, ltedpeg_funtype_51_t y){
        return false;}

char* json_ltedpeg_funtype_51(ltedpeg_funtype_51_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_51\""); return result;}

void release_ltedpeg_funtype_52(ltedpeg_funtype_52_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_52_t copy_ltedpeg_funtype_52(ltedpeg_funtype_52_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_52(ltedpeg_funtype_52_t x, ltedpeg_funtype_52_t y){
        return false;}

char* json_ltedpeg_funtype_52(ltedpeg_funtype_52_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_52\""); return result;}


ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_53(struct ltedpeg_closure_53_s * closure, ltedpeg__prepeg_adt_t bvar){
        ltedpeg_funtype_45_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_50_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_51_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_52_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_45_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)closure);
        ordstruct_adt__ordstruct_adt_t result;
        result = (ordstruct_adt__ordstruct_adt_t)h_ltedpeg_closure_53(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);
        return result;
}

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_53(struct ltedpeg_closure_53_s * closure, ltedpeg__prepeg_adt_t bvar){
        ltedpeg_funtype_45_t fvar_1 = closure->fvar_1;
        ltedpeg_funtype_50_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_51_t fvar_3 = closure->fvar_3;
        ltedpeg_funtype_52_t fvar_4 = closure->fvar_4;
        ltedpeg_funtype_45_t fvar_5 = closure->fvar_5;
        fvar_1->count++;
        fvar_2->count++;
        fvar_3->count++;
        fvar_4->count++;
        fvar_5->count++;
        release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)closure);
        return h_ltedpeg_closure_53(bvar, fvar_1, fvar_2, fvar_3, fvar_4, fvar_5);}

ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_53(ltedpeg__prepeg_adt_t ivar_13, ltedpeg_funtype_45_t ivar_1, ltedpeg_funtype_50_t ivar_5, ltedpeg_funtype_51_t ivar_7, ltedpeg_funtype_52_t ivar_9, ltedpeg_funtype_45_t ivar_3){
        ordstruct_adt__ordstruct_adt_t result;

        bool_t ivar_40;
        ivar_13->count++;
        ivar_40 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_13);
        if (ivar_40){
             ivar_1->count++;
             result = (ordstruct_adt__ordstruct_adt_t)ivar_1->ftbl->fptr(ivar_1, ivar_13);
        } else {
             bool_t ivar_50;
             ivar_13->count++;
             ivar_50 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_13);
             if (ivar_50){
           ivar_3->count++;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_3->ftbl->fptr(ivar_3, ivar_13);
             } else {
           bool_t ivar_66;
           ivar_13->count++;
           ivar_66 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_13);
           if (ivar_66){
           dpeg__dpeg_grammar_t ivar_54;
           ivar_13->count++;
           ivar_54 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_13);
           ivar_5->count++;
           result = (ordstruct_adt__ordstruct_adt_t)ivar_5->ftbl->mptr(ivar_5, ivar_54, ivar_13);
           } else {
           bool_t ivar_82;
           ivar_13->count++;
           ivar_82 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_13);
           if (ivar_82){
            uint8_t ivar_70;
            ivar_13->count++;
            ivar_70 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_13);
            ivar_7->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_7->ftbl->mptr(ivar_7, ivar_70, ivar_13);
           } else {
            uint8_t ivar_86;
            ivar_13->count++;
            ivar_86 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_13);
            uint8_t ivar_87;
            ivar_13->count++;
            ivar_87 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_13);
            uint8_t ivar_88;
            ivar_13->count++;
            ivar_88 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_13);
            ivar_9->count++;
            result = (ordstruct_adt__ordstruct_adt_t)ivar_9->ftbl->mptr(ivar_9, ivar_86, ivar_87, ivar_88, ivar_13);};};};};
        return result;
}

ltedpeg_closure_53_t new_ltedpeg_closure_53(void){
        static struct ltedpeg_funtype_45_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_45_t, ltedpeg__prepeg_adt_t))&f_ltedpeg_closure_53, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_45_t, ltedpeg__prepeg_adt_t))&m_ltedpeg_closure_53, .rptr =  (void (*)(ltedpeg_funtype_45_t))&release_ltedpeg_closure_53, .cptr = (ltedpeg_funtype_45_t (*)(ltedpeg_funtype_45_t))&copy_ltedpeg_closure_53};
        ltedpeg_closure_53_t tmp = (ltedpeg_closure_53_t) safe_malloc(sizeof(struct ltedpeg_closure_53_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_53(ltedpeg_funtype_45_t closure){
        ltedpeg_closure_53_t x = (ltedpeg_closure_53_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)x->fvar_1);
         release_ltedpeg_funtype_50((ltedpeg_funtype_50_t)x->fvar_2);
         release_ltedpeg_funtype_51((ltedpeg_funtype_51_t)x->fvar_3);
         release_ltedpeg_funtype_52((ltedpeg_funtype_52_t)x->fvar_4);
         release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)x->fvar_5);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->htbl->data[j].key); release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_53_t copy_ltedpeg_closure_53(ltedpeg_closure_53_t x){
        ltedpeg_closure_53_t y = new_ltedpeg_closure_53();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        y->fvar_5 = x->fvar_5; x->fvar_5->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_45_htbl_t new_htbl = (ltedpeg_funtype_45_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_45_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_45_hashentry_t * new_data = (ltedpeg_funtype_45_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_45_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__prepeg_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_54(ltedpeg_funtype_54_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_54_t copy_ltedpeg_funtype_54(ltedpeg_funtype_54_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_54(ltedpeg_funtype_54_t x, ltedpeg_funtype_54_t y){
        return false;}

char* json_ltedpeg_funtype_54(ltedpeg_funtype_54_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_54\""); return result;}


bool_t f_ltedpeg_closure_55(struct ltedpeg_closure_55_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_55(bvar, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_55(struct ltedpeg_closure_55_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_55(bvar, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_55(ltedpeg__ent_adt_t ivar_5, uint32_t ivar_1, uint32_t ivar_2){
        bool_t result;

        uint64_t ivar_6;
        uint32_t ivar_9;
        ivar_9 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_5);
        ivar_6 = (uint64_t)(ivar_2 + ivar_9);
        result = (ivar_6 <= ivar_1);
        return result;
}

ltedpeg_closure_55_t new_ltedpeg_closure_55(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_55, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_55, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_55, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_55};
        ltedpeg_closure_55_t tmp = (ltedpeg_closure_55_t) safe_malloc(sizeof(struct ltedpeg_closure_55_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_55(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_55_t x = (ltedpeg_closure_55_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_55_t copy_ltedpeg_closure_55(ltedpeg_closure_55_t x){
        ltedpeg_closure_55_t y = new_ltedpeg_closure_55();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint32_t)x->fvar_1;
        y->fvar_2 = (uint32_t)x->fvar_2;
        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_56(struct ltedpeg_closure_56_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_56(bvar, fvar_1);
        return result;
}

bool_t m_ltedpeg_closure_56(struct ltedpeg_closure_56_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_56(bvar, fvar_1);}

bool_t h_ltedpeg_closure_56(ltedpeg__ent_adt_t ivar_4, uint32_t ivar_1){
        bool_t result;

        bool_t ivar_5;
        ivar_4->count++;
        ivar_5 = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_4);
        if (ivar_5){
             bool_t ivar_10;
             uint32_t ivar_12;
             ivar_4->count++;
             ivar_12 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_4);
             ivar_10 = (ivar_12 <= ivar_1);
             if (ivar_10){
           uint8_t ivar_18;
           ivar_18 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_4);
           uint8_t ivar_19;
           ivar_19 = (uint8_t)ltedpeg__num_non_terminals();
           result = (ivar_18 <= ivar_19);
             } else {
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_4);
           result = (bool_t) false;};
        } else {
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_4);
             result = (bool_t) false;};
        return result;
}

ltedpeg_closure_56_t new_ltedpeg_closure_56(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_56, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_56, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_56, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_56};
        ltedpeg_closure_56_t tmp = (ltedpeg_closure_56_t) safe_malloc(sizeof(struct ltedpeg_closure_56_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_56(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_56_t x = (ltedpeg_closure_56_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_56_t copy_ltedpeg_closure_56(ltedpeg_closure_56_t x){
        ltedpeg_closure_56_t y = new_ltedpeg_closure_56();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint32_t)x->fvar_1;
        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_57(struct ltedpeg_closure_57_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_57(bvar, fvar_1);
        return result;
}

bool_t m_ltedpeg_closure_57(struct ltedpeg_closure_57_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_57(bvar, fvar_1);}

bool_t h_ltedpeg_closure_57(ltedpeg__ent_adt_t ivar_4, uint32_t ivar_1){
        bool_t result;

        bool_t ivar_5;
        ltedpeg_funtype_54_t ivar_10;
        ivar_10 = (ltedpeg_funtype_54_t)ltedpeg__good_push_entryp((uint32_t)ivar_1);
        ivar_4->count++;
        ivar_5 = (bool_t)ivar_10->ftbl->fptr(ivar_10, ivar_4);
        if (ivar_5){
             uint8_t ivar_16;
             ivar_16 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_4);
             uint8_t ivar_17;
             ivar_17 = (uint8_t)ltedpeg__num_non_terminals();
             result = (ivar_16 < ivar_17);
        } else {
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_4);
             result = (bool_t) false;};
        return result;
}

ltedpeg_closure_57_t new_ltedpeg_closure_57(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_57, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_57, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_57, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_57};
        ltedpeg_closure_57_t tmp = (ltedpeg_closure_57_t) safe_malloc(sizeof(struct ltedpeg_closure_57_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_57(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_57_t x = (ltedpeg_closure_57_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_57_t copy_ltedpeg_closure_57(ltedpeg_closure_57_t x){
        ltedpeg_closure_57_t y = new_ltedpeg_closure_57();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint32_t)x->fvar_1;
        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_58(struct ltedpeg_closure_58_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_58(bvar, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_58(struct ltedpeg_closure_58_s * closure, ltedpeg__ent_adt_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_58(bvar, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_58(ltedpeg__ent_adt_t ivar_5, uint32_t ivar_1, uint32_t ivar_2){
        bool_t result;

        bool_t ivar_6;
        bool_t ivar_8;
        ivar_5->count++;
        ivar_8 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_5);
        if (ivar_8){
             ltedpeg_funtype_54_t ivar_16;
             ivar_16 = (ltedpeg_funtype_54_t)ltedpeg__good_good_entryp((uint32_t)ivar_1, (uint32_t)ivar_2);
             ivar_5->count++;
             ivar_6 = (bool_t)ivar_16->ftbl->fptr(ivar_16, ivar_5);
        } else {
             ivar_6 = (bool_t) true;};
        if (ivar_6){
             bool_t ivar_25;
             ivar_5->count++;
             ivar_25 = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_5);
             if (ivar_25){
           ltedpeg_funtype_54_t ivar_33;
           ivar_33 = (ltedpeg_funtype_54_t)ltedpeg__good_push_entryp((uint32_t)ivar_1);
           result = (bool_t)ivar_33->ftbl->fptr(ivar_33, ivar_5);
             } else {
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_5);
           result = (bool_t) true;};
        } else {
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_5);
             result = (bool_t) false;};
        return result;
}

ltedpeg_closure_58_t new_ltedpeg_closure_58(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_58, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_58, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_58, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_58};
        ltedpeg_closure_58_t tmp = (ltedpeg_closure_58_t) safe_malloc(sizeof(struct ltedpeg_closure_58_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_58(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_58_t x = (ltedpeg_closure_58_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_58_t copy_ltedpeg_closure_58(ltedpeg_closure_58_t x){
        ltedpeg_closure_58_t y = new_ltedpeg_closure_58();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint32_t)x->fvar_1;
        y->fvar_2 = (uint32_t)x->fvar_2;
        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_array_59_t new_ltedpeg_array_59(uint32_t size){
        ltedpeg_array_59_t tmp = (ltedpeg_array_59_t) safe_malloc(sizeof(struct ltedpeg_array_59_s) + (size * sizeof(ltedpeg__ent_adt_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_ltedpeg_array_59(ltedpeg_array_59_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_ltedpeg_array_59_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_array_59((ltedpeg_array_59_t)x);
}

ltedpeg_array_59_t copy_ltedpeg_array_59(ltedpeg_array_59_t x){
        ltedpeg_array_59_t tmp = new_ltedpeg_array_59(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_ltedpeg_array_59(ltedpeg_array_59_t x, ltedpeg_array_59_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_ltedpeg__ent_adt(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_ltedpeg_array_59(ltedpeg_array_59_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_ltedpeg__ent_adt(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpeg_array_59_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpeg_array_59((ltedpeg_array_59_t)x, (ltedpeg_array_59_t)y);
}

char * json_ltedpeg_array_59_ptr(pointer_t x, type_actual_t T){
        return json_ltedpeg_array_59((ltedpeg_array_59_t)x);
}

actual_ltedpeg_array_59_t actual_ltedpeg_array_59(void){
        actual_ltedpeg_array_59_t new = (actual_ltedpeg_array_59_t)safe_malloc(sizeof(struct actual_ltedpeg_array_59_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_array_59_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_array_59_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_array_59_ptr);
 

 
        return new;
 }

ltedpeg_array_59_t update_ltedpeg_array_59(ltedpeg_array_59_t x, uint32_t i, ltedpeg__ent_adt_t v){
         ltedpeg_array_59_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_ltedpeg_array_59(x);
                      x->count--;};
        ltedpeg__ent_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}

ltedpeg_array_59_t upgrade_ltedpeg_array_59(ltedpeg_array_59_t x, uint32_t i, ltedpeg__ent_adt_t v){
         ltedpeg_array_59_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct ltedpeg_array_59_s) + (newmax * sizeof(ltedpeg__ent_adt_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_ltedpeg_array_59(x);
                            x->count--;};
        ltedpeg__ent_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}




ltedpeg__scaffold_t new_ltedpeg__scaffold(uint32_t size){
        ltedpeg__scaffold_t tmp = (ltedpeg__scaffold_t) safe_malloc(sizeof(struct ltedpeg__scaffold_s) + (size * sizeof(ltedpeg_array_59_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_ltedpeg__scaffold(ltedpeg__scaffold_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_ltedpeg_array_59((ltedpeg_array_59_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_ltedpeg__scaffold_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)x);
}

ltedpeg__scaffold_t copy_ltedpeg__scaffold(ltedpeg__scaffold_t x){
        ltedpeg__scaffold_t tmp = new_ltedpeg__scaffold(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_ltedpeg__scaffold(ltedpeg__scaffold_t x, ltedpeg__scaffold_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_ltedpeg_array_59(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_ltedpeg__scaffold(ltedpeg__scaffold_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_ltedpeg_array_59(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpeg__scaffold_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpeg__scaffold((ltedpeg__scaffold_t)x, (ltedpeg__scaffold_t)y);
}

char * json_ltedpeg__scaffold_ptr(pointer_t x, type_actual_t T){
        return json_ltedpeg__scaffold((ltedpeg__scaffold_t)x);
}

actual_ltedpeg__scaffold_t actual_ltedpeg__scaffold(void){
        actual_ltedpeg__scaffold_t new = (actual_ltedpeg__scaffold_t)safe_malloc(sizeof(struct actual_ltedpeg__scaffold_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__scaffold_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__scaffold_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__scaffold_ptr);
 

 
        return new;
 }

ltedpeg__scaffold_t update_ltedpeg__scaffold(ltedpeg__scaffold_t x, uint32_t i, ltedpeg_array_59_t v){
         ltedpeg__scaffold_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_ltedpeg__scaffold(x);
                      x->count--;};
        ltedpeg_array_59_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_ltedpeg_array_59((ltedpeg_array_59_t)yelems[i]);};
         yelems[i] = v;
         return y;}

ltedpeg__scaffold_t upgrade_ltedpeg__scaffold(ltedpeg__scaffold_t x, uint32_t i, ltedpeg_array_59_t v){
         ltedpeg__scaffold_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct ltedpeg__scaffold_s) + (newmax * sizeof(ltedpeg_array_59_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_ltedpeg__scaffold(x);
                            x->count--;};
        ltedpeg_array_59_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_ltedpeg_array_59((ltedpeg_array_59_t)yelems[i]);};
         yelems[i] = v;
         return y;}




ltedpeg__lang_spec_t new_ltedpeg__lang_spec(uint32_t size){
        ltedpeg__lang_spec_t tmp = (ltedpeg__lang_spec_t) safe_malloc(sizeof(struct ltedpeg__lang_spec_s) + (size * sizeof(ltedpeg__prepeg_adt_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_ltedpeg__lang_spec(ltedpeg__lang_spec_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_ltedpeg__lang_spec_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x);
}

ltedpeg__lang_spec_t copy_ltedpeg__lang_spec(ltedpeg__lang_spec_t x){
        ltedpeg__lang_spec_t tmp = new_ltedpeg__lang_spec(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){tmp->elems[i] = x->elems[i];
                if (i < x->size) x->elems[i]->count++;};
         return tmp;}

bool_t equal_ltedpeg__lang_spec(ltedpeg__lang_spec_t x, ltedpeg__lang_spec_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_ltedpeg__prepeg_adt(x->elems[i], y->elems[i]); i++;};
        return tmp;}

char * json_ltedpeg__lang_spec(ltedpeg__lang_spec_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_ltedpeg__prepeg_adt(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpeg__lang_spec_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x, (ltedpeg__lang_spec_t)y);
}

char * json_ltedpeg__lang_spec_ptr(pointer_t x, type_actual_t T){
        return json_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x);
}

actual_ltedpeg__lang_spec_t actual_ltedpeg__lang_spec(void){
        actual_ltedpeg__lang_spec_t new = (actual_ltedpeg__lang_spec_t)safe_malloc(sizeof(struct actual_ltedpeg__lang_spec_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__lang_spec_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__lang_spec_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__lang_spec_ptr);
 

 
        return new;
 }

ltedpeg__lang_spec_t update_ltedpeg__lang_spec(ltedpeg__lang_spec_t x, uint32_t i, ltedpeg__prepeg_adt_t v){
         ltedpeg__lang_spec_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_ltedpeg__lang_spec(x);
                      x->count--;};
        ltedpeg__prepeg_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}

ltedpeg__lang_spec_t upgrade_ltedpeg__lang_spec(ltedpeg__lang_spec_t x, uint32_t i, ltedpeg__prepeg_adt_t v){
         ltedpeg__lang_spec_t y;
        uint32_t xmax = x->max;
        uint32_t xsize = x->size;
         if (x->count == 1 && i < xmax){y = x;}
                 else if (i >= xmax){
                            uint32_t newmax = ((xmax < UINT32_MAX/2)  ? ((i < 2 * (xmax + 1))  ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                            y = safe_realloc(x, sizeof(struct ltedpeg__lang_spec_s) + (newmax * sizeof(ltedpeg__prepeg_adt_t)));
                            y->count = 1;
                            y->max = newmax;
                            for (uint32_t j = xsize; j < newmax; j++){y->elems[j] = NULL;};}
                         else {y = copy_ltedpeg__lang_spec(x);
                            x->count--;};
        ltedpeg__prepeg_adt_t * yelems = y->elems;
        if (v != NULL){v->count++;};
        y->size = xsize > i ? xsize : i + 1;
        if (i < xmax && yelems[i] != NULL){release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)yelems[i]);};
         yelems[i] = v;
         return y;}



void release_ltedpeg_funtype_62(ltedpeg_funtype_62_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_62_t copy_ltedpeg_funtype_62(ltedpeg_funtype_62_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_62(ltedpeg_funtype_62_t x, ltedpeg_funtype_62_t y){
        return false;}

char* json_ltedpeg_funtype_62(ltedpeg_funtype_62_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_62\""); return result;}


bool_t f_ltedpeg_closure_63(struct ltedpeg_closure_63_s * closure, ltedpeg_record_9_t bvar){
        uint32_t bvar_1;
        bvar_1 = (uint32_t)bvar->project_1;
        uint8_t bvar_2;
        bvar_2 = (uint8_t)bvar->project_2;
        release_ltedpeg_record_9((ltedpeg_record_9_t)bvar);
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_62((ltedpeg_funtype_62_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_63(bvar_1, bvar_2, fvar_1);
        return result;
}

bool_t m_ltedpeg_closure_63(struct ltedpeg_closure_63_s * closure, uint32_t bvar_1, uint8_t bvar_2){
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_62((ltedpeg_funtype_62_t)closure);
        return h_ltedpeg_closure_63(bvar_1, bvar_2, fvar_1);}

bool_t h_ltedpeg_closure_63(uint32_t ivar_7, uint8_t ivar_8, ltedpeg__scaffold_t ivar_2){
        bool_t result;

        ltedpeg__ent_adt_t ivar_21;
        ltedpeg_array_59_t ivar_12;
        ltedpeg_array_59_t ivar_14;
        ivar_14 = (ltedpeg_array_59_t)ivar_2->elems[ivar_7];
        ivar_14->count++;
        //copying to ltedpeg_array_59 from ltedpeg_array_59;
        ivar_12 = (ltedpeg_array_59_t)ivar_14;
        if (ivar_12 != NULL) ivar_12->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_14);
        ivar_21 = (ltedpeg__ent_adt_t)ivar_12->elems[ivar_8];
        ivar_21->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_12);
        result = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_21);
        return result;
}

ltedpeg_closure_63_t new_ltedpeg_closure_63(void){
        static struct ltedpeg_funtype_62_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_62_t, ltedpeg_record_9_t))&f_ltedpeg_closure_63, .mptr = (bool_t (*)(ltedpeg_funtype_62_t, uint32_t, uint8_t))&m_ltedpeg_closure_63, .rptr =  (void (*)(ltedpeg_funtype_62_t))&release_ltedpeg_closure_63, .cptr = (ltedpeg_funtype_62_t (*)(ltedpeg_funtype_62_t))&copy_ltedpeg_closure_63};
        ltedpeg_closure_63_t tmp = (ltedpeg_closure_63_t) safe_malloc(sizeof(struct ltedpeg_closure_63_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_63(ltedpeg_funtype_62_t closure){
        ltedpeg_closure_63_t x = (ltedpeg_closure_63_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_1);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_9((ltedpeg_record_9_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_63_t copy_ltedpeg_closure_63(ltedpeg_closure_63_t x){
        ltedpeg_closure_63_t y = new_ltedpeg_closure_63();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_62_htbl_t new_htbl = (ltedpeg_funtype_62_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_62_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_62_hashentry_t * new_data = (ltedpeg_funtype_62_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_62_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_9_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_64_t new_ltedpeg_record_64(void){
        ltedpeg_record_64_t tmp = (ltedpeg_record_64_t) safe_malloc(sizeof(struct ltedpeg_record_64_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_64(ltedpeg_record_64_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_1);
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_64_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_64((ltedpeg_record_64_t)x);
}

ltedpeg_record_64_t copy_ltedpeg_record_64(ltedpeg_record_64_t x){
        ltedpeg_record_64_t y = new_ltedpeg_record_64();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = x->project_2;
        if (y->project_2 != NULL){y->project_2->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_64(ltedpeg_record_64_t x, ltedpeg_record_64_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_1, (ltedpeg__ent_adt_t)y->project_1); tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2, (ltedpeg__ent_adt_t)y->project_2);
        return tmp;}

char * json_ltedpeg_record_64(ltedpeg_record_64_t x){
        char * tmp[2]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2));
         char * result = json_list_with_sep(tmp, 2,  '{', ',', '}');
         for (uint32_t i = 0; i < 2; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_64_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_64_t T){
        return equal_ltedpeg_record_64((ltedpeg_record_64_t)x, (ltedpeg_record_64_t)y);
}

char * json_ltedpeg_record_64_ptr(pointer_t x, actual_ltedpeg_record_64_t T){
        return json_ltedpeg_record_64((ltedpeg_record_64_t)x);
}

actual_ltedpeg_record_64_t actual_ltedpeg_record_64(void){
        actual_ltedpeg_record_64_t new = (actual_ltedpeg_record_64_t)safe_malloc(sizeof(struct actual_ltedpeg_record_64_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_64_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_64_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_64_ptr);
 

 
        return new;
 }

ltedpeg_record_64_t update_ltedpeg_record_64_project_1(ltedpeg_record_64_t x, ltedpeg__ent_adt_t v){
        ltedpeg_record_64_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_1);};}
        else {y = copy_ltedpeg_record_64(x); x->count--; y->project_1->count--;};
        y->project_1 = (ltedpeg__ent_adt_t)v;
        return y;}

ltedpeg_record_64_t update_ltedpeg_record_64_project_2(ltedpeg_record_64_t x, ltedpeg__ent_adt_t v){
        ltedpeg_record_64_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_2 != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_2);};}
        else {y = copy_ltedpeg_record_64(x); x->count--; y->project_2->count--;};
        y->project_2 = (ltedpeg__ent_adt_t)v;
        return y;}



void release_ltedpeg_funtype_65(ltedpeg_funtype_65_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_65_t copy_ltedpeg_funtype_65(ltedpeg_funtype_65_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_65(ltedpeg_funtype_65_t x, ltedpeg_funtype_65_t y){
        return false;}

char* json_ltedpeg_funtype_65(ltedpeg_funtype_65_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_65\""); return result;}


bool_t f_ltedpeg_closure_66(struct ltedpeg_closure_66_s * closure, ltedpeg_record_64_t bvar){
        ltedpeg__ent_adt_t bvar_1;
        bvar_1 = (ltedpeg__ent_adt_t)bvar->project_1;
        bvar->project_1->count++;
        ltedpeg__ent_adt_t bvar_2;
        bvar_2 = (ltedpeg__ent_adt_t)bvar->project_2;
        bvar->project_2->count++;
        release_ltedpeg_record_64((ltedpeg_record_64_t)bvar);
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        ltedpeg__scaffold_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_65((ltedpeg_funtype_65_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_66(bvar_1, bvar_2, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_66(struct ltedpeg_closure_66_s * closure, ltedpeg__ent_adt_t bvar_1, ltedpeg__ent_adt_t bvar_2){
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        ltedpeg__scaffold_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_65((ltedpeg_funtype_65_t)closure);
        return h_ltedpeg_closure_66(bvar_1, bvar_2, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_66(ltedpeg__ent_adt_t ivar_8, ltedpeg__ent_adt_t ivar_9, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_3){
        bool_t result;

        /* p1 */ uint32_t ivar_10;
        ivar_8->count++;
        ivar_10 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_8);
        /* nt1 */ uint8_t ivar_14;
        ivar_14 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_8);
        /* p2 */ uint32_t ivar_18;
        ivar_9->count++;
        ivar_18 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_9);
        /* nt2 */ uint8_t ivar_22;
        ivar_22 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_9);
        bool_t ivar_26;
        uint8_t ivar_29;
        ivar_29 = (uint8_t)ltedpeg__num_non_terminals();
        ivar_26 = (ivar_14 >= ivar_29);
        if (ivar_26){
             result = (bool_t) true;
        } else {
             ltedpeg__prepeg_adt_t ivar_31;
             ivar_31 = (ltedpeg__prepeg_adt_t)ivar_2->elems[ivar_14];
             ivar_31->count++;
             bool_t ivar_129;
             ivar_31->count++;
             ivar_129 = (bool_t)rec_ltedpeg__ltep((ltedpeg__prepeg_adt_t)ivar_31);
             if (ivar_129){
           uint8_t ivar_36;
           ivar_31->count++;
           ivar_36 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_31);
           uint8_t ivar_37;
           ivar_31->count++;
           ivar_37 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_31);
           uint8_t ivar_38;
           ivar_38 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_31);
           bool_t ivar_48;
           bool_t ivar_50;
           ivar_50 = (ivar_18 == ivar_10);
           if (ivar_50){
           ivar_48 = (ivar_22 == ivar_36);
           } else {
           ivar_48 = (bool_t) false;};
           if (ivar_48){
           result = (bool_t) true;
           } else {
           bool_t ivar_59;
           bool_t ivar_61;
           ltedpeg__ent_adt_t ivar_75;
           ltedpeg_array_59_t ivar_66;
           ltedpeg_array_59_t ivar_68;
           ivar_68 = (ltedpeg_array_59_t)ivar_3->elems[ivar_10];
           ivar_68->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_66 = (ltedpeg_array_59_t)ivar_68;
           if (ivar_66 != NULL) ivar_66->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_68);
           ivar_75 = (ltedpeg__ent_adt_t)ivar_66->elems[ivar_36];
           ivar_75->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_66);
           ivar_61 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_75);
           if (ivar_61){
            bool_t ivar_76;
            ivar_76 = (ivar_22 == ivar_37);
            if (ivar_76){
             uint64_t ivar_82;
             uint32_t ivar_84;
             ltedpeg__ent_adt_t ivar_97;
             ltedpeg_array_59_t ivar_88;
             ltedpeg_array_59_t ivar_90;
             ivar_90 = (ltedpeg_array_59_t)ivar_3->elems[ivar_10];
             ivar_90->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_88 = (ltedpeg_array_59_t)ivar_90;
             if (ivar_88 != NULL) ivar_88->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_90);
             ivar_97 = (ltedpeg__ent_adt_t)ivar_88->elems[ivar_36];
             ivar_97->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_88);
             ivar_84 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_97);
             ivar_82 = (uint64_t)(ivar_10 + ivar_84);
             ivar_59 = (ivar_18 == ivar_82);
            } else {
             ivar_59 = (bool_t) false;};
           } else {
            ivar_59 = (bool_t) false;};
           if (ivar_59){
            result = (bool_t) true;
           } else {
            bool_t ivar_102;
            ltedpeg__ent_adt_t ivar_116;
            ltedpeg_array_59_t ivar_107;
            ltedpeg_array_59_t ivar_109;
            ivar_109 = (ltedpeg_array_59_t)ivar_3->elems[ivar_10];
            ivar_109->count++;
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_107 = (ltedpeg_array_59_t)ivar_109;
            if (ivar_107 != NULL) ivar_107->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_109);
            ivar_116 = (ltedpeg__ent_adt_t)ivar_107->elems[ivar_36];
            ivar_116->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_107);
            ivar_102 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_116);
            if (ivar_102){
             bool_t ivar_117;
             ivar_117 = (ivar_22 == ivar_38);
             if (ivar_117){
              result = (ivar_18 == ivar_10);
             } else {
              result = (bool_t) false;};
            } else {
             result = (bool_t) false;};};};
             } else {
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_31);
           result = (bool_t) false;};};
        return result;
}

ltedpeg_closure_66_t new_ltedpeg_closure_66(void){
        static struct ltedpeg_funtype_65_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_65_t, ltedpeg_record_64_t))&f_ltedpeg_closure_66, .mptr = (bool_t (*)(ltedpeg_funtype_65_t, ltedpeg__ent_adt_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_66, .rptr =  (void (*)(ltedpeg_funtype_65_t))&release_ltedpeg_closure_66, .cptr = (ltedpeg_funtype_65_t (*)(ltedpeg_funtype_65_t))&copy_ltedpeg_closure_66};
        ltedpeg_closure_66_t tmp = (ltedpeg_closure_66_t) safe_malloc(sizeof(struct ltedpeg_closure_66_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_66(ltedpeg_funtype_65_t closure){
        ltedpeg_closure_66_t x = (ltedpeg_closure_66_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_1);
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_64((ltedpeg_record_64_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_66_t copy_ltedpeg_closure_66(ltedpeg_closure_66_t x){
        ltedpeg_closure_66_t y = new_ltedpeg_closure_66();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_65_htbl_t new_htbl = (ltedpeg_funtype_65_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_65_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_65_hashentry_t * new_data = (ltedpeg_funtype_65_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_65_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_64_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_67(ltedpeg_funtype_67_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_67_t copy_ltedpeg_funtype_67(ltedpeg_funtype_67_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_67(ltedpeg_funtype_67_htbl_t htbl, uint32_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_67_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_67_t dupdate_ltedpeg_funtype_67(ltedpeg_funtype_67_t a, uint32_t i, mpz_ptr_t v){
        ltedpeg_funtype_67_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_67_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_67_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_67_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_67_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint32_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_67_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_67_hashentry_t * new_data = (ltedpeg_funtype_67_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_67_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = (uint32_t)0; 
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
                                new_data[new_loc].key = (uint32_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                mpz_set(new_data[new_loc].value, data[j].value);
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                for (uint32_t j=0; j < size; j++){mpz_clear(data[j].value);};
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_67(htbl, i, ihash);
        ltedpeg_funtype_67_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint32_t)i; htbl->data[hashindex].keyhash = ihash; mpz_set(htbl->data[hashindex].value, v); htbl->num_entries++;}
            else {mpz_set(htbl->data[hashindex].value, v);};
        return a;

}

ltedpeg_funtype_67_t update_ltedpeg_funtype_67(ltedpeg_funtype_67_t a, uint32_t i, mpz_ptr_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_67(a, i, v);
            } else {
                ltedpeg_funtype_67_t x = copy_ltedpeg_funtype_67(a);
                a->count--;
                return dupdate_ltedpeg_funtype_67(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_67(ltedpeg_funtype_67_t x, ltedpeg_funtype_67_t y){
        return false;}

char* json_ltedpeg_funtype_67(ltedpeg_funtype_67_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_67\""); return result;}


ltedpeg_array_68_t new_ltedpeg_array_68(uint32_t size){
        ltedpeg_array_68_t tmp = (ltedpeg_array_68_t) safe_malloc(sizeof(struct ltedpeg_array_68_s) + (size * sizeof(mpz_ptr_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_ltedpeg_array_68(ltedpeg_array_68_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_ltedpeg_array_68_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_array_68((ltedpeg_array_68_t)x);
}

ltedpeg_array_68_t copy_ltedpeg_array_68(ltedpeg_array_68_t x){
        ltedpeg_array_68_t tmp = new_ltedpeg_array_68(x->max);
        tmp->count = 1;
        tmp->size = x->max;
        for (uint32_t i = 0; i < x->max; i++){ tmp->elems[i] = (mpz_ptr_t)safe_malloc(sizeof(mpz_t));
                mpz_init(tmp->elems[i]);
                if (i < x->size) mpz_set(tmp->elems[i], x->elems[i]);};
         return tmp;}

bool_t equal_ltedpeg_array_68(ltedpeg_array_68_t x, ltedpeg_array_68_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while  (i < x->size && tmp){tmp = (mpz_cmp(x->elems[i], y->elems[i]) == 0); i++;};
        return tmp;}

char * json_ltedpeg_array_68(ltedpeg_array_68_t x){
        char ** tmp = (char **)safe_malloc(sizeof(void *) * x->size);
        for (uint32_t i = 0; i < x->size; i++){tmp[i] = json_mpz(x->elems[i]);};
        char * result = json_list_with_sep(tmp, x->size, '[', ',', ']');
        for (uint32_t i = 0; i < x->size; i++) free(tmp[i]);
        free(tmp);
        return result;}

bool_t equal_ltedpeg_array_68_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_ltedpeg_array_68((ltedpeg_array_68_t)x, (ltedpeg_array_68_t)y);
}

char * json_ltedpeg_array_68_ptr(pointer_t x, type_actual_t T){
        return json_ltedpeg_array_68((ltedpeg_array_68_t)x);
}

actual_ltedpeg_array_68_t actual_ltedpeg_array_68(void){
        actual_ltedpeg_array_68_t new = (actual_ltedpeg_array_68_t)safe_malloc(sizeof(struct actual_ltedpeg_array_68_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_array_68_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_array_68_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_array_68_ptr);
 

 
        return new;
 }

ltedpeg_array_68_t update_ltedpeg_array_68(ltedpeg_array_68_t x, uint32_t i, mpz_t v){
        ltedpeg_array_68_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_ltedpeg_array_68(x );
                x->count--;};
        mpz_set(y->elems[i], v);
        return y;}

ltedpeg_array_68_t upgrade_ltedpeg_array_68(ltedpeg_array_68_t x, uint32_t i, mpz_t v){
        ltedpeg_array_68_t y;
        uint32_t xmax = x->max;
         if (x->count == 1 && i < xmax){y = x;}
           else if (i >= xmax){uint32_t newmax = ((xmax < UINT32_MAX/2) ? ((i < 2 * (xmax + 1)) ? 2 * (xmax + 1) : i + 1) : UINT32_MAX);
                y = safe_realloc(x, sizeof(struct ltedpeg_array_68_s) + (newmax * sizeof(mpz_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;}
           else {y = copy_ltedpeg_array_68(x );
                x->count--;};
        mpz_set(y->elems[i], v);
        return y;}




mpz_ptr_t f_ltedpeg_closure_69(struct ltedpeg_closure_69_s * closure, uint32_t bvar){
if (closure->htbl != NULL){
        ltedpeg_funtype_67_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_ltedpeg_funtype_67(htbl, bvar, hash);
        ltedpeg_funtype_67_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
                mpz_ptr_t result;
                release_ltedpeg_funtype_67((ltedpeg_funtype_67_t)closure);
                result = (mpz_ptr_t)entry.value;
                return result;}
        else {
            ltedpeg_array_68_t fvar_1 = closure->fvar_1;
            uint32_t fvar_2 = closure->fvar_2;

            fvar_1->count++;
            release_ltedpeg_funtype_67((ltedpeg_funtype_67_t)closure);
            mpz_ptr_t result;
            result = (mpz_ptr_t)h_ltedpeg_closure_69(bvar, fvar_1, fvar_2);
            return result;};
        }

      else {
        ltedpeg_array_68_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        release_ltedpeg_funtype_67((ltedpeg_funtype_67_t)closure);
        mpz_ptr_t result;
        result = (mpz_ptr_t)h_ltedpeg_closure_69(bvar, fvar_1, fvar_2);
        return result;}
}

mpz_ptr_t m_ltedpeg_closure_69(struct ltedpeg_closure_69_s * closure, uint32_t bvar){
        ltedpeg_array_68_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        release_ltedpeg_funtype_67((ltedpeg_funtype_67_t)closure);
        return h_ltedpeg_closure_69(bvar, fvar_1, fvar_2);}

mpz_ptr_t h_ltedpeg_closure_69(uint32_t ivar_5, ltedpeg_array_68_t ivar_2, uint32_t ivar_1){
        mpz_ptr_t result;

        bool_t ivar_6;
        uint8_t ivar_8;
        ivar_8 = (uint8_t)0;
        ivar_6 = (ivar_5 == ivar_8);
        if (ivar_6){
             uint32_t ivar_13;
             ivar_13 = (uint32_t)0;
             result = safe_malloc(sizeof(mpz_t));
             mpz_init(result);
             mpz_set(result, ivar_2->elems[ivar_13]);
        } else {
             mpz_ptr_t ivar_14;
             ivar_14 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_14);
             mpz_set(ivar_14, ivar_2->elems[ivar_5]);
             mpz_ptr_t ivar_15;
             ltedpeg_funtype_67_t ivar_26;
             ivar_2->count++;
             ivar_26 = (ltedpeg_funtype_67_t)ltedpeg__sigma((uint32_t)ivar_1, (ltedpeg_array_68_t)ivar_2);
             int32_t ivar_34;
             uint8_t ivar_22;
             ivar_22 = (uint8_t)1;
             ivar_34 = (int32_t)((uint64_t)ivar_5 - (uint64_t)ivar_22);
             uint32_t ivar_33;
             //copying to uint32 from int32;
             ivar_33 = (uint32_t)ivar_34;
             mpz_mk_set(ivar_15, ivar_26->ftbl->fptr(ivar_26, ivar_33));
             mpz_mk_add(result, ivar_15, ivar_14);
             mpz_clear(ivar_14);
             mpz_clear(ivar_15);};
        return result;
}

ltedpeg_closure_69_t new_ltedpeg_closure_69(void){
        static struct ltedpeg_funtype_67_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ltedpeg_funtype_67_t, uint32_t))&f_ltedpeg_closure_69, .mptr = (mpz_ptr_t (*)(ltedpeg_funtype_67_t, uint32_t))&m_ltedpeg_closure_69, .rptr =  (void (*)(ltedpeg_funtype_67_t))&release_ltedpeg_closure_69, .cptr = (ltedpeg_funtype_67_t (*)(ltedpeg_funtype_67_t))&copy_ltedpeg_closure_69};
        ltedpeg_closure_69_t tmp = (ltedpeg_closure_69_t) safe_malloc(sizeof(struct ltedpeg_closure_69_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_69(ltedpeg_funtype_67_t closure){
        ltedpeg_closure_69_t x = (ltedpeg_closure_69_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg_array_68((ltedpeg_array_68_t)x->fvar_1);
          if (x->htbl != NULL){
               

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_69_t copy_ltedpeg_closure_69(ltedpeg_closure_69_t x){
        ltedpeg_closure_69_t y = new_ltedpeg_closure_69();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = (uint32_t)x->fvar_2;
        if (x->htbl != NULL){
            ltedpeg_funtype_67_htbl_t new_htbl = (ltedpeg_funtype_67_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_67_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_67_hashentry_t * new_data = (ltedpeg_funtype_67_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_67_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (uint32_t)x->htbl->data[j].key;
                  mpz_init(new_data[j].value); mpz_set(new_data[j].value, x->htbl->data[j].value);;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_70(ltedpeg_funtype_70_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_70_t copy_ltedpeg_funtype_70(ltedpeg_funtype_70_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_70(ltedpeg_funtype_70_htbl_t htbl, uint32_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_70_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_70_t dupdate_ltedpeg_funtype_70(ltedpeg_funtype_70_t a, uint32_t i, uint8_t v){
        ltedpeg_funtype_70_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_70_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_70_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_70_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_70_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint32_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_70_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_70_hashentry_t * new_data = (ltedpeg_funtype_70_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_70_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = (uint32_t)0; 
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
                                new_data[new_loc].key = (uint32_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (uint8_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                ;
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_70(htbl, i, ihash);
        ltedpeg_funtype_70_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint32_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (uint8_t)v; htbl->num_entries++;}
            else {htbl->data[hashindex].value = (uint8_t)v;};
        return a;

}

ltedpeg_funtype_70_t update_ltedpeg_funtype_70(ltedpeg_funtype_70_t a, uint32_t i, uint8_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_70(a, i, v);
            } else {
                ltedpeg_funtype_70_t x = copy_ltedpeg_funtype_70(a);
                a->count--;
                return dupdate_ltedpeg_funtype_70(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_70(ltedpeg_funtype_70_t x, ltedpeg_funtype_70_t y){
        return false;}

char* json_ltedpeg_funtype_70(ltedpeg_funtype_70_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_70\""); return result;}


uint8_t f_ltedpeg_closure_71(struct ltedpeg_closure_71_s * closure, uint32_t bvar){
if (closure->htbl != NULL){
        ltedpeg_funtype_70_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_ltedpeg_funtype_70(htbl, bvar, hash);
        ltedpeg_funtype_70_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
                uint8_t result;
                release_ltedpeg_funtype_70((ltedpeg_funtype_70_t)closure);
                result = (uint8_t)entry.value;
                return result;}
        else {
            ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
            type_actual_t fvar_2 = closure->fvar_2;
            ltedpeg_funtype_54_t fvar_3 = closure->fvar_3;

            fvar_1->count++;
            fvar_3->count++;
            release_ltedpeg_funtype_70((ltedpeg_funtype_70_t)closure);
            uint8_t result;
            result = (uint8_t)h_ltedpeg_closure_71(bvar, fvar_1, fvar_2, fvar_3);
            return result;};
        }

      else {
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        type_actual_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_54_t fvar_3 = closure->fvar_3;
        fvar_1->count++;
        fvar_3->count++;
        release_ltedpeg_funtype_70((ltedpeg_funtype_70_t)closure);
        uint8_t result;
        result = (uint8_t)h_ltedpeg_closure_71(bvar, fvar_1, fvar_2, fvar_3);
        return result;}
}

uint8_t m_ltedpeg_closure_71(struct ltedpeg_closure_71_s * closure, uint32_t bvar){
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        type_actual_t fvar_2 = closure->fvar_2;
        ltedpeg_funtype_54_t fvar_3 = closure->fvar_3;
        fvar_1->count++;
        fvar_3->count++;
        release_ltedpeg_funtype_70((ltedpeg_funtype_70_t)closure);
        return h_ltedpeg_closure_71(bvar, fvar_1, fvar_2, fvar_3);}

uint8_t h_ltedpeg_closure_71(uint32_t ivar_14, ltedpeg__scaffold_t ivar_2, type_actual_t ivar_37, ltedpeg_funtype_54_t ivar_4){
        uint8_t result;

        ltedpeg_funtype_72_t ivar_24;
        ltedpeg_funtype_74_t ivar_31;
        uint8_t ivar_40;
        ivar_40 = (uint8_t)ltedpeg__num_non_terminals();
        uint32_t ivar_39;
        //copying to uint32 from uint8;
        ivar_39 = (uint32_t)ivar_40;
        ivar_31 = (ltedpeg_funtype_74_t)arrayCount__count((type_actual_t)ivar_37, (uint32_t)ivar_39);
        ivar_4->count++;
        ivar_24 = (ltedpeg_funtype_72_t)ivar_31->ftbl->fptr(ivar_31, ivar_4);
        ltedpeg_array_59_t ivar_42;
        ltedpeg_array_59_t ivar_17;
        ivar_17 = (ltedpeg_array_59_t)ivar_2->elems[ivar_14];
        ivar_17->count++;
        //copying to ltedpeg_array_59 from ltedpeg_array_59;
        ivar_42 = (ltedpeg_array_59_t)ivar_17;
        if (ivar_42 != NULL) ivar_42->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_17);
        result = (uint8_t)ivar_24->ftbl->fptr(ivar_24, ivar_42);
        return result;
}

ltedpeg_closure_71_t new_ltedpeg_closure_71(void){
        static struct ltedpeg_funtype_70_ftbl_s ftbl = {.fptr = (uint8_t (*)(ltedpeg_funtype_70_t, uint32_t))&f_ltedpeg_closure_71, .mptr = (uint8_t (*)(ltedpeg_funtype_70_t, uint32_t))&m_ltedpeg_closure_71, .rptr =  (void (*)(ltedpeg_funtype_70_t))&release_ltedpeg_closure_71, .cptr = (ltedpeg_funtype_70_t (*)(ltedpeg_funtype_70_t))&copy_ltedpeg_closure_71};
        ltedpeg_closure_71_t tmp = (ltedpeg_closure_71_t) safe_malloc(sizeof(struct ltedpeg_closure_71_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_71(ltedpeg_funtype_70_t closure){
        ltedpeg_closure_71_t x = (ltedpeg_closure_71_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_1);
         release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)x->fvar_3);
          if (x->htbl != NULL){
               

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_71_t copy_ltedpeg_closure_71(ltedpeg_closure_71_t x){
        ltedpeg_closure_71_t y = new_ltedpeg_closure_71();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = (type_actual_t)x->fvar_2;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_70_htbl_t new_htbl = (ltedpeg_funtype_70_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_70_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_70_hashentry_t * new_data = (ltedpeg_funtype_70_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_70_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (uint32_t)x->htbl->data[j].key;
                  new_data[j].value = (uint8_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_72(ltedpeg_funtype_72_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_72_t copy_ltedpeg_funtype_72(ltedpeg_funtype_72_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_72(ltedpeg_funtype_72_t x, ltedpeg_funtype_72_t y){
        return false;}

char* json_ltedpeg_funtype_72(ltedpeg_funtype_72_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_72\""); return result;}

void release_ltedpeg_funtype_73(ltedpeg_funtype_73_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_73_t copy_ltedpeg_funtype_73(ltedpeg_funtype_73_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_73(ltedpeg_funtype_73_t x, ltedpeg_funtype_73_t y){
        return false;}

char* json_ltedpeg_funtype_73(ltedpeg_funtype_73_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_73\""); return result;}

void release_ltedpeg_funtype_74(ltedpeg_funtype_74_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_74_t copy_ltedpeg_funtype_74(ltedpeg_funtype_74_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_74(ltedpeg_funtype_74_t x, ltedpeg_funtype_74_t y){
        return false;}

char* json_ltedpeg_funtype_74(ltedpeg_funtype_74_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_74\""); return result;}


bool_t f_ltedpeg_closure_75(struct ltedpeg_closure_75_s * closure, ltedpeg__ent_adt_t bvar){
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_75(bvar);
        return result;
}

bool_t m_ltedpeg_closure_75(struct ltedpeg_closure_75_s * closure, ltedpeg__ent_adt_t bvar){
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_75(bvar);}

bool_t h_ltedpeg_closure_75(ltedpeg__ent_adt_t ivar_19){
        bool_t result;

        result = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_19);
        return result;
}

ltedpeg_closure_75_t new_ltedpeg_closure_75(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_75, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_75, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_75, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_75};
        ltedpeg_closure_75_t tmp = (ltedpeg_closure_75_t) safe_malloc(sizeof(struct ltedpeg_closure_75_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_75(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_75_t x = (ltedpeg_closure_75_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_75_t copy_ltedpeg_closure_75(ltedpeg_closure_75_t x){
        ltedpeg_closure_75_t y = new_ltedpeg_closure_75();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_76(struct ltedpeg_closure_76_s * closure, ltedpeg__ent_adt_t bvar){
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_76(bvar);
        return result;
}

bool_t m_ltedpeg_closure_76(struct ltedpeg_closure_76_s * closure, ltedpeg__ent_adt_t bvar){
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_76(bvar);}

bool_t h_ltedpeg_closure_76(ltedpeg__ent_adt_t ivar_9){
        bool_t result;

        result = (bool_t)ltedpeg__good_or_failp((ltedpeg__ent_adt_t)ivar_9);
        return result;
}

ltedpeg_closure_76_t new_ltedpeg_closure_76(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_76, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_76, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_76, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_76};
        ltedpeg_closure_76_t tmp = (ltedpeg_closure_76_t) safe_malloc(sizeof(struct ltedpeg_closure_76_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_76(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_76_t x = (ltedpeg_closure_76_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_76_t copy_ltedpeg_closure_76(ltedpeg_closure_76_t x){
        ltedpeg_closure_76_t y = new_ltedpeg_closure_76();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_77(ltedpeg_funtype_77_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_77_t copy_ltedpeg_funtype_77(ltedpeg_funtype_77_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_77(ltedpeg_funtype_77_htbl_t htbl, uint64_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_77_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_77_t dupdate_ltedpeg_funtype_77(ltedpeg_funtype_77_t a, uint64_t i, bool_t v){
        ltedpeg_funtype_77_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_77_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_77_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_77_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_77_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint64_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_77_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_77_hashentry_t * new_data = (ltedpeg_funtype_77_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_77_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = (uint64_t)0; 
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
                                new_data[new_loc].key = (uint64_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (bool_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                ;
                safe_free(data);}
        uint32_t ihash = uint64_hash(i);
        uint32_t hashindex = lookup_ltedpeg_funtype_77(htbl, i, ihash);
        ltedpeg_funtype_77_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint64_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (bool_t)v; htbl->num_entries++;}
            else {htbl->data[hashindex].value = (bool_t)v;};
        return a;

}

ltedpeg_funtype_77_t update_ltedpeg_funtype_77(ltedpeg_funtype_77_t a, uint64_t i, bool_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_77(a, i, v);
            } else {
                ltedpeg_funtype_77_t x = copy_ltedpeg_funtype_77(a);
                a->count--;
                return dupdate_ltedpeg_funtype_77(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_77(ltedpeg_funtype_77_t x, ltedpeg_funtype_77_t y){
        return false;}

char* json_ltedpeg_funtype_77(ltedpeg_funtype_77_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_77\""); return result;}


bool_t f_ltedpeg_closure_78(struct ltedpeg_closure_78_s * closure, uint64_t bvar){
if (closure->htbl != NULL){
        ltedpeg_funtype_77_htbl_t htbl = closure->htbl;
        uint32_t hash = uint64_hash(bvar);
        uint32_t hashindex = lookup_ltedpeg_funtype_77(htbl, bvar, hash);
        ltedpeg_funtype_77_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
                bool_t result;
                release_ltedpeg_funtype_77((ltedpeg_funtype_77_t)closure);
                result = (bool_t)entry.value;
                return result;}
        else {
            uint32_t fvar_1 = closure->fvar_1;
            ltedpeg__scaffold_t fvar_2 = closure->fvar_2;

            fvar_2->count++;
            release_ltedpeg_funtype_77((ltedpeg_funtype_77_t)closure);
            bool_t result;
            result = (bool_t)h_ltedpeg_closure_78(bvar, fvar_1, fvar_2);
            return result;};
        }

      else {
        uint32_t fvar_1 = closure->fvar_1;
        ltedpeg__scaffold_t fvar_2 = closure->fvar_2;
        fvar_2->count++;
        release_ltedpeg_funtype_77((ltedpeg_funtype_77_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_78(bvar, fvar_1, fvar_2);
        return result;}
}

bool_t m_ltedpeg_closure_78(struct ltedpeg_closure_78_s * closure, uint64_t bvar){
        uint32_t fvar_1 = closure->fvar_1;
        ltedpeg__scaffold_t fvar_2 = closure->fvar_2;
        fvar_2->count++;
        release_ltedpeg_funtype_77((ltedpeg_funtype_77_t)closure);
        return h_ltedpeg_closure_78(bvar, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_78(uint64_t ivar_6, uint32_t ivar_1, ltedpeg__scaffold_t ivar_2){
        bool_t result;

        uint64_t ivar_7;
        ivar_2->count++;
        ivar_7 = (uint64_t)ltedpeg__pushcount((uint32_t)ivar_1, (ltedpeg__scaffold_t)ivar_2);
        result = (ivar_7 == ivar_6);
        return result;
}

ltedpeg_closure_78_t new_ltedpeg_closure_78(void){
        static struct ltedpeg_funtype_77_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_77_t, uint64_t))&f_ltedpeg_closure_78, .mptr = (bool_t (*)(ltedpeg_funtype_77_t, uint64_t))&m_ltedpeg_closure_78, .rptr =  (void (*)(ltedpeg_funtype_77_t))&release_ltedpeg_closure_78, .cptr = (ltedpeg_funtype_77_t (*)(ltedpeg_funtype_77_t))&copy_ltedpeg_closure_78};
        ltedpeg_closure_78_t tmp = (ltedpeg_closure_78_t) safe_malloc(sizeof(struct ltedpeg_closure_78_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_78(ltedpeg_funtype_77_t closure){
        ltedpeg_closure_78_t x = (ltedpeg_closure_78_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_2);
          if (x->htbl != NULL){
               

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_78_t copy_ltedpeg_closure_78(ltedpeg_closure_78_t x){
        ltedpeg_closure_78_t y = new_ltedpeg_closure_78();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint32_t)x->fvar_1;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_77_htbl_t new_htbl = (ltedpeg_funtype_77_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_77_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_77_hashentry_t * new_data = (ltedpeg_funtype_77_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_77_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (uint64_t)x->htbl->data[j].key;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_79(struct ltedpeg_closure_79_s * closure, ltedpeg__ent_adt_t bvar){
        uint64_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        ltedpeg__lang_spec_t fvar_3 = closure->fvar_3;
        ltedpeg__scaffold_t fvar_4 = closure->fvar_4;
        fvar_3->count++;
        fvar_4->count++;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_79(bvar, fvar_1, fvar_2, fvar_3, fvar_4);
        return result;
}

bool_t m_ltedpeg_closure_79(struct ltedpeg_closure_79_s * closure, ltedpeg__ent_adt_t bvar){
        uint64_t fvar_1 = closure->fvar_1;
        uint32_t fvar_2 = closure->fvar_2;
        ltedpeg__lang_spec_t fvar_3 = closure->fvar_3;
        ltedpeg__scaffold_t fvar_4 = closure->fvar_4;
        fvar_3->count++;
        fvar_4->count++;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_79(bvar, fvar_1, fvar_2, fvar_3, fvar_4);}

bool_t h_ltedpeg_closure_79(ltedpeg__ent_adt_t ivar_8, uint64_t ivar_3, uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_4){
        bool_t result;

        bool_t ivar_9;
        uint8_t ivar_10;
        ivar_8->count++;
        ivar_10 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_8);
        uint8_t ivar_11;
        ivar_11 = (uint8_t)ltedpeg__num_non_terminals();
        ivar_9 = (ivar_10 >= ivar_11);
        if (ivar_9){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_8);
             uint8_t ivar_17;
             ivar_17 = (uint8_t)0;
             result = (ivar_3 == ivar_17);
        } else {
             /* entry */ ltedpeg__ent_adt_t ivar_19;
             ltedpeg_array_59_t ivar_25;
             uint32_t ivar_34;
             ivar_8->count++;
             ivar_34 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_8);
             ltedpeg_array_59_t ivar_30;
             ivar_30 = (ltedpeg_array_59_t)ivar_4->elems[ivar_34];
             ivar_30->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_25 = (ltedpeg_array_59_t)ivar_30;
             if (ivar_25 != NULL) ivar_25->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_30);
             uint8_t ivar_35;
             ivar_8->count++;
             ivar_35 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_8);
             ivar_19 = (ltedpeg__ent_adt_t)ivar_25->elems[ivar_35];
             ivar_19->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_25);
             bool_t ivar_36;
             ltedpeg_funtype_54_t ivar_41;
             ivar_41 = (ltedpeg_funtype_54_t)ltedpeg__good_push_entryp((uint32_t)ivar_1);
             ivar_19->count++;
             ivar_36 = (bool_t)ivar_41->ftbl->fptr(ivar_41, ivar_19);
             if (ivar_36){
           bool_t ivar_47;
           bool_t ivar_49;
           uint8_t ivar_51;
           ivar_19->count++;
           ivar_51 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_19);
           uint8_t ivar_52;
           ivar_52 = (uint8_t)ltedpeg__num_non_terminals();
           ivar_49 = (ivar_51 == ivar_52);
           if (ivar_49){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_8);
           ivar_47 = (bool_t) true;
           } else {
           ltedpeg_funtype_65_t ivar_61;
           ivar_2->count++;
           ivar_4->count++;
           ivar_61 = (ltedpeg_funtype_65_t)ltedpeg__successor((uint32_t)ivar_1, (ltedpeg__lang_spec_t)ivar_2, (ltedpeg__scaffold_t)ivar_4);
           ivar_19->count++;
           ivar_47 = (bool_t)ivar_61->ftbl->mptr(ivar_61, ivar_19, ivar_8);};
           if (ivar_47){
           bool_t ivar_74;
           uint8_t ivar_77;
           ivar_77 = (uint8_t)0;
           ivar_74 = (ivar_3 > ivar_77);
           if (ivar_74){
            ltedpeg_funtype_54_t ivar_82;
            mpz_ptr_t ivar_98;
            uint8_t ivar_89;
            ivar_89 = (uint8_t)1;
            mpz_mk_set_ui(ivar_98, (uint64_t)ivar_3);
            mpz_sub_ui(ivar_98, ivar_98, (uint64_t)ivar_89);
            uint64_t ivar_94;
            //copying to uint64 from mpz;
            ivar_94 = (uint64_t)mpz_get_ui(ivar_98);
            mpz_clear(ivar_98);
            ivar_2->count++;
            ivar_4->count++;
            ivar_82 = (ltedpeg_funtype_54_t)ltedpeg__good_stackp((uint32_t)ivar_1, (ltedpeg__lang_spec_t)ivar_2, (uint64_t)ivar_94, (ltedpeg__scaffold_t)ivar_4);
            result = (bool_t)ivar_82->ftbl->fptr(ivar_82, ivar_19);
           } else {
            release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_19);
            result = (bool_t) false;};
           } else {
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_19);
           result = (bool_t) false;};
             } else {
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_19);
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_8);
           result = (bool_t) false;};};
        return result;
}

ltedpeg_closure_79_t new_ltedpeg_closure_79(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_79, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_79, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_79, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_79};
        ltedpeg_closure_79_t tmp = (ltedpeg_closure_79_t) safe_malloc(sizeof(struct ltedpeg_closure_79_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_79(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_79_t x = (ltedpeg_closure_79_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_3);
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_4);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_79_t copy_ltedpeg_closure_79(ltedpeg_closure_79_t x){
        ltedpeg_closure_79_t y = new_ltedpeg_closure_79();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint64_t)x->fvar_1;
        y->fvar_2 = (uint32_t)x->fvar_2;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_80(struct ltedpeg_closure_80_s * closure, ltedpeg_record_64_t bvar){
        ltedpeg__ent_adt_t bvar_1;
        bvar_1 = (ltedpeg__ent_adt_t)bvar->project_1;
        bvar->project_1->count++;
        ltedpeg__ent_adt_t bvar_2;
        bvar_2 = (ltedpeg__ent_adt_t)bvar->project_2;
        bvar->project_2->count++;
        release_ltedpeg_record_64((ltedpeg_record_64_t)bvar);
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        uint32_t fvar_3 = closure->fvar_3;
        uint64_t fvar_4 = closure->fvar_4;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_65((ltedpeg_funtype_65_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_80(bvar_1, bvar_2, fvar_1, fvar_2, fvar_3, fvar_4);
        return result;
}

bool_t m_ltedpeg_closure_80(struct ltedpeg_closure_80_s * closure, ltedpeg__ent_adt_t bvar_1, ltedpeg__ent_adt_t bvar_2){
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        uint32_t fvar_3 = closure->fvar_3;
        uint64_t fvar_4 = closure->fvar_4;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_65((ltedpeg_funtype_65_t)closure);
        return h_ltedpeg_closure_80(bvar_1, bvar_2, fvar_1, fvar_2, fvar_3, fvar_4);}

bool_t h_ltedpeg_closure_80(ltedpeg__ent_adt_t ivar_9, ltedpeg__ent_adt_t ivar_10, ltedpeg__scaffold_t ivar_4, ltedpeg__lang_spec_t ivar_2, uint32_t ivar_1, uint64_t ivar_3){
        bool_t result;

        bool_t ivar_11;
        uint8_t ivar_12;
        ivar_10->count++;
        ivar_12 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_10);
        uint8_t ivar_13;
        ivar_13 = (uint8_t)ltedpeg__num_non_terminals();
        ivar_11 = (ivar_12 >= ivar_13);
        if (ivar_11){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_10);
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_9);
             result = (bool_t) false;
        } else {
             bool_t ivar_18;
             ivar_9->count++;
             ivar_10->count++;
             ivar_18 = (bool_t) equal_ltedpeg__ent_adt(ivar_9, ivar_10);
             if (ivar_18){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_9);
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_10);
           result = (bool_t) true;
             } else {
           ltedpeg_funtype_65_t ivar_43;
           mpz_ptr_t ivar_59;
           uint8_t ivar_50;
           ivar_50 = (uint8_t)1;
           mpz_mk_set_ui(ivar_59, (uint64_t)ivar_3);
           mpz_sub_ui(ivar_59, ivar_59, (uint64_t)ivar_50);
           uint64_t ivar_55;
           //copying to uint64 from mpz;
           ivar_55 = (uint64_t)mpz_get_ui(ivar_59);
           mpz_clear(ivar_59);
           ivar_2->count++;
           ivar_4->count++;
           ivar_43 = (ltedpeg_funtype_65_t)ltedpeg__mem_stackp((uint32_t)ivar_1, (ltedpeg__lang_spec_t)ivar_2, (uint64_t)ivar_55, (ltedpeg__scaffold_t)ivar_4);
           ltedpeg__ent_adt_t ivar_61;
           ltedpeg_array_59_t ivar_30;
           uint32_t ivar_39;
           ivar_10->count++;
           ivar_39 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_10);
           ltedpeg_array_59_t ivar_35;
           ivar_35 = (ltedpeg_array_59_t)ivar_4->elems[ivar_39];
           ivar_35->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_30 = (ltedpeg_array_59_t)ivar_35;
           if (ivar_30 != NULL) ivar_30->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_35);
           uint8_t ivar_40;
           ivar_40 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_10);
           ivar_61 = (ltedpeg__ent_adt_t)ivar_30->elems[ivar_40];
           ivar_61->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_30);
           result = (bool_t)ivar_43->ftbl->mptr(ivar_43, ivar_9, ivar_61);};};
        return result;
}

ltedpeg_closure_80_t new_ltedpeg_closure_80(void){
        static struct ltedpeg_funtype_65_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_65_t, ltedpeg_record_64_t))&f_ltedpeg_closure_80, .mptr = (bool_t (*)(ltedpeg_funtype_65_t, ltedpeg__ent_adt_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_80, .rptr =  (void (*)(ltedpeg_funtype_65_t))&release_ltedpeg_closure_80, .cptr = (ltedpeg_funtype_65_t (*)(ltedpeg_funtype_65_t))&copy_ltedpeg_closure_80};
        ltedpeg_closure_80_t tmp = (ltedpeg_closure_80_t) safe_malloc(sizeof(struct ltedpeg_closure_80_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_80(ltedpeg_funtype_65_t closure){
        ltedpeg_closure_80_t x = (ltedpeg_closure_80_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_1);
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_64((ltedpeg_record_64_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_80_t copy_ltedpeg_closure_80(ltedpeg_closure_80_t x){
        ltedpeg_closure_80_t y = new_ltedpeg_closure_80();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = (uint32_t)x->fvar_3;
        y->fvar_4 = (uint64_t)x->fvar_4;
        if (x->htbl != NULL){
            ltedpeg_funtype_65_htbl_t new_htbl = (ltedpeg_funtype_65_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_65_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_65_hashentry_t * new_data = (ltedpeg_funtype_65_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_65_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_64_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_81(struct ltedpeg_closure_81_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        uint32_t fvar_3 = closure->fvar_3;
        uint64_t fvar_4 = closure->fvar_4;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_81(bvar, fvar_1, fvar_2, fvar_3, fvar_4);
        return result;
}

bool_t m_ltedpeg_closure_81(struct ltedpeg_closure_81_s * closure, ltedpeg__ent_adt_t bvar){
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        uint32_t fvar_3 = closure->fvar_3;
        uint64_t fvar_4 = closure->fvar_4;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_81(bvar, fvar_1, fvar_2, fvar_3, fvar_4);}

bool_t h_ltedpeg_closure_81(ltedpeg__ent_adt_t ivar_8, ltedpeg__scaffold_t ivar_4, ltedpeg__lang_spec_t ivar_2, uint32_t ivar_1, uint64_t ivar_3){
        bool_t result;

        bool_t ivar_9;
        uint8_t ivar_10;
        ivar_8->count++;
        ivar_10 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_8);
        uint8_t ivar_11;
        ivar_11 = (uint8_t)ltedpeg__num_non_terminals();
        ivar_9 = (ivar_10 >= ivar_11);
        if (ivar_9){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_8);
             result = (bool_t) true;
        } else {
             /* rest */ ltedpeg__ent_adt_t ivar_16;
             ltedpeg_array_59_t ivar_22;
             uint32_t ivar_31;
             ivar_8->count++;
             ivar_31 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_8);
             ltedpeg_array_59_t ivar_27;
             ivar_27 = (ltedpeg_array_59_t)ivar_4->elems[ivar_31];
             ivar_27->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_22 = (ltedpeg_array_59_t)ivar_27;
             if (ivar_22 != NULL) ivar_22->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_27);
             uint8_t ivar_32;
             ivar_8->count++;
             ivar_32 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_8);
             ivar_16 = (ltedpeg__ent_adt_t)ivar_22->elems[ivar_32];
             ivar_16->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_22);
             bool_t ivar_33;
             bool_t ivar_35;
             ltedpeg_funtype_65_t ivar_40;
             mpz_ptr_t ivar_56;
             uint8_t ivar_47;
             ivar_47 = (uint8_t)1;
             mpz_mk_set_ui(ivar_56, (uint64_t)ivar_3);
             mpz_sub_ui(ivar_56, ivar_56, (uint64_t)ivar_47);
             uint64_t ivar_52;
             //copying to uint64 from mpz;
             ivar_52 = (uint64_t)mpz_get_ui(ivar_56);
             mpz_clear(ivar_56);
             ivar_2->count++;
             ivar_4->count++;
             ivar_40 = (ltedpeg_funtype_65_t)ltedpeg__mem_stackp((uint32_t)ivar_1, (ltedpeg__lang_spec_t)ivar_2, (uint64_t)ivar_52, (ltedpeg__scaffold_t)ivar_4);
             ivar_8->count++;
             ivar_35 = (bool_t)ivar_40->ftbl->mptr(ivar_40, ivar_8, ivar_16);
             ivar_33 = !ivar_35;
             if (ivar_33){
           ltedpeg_funtype_54_t ivar_79;
           mpz_ptr_t ivar_95;
           uint8_t ivar_86;
           ivar_86 = (uint8_t)1;
           mpz_mk_set_ui(ivar_95, (uint64_t)ivar_3);
           mpz_sub_ui(ivar_95, ivar_95, (uint64_t)ivar_86);
           uint64_t ivar_91;
           //copying to uint64 from mpz;
           ivar_91 = (uint64_t)mpz_get_ui(ivar_95);
           mpz_clear(ivar_95);
           ivar_2->count++;
           ivar_4->count++;
           ivar_79 = (ltedpeg_funtype_54_t)ltedpeg__fine_stackp((uint32_t)ivar_1, (ltedpeg__lang_spec_t)ivar_2, (uint64_t)ivar_91, (ltedpeg__scaffold_t)ivar_4);
           ltedpeg__ent_adt_t ivar_96;
           ltedpeg_array_59_t ivar_66;
           uint32_t ivar_75;
           ivar_8->count++;
           ivar_75 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_8);
           ltedpeg_array_59_t ivar_71;
           ivar_71 = (ltedpeg_array_59_t)ivar_4->elems[ivar_75];
           ivar_71->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_66 = (ltedpeg_array_59_t)ivar_71;
           if (ivar_66 != NULL) ivar_66->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_71);
           uint8_t ivar_76;
           ivar_76 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_8);
           ivar_96 = (ltedpeg__ent_adt_t)ivar_66->elems[ivar_76];
           ivar_96->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_66);
           result = (bool_t)ivar_79->ftbl->fptr(ivar_79, ivar_96);
             } else {
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_8);
           result = (bool_t) false;};};
        return result;
}

ltedpeg_closure_81_t new_ltedpeg_closure_81(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_81, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_81, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_81, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_81};
        ltedpeg_closure_81_t tmp = (ltedpeg_closure_81_t) safe_malloc(sizeof(struct ltedpeg_closure_81_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_81(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_81_t x = (ltedpeg_closure_81_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_1);
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_81_t copy_ltedpeg_closure_81(ltedpeg_closure_81_t x){
        ltedpeg_closure_81_t y = new_ltedpeg_closure_81();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        y->fvar_3 = (uint32_t)x->fvar_3;
        y->fvar_4 = (uint64_t)x->fvar_4;
        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_82_t new_ltedpeg_record_82(void){
        ltedpeg_record_82_t tmp = (ltedpeg_record_82_t) safe_malloc(sizeof(struct ltedpeg_record_82_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_82(ltedpeg_record_82_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_82_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_82((ltedpeg_record_82_t)x);
}

ltedpeg_record_82_t copy_ltedpeg_record_82(ltedpeg_record_82_t x){
        ltedpeg_record_82_t y = new_ltedpeg_record_82();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = (uint32_t)x->project_2;
        y->project_3 = (uint8_t)x->project_3;
        y->project_4 = (uint64_t)x->project_4;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_82(ltedpeg_record_82_t x, ltedpeg_record_82_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1, (ltedpeg__scaffold_t)y->project_1); tmp = tmp && x->project_2 == y->project_2; tmp = tmp && x->project_3 == y->project_3; tmp = tmp && x->project_4 == y->project_4;
        return tmp;}

char * json_ltedpeg_record_82(ltedpeg_record_82_t x){
        char * tmp[4]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->project_3));
        char * fld3 = safe_malloc(21);
         sprintf(fld3, "\"project_4\" : ");
        tmp[3] = safe_strcat(fld3, json_uint64(x->project_4));
         char * result = json_list_with_sep(tmp, 4,  '{', ',', '}');
         for (uint32_t i = 0; i < 4; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_82_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_82_t T){
        return equal_ltedpeg_record_82((ltedpeg_record_82_t)x, (ltedpeg_record_82_t)y);
}

char * json_ltedpeg_record_82_ptr(pointer_t x, actual_ltedpeg_record_82_t T){
        return json_ltedpeg_record_82((ltedpeg_record_82_t)x);
}

actual_ltedpeg_record_82_t actual_ltedpeg_record_82(void){
        actual_ltedpeg_record_82_t new = (actual_ltedpeg_record_82_t)safe_malloc(sizeof(struct actual_ltedpeg_record_82_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_82_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_82_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_82_ptr);
 

 
        return new;
 }

ltedpeg_record_82_t update_ltedpeg_record_82_project_1(ltedpeg_record_82_t x, ltedpeg__scaffold_t v){
        ltedpeg_record_82_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);};}
        else {y = copy_ltedpeg_record_82(x); x->count--; y->project_1->count--;};
        y->project_1 = (ltedpeg__scaffold_t)v;
        return y;}

ltedpeg_record_82_t update_ltedpeg_record_82_project_2(ltedpeg_record_82_t x, uint32_t v){
        ltedpeg_record_82_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_82(x); x->count--;};
        y->project_2 = (uint32_t)v;
        return y;}

ltedpeg_record_82_t update_ltedpeg_record_82_project_3(ltedpeg_record_82_t x, uint8_t v){
        ltedpeg_record_82_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_82(x); x->count--;};
        y->project_3 = (uint8_t)v;
        return y;}

ltedpeg_record_82_t update_ltedpeg_record_82_project_4(ltedpeg_record_82_t x, uint64_t v){
        ltedpeg_record_82_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_82(x); x->count--;};
        y->project_4 = (uint64_t)v;
        return y;}



void release_ltedpeg_funtype_83(ltedpeg_funtype_83_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_83_t copy_ltedpeg_funtype_83(ltedpeg_funtype_83_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_83(ltedpeg_funtype_83_t x, ltedpeg_funtype_83_t y){
        return false;}

char* json_ltedpeg_funtype_83(ltedpeg_funtype_83_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_83\""); return result;}


bool_t f_ltedpeg_closure_84(struct ltedpeg_closure_84_s * closure, ltedpeg_record_82_t bvar){
        ltedpeg__scaffold_t bvar_1;
        bvar_1 = (ltedpeg__scaffold_t)bvar->project_1;
        bvar->project_1->count++;
        uint32_t bvar_2;
        bvar_2 = (uint32_t)bvar->project_2;
        uint8_t bvar_3;
        bvar_3 = (uint8_t)bvar->project_3;
        uint64_t bvar_4;
        bvar_4 = (uint64_t)bvar->project_4;
        release_ltedpeg_record_82((ltedpeg_record_82_t)bvar);
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        bytestrings__bytestring_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_83((ltedpeg_funtype_83_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_84(bvar_1, bvar_2, bvar_3, bvar_4, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_84(struct ltedpeg_closure_84_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, uint64_t bvar_4){
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        bytestrings__bytestring_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_83((ltedpeg_funtype_83_t)closure);
        return h_ltedpeg_closure_84(bvar_1, bvar_2, bvar_3, bvar_4, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_84(ltedpeg__scaffold_t ivar_14, uint32_t ivar_17, uint8_t ivar_19, uint64_t ivar_20, ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2){
        bool_t result;

        ltedpeg__prepeg_adt_t ivar_21;
        ivar_21 = (ltedpeg__prepeg_adt_t)ivar_1->elems[ivar_19];
        ivar_21->count++;
        bool_t ivar_61;
        ivar_21->count++;
        ivar_61 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_21);
        if (ivar_61){
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
             dpeg__dpeg_grammar_t ivar_26;
             ivar_26 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_21);
             bool_t ivar_30;
             uint32_t ivar_32;
             int32_t ivar_55;
             uint32_t ivar_39;
             ivar_39 = (uint32_t)ivar_26->length;
             uint8_t ivar_40;
             ivar_40 = (uint8_t)1;
             ivar_55 = (int32_t)((uint64_t)ivar_39 - (uint64_t)ivar_40);
             uint32_t ivar_45;
             //copying to uint32 from int32;
             ivar_45 = (uint32_t)ivar_55;
             uint8_t ivar_54;
             ivar_54 = (uint8_t)0;
             uint32_t ivar_48;
             //copying to uint32 from uint8;
             ivar_48 = (uint32_t)ivar_54;
             ivar_2->count++;
             ivar_32 = (uint32_t)dpeg__dpeg_parse((dpeg__dpeg_grammar_t)ivar_26, (uint32_t)ivar_45, (bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_48, (uint32_t)ivar_17);
             uint8_t ivar_33;
             ivar_33 = (uint8_t)0;
             ivar_30 = (ivar_32 == ivar_33);
             if (ivar_30){
           uint8_t ivar_58;
           ivar_58 = (uint8_t)0;
           result = (ivar_20 == ivar_58);
             } else {
           result = (bool_t) false;};
        } else {
             bool_t ivar_94;
             ivar_21->count++;
             ivar_94 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_21);
             if (ivar_94){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
           uint8_t ivar_65;
           ivar_65 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_21);
           bool_t ivar_69;
           bool_t ivar_71;
           uint32_t ivar_74;
           ivar_74 = (uint32_t)ivar_2->length;
           ivar_71 = (ivar_17 == ivar_74);
           if (ivar_71){
           ivar_69 = (bool_t) true;
           } else {
           uint8_t ivar_78;
           ltedpeg__strings_t ivar_81;
           ltedpeg__strings_t ivar_86;
           ivar_86 = (ltedpeg__strings_t)ivar_2->seq;
           ivar_86->count++;
           //copying to ltedpeg__strings from ltedpeg__strings;
           ivar_81 = (ltedpeg__strings_t)ivar_86;
           if (ivar_81 != NULL) ivar_81->count++;
           release_ltedpeg__strings((ltedpeg__strings_t)ivar_86);
           ivar_78 = (uint8_t)ivar_81->elems[ivar_17];
           release_ltedpeg__strings((ltedpeg__strings_t)ivar_81);
           ivar_69 = (ivar_65 != ivar_78);};
           if (ivar_69){
           uint8_t ivar_91;
           ivar_91 = (uint8_t)0;
           result = (ivar_20 == ivar_91);
           } else {
           result = (bool_t) false;};
             } else {
           bool_t ivar_301;
           ivar_21->count++;
           ivar_301 = (bool_t)rec_ltedpeg__ltep((ltedpeg__prepeg_adt_t)ivar_21);
           if (ivar_301){
           uint8_t ivar_98;
           ivar_21->count++;
           ivar_98 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_21);
           uint8_t ivar_99;
           ivar_21->count++;
           ivar_99 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_21);
           uint8_t ivar_100;
           ivar_100 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_21);
           bool_t ivar_110;
           bool_t ivar_112;
           ltedpeg__ent_adt_t ivar_127;
           ltedpeg_array_59_t ivar_117;
           ltedpeg_array_59_t ivar_119;
           ivar_119 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
           ivar_119->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_117 = (ltedpeg_array_59_t)ivar_119;
           if (ivar_117 != NULL) ivar_117->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_119);
           ivar_127 = (ltedpeg__ent_adt_t)ivar_117->elems[ivar_98];
           ivar_127->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_117);
           ivar_112 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_127);
           if (ivar_112){
            bool_t ivar_128;
            ltedpeg__ent_adt_t ivar_143;
            ltedpeg_array_59_t ivar_133;
            ltedpeg_array_59_t ivar_135;
            ivar_135 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
            ivar_135->count++;
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_133 = (ltedpeg_array_59_t)ivar_135;
            if (ivar_133 != NULL) ivar_133->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_135);
            ivar_143 = (ltedpeg__ent_adt_t)ivar_133->elems[ivar_100];
            ivar_143->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_133);
            ivar_128 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_143);
            if (ivar_128){
             mpz_ptr_t ivar_145;
             uint8_t ivar_146;
             ivar_146 = (uint8_t)1;
             mpq_ptr_t ivar_147;
             uint64_t ivar_184;
             ltedpeg__ent_adt_t ivar_163;
             ltedpeg_array_59_t ivar_153;
             ltedpeg_array_59_t ivar_155;
             ivar_155 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
             ivar_155->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_153 = (ltedpeg_array_59_t)ivar_155;
             if (ivar_153 != NULL) ivar_153->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_155);
             ivar_163 = (ltedpeg__ent_adt_t)ivar_153->elems[ivar_98];
             ivar_163->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_153);
             ivar_184 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_163);
             mpq_ptr_t ivar_179;
             //copying to mpq from uint64;
             mpq_mk_set_ui(ivar_179, ivar_184);
             uint64_t ivar_183;
             ltedpeg__ent_adt_t ivar_177;
             ltedpeg_array_59_t ivar_167;
             ltedpeg_array_59_t ivar_169;
             ivar_169 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
             ivar_169->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_167 = (ltedpeg_array_59_t)ivar_169;
             if (ivar_167 != NULL) ivar_167->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_169);
             ivar_177 = (ltedpeg__ent_adt_t)ivar_167->elems[ivar_100];
             ivar_177->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_167);
             ivar_183 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_177);
             mpq_ptr_t ivar_180;
             //copying to mpq from uint64;
             mpq_mk_set_ui(ivar_180, ivar_183);
             ivar_147 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_179, (mpq_ptr_t)ivar_180);
             mpz_mk_set_q(ivar_145, ivar_147);
             mpz_add_ui(ivar_145, ivar_145, ivar_146);
             mpq_clear(ivar_147);
             int64_t tmp33501 = mpz_cmp_ui(ivar_145, ivar_20);
             ivar_110 = (tmp33501 == 0);
             mpz_clear(ivar_145);
            } else {
             ivar_110 = (bool_t) false;};
           } else {
            ivar_110 = (bool_t) false;};
           if (ivar_110){
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
            result = (bool_t) true;
           } else {
            bool_t ivar_189;
            ltedpeg__ent_adt_t ivar_204;
            ltedpeg_array_59_t ivar_194;
            ltedpeg_array_59_t ivar_196;
            ivar_196 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
            ivar_196->count++;
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_194 = (ltedpeg_array_59_t)ivar_196;
            if (ivar_194 != NULL) ivar_194->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_196);
            ivar_204 = (ltedpeg__ent_adt_t)ivar_194->elems[ivar_98];
            ivar_204->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_194);
            ivar_189 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_204);
            if (ivar_189){
             bool_t ivar_205;
             ltedpeg__ent_adt_t ivar_237;
             ltedpeg_array_59_t ivar_210;
             uint32_t ivar_234;
             uint32_t ivar_213;
             ltedpeg__ent_adt_t ivar_227;
             ltedpeg_array_59_t ivar_217;
             ltedpeg_array_59_t ivar_219;
             ivar_219 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
             ivar_219->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_217 = (ltedpeg_array_59_t)ivar_219;
             if (ivar_217 != NULL) ivar_217->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_219);
             ivar_227 = (ltedpeg__ent_adt_t)ivar_217->elems[ivar_98];
             ivar_227->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_217);
             ivar_213 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_227);
             ivar_234 = (uint32_t)(ivar_17 + ivar_213);
             ltedpeg_array_59_t ivar_229;
             ivar_229 = (ltedpeg_array_59_t)ivar_14->elems[ivar_234];
             ivar_229->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_210 = (ltedpeg_array_59_t)ivar_229;
             if (ivar_210 != NULL) ivar_210->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_229);
             ivar_237 = (ltedpeg__ent_adt_t)ivar_210->elems[ivar_99];
             ivar_237->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_210);
             ivar_205 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_237);
             if (ivar_205){
              mpz_ptr_t ivar_239;
              uint8_t ivar_240;
              ivar_240 = (uint8_t)1;
              mpq_ptr_t ivar_241;
              uint64_t ivar_295;
              ltedpeg__ent_adt_t ivar_257;
              ltedpeg_array_59_t ivar_247;
              ltedpeg_array_59_t ivar_249;
              ivar_249 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
              ivar_249->count++;
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_247 = (ltedpeg_array_59_t)ivar_249;
              if (ivar_247 != NULL) ivar_247->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_249);
              ivar_257 = (ltedpeg__ent_adt_t)ivar_247->elems[ivar_98];
              ivar_257->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_247);
              ivar_295 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_257);
              mpq_ptr_t ivar_290;
              //copying to mpq from uint64;
              mpq_mk_set_ui(ivar_290, ivar_295);
              uint64_t ivar_294;
              ltedpeg__ent_adt_t ivar_288;
              ltedpeg_array_59_t ivar_261;
              uint32_t ivar_285;
              uint32_t ivar_264;
              ltedpeg__ent_adt_t ivar_278;
              ltedpeg_array_59_t ivar_268;
              ltedpeg_array_59_t ivar_270;
              ivar_270 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
              ivar_270->count++;
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_268 = (ltedpeg_array_59_t)ivar_270;
              if (ivar_268 != NULL) ivar_268->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_270);
              ivar_278 = (ltedpeg__ent_adt_t)ivar_268->elems[ivar_98];
              ivar_278->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_268);
              ivar_264 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_278);
              ivar_285 = (uint32_t)(ivar_17 + ivar_264);
              ltedpeg_array_59_t ivar_280;
              ivar_280 = (ltedpeg_array_59_t)ivar_14->elems[ivar_285];
              ivar_280->count++;
              release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_261 = (ltedpeg_array_59_t)ivar_280;
              if (ivar_261 != NULL) ivar_261->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_280);
              ivar_288 = (ltedpeg__ent_adt_t)ivar_261->elems[ivar_99];
              ivar_288->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_261);
              ivar_294 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_288);
              mpq_ptr_t ivar_291;
              //copying to mpq from uint64;
              mpq_mk_set_ui(ivar_291, ivar_294);
              ivar_241 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_290, (mpq_ptr_t)ivar_291);
              mpz_mk_set_q(ivar_239, ivar_241);
              mpz_add_ui(ivar_239, ivar_239, ivar_240);
              mpq_clear(ivar_241);
              int64_t tmp33502 = mpz_cmp_ui(ivar_239, ivar_20);
              result = (tmp33502 == 0);
              mpz_clear(ivar_239);
             } else {
              release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
              result = (bool_t) false;};
            } else {
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
             result = (bool_t) false;};};
           } else {
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
           bool_t ivar_308;
           ivar_308 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_21);
           if (ivar_308){
            uint8_t ivar_306;
            ivar_306 = (uint8_t)0;
            result = (ivar_20 == ivar_306);
           } else {
            result = (bool_t) false;};};};};
        return result;
}

ltedpeg_closure_84_t new_ltedpeg_closure_84(void){
        static struct ltedpeg_funtype_83_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_83_t, ltedpeg_record_82_t))&f_ltedpeg_closure_84, .mptr = (bool_t (*)(ltedpeg_funtype_83_t, ltedpeg__scaffold_t, uint32_t, uint8_t, uint64_t))&m_ltedpeg_closure_84, .rptr =  (void (*)(ltedpeg_funtype_83_t))&release_ltedpeg_closure_84, .cptr = (ltedpeg_funtype_83_t (*)(ltedpeg_funtype_83_t))&copy_ltedpeg_closure_84};
        ltedpeg_closure_84_t tmp = (ltedpeg_closure_84_t) safe_malloc(sizeof(struct ltedpeg_closure_84_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_84(ltedpeg_funtype_83_t closure){
        ltedpeg_closure_84_t x = (ltedpeg_closure_84_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_1);
         release_bytestrings__bytestring((bytestrings__bytestring_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_82((ltedpeg_record_82_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_84_t copy_ltedpeg_closure_84(ltedpeg_closure_84_t x){
        ltedpeg_closure_84_t y = new_ltedpeg_closure_84();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_83_htbl_t new_htbl = (ltedpeg_funtype_83_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_83_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_83_hashentry_t * new_data = (ltedpeg_funtype_83_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_83_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_82_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_85_t new_ltedpeg_record_85(void){
        ltedpeg_record_85_t tmp = (ltedpeg_record_85_t) safe_malloc(sizeof(struct ltedpeg_record_85_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_85(ltedpeg_record_85_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_85_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_85((ltedpeg_record_85_t)x);
}

ltedpeg_record_85_t copy_ltedpeg_record_85(ltedpeg_record_85_t x){
        ltedpeg_record_85_t y = new_ltedpeg_record_85();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = (uint32_t)x->project_2;
        y->project_3 = (uint8_t)x->project_3;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_85(ltedpeg_record_85_t x, ltedpeg_record_85_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1, (ltedpeg__scaffold_t)y->project_1); tmp = tmp && x->project_2 == y->project_2; tmp = tmp && x->project_3 == y->project_3;
        return tmp;}

char * json_ltedpeg_record_85(ltedpeg_record_85_t x){
        char * tmp[3]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->project_3));
         char * result = json_list_with_sep(tmp, 3,  '{', ',', '}');
         for (uint32_t i = 0; i < 3; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_85_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_85_t T){
        return equal_ltedpeg_record_85((ltedpeg_record_85_t)x, (ltedpeg_record_85_t)y);
}

char * json_ltedpeg_record_85_ptr(pointer_t x, actual_ltedpeg_record_85_t T){
        return json_ltedpeg_record_85((ltedpeg_record_85_t)x);
}

actual_ltedpeg_record_85_t actual_ltedpeg_record_85(void){
        actual_ltedpeg_record_85_t new = (actual_ltedpeg_record_85_t)safe_malloc(sizeof(struct actual_ltedpeg_record_85_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_85_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_85_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_85_ptr);
 

 
        return new;
 }

ltedpeg_record_85_t update_ltedpeg_record_85_project_1(ltedpeg_record_85_t x, ltedpeg__scaffold_t v){
        ltedpeg_record_85_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);};}
        else {y = copy_ltedpeg_record_85(x); x->count--; y->project_1->count--;};
        y->project_1 = (ltedpeg__scaffold_t)v;
        return y;}

ltedpeg_record_85_t update_ltedpeg_record_85_project_2(ltedpeg_record_85_t x, uint32_t v){
        ltedpeg_record_85_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_85(x); x->count--;};
        y->project_2 = (uint32_t)v;
        return y;}

ltedpeg_record_85_t update_ltedpeg_record_85_project_3(ltedpeg_record_85_t x, uint8_t v){
        ltedpeg_record_85_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_85(x); x->count--;};
        y->project_3 = (uint8_t)v;
        return y;}



void release_ltedpeg_funtype_86(ltedpeg_funtype_86_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_86_t copy_ltedpeg_funtype_86(ltedpeg_funtype_86_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_86(ltedpeg_funtype_86_t x, ltedpeg_funtype_86_t y){
        return false;}

char* json_ltedpeg_funtype_86(ltedpeg_funtype_86_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_86\""); return result;}


bool_t f_ltedpeg_closure_87(struct ltedpeg_closure_87_s * closure, ltedpeg_record_85_t bvar){
        ltedpeg__scaffold_t bvar_1;
        bvar_1 = (ltedpeg__scaffold_t)bvar->project_1;
        bvar->project_1->count++;
        uint32_t bvar_2;
        bvar_2 = (uint32_t)bvar->project_2;
        uint8_t bvar_3;
        bvar_3 = (uint8_t)bvar->project_3;
        release_ltedpeg_record_85((ltedpeg_record_85_t)bvar);
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_86((ltedpeg_funtype_86_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_87(bvar_1, bvar_2, bvar_3, fvar_1);
        return result;
}

bool_t m_ltedpeg_closure_87(struct ltedpeg_closure_87_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3){
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_86((ltedpeg_funtype_86_t)closure);
        return h_ltedpeg_closure_87(bvar_1, bvar_2, bvar_3, fvar_1);}

bool_t h_ltedpeg_closure_87(ltedpeg__scaffold_t ivar_9, uint32_t ivar_11, uint8_t ivar_12, ltedpeg__lang_spec_t ivar_2){
        bool_t result;

        ltedpeg__prepeg_adt_t ivar_13;
        ivar_13 = (ltedpeg__prepeg_adt_t)ivar_2->elems[ivar_12];
        ivar_13->count++;
        bool_t ivar_123;
        ivar_13->count++;
        ivar_123 = (bool_t)rec_ltedpeg__ltep((ltedpeg__prepeg_adt_t)ivar_13);
        if (ivar_123){
             uint8_t ivar_18;
             ivar_13->count++;
             ivar_18 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_13);
             uint8_t ivar_19;
             ivar_19 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_13);
             bool_t ivar_30;
             ltedpeg__ent_adt_t ivar_44;
             ltedpeg_array_59_t ivar_35;
             ltedpeg_array_59_t ivar_37;
             ivar_37 = (ltedpeg_array_59_t)ivar_9->elems[ivar_11];
             ivar_37->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_35 = (ltedpeg_array_59_t)ivar_37;
             if (ivar_35 != NULL) ivar_35->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_37);
             ivar_44 = (ltedpeg__ent_adt_t)ivar_35->elems[ivar_18];
             ivar_44->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_35);
             ivar_30 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_44);
             if (ivar_30){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_9);
           result = (bool_t) true;
             } else {
           bool_t ivar_45;
           bool_t ivar_47;
           ltedpeg__ent_adt_t ivar_61;
           ltedpeg_array_59_t ivar_52;
           ltedpeg_array_59_t ivar_54;
           ivar_54 = (ltedpeg_array_59_t)ivar_9->elems[ivar_11];
           ivar_54->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_52 = (ltedpeg_array_59_t)ivar_54;
           if (ivar_52 != NULL) ivar_52->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_54);
           ivar_61 = (ltedpeg__ent_adt_t)ivar_52->elems[ivar_18];
           ivar_61->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_52);
           ivar_47 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_61);
           if (ivar_47){
           ltedpeg__ent_adt_t ivar_90;
           ltedpeg_array_59_t ivar_65;
           uint32_t ivar_87;
           uint32_t ivar_68;
           ltedpeg__ent_adt_t ivar_81;
           ltedpeg_array_59_t ivar_72;
           ltedpeg_array_59_t ivar_74;
           ivar_74 = (ltedpeg_array_59_t)ivar_9->elems[ivar_11];
           ivar_74->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_72 = (ltedpeg_array_59_t)ivar_74;
           if (ivar_72 != NULL) ivar_72->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_74);
           ivar_81 = (ltedpeg__ent_adt_t)ivar_72->elems[ivar_18];
           ivar_81->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_72);
           ivar_68 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_81);
           ivar_87 = (uint32_t)(ivar_11 + ivar_68);
           ltedpeg_array_59_t ivar_83;
           ivar_83 = (ltedpeg_array_59_t)ivar_9->elems[ivar_87];
           ivar_83->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_65 = (ltedpeg_array_59_t)ivar_83;
           if (ivar_65 != NULL) ivar_65->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_83);
           ivar_90 = (ltedpeg__ent_adt_t)ivar_65->elems[ivar_19];
           ivar_90->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_65);
           ivar_45 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_90);
           } else {
           ivar_45 = (bool_t) false;};
           if (ivar_45){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_9);
           result = (bool_t) true;
           } else {
           bool_t ivar_92;
           ltedpeg__ent_adt_t ivar_106;
           ltedpeg_array_59_t ivar_97;
           ltedpeg_array_59_t ivar_99;
           ivar_99 = (ltedpeg_array_59_t)ivar_9->elems[ivar_11];
           ivar_99->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_97 = (ltedpeg_array_59_t)ivar_99;
           if (ivar_97 != NULL) ivar_97->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_99);
           ivar_106 = (ltedpeg__ent_adt_t)ivar_97->elems[ivar_18];
           ivar_106->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_97);
           ivar_92 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_106);
           if (ivar_92){
            ltedpeg__ent_adt_t ivar_119;
            ltedpeg_array_59_t ivar_110;
            ltedpeg_array_59_t ivar_112;
            ivar_112 = (ltedpeg_array_59_t)ivar_9->elems[ivar_11];
            ivar_112->count++;
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_9);
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_110 = (ltedpeg_array_59_t)ivar_112;
            if (ivar_110 != NULL) ivar_110->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_112);
            ivar_119 = (ltedpeg__ent_adt_t)ivar_110->elems[ivar_19];
            ivar_119->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_110);
            result = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_119);
           } else {
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_9);
            result = (bool_t) false;};};};
        } else {
             release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_13);
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_9);
             result = (bool_t) false;};
        return result;
}

ltedpeg_closure_87_t new_ltedpeg_closure_87(void){
        static struct ltedpeg_funtype_86_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_86_t, ltedpeg_record_85_t))&f_ltedpeg_closure_87, .mptr = (bool_t (*)(ltedpeg_funtype_86_t, ltedpeg__scaffold_t, uint32_t, uint8_t))&m_ltedpeg_closure_87, .rptr =  (void (*)(ltedpeg_funtype_86_t))&release_ltedpeg_closure_87, .cptr = (ltedpeg_funtype_86_t (*)(ltedpeg_funtype_86_t))&copy_ltedpeg_closure_87};
        ltedpeg_closure_87_t tmp = (ltedpeg_closure_87_t) safe_malloc(sizeof(struct ltedpeg_closure_87_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_87(ltedpeg_funtype_86_t closure){
        ltedpeg_closure_87_t x = (ltedpeg_closure_87_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_1);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_85((ltedpeg_record_85_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_87_t copy_ltedpeg_closure_87(ltedpeg_closure_87_t x){
        ltedpeg_closure_87_t y = new_ltedpeg_closure_87();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_86_htbl_t new_htbl = (ltedpeg_funtype_86_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_86_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_86_hashentry_t * new_data = (ltedpeg_funtype_86_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_86_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_85_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_88_t new_ltedpeg_record_88(void){
        ltedpeg_record_88_t tmp = (ltedpeg_record_88_t) safe_malloc(sizeof(struct ltedpeg_record_88_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_88(ltedpeg_record_88_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);
         mpz_clear(x->project_5);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_88_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_88((ltedpeg_record_88_t)x);
}

ltedpeg_record_88_t copy_ltedpeg_record_88(ltedpeg_record_88_t x){
        ltedpeg_record_88_t y = new_ltedpeg_record_88();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = (uint32_t)x->project_2;
        y->project_3 = (uint8_t)x->project_3;
        y->project_4 = (uint64_t)x->project_4;
        mpz_set(y->project_5, x->project_5);
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_88(ltedpeg_record_88_t x, ltedpeg_record_88_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1, (ltedpeg__scaffold_t)y->project_1); tmp = tmp && x->project_2 == y->project_2; tmp = tmp && x->project_3 == y->project_3; tmp = tmp && x->project_4 == y->project_4; tmp = tmp && (mpz_cmp(x->project_5, y->project_5) == 0);
        return tmp;}

char * json_ltedpeg_record_88(ltedpeg_record_88_t x){
        char * tmp[5]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->project_3));
        char * fld3 = safe_malloc(21);
         sprintf(fld3, "\"project_4\" : ");
        tmp[3] = safe_strcat(fld3, json_uint64(x->project_4));
        char * fld4 = safe_malloc(21);
         sprintf(fld4, "\"project_5\" : ");
        tmp[4] = safe_strcat(fld4, json_mpz(x->project_5));
         char * result = json_list_with_sep(tmp, 5,  '{', ',', '}');
         for (uint32_t i = 0; i < 5; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_88_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_88_t T){
        return equal_ltedpeg_record_88((ltedpeg_record_88_t)x, (ltedpeg_record_88_t)y);
}

char * json_ltedpeg_record_88_ptr(pointer_t x, actual_ltedpeg_record_88_t T){
        return json_ltedpeg_record_88((ltedpeg_record_88_t)x);
}

actual_ltedpeg_record_88_t actual_ltedpeg_record_88(void){
        actual_ltedpeg_record_88_t new = (actual_ltedpeg_record_88_t)safe_malloc(sizeof(struct actual_ltedpeg_record_88_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_88_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_88_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_88_ptr);
 

 
        return new;
 }

ltedpeg_record_88_t update_ltedpeg_record_88_project_1(ltedpeg_record_88_t x, ltedpeg__scaffold_t v){
        ltedpeg_record_88_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);};}
        else {y = copy_ltedpeg_record_88(x); x->count--; y->project_1->count--;};
        y->project_1 = (ltedpeg__scaffold_t)v;
        return y;}

ltedpeg_record_88_t update_ltedpeg_record_88_project_2(ltedpeg_record_88_t x, uint32_t v){
        ltedpeg_record_88_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_88(x); x->count--;};
        y->project_2 = (uint32_t)v;
        return y;}

ltedpeg_record_88_t update_ltedpeg_record_88_project_3(ltedpeg_record_88_t x, uint8_t v){
        ltedpeg_record_88_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_88(x); x->count--;};
        y->project_3 = (uint8_t)v;
        return y;}

ltedpeg_record_88_t update_ltedpeg_record_88_project_4(ltedpeg_record_88_t x, uint64_t v){
        ltedpeg_record_88_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_88(x); x->count--;};
        y->project_4 = (uint64_t)v;
        return y;}

ltedpeg_record_88_t update_ltedpeg_record_88_project_5(ltedpeg_record_88_t x, mpz_ptr_t v){
        ltedpeg_record_88_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_88(x); x->count--;};
        mpz_set(y->project_5, v);
        return y;}



void release_ltedpeg_funtype_89(ltedpeg_funtype_89_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_89_t copy_ltedpeg_funtype_89(ltedpeg_funtype_89_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_89(ltedpeg_funtype_89_t x, ltedpeg_funtype_89_t y){
        return false;}

char* json_ltedpeg_funtype_89(ltedpeg_funtype_89_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_89\""); return result;}


bool_t f_ltedpeg_closure_90(struct ltedpeg_closure_90_s * closure, ltedpeg_record_88_t bvar){
        ltedpeg__scaffold_t bvar_1;
        bvar_1 = (ltedpeg__scaffold_t)bvar->project_1;
        bvar->project_1->count++;
        uint32_t bvar_2;
        bvar_2 = (uint32_t)bvar->project_2;
        uint8_t bvar_3;
        bvar_3 = (uint8_t)bvar->project_3;
        uint64_t bvar_4;
        bvar_4 = (uint64_t)bvar->project_4;
        mpz_t bvar_5;
        mpz_init(bvar_5);
        mpz_set(bvar_5, bvar->project_5);
        release_ltedpeg_record_88((ltedpeg_record_88_t)bvar);
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        bytestrings__bytestring_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_89((ltedpeg_funtype_89_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_90(bvar_1, bvar_2, bvar_3, bvar_4, bvar_5, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_90(struct ltedpeg_closure_90_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, uint64_t bvar_4, mpz_ptr_t bvar_5){
        ltedpeg__lang_spec_t fvar_1 = closure->fvar_1;
        bytestrings__bytestring_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_89((ltedpeg_funtype_89_t)closure);
        return h_ltedpeg_closure_90(bvar_1, bvar_2, bvar_3, bvar_4, bvar_5, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_90(ltedpeg__scaffold_t ivar_23, uint32_t ivar_26, uint8_t ivar_28, uint64_t ivar_29, mpz_ptr_t ivar_30, ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2){
        bool_t result;

        ltedpeg__prepeg_adt_t ivar_35;
        ivar_35 = (ltedpeg__prepeg_adt_t)ivar_1->elems[ivar_28];
        ivar_35->count++;
        bool_t ivar_49;
        ivar_35->count++;
        ivar_49 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_35);
        if (ivar_49){
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
             release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_35);
             bool_t ivar_40;
             uint8_t ivar_43;
             ivar_43 = (uint8_t)0;
             int64_t tmp33523 = mpz_cmp_ui(ivar_30, ivar_43);
             ivar_40 = (tmp33523 == 0);
             mpz_clear(ivar_30);
             if (ivar_40){
           uint8_t ivar_46;
           ivar_46 = (uint8_t)0;
           result = (ivar_29 == ivar_46);
             } else {
           result = (bool_t) false;};
        } else {
             bool_t ivar_98;
             ivar_35->count++;
             ivar_98 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_35);
             if (ivar_98){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
           dpeg__dpeg_grammar_t ivar_53;
           ivar_53 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_35);
           /* res */ uint32_t ivar_57;
           int32_t ivar_79;
           uint32_t ivar_63;
           ivar_63 = (uint32_t)ivar_53->length;
           uint8_t ivar_64;
           ivar_64 = (uint8_t)1;
           ivar_79 = (int32_t)((uint64_t)ivar_63 - (uint64_t)ivar_64);
           uint32_t ivar_69;
           //copying to uint32 from int32;
           ivar_69 = (uint32_t)ivar_79;
           uint8_t ivar_78;
           ivar_78 = (uint8_t)0;
           uint32_t ivar_72;
           //copying to uint32 from uint8;
           ivar_72 = (uint32_t)ivar_78;
           ivar_2->count++;
           ivar_57 = (uint32_t)dpeg__dpeg_parse((dpeg__dpeg_grammar_t)ivar_53, (uint32_t)ivar_69, (bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_72, (uint32_t)ivar_26);
           bool_t ivar_80;
           uint8_t ivar_83;
           ivar_83 = (uint8_t)0;
           ivar_80 = (ivar_57 > ivar_83);
           if (ivar_80){
           bool_t ivar_85;
           int32_t ivar_88;
           uint8_t ivar_90;
           ivar_90 = (uint8_t)1;
           ivar_88 = (int32_t)((uint64_t)ivar_57 - (uint64_t)ivar_90);
           int64_t tmp33524 = mpz_cmp_si(ivar_30, ivar_88);
           ivar_85 = (tmp33524 == 0);
           mpz_clear(ivar_30);
           if (ivar_85){
            uint8_t ivar_94;
            ivar_94 = (uint8_t)0;
            result = (ivar_29 == ivar_94);
           } else {
            result = (bool_t) false;};
           } else {
           mpz_clear(ivar_30);
           result = (bool_t) false;};
             } else {
           bool_t ivar_130;
           ivar_35->count++;
           ivar_130 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_35);
           if (ivar_130){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
           uint8_t ivar_102;
           ivar_102 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_35);
           bool_t ivar_106;
           uint8_t ivar_109;
           ivar_109 = (uint8_t)1;
           int64_t tmp33525 = mpz_cmp_ui(ivar_30, ivar_109);
           ivar_106 = (tmp33525 == 0);
           mpz_clear(ivar_30);
           if (ivar_106){
            bool_t ivar_111;
            uint8_t ivar_113;
            ltedpeg__strings_t ivar_117;
            ltedpeg__strings_t ivar_122;
            ivar_122 = (ltedpeg__strings_t)ivar_2->seq;
            ivar_122->count++;
            //copying to ltedpeg__strings from ltedpeg__strings;
            ivar_117 = (ltedpeg__strings_t)ivar_122;
            if (ivar_117 != NULL) ivar_117->count++;
            release_ltedpeg__strings((ltedpeg__strings_t)ivar_122);
            ivar_113 = (uint8_t)ivar_117->elems[ivar_26];
            release_ltedpeg__strings((ltedpeg__strings_t)ivar_117);
            ivar_111 = (ivar_113 == ivar_102);
            if (ivar_111){
             uint8_t ivar_126;
             ivar_126 = (uint8_t)0;
             result = (ivar_29 == ivar_126);
            } else {
             result = (bool_t) false;};
           } else {
            result = (bool_t) false;};
           } else {
           mpz_clear(ivar_30);
           bool_t ivar_337;
           ivar_35->count++;
           ivar_337 = (bool_t)rec_ltedpeg__ltep((ltedpeg__prepeg_adt_t)ivar_35);
           if (ivar_337){
            uint8_t ivar_134;
            ivar_35->count++;
            ivar_134 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_35);
            uint8_t ivar_135;
            ivar_35->count++;
            ivar_135 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_35);
            uint8_t ivar_136;
            ivar_136 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_35);
            bool_t ivar_146;
            bool_t ivar_148;
            ltedpeg__ent_adt_t ivar_163;
            ltedpeg_array_59_t ivar_153;
            ltedpeg_array_59_t ivar_155;
            ivar_155 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
            ivar_155->count++;
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_153 = (ltedpeg_array_59_t)ivar_155;
            if (ivar_153 != NULL) ivar_153->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_155);
            ivar_163 = (ltedpeg__ent_adt_t)ivar_153->elems[ivar_134];
            ivar_163->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_153);
            ivar_148 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_163);
            if (ivar_148){
             bool_t ivar_164;
             ltedpeg__ent_adt_t ivar_196;
             ltedpeg_array_59_t ivar_169;
             uint32_t ivar_193;
             uint32_t ivar_172;
             ltedpeg__ent_adt_t ivar_186;
             ltedpeg_array_59_t ivar_176;
             ltedpeg_array_59_t ivar_178;
             ivar_178 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
             ivar_178->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_176 = (ltedpeg_array_59_t)ivar_178;
             if (ivar_176 != NULL) ivar_176->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_178);
             ivar_186 = (ltedpeg__ent_adt_t)ivar_176->elems[ivar_134];
             ivar_186->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_176);
             ivar_172 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_186);
             ivar_193 = (uint32_t)(ivar_26 + ivar_172);
             ltedpeg_array_59_t ivar_188;
             ivar_188 = (ltedpeg_array_59_t)ivar_23->elems[ivar_193];
             ivar_188->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_169 = (ltedpeg_array_59_t)ivar_188;
             if (ivar_169 != NULL) ivar_169->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_188);
             ivar_196 = (ltedpeg__ent_adt_t)ivar_169->elems[ivar_135];
             ivar_196->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_169);
             ivar_164 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_196);
             if (ivar_164){
              mpz_ptr_t ivar_198;
              uint8_t ivar_199;
              ivar_199 = (uint8_t)1;
              mpq_ptr_t ivar_200;
              uint64_t ivar_254;
              ltedpeg__ent_adt_t ivar_216;
              ltedpeg_array_59_t ivar_206;
              ltedpeg_array_59_t ivar_208;
              ivar_208 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
              ivar_208->count++;
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_206 = (ltedpeg_array_59_t)ivar_208;
              if (ivar_206 != NULL) ivar_206->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_208);
              ivar_216 = (ltedpeg__ent_adt_t)ivar_206->elems[ivar_134];
              ivar_216->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_206);
              ivar_254 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_216);
              mpq_ptr_t ivar_249;
              //copying to mpq from uint64;
              mpq_mk_set_ui(ivar_249, ivar_254);
              uint64_t ivar_253;
              ltedpeg__ent_adt_t ivar_247;
              ltedpeg_array_59_t ivar_220;
              uint32_t ivar_244;
              uint32_t ivar_223;
              ltedpeg__ent_adt_t ivar_237;
              ltedpeg_array_59_t ivar_227;
              ltedpeg_array_59_t ivar_229;
              ivar_229 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
              ivar_229->count++;
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_227 = (ltedpeg_array_59_t)ivar_229;
              if (ivar_227 != NULL) ivar_227->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_229);
              ivar_237 = (ltedpeg__ent_adt_t)ivar_227->elems[ivar_134];
              ivar_237->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_227);
              ivar_223 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_237);
              ivar_244 = (uint32_t)(ivar_26 + ivar_223);
              ltedpeg_array_59_t ivar_239;
              ivar_239 = (ltedpeg_array_59_t)ivar_23->elems[ivar_244];
              ivar_239->count++;
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_220 = (ltedpeg_array_59_t)ivar_239;
              if (ivar_220 != NULL) ivar_220->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_239);
              ivar_247 = (ltedpeg__ent_adt_t)ivar_220->elems[ivar_135];
              ivar_247->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_220);
              ivar_253 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_247);
              mpq_ptr_t ivar_250;
              //copying to mpq from uint64;
              mpq_mk_set_ui(ivar_250, ivar_253);
              ivar_200 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_249, (mpq_ptr_t)ivar_250);
              mpz_mk_set_q(ivar_198, ivar_200);
              mpz_add_ui(ivar_198, ivar_198, ivar_199);
              mpq_clear(ivar_200);
              int64_t tmp33526 = mpz_cmp_ui(ivar_198, ivar_29);
              ivar_146 = (tmp33526 == 0);
              mpz_clear(ivar_198);
             } else {
              ivar_146 = (bool_t) false;};
            } else {
             ivar_146 = (bool_t) false;};
            if (ivar_146){
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
             result = (bool_t) true;
            } else {
             bool_t ivar_259;
             ltedpeg__ent_adt_t ivar_274;
             ltedpeg_array_59_t ivar_264;
             ltedpeg_array_59_t ivar_266;
             ivar_266 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
             ivar_266->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_264 = (ltedpeg_array_59_t)ivar_266;
             if (ivar_264 != NULL) ivar_264->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_266);
             ivar_274 = (ltedpeg__ent_adt_t)ivar_264->elems[ivar_134];
             ivar_274->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_264);
             ivar_259 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_274);
             if (ivar_259){
              bool_t ivar_275;
              ltedpeg__ent_adt_t ivar_290;
              ltedpeg_array_59_t ivar_280;
              ltedpeg_array_59_t ivar_282;
              ivar_282 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
              ivar_282->count++;
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_280 = (ltedpeg_array_59_t)ivar_282;
              if (ivar_280 != NULL) ivar_280->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_282);
              ivar_290 = (ltedpeg__ent_adt_t)ivar_280->elems[ivar_136];
              ivar_290->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_280);
              ivar_275 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_290);
              if (ivar_275){
               mpz_ptr_t ivar_292;
               uint8_t ivar_293;
               ivar_293 = (uint8_t)1;
               mpq_ptr_t ivar_294;
               uint64_t ivar_331;
               ltedpeg__ent_adt_t ivar_310;
               ltedpeg_array_59_t ivar_300;
               ltedpeg_array_59_t ivar_302;
               ivar_302 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
               ivar_302->count++;
               //copying to ltedpeg_array_59 from ltedpeg_array_59;
               ivar_300 = (ltedpeg_array_59_t)ivar_302;
               if (ivar_300 != NULL) ivar_300->count++;
               release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_302);
               ivar_310 = (ltedpeg__ent_adt_t)ivar_300->elems[ivar_134];
               ivar_310->count++;
               release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_300);
               ivar_331 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_310);
               mpq_ptr_t ivar_326;
               //copying to mpq from uint64;
               mpq_mk_set_ui(ivar_326, ivar_331);
               uint64_t ivar_330;
               ltedpeg__ent_adt_t ivar_324;
               ltedpeg_array_59_t ivar_314;
               ltedpeg_array_59_t ivar_316;
               ivar_316 = (ltedpeg_array_59_t)ivar_23->elems[ivar_26];
               ivar_316->count++;
               release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
               //copying to ltedpeg_array_59 from ltedpeg_array_59;
               ivar_314 = (ltedpeg_array_59_t)ivar_316;
               if (ivar_314 != NULL) ivar_314->count++;
               release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_316);
               ivar_324 = (ltedpeg__ent_adt_t)ivar_314->elems[ivar_136];
               ivar_324->count++;
               release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_314);
               ivar_330 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_324);
               mpq_ptr_t ivar_327;
               //copying to mpq from uint64;
               mpq_mk_set_ui(ivar_327, ivar_330);
               ivar_294 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_326, (mpq_ptr_t)ivar_327);
               mpz_mk_set_q(ivar_292, ivar_294);
               mpz_add_ui(ivar_292, ivar_292, ivar_293);
               mpq_clear(ivar_294);
               int64_t tmp33527 = mpz_cmp_ui(ivar_292, ivar_29);
               result = (tmp33527 == 0);
               mpz_clear(ivar_292);
              } else {
               release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
               result = (bool_t) false;};
             } else {
              release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
              result = (bool_t) false;};};
           } else {
            release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_35);
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_23);
            result = (bool_t) false;};};};};
        return result;
}

ltedpeg_closure_90_t new_ltedpeg_closure_90(void){
        static struct ltedpeg_funtype_89_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_89_t, ltedpeg_record_88_t))&f_ltedpeg_closure_90, .mptr = (bool_t (*)(ltedpeg_funtype_89_t, ltedpeg__scaffold_t, uint32_t, uint8_t, uint64_t, mpz_ptr_t))&m_ltedpeg_closure_90, .rptr =  (void (*)(ltedpeg_funtype_89_t))&release_ltedpeg_closure_90, .cptr = (ltedpeg_funtype_89_t (*)(ltedpeg_funtype_89_t))&copy_ltedpeg_closure_90};
        ltedpeg_closure_90_t tmp = (ltedpeg_closure_90_t) safe_malloc(sizeof(struct ltedpeg_closure_90_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_90(ltedpeg_funtype_89_t closure){
        ltedpeg_closure_90_t x = (ltedpeg_closure_90_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_1);
         release_bytestrings__bytestring((bytestrings__bytestring_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_88((ltedpeg_record_88_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_90_t copy_ltedpeg_closure_90(ltedpeg_closure_90_t x){
        ltedpeg_closure_90_t y = new_ltedpeg_closure_90();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_89_htbl_t new_htbl = (ltedpeg_funtype_89_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_89_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_89_hashentry_t * new_data = (ltedpeg_funtype_89_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_89_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_88_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg_record_91_t new_ltedpeg_record_91(void){
        ltedpeg_record_91_t tmp = (ltedpeg_record_91_t) safe_malloc(sizeof(struct ltedpeg_record_91_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg_record_91(ltedpeg_record_91_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_4);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg_record_91_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg_record_91((ltedpeg_record_91_t)x);
}

ltedpeg_record_91_t copy_ltedpeg_record_91(ltedpeg_record_91_t x){
        ltedpeg_record_91_t y = new_ltedpeg_record_91();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = (uint32_t)x->project_2;
        y->project_3 = (uint8_t)x->project_3;
        y->project_4 = x->project_4;
        if (y->project_4 != NULL){y->project_4->count++;};
        y->count = 1;
        return y;}

bool_t equal_ltedpeg_record_91(ltedpeg_record_91_t x, ltedpeg_record_91_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1, (ltedpeg__scaffold_t)y->project_1); tmp = tmp && x->project_2 == y->project_2; tmp = tmp && x->project_3 == y->project_3; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_4, (ltedpeg__ent_adt_t)y->project_4);
        return tmp;}

char * json_ltedpeg_record_91(ltedpeg_record_91_t x){
        char * tmp[4]; 
        char * fld0 = safe_malloc(21);
         sprintf(fld0, "\"project_1\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1));
        char * fld1 = safe_malloc(21);
         sprintf(fld1, "\"project_2\" : ");
        tmp[1] = safe_strcat(fld1, json_uint32(x->project_2));
        char * fld2 = safe_malloc(21);
         sprintf(fld2, "\"project_3\" : ");
        tmp[2] = safe_strcat(fld2, json_uint8(x->project_3));
        char * fld3 = safe_malloc(21);
         sprintf(fld3, "\"project_4\" : ");
        tmp[3] = safe_strcat(fld3, json_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_4));
         char * result = json_list_with_sep(tmp, 4,  '{', ',', '}');
         for (uint32_t i = 0; i < 4; i++) free(tmp[i]);
        return result;}

bool_t equal_ltedpeg_record_91_ptr(pointer_t x, pointer_t y, actual_ltedpeg_record_91_t T){
        return equal_ltedpeg_record_91((ltedpeg_record_91_t)x, (ltedpeg_record_91_t)y);
}

char * json_ltedpeg_record_91_ptr(pointer_t x, actual_ltedpeg_record_91_t T){
        return json_ltedpeg_record_91((ltedpeg_record_91_t)x);
}

actual_ltedpeg_record_91_t actual_ltedpeg_record_91(void){
        actual_ltedpeg_record_91_t new = (actual_ltedpeg_record_91_t)safe_malloc(sizeof(struct actual_ltedpeg_record_91_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg_record_91_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg_record_91_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg_record_91_ptr);
 

 
        return new;
 }

ltedpeg_record_91_t update_ltedpeg_record_91_project_1(ltedpeg_record_91_t x, ltedpeg__scaffold_t v){
        ltedpeg_record_91_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->project_1);};}
        else {y = copy_ltedpeg_record_91(x); x->count--; y->project_1->count--;};
        y->project_1 = (ltedpeg__scaffold_t)v;
        return y;}

ltedpeg_record_91_t update_ltedpeg_record_91_project_2(ltedpeg_record_91_t x, uint32_t v){
        ltedpeg_record_91_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_91(x); x->count--;};
        y->project_2 = (uint32_t)v;
        return y;}

ltedpeg_record_91_t update_ltedpeg_record_91_project_3(ltedpeg_record_91_t x, uint8_t v){
        ltedpeg_record_91_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg_record_91(x); x->count--;};
        y->project_3 = (uint8_t)v;
        return y;}

ltedpeg_record_91_t update_ltedpeg_record_91_project_4(ltedpeg_record_91_t x, ltedpeg__ent_adt_t v){
        ltedpeg_record_91_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_4 != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->project_4);};}
        else {y = copy_ltedpeg_record_91(x); x->count--; y->project_4->count--;};
        y->project_4 = (ltedpeg__ent_adt_t)v;
        return y;}



void release_ltedpeg_funtype_92(ltedpeg_funtype_92_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_92_t copy_ltedpeg_funtype_92(ltedpeg_funtype_92_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_92(ltedpeg_funtype_92_t x, ltedpeg_funtype_92_t y){
        return false;}

char* json_ltedpeg_funtype_92(ltedpeg_funtype_92_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_92\""); return result;}


bool_t f_ltedpeg_closure_93(struct ltedpeg_closure_93_s * closure, ltedpeg_record_91_t bvar){
        ltedpeg__scaffold_t bvar_1;
        bvar_1 = (ltedpeg__scaffold_t)bvar->project_1;
        bvar->project_1->count++;
        uint32_t bvar_2;
        bvar_2 = (uint32_t)bvar->project_2;
        uint8_t bvar_3;
        bvar_3 = (uint8_t)bvar->project_3;
        ltedpeg__ent_adt_t bvar_4;
        bvar_4 = (ltedpeg__ent_adt_t)bvar->project_4;
        bvar->project_4->count++;
        release_ltedpeg_record_91((ltedpeg_record_91_t)bvar);
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_92((ltedpeg_funtype_92_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_93(bvar_1, bvar_2, bvar_3, bvar_4, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_93(struct ltedpeg_closure_93_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, ltedpeg__ent_adt_t bvar_4){
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_92((ltedpeg_funtype_92_t)closure);
        return h_ltedpeg_closure_93(bvar_1, bvar_2, bvar_3, bvar_4, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_93(ltedpeg__scaffold_t ivar_14, uint32_t ivar_17, uint8_t ivar_19, ltedpeg__ent_adt_t ivar_20, bytestrings__bytestring_t ivar_2, ltedpeg__lang_spec_t ivar_1){
        bool_t result;

        bool_t ivar_47;
        ivar_20->count++;
        ivar_47 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_20);
        if (ivar_47){
             uint64_t ivar_22;
             ivar_22 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_20);
             ltedpeg_funtype_83_t ivar_33;
             ivar_1->count++;
             ivar_2->count++;
             ivar_33 = (ltedpeg_funtype_83_t)ltedpeg__good_failp((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2);
             result = (bool_t)ivar_33->ftbl->mptr(ivar_33, ivar_14, ivar_17, ivar_19, ivar_22);
        } else {
             bool_t ivar_64;
             ivar_20->count++;
             ivar_64 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_20);
             if (ivar_64){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_20);
           uint32_t ivar_58;
           ivar_58 = (uint32_t)ivar_2->length;
           ivar_1->count++;
           result = (bool_t)ltedpeg__loop_readyp((uint32_t)ivar_58, (ltedpeg__lang_spec_t)ivar_1, (ltedpeg__scaffold_t)ivar_14, (uint32_t)ivar_17, (uint8_t)ivar_19);
             } else {
           bool_t ivar_113;
           ivar_20->count++;
           ivar_113 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_20);
           if (ivar_113){
           uint64_t ivar_68;
           ivar_20->count++;
           ivar_68 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_20);
           uint32_t ivar_69;
           ivar_69 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_20);
           bool_t ivar_76;
           int32_t ivar_79;
           uint32_t ivar_80;
           ivar_80 = (uint32_t)ivar_2->length;
           ivar_79 = (int32_t)((uint64_t)ivar_80 - (uint64_t)ivar_17);
           if ((ivar_79 < 0)){
            ivar_76 = false;
           } else {
            ivar_76 = (ivar_69 <= (uint32_t)ivar_79);};
           if (ivar_76){
            ltedpeg_funtype_89_t ivar_93;
            ivar_1->count++;
            ivar_2->count++;
            ivar_93 = (ltedpeg_funtype_89_t)ltedpeg__good_goodp((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2);
            mpz_ptr_t ivar_111;
            //copying to mpz from uint32;
            mpz_mk_set_ui(ivar_111, ivar_69);
            result = (bool_t)ivar_93->ftbl->mptr(ivar_93, ivar_14, ivar_17, ivar_19, ivar_68, ivar_111);
           } else {
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
            result = (bool_t) false;};
           } else {
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_20);
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
           result = (bool_t) true;};};};
        return result;
}

ltedpeg_closure_93_t new_ltedpeg_closure_93(void){
        static struct ltedpeg_funtype_92_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_92_t, ltedpeg_record_91_t))&f_ltedpeg_closure_93, .mptr = (bool_t (*)(ltedpeg_funtype_92_t, ltedpeg__scaffold_t, uint32_t, uint8_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_93, .rptr =  (void (*)(ltedpeg_funtype_92_t))&release_ltedpeg_closure_93, .cptr = (ltedpeg_funtype_92_t (*)(ltedpeg_funtype_92_t))&copy_ltedpeg_closure_93};
        ltedpeg_closure_93_t tmp = (ltedpeg_closure_93_t) safe_malloc(sizeof(struct ltedpeg_closure_93_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_93(ltedpeg_funtype_92_t closure){
        ltedpeg_closure_93_t x = (ltedpeg_closure_93_t)closure;
        x->count--;
        if (x->count <= 0){
         release_bytestrings__bytestring((bytestrings__bytestring_t)x->fvar_1);
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_91((ltedpeg_record_91_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_93_t copy_ltedpeg_closure_93(ltedpeg_closure_93_t x){
        ltedpeg_closure_93_t y = new_ltedpeg_closure_93();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_92_htbl_t new_htbl = (ltedpeg_funtype_92_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_92_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_92_hashentry_t * new_data = (ltedpeg_funtype_92_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_92_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_91_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_94(struct ltedpeg_closure_94_s * closure, ltedpeg_record_91_t bvar){
        ltedpeg__scaffold_t bvar_1;
        bvar_1 = (ltedpeg__scaffold_t)bvar->project_1;
        bvar->project_1->count++;
        uint32_t bvar_2;
        bvar_2 = (uint32_t)bvar->project_2;
        uint8_t bvar_3;
        bvar_3 = (uint8_t)bvar->project_3;
        ltedpeg__ent_adt_t bvar_4;
        bvar_4 = (ltedpeg__ent_adt_t)bvar->project_4;
        bvar->project_4->count++;
        release_ltedpeg_record_91((ltedpeg_record_91_t)bvar);
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_92((ltedpeg_funtype_92_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_94(bvar_1, bvar_2, bvar_3, bvar_4, fvar_1, fvar_2);
        return result;
}

bool_t m_ltedpeg_closure_94(struct ltedpeg_closure_94_s * closure, ltedpeg__scaffold_t bvar_1, uint32_t bvar_2, uint8_t bvar_3, ltedpeg__ent_adt_t bvar_4){
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_92((ltedpeg_funtype_92_t)closure);
        return h_ltedpeg_closure_94(bvar_1, bvar_2, bvar_3, bvar_4, fvar_1, fvar_2);}

bool_t h_ltedpeg_closure_94(ltedpeg__scaffold_t ivar_14, uint32_t ivar_17, uint8_t ivar_19, ltedpeg__ent_adt_t ivar_20, bytestrings__bytestring_t ivar_2, ltedpeg__lang_spec_t ivar_1){
        bool_t result;

        bool_t ivar_47;
        ivar_20->count++;
        ivar_47 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_20);
        if (ivar_47){
             uint64_t ivar_22;
             ivar_22 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_20);
             ltedpeg_funtype_83_t ivar_33;
             ivar_1->count++;
             ivar_2->count++;
             ivar_33 = (ltedpeg_funtype_83_t)ltedpeg__good_failp((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2);
             result = (bool_t)ivar_33->ftbl->mptr(ivar_33, ivar_14, ivar_17, ivar_19, ivar_22);
        } else {
             bool_t ivar_64;
             ivar_20->count++;
             ivar_64 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_20);
             if (ivar_64){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_20);
           uint32_t ivar_58;
           ivar_58 = (uint32_t)ivar_2->length;
           ivar_1->count++;
           result = (bool_t)ltedpeg__loop_readyp((uint32_t)ivar_58, (ltedpeg__lang_spec_t)ivar_1, (ltedpeg__scaffold_t)ivar_14, (uint32_t)ivar_17, (uint8_t)ivar_19);
             } else {
           bool_t ivar_113;
           ivar_20->count++;
           ivar_113 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_20);
           if (ivar_113){
           uint64_t ivar_68;
           ivar_20->count++;
           ivar_68 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_20);
           uint32_t ivar_69;
           ivar_69 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_20);
           bool_t ivar_76;
           int32_t ivar_79;
           uint32_t ivar_80;
           ivar_80 = (uint32_t)ivar_2->length;
           ivar_79 = (int32_t)((uint64_t)ivar_80 - (uint64_t)ivar_17);
           if ((ivar_79 < 0)){
            ivar_76 = false;
           } else {
            ivar_76 = (ivar_69 <= (uint32_t)ivar_79);};
           if (ivar_76){
            ltedpeg_funtype_89_t ivar_93;
            ivar_1->count++;
            ivar_2->count++;
            ivar_93 = (ltedpeg_funtype_89_t)ltedpeg__good_goodp((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2);
            mpz_ptr_t ivar_111;
            //copying to mpz from uint32;
            mpz_mk_set_ui(ivar_111, ivar_69);
            result = (bool_t)ivar_93->ftbl->mptr(ivar_93, ivar_14, ivar_17, ivar_19, ivar_68, ivar_111);
           } else {
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
            result = (bool_t) false;};
           } else {
           bool_t ivar_117;
           ivar_117 = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_20);
           if (ivar_117){
            ltedpeg__ent_adt_t ivar_135;
            ltedpeg_array_59_t ivar_125;
            ltedpeg_array_59_t ivar_127;
            ivar_127 = (ltedpeg_array_59_t)ivar_14->elems[ivar_17];
            ivar_127->count++;
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_125 = (ltedpeg_array_59_t)ivar_127;
            if (ivar_125 != NULL) ivar_125->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_127);
            ivar_135 = (ltedpeg__ent_adt_t)ivar_125->elems[ivar_19];
            ivar_135->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_125);
            result = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_135);
           } else {
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_14);
            result = (bool_t) false;};};};};
        return result;
}

ltedpeg_closure_94_t new_ltedpeg_closure_94(void){
        static struct ltedpeg_funtype_92_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_92_t, ltedpeg_record_91_t))&f_ltedpeg_closure_94, .mptr = (bool_t (*)(ltedpeg_funtype_92_t, ltedpeg__scaffold_t, uint32_t, uint8_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_94, .rptr =  (void (*)(ltedpeg_funtype_92_t))&release_ltedpeg_closure_94, .cptr = (ltedpeg_funtype_92_t (*)(ltedpeg_funtype_92_t))&copy_ltedpeg_closure_94};
        ltedpeg_closure_94_t tmp = (ltedpeg_closure_94_t) safe_malloc(sizeof(struct ltedpeg_closure_94_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_94(ltedpeg_funtype_92_t closure){
        ltedpeg_closure_94_t x = (ltedpeg_closure_94_t)closure;
        x->count--;
        if (x->count <= 0){
         release_bytestrings__bytestring((bytestrings__bytestring_t)x->fvar_1);
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_91((ltedpeg_record_91_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_94_t copy_ltedpeg_closure_94(ltedpeg_closure_94_t x){
        ltedpeg_closure_94_t y = new_ltedpeg_closure_94();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_92_htbl_t new_htbl = (ltedpeg_funtype_92_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_92_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_92_hashentry_t * new_data = (ltedpeg_funtype_92_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_92_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_91_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_95(struct ltedpeg_closure_95_s * closure, ltedpeg_record_9_t bvar){
        uint32_t bvar_1;
        bvar_1 = (uint32_t)bvar->project_1;
        uint8_t bvar_2;
        bvar_2 = (uint8_t)bvar->project_2;
        release_ltedpeg_record_9((ltedpeg_record_9_t)bvar);
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_62((ltedpeg_funtype_62_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_95(bvar_1, bvar_2, fvar_1);
        return result;
}

bool_t m_ltedpeg_closure_95(struct ltedpeg_closure_95_s * closure, uint32_t bvar_1, uint8_t bvar_2){
        ltedpeg__scaffold_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_62((ltedpeg_funtype_62_t)closure);
        return h_ltedpeg_closure_95(bvar_1, bvar_2, fvar_1);}

bool_t h_ltedpeg_closure_95(uint32_t ivar_7, uint8_t ivar_8, ltedpeg__scaffold_t ivar_2){
        bool_t result;

        bool_t ivar_9;
        ltedpeg__ent_adt_t ivar_22;
        ltedpeg_array_59_t ivar_13;
        ltedpeg_array_59_t ivar_15;
        ivar_15 = (ltedpeg_array_59_t)ivar_2->elems[ivar_7];
        ivar_15->count++;
        //copying to ltedpeg_array_59 from ltedpeg_array_59;
        ivar_13 = (ltedpeg_array_59_t)ivar_15;
        if (ivar_13 != NULL) ivar_13->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_15);
        ivar_22 = (ltedpeg__ent_adt_t)ivar_13->elems[ivar_8];
        ivar_22->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_13);
        ivar_9 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_22);
        result = !ivar_9;
        return result;
}

ltedpeg_closure_95_t new_ltedpeg_closure_95(void){
        static struct ltedpeg_funtype_62_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_62_t, ltedpeg_record_9_t))&f_ltedpeg_closure_95, .mptr = (bool_t (*)(ltedpeg_funtype_62_t, uint32_t, uint8_t))&m_ltedpeg_closure_95, .rptr =  (void (*)(ltedpeg_funtype_62_t))&release_ltedpeg_closure_95, .cptr = (ltedpeg_funtype_62_t (*)(ltedpeg_funtype_62_t))&copy_ltedpeg_closure_95};
        ltedpeg_closure_95_t tmp = (ltedpeg_closure_95_t) safe_malloc(sizeof(struct ltedpeg_closure_95_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_95(ltedpeg_funtype_62_t closure){
        ltedpeg_closure_95_t x = (ltedpeg_closure_95_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->fvar_1);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg_record_9((ltedpeg_record_9_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_95_t copy_ltedpeg_closure_95(ltedpeg_closure_95_t x){
        ltedpeg_closure_95_t y = new_ltedpeg_closure_95();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_62_htbl_t new_htbl = (ltedpeg_funtype_62_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_62_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_62_hashentry_t * new_data = (ltedpeg_funtype_62_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_62_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg_record_9_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ltedpeg__state_t new_ltedpeg__state(void){
        ltedpeg__state_t tmp = (ltedpeg__state_t) safe_malloc(sizeof(struct ltedpeg__state_s));
        tmp->count = 1;
        return tmp;}

void release_ltedpeg__state(ltedpeg__state_t x){
        x->count--;
        if (x->count <= 0){
         release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->scaf);
         release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ltedpeg__state_ptr(pointer_t x, type_actual_t T){
        release_ltedpeg__state((ltedpeg__state_t)x);
}

ltedpeg__state_t copy_ltedpeg__state(ltedpeg__state_t x){
        ltedpeg__state_t y = new_ltedpeg__state();
        y->scaf = x->scaf;
        if (y->scaf != NULL){y->scaf->count++;};
        y->depth = (uint64_t)x->depth;
        y->stack = x->stack;
        if (y->stack != NULL){y->stack->count++;};
        y->lflag = (bool_t)x->lflag;
        y->count = 1;
        return y;}

bool_t equal_ltedpeg__state(ltedpeg__state_t x, ltedpeg__state_t y){
        bool_t tmp = true; tmp = tmp && equal_ltedpeg__scaffold((ltedpeg__scaffold_t)x->scaf, (ltedpeg__scaffold_t)y->scaf); tmp = tmp && x->depth == y->depth; tmp = tmp && equal_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack, (ltedpeg__ent_adt_t)y->stack); tmp = tmp && x->lflag == y->lflag;
        return tmp;}

char * json_ltedpeg__state(ltedpeg__state_t x){
        char * tmp[4]; 
        char * fld0 = safe_malloc(16);
         sprintf(fld0, "\"scaf\" : ");
        tmp[0] = safe_strcat(fld0, json_ltedpeg__scaffold((ltedpeg__scaffold_t)x->scaf));
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

bool_t equal_ltedpeg__state_ptr(pointer_t x, pointer_t y, actual_ltedpeg__state_t T){
        return equal_ltedpeg__state((ltedpeg__state_t)x, (ltedpeg__state_t)y);
}

char * json_ltedpeg__state_ptr(pointer_t x, actual_ltedpeg__state_t T){
        return json_ltedpeg__state((ltedpeg__state_t)x);
}

actual_ltedpeg__state_t actual_ltedpeg__state(void){
        actual_ltedpeg__state_t new = (actual_ltedpeg__state_t)safe_malloc(sizeof(struct actual_ltedpeg__state_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ltedpeg__state_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ltedpeg__state_ptr);
 
        new->json_ptr = (json_ptr_t)(*json_ltedpeg__state_ptr);
 

 
        return new;
 }

ltedpeg__state_t update_ltedpeg__state_scaf(ltedpeg__state_t x, ltedpeg__scaffold_t v){
        ltedpeg__state_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->scaf != NULL){release_ltedpeg__scaffold((ltedpeg__scaffold_t)x->scaf);};}
        else {y = copy_ltedpeg__state(x); x->count--; y->scaf->count--;};
        y->scaf = (ltedpeg__scaffold_t)v;
        return y;}

ltedpeg__state_t update_ltedpeg__state_depth(ltedpeg__state_t x, uint64_t v){
        ltedpeg__state_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__state(x); x->count--;};
        y->depth = (uint64_t)v;
        return y;}

ltedpeg__state_t update_ltedpeg__state_stack(ltedpeg__state_t x, ltedpeg__ent_adt_t v){
        ltedpeg__state_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->stack != NULL){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->stack);};}
        else {y = copy_ltedpeg__state(x); x->count--; y->stack->count--;};
        y->stack = (ltedpeg__ent_adt_t)v;
        return y;}

ltedpeg__state_t update_ltedpeg__state_lflag(ltedpeg__state_t x, bool_t v){
        ltedpeg__state_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ltedpeg__state(x); x->count--;};
        y->lflag = (bool_t)v;
        return y;}



void release_ltedpeg_funtype_97(ltedpeg_funtype_97_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_97_t copy_ltedpeg_funtype_97(ltedpeg_funtype_97_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_97(ltedpeg_funtype_97_t x, ltedpeg_funtype_97_t y){
        return false;}

char* json_ltedpeg_funtype_97(ltedpeg_funtype_97_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_97\""); return result;}


ltedpeg__state_t f_ltedpeg_closure_98(struct ltedpeg_closure_98_s * closure, ltedpeg__state_t bvar){
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_97((ltedpeg_funtype_97_t)closure);
        ltedpeg__state_t result;
        result = (ltedpeg__state_t)h_ltedpeg_closure_98(bvar, fvar_1, fvar_2);
        return result;
}

ltedpeg__state_t m_ltedpeg_closure_98(struct ltedpeg_closure_98_s * closure, ltedpeg__state_t bvar){
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        ltedpeg__lang_spec_t fvar_2 = closure->fvar_2;
        fvar_1->count++;
        fvar_2->count++;
        release_ltedpeg_funtype_97((ltedpeg_funtype_97_t)closure);
        return h_ltedpeg_closure_98(bvar, fvar_1, fvar_2);}

ltedpeg__state_t h_ltedpeg_closure_98(ltedpeg__state_t ivar_14, bytestrings__bytestring_t ivar_2, ltedpeg__lang_spec_t ivar_1){
        ltedpeg__state_t result;

        /* scaf */ ltedpeg__scaffold_t ivar_19;
        ltedpeg__scaffold_t ivar_30;
        ivar_30 = (ltedpeg__scaffold_t)ivar_14->scaf;
        ivar_30->count++;
        //copying to ltedpeg__scaffold from ltedpeg__scaffold;
        ivar_19 = (ltedpeg__scaffold_t)ivar_30;
        if (ivar_19 != NULL) ivar_19->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_30);
        /* stack */ ltedpeg__ent_adt_t ivar_31;
        ltedpeg__ent_adt_t ivar_36;
        ivar_36 = (ltedpeg__ent_adt_t)ivar_14->stack;
        ivar_36->count++;
        //copying to ltedpeg__ent_adt from ltedpeg__ent_adt;
        ivar_31 = (ltedpeg__ent_adt_t)ivar_36;
        if (ivar_31 != NULL) ivar_31->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_36);
        /* depth */ uint64_t ivar_37;
        ivar_37 = (uint64_t)ivar_14->depth;
        bool_t ivar_49;
        ivar_31->count++;
        ivar_49 = (bool_t)ltedpeg__emptyp((ltedpeg__ent_adt_t)ivar_31);
        if (ivar_49){
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
             //copying to ltedpeg__state from ltedpeg__state;
             result = (ltedpeg__state_t)ivar_14;
             if (result != NULL) result->count++;
             release_ltedpeg__state((ltedpeg__state_t)ivar_14);
        } else {
             /* pos */ uint32_t ivar_54;
             ivar_31->count++;
             ivar_54 = (uint32_t)acc_ltedpeg__ent_adt_pos((ltedpeg__ent_adt_t)ivar_31);
             /* cur */ uint8_t ivar_58;
             ivar_31->count++;
             ivar_58 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_31);
             /* rest */ ltedpeg__ent_adt_t ivar_62;
             ltedpeg_array_59_t ivar_65;
             ltedpeg_array_59_t ivar_67;
             ivar_67 = (ltedpeg_array_59_t)ivar_19->elems[ivar_54];
             ivar_67->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_65 = (ltedpeg_array_59_t)ivar_67;
             if (ivar_65 != NULL) ivar_65->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_67);
             ivar_62 = (ltedpeg__ent_adt_t)ivar_65->elems[ivar_58];
             ivar_62->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_65);
             ltedpeg__prepeg_adt_t ivar_74;
             ivar_74 = (ltedpeg__prepeg_adt_t)ivar_1->elems[ivar_58];
             ivar_74->count++;
             bool_t ivar_122;
             ivar_74->count++;
             ivar_122 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_74);
             if (ivar_122){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_74);
           ltedpeg__ent_adt_t ivar_82;
           uint8_t ivar_93;
           ivar_93 = (uint8_t)0;
           uint64_t ivar_88;
           //copying to uint64 from uint8;
           ivar_88 = (uint64_t)ivar_93;
           uint8_t ivar_92;
           ivar_92 = (uint8_t)0;
           uint32_t ivar_89;
           //copying to uint32 from uint8;
           ivar_89 = (uint32_t)ivar_92;
           ivar_82 = (ltedpeg__ent_adt_t)con_ltedpeg__good((uint64_t)ivar_88, (uint32_t)ivar_89);
           uint64_t ivar_84;
           uint8_t ivar_95;
           ivar_95 = (uint8_t)1;
           ivar_84 = (uint64_t)(ivar_37 - ivar_95);
           ltedpeg__state_t ivar_112;
           ltedpeg__scaffold_t ivar_98;
           ivar_98 = (ltedpeg__scaffold_t)ivar_14->scaf;
           ivar_98->count++;
           ltedpeg__state_t ivar_109;
           ltedpeg__scaffold_t ivar_111;
           ivar_111 = NULL;
           ivar_109 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_111);
           if (ivar_111 != NULL) ivar_111->count--;
           ltedpeg__scaffold_t ivar_110;
           ltedpeg_array_59_t ivar_99;
           ivar_99 = (ltedpeg_array_59_t)ivar_98->elems[ivar_54];
           ivar_99->count++;
           ltedpeg__scaffold_t ivar_106;
           ltedpeg_array_59_t ivar_108;
           ivar_108 = NULL;
           ivar_106 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_98, ivar_54, ivar_108);
           if (ivar_108 != NULL) ivar_108->count--;
           ltedpeg_array_59_t ivar_107;
           ltedpeg_array_59_t ivar_102;
           ltedpeg__ent_adt_t ivar_104;
           ivar_104 = NULL;
           ivar_102 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_99, ivar_58, ivar_104);
           if (ivar_104 != NULL) ivar_104->count--;
           ivar_107 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_102, ivar_58, ivar_82);
           if (ivar_82 != NULL) ivar_82->count--;
           ivar_110 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_106, ivar_54, ivar_107);
           if (ivar_107 != NULL) ivar_107->count--;
           ivar_112 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_109, ivar_110);
           if (ivar_110 != NULL) ivar_110->count--;
           ltedpeg__state_t ivar_117;
           ltedpeg__state_t ivar_114;
           ltedpeg__ent_adt_t ivar_116;
           ivar_116 = NULL;
           ivar_114 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_112, ivar_116);
           if (ivar_116 != NULL) ivar_116->count--;
           ivar_117 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_114, ivar_62);
           if (ivar_62 != NULL) ivar_62->count--;
           result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_117, ivar_84);
             } else {
           bool_t ivar_165;
           ivar_74->count++;
           ivar_165 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_74);
           if (ivar_165){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_74);
           ltedpeg__ent_adt_t ivar_129;
           uint8_t ivar_136;
           ivar_136 = (uint8_t)0;
           uint64_t ivar_134;
           //copying to uint64 from uint8;
           ivar_134 = (uint64_t)ivar_136;
           ivar_129 = (ltedpeg__ent_adt_t)con_ltedpeg__fail((uint64_t)ivar_134);
           uint64_t ivar_131;
           uint8_t ivar_138;
           ivar_138 = (uint8_t)1;
           ivar_131 = (uint64_t)(ivar_37 - ivar_138);
           ltedpeg__state_t ivar_155;
           ltedpeg__scaffold_t ivar_141;
           ivar_141 = (ltedpeg__scaffold_t)ivar_14->scaf;
           ivar_141->count++;
           ltedpeg__state_t ivar_152;
           ltedpeg__scaffold_t ivar_154;
           ivar_154 = NULL;
           ivar_152 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_154);
           if (ivar_154 != NULL) ivar_154->count--;
           ltedpeg__scaffold_t ivar_153;
           ltedpeg_array_59_t ivar_142;
           ivar_142 = (ltedpeg_array_59_t)ivar_141->elems[ivar_54];
           ivar_142->count++;
           ltedpeg__scaffold_t ivar_149;
           ltedpeg_array_59_t ivar_151;
           ivar_151 = NULL;
           ivar_149 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_141, ivar_54, ivar_151);
           if (ivar_151 != NULL) ivar_151->count--;
           ltedpeg_array_59_t ivar_150;
           ltedpeg_array_59_t ivar_145;
           ltedpeg__ent_adt_t ivar_147;
           ivar_147 = NULL;
           ivar_145 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_142, ivar_58, ivar_147);
           if (ivar_147 != NULL) ivar_147->count--;
           ivar_150 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_145, ivar_58, ivar_129);
           if (ivar_129 != NULL) ivar_129->count--;
           ivar_153 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_149, ivar_54, ivar_150);
           if (ivar_150 != NULL) ivar_150->count--;
           ivar_155 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_152, ivar_153);
           if (ivar_153 != NULL) ivar_153->count--;
           ltedpeg__state_t ivar_160;
           ltedpeg__state_t ivar_157;
           ltedpeg__ent_adt_t ivar_159;
           ivar_159 = NULL;
           ivar_157 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_155, ivar_159);
           if (ivar_159 != NULL) ivar_159->count--;
           ivar_160 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_157, ivar_62);
           if (ivar_62 != NULL) ivar_62->count--;
           result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_160, ivar_131);
           } else {
           bool_t ivar_252;
           ivar_74->count++;
           ivar_252 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_74);
           if (ivar_252){
            release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
            dpeg__dpeg_grammar_t ivar_169;
            ivar_169 = (dpeg__dpeg_grammar_t)acc_ltedpeg__prepeg_adt_dpg((ltedpeg__prepeg_adt_t)ivar_74);
            /* res */ uint32_t ivar_173;
            int32_t ivar_195;
            uint32_t ivar_179;
            ivar_179 = (uint32_t)ivar_169->length;
            uint8_t ivar_180;
            ivar_180 = (uint8_t)1;
            ivar_195 = (int32_t)((uint64_t)ivar_179 - (uint64_t)ivar_180);
            uint32_t ivar_185;
            //copying to uint32 from int32;
            ivar_185 = (uint32_t)ivar_195;
            uint8_t ivar_194;
            ivar_194 = (uint8_t)0;
            uint32_t ivar_188;
            //copying to uint32 from uint8;
            ivar_188 = (uint32_t)ivar_194;
            ivar_2->count++;
            ivar_173 = (uint32_t)dpeg__dpeg_parse((dpeg__dpeg_grammar_t)ivar_169, (uint32_t)ivar_185, (bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_188, (uint32_t)ivar_54);
            /* v */ ltedpeg__ent_adt_t ivar_196;
            bool_t ivar_197;
            uint8_t ivar_199;
            ivar_199 = (uint8_t)0;
            ivar_197 = (ivar_173 == ivar_199);
            if (ivar_197){
             uint8_t ivar_205;
             ivar_205 = (uint8_t)0;
             uint64_t ivar_203;
             //copying to uint64 from uint8;
             ivar_203 = (uint64_t)ivar_205;
             ivar_196 = (ltedpeg__ent_adt_t)con_ltedpeg__fail((uint64_t)ivar_203);
            } else {
             uint8_t ivar_217;
             ivar_217 = (uint8_t)0;
             uint64_t ivar_212;
             //copying to uint64 from uint8;
             ivar_212 = (uint64_t)ivar_217;
             int32_t ivar_216;
             uint8_t ivar_209;
             ivar_209 = (uint8_t)1;
             ivar_216 = (int32_t)((uint64_t)ivar_173 - (uint64_t)ivar_209);
             uint32_t ivar_213;
             //copying to uint32 from int32;
             ivar_213 = (uint32_t)ivar_216;
             ivar_196 = (ltedpeg__ent_adt_t)con_ltedpeg__good((uint64_t)ivar_212, (uint32_t)ivar_213);};
            uint64_t ivar_223;
            uint8_t ivar_225;
            ivar_225 = (uint8_t)1;
            ivar_223 = (uint64_t)(ivar_37 - ivar_225);
            ltedpeg__state_t ivar_242;
            ltedpeg__scaffold_t ivar_228;
            ivar_228 = (ltedpeg__scaffold_t)ivar_14->scaf;
            ivar_228->count++;
            ltedpeg__state_t ivar_239;
            ltedpeg__scaffold_t ivar_241;
            ivar_241 = NULL;
            ivar_239 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_241);
            if (ivar_241 != NULL) ivar_241->count--;
            ltedpeg__scaffold_t ivar_240;
            ltedpeg_array_59_t ivar_229;
            ivar_229 = (ltedpeg_array_59_t)ivar_228->elems[ivar_54];
            ivar_229->count++;
            ltedpeg__scaffold_t ivar_236;
            ltedpeg_array_59_t ivar_238;
            ivar_238 = NULL;
            ivar_236 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_228, ivar_54, ivar_238);
            if (ivar_238 != NULL) ivar_238->count--;
            ltedpeg_array_59_t ivar_237;
            ltedpeg_array_59_t ivar_232;
            ltedpeg__ent_adt_t ivar_234;
            ivar_234 = NULL;
            ivar_232 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_229, ivar_58, ivar_234);
            if (ivar_234 != NULL) ivar_234->count--;
            ivar_237 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_232, ivar_58, ivar_196);
            if (ivar_196 != NULL) ivar_196->count--;
            ivar_240 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_236, ivar_54, ivar_237);
            if (ivar_237 != NULL) ivar_237->count--;
            ivar_242 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_239, ivar_240);
            if (ivar_240 != NULL) ivar_240->count--;
            ltedpeg__state_t ivar_247;
            ltedpeg__state_t ivar_244;
            ltedpeg__ent_adt_t ivar_246;
            ivar_246 = NULL;
            ivar_244 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_242, ivar_246);
            if (ivar_246 != NULL) ivar_246->count--;
            ivar_247 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_244, ivar_62);
            if (ivar_62 != NULL) ivar_62->count--;
            result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_247, ivar_223);
           } else {
            bool_t ivar_329;
            ivar_74->count++;
            ivar_329 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_74);
            if (ivar_329){
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
             uint8_t ivar_256;
             ivar_256 = (uint8_t)acc_ltedpeg__prepeg_adt_a((ltedpeg__prepeg_adt_t)ivar_74);
             /* v */ ltedpeg__ent_adt_t ivar_260;
             bool_t ivar_261;
             bool_t ivar_262;
             uint32_t ivar_265;
             ivar_265 = (uint32_t)ivar_2->length;
             ivar_262 = (ivar_54 == ivar_265);
             if (ivar_262){
              ivar_261 = (bool_t) true;
             } else {
              uint8_t ivar_269;
              ltedpeg__strings_t ivar_272;
              ltedpeg__strings_t ivar_277;
              ivar_277 = (ltedpeg__strings_t)ivar_2->seq;
              ivar_277->count++;
              //copying to ltedpeg__strings from ltedpeg__strings;
              ivar_272 = (ltedpeg__strings_t)ivar_277;
              if (ivar_272 != NULL) ivar_272->count++;
              release_ltedpeg__strings((ltedpeg__strings_t)ivar_277);
              ivar_269 = (uint8_t)ivar_272->elems[ivar_54];
              release_ltedpeg__strings((ltedpeg__strings_t)ivar_272);
              ivar_261 = (ivar_256 != ivar_269);};
             if (ivar_261){
              uint8_t ivar_285;
              ivar_285 = (uint8_t)0;
              uint64_t ivar_283;
              //copying to uint64 from uint8;
              ivar_283 = (uint64_t)ivar_285;
              ivar_260 = (ltedpeg__ent_adt_t)con_ltedpeg__fail((uint64_t)ivar_283);
             } else {
              uint8_t ivar_294;
              ivar_294 = (uint8_t)0;
              uint64_t ivar_289;
              //copying to uint64 from uint8;
              ivar_289 = (uint64_t)ivar_294;
              uint8_t ivar_293;
              ivar_293 = (uint8_t)1;
              uint32_t ivar_290;
              //copying to uint32 from uint8;
              ivar_290 = (uint32_t)ivar_293;
              ivar_260 = (ltedpeg__ent_adt_t)con_ltedpeg__good((uint64_t)ivar_289, (uint32_t)ivar_290);};
             uint64_t ivar_300;
             uint8_t ivar_302;
             ivar_302 = (uint8_t)1;
             ivar_300 = (uint64_t)(ivar_37 - ivar_302);
             ltedpeg__state_t ivar_319;
             ltedpeg__scaffold_t ivar_305;
             ivar_305 = (ltedpeg__scaffold_t)ivar_14->scaf;
             ivar_305->count++;
             ltedpeg__state_t ivar_316;
             ltedpeg__scaffold_t ivar_318;
             ivar_318 = NULL;
             ivar_316 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_318);
             if (ivar_318 != NULL) ivar_318->count--;
             ltedpeg__scaffold_t ivar_317;
             ltedpeg_array_59_t ivar_306;
             ivar_306 = (ltedpeg_array_59_t)ivar_305->elems[ivar_54];
             ivar_306->count++;
             ltedpeg__scaffold_t ivar_313;
             ltedpeg_array_59_t ivar_315;
             ivar_315 = NULL;
             ivar_313 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_305, ivar_54, ivar_315);
             if (ivar_315 != NULL) ivar_315->count--;
             ltedpeg_array_59_t ivar_314;
             ltedpeg_array_59_t ivar_309;
             ltedpeg__ent_adt_t ivar_311;
             ivar_311 = NULL;
             ivar_309 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_306, ivar_58, ivar_311);
             if (ivar_311 != NULL) ivar_311->count--;
             ivar_314 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_309, ivar_58, ivar_260);
             if (ivar_260 != NULL) ivar_260->count--;
             ivar_317 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_313, ivar_54, ivar_314);
             if (ivar_314 != NULL) ivar_314->count--;
             ivar_319 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_316, ivar_317);
             if (ivar_317 != NULL) ivar_317->count--;
             ltedpeg__state_t ivar_324;
             ltedpeg__state_t ivar_321;
             ltedpeg__ent_adt_t ivar_323;
             ivar_323 = NULL;
             ivar_321 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_319, ivar_323);
             if (ivar_323 != NULL) ivar_323->count--;
             ivar_324 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_321, ivar_62);
             if (ivar_62 != NULL) ivar_62->count--;
             result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_324, ivar_300);
            } else {
             uint8_t ivar_333;
             ivar_74->count++;
             ivar_333 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_74);
             uint8_t ivar_334;
             ivar_74->count++;
             ivar_334 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_74);
             uint8_t ivar_335;
             ivar_335 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_74);
             ltedpeg__ent_adt_t ivar_345;
             ltedpeg_array_59_t ivar_348;
             ltedpeg__scaffold_t ivar_353;
             ltedpeg__scaffold_t ivar_362;
             ivar_362 = (ltedpeg__scaffold_t)ivar_14->scaf;
             ivar_362->count++;
             //copying to ltedpeg__scaffold from ltedpeg__scaffold;
             ivar_353 = (ltedpeg__scaffold_t)ivar_362;
             if (ivar_353 != NULL) ivar_353->count++;
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_362);
             ltedpeg_array_59_t ivar_350;
             ivar_350 = (ltedpeg_array_59_t)ivar_353->elems[ivar_54];
             ivar_350->count++;
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_353);
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_348 = (ltedpeg_array_59_t)ivar_350;
             if (ivar_348 != NULL) ivar_348->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_350);
             ivar_345 = (ltedpeg__ent_adt_t)ivar_348->elems[ivar_333];
             ivar_345->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_348);
             bool_t ivar_579;
             ivar_345->count++;
             ivar_579 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_345);
             if (ivar_579){
              uint64_t ivar_365;
              ivar_365 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_345);
              ltedpeg__ent_adt_t ivar_369;
              ltedpeg_array_59_t ivar_372;
              ltedpeg_array_59_t ivar_374;
              ivar_374 = (ltedpeg_array_59_t)ivar_19->elems[ivar_54];
              ivar_374->count++;
              release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
              //copying to ltedpeg_array_59 from ltedpeg_array_59;
              ivar_372 = (ltedpeg_array_59_t)ivar_374;
              if (ivar_372 != NULL) ivar_372->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_374);
              ivar_369 = (ltedpeg__ent_adt_t)ivar_372->elems[ivar_335];
              ivar_369->count++;
              release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_372);
              bool_t ivar_432;
              ivar_369->count++;
              ivar_432 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_369);
              if (ivar_432){
               release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
               uint64_t ivar_381;
               ivar_381 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_369);
               ltedpeg__ent_adt_t ivar_388;
               mpz_ptr_t ivar_403;
               mpq_ptr_t ivar_392;
               mpq_ptr_t ivar_397;
               //copying to mpq from uint64;
               mpq_mk_set_ui(ivar_397, ivar_365);
               mpq_ptr_t ivar_398;
               //copying to mpq from uint64;
               mpq_mk_set_ui(ivar_398, ivar_381);
               ivar_392 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_397, (mpq_ptr_t)ivar_398);
               uint8_t ivar_393;
               ivar_393 = (uint8_t)1;
               mpz_mk_set_q(ivar_403, ivar_392);
               mpz_add_ui(ivar_403, ivar_403, (uint64_t)ivar_393);
               mpq_clear(ivar_392);
               uint64_t ivar_401;
               //copying to uint64 from mpz;
               ivar_401 = (uint64_t)mpz_get_ui(ivar_403);
               mpz_clear(ivar_403);
               ivar_388 = (ltedpeg__ent_adt_t)con_ltedpeg__fail((uint64_t)ivar_401);
               uint64_t ivar_390;
               uint8_t ivar_405;
               ivar_405 = (uint8_t)1;
               ivar_390 = (uint64_t)(ivar_37 - ivar_405);
               ltedpeg__state_t ivar_422;
               ltedpeg__scaffold_t ivar_408;
               ivar_408 = (ltedpeg__scaffold_t)ivar_14->scaf;
               ivar_408->count++;
               ltedpeg__state_t ivar_419;
               ltedpeg__scaffold_t ivar_421;
               ivar_421 = NULL;
               ivar_419 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_421);
               if (ivar_421 != NULL) ivar_421->count--;
               ltedpeg__scaffold_t ivar_420;
               ltedpeg_array_59_t ivar_409;
               ivar_409 = (ltedpeg_array_59_t)ivar_408->elems[ivar_54];
               ivar_409->count++;
               ltedpeg__scaffold_t ivar_416;
               ltedpeg_array_59_t ivar_418;
               ivar_418 = NULL;
               ivar_416 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_408, ivar_54, ivar_418);
               if (ivar_418 != NULL) ivar_418->count--;
               ltedpeg_array_59_t ivar_417;
               ltedpeg_array_59_t ivar_412;
               ltedpeg__ent_adt_t ivar_414;
               ivar_414 = NULL;
               ivar_412 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_409, ivar_58, ivar_414);
               if (ivar_414 != NULL) ivar_414->count--;
               ivar_417 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_412, ivar_58, ivar_388);
               if (ivar_388 != NULL) ivar_388->count--;
               ivar_420 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_416, ivar_54, ivar_417);
               if (ivar_417 != NULL) ivar_417->count--;
               ivar_422 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_419, ivar_420);
               if (ivar_420 != NULL) ivar_420->count--;
               ltedpeg__state_t ivar_427;
               ltedpeg__state_t ivar_424;
               ltedpeg__ent_adt_t ivar_426;
               ivar_426 = NULL;
               ivar_424 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_422, ivar_426);
               if (ivar_426 != NULL) ivar_426->count--;
               ivar_427 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_424, ivar_62);
               if (ivar_62 != NULL) ivar_62->count--;
               result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_427, ivar_390);
              } else {
               bool_t ivar_493;
               ivar_369->count++;
               ivar_493 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_369);
               if (ivar_493){
                release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
                uint64_t ivar_436;
                ivar_369->count++;
                ivar_436 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_369);
                uint32_t ivar_437;
                ivar_437 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_369);
                ltedpeg__ent_adt_t ivar_447;
                mpz_ptr_t ivar_464;
                mpq_ptr_t ivar_452;
                mpq_ptr_t ivar_457;
                //copying to mpq from uint64;
                mpq_mk_set_ui(ivar_457, ivar_365);
                mpq_ptr_t ivar_458;
                //copying to mpq from uint64;
                mpq_mk_set_ui(ivar_458, ivar_436);
                ivar_452 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_457, (mpq_ptr_t)ivar_458);
                uint8_t ivar_453;
                ivar_453 = (uint8_t)1;
                mpz_mk_set_q(ivar_464, ivar_452);
                mpz_add_ui(ivar_464, ivar_464, (uint64_t)ivar_453);
                mpq_clear(ivar_452);
                uint64_t ivar_461;
                //copying to uint64 from mpz;
                ivar_461 = (uint64_t)mpz_get_ui(ivar_464);
                mpz_clear(ivar_464);
                ivar_447 = (ltedpeg__ent_adt_t)con_ltedpeg__good((uint64_t)ivar_461, (uint32_t)ivar_437);
                uint64_t ivar_449;
                uint8_t ivar_466;
                ivar_466 = (uint8_t)1;
                ivar_449 = (uint64_t)(ivar_37 - ivar_466);
                ltedpeg__state_t ivar_483;
                ltedpeg__scaffold_t ivar_469;
                ivar_469 = (ltedpeg__scaffold_t)ivar_14->scaf;
                ivar_469->count++;
                ltedpeg__state_t ivar_480;
                ltedpeg__scaffold_t ivar_482;
                ivar_482 = NULL;
                ivar_480 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_482);
                if (ivar_482 != NULL) ivar_482->count--;
                ltedpeg__scaffold_t ivar_481;
                ltedpeg_array_59_t ivar_470;
                ivar_470 = (ltedpeg_array_59_t)ivar_469->elems[ivar_54];
                ivar_470->count++;
                ltedpeg__scaffold_t ivar_477;
                ltedpeg_array_59_t ivar_479;
                ivar_479 = NULL;
                ivar_477 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_469, ivar_54, ivar_479);
                if (ivar_479 != NULL) ivar_479->count--;
                ltedpeg_array_59_t ivar_478;
                ltedpeg_array_59_t ivar_473;
                ltedpeg__ent_adt_t ivar_475;
                ivar_475 = NULL;
                ivar_473 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_470, ivar_58, ivar_475);
                if (ivar_475 != NULL) ivar_475->count--;
                ivar_478 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_473, ivar_58, ivar_447);
                if (ivar_447 != NULL) ivar_447->count--;
                ivar_481 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_477, ivar_54, ivar_478);
                if (ivar_478 != NULL) ivar_478->count--;
                ivar_483 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_480, ivar_481);
                if (ivar_481 != NULL) ivar_481->count--;
                ltedpeg__state_t ivar_488;
                ltedpeg__state_t ivar_485;
                ltedpeg__ent_adt_t ivar_487;
                ivar_487 = NULL;
                ivar_485 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_483, ivar_487);
                if (ivar_487 != NULL) ivar_487->count--;
                ivar_488 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_485, ivar_62);
                if (ivar_62 != NULL) ivar_62->count--;
                result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_488, ivar_449);
               } else {
                bool_t ivar_536;
                ivar_536 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_369);
                if (ivar_536){
                 release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_62);
                 ltedpeg__ent_adt_t ivar_500;
                 ivar_500 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_54, (uint8_t)ivar_335);
                 uint64_t ivar_501;
                 uint8_t ivar_509;
                 ivar_509 = (uint8_t)1;
                 ivar_501 = (uint64_t)(ivar_37 + ivar_509);
                 ltedpeg__state_t ivar_516;
                 ltedpeg__state_t ivar_513;
                 ltedpeg__ent_adt_t ivar_515;
                 ivar_515 = NULL;
                 ivar_513 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_14, ivar_515);
                 if (ivar_515 != NULL) ivar_515->count--;
                 ivar_516 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_513, ivar_500);
                 if (ivar_500 != NULL) ivar_500->count--;
                 ltedpeg__state_t ivar_520;
                 ivar_520 = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_516, ivar_501);
                 ltedpeg__scaffold_t ivar_521;
                 ivar_521 = (ltedpeg__scaffold_t)ivar_520->scaf;
                 ivar_521->count++;
                 ltedpeg__state_t ivar_532;
                 ltedpeg__scaffold_t ivar_534;
                 ivar_534 = NULL;
                 ivar_532 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_520, ivar_534);
                 if (ivar_534 != NULL) ivar_534->count--;
                 ltedpeg__scaffold_t ivar_533;
                 ltedpeg_array_59_t ivar_522;
                 ivar_522 = (ltedpeg_array_59_t)ivar_521->elems[ivar_54];
                 ivar_522->count++;
                 ltedpeg__scaffold_t ivar_529;
                 ltedpeg_array_59_t ivar_531;
                 ivar_531 = NULL;
                 ivar_529 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_521, ivar_54, ivar_531);
                 if (ivar_531 != NULL) ivar_531->count--;
                 ltedpeg_array_59_t ivar_530;
                 ltedpeg_array_59_t ivar_525;
                 ltedpeg__ent_adt_t ivar_527;
                 ivar_527 = NULL;
                 ivar_525 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_522, ivar_335, ivar_527);
                 if (ivar_527 != NULL) ivar_527->count--;
                 ivar_530 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_525, ivar_335, ivar_31);
                 if (ivar_31 != NULL) ivar_31->count--;
                 ivar_533 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_529, ivar_54, ivar_530);
                 if (ivar_530 != NULL) ivar_530->count--;
                 result = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_532, ivar_533);
                 if (ivar_533 != NULL) ivar_533->count--;
                } else {
                 release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
                 ltedpeg__ent_adt_t ivar_543;
                 ivar_543 = (ltedpeg__ent_adt_t)con_ltedpeg__loop();
                 if (ivar_543 != NULL) ivar_543->count++;
                 uint64_t ivar_544;
                 uint8_t ivar_548;
                 ivar_548 = (uint8_t)1;
                 ivar_544 = (uint64_t)(ivar_37 - ivar_548);
                 bool_t ivar_546;
                 ivar_546 = (bool_t) true;
                 ltedpeg__state_t ivar_565;
                 ltedpeg__scaffold_t ivar_551;
                 ivar_551 = (ltedpeg__scaffold_t)ivar_14->scaf;
                 ivar_551->count++;
                 ltedpeg__state_t ivar_562;
                 ltedpeg__scaffold_t ivar_564;
                 ivar_564 = NULL;
                 ivar_562 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_564);
                 if (ivar_564 != NULL) ivar_564->count--;
                 ltedpeg__scaffold_t ivar_563;
                 ltedpeg_array_59_t ivar_552;
                 ivar_552 = (ltedpeg_array_59_t)ivar_551->elems[ivar_54];
                 ivar_552->count++;
                 ltedpeg__scaffold_t ivar_559;
                 ltedpeg_array_59_t ivar_561;
                 ivar_561 = NULL;
                 ivar_559 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_551, ivar_54, ivar_561);
                 if (ivar_561 != NULL) ivar_561->count--;
                 ltedpeg_array_59_t ivar_560;
                 ltedpeg_array_59_t ivar_555;
                 ltedpeg__ent_adt_t ivar_557;
                 ivar_557 = NULL;
                 ivar_555 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_552, ivar_58, ivar_557);
                 if (ivar_557 != NULL) ivar_557->count--;
                 ivar_560 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_555, ivar_58, ivar_543);
                 if (ivar_543 != NULL) ivar_543->count--;
                 ivar_563 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_559, ivar_54, ivar_560);
                 if (ivar_560 != NULL) ivar_560->count--;
                 ivar_565 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_562, ivar_563);
                 if (ivar_563 != NULL) ivar_563->count--;
                 ltedpeg__state_t ivar_569;
                 ivar_569 = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_565, ivar_544);
                 ltedpeg__state_t ivar_574;
                 ltedpeg__state_t ivar_571;
                 ltedpeg__ent_adt_t ivar_573;
                 ivar_573 = NULL;
                 ivar_571 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_569, ivar_573);
                 if (ivar_573 != NULL) ivar_573->count--;
                 ivar_574 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_571, ivar_62);
                 if (ivar_62 != NULL) ivar_62->count--;
                 result = (ltedpeg__state_t)update_ltedpeg__state_lflag(ivar_574, ivar_546);};};};
             } else {
              release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_19);
              bool_t ivar_831;
              ivar_345->count++;
              ivar_831 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_345);
              if (ivar_831){
               release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
               uint64_t ivar_583;
               ivar_345->count++;
               ivar_583 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_345);
               uint32_t ivar_584;
               ivar_584 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_345);
               ltedpeg__ent_adt_t ivar_591;
               ltedpeg_array_59_t ivar_594;
               ltedpeg__scaffold_t ivar_602;
               ltedpeg__scaffold_t ivar_611;
               ivar_611 = (ltedpeg__scaffold_t)ivar_14->scaf;
               ivar_611->count++;
               //copying to ltedpeg__scaffold from ltedpeg__scaffold;
               ivar_602 = (ltedpeg__scaffold_t)ivar_611;
               if (ivar_602 != NULL) ivar_602->count++;
               release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_611);
               uint32_t ivar_612;
               ivar_612 = (uint32_t)(ivar_54 + ivar_584);
               ltedpeg_array_59_t ivar_599;
               ivar_599 = (ltedpeg_array_59_t)ivar_602->elems[ivar_612];
               ivar_599->count++;
               release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_602);
               //copying to ltedpeg_array_59 from ltedpeg_array_59;
               ivar_594 = (ltedpeg_array_59_t)ivar_599;
               if (ivar_594 != NULL) ivar_594->count++;
               release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_599);
               ivar_591 = (ltedpeg__ent_adt_t)ivar_594->elems[ivar_334];
               ivar_591->count++;
               release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_594);
               bool_t ivar_665;
               ivar_591->count++;
               ivar_665 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_591);
               if (ivar_665){
                uint64_t ivar_614;
                ivar_614 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_591);
                ltedpeg__ent_adt_t ivar_621;
                mpz_ptr_t ivar_636;
                uint8_t ivar_625;
                ivar_625 = (uint8_t)1;
                mpq_ptr_t ivar_626;
                mpq_ptr_t ivar_630;
                //copying to mpq from uint64;
                mpq_mk_set_ui(ivar_630, ivar_583);
                mpq_ptr_t ivar_631;
                //copying to mpq from uint64;
                mpq_mk_set_ui(ivar_631, ivar_614);
                ivar_626 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_630, (mpq_ptr_t)ivar_631);
                mpz_mk_set_q(ivar_636, ivar_626);
                mpz_add_ui(ivar_636, ivar_636, ivar_625);
                mpq_clear(ivar_626);
                uint64_t ivar_634;
                //copying to uint64 from mpz;
                ivar_634 = (uint64_t)mpz_get_ui(ivar_636);
                mpz_clear(ivar_636);
                ivar_621 = (ltedpeg__ent_adt_t)con_ltedpeg__fail((uint64_t)ivar_634);
                uint64_t ivar_623;
                uint8_t ivar_638;
                ivar_638 = (uint8_t)1;
                ivar_623 = (uint64_t)(ivar_37 - ivar_638);
                ltedpeg__state_t ivar_655;
                ltedpeg__scaffold_t ivar_641;
                ivar_641 = (ltedpeg__scaffold_t)ivar_14->scaf;
                ivar_641->count++;
                ltedpeg__state_t ivar_652;
                ltedpeg__scaffold_t ivar_654;
                ivar_654 = NULL;
                ivar_652 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_654);
                if (ivar_654 != NULL) ivar_654->count--;
                ltedpeg__scaffold_t ivar_653;
                ltedpeg_array_59_t ivar_642;
                ivar_642 = (ltedpeg_array_59_t)ivar_641->elems[ivar_54];
                ivar_642->count++;
                ltedpeg__scaffold_t ivar_649;
                ltedpeg_array_59_t ivar_651;
                ivar_651 = NULL;
                ivar_649 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_641, ivar_54, ivar_651);
                if (ivar_651 != NULL) ivar_651->count--;
                ltedpeg_array_59_t ivar_650;
                ltedpeg_array_59_t ivar_645;
                ltedpeg__ent_adt_t ivar_647;
                ivar_647 = NULL;
                ivar_645 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_642, ivar_58, ivar_647);
                if (ivar_647 != NULL) ivar_647->count--;
                ivar_650 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_645, ivar_58, ivar_621);
                if (ivar_621 != NULL) ivar_621->count--;
                ivar_653 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_649, ivar_54, ivar_650);
                if (ivar_650 != NULL) ivar_650->count--;
                ivar_655 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_652, ivar_653);
                if (ivar_653 != NULL) ivar_653->count--;
                ltedpeg__state_t ivar_660;
                ltedpeg__state_t ivar_657;
                ltedpeg__ent_adt_t ivar_659;
                ivar_659 = NULL;
                ivar_657 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_655, ivar_659);
                if (ivar_659 != NULL) ivar_659->count--;
                ivar_660 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_657, ivar_62);
                if (ivar_62 != NULL) ivar_62->count--;
                result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_660, ivar_623);
               } else {
                bool_t ivar_731;
                ivar_591->count++;
                ivar_731 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_591);
                if (ivar_731){
                 uint64_t ivar_669;
                 ivar_591->count++;
                 ivar_669 = (uint64_t)ltedpeg__ent_adt_dep((ltedpeg__ent_adt_t)ivar_591);
                 uint32_t ivar_670;
                 ivar_670 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_591);
                 ltedpeg__ent_adt_t ivar_680;
                 mpz_ptr_t ivar_702;
                 uint8_t ivar_685;
                 ivar_685 = (uint8_t)1;
                 mpq_ptr_t ivar_686;
                 mpq_ptr_t ivar_690;
                 //copying to mpq from uint64;
                 mpq_mk_set_ui(ivar_690, ivar_583);
                 mpq_ptr_t ivar_691;
                 //copying to mpq from uint64;
                 mpq_mk_set_ui(ivar_691, ivar_669);
                 ivar_686 = (mpq_ptr_t)real_defs__max((mpq_ptr_t)ivar_690, (mpq_ptr_t)ivar_691);
                 mpz_mk_set_q(ivar_702, ivar_686);
                 mpz_add_ui(ivar_702, ivar_702, ivar_685);
                 mpq_clear(ivar_686);
                 uint64_t ivar_697;
                 //copying to uint64 from mpz;
                 ivar_697 = (uint64_t)mpz_get_ui(ivar_702);
                 mpz_clear(ivar_702);
                 uint64_t ivar_701;
                 ivar_701 = (uint64_t)(ivar_584 + ivar_670);
                 uint32_t ivar_698;
                 //copying to uint32 from uint64;
                 ivar_698 = (uint32_t)ivar_701;
                 ivar_680 = (ltedpeg__ent_adt_t)con_ltedpeg__good((uint64_t)ivar_697, (uint32_t)ivar_698);
                 uint64_t ivar_682;
                 uint8_t ivar_704;
                 ivar_704 = (uint8_t)1;
                 ivar_682 = (uint64_t)(ivar_37 - ivar_704);
                 ltedpeg__state_t ivar_721;
                 ltedpeg__scaffold_t ivar_707;
                 ivar_707 = (ltedpeg__scaffold_t)ivar_14->scaf;
                 ivar_707->count++;
                 ltedpeg__state_t ivar_718;
                 ltedpeg__scaffold_t ivar_720;
                 ivar_720 = NULL;
                 ivar_718 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_720);
                 if (ivar_720 != NULL) ivar_720->count--;
                 ltedpeg__scaffold_t ivar_719;
                 ltedpeg_array_59_t ivar_708;
                 ivar_708 = (ltedpeg_array_59_t)ivar_707->elems[ivar_54];
                 ivar_708->count++;
                 ltedpeg__scaffold_t ivar_715;
                 ltedpeg_array_59_t ivar_717;
                 ivar_717 = NULL;
                 ivar_715 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_707, ivar_54, ivar_717);
                 if (ivar_717 != NULL) ivar_717->count--;
                 ltedpeg_array_59_t ivar_716;
                 ltedpeg_array_59_t ivar_711;
                 ltedpeg__ent_adt_t ivar_713;
                 ivar_713 = NULL;
                 ivar_711 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_708, ivar_58, ivar_713);
                 if (ivar_713 != NULL) ivar_713->count--;
                 ivar_716 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_711, ivar_58, ivar_680);
                 if (ivar_680 != NULL) ivar_680->count--;
                 ivar_719 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_715, ivar_54, ivar_716);
                 if (ivar_716 != NULL) ivar_716->count--;
                 ivar_721 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_718, ivar_719);
                 if (ivar_719 != NULL) ivar_719->count--;
                 ltedpeg__state_t ivar_726;
                 ltedpeg__state_t ivar_723;
                 ltedpeg__ent_adt_t ivar_725;
                 ivar_725 = NULL;
                 ivar_723 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_721, ivar_725);
                 if (ivar_725 != NULL) ivar_725->count--;
                 ivar_726 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_723, ivar_62);
                 if (ivar_62 != NULL) ivar_62->count--;
                 result = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_726, ivar_682);
                } else {
                 bool_t ivar_788;
                 ivar_788 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_591);
                 if (ivar_788){
                  release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_62);
                  uint32_t ivar_777;
                  ivar_777 = (uint32_t)(ivar_54 + ivar_584);
                  ltedpeg__ent_adt_t ivar_738;
                  uint64_t ivar_750;
                  ivar_750 = (uint64_t)(ivar_54 + ivar_584);
                  uint32_t ivar_747;
                  //copying to uint32 from uint64;
                  ivar_747 = (uint32_t)ivar_750;
                  ivar_738 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_747, (uint8_t)ivar_334);
                  uint64_t ivar_739;
                  uint64_t ivar_751;
                  ivar_751 = (uint64_t)ivar_14->depth;
                  uint8_t ivar_752;
                  ivar_752 = (uint8_t)1;
                  ivar_739 = (uint64_t)(ivar_751 + ivar_752);
                  ltedpeg__ent_adt_t ivar_740;
                  ivar_740 = (ltedpeg__ent_adt_t)ivar_14->stack;
                  ivar_740->count++;
                  ltedpeg__state_t ivar_765;
                  ltedpeg__state_t ivar_762;
                  ltedpeg__ent_adt_t ivar_764;
                  ivar_764 = NULL;
                  ivar_762 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_14, ivar_764);
                  if (ivar_764 != NULL) ivar_764->count--;
                  ivar_765 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_762, ivar_738);
                  if (ivar_738 != NULL) ivar_738->count--;
                  ltedpeg__state_t ivar_769;
                  ivar_769 = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_765, ivar_739);
                  ltedpeg__scaffold_t ivar_770;
                  ivar_770 = (ltedpeg__scaffold_t)ivar_769->scaf;
                  ivar_770->count++;
                  ltedpeg__state_t ivar_784;
                  ltedpeg__scaffold_t ivar_786;
                  ivar_786 = NULL;
                  ivar_784 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_769, ivar_786);
                  if (ivar_786 != NULL) ivar_786->count--;
                  ltedpeg__scaffold_t ivar_785;
                  ltedpeg_array_59_t ivar_771;
                  ivar_771 = (ltedpeg_array_59_t)ivar_770->elems[ivar_777];
                  ivar_771->count++;
                  ltedpeg__scaffold_t ivar_781;
                  ltedpeg_array_59_t ivar_783;
                  ivar_783 = NULL;
                  ivar_781 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_770, ivar_777, ivar_783);
                  if (ivar_783 != NULL) ivar_783->count--;
                  ltedpeg_array_59_t ivar_782;
                  ltedpeg_array_59_t ivar_774;
                  ltedpeg__ent_adt_t ivar_776;
                  ivar_776 = NULL;
                  ivar_774 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_771, ivar_334, ivar_776);
                  if (ivar_776 != NULL) ivar_776->count--;
                  ivar_782 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_774, ivar_334, ivar_740);
                  if (ivar_740 != NULL) ivar_740->count--;
                  ivar_785 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_781, ivar_777, ivar_782);
                  if (ivar_782 != NULL) ivar_782->count--;
                  result = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_784, ivar_785);
                  if (ivar_785 != NULL) ivar_785->count--;
                 } else {
                  ltedpeg__ent_adt_t ivar_795;
                  ivar_795 = (ltedpeg__ent_adt_t)con_ltedpeg__loop();
                  if (ivar_795 != NULL) ivar_795->count++;
                  uint64_t ivar_796;
                  uint8_t ivar_800;
                  ivar_800 = (uint8_t)1;
                  ivar_796 = (uint64_t)(ivar_37 - ivar_800);
                  bool_t ivar_798;
                  ivar_798 = (bool_t) true;
                  ltedpeg__state_t ivar_817;
                  ltedpeg__scaffold_t ivar_803;
                  ivar_803 = (ltedpeg__scaffold_t)ivar_14->scaf;
                  ivar_803->count++;
                  ltedpeg__state_t ivar_814;
                  ltedpeg__scaffold_t ivar_816;
                  ivar_816 = NULL;
                  ivar_814 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_816);
                  if (ivar_816 != NULL) ivar_816->count--;
                  ltedpeg__scaffold_t ivar_815;
                  ltedpeg_array_59_t ivar_804;
                  ivar_804 = (ltedpeg_array_59_t)ivar_803->elems[ivar_54];
                  ivar_804->count++;
                  ltedpeg__scaffold_t ivar_811;
                  ltedpeg_array_59_t ivar_813;
                  ivar_813 = NULL;
                  ivar_811 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_803, ivar_54, ivar_813);
                  if (ivar_813 != NULL) ivar_813->count--;
                  ltedpeg_array_59_t ivar_812;
                  ltedpeg_array_59_t ivar_807;
                  ltedpeg__ent_adt_t ivar_809;
                  ivar_809 = NULL;
                  ivar_807 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_804, ivar_58, ivar_809);
                  if (ivar_809 != NULL) ivar_809->count--;
                  ivar_812 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_807, ivar_58, ivar_795);
                  if (ivar_795 != NULL) ivar_795->count--;
                  ivar_815 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_811, ivar_54, ivar_812);
                  if (ivar_812 != NULL) ivar_812->count--;
                  ivar_817 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_814, ivar_815);
                  if (ivar_815 != NULL) ivar_815->count--;
                  ltedpeg__state_t ivar_821;
                  ivar_821 = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_817, ivar_796);
                  ltedpeg__state_t ivar_826;
                  ltedpeg__state_t ivar_823;
                  ltedpeg__ent_adt_t ivar_825;
                  ivar_825 = NULL;
                  ivar_823 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_821, ivar_825);
                  if (ivar_825 != NULL) ivar_825->count--;
                  ivar_826 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_823, ivar_62);
                  if (ivar_62 != NULL) ivar_62->count--;
                  result = (ltedpeg__state_t)update_ltedpeg__state_lflag(ivar_826, ivar_798);};};};
              } else {
               bool_t ivar_874;
               ivar_874 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_345);
               if (ivar_874){
                release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_62);
                ltedpeg__ent_adt_t ivar_838;
                ivar_838 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_54, (uint8_t)ivar_333);
                uint64_t ivar_839;
                uint8_t ivar_847;
                ivar_847 = (uint8_t)1;
                ivar_839 = (uint64_t)(ivar_37 + ivar_847);
                ltedpeg__state_t ivar_854;
                ltedpeg__state_t ivar_851;
                ltedpeg__ent_adt_t ivar_853;
                ivar_853 = NULL;
                ivar_851 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_14, ivar_853);
                if (ivar_853 != NULL) ivar_853->count--;
                ivar_854 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_851, ivar_838);
                if (ivar_838 != NULL) ivar_838->count--;
                ltedpeg__state_t ivar_858;
                ivar_858 = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_854, ivar_839);
                ltedpeg__scaffold_t ivar_859;
                ivar_859 = (ltedpeg__scaffold_t)ivar_858->scaf;
                ivar_859->count++;
                ltedpeg__state_t ivar_870;
                ltedpeg__scaffold_t ivar_872;
                ivar_872 = NULL;
                ivar_870 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_858, ivar_872);
                if (ivar_872 != NULL) ivar_872->count--;
                ltedpeg__scaffold_t ivar_871;
                ltedpeg_array_59_t ivar_860;
                ivar_860 = (ltedpeg_array_59_t)ivar_859->elems[ivar_54];
                ivar_860->count++;
                ltedpeg__scaffold_t ivar_867;
                ltedpeg_array_59_t ivar_869;
                ivar_869 = NULL;
                ivar_867 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_859, ivar_54, ivar_869);
                if (ivar_869 != NULL) ivar_869->count--;
                ltedpeg_array_59_t ivar_868;
                ltedpeg_array_59_t ivar_863;
                ltedpeg__ent_adt_t ivar_865;
                ivar_865 = NULL;
                ivar_863 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_860, ivar_333, ivar_865);
                if (ivar_865 != NULL) ivar_865->count--;
                ivar_868 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_863, ivar_333, ivar_31);
                if (ivar_31 != NULL) ivar_31->count--;
                ivar_871 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_867, ivar_54, ivar_868);
                if (ivar_868 != NULL) ivar_868->count--;
                result = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_870, ivar_871);
                if (ivar_871 != NULL) ivar_871->count--;
               } else {
                release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_31);
                ltedpeg__ent_adt_t ivar_881;
                ivar_881 = (ltedpeg__ent_adt_t)con_ltedpeg__loop();
                if (ivar_881 != NULL) ivar_881->count++;
                uint64_t ivar_882;
                uint8_t ivar_886;
                ivar_886 = (uint8_t)1;
                ivar_882 = (uint64_t)(ivar_37 - ivar_886);
                bool_t ivar_884;
                ivar_884 = (bool_t) true;
                ltedpeg__state_t ivar_903;
                ltedpeg__scaffold_t ivar_889;
                ivar_889 = (ltedpeg__scaffold_t)ivar_14->scaf;
                ivar_889->count++;
                ltedpeg__state_t ivar_900;
                ltedpeg__scaffold_t ivar_902;
                ivar_902 = NULL;
                ivar_900 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_14, ivar_902);
                if (ivar_902 != NULL) ivar_902->count--;
                ltedpeg__scaffold_t ivar_901;
                ltedpeg_array_59_t ivar_890;
                ivar_890 = (ltedpeg_array_59_t)ivar_889->elems[ivar_54];
                ivar_890->count++;
                ltedpeg__scaffold_t ivar_897;
                ltedpeg_array_59_t ivar_899;
                ivar_899 = NULL;
                ivar_897 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_889, ivar_54, ivar_899);
                if (ivar_899 != NULL) ivar_899->count--;
                ltedpeg_array_59_t ivar_898;
                ltedpeg_array_59_t ivar_893;
                ltedpeg__ent_adt_t ivar_895;
                ivar_895 = NULL;
                ivar_893 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_890, ivar_58, ivar_895);
                if (ivar_895 != NULL) ivar_895->count--;
                ivar_898 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_893, ivar_58, ivar_881);
                if (ivar_881 != NULL) ivar_881->count--;
                ivar_901 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_897, ivar_54, ivar_898);
                if (ivar_898 != NULL) ivar_898->count--;
                ivar_903 = (ltedpeg__state_t)update_ltedpeg__state_scaf(ivar_900, ivar_901);
                if (ivar_901 != NULL) ivar_901->count--;
                ltedpeg__state_t ivar_907;
                ivar_907 = (ltedpeg__state_t)update_ltedpeg__state_depth(ivar_903, ivar_882);
                ltedpeg__state_t ivar_912;
                ltedpeg__state_t ivar_909;
                ltedpeg__ent_adt_t ivar_911;
                ivar_911 = NULL;
                ivar_909 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_907, ivar_911);
                if (ivar_911 != NULL) ivar_911->count--;
                ivar_912 = (ltedpeg__state_t)update_ltedpeg__state_stack(ivar_909, ivar_62);
                if (ivar_62 != NULL) ivar_62->count--;
                result = (ltedpeg__state_t)update_ltedpeg__state_lflag(ivar_912, ivar_884);};};};};};};};};
        return result;
}

ltedpeg_closure_98_t new_ltedpeg_closure_98(void){
        static struct ltedpeg_funtype_97_ftbl_s ftbl = {.fptr = (ltedpeg__state_t (*)(ltedpeg_funtype_97_t, ltedpeg__state_t))&f_ltedpeg_closure_98, .mptr = (ltedpeg__state_t (*)(ltedpeg_funtype_97_t, ltedpeg__state_t))&m_ltedpeg_closure_98, .rptr =  (void (*)(ltedpeg_funtype_97_t))&release_ltedpeg_closure_98, .cptr = (ltedpeg_funtype_97_t (*)(ltedpeg_funtype_97_t))&copy_ltedpeg_closure_98};
        ltedpeg_closure_98_t tmp = (ltedpeg_closure_98_t) safe_malloc(sizeof(struct ltedpeg_closure_98_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_98(ltedpeg_funtype_97_t closure){
        ltedpeg_closure_98_t x = (ltedpeg_closure_98_t)closure;
        x->count--;
        if (x->count <= 0){
         release_bytestrings__bytestring((bytestrings__bytestring_t)x->fvar_1);
         release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)x->fvar_2);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__state((ltedpeg__state_t)x->htbl->data[j].key); release_ltedpeg__state((ltedpeg__state_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_98_t copy_ltedpeg_closure_98(ltedpeg_closure_98_t x){
        ltedpeg_closure_98_t y = new_ltedpeg_closure_98();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_97_htbl_t new_htbl = (ltedpeg_funtype_97_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_97_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_97_hashentry_t * new_data = (ltedpeg_funtype_97_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_97_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__state_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (ltedpeg__state_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_99(ltedpeg_funtype_99_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_99_t copy_ltedpeg_funtype_99(ltedpeg_funtype_99_t x){return x->ftbl->cptr(x);}

bool_t equal_ltedpeg_funtype_99(ltedpeg_funtype_99_t x, ltedpeg_funtype_99_t y){
        return false;}

char* json_ltedpeg_funtype_99(ltedpeg_funtype_99_t x){char * result = safe_malloc(28); sprintf(result, "%s", "\"ltedpeg_funtype_99\""); return result;}


ordstruct_adt__ordstruct_adt_t f_ltedpeg_closure_100(struct ltedpeg_closure_100_s * closure, ltedpeg__state_t bvar){
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_99((ltedpeg_funtype_99_t)closure);
        ordstruct_adt__ordstruct_adt_t result;
        result = (ordstruct_adt__ordstruct_adt_t)h_ltedpeg_closure_100(bvar, fvar_1);
        return result;
}

ordstruct_adt__ordstruct_adt_t m_ltedpeg_closure_100(struct ltedpeg_closure_100_s * closure, ltedpeg__state_t bvar){
        bytestrings__bytestring_t fvar_1 = closure->fvar_1;
        fvar_1->count++;
        release_ltedpeg_funtype_99((ltedpeg_funtype_99_t)closure);
        return h_ltedpeg_closure_100(bvar, fvar_1);}

ordstruct_adt__ordstruct_adt_t h_ltedpeg_closure_100(ltedpeg__state_t ivar_12, bytestrings__bytestring_t ivar_2){
        ordstruct_adt__ordstruct_adt_t result;

        uint64_t ivar_58;
        uint32_t ivar_35;
        ivar_35 = (uint32_t)ivar_2->length;
        ltedpeg__scaffold_t ivar_36;
        ivar_36 = (ltedpeg__scaffold_t)ivar_12->scaf;
        ivar_36->count++;
        ltedpeg_funtype_54_t ivar_38;
        ltedpeg_closure_101_t cl33801;
        cl33801 = new_ltedpeg_closure_101();
        ivar_38 = (ltedpeg_funtype_54_t)cl33801;
        uint32_t ivar_40;
        ivar_40 = (uint32_t)ivar_2->length;
        ivar_58 = (uint64_t)ltedpeg__scafcount((uint32_t)ivar_35, (ltedpeg__scaffold_t)ivar_36, (ltedpeg_funtype_54_t)ivar_38, (uint32_t)ivar_40);
        mpz_ptr_t ivar_55;
        //copying to mpz from uint64;
        mpz_mk_set_ui(ivar_55, ivar_58);
        mpz_ptr_t ivar_56;
        uint64_t ivar_41;
        uint32_t ivar_43;
        uint32_t ivar_45;
        ivar_45 = (uint32_t)ivar_2->length;
        uint8_t ivar_46;
        ivar_46 = (uint8_t)1;
        ivar_43 = (uint32_t)(ivar_45 + ivar_46);
        uint8_t ivar_44;
        ivar_44 = (uint8_t)ltedpeg__num_non_terminals();
        ivar_41 = (uint64_t)((uint64_t)ivar_43 * (uint64_t)ivar_44);
        uint64_t ivar_42;
        ivar_42 = (uint64_t)ivar_12->depth;
        release_ltedpeg__state((ltedpeg__state_t)ivar_12);
        mpz_mk_set_ui(ivar_56, (uint64_t)ivar_41);
        mpz_sub_ui(ivar_56, ivar_56, (uint64_t)ivar_42);
        result = (ordstruct_adt__ordstruct_adt_t)lex2__lex2((mpz_ptr_t)ivar_55, (mpz_ptr_t)ivar_56);
        return result;
}

ltedpeg_closure_100_t new_ltedpeg_closure_100(void){
        static struct ltedpeg_funtype_99_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_99_t, ltedpeg__state_t))&f_ltedpeg_closure_100, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(ltedpeg_funtype_99_t, ltedpeg__state_t))&m_ltedpeg_closure_100, .rptr =  (void (*)(ltedpeg_funtype_99_t))&release_ltedpeg_closure_100, .cptr = (ltedpeg_funtype_99_t (*)(ltedpeg_funtype_99_t))&copy_ltedpeg_closure_100};
        ltedpeg_closure_100_t tmp = (ltedpeg_closure_100_t) safe_malloc(sizeof(struct ltedpeg_closure_100_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_100(ltedpeg_funtype_99_t closure){
        ltedpeg_closure_100_t x = (ltedpeg_closure_100_t)closure;
        x->count--;
        if (x->count <= 0){
         release_bytestrings__bytestring((bytestrings__bytestring_t)x->fvar_1);
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__state((ltedpeg__state_t)x->htbl->data[j].key); release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_100_t copy_ltedpeg_closure_100(ltedpeg_closure_100_t x){
        ltedpeg_closure_100_t y = new_ltedpeg_closure_100();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            ltedpeg_funtype_99_htbl_t new_htbl = (ltedpeg_funtype_99_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_99_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_99_hashentry_t * new_data = (ltedpeg_funtype_99_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_99_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__state_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (ordstruct_adt__ordstruct_adt_t)x->htbl->data[j].value;
                  if (new_data[j].value != NULL) new_data[j].value->count++;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


bool_t f_ltedpeg_closure_101(struct ltedpeg_closure_101_s * closure, ltedpeg__ent_adt_t bvar){
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        bool_t result;
        result = (bool_t)h_ltedpeg_closure_101(bvar);
        return result;
}

bool_t m_ltedpeg_closure_101(struct ltedpeg_closure_101_s * closure, ltedpeg__ent_adt_t bvar){
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)closure);
        return h_ltedpeg_closure_101(bvar);}

bool_t h_ltedpeg_closure_101(ltedpeg__ent_adt_t ivar_28){
        bool_t result;

        result = (bool_t)ltedpeg__push_or_pendingp((ltedpeg__ent_adt_t)ivar_28);
        return result;
}

ltedpeg_closure_101_t new_ltedpeg_closure_101(void){
        static struct ltedpeg_funtype_54_ftbl_s ftbl = {.fptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&f_ltedpeg_closure_101, .mptr = (bool_t (*)(ltedpeg_funtype_54_t, ltedpeg__ent_adt_t))&m_ltedpeg_closure_101, .rptr =  (void (*)(ltedpeg_funtype_54_t))&release_ltedpeg_closure_101, .cptr = (ltedpeg_funtype_54_t (*)(ltedpeg_funtype_54_t))&copy_ltedpeg_closure_101};
        ltedpeg_closure_101_t tmp = (ltedpeg_closure_101_t) safe_malloc(sizeof(struct ltedpeg_closure_101_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_101(ltedpeg_funtype_54_t closure){
        ltedpeg_closure_101_t x = (ltedpeg_closure_101_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].key);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_101_t copy_ltedpeg_closure_101(ltedpeg_closure_101_t x){
        ltedpeg_closure_101_t y = new_ltedpeg_closure_101();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            ltedpeg_funtype_54_htbl_t new_htbl = (ltedpeg_funtype_54_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_54_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_54_hashentry_t * new_data = (ltedpeg_funtype_54_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_54_hashentry_s));
            
             for (uint32_t j = 0; j < new_htbl->size; j++){
                  new_data[j].keyhash = (uint32_t)x->htbl->data[j].keyhash;
                  new_data[j].key = (ltedpeg__ent_adt_t)x->htbl->data[j].key;
                  if (new_data[j].key != NULL) new_data[j].key->count++;
                  new_data[j].value = (bool_t)x->htbl->data[j].value;
             };
            new_htbl->data = new_data;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_ltedpeg_funtype_102(ltedpeg_funtype_102_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ltedpeg_funtype_102_t copy_ltedpeg_funtype_102(ltedpeg_funtype_102_t x){return x->ftbl->cptr(x);}

uint32_t lookup_ltedpeg_funtype_102(ltedpeg_funtype_102_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        ltedpeg_funtype_102_hashentry_t data = htbl->data[hashindex];
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

ltedpeg_funtype_102_t dupdate_ltedpeg_funtype_102(ltedpeg_funtype_102_t a, uint8_t i, ltedpeg__ent_adt_t v){
        ltedpeg_funtype_102_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (ltedpeg_funtype_102_htbl_t)safe_malloc(sizeof(struct ltedpeg_funtype_102_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (ltedpeg_funtype_102_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct ltedpeg_funtype_102_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        ltedpeg_funtype_102_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                ltedpeg_funtype_102_hashentry_t * new_data = (ltedpeg_funtype_102_hashentry_t *)safe_malloc(new_size * sizeof(struct ltedpeg_funtype_102_hashentry_s));
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
        uint32_t hashindex = lookup_ltedpeg_funtype_102(htbl, i, ihash);
        ltedpeg_funtype_102_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (ltedpeg__ent_adt_t)v; htbl->num_entries++;}
            else {ltedpeg__ent_adt_t tempvalue;tempvalue = (ltedpeg__ent_adt_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (ltedpeg__ent_adt_t)v;if (v != NULL) v->count++;if (tempvalue != NULL)release_ltedpeg__ent_adt(tempvalue);};
        return a;

}

ltedpeg_funtype_102_t update_ltedpeg_funtype_102(ltedpeg_funtype_102_t a, uint8_t i, ltedpeg__ent_adt_t v){
        if (a->count == 1){
                return dupdate_ltedpeg_funtype_102(a, i, v);
            } else {
                ltedpeg_funtype_102_t x = copy_ltedpeg_funtype_102(a);
                a->count--;
                return dupdate_ltedpeg_funtype_102(x, i, v);
            }}

bool_t equal_ltedpeg_funtype_102(ltedpeg_funtype_102_t x, ltedpeg_funtype_102_t y){
        return false;}

char* json_ltedpeg_funtype_102(ltedpeg_funtype_102_t x){char * result = safe_malloc(29); sprintf(result, "%s", "\"ltedpeg_funtype_102\""); return result;}


ltedpeg__ent_adt_t f_ltedpeg_closure_103(struct ltedpeg_closure_103_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        ltedpeg_funtype_102_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_ltedpeg_funtype_102(htbl, bvar, hash);
        ltedpeg_funtype_102_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
                ltedpeg__ent_adt_t result;
                release_ltedpeg_funtype_102((ltedpeg_funtype_102_t)closure);
                result = (ltedpeg__ent_adt_t)entry.value;
                return result;}
        else {

            release_ltedpeg_funtype_102((ltedpeg_funtype_102_t)closure);
            ltedpeg__ent_adt_t result;
            result = (ltedpeg__ent_adt_t)h_ltedpeg_closure_103(bvar);
            return result;};
        }

      else {
        release_ltedpeg_funtype_102((ltedpeg_funtype_102_t)closure);
        ltedpeg__ent_adt_t result;
        result = (ltedpeg__ent_adt_t)h_ltedpeg_closure_103(bvar);
        return result;}
}

ltedpeg__ent_adt_t m_ltedpeg_closure_103(struct ltedpeg_closure_103_s * closure, uint8_t bvar){
        release_ltedpeg_funtype_102((ltedpeg_funtype_102_t)closure);
        return h_ltedpeg_closure_103(bvar);}

ltedpeg__ent_adt_t h_ltedpeg_closure_103(uint8_t ivar_7){
        ltedpeg__ent_adt_t result;

        result = (ltedpeg__ent_adt_t)con_ltedpeg__pending();
        if (result != NULL) result->count++;
        return result;
}

ltedpeg_closure_103_t new_ltedpeg_closure_103(void){
        static struct ltedpeg_funtype_102_ftbl_s ftbl = {.fptr = (ltedpeg__ent_adt_t (*)(ltedpeg_funtype_102_t, uint8_t))&f_ltedpeg_closure_103, .mptr = (ltedpeg__ent_adt_t (*)(ltedpeg_funtype_102_t, uint8_t))&m_ltedpeg_closure_103, .rptr =  (void (*)(ltedpeg_funtype_102_t))&release_ltedpeg_closure_103, .cptr = (ltedpeg_funtype_102_t (*)(ltedpeg_funtype_102_t))&copy_ltedpeg_closure_103};
        ltedpeg_closure_103_t tmp = (ltedpeg_closure_103_t) safe_malloc(sizeof(struct ltedpeg_closure_103_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ltedpeg_closure_103(ltedpeg_funtype_102_t closure){
        ltedpeg_closure_103_t x = (ltedpeg_closure_103_t)closure;
        x->count--;
        if (x->count <= 0){
          if (x->htbl != NULL){
               for (uint32_t j = 0; j < x->htbl->size; j++){release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)x->htbl->data[j].value);}

               safe_free(x->htbl->data);

               safe_free(x->htbl);

               }

        //printf("\nFreeing\n");
        safe_free(x);}}

ltedpeg_closure_103_t copy_ltedpeg_closure_103(ltedpeg_closure_103_t x){
        ltedpeg_closure_103_t y = new_ltedpeg_closure_103();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            ltedpeg_funtype_102_htbl_t new_htbl = (ltedpeg_funtype_102_htbl_t) safe_malloc(sizeof(struct ltedpeg_funtype_102_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ltedpeg_funtype_102_hashentry_t * new_data = (ltedpeg_funtype_102_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ltedpeg_funtype_102_hashentry_s));
            
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
uint8_t ltedpeg__num_non_terminals(void){
        uint8_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        result = (uint8_t)255;
        defined = true;};
        
        
        return result;
}

bool_t rec_ltedpeg__failp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)0;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__ent_adt_index;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__pendingp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)1;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__ent_adt_index;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__loopp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)2;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__ent_adt_index;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__goodp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)3;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__ent_adt_index;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__pushp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)4;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__ent_adt_index;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

ltedpeg__ent_adt_t update_ltedpeg__ent_adt_dep(ltedpeg__ent_adt_t ivar_1, uint64_t ivar_7){
        ltedpeg__ent_adt_t  result;

        bool_t ivar_9;
        uint32_t ivar_10;
        ivar_10 = (uint32_t)ivar_1->ltedpeg__ent_adt_index;
        uint32_t ivar_11;
        ivar_11 = (uint32_t)0;
        ivar_9 = (ivar_10 == ivar_11);
        if (ivar_9){
             ltedpeg__fail_t ivar_8;
             //copying to ltedpeg__fail from ltedpeg__ent_adt;
             ivar_8 = (ltedpeg__fail_t)ivar_1;
             if (ivar_8 != NULL) ivar_8->count++;
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (ltedpeg__ent_adt_t)update_ltedpeg__fail_dep(ivar_8, ivar_7);
        } else {
             ltedpeg__good_t ivar_12;
             //copying to ltedpeg__good from ltedpeg__ent_adt;
             ivar_12 = (ltedpeg__good_t)ivar_1;
             if (ivar_12 != NULL) ivar_12->count++;
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (ltedpeg__ent_adt_t)update_ltedpeg__good_dep(ivar_12, ivar_7);};
        
        
        return result;
}

uint64_t ltedpeg__ent_adt_dep(ltedpeg__ent_adt_t ivar_1){
        uint64_t  result;

        bool_t ivar_3;
        uint32_t ivar_4;
        ivar_4 = (uint32_t)ivar_1->ltedpeg__ent_adt_index;
        uint32_t ivar_5;
        ivar_5 = (uint32_t)0;
        ivar_3 = (ivar_4 == ivar_5);
        if (ivar_3){
             ltedpeg__fail_t ivar_2;
             //copying to ltedpeg__fail from ltedpeg__ent_adt;
             ivar_2 = (ltedpeg__fail_t)ivar_1;
             if (ivar_2 != NULL) ivar_2->count++;
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (uint64_t)ivar_2->dep;
             release_ltedpeg__fail((ltedpeg__fail_t)ivar_2);
        } else {
             ltedpeg__good_t ivar_6;
             //copying to ltedpeg__good from ltedpeg__ent_adt;
             ivar_6 = (ltedpeg__good_t)ivar_1;
             if (ivar_6 != NULL) ivar_6->count++;
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (uint64_t)ivar_6->dep;
             release_ltedpeg__good((ltedpeg__good_t)ivar_6);};
        
        
        return result;
}

ltedpeg__good_t update_ltedpeg__ent_adt_span(ltedpeg__ent_adt_t ivar_1, uint32_t ivar_3){
        ltedpeg__good_t  result;

        ltedpeg__good_t ivar_2;
        //copying to ltedpeg__good from ltedpeg__ent_adt;
        ivar_2 = (ltedpeg__good_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ltedpeg__good_t)update_ltedpeg__good_span(ivar_2, ivar_3);
        
        
        return result;
}

uint32_t acc_ltedpeg__ent_adt_span(ltedpeg__ent_adt_t ivar_1){
        uint32_t  result;

        ltedpeg__good_t ivar_2;
        //copying to ltedpeg__good from ltedpeg__ent_adt;
        ivar_2 = (ltedpeg__good_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (uint32_t)ivar_2->span;
        release_ltedpeg__good((ltedpeg__good_t)ivar_2);
        
        
        return result;
}

ltedpeg__push_t update_ltedpeg__ent_adt_pos(ltedpeg__ent_adt_t ivar_1, uint32_t ivar_3){
        ltedpeg__push_t  result;

        ltedpeg__push_t ivar_2;
        //copying to ltedpeg__push from ltedpeg__ent_adt;
        ivar_2 = (ltedpeg__push_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ltedpeg__push_t)update_ltedpeg__push_pos(ivar_2, ivar_3);
        
        
        return result;
}

uint32_t acc_ltedpeg__ent_adt_pos(ltedpeg__ent_adt_t ivar_1){
        uint32_t  result;

        ltedpeg__push_t ivar_2;
        //copying to ltedpeg__push from ltedpeg__ent_adt;
        ivar_2 = (ltedpeg__push_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (uint32_t)ivar_2->pos;
        release_ltedpeg__push((ltedpeg__push_t)ivar_2);
        
        
        return result;
}

ltedpeg__push_t update_ltedpeg__ent_adt_nt(ltedpeg__ent_adt_t ivar_1, uint8_t ivar_3){
        ltedpeg__push_t  result;

        ltedpeg__push_t ivar_2;
        //copying to ltedpeg__push from ltedpeg__ent_adt;
        ivar_2 = (ltedpeg__push_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (ltedpeg__push_t)update_ltedpeg__push_nt(ivar_2, ivar_3);
        
        
        return result;
}

uint8_t acc_ltedpeg__ent_adt_nt(ltedpeg__ent_adt_t ivar_1){
        uint8_t  result;

        ltedpeg__push_t ivar_2;
        //copying to ltedpeg__push from ltedpeg__ent_adt;
        ivar_2 = (ltedpeg__push_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
        result = (uint8_t)ivar_2->nt;
        release_ltedpeg__push((ltedpeg__push_t)ivar_2);
        
        
        return result;
}

ltedpeg__ent_adt_t con_ltedpeg__fail(uint64_t ivar_2){
        ltedpeg__ent_adt_t  result;

        uint8_t ivar_1;
        ivar_1 = (uint8_t)0;
        ltedpeg__fail_t tmp33228 = new_ltedpeg__fail();;
        result = (ltedpeg__ent_adt_t)tmp33228;
        tmp33228->ltedpeg__ent_adt_index = (uint8_t)ivar_1;
        tmp33228->dep = (uint64_t)ivar_2;
        
        
        return result;
}

ltedpeg__ent_adt_t con_ltedpeg__pending(void){
        ltedpeg__ent_adt_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        uint8_t ivar_1;
        ivar_1 = (uint8_t)1;
        ltedpeg__ent_adt_t tmp33229 = new_ltedpeg__ent_adt();;
        result = (ltedpeg__ent_adt_t)tmp33229;
        tmp33229->ltedpeg__ent_adt_index = (uint8_t)ivar_1;
        defined = true;};
        
        
        return result;
}

ltedpeg__ent_adt_t con_ltedpeg__loop(void){
        ltedpeg__ent_adt_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        uint8_t ivar_1;
        ivar_1 = (uint8_t)2;
        ltedpeg__ent_adt_t tmp33230 = new_ltedpeg__ent_adt();;
        result = (ltedpeg__ent_adt_t)tmp33230;
        tmp33230->ltedpeg__ent_adt_index = (uint8_t)ivar_1;
        defined = true;};
        
        
        return result;
}

ltedpeg__ent_adt_t con_ltedpeg__good(uint64_t ivar_2, uint32_t ivar_3){
        ltedpeg__ent_adt_t  result;

        uint8_t ivar_1;
        ivar_1 = (uint8_t)3;
        ltedpeg__good_t tmp33231 = new_ltedpeg__good();;
        result = (ltedpeg__ent_adt_t)tmp33231;
        tmp33231->ltedpeg__ent_adt_index = (uint8_t)ivar_1;
        tmp33231->dep = (uint64_t)ivar_2;
        tmp33231->span = (uint32_t)ivar_3;
        
        
        return result;
}

ltedpeg__ent_adt_t con_ltedpeg__push(uint32_t ivar_2, uint8_t ivar_3){
        ltedpeg__ent_adt_t  result;

        uint8_t ivar_1;
        ivar_1 = (uint8_t)4;
        ltedpeg__push_t tmp33232 = new_ltedpeg__push();;
        result = (ltedpeg__ent_adt_t)tmp33232;
        tmp33232->ltedpeg__ent_adt_index = (uint8_t)ivar_1;
        tmp33232->pos = (uint32_t)ivar_2;
        tmp33232->nt = (uint8_t)ivar_3;
        
        
        return result;
}

uint8_t ltedpeg__ord_1(ltedpeg__ent_adt_t ivar_1){
        uint8_t  result;

        bool_t ivar_7;
        ivar_1->count++;
        ivar_7 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_1);
        if (ivar_7){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (uint8_t)0;
        } else {
             bool_t ivar_11;
             ivar_1->count++;
             ivar_11 = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_1);
             if (ivar_11){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
           result = (uint8_t)1;
             } else {
           bool_t ivar_15;
           ivar_1->count++;
           ivar_15 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_1);
           if (ivar_15){
           release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
           result = (uint8_t)2;
           } else {
           bool_t ivar_27;
           ivar_27 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_1);
           if (ivar_27){
            result = (uint8_t)3;
           } else {
            result = (uint8_t)4;};};};};
        
        
        return result;
}

bool_t ltedpeg__subterm_1(ltedpeg__ent_adt_t ivar_1, ltedpeg__ent_adt_t ivar_2){
        bool_t  result;

        result = (bool_t) equal_ltedpeg__ent_adt(ivar_1, ivar_2);
        
        
        return result;
}

bool_t ltedpeg__doublelessp_1(ltedpeg__ent_adt_t ivar_1, ltedpeg__ent_adt_t ivar_2){
        bool_t  result;

        result = (bool_t) false;
        
        
        return result;
}

ltedpeg_funtype_5_t ltedpeg__reduce_nat_1(ltedpeg_funtype_6_t ivar_1, mpz_ptr_t ivar_3, mpz_ptr_t ivar_4, ltedpeg_funtype_8_t ivar_5, ltedpeg_funtype_10_t ivar_7){
        ltedpeg_funtype_5_t  result;

        ltedpeg_closure_11_t cl33251;
        cl33251 = new_ltedpeg_closure_11();
        cl33251->fvar_1 = (ltedpeg_funtype_6_t)ivar_1;
        if (cl33251->fvar_1 != NULL) cl33251->fvar_1->count++;
        mpz_set(cl33251->fvar_2, ivar_4);
        cl33251->fvar_3 = (ltedpeg_funtype_8_t)ivar_5;
        if (cl33251->fvar_3 != NULL) cl33251->fvar_3->count++;
        cl33251->fvar_4 = (ltedpeg_funtype_10_t)ivar_7;
        if (cl33251->fvar_4 != NULL) cl33251->fvar_4->count++;
        mpz_set(cl33251->fvar_5, ivar_3);
        release_ltedpeg_funtype_6((ltedpeg_funtype_6_t)ivar_1);
        mpz_clear(ivar_4);
        release_ltedpeg_funtype_8((ltedpeg_funtype_8_t)ivar_5);
        release_ltedpeg_funtype_10((ltedpeg_funtype_10_t)ivar_7);
        mpz_clear(ivar_3);
        result = (ltedpeg_funtype_5_t)cl33251;
        
        
        return result;
}

ltedpeg_funtype_5_t ltedpeg__REDUCE_nat_1(ltedpeg_funtype_13_t ivar_1, ltedpeg_funtype_5_t ivar_3, ltedpeg_funtype_5_t ivar_5, ltedpeg_funtype_15_t ivar_7, ltedpeg_funtype_17_t ivar_9){
        ltedpeg_funtype_5_t  result;

        ltedpeg_closure_18_t cl33285;
        cl33285 = new_ltedpeg_closure_18();
        cl33285->fvar_1 = (ltedpeg_funtype_13_t)ivar_1;
        if (cl33285->fvar_1 != NULL) cl33285->fvar_1->count++;
        cl33285->fvar_2 = (ltedpeg_funtype_5_t)ivar_5;
        if (cl33285->fvar_2 != NULL) cl33285->fvar_2->count++;
        cl33285->fvar_3 = (ltedpeg_funtype_15_t)ivar_7;
        if (cl33285->fvar_3 != NULL) cl33285->fvar_3->count++;
        cl33285->fvar_4 = (ltedpeg_funtype_17_t)ivar_9;
        if (cl33285->fvar_4 != NULL) cl33285->fvar_4->count++;
        cl33285->fvar_5 = (ltedpeg_funtype_5_t)ivar_3;
        if (cl33285->fvar_5 != NULL) cl33285->fvar_5->count++;
        release_ltedpeg_funtype_13((ltedpeg_funtype_13_t)ivar_1);
        release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)ivar_5);
        release_ltedpeg_funtype_15((ltedpeg_funtype_15_t)ivar_7);
        release_ltedpeg_funtype_17((ltedpeg_funtype_17_t)ivar_9);
        release_ltedpeg_funtype_5((ltedpeg_funtype_5_t)ivar_3);
        result = (ltedpeg_funtype_5_t)cl33285;
        
        
        return result;
}

ltedpeg_funtype_19_t ltedpeg__reduce_ordinal_1(ltedpeg_funtype_20_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_3, ordstruct_adt__ordstruct_adt_t ivar_4, ltedpeg_funtype_21_t ivar_5, ltedpeg_funtype_22_t ivar_7){
        ltedpeg_funtype_19_t  result;

        ltedpeg_closure_23_t cl33303;
        cl33303 = new_ltedpeg_closure_23();
        cl33303->fvar_1 = (ltedpeg_funtype_20_t)ivar_1;
        if (cl33303->fvar_1 != NULL) cl33303->fvar_1->count++;
        cl33303->fvar_2 = (ordstruct_adt__ordstruct_adt_t)ivar_4;
        if (cl33303->fvar_2 != NULL) cl33303->fvar_2->count++;
        cl33303->fvar_3 = (ltedpeg_funtype_21_t)ivar_5;
        if (cl33303->fvar_3 != NULL) cl33303->fvar_3->count++;
        cl33303->fvar_4 = (ltedpeg_funtype_22_t)ivar_7;
        if (cl33303->fvar_4 != NULL) cl33303->fvar_4->count++;
        cl33303->fvar_5 = (ordstruct_adt__ordstruct_adt_t)ivar_3;
        if (cl33303->fvar_5 != NULL) cl33303->fvar_5->count++;
        release_ltedpeg_funtype_20((ltedpeg_funtype_20_t)ivar_1);
        release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)ivar_4);
        release_ltedpeg_funtype_21((ltedpeg_funtype_21_t)ivar_5);
        release_ltedpeg_funtype_22((ltedpeg_funtype_22_t)ivar_7);
        release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)ivar_3);
        result = (ltedpeg_funtype_19_t)cl33303;
        
        
        return result;
}

ltedpeg_funtype_19_t ltedpeg__REDUCE_ordinal_1(ltedpeg_funtype_24_t ivar_1, ltedpeg_funtype_19_t ivar_3, ltedpeg_funtype_19_t ivar_5, ltedpeg_funtype_25_t ivar_7, ltedpeg_funtype_26_t ivar_9){
        ltedpeg_funtype_19_t  result;

        ltedpeg_closure_27_t cl33337;
        cl33337 = new_ltedpeg_closure_27();
        cl33337->fvar_1 = (ltedpeg_funtype_24_t)ivar_1;
        if (cl33337->fvar_1 != NULL) cl33337->fvar_1->count++;
        cl33337->fvar_2 = (ltedpeg_funtype_19_t)ivar_5;
        if (cl33337->fvar_2 != NULL) cl33337->fvar_2->count++;
        cl33337->fvar_3 = (ltedpeg_funtype_25_t)ivar_7;
        if (cl33337->fvar_3 != NULL) cl33337->fvar_3->count++;
        cl33337->fvar_4 = (ltedpeg_funtype_26_t)ivar_9;
        if (cl33337->fvar_4 != NULL) cl33337->fvar_4->count++;
        cl33337->fvar_5 = (ltedpeg_funtype_19_t)ivar_3;
        if (cl33337->fvar_5 != NULL) cl33337->fvar_5->count++;
        release_ltedpeg_funtype_24((ltedpeg_funtype_24_t)ivar_1);
        release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)ivar_5);
        release_ltedpeg_funtype_25((ltedpeg_funtype_25_t)ivar_7);
        release_ltedpeg_funtype_26((ltedpeg_funtype_26_t)ivar_9);
        release_ltedpeg_funtype_19((ltedpeg_funtype_19_t)ivar_3);
        result = (ltedpeg_funtype_19_t)cl33337;
        
        
        return result;
}

bool_t rec_ltedpeg__epsilonp(ltedpeg__prepeg_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)0;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__prepeg_adt_index;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__failurep(ltedpeg__prepeg_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)1;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__prepeg_adt_index;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__anyp(ltedpeg__prepeg_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)2;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__prepeg_adt_index;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__terminalp(ltedpeg__prepeg_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)3;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__prepeg_adt_index;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

bool_t rec_ltedpeg__ltep(ltedpeg__prepeg_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_3;
        ivar_3 = (uint8_t)4;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ltedpeg__prepeg_adt_index;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

ltedpeg__any_t update_ltedpeg__prepeg_adt_dpg(ltedpeg__prepeg_adt_t ivar_1, dpeg__dpeg_grammar_t ivar_3){
        ltedpeg__any_t  result;

        ltedpeg__any_t ivar_2;
        //copying to ltedpeg__any from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__any_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ltedpeg__any_t)update_ltedpeg__any_dpg(ivar_2, ivar_3);
        
        
        return result;
}

dpeg__dpeg_grammar_t acc_ltedpeg__prepeg_adt_dpg(ltedpeg__prepeg_adt_t ivar_1){
        dpeg__dpeg_grammar_t  result;

        ltedpeg__any_t ivar_2;
        //copying to ltedpeg__any from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__any_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (dpeg__dpeg_grammar_t)ivar_2->dpg;
        result->count++;
        release_ltedpeg__any((ltedpeg__any_t)ivar_2);
        
        
        return result;
}

ltedpeg__terminal_t update_ltedpeg__prepeg_adt_a(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3){
        ltedpeg__terminal_t  result;

        ltedpeg__terminal_t ivar_2;
        //copying to ltedpeg__terminal from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__terminal_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ltedpeg__terminal_t)update_ltedpeg__terminal_a(ivar_2, ivar_3);
        
        
        return result;
}

uint8_t acc_ltedpeg__prepeg_adt_a(ltedpeg__prepeg_adt_t ivar_1){
        uint8_t  result;

        ltedpeg__terminal_t ivar_2;
        //copying to ltedpeg__terminal from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__terminal_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (uint8_t)ivar_2->a;
        release_ltedpeg__terminal((ltedpeg__terminal_t)ivar_2);
        
        
        return result;
}

ltedpeg__lte_t update_ltedpeg__prepeg_adt_fst(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3){
        ltedpeg__lte_t  result;

        ltedpeg__lte_t ivar_2;
        //copying to ltedpeg__lte from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__lte_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ltedpeg__lte_t)update_ltedpeg__lte_fst(ivar_2, ivar_3);
        
        
        return result;
}

uint8_t acc_ltedpeg__prepeg_adt_fst(ltedpeg__prepeg_adt_t ivar_1){
        uint8_t  result;

        ltedpeg__lte_t ivar_2;
        //copying to ltedpeg__lte from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__lte_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (uint8_t)ivar_2->fst;
        release_ltedpeg__lte((ltedpeg__lte_t)ivar_2);
        
        
        return result;
}

ltedpeg__lte_t update_ltedpeg__prepeg_adt_lthen(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3){
        ltedpeg__lte_t  result;

        ltedpeg__lte_t ivar_2;
        //copying to ltedpeg__lte from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__lte_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ltedpeg__lte_t)update_ltedpeg__lte_lthen(ivar_2, ivar_3);
        
        
        return result;
}

uint8_t acc_ltedpeg__prepeg_adt_lthen(ltedpeg__prepeg_adt_t ivar_1){
        uint8_t  result;

        ltedpeg__lte_t ivar_2;
        //copying to ltedpeg__lte from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__lte_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (uint8_t)ivar_2->lthen;
        release_ltedpeg__lte((ltedpeg__lte_t)ivar_2);
        
        
        return result;
}

ltedpeg__lte_t update_ltedpeg__prepeg_adt_lelse(ltedpeg__prepeg_adt_t ivar_1, uint8_t ivar_3){
        ltedpeg__lte_t  result;

        ltedpeg__lte_t ivar_2;
        //copying to ltedpeg__lte from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__lte_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (ltedpeg__lte_t)update_ltedpeg__lte_lelse(ivar_2, ivar_3);
        
        
        return result;
}

uint8_t acc_ltedpeg__prepeg_adt_lelse(ltedpeg__prepeg_adt_t ivar_1){
        uint8_t  result;

        ltedpeg__lte_t ivar_2;
        //copying to ltedpeg__lte from ltedpeg__prepeg_adt;
        ivar_2 = (ltedpeg__lte_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
        result = (uint8_t)ivar_2->lelse;
        release_ltedpeg__lte((ltedpeg__lte_t)ivar_2);
        
        
        return result;
}

ltedpeg__prepeg_adt_t con_ltedpeg__epsilon(void){
        ltedpeg__prepeg_adt_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        uint8_t ivar_1;
        ivar_1 = (uint8_t)0;
        ltedpeg__prepeg_adt_t tmp33349 = new_ltedpeg__prepeg_adt();;
        result = (ltedpeg__prepeg_adt_t)tmp33349;
        tmp33349->ltedpeg__prepeg_adt_index = (uint8_t)ivar_1;
        defined = true;};
        
        
        return result;
}

ltedpeg__prepeg_adt_t con_ltedpeg__failure(void){
        ltedpeg__prepeg_adt_t  static  result;

        static bool_t defined = false;
        if (!defined){
            
        uint8_t ivar_1;
        ivar_1 = (uint8_t)1;
        ltedpeg__prepeg_adt_t tmp33350 = new_ltedpeg__prepeg_adt();;
        result = (ltedpeg__prepeg_adt_t)tmp33350;
        tmp33350->ltedpeg__prepeg_adt_index = (uint8_t)ivar_1;
        defined = true;};
        
        
        return result;
}

ltedpeg__prepeg_adt_t con_ltedpeg__any(dpeg__dpeg_grammar_t ivar_2){
        ltedpeg__prepeg_adt_t  result;

        uint8_t ivar_1;
        ivar_1 = (uint8_t)2;
        ltedpeg__any_t tmp33351 = new_ltedpeg__any();;
        result = (ltedpeg__prepeg_adt_t)tmp33351;
        tmp33351->ltedpeg__prepeg_adt_index = (uint8_t)ivar_1;
        tmp33351->dpg = (dpeg__dpeg_grammar_t)ivar_2;
        
        
        return result;
}

ltedpeg__prepeg_adt_t con_ltedpeg__terminal(uint8_t ivar_2){
        ltedpeg__prepeg_adt_t  result;

        uint8_t ivar_1;
        ivar_1 = (uint8_t)3;
        ltedpeg__terminal_t tmp33352 = new_ltedpeg__terminal();;
        result = (ltedpeg__prepeg_adt_t)tmp33352;
        tmp33352->ltedpeg__prepeg_adt_index = (uint8_t)ivar_1;
        tmp33352->a = (uint8_t)ivar_2;
        
        
        return result;
}

ltedpeg__prepeg_adt_t con_ltedpeg__lte(uint8_t ivar_2, uint8_t ivar_3, uint8_t ivar_4){
        ltedpeg__prepeg_adt_t  result;

        uint8_t ivar_1;
        ivar_1 = (uint8_t)4;
        ltedpeg__lte_t tmp33353 = new_ltedpeg__lte();;
        result = (ltedpeg__prepeg_adt_t)tmp33353;
        tmp33353->ltedpeg__prepeg_adt_index = (uint8_t)ivar_1;
        tmp33353->fst = (uint8_t)ivar_2;
        tmp33353->lthen = (uint8_t)ivar_3;
        tmp33353->lelse = (uint8_t)ivar_4;
        
        
        return result;
}

uint8_t ltedpeg__ord_2(ltedpeg__prepeg_adt_t ivar_1){
        uint8_t  result;

        bool_t ivar_3;
        ivar_1->count++;
        ivar_3 = (bool_t)rec_ltedpeg__epsilonp((ltedpeg__prepeg_adt_t)ivar_1);
        if (ivar_3){
             release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
             result = (uint8_t)0;
        } else {
             bool_t ivar_7;
             ivar_1->count++;
             ivar_7 = (bool_t)rec_ltedpeg__failurep((ltedpeg__prepeg_adt_t)ivar_1);
             if (ivar_7){
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
           result = (uint8_t)1;
             } else {
           bool_t ivar_15;
           ivar_1->count++;
           ivar_15 = (bool_t)rec_ltedpeg__anyp((ltedpeg__prepeg_adt_t)ivar_1);
           if (ivar_15){
           release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_1);
           result = (uint8_t)2;
           } else {
           bool_t ivar_23;
           ivar_23 = (bool_t)rec_ltedpeg__terminalp((ltedpeg__prepeg_adt_t)ivar_1);
           if (ivar_23){
            result = (uint8_t)3;
           } else {
            result = (uint8_t)4;};};};};
        
        
        return result;
}

bool_t ltedpeg__subterm_2(ltedpeg__prepeg_adt_t ivar_1, ltedpeg__prepeg_adt_t ivar_2){
        bool_t  result;

        result = (bool_t) equal_ltedpeg__prepeg_adt(ivar_1, ivar_2);
        
        
        return result;
}

bool_t ltedpeg__doublelessp_2(ltedpeg__prepeg_adt_t ivar_1, ltedpeg__prepeg_adt_t ivar_2){
        bool_t  result;

        result = (bool_t) false;
        
        
        return result;
}

ltedpeg_funtype_32_t ltedpeg__reduce_nat_2(mpz_ptr_t ivar_1, mpz_ptr_t ivar_2, ltedpeg_funtype_33_t ivar_3, ltedpeg_funtype_34_t ivar_5, ltedpeg_funtype_36_t ivar_7){
        ltedpeg_funtype_32_t  result;

        ltedpeg_closure_37_t cl33368;
        cl33368 = new_ltedpeg_closure_37();
        mpz_set(cl33368->fvar_1, ivar_1);
        cl33368->fvar_2 = (ltedpeg_funtype_33_t)ivar_3;
        if (cl33368->fvar_2 != NULL) cl33368->fvar_2->count++;
        cl33368->fvar_3 = (ltedpeg_funtype_34_t)ivar_5;
        if (cl33368->fvar_3 != NULL) cl33368->fvar_3->count++;
        cl33368->fvar_4 = (ltedpeg_funtype_36_t)ivar_7;
        if (cl33368->fvar_4 != NULL) cl33368->fvar_4->count++;
        mpz_set(cl33368->fvar_5, ivar_2);
        mpz_clear(ivar_1);
        release_ltedpeg_funtype_33((ltedpeg_funtype_33_t)ivar_3);
        release_ltedpeg_funtype_34((ltedpeg_funtype_34_t)ivar_5);
        release_ltedpeg_funtype_36((ltedpeg_funtype_36_t)ivar_7);
        mpz_clear(ivar_2);
        result = (ltedpeg_funtype_32_t)cl33368;
        
        
        return result;
}

ltedpeg_funtype_32_t ltedpeg__REDUCE_nat_2(ltedpeg_funtype_32_t ivar_1, ltedpeg_funtype_32_t ivar_3, ltedpeg_funtype_39_t ivar_5, ltedpeg_funtype_41_t ivar_7, ltedpeg_funtype_43_t ivar_9){
        ltedpeg_funtype_32_t  result;

        ltedpeg_closure_44_t cl33402;
        cl33402 = new_ltedpeg_closure_44();
        cl33402->fvar_1 = (ltedpeg_funtype_32_t)ivar_1;
        if (cl33402->fvar_1 != NULL) cl33402->fvar_1->count++;
        cl33402->fvar_2 = (ltedpeg_funtype_39_t)ivar_5;
        if (cl33402->fvar_2 != NULL) cl33402->fvar_2->count++;
        cl33402->fvar_3 = (ltedpeg_funtype_41_t)ivar_7;
        if (cl33402->fvar_3 != NULL) cl33402->fvar_3->count++;
        cl33402->fvar_4 = (ltedpeg_funtype_43_t)ivar_9;
        if (cl33402->fvar_4 != NULL) cl33402->fvar_4->count++;
        cl33402->fvar_5 = (ltedpeg_funtype_32_t)ivar_3;
        if (cl33402->fvar_5 != NULL) cl33402->fvar_5->count++;
        release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)ivar_1);
        release_ltedpeg_funtype_39((ltedpeg_funtype_39_t)ivar_5);
        release_ltedpeg_funtype_41((ltedpeg_funtype_41_t)ivar_7);
        release_ltedpeg_funtype_43((ltedpeg_funtype_43_t)ivar_9);
        release_ltedpeg_funtype_32((ltedpeg_funtype_32_t)ivar_3);
        result = (ltedpeg_funtype_32_t)cl33402;
        
        
        return result;
}

ltedpeg_funtype_45_t ltedpeg__reduce_ordinal_2(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2, ltedpeg_funtype_46_t ivar_3, ltedpeg_funtype_47_t ivar_5, ltedpeg_funtype_48_t ivar_7){
        ltedpeg_funtype_45_t  result;

        ltedpeg_closure_49_t cl33416;
        cl33416 = new_ltedpeg_closure_49();
        cl33416->fvar_1 = (ordstruct_adt__ordstruct_adt_t)ivar_1;
        if (cl33416->fvar_1 != NULL) cl33416->fvar_1->count++;
        cl33416->fvar_2 = (ltedpeg_funtype_46_t)ivar_3;
        if (cl33416->fvar_2 != NULL) cl33416->fvar_2->count++;
        cl33416->fvar_3 = (ltedpeg_funtype_47_t)ivar_5;
        if (cl33416->fvar_3 != NULL) cl33416->fvar_3->count++;
        cl33416->fvar_4 = (ltedpeg_funtype_48_t)ivar_7;
        if (cl33416->fvar_4 != NULL) cl33416->fvar_4->count++;
        cl33416->fvar_5 = (ordstruct_adt__ordstruct_adt_t)ivar_2;
        if (cl33416->fvar_5 != NULL) cl33416->fvar_5->count++;
        release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)ivar_1);
        release_ltedpeg_funtype_46((ltedpeg_funtype_46_t)ivar_3);
        release_ltedpeg_funtype_47((ltedpeg_funtype_47_t)ivar_5);
        release_ltedpeg_funtype_48((ltedpeg_funtype_48_t)ivar_7);
        release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)ivar_2);
        result = (ltedpeg_funtype_45_t)cl33416;
        
        
        return result;
}

ltedpeg_funtype_45_t ltedpeg__REDUCE_ordinal_2(ltedpeg_funtype_45_t ivar_1, ltedpeg_funtype_45_t ivar_3, ltedpeg_funtype_50_t ivar_5, ltedpeg_funtype_51_t ivar_7, ltedpeg_funtype_52_t ivar_9){
        ltedpeg_funtype_45_t  result;

        ltedpeg_closure_53_t cl33450;
        cl33450 = new_ltedpeg_closure_53();
        cl33450->fvar_1 = (ltedpeg_funtype_45_t)ivar_1;
        if (cl33450->fvar_1 != NULL) cl33450->fvar_1->count++;
        cl33450->fvar_2 = (ltedpeg_funtype_50_t)ivar_5;
        if (cl33450->fvar_2 != NULL) cl33450->fvar_2->count++;
        cl33450->fvar_3 = (ltedpeg_funtype_51_t)ivar_7;
        if (cl33450->fvar_3 != NULL) cl33450->fvar_3->count++;
        cl33450->fvar_4 = (ltedpeg_funtype_52_t)ivar_9;
        if (cl33450->fvar_4 != NULL) cl33450->fvar_4->count++;
        cl33450->fvar_5 = (ltedpeg_funtype_45_t)ivar_3;
        if (cl33450->fvar_5 != NULL) cl33450->fvar_5->count++;
        release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)ivar_1);
        release_ltedpeg_funtype_50((ltedpeg_funtype_50_t)ivar_5);
        release_ltedpeg_funtype_51((ltedpeg_funtype_51_t)ivar_7);
        release_ltedpeg_funtype_52((ltedpeg_funtype_52_t)ivar_9);
        release_ltedpeg_funtype_45((ltedpeg_funtype_45_t)ivar_3);
        result = (ltedpeg_funtype_45_t)cl33450;
        
        
        return result;
}

ltedpeg_funtype_54_t ltedpeg__good_good_entryp(uint32_t ivar_1, uint32_t ivar_2){
        ltedpeg_funtype_54_t  result;

        ltedpeg_closure_55_t cl33451;
        cl33451 = new_ltedpeg_closure_55();
        cl33451->fvar_1 = (uint32_t)ivar_1;
        cl33451->fvar_2 = (uint32_t)ivar_2;
        result = (ltedpeg_funtype_54_t)cl33451;
        
        
        return result;
}

ltedpeg_funtype_54_t ltedpeg__good_push_entryp(uint32_t ivar_1){
        ltedpeg_funtype_54_t  result;

        ltedpeg_closure_56_t cl33452;
        cl33452 = new_ltedpeg_closure_56();
        cl33452->fvar_1 = (uint32_t)ivar_1;
        result = (ltedpeg_funtype_54_t)cl33452;
        
        
        return result;
}

ltedpeg_funtype_54_t ltedpeg__fine_push_entryp(uint32_t ivar_1){
        ltedpeg_funtype_54_t  result;

        ltedpeg_closure_57_t cl33453;
        cl33453 = new_ltedpeg_closure_57();
        cl33453->fvar_1 = (uint32_t)ivar_1;
        result = (ltedpeg_funtype_54_t)cl33453;
        
        
        return result;
}

ltedpeg_funtype_54_t ltedpeg__nice_entryp(uint32_t ivar_1, uint32_t ivar_2){
        ltedpeg_funtype_54_t  result;

        ltedpeg_closure_58_t cl33454;
        cl33454 = new_ltedpeg_closure_58();
        cl33454->fvar_1 = (uint32_t)ivar_1;
        cl33454->fvar_2 = (uint32_t)ivar_2;
        result = (ltedpeg_funtype_54_t)cl33454;
        
        
        return result;
}

bool_t ltedpeg__loop_or_pushp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        ivar_1->count++;
        ivar_2 = (bool_t)rec_ltedpeg__loopp((ltedpeg__ent_adt_t)ivar_1);
        if (ivar_2){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (bool_t) true;
        } else {
             result = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_1);};
        
        
        return result;
}

ltedpeg_funtype_62_t ltedpeg__instack(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2){
        ltedpeg_funtype_62_t  result;

        ltedpeg_closure_63_t cl33459;
        cl33459 = new_ltedpeg_closure_63();
        cl33459->fvar_1 = (ltedpeg__scaffold_t)ivar_2;
        if (cl33459->fvar_1 != NULL) cl33459->fvar_1->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_2);
        result = (ltedpeg_funtype_62_t)cl33459;
        
        
        return result;
}

ltedpeg_funtype_65_t ltedpeg__successor(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_3){
        ltedpeg_funtype_65_t  result;

        ltedpeg_closure_66_t cl33465;
        cl33465 = new_ltedpeg_closure_66();
        cl33465->fvar_1 = (ltedpeg__lang_spec_t)ivar_2;
        if (cl33465->fvar_1 != NULL) cl33465->fvar_1->count++;
        cl33465->fvar_2 = (ltedpeg__scaffold_t)ivar_3;
        if (cl33465->fvar_2 != NULL) cl33465->fvar_2->count++;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_2);
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_3);
        result = (ltedpeg_funtype_65_t)cl33465;
        
        
        return result;
}

ltedpeg_funtype_67_t ltedpeg__sigma(uint32_t ivar_1, ltedpeg_array_68_t ivar_2){
        ltedpeg_funtype_67_t  result;

        ltedpeg_closure_69_t cl33466;
        cl33466 = new_ltedpeg_closure_69();
        cl33466->fvar_1 = (ltedpeg_array_68_t)ivar_2;
        if (cl33466->fvar_1 != NULL) cl33466->fvar_1->count++;
        cl33466->fvar_2 = (uint32_t)ivar_1;
        release_ltedpeg_array_68((ltedpeg_array_68_t)ivar_2);
        result = (ltedpeg_funtype_67_t)cl33466;
        
        
        return result;
}

uint64_t ltedpeg__scafcount(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2, ltedpeg_funtype_54_t ivar_4, uint32_t ivar_6){
        uint64_t  result;

        type_actual_t ivar_37;
        ivar_37 = (type_actual_t)actual_ltedpeg__ent_adt();
        ltedpeg_funtype_67_t ivar_10;
        ltedpeg_funtype_70_t ivar_49;
        ltedpeg_closure_71_t cl33467;
        cl33467 = new_ltedpeg_closure_71();
        cl33467->fvar_1 = (ltedpeg__scaffold_t)ivar_2;
        if (cl33467->fvar_1 != NULL) cl33467->fvar_1->count++;
        cl33467->fvar_2 = (type_actual_t)ivar_37;
        cl33467->fvar_3 = (ltedpeg_funtype_54_t)ivar_4;
        if (cl33467->fvar_3 != NULL) cl33467->fvar_3->count++;
        release_ltedpeg_funtype_54((ltedpeg_funtype_54_t)ivar_4);
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_2);
        ivar_49 = (ltedpeg_funtype_70_t)cl33467;
        ltedpeg_array_68_t ivar_47;
        //copying to ltedpeg_array_68 from ltedpeg_funtype_70;
        uint32_t tmp33468;
        //copying to uint32 from uint32;
        tmp33468 = (uint32_t)ivar_1;
        tmp33468 += 1;
        ivar_47 = new_ltedpeg_array_68(tmp33468);
        for (uint32_t index_51 = 0; index_51 < tmp33468; index_51++){
             ivar_47->elems[index_51] = (mpz_ptr_t)safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_47->elems[index_51]);
             mpz_mk_set_ui(ivar_47->elems[index_51], ivar_49->ftbl->fptr(ivar_49, index_51));
        };
        release_ltedpeg_funtype_70((ltedpeg_funtype_70_t)ivar_49);
        ivar_10 = (ltedpeg_funtype_67_t)ltedpeg__sigma((uint32_t)ivar_1, (ltedpeg_array_68_t)ivar_47);
        result = (uint64_t)mpz_get_ui(ivar_10->ftbl->fptr(ivar_10, ivar_6));
        
        
        return result;
}

uint64_t ltedpeg__pushcount(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2){
        uint64_t  result;

        ltedpeg_funtype_54_t ivar_15;
        ltedpeg_closure_75_t cl33469;
        cl33469 = new_ltedpeg_closure_75();
        ivar_15 = (ltedpeg_funtype_54_t)cl33469;
        result = (uint64_t)ltedpeg__scafcount((uint32_t)ivar_1, (ltedpeg__scaffold_t)ivar_2, (ltedpeg_funtype_54_t)ivar_15, (uint32_t)ivar_1);
        
        
        return result;
}

bool_t ltedpeg__good_or_failp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        ivar_1->count++;
        ivar_2 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_1);
        if (ivar_2){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (bool_t) true;
        } else {
             result = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_1);};
        
        
        return result;
}

uint64_t ltedpeg__gfcount(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2){
        uint64_t  result;

        ltedpeg_funtype_54_t ivar_16;
        ltedpeg_closure_76_t cl33470;
        cl33470 = new_ltedpeg_closure_76();
        ivar_16 = (ltedpeg_funtype_54_t)cl33470;
        result = (uint64_t)ltedpeg__scafcount((uint32_t)ivar_1, (ltedpeg__scaffold_t)ivar_2, (ltedpeg_funtype_54_t)ivar_16, (uint32_t)ivar_1);
        
        
        return result;
}

ltedpeg_funtype_77_t ltedpeg__good_depthp(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2){
        ltedpeg_funtype_77_t  result;

        ltedpeg_closure_78_t cl33471;
        cl33471 = new_ltedpeg_closure_78();
        cl33471->fvar_1 = (uint32_t)ivar_1;
        cl33471->fvar_2 = (ltedpeg__scaffold_t)ivar_2;
        if (cl33471->fvar_2 != NULL) cl33471->fvar_2->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_2);
        result = (ltedpeg_funtype_77_t)cl33471;
        
        
        return result;
}

ltedpeg_funtype_54_t ltedpeg__good_stackp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, uint64_t ivar_3, ltedpeg__scaffold_t ivar_4){
        ltedpeg_funtype_54_t  result;

        ltedpeg_closure_79_t cl33476;
        cl33476 = new_ltedpeg_closure_79();
        cl33476->fvar_1 = (uint64_t)ivar_3;
        cl33476->fvar_2 = (uint32_t)ivar_1;
        cl33476->fvar_3 = (ltedpeg__lang_spec_t)ivar_2;
        if (cl33476->fvar_3 != NULL) cl33476->fvar_3->count++;
        cl33476->fvar_4 = (ltedpeg__scaffold_t)ivar_4;
        if (cl33476->fvar_4 != NULL) cl33476->fvar_4->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_4);
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_2);
        result = (ltedpeg_funtype_54_t)cl33476;
        
        
        return result;
}

ltedpeg_funtype_65_t ltedpeg__mem_stackp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, uint64_t ivar_3, ltedpeg__scaffold_t ivar_4){
        ltedpeg_funtype_65_t  result;

        ltedpeg_closure_80_t cl33485;
        cl33485 = new_ltedpeg_closure_80();
        cl33485->fvar_1 = (ltedpeg__scaffold_t)ivar_4;
        if (cl33485->fvar_1 != NULL) cl33485->fvar_1->count++;
        cl33485->fvar_2 = (ltedpeg__lang_spec_t)ivar_2;
        if (cl33485->fvar_2 != NULL) cl33485->fvar_2->count++;
        cl33485->fvar_3 = (uint32_t)ivar_1;
        cl33485->fvar_4 = (uint64_t)ivar_3;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_4);
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_2);
        result = (ltedpeg_funtype_65_t)cl33485;
        
        
        return result;
}

bool_t ltedpeg__push_or_pendingp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        bool_t ivar_2;
        ivar_1->count++;
        ivar_2 = (bool_t)rec_ltedpeg__pushp((ltedpeg__ent_adt_t)ivar_1);
        if (ivar_2){
             release_ltedpeg__ent_adt((ltedpeg__ent_adt_t)ivar_1);
             result = (bool_t) true;
        } else {
             result = (bool_t)rec_ltedpeg__pendingp((ltedpeg__ent_adt_t)ivar_1);};
        
        
        return result;
}

ltedpeg_funtype_54_t ltedpeg__fine_stackp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, uint64_t ivar_3, ltedpeg__scaffold_t ivar_4){
        ltedpeg_funtype_54_t  result;

        ltedpeg_closure_81_t cl33490;
        cl33490 = new_ltedpeg_closure_81();
        cl33490->fvar_1 = (ltedpeg__scaffold_t)ivar_4;
        if (cl33490->fvar_1 != NULL) cl33490->fvar_1->count++;
        cl33490->fvar_2 = (ltedpeg__lang_spec_t)ivar_2;
        if (cl33490->fvar_2 != NULL) cl33490->fvar_2->count++;
        cl33490->fvar_3 = (uint32_t)ivar_1;
        cl33490->fvar_4 = (uint64_t)ivar_3;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_2);
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_4);
        result = (ltedpeg_funtype_54_t)cl33490;
        
        
        return result;
}

bool_t ltedpeg__loop_readyp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2, ltedpeg__scaffold_t ivar_3, uint32_t ivar_5, uint8_t ivar_6){
        bool_t  result;

        ltedpeg__prepeg_adt_t ivar_7;
        ivar_7 = (ltedpeg__prepeg_adt_t)ivar_2->elems[ivar_6];
        ivar_7->count++;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_2);
        bool_t ivar_117;
        ivar_7->count++;
        ivar_117 = (bool_t)rec_ltedpeg__ltep((ltedpeg__prepeg_adt_t)ivar_7);
        if (ivar_117){
             uint8_t ivar_12;
             ivar_7->count++;
             ivar_12 = (uint8_t)acc_ltedpeg__prepeg_adt_fst((ltedpeg__prepeg_adt_t)ivar_7);
             uint8_t ivar_13;
             ivar_7->count++;
             ivar_13 = (uint8_t)acc_ltedpeg__prepeg_adt_lthen((ltedpeg__prepeg_adt_t)ivar_7);
             uint8_t ivar_14;
             ivar_14 = (uint8_t)acc_ltedpeg__prepeg_adt_lelse((ltedpeg__prepeg_adt_t)ivar_7);
             bool_t ivar_24;
             ltedpeg__ent_adt_t ivar_38;
             ltedpeg_array_59_t ivar_29;
             ltedpeg_array_59_t ivar_31;
             ivar_31 = (ltedpeg_array_59_t)ivar_3->elems[ivar_5];
             ivar_31->count++;
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_29 = (ltedpeg_array_59_t)ivar_31;
             if (ivar_29 != NULL) ivar_29->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_31);
             ivar_38 = (ltedpeg__ent_adt_t)ivar_29->elems[ivar_12];
             ivar_38->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_29);
             ivar_24 = (bool_t)ltedpeg__loop_or_pushp((ltedpeg__ent_adt_t)ivar_38);
             if (ivar_24){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_3);
           result = (bool_t) true;
             } else {
           bool_t ivar_39;
           bool_t ivar_41;
           ltedpeg__ent_adt_t ivar_55;
           ltedpeg_array_59_t ivar_46;
           ltedpeg_array_59_t ivar_48;
           ivar_48 = (ltedpeg_array_59_t)ivar_3->elems[ivar_5];
           ivar_48->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_46 = (ltedpeg_array_59_t)ivar_48;
           if (ivar_46 != NULL) ivar_46->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_48);
           ivar_55 = (ltedpeg__ent_adt_t)ivar_46->elems[ivar_12];
           ivar_55->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_46);
           ivar_41 = (bool_t)rec_ltedpeg__goodp((ltedpeg__ent_adt_t)ivar_55);
           if (ivar_41){
           ltedpeg__ent_adt_t ivar_84;
           ltedpeg_array_59_t ivar_59;
           uint32_t ivar_81;
           uint32_t ivar_62;
           ltedpeg__ent_adt_t ivar_75;
           ltedpeg_array_59_t ivar_66;
           ltedpeg_array_59_t ivar_68;
           ivar_68 = (ltedpeg_array_59_t)ivar_3->elems[ivar_5];
           ivar_68->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_66 = (ltedpeg_array_59_t)ivar_68;
           if (ivar_66 != NULL) ivar_66->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_68);
           ivar_75 = (ltedpeg__ent_adt_t)ivar_66->elems[ivar_12];
           ivar_75->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_66);
           ivar_62 = (uint32_t)acc_ltedpeg__ent_adt_span((ltedpeg__ent_adt_t)ivar_75);
           ivar_81 = (uint32_t)(ivar_5 + ivar_62);
           ltedpeg_array_59_t ivar_77;
           ivar_77 = (ltedpeg_array_59_t)ivar_3->elems[ivar_81];
           ivar_77->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_59 = (ltedpeg_array_59_t)ivar_77;
           if (ivar_59 != NULL) ivar_59->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_77);
           ivar_84 = (ltedpeg__ent_adt_t)ivar_59->elems[ivar_13];
           ivar_84->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_59);
           ivar_39 = (bool_t)ltedpeg__loop_or_pushp((ltedpeg__ent_adt_t)ivar_84);
           } else {
           ivar_39 = (bool_t) false;};
           if (ivar_39){
           release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_3);
           result = (bool_t) true;
           } else {
           bool_t ivar_86;
           ltedpeg__ent_adt_t ivar_100;
           ltedpeg_array_59_t ivar_91;
           ltedpeg_array_59_t ivar_93;
           ivar_93 = (ltedpeg_array_59_t)ivar_3->elems[ivar_5];
           ivar_93->count++;
           //copying to ltedpeg_array_59 from ltedpeg_array_59;
           ivar_91 = (ltedpeg_array_59_t)ivar_93;
           if (ivar_91 != NULL) ivar_91->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_93);
           ivar_100 = (ltedpeg__ent_adt_t)ivar_91->elems[ivar_12];
           ivar_100->count++;
           release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_91);
           ivar_86 = (bool_t)rec_ltedpeg__failp((ltedpeg__ent_adt_t)ivar_100);
           if (ivar_86){
            ltedpeg__ent_adt_t ivar_113;
            ltedpeg_array_59_t ivar_104;
            ltedpeg_array_59_t ivar_106;
            ivar_106 = (ltedpeg_array_59_t)ivar_3->elems[ivar_5];
            ivar_106->count++;
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_3);
            //copying to ltedpeg_array_59 from ltedpeg_array_59;
            ivar_104 = (ltedpeg_array_59_t)ivar_106;
            if (ivar_104 != NULL) ivar_104->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_106);
            ivar_113 = (ltedpeg__ent_adt_t)ivar_104->elems[ivar_14];
            ivar_113->count++;
            release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_104);
            result = (bool_t)ltedpeg__loop_or_pushp((ltedpeg__ent_adt_t)ivar_113);
           } else {
            release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_3);
            result = (bool_t) false;};};};
        } else {
             release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_3);
             release_ltedpeg__prepeg_adt((ltedpeg__prepeg_adt_t)ivar_7);
             result = (bool_t) false;};
        
        
        return result;
}

ltedpeg_funtype_83_t ltedpeg__good_failp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2){
        ltedpeg_funtype_83_t  result;

        ltedpeg_closure_84_t cl33503;
        cl33503 = new_ltedpeg_closure_84();
        cl33503->fvar_1 = (ltedpeg__lang_spec_t)ivar_1;
        if (cl33503->fvar_1 != NULL) cl33503->fvar_1->count++;
        cl33503->fvar_2 = (bytestrings__bytestring_t)ivar_2;
        if (cl33503->fvar_2 != NULL) cl33503->fvar_2->count++;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_1);
        release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
        result = (ltedpeg_funtype_83_t)cl33503;
        
        
        return result;
}

ltedpeg_funtype_86_t ltedpeg__good_loopp(uint32_t ivar_1, ltedpeg__lang_spec_t ivar_2){
        ltedpeg_funtype_86_t  result;

        ltedpeg_closure_87_t cl33511;
        cl33511 = new_ltedpeg_closure_87();
        cl33511->fvar_1 = (ltedpeg__lang_spec_t)ivar_2;
        if (cl33511->fvar_1 != NULL) cl33511->fvar_1->count++;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_2);
        result = (ltedpeg_funtype_86_t)cl33511;
        
        
        return result;
}

ltedpeg_funtype_89_t ltedpeg__good_goodp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2){
        ltedpeg_funtype_89_t  result;

        ltedpeg_closure_90_t cl33528;
        cl33528 = new_ltedpeg_closure_90();
        cl33528->fvar_1 = (ltedpeg__lang_spec_t)ivar_1;
        if (cl33528->fvar_1 != NULL) cl33528->fvar_1->count++;
        cl33528->fvar_2 = (bytestrings__bytestring_t)ivar_2;
        if (cl33528->fvar_2 != NULL) cl33528->fvar_2->count++;
        release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_1);
        result = (ltedpeg_funtype_89_t)cl33528;
        
        
        return result;
}

ltedpeg_funtype_92_t ltedpeg__good_entryp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2){
        ltedpeg_funtype_92_t  result;

        ltedpeg_closure_93_t cl33556;
        cl33556 = new_ltedpeg_closure_93();
        cl33556->fvar_1 = (bytestrings__bytestring_t)ivar_2;
        if (cl33556->fvar_1 != NULL) cl33556->fvar_1->count++;
        cl33556->fvar_2 = (ltedpeg__lang_spec_t)ivar_1;
        if (cl33556->fvar_2 != NULL) cl33556->fvar_2->count++;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_1);
        release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
        result = (ltedpeg_funtype_92_t)cl33556;
        
        
        return result;
}

ltedpeg_funtype_92_t ltedpeg__fine_entryp(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2){
        ltedpeg_funtype_92_t  result;

        ltedpeg_closure_94_t cl33584;
        cl33584 = new_ltedpeg_closure_94();
        cl33584->fvar_1 = (bytestrings__bytestring_t)ivar_2;
        if (cl33584->fvar_1 != NULL) cl33584->fvar_1->count++;
        cl33584->fvar_2 = (ltedpeg__lang_spec_t)ivar_1;
        if (cl33584->fvar_2 != NULL) cl33584->fvar_2->count++;
        release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_1);
        result = (ltedpeg_funtype_92_t)cl33584;
        
        
        return result;
}

ltedpeg_funtype_62_t ltedpeg__good_rootp(uint32_t ivar_1, ltedpeg__scaffold_t ivar_2){
        ltedpeg_funtype_62_t  result;

        ltedpeg_closure_95_t cl33597;
        cl33597 = new_ltedpeg_closure_95();
        cl33597->fvar_1 = (ltedpeg__scaffold_t)ivar_2;
        if (cl33597->fvar_1 != NULL) cl33597->fvar_1->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_2);
        result = (ltedpeg_funtype_62_t)cl33597;
        
        
        return result;
}

bool_t ltedpeg__emptyp(ltedpeg__ent_adt_t ivar_1){
        bool_t  result;

        uint8_t ivar_2;
        ivar_2 = (uint8_t)acc_ltedpeg__ent_adt_nt((ltedpeg__ent_adt_t)ivar_1);
        uint8_t ivar_3;
        ivar_3 = (uint8_t)ltedpeg__num_non_terminals();
        result = (ivar_2 == ivar_3);
        
        
        return result;
}

ltedpeg_funtype_97_t ltedpeg__step(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3, uint8_t ivar_5){
        ltedpeg_funtype_97_t  result;

        ltedpeg_closure_98_t cl33780;
        cl33780 = new_ltedpeg_closure_98();
        cl33780->fvar_1 = (bytestrings__bytestring_t)ivar_2;
        if (cl33780->fvar_1 != NULL) cl33780->fvar_1->count++;
        cl33780->fvar_2 = (ltedpeg__lang_spec_t)ivar_1;
        if (cl33780->fvar_2 != NULL) cl33780->fvar_2->count++;
        release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_1);
        release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
        result = (ltedpeg_funtype_97_t)cl33780;
        
        
        return result;
}

ltedpeg_funtype_99_t ltedpeg__size(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3, uint8_t ivar_5){
        ltedpeg_funtype_99_t  result;

        ltedpeg_closure_100_t cl33802;
        cl33802 = new_ltedpeg_closure_100();
        cl33802->fvar_1 = (bytestrings__bytestring_t)ivar_2;
        if (cl33802->fvar_1 != NULL) cl33802->fvar_1->count++;
        release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
        result = (ltedpeg_funtype_99_t)cl33802;
        
        
        return result;
}

ltedpeg__state_t ltedpeg__parse(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3, uint8_t ivar_5, ltedpeg__state_t ivar_6){
        ltedpeg__state_t  result;

        bool_t ivar_11;
        uint64_t ivar_12;
        ivar_12 = (uint64_t)ivar_6->depth;
        uint8_t ivar_13;
        ivar_13 = (uint8_t)0;
        ivar_11 = (ivar_12 == ivar_13);
        if (ivar_11){
             release_ltedpeg__lang_spec((ltedpeg__lang_spec_t)ivar_1);
             release_bytestrings__bytestring((bytestrings__bytestring_t)ivar_2);
             //copying to ltedpeg__state from ltedpeg__state;
             result = (ltedpeg__state_t)ivar_6;
             if (result != NULL) result->count++;
             release_ltedpeg__state((ltedpeg__state_t)ivar_6);
        } else {
             ltedpeg__state_t ivar_58;
             ltedpeg_funtype_97_t ivar_33;
             ivar_1->count++;
             ivar_2->count++;
             ivar_33 = (ltedpeg_funtype_97_t)ltedpeg__step((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_3, (uint8_t)ivar_5);
             ivar_58 = (ltedpeg__state_t)ivar_33->ftbl->fptr(ivar_33, ivar_6);
             result = (ltedpeg__state_t)ltedpeg__parse((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_3, (uint8_t)ivar_5, (ltedpeg__state_t)ivar_58);};
        
        
        return result;
}

ltedpeg__ent_adt_t ltedpeg__doparse(ltedpeg__lang_spec_t ivar_1, bytestrings__bytestring_t ivar_2, uint8_t ivar_3){
        ltedpeg__ent_adt_t  result;

        /* pend */ ltedpeg_funtype_102_t ivar_4;
        ltedpeg_closure_103_t cl33875;
        cl33875 = new_ltedpeg_closure_103();
        ivar_4 = (ltedpeg_funtype_102_t)cl33875;
        /* St */ ltedpeg__state_t ivar_8;
        ltedpeg__scaffold_t ivar_44;
        uint32_t ivar_39;
        ivar_39 = (uint32_t)0;
        ltedpeg__ent_adt_t ivar_24;
        uint8_t ivar_31;
        ivar_31 = (uint8_t)0;
        uint32_t ivar_28;
        //copying to uint32 from uint8;
        ivar_28 = (uint32_t)ivar_31;
        uint8_t ivar_29;
        ivar_29 = (uint8_t)ltedpeg__num_non_terminals();
        ivar_24 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_28, (uint8_t)ivar_29);
        ltedpeg__scaffold_t ivar_32;
        uint32_t size33878;
        size33878 = (uint32_t)ivar_2->length;
        size33878 += 1;
        ivar_32 = new_ltedpeg__scaffold(size33878);
        uint32_t ivar_19;
        for (uint32_t index33876 = 0; index33876 < size33878; index33876++){
             ivar_19 = (uint32_t)index33876;
             ltedpeg_array_59_t ivar_21;
             //copying to ltedpeg_array_59 from ltedpeg_funtype_102;
             uint32_t tmp33877;
             tmp33877 = (uint32_t)255;
             ivar_21 = new_ltedpeg_array_59(tmp33877);
             for (uint32_t index_94 = 0; index_94 < tmp33877; index_94++){
           ivar_21->elems[index_94] = (ltedpeg__ent_adt_t)ivar_4->ftbl->fptr(ivar_4, index_94);
           if (ivar_21->elems[index_94] != NULL) ivar_21->elems[index_94]->count++;
             };
             //copying to ltedpeg_array_59 from ltedpeg_array_59;
             ivar_32->elems[index33876] = (ltedpeg_array_59_t)ivar_21;
             if (ivar_32->elems[index33876] != NULL) ivar_32->elems[index33876]->count++;
             release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_21);
        };
        release_ltedpeg_funtype_102((ltedpeg_funtype_102_t)ivar_4);
        ltedpeg__scaffold_t ivar_43;
        ltedpeg_array_59_t ivar_33;
        ivar_33 = (ltedpeg_array_59_t)ivar_32->elems[ivar_39];
        ivar_33->count++;
        ltedpeg__scaffold_t ivar_40;
        ltedpeg_array_59_t ivar_42;
        ivar_42 = NULL;
        ivar_40 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_32, ivar_39, ivar_42);
        if (ivar_42 != NULL) ivar_42->count--;
        ltedpeg_array_59_t ivar_41;
        ltedpeg_array_59_t ivar_36;
        ltedpeg__ent_adt_t ivar_38;
        ivar_38 = NULL;
        ivar_36 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_33, ivar_3, ivar_38);
        if (ivar_38 != NULL) ivar_38->count--;
        ivar_41 = (ltedpeg_array_59_t)update_ltedpeg_array_59(ivar_36, ivar_3, ivar_24);
        if (ivar_24 != NULL) ivar_24->count--;
        ivar_43 = (ltedpeg__scaffold_t)update_ltedpeg__scaffold(ivar_40, ivar_39, ivar_41);
        if (ivar_41 != NULL) ivar_41->count--;
        //copying to ltedpeg__scaffold from ltedpeg__scaffold;
        ivar_44 = (ltedpeg__scaffold_t)ivar_43;
        if (ivar_44 != NULL) ivar_44->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_43);
        uint64_t ivar_47;
        ivar_47 = (uint64_t)1;
        ltedpeg__ent_adt_t ivar_55;
        uint8_t ivar_54;
        ivar_54 = (uint8_t)0;
        uint32_t ivar_51;
        //copying to uint32 from uint8;
        ivar_51 = (uint32_t)ivar_54;
        ivar_55 = (ltedpeg__ent_adt_t)con_ltedpeg__push((uint32_t)ivar_51, (uint8_t)ivar_3);
        bool_t ivar_56;
        ivar_56 = (bool_t) false;
        ltedpeg__state_t tmp33879 = new_ltedpeg__state();;
        ivar_8 = (ltedpeg__state_t)tmp33879;
        tmp33879->scaf = (ltedpeg__scaffold_t)ivar_44;
        tmp33879->depth = (uint64_t)ivar_47;
        tmp33879->stack = (ltedpeg__ent_adt_t)ivar_55;
        tmp33879->lflag = (bool_t)ivar_56;
        ltedpeg_array_59_t ivar_59;
        ltedpeg__scaffold_t ivar_64;
        ltedpeg__state_t ivar_87;
        uint8_t ivar_82;
        ivar_82 = (uint8_t)0;
        uint32_t ivar_75;
        //copying to uint32 from uint8;
        ivar_75 = (uint32_t)ivar_82;
        ivar_87 = (ltedpeg__state_t)ltedpeg__parse((ltedpeg__lang_spec_t)ivar_1, (bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_75, (uint8_t)ivar_3, (ltedpeg__state_t)ivar_8);
        ltedpeg__scaffold_t ivar_91;
        ivar_91 = (ltedpeg__scaffold_t)ivar_87->scaf;
        ivar_91->count++;
        release_ltedpeg__state((ltedpeg__state_t)ivar_87);
        //copying to ltedpeg__scaffold from ltedpeg__scaffold;
        ivar_64 = (ltedpeg__scaffold_t)ivar_91;
        if (ivar_64 != NULL) ivar_64->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_91);
        uint32_t ivar_92;
        ivar_92 = (uint32_t)0;
        ltedpeg_array_59_t ivar_61;
        ivar_61 = (ltedpeg_array_59_t)ivar_64->elems[ivar_92];
        ivar_61->count++;
        release_ltedpeg__scaffold((ltedpeg__scaffold_t)ivar_64);
        //copying to ltedpeg_array_59 from ltedpeg_array_59;
        ivar_59 = (ltedpeg_array_59_t)ivar_61;
        if (ivar_59 != NULL) ivar_59->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_61);
        result = (ltedpeg__ent_adt_t)ivar_59->elems[ivar_3];
        result->count++;
        release_ltedpeg_array_59((ltedpeg_array_59_t)ivar_59);
        
        
        return result;
}
