// Program that calculates and lists all the prime numbers up to a value given by the user (max = 268435456)

#include <bits/stdc++.h>

using namespace std;

int listprime[268435456];

int main () {

	int n, amount;

	printf("\n< PrimeNumberLister v1.0.0 >        ||| Welcome! |||\n");

	printf("\nEnter the amount of numbers you want to check (min = 0 and max = 268435456):\n");
	scanf("%d", &n);

	if(n > 268435456 || n < 0) {
		printf("\nERROR: Invalid input!!!\n\n");
		return 0;
	} else if (n < 2) {
		printf("\nNo prime numbers!!!\n\n");
		return 0;
	}else{

		printf("\nPrime numbers up to %d: \n\n", n);

		printf("      2 ");

		listprime[0] = 2;
		amount = 1;

		int line = amount;
		for (int i = 3; i <= n; i++) {

			bool prime = true;

			for (int j = 0; j < amount; j++) {
				if(i % listprime[j] == 0) {
					prime = false;
					break;
				}
			}

			if(prime) {

				printf("%7.0d ", i);

				listprime[amount] = i;
				amount++;

				line = amount % 7;			
				if(line == 0)
					printf("    (TOTAL = %7.0d)\n", amount);
			}

		}

		line = amount % 7;
		if(line != 0) {
			for (int i = 0; i < 7 - line; i++) {

				printf("        ");
			}
			printf("    (TOTAL = %7.0d)\n", amount);
		}
	}

	printf("\n");

	return 0;
}