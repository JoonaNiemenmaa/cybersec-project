#ifndef FILE_H 
#define FILE_H

#define MAX_PATH 4096 // According to source 4 max file path in Ubuntu can be 4096 characters
#define PROJECT "project" // Name of the program binary to ignore

// Struct for linked list where folder paths are stored
typedef struct folder {
    char path[256];
    struct folder * next;
} folder_t;

// Functions
int loop_through_files(folder_t *first);
void add_new_folder(char *path, folder_t *first);
void print_folders(folder_t *first);
folder_t *delete_first_folder(folder_t *first);
void free_memory(folder_t *first);



#endif
