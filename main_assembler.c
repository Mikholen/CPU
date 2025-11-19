#include <stdio.h>
#include "assembler.h"

int main (int argc, char *argv[]) {

    const char *filename_input = argv[1];
    const char *filename_output = argv[2];

    assembler_info assembler_struct = {};

    assembler_constructor (&assembler_struct, filename_input, filename_output);
    restore_input_info (&assembler_struct);
    assembler_destructor (&assembler_struct);

    // int array[20];
    // FILE *f = fopen ("out.txt", "rb");
    // fread (array, sizeof (elem_type), 10, f);
    // fclose(f);

    // for (size_t i = 0; i < 7; i++) {
    //     printf ("%d\n", array[i]);
    // }
    return 0;
}