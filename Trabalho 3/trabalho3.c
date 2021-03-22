// Código que recebe um mapa juntamente com a posição de duas bases de jogadores e de uma determinada quantidade de recursos e verifica se esse
// mapa seria balanceado para uma espécie de jogo de RTS.

// Feito por Luís Eduardo Rozante de Freitas Pereira - NºUSP: 10734794
// 25/05/2018

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// Define um struct para guardar as coordenadas de um ponto.
typedef struct {
    int x;
    int y;
}point;

// Funções (serão declaradas por completo após a main).
point* allocateResourcePos(int resAmount);
int checkBalance(int map[9][9], int moveableTilesAmount, point p1Pos, point p2Pos, int resAmount, point* resourcePositions);
float calculateExploration(int map[9][9], int moveableTilesAmount, point startPos, int resAmount, point* resourcePositions, int** visitedPositions);
void floodFill(int map[9][9], point startPosition, point targetPos, int* explorValue, int* foundResource, int** visitedPositions);
void freeResourcePos(point* resources);

int main (int argc, char* argv[]) {

    // Mapa do jogo.
    int map[9][9];
    // Guarda o número de espaços transponíveis no mapa.
    int moveableTilesAmount = 0;

    // Recebe as informações sobre o mapa.
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++) {

            // Recebe se o espaço (i,j) é transponível ou não.
            scanf(" %d", &map[i][j]);

            // Conta o número de espaços transponíveis no mapa.
            if(map[i][j] == 0)
                moveableTilesAmount++;

        }

    // GUarda as coordenadas do player 1.
    point p1Pos;

    // Recebe as coordenadas do player 1.
    scanf(" %d", &p1Pos.x);
    scanf(" %d", &p1Pos.y);

    // Guarda as coordenadas do player 2.
    point p2Pos;

    // Recebe as coordenadas do player 2.
    scanf(" %d", &p2Pos.x);
    scanf(" %d", &p2Pos.y);

    // Quantidade de recursos no jogo.
    int resourceAmount;

    // Recebe a quantidade de recursos no jogo.
    scanf(" %d", &resourceAmount);

    // Guarda a matriz com a posição dos recursos.
    point* resourcePositions = NULL;

    // Aloca a memória necessária para a matriz.
    resourcePositions = allocateResourcePos(resourceAmount);

    // Recebe a posição de cada recurso.
    for (int i = 0; i < resourceAmount; i++) {

        scanf(" %d", &resourcePositions[i].x);
        scanf(" %d", &resourcePositions[i].y);

    }

    // Checa o balanceamento do mapa e retorna 0 caso ele seja balanceado ou o numero do jogador que tem vantagem caso ele não seja.
    int balance = checkBalance(map, moveableTilesAmount, p1Pos, p2Pos, resourceAmount, resourcePositions);

    // Printa os resultados sobre o balanceamento do mapa.
    if(balance == 0)
        printf("O mapa eh balanceado \n");
    else
        printf("O jogador %d possui vantagem\n", balance);

    // Desaloca a matriz que guarda a posição dos recursos.
    freeResourcePos(resourcePositions);

    return 0;
}

// Aloca na heap uma matriz de point para guardar a posição dos recursos e retorna um endereço para ela.
point* allocateResourcePos(int resAmount) {

    point* resources = (point*)malloc(resAmount * sizeof(point));
    return resources;

}

