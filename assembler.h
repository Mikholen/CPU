#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "enum.h"

const size_t INIT_TEXT_SIZE = 10;

typedef struct assembler_info {

    FILE *file;
    size_t text_size;
    size_t num_elements;
    elem_type *output_info;
    char cmd[6];
} assembler_info;

void push (assembler_info *assembler_struct);
void other (assembler_info *assembler_struct, int cmd_id);
void reallocate_memory (assembler_info *assembler_struct);
void restore_input_info (assembler_info *assembler_struct);
void assembler_destructor (assembler_info *assembler_struct);
void assembler_constructor (assembler_info *assembler_struct, char *filename);
void move_array_into_file (elem_type const *array, size_t const num_elements);
void dump (assembler_info *assembler_struct, bool sizes, bool cmd, bool array);
