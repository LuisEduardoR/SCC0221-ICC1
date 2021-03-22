#include <bits/stdc++.h>

long long unsigned phi[12000]; 

long long unsigned fibonacci (long long unsigned n);
long long unsigned fibonacci_no_opt (long long unsigned n);

int main (int argc, char* argv[]) {
	
	int n = atoi(argv[1]);

	clock_t t1;
	clock_t t2;

	t1 = clock();

	for(int i = 0; i < 12000; i++) {

		phi[i] = -1;

	}

	phi[1] = 1;
	phi[2] = 1;

	printf("%d'th number: %llu", n, fibonacci(n));
	t2 = clock();

	printf(" / Time spent (with DP): %f seconds.\n", (t2-t1) / (double)CLOCKS_PER_SEC);

	t1 = clock();
	printf("%d'th number: %llu", n, fibonacci_no_opt(n));
	t2 = clock();

	printf(" / Time spent (without DP): %f seconds.\n", (t2-t1) / (double)CLOCKS_PER_SEC);

	return 0;
}

long long unsigned fibonacci (long long unsigned n) {

	if(phi[n] != -1) {
		return phi[n];
	} else {
		phi[n] = fibonacci(n -2) + fibonacci(n -1);
		return phi[n];
	}
}

long long unsigned fibonacci_no_opt (long long unsigned n) {

	if(n == 1) return 1;
	else if(n == 2) return 1;
	else return fibonacci_no_opt(n-1) + fibonacci_no_opt(n-2);
}
