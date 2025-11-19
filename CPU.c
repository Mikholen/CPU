#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include "Stack/preambule.h"
#include "Stack/config.h"
#include "config.h"
#include "CPU.h"

void dump_CPU (CPU_info *CPU_struct, bool stack, bool data, bool other) {

    if (stack) { 

        printf ("Stack state:\n");
        print_stack (CPU_struct->stack);
    }

    if (data) {

        printf ("Data len: %lu\n", CPU_struct->data_len);
        printf ("Data:\n");

        for (size_t i = 0; i < CPU_struct->data_len; i++) { printf ("%d ", CPU_struct->data[i]); }

        printf ("\n");
    }

    if (other) { 
        
        printf ("Escape flag: %d\n", CPU_struct->escape_flag); 
        printf ("Current position: %lu\n", CPU_struct->position);
    }
}

void constructor_CPU (const char *filename, CPU_info *CPU_struct, Stack_info *stack) {

    CPU_struct->file = fopen (filename, "rb");
    CPU_struct->escape_flag = false;

    size_t max_size = 20;
    create_stack (stack, max_size);
    CPU_struct->stack = stack;
    CPU_struct->position = 0;

    fread(&(CPU_struct->data_len), sizeof(size_t), 1, CPU_struct->file);;
    CPU_struct->data = (elem_type *) calloc (CPU_struct->data_len, sizeof (elem_type));
    fread(CPU_struct->data, sizeof(elem_type), CPU_struct->data_len, CPU_struct->file);
}

void make_all_instructions (CPU_info *CPU_struct) {

    // int array[20];
    // FILE *f = fopen (filename, "rb");
    // fread (array, sizeof (elem_type), 10, f);

    // for (size_t i = 0; i < 7; i++) {
    //     printf ("%d\n", array[i]);
    // }

    for (CPU_struct->position = 0; CPU_struct->position < CPU_struct->data_len; CPU_struct->position++) {

        // printf ("%d\n", CPU_struct->cmd);
        if (CPU_struct->escape_flag)  break;

        switch (CPU_struct->data[CPU_struct->position]) {

        case PUSH: {

                push_ (CPU_struct);
                break;
            }

        case POP: {

                pop_ (CPU_struct);
                break;
            }

        case ADD: {

                simple_operation_ (CPU_struct, ADD);
                break;
            }
        
        case SUB: {

                simple_operation_ (CPU_struct, SUB);
                break;
            }

        case MUL: {

                simple_operation_ (CPU_struct, MUL);
                break;
            }
        
        case DIV: {

                simple_operation_ (CPU_struct, DIV);
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

        case OUT : {
#ifdef CHICKEN
                printf ("%d\n", CPU_struct->stack->data[CPU_struct->stack->n_elements]);
#else
                printf ("%d\n", CPU_struct->stack->data[CPU_struct->stack->n_elements - 1]);
#endif
                break;
            }

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
    free (CPU_struct->data);
    destructor (CPU_struct->stack);
}

void push_ (CPU_info *CPU_struct) {

    elem_type num = 0;
    num = CPU_struct->data[CPU_struct->position + 1];
    CPU_struct->position++;
    // printf ("%d\n", num);
    push_back (CPU_struct->stack, num);
}

void pop_ (CPU_info *CPU_struct) {

    elem_type num = 0;
    pop (CPU_struct->stack, &num);
    // printf ("%d\n", num);
}

void simple_operation_ (CPU_info *CPU_struct, cmd_index CMD) {

    elem_type num_1 = 0, num_2 = 0;
    pop (CPU_struct->stack, &num_1);
    pop (CPU_struct->stack, &num_2);
    // printf ("%d %d\n", num_1, num_2);

    switch (CMD) {

    case ADD:   { push_back (CPU_struct->stack, num_1 + num_2); break; }
    case SUB:   { push_back (CPU_struct->stack, num_1 - num_2); break; }
    case MUL:   { push_back (CPU_struct->stack, num_1 + num_2); break; }
    case DIV:   { push_back (CPU_struct->stack, num_1 + num_2); break; }
    default:    { printf ("This coomand (id %d) is not supported by function simple_operation_", CMD); }
    }
}

void math_func_ (CPU_info *CPU_struct, double (*operation) (double)) {

    elem_type num = 0;
    pop (CPU_struct->stack, &num);
    // printf ("%d\n", num);
    push_back (CPU_struct->stack, (elem_type )operation (num));
}

void in_ (CPU_info *CPU_struct) {

    int num = 0;
    printf ("Enter number: \n");
    scanf ("%d", &num);
    push_back (CPU_struct->stack, num);
}