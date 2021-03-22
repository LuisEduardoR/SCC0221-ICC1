#include <stdio.h>

int main (int argc, char* argv[]) {
	
	int n;
	printf("n: ");
	scanf(" %d", &n);


	int A[n];
	printf("A: ");
	for (int i = 0; i < n; i++) 
		scanf(" %d", &A[i]);
	
	int B[n];
	printf("B: ");
	for (int i = 0; i < n; i++)
		scanf(" %d", &B[i]);
	
	int C[2*n];
	printf("C: ");
	for (int i = 0; i < 2*n; i++)
		if(i % 2 == 0)
			C[i] = A[i/2];
		else
			C[i] = B[i/2];

	for (int i = 0; i < 2*n; i++)
		if(i == 2*n - 1)
			printf("%d\n", C[i]);
		else
			printf("%d, ", C[i]);

	return 0;
}