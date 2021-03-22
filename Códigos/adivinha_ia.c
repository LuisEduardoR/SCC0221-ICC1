#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXATPTS 10

int main (int argc, char* argv[]) { 

	int iamax, iamin, signal;
	iamax = 128;
	iamin = 1;

	int attempts = 1;
	int number, try;

	srand(time(NULL));

	number = (rand() % 128) +1;

	printf("Essa IA adivinhara um numero de 1 a 128 em ate 8 tentativas ((log2 de 128) + 1), o numero q ela tem que adivinhar eh %d.\n\n", number);

	printf("IA, adivinhe um numero de 1 a 128. \n\n");

	printf("OK!\n");
	while (attempts <= MAXATPTS && number != try) {

		// adivinha da ia
		if (try == 127)
			try++;
		else
			try = iamin + (iamax - iamin) / 2;

		printf("%d\n", try);		
		//

		attempts++;

		if(attempts > MAXATPTS)
			break;

		if (number > try) {
			printf ("Tente um numero maior.\n");
			iamin = try;			
		} else if (number < try) {
			printf ("Tente um numero menor.\n");
			iamax = try;			
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