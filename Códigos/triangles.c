#include <stdio.h>

int main (int argc, char* argv[]) { 

	int size;

	scanf(" %d", &size);

	int sfront, sback;

	if (size % 2 == 0) {
		sfront = size / 2;	
		sback = size / 2;
	} else {
		sfront = size / 2 + 1;	
		sback = size / 2;
	}

	for(int i = 1; i <= sfront; i++) {
		for(int j = 0; j < i; j++) {
			if(i == sfront && j == (i - 1) && size % 2 != 0)
				printf(")");
			else if(i == sfront && size % 2 != 0)
				printf("|");
			else
				printf("\\");
		}
		printf("\n");
	}

	for(int i = sback; i >= 1; i--) {
		for(int j = i; j > 0; j--)
			printf("/");
					
		printf("\n");
	}

	return 0;
}