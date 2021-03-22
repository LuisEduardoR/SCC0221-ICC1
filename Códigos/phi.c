//""

#include <stdio.h>

int main (int argc, char* argv[]) { 

	
	int n;

	printf("Escreva a quantidade de numeros da sequencia desejados :\n");
	scanf(" %d", &n);

	int phi[n];

	int i = 0;
	while (i < n) {
	
		if(i == 0) {
			phi[i] = 0;
			printf("%d", phi[i]);
		} else if (i == 1) {
			phi[i] = 1;
			printf(", %d", phi[i]);
		} else {

			phi[i] = phi[i-1] + phi[i-2];
			printf(", %d", phi[i]);
		}		

		i++;
	}

	return 0;
}