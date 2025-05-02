#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

int main(void) {
    char *path = getenv("HOME");

    // Create the first node of the linked list
    folder_t * first_folder = NULL;
    first_folder = (folder_t *) malloc(sizeof(folder_t));
    if (first_folder == NULL) {
        return 1;
    };
    strcpy(first_folder->path, path);
    first_folder->next = NULL;

    // Loop through the file tree
    loop_through_files(first_folder);

    return (0);
}
