#include "preambule.h"

int main () {

    size_t max_size = 10;
    Stack_info stack = {};

    dump (create_stack (&stack, max_size));

    // stack.data[0] = 1;
    // stack.data[1] = 1;

    int me = 0;

    for (int i = 0; i < 7; i++) {

        scanf ("%d", &me);
        dump (push_back (&stack, me));
        print_stack (&stack);

    }

    for (int i = 0; i < 7; i++) {

        // scanf ("%d", &me);
        dump (pop (&stack, &me));
        printf ("%d\n", me);
        print_stack (&stack);

    }

    destructor (&stack);

    return 0;
}