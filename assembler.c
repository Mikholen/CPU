#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "preambule.h"
#include "config.h"

size_t get_text_size (const char *filename) {

    struct stat text_stat;
    stat (filename, &text_stat);
    return (size_t)text_stat.st_size;
}

void read_input_file (const char *filename, int *array) {

    size_t text_size = get_text_size(filename);

    char *input_info = (char *)calloc (text_size, sizeof (char));
    FILE *f = fopen (filename, "r");
    fread (input_info, sizeof (char), text_size, f);
    fclose (f);
    
    elem_type *output_info = (elem_type *)calloc ((size_t)(text_size / 2), sizeof (elem_type));

    size_t num_elements = 0;

    for (size_t i = 0; i < text_size; i++) {

        if (isdigit (input_info[i])) {

            output_info[num_elements] = input_info[i];
            num_elements++;
        }

        else if (isalpha (input_info[i])) {

           size_t k = 1;
           char cmd[5] = {input_info[i], 0};
           i++;

           while (isalpha (input_info[i])) {

                cmd[k] = input_info[i];
                k++;
                i++;
           }

           output_info[num_elements] = get_cmd_id (cmd);
           num_elements++;
        }
        
    }

    move_array_into_file (array, num_elements);
}

elem_type get_cmd_id (const char *cmd) {

    if      (!strcmp (cmd, "push"))     return PUSH;
    else if (!strcmp (cmd, "pop"))      return POP;
    else if (!strcmp (cmd, "add"))      return ADD;
    else if (!strcmp (cmd, "sub"))      return SUB;
    else if (!strcmp (cmd, "mul"))      return MUL;
    else if (!strcmp (cmd, "div"))      return DIV;
    else if (!strcmp (cmd, "out"))      return OUT;
    else if (!strcmp (cmd, "in"))       return IN;
    else if (!strcmp (cmd, "sqrt"))     return SQRT;
    else if (!strcmp (cmd, "sin"))      return SIN;
    else if (!strcmp (cmd, "cos"))      return COS;
    else if (!strcmp (cmd, "dump"))     return DUMP;
    else if (!strcmp (cmd, "hlt"))      return HLT;
}

void move_array_into_file (const *array, const num_elements) {

    FILE *f = fopen ("data.bin", "wb");
    fwrite (array, sizeof (elem_type), num_elements, f);
    fclose(f);
}