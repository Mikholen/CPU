#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include "Stack/preambule.h"
#include "config.h"
#include "CPU.h"

void make_all_instructions (const char *filename, Stack_info *stack) {

    // int array[20];
    // FILE *f = fopen (filename, "rb");
    // fread (array, sizeof (elem_type), 10, f);

    // for (size_t i = 0; i < 7; i++) {
    //     printf ("%d\n", array[i]);
    // }
    FILE *f = fopen (filename, "rb");

    bool escape_flag = false;
    int cmd = 0;

    // fseek(f, 0, SEEK_SET);

    while (fread(&cmd, sizeof (elem_type), 1, f) == 1) {

        // printf ("&&&&&&&&&&&\n");

        // printf ("%d\n", cmd);
        if (escape_flag)  break;

        switch (cmd) {

        case PUSH: {

                elem_type num = 0;
                fread(&num, sizeof (elem_type), 1, f);
                // printf ("%d\n", num);
                push_back (stack, num);
                break;
            }

        case POP: {

                elem_type num = 0;
                pop (stack, &num);
                // printf ("%d\n", num);
                break;
            }

        case ADD: {

                elem_type num_1 = 0, num_2 = 0;
                pop (stack, &num_1);
                pop (stack, &num_2);
                // printf ("%d %d\n", num_1, num_2);
                print_stack (stack);
                push_back (stack, num_1 + num_2);
                break;
            }
        
        case SUB: {

                elem_type num_1 = 0, num_2 = 0;
                pop (stack, &num_1);
                pop (stack, &num_2);
                // printf ("%d %d\n", num_1, num_2);
                push_back (stack, num_1 - num_2);
                break;
            }

        case MUL: {

                elem_type num_1 = 0, num_2 = 0;
                pop (stack, &num_1);
                pop (stack, &num_2);
                // printf ("%d %d\n", num_1, num_2);
                push_back (stack, num_1 * num_2);
                break;
            }
        
        case DIV: {

                elem_type num_1 = 0, num_2 = 0;
                pop (stack, &num_1);
                pop (stack, &num_2);
                // printf ("%d %d\n", num_1, num_2);
                push_back (stack, num_1 / num_2);
                break;
            }

        case SQRT: {

                elem_type num = 0;
                pop (stack, &num);
                // printf ("%d\n", num);
                push_back (stack, (elem_type )sqrt (num));
                break;
            }

        case SIN: {

                elem_type num = 0;
                pop (stack, &num);
                // printf ("%d\n", num);
                push_back (stack, (elem_type )sin (num));
                break;
            }

        case COS: {

                elem_type num = 0;
                pop (stack, &num);
                // printf ("%d\n", num);
                push_back (stack, (elem_type )cos (num));
                break;
            }

        // case IN :
        // case OUT:

        case DUMP: {

                // printf ("***\n");
                print_stack (stack);
                break;
            }

        case HLT: {

                // printf ("###\n");
                escape_flag = true;
                break;
            }

        default:

                break;
        }
    }

    fclose (f);
}