#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include "preambule.h"

#ifdef CHICKEN
    const elem_type KANAREIKA = 9327645;
    const int N_KANAREEK = 2;
#endif

const elem_type POISON = 5467239;

static void reallocate_memory (Stack_info *stack, const size_t new_len);

error_code_type create_stack (Stack_info *stack, const size_t max_size) {

    if (max_size <= 0)              return UNABLE_TO_CREATE_MAX_SIZE;

    else if (stack == NULL)         return NULL_STACK_POINTER;
    
    else if (stack->data != NULL)   return STACK_ALREADY_INITIALIZED;

    else { 

        stack->n_elements = 0;
        stack->max_size = max_size;
        
#ifdef CHICKEN
        stack->data = (elem_type *)calloc (N_KANAREEK, sizeof(elem_type));
        stack->data[0] = stack->data[1] = stack->kanareika_begin = stack->kanareika_end = KANAREIKA;
        stack->data_len = N_KANAREEK;
#else
        stack->data = (elem_type *)calloc (1, sizeof(elem_type));
        stack->data[0] = POISON;
        stack->data_len = 1;
#endif
#ifdef SAUSAGE
        stack->hash_sizes = hash_func_stack (stack);
        stack->hash_arr = hash_func_arr (stack);
#endif

        return stack_check (stack);
    }
}

#ifdef SAUSAGE
size_t hash_func_stack (const Stack_info *stack) {

#ifdef CHICKEN
    return (stack->n_elements + stack->max_size + stack->data_len + 
        (size_t)stack->data + (size_t)stack->kanareika_begin + (size_t)stack->kanareika_end);
#else
    return (stack->n_elements + stack->max_size + stack->data_len + (size_t)stack->data);
#endif
}

elem_type hash_func_arr (const Stack_info *stack) {

    elem_type return_val = 0;

#ifdef CHICKEN
    size_t i = 1, n = stack->n_elements + 1;
#else
    size_t i = 0, n = stack->n_elements;
#endif

    for (; i < n; i++) {

        return_val += stack->data[i] % 78;
    }

    return return_val;
}
#endif

error_code_type push_back (Stack_info *stack, const elem_type element) {


    error_code_type err = stack_check (stack);
    if (err) return err;

#ifdef CHICKEN
    size_t cur_size = stack->n_elements + N_KANAREEK;
#else
    size_t cur_size = stack->n_elements;
#endif

    if ((stack->n_elements + 1) > stack->max_size)      return STACK_OVERFULL;

    if ((cur_size + 1) > stack->data_len) {

        reallocate_memory (stack, cur_size * 2);  
    }

#ifdef CHICKEN
    (stack->data)[cur_size - 1] = element;
    (stack->data)[cur_size] = KANAREIKA;
#else
    (stack->data)[cur_size] = element;
#endif

    stack->n_elements++;

#ifdef SAUSAGE
    stack->hash_arr = hash_func_arr (stack);
    stack->hash_sizes = hash_func_stack (stack);
#endif

    return stack_check (stack);
}

error_code_type pop (Stack_info *stack, elem_type *element) {

    error_code_type err = stack_check (stack);
    if (err) {

        *element = POISON;
        return err;
    }

#ifdef CHICKEN
    size_t cur_size = stack->n_elements + N_KANAREEK;
#else
    size_t cur_size = stack->n_elements;
#endif

    if (stack->n_elements == 0) {

        *element = POISON;
        return STACK_EMPTY;
    }    

#ifdef CHICKEN
    *element = stack->data[stack->n_elements];        
    stack->data[stack->n_elements] = KANAREIKA;
#else
    *element = stack->data[stack->n_elements - 1];        
#endif

    if (cur_size - 1 < stack->data_len / 2) {

        cur_size = (cur_size > 1) ? cur_size : 2; 
        reallocate_memory (stack, cur_size - 1);
        stack->data_len = cur_size - 1;
    }

    else {

        stack->data[cur_size - 1] = POISON;
    }

    stack->n_elements--;

#ifdef SAUSAGE
    stack->hash_arr = hash_func_arr (stack);
    stack->hash_sizes = hash_func_stack (stack);
#endif
        
    return stack_check (stack);
}

