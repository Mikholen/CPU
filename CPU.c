#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include "Stack/preambule.h"
#include "Stack/config.h"
#include "config.h"
#include "CPU.h"

void constructor_CPU (const char *filename, CPU_info *CPU_struct, Stack_info *stack) {

    CPU_struct->file = fopen (filename, "r");
    CPU_struct->escape_flag = false;

    size_t max_size = 20;
    create_stack (stack, max_size);
    CPU_struct->stack = stack;
    CPU_struct->cmd = -1;
}

void make_all_instructions (CPU_info *CPU_struct) {

    // int array[20];
    // FILE *f = fopen (filename, "rb");
    // fread (array, sizeof (elem_type), 10, f);

    // for (size_t i = 0; i < 7; i++) {
    //     printf ("%d\n", array[i]);
    // }

    while (fread(&(CPU_struct->cmd), sizeof (elem_type), 1, CPU_struct->file) == 1) {

        // printf ("%d\n", CPU_struct->cmd);
        if (CPU_struct->escape_flag)  break;

        switch (CPU_struct->cmd) {

        case PUSH: {

                push_ (CPU_struct);
                break;
            }

        case POP: {

                pop_ (CPU_struct);
                break;
            }

        case ADD: {

                add_ (CPU_struct);
                break;
            }
        
        case SUB: {

                sub_ (CPU_struct);
                break;
            }

        case MUL: {

                mul_ (CPU_struct);
                break;
            }
        
        case DIV: {

                div_ (CPU_struct);
                break;
            }

        case SQRT: {

                math_func_ (CPU_struct, sqrt);
                break;
            }

        case SIN: {

                math_func_ (CPU_struct, sin);
                break;
            }

        case COS: {

                math_func_ (CPU_struct, cos);
                break;
            }

        case IN : {

                in_ (CPU_struct);
                break;
            }

        // case OUT:

        case DUMP: {

                // printf ("***\n");
                print_stack (CPU_struct->stack);
                break;
            }

        case HLT: {

                // printf ("###\n");
                CPU_struct->escape_flag = true;
                break;
            }

        default:

                break;
        }
    }

}

void destructor_CPU (CPU_info *CPU_struct) {

    fclose (CPU_struct->file);
    CPU_struct->file = NULL;
    destructor (CPU_struct->stack);
}

void push_ (CPU_info *CPU_struct) {

    elem_type num = 0;
    fread(&num, sizeof (elem_type), 1, CPU_struct->file);
    // printf ("%d\n", num);
    push_back (CPU_struct->stack, num);
}

void pop_ (CPU_info *CPU_struct) {

    elem_type num = 0;
    pop (CPU_struct->stack, &num);
    // printf ("%d\n", num);
}

void add_ (CPU_info *CPU_struct) { // можно через if else объединить с другими операциями

    elem_type num_1 = 0, num_2 = 0;
    pop (CPU_struct->stack, &num_1);
    pop (CPU_struct->stack, &num_2);
    // printf ("%d %d\n", num_1, num_2);
    print_stack (CPU_struct->stack);
    push_back (CPU_struct->stack, num_1 + num_2);
}

void sub_ (CPU_info *CPU_struct) {

    elem_type num_1 = 0, num_2 = 0;
    pop (CPU_struct->stack, &num_1);
    pop (CPU_struct->stack, &num_2);
    // printf ("%d %d\n", num_1, num_2);
    push_back (CPU_struct->stack, num_1 - num_2);
}

void mul_ (CPU_info *CPU_struct) {

    elem_type num_1 = 0, num_2 = 0;
    pop (CPU_struct->stack, &num_1);
    pop (CPU_struct->stack, &num_2);
    // printf ("%d %d\n", num_1, num_2);
    push_back (CPU_struct->stack, num_1 * num_2);
}

void div_ (CPU_info *CPU_struct) {

    elem_type num_1 = 0, num_2 = 0;
    pop (CPU_struct->stack, &num_1);
    pop (CPU_struct->stack, &num_2);
    // printf ("%d %d\n", num_1, num_2);
    push_back (CPU_struct->stack, num_1 / num_2);
}

void math_func_ (CPU_info *CPU_struct, double (*operation) (double)) { // попробовать объединить синус и косинус через указатель на функцию

    elem_type num = 0;
    pop (CPU_struct->stack, &num);
    // printf ("%d\n", num);
    push_back (CPU_struct->stack, (elem_type )operation (num));
}

// void sin_ (CPU_info *CPU_struct) { // попробовать объединить синус и косинус через указатель на функцию

//     elem_type num = 0;
//     pop (CPU_struct->stack, &num);
//     // printf ("%d\n", num);
//     push_back (CPU_struct->stack, (elem_type )sin (num));
// }

// void cos_ (CPU_info *CPU_struct) { // попробовать объединить синус и косинус через указатель на функцию

//     elem_type num = 0;
//     pop (CPU_struct->stack, &num);
//     // printf ("%d\n", num);
//     push_back (CPU_struct->stack, (elem_type )cos (num));
// }

void in_ (CPU_info *CPU_struct) {

    int num = 0;
    printf ("Enter number: \n");
    scanf ("%d", &num);
    push_back (CPU_struct->stack, num);
}