/* Programa que retorna a mediana de 4 números */

#include <stdio.h>

int main (int argc, char* argv[]) {

	int n1, n2, n3, n4; 

	printf("\nOs numeros digitados abaixo sao distintos\n");
	printf("\nNumero 1: "); scanf("%d", &n1);
	printf("\nNumero 2: "); scanf("%d", &n2);
	printf("\nNumero 3: "); scanf("%d", &n3);
	printf("\nNumero 4: "); scanf("%d", &n4);

	int max, min;

	if(n1 > n2 && n1 > n3 && n1 > n4)
		max = n1;
	else if(n2 > n1 && n2 > n3 && n2 > n4)
		max = n2;
	else if(n3 > n1 && n3 > n2 && n3 > n4)
		max = n3;
	else if(n4 > n1 && n4 > n2 && n4 > n3)
		max = n4;

	if(n1 < n2 && n1 < n3 && n1 < n4)
		min = n1;
	else if(n2 < n1 && n2 < n3 && n2 < n4)
		min = n2;
	else if(n3 < n1 && n3 < n2 && n3 < n4)
		min = n3;
	else if(n4 < n1 && n4 < n2 && n4 < n3)
		min = n4;

	float md1, md2;

	if (n1 != max && n1 != min)
		md1 = n1;
	else if (n2 != max && n2 != min)
		md1 = n2;
	else if (n3 != max && n3 != min)
		md1 = n3;
	else if (n4 != max && n4 != min)
		md1 = n4;

	if (n1 != max && n1 != min && n1 != md1)
		md2 = n1;
	else if (n2 != max && n2 != min && n2 != md1)
		md2 = n2;
	else if (n3 != max && n3 != min && n3 != md1)
		md2 = n3;
	else if (n4 != max && n4 != min && n4 != md1)
		md2 = n4;


	printf("\nMediana: %.1f\n\n", ((md1 + md2) / 2));

	return 0;
}