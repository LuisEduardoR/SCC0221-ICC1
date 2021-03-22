#include <stdio.h>
#include <stdlib.h>

char* AllocChar (long unsigned int amount);

int main (int argc, char* argv[]) {

	printf("Enter amount of chars's to allocate:\n");

	unsigned int amount;

	scanf(" %u", &amount);

	char* p_char = AllocChar(amount);
	printf("Memory allocated!\n");

	for (int i = 0; i < amount; i++)
		*(p_char + i) = '0';

	printf("Memory initialized with '0'!\n");

	printf("First allocated adress: %p / Last allocated adress: %p\n", p_char, p_char + amount - 1);

	printf("Input any character to exit:\n");

	scanf(" %c", p_char);

	free(p_char);
	printf("Allocated memory liberated.\n");

	return 0;
}

char* AllocChar (long unsigned int amount) {

	// calloc(10, sizeof(type)) aloca memoria e zera os bits.

	printf("Allocating %lu char's (%lu bytes)...\n", amount, amount * sizeof(char));
	return (char*) malloc(amount * sizeof(char));

}