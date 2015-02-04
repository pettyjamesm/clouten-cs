
#include <stdio.h>
#include <stdlib.h>
#include "../include/launcher.h"

/**
 * 1 - Stack Size Measurement
 * Receives a counter value and the previously known memory location of the call stack. It prints the details of its current
 * location and then recursively calls itself up to 5 times
 **/
int measure_stack_size(int call, int last_location){
    int  some_value       = 0;
    int  current_location = (int)&some_value;

    if (last_location == 0){
        return measure_stack_size(call + 1, current_location);
    } else if (call < 5) {
        printf("Call %d at x%08x Stack Growth: %d\n", call, current_location, last_location - current_location);
        return measure_stack_size(call + 1, current_location);
    } else {
        return current_location;
    }
}

/**
 * 2 - Stack Allocation Overflow
 * Receives a counter value and proceeds to recursively call itself until the stack overflows, printing the counter every
 * 1000 times.
 */
int overflow_stack_allocation(int call){
    char some_large_buffer[2048];   //  Note this large buffer allocation on stack
    int some_value       = 0;
    int current_location = (int)&some_value;

    if (call % 1000 == 0){
        printf("Call %4d Stack Location: x%08x\n", call, current_location);
    }


    return overflow_stack_allocation(call + 1);
}

/**
 * 3 - Heap Allocation Overflow
 * Receives a counter value and proceeds to recursively call itself until the stack overflows, printing the counter every 1000 calls.
 */
int overflow_heap_allocation(int call){
    char* heap_buffer   = (char*)malloc(2048);
    int some_value       = 0;
    int current_location = (int)&some_value;

    if (call % 1000 == 0){
        printf("Call %4d Stack Location: x%08x\n", call, current_location);
    }


    return overflow_heap_allocation(call + 1);
}

/**
 * 4 - Heap (over) allocation
 * Allocates a large buffer (10MB) on heap and then finds the largest value in the buffer. When the largest value is 0,
 * the memory is freed and returned to the heap. If a larger value is found, that memory is not freed. This function
 * then recursively calls itself until the program runs out of memory or is killed.
 */
void heap_exhaustion_example(){
    size_t buffer_size = 10000000;
    int* big_buffer;

    // ~ 40 MB allocation (10,000,000 * 4 bytes)
    big_buffer = (int*)malloc(buffer_size * sizeof(int));
    if (big_buffer == NULL){
        perror("Failed to allocate enough memory");
        exit(1);
    }

    int max_value = 0;

    while (max_value == 0){
        for (size_t i = 0; i < buffer_size; i++){
            max_value = (big_buffer[i] > max_value) ? big_buffer[i] : max_value;
            big_buffer[i]++;
        }
        //  Attempt to release zeroed memory to get pre-found memory later
        if (max_value == 0){
            free(big_buffer);
        } else {
            printf("Found Max Value %d in Heap Location x%08x\n", max_value, (int)big_buffer);
            break;
        }
    }

    heap_exhaustion_example();

    printf("Maintaining a reference to buffer location: x%x\n", (int)big_buffer);
}

int main(int argc, char** argv){
    struct example options[] = {
            {1, "Stack Size Measurement"},
            {2, "Stack Allocation Overflow"},
            {3, "Heap Allocation Overflow"},
            {4, "Heap Exhaustion"},
    };

    printf("Current PID: %d\n", getpid());

    int option_count = sizeof(options) / sizeof(struct example);

    switch (parse_example_input(option_count, options)){
        case 1:
            measure_stack_size(0, 0);
            break;
        case 2:
            overflow_stack_allocation(0);
            break;
        case 3:
            overflow_heap_allocation(0);
            break;
        case 4:
            heap_exhaustion_example();
            break;
        default:
            exit(1);
    }
    return 0;
}