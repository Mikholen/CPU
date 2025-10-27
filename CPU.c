#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include "stack"
#include "config.h"
#include "preambule.h"

size_t get_text_size (const char *filename) {

    struct stat text_stat;
    stat (filename, &text_stat);
    return (size_t)text_stat.st_size;
}

elem_type *read_assemler_output_file (const char *filename, size_t *n_elements) {

    size_t n_elements = get_text_size(filename);
    elem_type *assembler_output = (elem_type *)calloc (n_elements, sizeof (elem_type));
    FILE *f = fopen (filename, "rb");
    fread (assembler_output, sizeof (elem_type), n_elements, f);
    fclose (f);

    return assembler_output;
}

void make_all_instructions (const elem_type *assembler_output, const size_t n_elements, stack *stack) {

    for (size_t i = 0; i < n_elements; i++) {

        switch (assembler_output[i]) {

        case PUSH:
            push_back (&stack, assembler_output[++i]);
            break;

        case POP:
            pop (&stack);
            break;

        case ADD:
            push_back (&stack, pop (&stack) + pop (&stack));
            i += 2;
            break;
        
        case SUB:
            push_back (&stack, pop (&stack) - pop (&stack));
            i += 2;
            break;

        case MUL:
            push_back (&stack, pop (&stack) * pop (&stack));
            i += 2;
            break;
        
        case DIV: // &&&&&&&&&&&&&&&&&& type????
            push_back (&stack, pop (&stack) / pop (&stack));
            i += 2;
            break;

        case SQRT:
            push_back (&stack, sqrt (pop (&stack)));
            i++;
            break;

        case SIN:
            push_back (&stack, sin (pop (&stack)));
            i++;
            break;

        case COS:
            push_back (&stack, cos (pop (&stack)));
            i++;
            break;

        default:
            break;
        }
    }
}