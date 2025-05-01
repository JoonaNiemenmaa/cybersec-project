#ifndef ENCRYPT_H
#define ENCRYPT_H

#define XOR_KEY 'A'

int primality_test(int number);
void generate_keys();
char encrypt(char input);
void encrypt_file(char *file_path);

#endif
