#include "file.h"

/*
Sources:
1. C language in general: LUT C ohjelmointiopas
2. Looping through a directory: https://www.geeksforgeeks.org/c-program-list-files-sub-directories-directory/
3. Looping through a directory 2: https://stackoverflow.com/questions/67544777/in-c-how-to-match-d-type-value-to-state-of-element
4. Max filepath length: https://askubuntu.com/questions/859945/what-is-the-maximum-length-of-a-file-path-in-ubuntu
5. Linked list: https://www.learn-c.org/en/Linked_lists
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


int loop_through_files(folder_t *first) {
    unsigned char folder_id = 4; // 4 means default directory in dirent library
    char parent_folder[256] = "..";
    char dot_folder[256] = ".";
    char new_path[MAX_PATH] = "";
    char project_path[MAX_PATH] = "";
    struct dirent *dir_entry = NULL; // Pointer for directory entry

    while (first != NULL) {
        // Source 2 and 3
        DIR *dr = opendir(first->path); // opendir() returns a pointer of DIR type.

        // Check if directory is found and opened properly
        if (dr == NULL) {
            printf("Could not open directory %s.\n", first->path);
            first = delete_first_folder(first);
            continue;
        }

        // Source 3
        while ((dir_entry = readdir(dr)) != NULL) {
            // .. and . folders do not get added to the folder list
            if (strcmp(dir_entry->d_name, parent_folder) == 0) {
                // printf("PARENT FOLDER: %s\n", dir_entry->d_name);
                continue; // Continue if folder is parent folder (..)
            } else if (strcmp(dir_entry->d_name, dot_folder) == 0) {
                // printf("DOT FOLDER: %s\n", dir_entry->d_name);
                continue; // Continue if folder is current folder (.)
            }

            // Check if the read item is a folder or a file
            if (dir_entry->d_type == folder_id) {
                // Create the path for the new directory
                strcpy(new_path, first->path);
                strcat(new_path, "/");
                strcat(new_path, dir_entry->d_name);
                // printf("DIR: %s\n", new_path);
                // Add the new directory path to the linked list
                add_new_folder(new_path, first);
            } else {
                // Form the path of the new file
                strcpy(new_path, first->path);
                strcat(new_path, "/");
                strcat(new_path, dir_entry->d_name);
                // Form the path for the project file check
                strcpy(project_path, first->path);
                strcat(project_path, "/");
                strcat(project_path, PROJECT);

                if (strcmp(project_path, new_path) == 0) {
                    printf("PROJECT PATH: %s\n", project_path);
                    continue; // Continue if first node is same as program folder   
                } else {  
                    // printf("FILE: %s\n", new_path);
                    /* 
                    Call the encryption function
                    
                    */
                }
            }
        }
        // Delete the current first from the linked list
        first = delete_first_folder(first);
        closedir(dr);
    }
    free_memory(first);
    return 0;
}

void add_new_folder(char *path, folder_t *first) {
    // Find the last node
    folder_t *last = first;
    while (last->next != NULL) {
        last = last->next;
    }
    // Add a new folder at the end of the list
    last->next = (folder_t *) malloc(sizeof(folder_t));
    strcpy(last->next->path, path);
    last->next->next = NULL;
    return;
}

// Debug function
void print_folders(folder_t *first) {
    printf("\nFOLDERS\n");
    // Loop through nodes
    folder_t *current = first;
    while (current->next != NULL) {
        printf("%s\n", current->path);
        current = current->next;
    }
    printf("\n");
    return;
}

folder_t *delete_first_folder(folder_t *first) {
    if (first->next == NULL) {
        free(first);
        return NULL;
    }
    folder_t *new_first = first->next;
    free(first);
    return new_first;
}

void free_memory(folder_t *first) {
    folder_t *current = first;
    while (first != NULL) {
        current = first->next;
        free(first);
        first = current;
    }
    return;
}