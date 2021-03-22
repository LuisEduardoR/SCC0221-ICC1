#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXATPTS 10

int main (int argc, char* argv[]) { 

	int attempts = 1;
	int number, try;

	srand(time(NULL));

	number = (rand() % 128) +1;

	printf("Adivinhe um numero de 1 a 128. \n");

	while (attempts <= MAXATPTS && number != try) {

		scanf(" %d", &try);
		
		attempts++;

		if(attempts > MAXATPTS)
			break;

		if (number > try) {
			printf ("Tente um numero maior.\n");			
		} else if (number < try) {
			printf ("Tente um numero menor.\n");			
		} else if (try < 1 || try > 128) {
			printf ("O que voce esta fazendo?\n");			
		}

	}

	if(try == number) {
		printf ("Parabens!\n");
	} else if(attempts >= MAXATPTS) {
		printf ("Acabaram as tentativas!\n");
	}

	return 0;
}