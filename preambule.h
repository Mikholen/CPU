#include <stdio.h>
#include "config.h"

typedef enum {

    PUSH = 1,
    POP = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    OUT = 7,
    IN = 8,
    SQRT = 9,
    SIN = 10,
    COS = 11,
    DUMP = 12,
    HLT = 13
} cmd_index;

elem_type get_cmd_id (char *cmd);
void read_input_file (const char *filename, int *array);
size_t get_text_size (const char *filename);
elem_type *read_assemler_output_file (const char *filename);
