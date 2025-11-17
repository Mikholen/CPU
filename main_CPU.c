#include <stdio.h>
#include "Stack/preambule.h"
#include "CPU.h"

int main () {

    const char *filename = "out.dat";
    CPU_info CPU_struct = {};
    Stack_info stack = {};

    constructor_CPU (filename, &CPU_struct, &stack);

    make_all_instructions (&CPU_struct);

    destructor_CPU (&CPU_struct);

    return 0;
}