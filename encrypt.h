#ifndef ENCRYPT_H
#define ENCRYPT_H

#define XOR_KEY 'A'

void generate_keys(int *n, int *d, int *e);
int encrypt_rsa(int input, int n, int e);
int decrypt_rsa(int input, int d, int n);
char encrypt_xor(char input);
void encrypt_file(char *file_path);

#endif
