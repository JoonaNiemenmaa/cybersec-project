#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "encrypt.h"

int primality_test(int number) {
	for (int i = 2; i * i <= number; i++) {
		if (number % i == 0) {
			return 0;
		}
	}
	return number >= 2;
}

int generate_prime() {
	const int max = (int)sqrt(INT_MAX);
	int number = 0;
	while (!primality_test(number)) {
		number = rand() % max;
	}
	return number;
}

/* geeks for geeks */
int gcd(int m, int n) {
	int r = 0;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
    }
	return m;
}

int multiplicative_inverse(int e, int lambda) {
	for (int d = 2; d < INT_MAX; d++) {
		if ((d * e) % lambda == 1) {
			return d; 
		}
	}
	return -1;
}

void generate_keys(int *n, int *d, int *e) {
	int p = 0, q = 0, lambda = 0;

	do {
		p = generate_prime();
		q = generate_prime();
	} while (p >= INT_MAX / q);

	*n = p * q;

	lambda = abs((p - 1) * (q - 1)) / gcd(p - 1, q - 1);

	do {
		*e = generate_prime();
	} while (!(*e < lambda && gcd(*e, lambda) == 1));

	*d = multiplicative_inverse(*e, lambda);

	printf("------ KEY ------\n");
	printf("n %d\n", *n);
	printf("d %d\n", *d);
	printf("e %d\n", *e);

	return;
}

/* mä oon fraud tää on kopioitu geeksforgeeksistä */
int power(int base, int expo, int m) {
	int res = 1;
	base = base % m;
	while (expo > 0) {
		if (expo & 1)
			res = (res * 1LL * base) % m;
		base = (base * 1LL * base) % m;
		expo = expo / 2;
	}
	return res;
}

int encrypt_rsa(int input, int e, int n) {
	return power(input, e, n);
}

int decrypt_rsa(int input, int d, int n) {
	return power(input, d, n);
}

char encrypt_xor(char input) {
	return input ^ XOR_KEY;
}

void encrypt_file(char *file_path) {
	FILE *file = NULL;
	char *file_bytes = NULL;
	char byte = '\0';
	int byte_amount = 0;

	if ((file = fopen(file_path, "rb")) == NULL) {
		perror("Failed to open file, terminating.");
		exit(1);
	}
	
	while (fread(&byte, sizeof(char), 1, file) != 0) {
		byte_amount++;
		if ((file_bytes = (char *)realloc(file_bytes, sizeof(char) * byte_amount)) == NULL) {
			perror("Failed to allocate memory, terminating.");
			exit(1);
		}
		file_bytes[byte_amount - 1] = encrypt_xor(byte);
	}

	fclose(file);
	file = NULL;

	if ((file = fopen(file_path, "wb")) == NULL) {
		perror("Failed to open file, terminating.");
		exit(1);
	}

	for (int i = 0; i < byte_amount; i++) {
		fwrite(file_bytes + i, sizeof(char), 1, file);
	}

	fclose(file);
	return;
}

