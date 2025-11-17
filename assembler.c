#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "assembler.h"
#include "config.h"

void dump (assembler_info *assembler_struct, bool sizes, bool cmd, bool array) {

    if (sizes) {

        printf ("Text size : %lu\nNumber of elements : %lu\n", assembler_struct->text_size, assembler_struct->num_elements);
    }

    if (cmd) {

        printf ("Current command : %s", assembler_struct->cmd);
    }

    if (array) {

        printf ("Encoded info : ");

        for (size_t i = 0; i < assembler_struct->num_elements; i++)     printf ("%d ", assembler_struct->output_info[i]);

        printf ("\n");
    }
}

void assembler_constructor (assembler_info *assembler_struct, char *filename) {

    assembler_struct->file = fopen (filename, "r");
    assembler_struct->text_size = INIT_TEXT_SIZE;
    assembler_struct->num_elements = 0;
    assembler_struct->output_info = (elem_type *)calloc (assembler_struct->text_size, sizeof (elem_type));

    for (size_t i = 0; i < sizeof (assembler_struct->cmd) / sizeof (assembler_struct->cmd[0]); i++) {

        assembler_struct->cmd[i] = '\0';
    }
}

void restore_input_info (assembler_info *assembler_struct) {

    while (fscanf (assembler_struct->file, "%s", assembler_struct->cmd) == 1) {

        if ((assembler_struct->num_elements + 3) > assembler_struct->text_size) {

            reallocate_memory (assembler_struct);
        }

        if      (!strcmp (assembler_struct->cmd, "push"))   push  (assembler_struct);

        else if (!strcmp (assembler_struct->cmd, "pop"))    other (assembler_struct, POP);

        else if (!strcmp (assembler_struct->cmd, "add"))    other (assembler_struct, ADD);

        else if (!strcmp (assembler_struct->cmd, "sub"))    other (assembler_struct, SUB);
        
        else if (!strcmp (assembler_struct->cmd, "mul"))    other (assembler_struct, MUL);

        else if (!strcmp (assembler_struct->cmd, "div"))    other (assembler_struct, DIV);

        else if (!strcmp (assembler_struct->cmd, "out"))    other (assembler_struct, OUT);

        else if (!strcmp (assembler_struct->cmd, "in"))     other (assembler_struct, IN);

        else if (!strcmp (assembler_struct->cmd, "sqrt"))   other (assembler_struct, SQRT);

        else if (!strcmp (assembler_struct->cmd, "sin"))    other (assembler_struct, SIN);

        else if (!strcmp (assembler_struct->cmd, "cos"))    other (assembler_struct, COS);

        else if (!strcmp (assembler_struct->cmd, "mul"))    other (assembler_struct, MUL);


        assembler_struct->num_elements++;
    }

    move_array_into_file (assembler_struct->output_info, assembler_struct->num_elements);
}

void assembler_destructor (assembler_info *assembler_struct) {

    fclose (assembler_struct->file);
    assembler_struct->file = NULL;
    free (assembler_struct->output_info);
}

void move_array_into_file (elem_type const *array, size_t const num_elements) {

    FILE *f = fopen ("out.dat", "wb");
    fwrite (array, sizeof (elem_type), num_elements, f);
    fclose(f);
}

void push (assembler_info *assembler_struct) {

    elem_type num;
    fscanf (assembler_struct->file, "%d", &num);

    if ((assembler_struct->num_elements + 3) > assembler_struct->text_size) {

        assembler_struct->text_size *= 10;
        assembler_struct->output_info = (elem_type *)realloc (assembler_struct->output_info, assembler_struct->text_size * sizeof (elem_type));
    }
    assembler_struct->output_info[assembler_struct->num_elements] = PUSH;
    assembler_struct->num_elements++;
    assembler_struct->output_info[assembler_struct->num_elements] = num;
}

void other (assembler_info *assembler_struct, int cmd_id) {

    if ((assembler_struct->num_elements + 2) > assembler_struct->text_size) {

        assembler_struct->text_size *= 10;
        assembler_struct->output_info = (elem_type *)realloc (assembler_struct->output_info, assembler_struct->text_size * sizeof (elem_type));
    }

    assembler_struct->output_info[assembler_struct->num_elements] = cmd_id;
}

void reallocate_memory (assembler_info *assembler_struct) {

    assembler_struct->text_size *= 10;
    assembler_struct->output_info = (elem_type *)realloc (assembler_struct->output_info, assembler_struct->text_size * sizeof (elem_type));
}