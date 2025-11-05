#include <stdio.h>
#include "Stack/preambule.h"
#include "CPU.h"

int main () {

    size_t max_size = 20;
    Stack_info stack = {};

    create_stack (&stack, max_size);

    make_all_instructions ("out.dat", &stack);

    destructor (&stack);

    return 0;
}