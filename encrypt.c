#include <stdio.h>
#include <stdlib.h>
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
	int number = 0;
	while (primality_test(number) == 0) {
		number = rand();
	}
	return number;
}

/* geeks for geeks */
long int gcd(long int m, long int n) {
	long int r = 0;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
    }
	return m;
}

long int mod_inverse(int e, long int lambda) {
    for (int d = 2; d < lambda; d++) {
        if ((e * d) % lambda == 1)
            return d;
    }
    return -1;
}

void generate_keys() {
	long int p = 0, q = 0, n = 0, lambda = 0, d = 0;
	int e = 0;
	p = generate_prime();
	q = generate_prime();
	n = p * q;
	lambda = labs((p - 1) * (q - 1)) / gcd(p - 1, q - 1);

	e = 65537;
	if (!(e < lambda && gcd(e, lambda) == 1)) {
		printf("Failed to key.\n");
		exit(1);
	}

	d = mod_inverse(e, lambda);

	printf("---------------\n");
	printf("%ld\n", p);
	printf("%ld\n", q);
	printf("%ld\n", n);
	printf("%ld\n", lambda);
	printf("%d\n", e);
	printf("%ld\n", d);



	return;
}

char encrypt(char input) {
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
		file_bytes[byte_amount - 1] = encrypt(byte);
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
