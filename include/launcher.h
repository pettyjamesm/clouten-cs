#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct example {
    int   value;
    char* name;
};

int parse_example_input(const size_t option_size, const struct example* options){
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Available Examples to Run:\n");
    for (int i = 0; i < option_size; i++){
        struct example current = options[i];
        printf("  %2d - %s\n", current.value, current.name);
    }
    printf("Select an available example: ");

    char buffer[10];
    size_t length  = read(STDIN_FILENO, &buffer, sizeof(buffer) - 1);
    buffer[length] = '\0';

    int read_value = atoi(buffer);
    for (int i = 0; i < sizeof(options) / sizeof(struct example); i++){
        struct example current = options[i];
        if (current.value == read_value){
            printf("Launching %s\n", current.name);
        }
    }
    return read_value;
}