void print_stack (const Stack_info *stack) {

#ifdef CHICKEN
    size_t cur_size = stack->n_elements + N_KANAREEK;
#else
    size_t cur_size = stack->n_elements;
#endif

    for (size_t i = 0; i < cur_size; i++) {

        printf ("%d ", stack->data[i]);
    }

    printf ("\n");
}

static void reallocate_memory (Stack_info *stack, const size_t new_len) {

    stack->data_len = new_len;
    stack->data = (elem_type *)realloc (stack->data, new_len * sizeof (elem_type));

#ifdef CHICKEN
    size_t cur_size = stack->n_elements + N_KANAREEK;
#else
    size_t cur_size = stack->n_elements;
#endif

    for (size_t i = cur_size; i < new_len; i++) {

        stack->data[i] = POISON;
    }
}

void destructor (Stack_info *stack) {

    free (stack->data);
    stack->data = NULL;
}

error_code_type stack_check (const Stack_info *stack) {

    error_code_type flag = CORRECT;

    if (stack == NULL)                                          flag = flag | NULL_STACK_POINTER;

    else {

#ifdef CHICKEN
        if (stack->data[0] != KANAREIKA)                        flag = flag | BEGIN_KANAREIKA_NOT_FOUND;
    
        if (stack->data[stack->n_elements + 1] != KANAREIKA)    flag = flag | END_KANAREIKA_NOT_FOUND;

        if (stack->kanareika_begin != KANAREIKA)                flag = flag | BEGIN_KANAREIKA_NOT_FOUND_IN_STRUCT;
    
        if (stack->kanareika_end != KANAREIKA)                  flag = flag | END_KANAREIKA_NOT_FOUND_IN_STRUCT;
#endif
#ifdef SAUSAGE
        if (stack->hash_sizes != hash_func_stack (stack))       flag = flag | HASH_STRUCT_STACK_MISMATCH;

        if (stack->hash_arr != hash_func_arr (stack))           flag = flag | HASH_DATA_ARRAY_MISMATCH;
#endif
    }

    return flag;
}

void dump (const error_code_type flag) {

    if (flag & NULL_STACK_POINTER)                        printf ("Invalid input pointer for stack *-*\n");

    if (flag & UNABLE_TO_CREATE_MAX_SIZE)                 printf ("Unable to create stack with maximum size <= 0 *-*\n");

    if (flag & STACK_ALREADY_INITIALIZED)                 printf ("Stack is already initialized *-*\n");

    if (flag & STACK_OVERFULL)                            printf ("Stack overfull can not push element *-*\n");

    if (flag & STACK_EMPTY)                               printf ("Stack is empty nothing to pop *-*\n");

#ifdef CHICKEN
    if (flag & BEGIN_KANAREIKA_NOT_FOUND)                 printf ("Kanareika in the beginning of data array is not found. Stack has been spoiled *-*\n");

    if (flag & END_KANAREIKA_NOT_FOUND)                   printf ("Kanareika in the ending of data array is not found. Stack has been spoiled *-*\n");

    if (flag & BEGIN_KANAREIKA_NOT_FOUND_IN_STRUCT)       printf ("Kanareika in the beginning of structure is not found. Stack has been spoiled *-*\n");

    if (flag & END_KANAREIKA_NOT_FOUND_IN_STRUCT)         printf ("Kanareika in the ending of structure is not found. Stack has been spoiled *-*\n");
#endif
#ifdef SAUSAGE
    if (flag & HASH_STRUCT_STACK_MISMATCH)                printf ("Hash function of stack structure does not match the calculated one. Stack has been spoiled *-*\n");

    if (flag & HASH_DATA_ARRAY_MISMATCH)                  printf ("Hash function of data array does not match the calculated one. Stack has been spoiled *-*\n");
#endif
}