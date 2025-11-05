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
    HLT = 13,
    NOT_FOUND = 0
} cmd_index;

elem_type get_cmd_id (const char *cmd);
void restore_input_info (const char *filename);
void move_array_into_file (elem_type const *array, size_t const num_elements);
