#ifndef CPU
#define CPU

#include "config.h"
#include "enum.h"

typedef struct CPU_info {

    FILE *file;
    bool escape_flag;
    Stack_info *stack;
    size_t position;
    size_t data_len;
    elem_type *data;
} CPU_info;

void dump_CPU (CPU_info *CPU_struct, bool stack, bool data, bool other);
void constructor_CPU (const char *filename, CPU_info *CPU_struct, Stack_info *stack);
void make_all_instructions (CPU_info *CPU_struct);
void destructor_CPU (CPU_info *CPU_struct);

#endif