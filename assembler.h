#ifndef ASSEMBLER
#define ASSEMBLER

#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "enum.h"

const size_t INIT_TEXT_SIZE = 200;

typedef struct assembler_info {

    FILE *file_input;
    FILE *file_output;
    size_t text_size;
    size_t num_elements;
    elem_type *output_info;
    char cmd[6];
} assembler_info;

void push (assembler_info *assembler_struct);
void other (assembler_info *assembler_struct, cmd_index cmd_id);
void reallocate_memory (assembler_info *assembler_struct);
void restore_input_info (assembler_info *assembler_struct);
void assembler_destructor (assembler_info *assembler_struct);
void assembler_constructor (assembler_info *assembler_struct, const char *filename_input, const char *filename_output);
void dump (assembler_info *assembler_struct, bool sizes, bool cmd, bool array);

#endif