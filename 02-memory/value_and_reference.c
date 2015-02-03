#include <stdio.h>
#include <stdlib.h>
#include "../include/launcher.h"


struct data_thing {
    int     counter;
    char*   modified_by;
};

void print_data_thing(const char* detail, const struct data_thing* value){
    printf("%22s - Location: x%x Modified By: %-30s Counter=%02d \n", detail, (int)value, value->modified_by, value->counter);
}

/**
 * 1 - Pass by Value
 * Receives the data item by value, mutates it, and prints the new values
 */
void handle_pass_by_value(struct data_thing value){
    value.counter++;
    value.modified_by = (char *)__func__;
    print_data_thing("Received by Value", &value);
}

/**
 * Creates the data item on the stack and passes it by value to the handler
 */
void pass_by_value_example(){
    struct data_thing data = {.counter = 0, .modified_by = (char *)__func__};
    print_data_thing("Initial Value", &data);
    handle_pass_by_value(data);
    print_data_thing("After Pass by Value", &data);
}

/**
 * 2 - Pass by Reference
 */
void handle_pass_by_reference(struct data_thing* reference){
    reference->counter++;
    reference->modified_by = (char *)__func__;
    print_data_thing("Received by Reference", reference);
}

/**
 * Creates the data item on the stack and passes it by reference to the handler
 */
void pass_by_reference_example(){
    struct data_thing data = {.counter = 0, .modified_by = (char *)__func__};
    print_data_thing("Initial Value", &data);
    handle_pass_by_reference(&data);
    print_data_thing("After Pass by Value", &data);
}

/**
 * 3 - Stack Reference Scoping
 */
struct data_thing* stack_reference_scope_creator(){
    struct data_thing data = {.counter = 0, .modified_by = (char*)__func__};
    print_data_thing("Created on Stack", &data);
    return &data;
}

void stack_reference_scope_example(){
    struct data_thing* data = stack_reference_scope_creator();
    //  Both of these values will be obliterated
    data->counter++;
    data->modified_by = (char*)__func__;
    print_data_thing("Received Reference", data);
}

/**
 * 4 - Heap Reference Scoping
 */
struct data_thing* heap_reference_scope_creator(){
    struct data_thing* data = (struct data_thing*)malloc(sizeof(struct data_thing));
    data->counter = 0;
    data->modified_by = (char*)__func__;
    print_data_thing("Created on Heap", data);
    return data;
}

void heap_reference_scope_example(){
    struct data_thing* data = heap_reference_scope_creator();
    data->counter++;
    data->modified_by = (char*)__func__;
    print_data_thing("Received from Heap", data);
}

/**
 * 5 - Freeing Memory
 */

void free_memory_example(){
    struct data_thing* data = heap_reference_scope_creator();
    data->counter++;
    data->modified_by = (char*)__func__;
    free(data);
    print_data_thing("After Free", data);
    data->counter++;
    print_data_thing("Postmortem Mutate", data);
}

int main(int argc, char** argv){
    struct example options[] = {
            {1, "Pass by Value"},
            {2, "Pass by Reference"},
            {3, "Stack Reference Scope"},
            {4, "Heap Reference Scope"},
            {5, "Freeing Memory"},
    };

    int option_count = sizeof(options) / sizeof(struct example);

    switch (parse_example_input(option_count, options)){
        case 1:
            pass_by_value_example();
            break;
        case 2:
            pass_by_reference_example();
            break;
        case 3:
            stack_reference_scope_example();
            break;
        case 4:
            heap_reference_scope_example();
            break;
        case 5:
            free_memory_example();
            break;
        default:
            exit(1);
    }
}