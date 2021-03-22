# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct profile Profile;
struct profile {

    char username[32];
    char realname[64];
    Profile* friends;

};

// Header
void createProfile (Profile** pnet);

int main (int argc, char* argv[]) {

    Profile* net = NULL;

    createProfile(&net);

    printf("%s\n", net[0].username);
    printf("%s\n", net[0].realname);

    return 0;
}

void createProfile (Profile** pnet) {

    static int network_size = 0;

    network_size++;

    (*pnet) = (Profile*) realloc ((*pnet), sizeof(Profile) * network_size);

    int curUserPos = network_size - 1;

    printf("Username: ");
    fgets((*pnet)[curUserPos].username, 32, stdin);

    for (int i = 0; i < 32; i++) {
        if((*pnet)[curUserPos].username[i] == '\n' || (*pnet)[curUserPos].username[i] == '\r' || (*pnet)[curUserPos].username[i] == '\t')
            (*pnet)[curUserPos].username[i] = '\0';
    }

    printf("Real Name: ");
    fgets((*pnet)[curUserPos].realname, 64, stdin);

    for (int i = 0; i < 64; i++) {
        if((*pnet)[curUserPos].realname[i] == '\n' || (*pnet)[curUserPos].username[i] == '\r' || (*pnet)[curUserPos].username[i] == '\t')
            (*pnet)[curUserPos].realname[i] = '\0';
    }

}
