#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

    FILE* fp;

    fp = fopen("opFile", "w");

    if(fp == NULL) {
        printf("Failed to open or create file!\n\n");
        return -1;
    }

    fprintf(fp, "Bye world!");

    fclose(fp);

    return 0;
}
