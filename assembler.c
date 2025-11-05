#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "assembler.h"
#include "config.h"

void restore_input_info (const char *filename) {

    FILE *f = fopen (filename, "r");    
    
    size_t text_size = 10, num_elements = 0;
    elem_type *output_info = (elem_type *)calloc (text_size, sizeof (elem_type));

    char cmd[6] = {};
    while (fscanf (f, "%5s", cmd) == 1) {

        if (!strcmp (cmd, "push")) {

            elem_type num;
            fscanf (f, "%d", &num);

            if ((num_elements + 3) > text_size) {

                text_size *= 2;
                output_info = (elem_type *)realloc (output_info, text_size * sizeof (elem_type));
            }
            output_info[num_elements] = PUSH;
            num_elements++;
            output_info[num_elements] = num;
        }

        else {

            if ((num_elements + 2) > text_size) {

                text_size *= 2;
                output_info = (elem_type *)realloc (output_info, text_size * sizeof (elem_type));
            }

            output_info[num_elements] = get_cmd_id (cmd);
            if (output_info[num_elements] == 0) {
                printf ("ERROR\n");
                break;
            }
        }

        num_elements++;
    }

    move_array_into_file (output_info, num_elements);
    fclose (f);
    free (output_info);
}

elem_type get_cmd_id (const char *cmd) {

    if      (!strcmp (cmd, "push"))     return PUSH;
    else if (!strcmp (cmd, "pop"))      return POP;
    else if (!strcmp (cmd, "add"))      return ADD;
    else if (!strcmp (cmd, "sub"))      return SUB;
    else if (!strcmp (cmd, "mul"))      return MUL;
    else if (!strcmp (cmd, "div"))      return DIV;
    else if (!strcmp (cmd, "out"))      return OUT;
    // else if (!strcmp (cmd, "in"))       return IN;
    else if (!strcmp (cmd, "sqrt"))     return SQRT;
    else if (!strcmp (cmd, "sin"))      return SIN;
    else if (!strcmp (cmd, "cos"))      return COS;
    else if (!strcmp (cmd, "dump"))     return DUMP;
    else if (!strcmp (cmd, "hlt"))      return HLT;

    return NOT_FOUND;
}

void move_array_into_file (elem_type const *array, size_t const num_elements) {

    FILE *f = fopen ("out.dat", "wb");
    fwrite (array, sizeof (elem_type), num_elements, f);
    fclose(f);
}