#include "config.h"
#include "enum.h"

typedef struct CPU_info {

    FILE *file;
    bool escape_flag;
    Stack_info *stack;
    int cmd;
} CPU_info;

void constructor_CPU (const char *filename, CPU_info *CPU_struct, Stack_info *stack);
void make_all_instructions (CPU_info *CPU_struct);
void destructor_CPU (CPU_info *CPU_struct);
void push_ (CPU_info *CPU_struct);
void pop_ (CPU_info *CPU_struct);
void simple_operation_ (CPU_info *CPU_struct, cmd_index CMD);
void math_func_ (CPU_info *CPU_struct, double (*operation) (double));
void in_ (CPU_info *CPU_struct);
