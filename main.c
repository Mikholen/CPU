#include <stdio.h>

int main (int argc, char *argv[]) {

    const char *filename = argv[1];
    size_t text_size = get_text_size (filename);

    return 0;
}