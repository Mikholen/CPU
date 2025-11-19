#include <stdio.h>
#include <stdbool.h>
#include "config.h"

typedef enum {

    CORRECT = 0,
    NULL_STACK_POINTER = 1,
#ifdef CHICKEN
    BEGIN_KANAREIKA_NOT_FOUND = 2,
    END_KANAREIKA_NOT_FOUND = 4,
    BEGIN_KANAREIKA_NOT_FOUND_IN_STRUCT = 32,
    END_KANAREIKA_NOT_FOUND_IN_STRUCT = 64,
#endif
#ifdef SAUSAGE
    HASH_STRUCT_STACK_MISMATCH = 8,
    HASH_DATA_ARRAY_MISMATCH = 16,
#endif
    UNABLE_TO_CREATE_MAX_SIZE = 128,
    STACK_ALREADY_INITIALIZED = 256,
    STACK_OVERFULL = 512,
    STACK_EMPTY = 1024
} error_type;

typedef struct Stack_info {

#ifdef CHICKEN
    elem_type kanareika_begin;
#endif
    size_t n_elements;
    size_t max_size;
    size_t data_len;
    elem_type *data;
#ifdef SAUSAGE
    size_t hash_sizes;
    elem_type hash_arr;
#endif
#ifdef CHICKEN
    elem_type kanareika_end;
#endif
} Stack_info;

#ifdef CHICKEN
extern const int N_KANAREEK;
extern const elem_type KANAREIKA;
#endif

extern const elem_type POISON;

error_code_type create_stack (Stack_info *stack, const size_t max_size);
#ifdef SAUSAGE
size_t hash_func_stack (const Stack_info *stack);
elem_type hash_func_arr (const Stack_info *stack);
#endif
error_code_type push_back (Stack_info *stack, const elem_type element);
error_code_type pop (Stack_info *stack, elem_type *element);
void print_stack (const Stack_info *stack);
error_code_type stack_check (const Stack_info *stack);
void dump_stack (error_code_type flag);
void destructor (Stack_info *stack);