// Checa o balanceamento do mapa e retorna 0 caso ele seja balanceado ou o numero do jogador que tem vantagem caso ele não seja.
int checkBalance(int map[9][9], int moveableTilesAmount, point p1Pos, point p2Pos, int resAmount, point* resourcePositions) {

    // Aloca uma matriz com o tamanho do mapa para guardar as posições que já foram visitadas pelo floodFill.
    int** visitedPositions = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++)
        visitedPositions[i] = malloc(9 * sizeof(int));

    // Guarda o valor da Exploration do player 1.
    float E1 = calculateExploration(map, moveableTilesAmount, p1Pos, resAmount, resourcePositions, visitedPositions);
    // Printa o valor de E1.
    printf ("%f\n", E1);

    // Guarda o valor da Exploration do player 2.
    float E2 = calculateExploration(map, moveableTilesAmount, p2Pos, resAmount, resourcePositions, visitedPositions);
    // Printa o valor de E2.
    printf ("%f\n", E2);

    // Libera a memória da matriz que guarda as posições visitadas pelo floodFill.
    for (int i = 0; i < 9; i++)
        free(visitedPositions[i]);
    free(visitedPositions);

    // Retorna o número do jogador que tem vantagem (o que tem menor valor de E) ou 0 se o mapa for balanceado (|E1 - E2| < 0.001).
    if(fabs(E1 - E2) >= 0.001) {
        if(E2 > E1)
            return 1;
        else
            return 2;
    } else
        return 0;

}

// Calcula o valor de Exploration.
float calculateExploration(int map[9][9], int moveableTilesAmount, point startPos, int resAmount, point* resourcePositions, int** visitedPositions) {

    // Faz a somatória que será usada na equação de Exploration.
    float som = 0;
    for (int i = 0; i < resAmount; i++) {

        // Faz o flood fill para o recurso i.
        int explor = 0;
        int found = 0;

        // Preenche a matriz de posições visitadas com zeros.
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                 visitedPositions[i][j] = 0;
             }
         }

        // Inicia o floodFill.
        floodFill(map, startPos, resourcePositions[i], &explor, &found, visitedPositions);

        // Atualiza a somatória.
        som += ((float)explor / (float)moveableTilesAmount);

    }

    // Retorna o resultado da equação de Exploration.
    return ((1 / (float)resAmount) * som);

}

// FUnção recursiva que realiza o flood fill.
void floodFill(int map[9][9], point startPosition, point targetPos, int* explorValue, int* foundResource, int** visitedPositions) {

    // Para de procurar caso o recurso em questão já tenha sido encontrado.
    if(*foundResource != 0)
        return;

    // Aumenta o número de locais visitados pelo floodFill.
    (*explorValue) ++;
    // Marca que a posição atual foi visitada.
    visitedPositions[startPosition.x][startPosition.y] = 1;

    // Verifica se o recurso em questão foi encontrado.
    if(startPosition.x == targetPos.x && startPosition.y == targetPos.y) {
        // Marca que o recurso foi encontrado para que outras 'partes' do floodFill saibam que devêm parar.
        (*foundResource) = 1;
        return;
    }

    // Caso o recurso não seja encontrado começa a buscar uma nova posição para visitar.
    point newPos;

    // Tenta visistar o Sul.
    newPos = startPosition;
    newPos.x ++;
    if(newPos.x <= 8 && visitedPositions[newPos.x][newPos.y] == 0 && map[newPos.x][newPos.y] == 0)
        floodFill(map, newPos, targetPos, explorValue, foundResource, visitedPositions);

    // Tenta visistar o Norte.
    newPos = startPosition;
    newPos.x --;
    if(newPos.x >= 0 && visitedPositions[newPos.x][newPos.y] == 0 && map[newPos.x][newPos.y] == 0)
        floodFill(map, newPos, targetPos, explorValue, foundResource, visitedPositions);

    // Tenta visistar o Oeste.
    newPos = startPosition;
    newPos.y --;
    if(newPos.y >= 0 && visitedPositions[newPos.x][newPos.y] == 0 && map[newPos.x][newPos.y] == 0)
        floodFill(map, newPos, targetPos, explorValue, foundResource, visitedPositions);

    // Tenta visistar o Leste.
    newPos = startPosition;
    newPos.y ++;
    if(newPos.y <= 8 && visitedPositions[newPos.x][newPos.y] == 0 && map[newPos.x][newPos.y] == 0)
        floodFill(map, newPos, targetPos, explorValue, foundResource, visitedPositions);

}

// Limpa a memória desalocando a matriz que guarda a posição dos recursos.
void freeResourcePos(point* resources) {

    // Limpa os recursos.
    free(resources);
}
