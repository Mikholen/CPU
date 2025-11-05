#include <stdio.h>
#include "assembler.h"

int main () {

    char filename[] = "sample.dat";

    restore_input_info (filename);

    // int array[20];
    // FILE *f = fopen ("out.txt", "rb");
    // fread (array, sizeof (elem_type), 10, f);
    // fclose(f);

    // for (size_t i = 0; i < 7; i++) {
    //     printf ("%d\n", array[i]);
    // }
    return 0;
}