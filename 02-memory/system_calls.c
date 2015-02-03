#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/launcher.h"

/**
 * 1 - Read Single Byte From File
 * Uses the FILE* struct defined in stdio.h to read from file in c. It reads the first byte of Overview.md and then closes
 * the file.
 */
void read_from_file(){
    FILE* file = fopen("docs/Overview.md", "r");

    if (file == NULL){
        perror("Couldn't open file");
        exit(1);
    }

    int first_byte = fgetc(file);
    if (first_byte < 0){
        perror("Couldn't read from file");
        exit(1);
    }

    printf("First Byte Value: %c\n", (char)first_byte);

    fclose(file);
}


/**
 * 2 - Read 100 Bytes From File Descriptor
 * Uses the POSIX standard API functions defined in fcntl.h to open() a file descriptor, read the first 100 bytes,
 * then closes it.
 * Note: file_descriptor is an integer value
 */
void read_from_file_descriptor(){
    int file_descriptor = open("docs/Overview.md", O_RDONLY);
    if (file_descriptor < 0){
        perror("Couldn't open file descriptor");
    }

    char contents[32];
    int  bytes_read = read(file_descriptor, contents, 30);
    if (bytes_read < 0){
        perror("Couldn't read first 100 bytes of file");
    }
    contents[bytes_read] = '\0';

    printf("\nFirst 100 Bytes of the Overview Doc:\n%s\n", contents);

    close(file_descriptor);
}



int main(int argc, char**argv){
    struct example options[] = {
            {1, "Read Single Byte From File"},
            {2, "Read 100 Bytes From File Descriptor"},
    };
    int option_count = sizeof(options) / sizeof(struct example);

    switch (parse_example_input(option_count, options)){
        case 1:
            read_from_file();
            break;
        case 2:
            read_from_file_descriptor();
            break;
        default:
            exit(1);
    }
}