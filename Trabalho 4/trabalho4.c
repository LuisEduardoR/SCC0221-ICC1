# include <stdio.h>
# include <stdlib.h>

// Estrutura para guardar um número racional na forma de fração.
typedef struct {

    int num, den;

} rationalNumber;

// Header - funções declaradas "oficialmente" após a main.
void GetObjectEquation(char obj_type, rationalNumber*** eq_system, int* cur_eq_num, int coef_num);
void DetectContradicitons(rationalNumber*** eq_system, int eq_num, int coef_num, int cur_step, int* contradict);
rationalNumber SubtractRationals(rationalNumber a, rationalNumber b);
rationalNumber MultiplyRationals(rationalNumber a, rationalNumber b);
rationalNumber DivideRationals(rationalNumber a, rationalNumber b);
rationalNumber SimplifyRational(rationalNumber r);
int MMC(int a, int b);
int MDC(int a, int b);
void PrintEqSystem(rationalNumber** eq_system, int eq_num, int coef_num);

int main (int argc, char* argv[]) {

    // Guarda o número de equações que serão recebidas no sistema.
    int eqNum;
    scanf(" %d", &eqNum);

    // Guarda o número de coeficientes por equação.
    int coefNum;
    scanf(" %d", &coefNum);

    // Guarda o sistema de equações que será utilizado.
    rationalNumber** eqSystem = NULL;

    // Número atual de equações no sistema.
    int currentEqNum = 0;

    // Usado para guardar o tipo do objeto a ser recebido.
    char objType = 'x';

    // Recebe o objeto geométrico 1.
    while (objType != 'p' && objType != 'r') {

        scanf(" %c", &objType);
        if(objType != 'p' && objType != 'r')
            printf(" > Tipo de objeto inva'lido!\n");

    }
    GetObjectEquation(objType, &eqSystem, &currentEqNum, coefNum);

    // Recebe as equações do segundo objeto, se for possível recebe-lo (o número de equações a serem
    // recebidas é maior do que o número de equações recebidas do objeto 1).
    if((objType == 'p' && eqNum > 1) || (objType == 'r' && eqNum > 2)) {

        // Reseta o input do tipo de objeto.
        objType = 'x';

        // Recebe o objeto geométrico 2.
        while (objType != 'p' && objType != 'r') {

            scanf(" %c", &objType);
            if(objType != 'p' && objType != 'r')
                printf(" > Tipo de objeto inva'lido!\n");

        }
        GetObjectEquation(objType, &eqSystem, &currentEqNum, coefNum);
    }

    // Detecta absurdos no sistem (se existirem então não há colisões).
    int contradictions = 0;
    DetectContradicitons(&eqSystem, eqNum, coefNum, 0, &contradictions);

    // Simplifica os números obtidos no sistema após o processo de detectar contradições.
    for(int i = 0; i < eqNum; i++) {
        for(int j = 0; j < coefNum; j++) {
            if(eqSystem[i][j].num != 0)
                eqSystem[i][j] = SimplifyRational(eqSystem[i][j]);
        }
    }

    // Printa o resultado do programa.
    if(contradictions > 0)
        printf("nao\n");
    else
        printf("sim\n");

    PrintEqSystem(eqSystem, eqNum, coefNum);

    // Libera a memória que guarda o sistema de equações.
    for (int i = 0; i < eqNum; i++) {
        free(eqSystem[i]);
    }
    free(eqSystem);

    return 0;

}

// Recebe um objeto geométrico sendo esse uma reta ou plano - baseado em obj_type.
void GetObjectEquation(char obj_type, rationalNumber*** eq_system, int* cur_eq_num, int coef_num){

    // Guarda temporariamente os numeradores e denominadores recebidos.
    int tNum, tDen;

    if(obj_type == 'p') { // Recebe a equação única de um plano.

        // Aumenta o tamanho do sistem de equações.
        (*cur_eq_num)++;
        (*eq_system) = (rationalNumber**)realloc((*eq_system), (*cur_eq_num) * sizeof(rationalNumber*));

        // Aloca o espaço para os coeficientes.
        (*eq_system)[(*cur_eq_num) - 1] = (rationalNumber*)malloc(coef_num * sizeof(rationalNumber));

        // Recebe os coeficientes.
        for(int i = 0; i < coef_num; i++) {

            scanf(" %d", &tNum); // Recebe o numerador do coeficiente i.
            (*eq_system)[(*cur_eq_num) - 1][i].num = tNum;

            // Recebe o denominador do coeficiente i garantindo que não seja 0.
            tDen = 0;
            while (tDen == 0) {
                scanf(" %d", &tDen);

                if(tDen == 0)
                    printf(" > Denominador inva'lido!\n");
            }
            (*eq_system)[(*cur_eq_num) - 1][i].den = tDen;
        }

    } else if(obj_type == 'r') { // Recebe as duas equações usadas para receber uma reta.

        // Similar ao de cima porém para retas, ou seja, usando duas equações.

        (*cur_eq_num) += 2;
        (*eq_system) = (rationalNumber**)realloc((*eq_system), (*cur_eq_num) * sizeof(rationalNumber*));

        // Aloca o espaço para os coeficientes da primeira reta.
        (*eq_system)[(*cur_eq_num) - 2] = (rationalNumber*)malloc(coef_num * sizeof(rationalNumber));
        // Aloca o espaço para os coeficientes da segunda reta.
        (*eq_system)[(*cur_eq_num) - 1] = (rationalNumber*)malloc(coef_num * sizeof(rationalNumber));

        for(int i = 0; i < coef_num; i++) { // Recebe a primeira equação da reta.

            scanf(" %d", &tNum);
            (*eq_system)[(*cur_eq_num) - 2][i].num = tNum;

            tDen = 0;
            while (tDen == 0) {
                scanf(" %d", &tDen);

                if(tDen == 0)
                    printf(" > Denominador inva'lido!\n");
            }
            (*eq_system)[(*cur_eq_num) - 2][i].den = tDen;

        }

        for(int i = 0; i < coef_num; i++) { // Recebe a segunda equação da reta.

            scanf(" %d", &tNum);
            (*eq_system)[(*cur_eq_num) - 1][i].num = tNum;

            tDen = 0;
            while (tDen == 0) {
                scanf(" %d", &tDen);

                if(tDen == 0)
                    printf(" > Denominador inva'lido!\n");
            }
            (*eq_system)[(*cur_eq_num) - 1][i].den = tDen;

        }
    }
}

// Função recursiva que descobre se há colisão entre os objetos geométricos.
void DetectContradicitons(rationalNumber*** eq_system, int eq_num, int coef_num, int cur_step, int* contradict){

    // Retorna caso esteja na última equação.
    if(cur_step == eq_num - 1)
        return;

    // Faz o swap caso o primeiro coeficiente da primeira equação do sistema atual seja 0.
    if((*eq_system)[cur_step][cur_step].num == 0) {
        for(int i = 1; i < eq_num; i++) { // Acha uma equação com o coeficiente inicial válido.
            if((*eq_system)[i][cur_step].num != 0) {

                // Guarda as equações em variáveis temporárias.
                rationalNumber* tempFirst = (*eq_system)[cur_step];
                rationalNumber* tempNewFirst = (*eq_system)[i];

                // Faz o swap.
                (*eq_system)[cur_step] = tempNewFirst;
                (*eq_system)[i] = tempFirst;

                break;
            }
        }
    }

    // Pega o "pivô".
    rationalNumber pivot = (*eq_system)[cur_step][cur_step];

    // Zera o primeiro coeficiente de cada equação a partir da do pivô.
    for(int i = cur_step + 1; i < eq_num; i++) {

        // Multiplicador usado para zerar o primeiro coeficiente da equação i.
        rationalNumber multiplier = DivideRationals((*eq_system)[i][cur_step], pivot);

        // Faz a subtração para cada coeficiente da equação i.
        for(int j = cur_step; j < coef_num; j++) {

            // Consegue o número a ser usado na subtração do coeficiente j da equação i.
            rationalNumber coefJSub = MultiplyRationals((*eq_system)[cur_step][j], multiplier);

            // Subtrai do coeficiente j da equação i.
            (*eq_system)[i][j] = SubtractRationals((*eq_system)[i][j], coefJSub);
        }
    }

    // Detecta se há um absurdo no sistema.
    for(int i = 0; i < eq_num; i++) {

        // Guarda o somatório de todos os coeficientes menos o último.
        int som = 0;
        for(int j = 0; j < coef_num - 1; j++) {
            som += (*eq_system)[i][j].num;
        }

        // Se todos os coeficientes menos o último são iguais a zero, então há um absurdo.
        if(som == 0 && (*eq_system)[i][coef_num - 1].num != 0)
            (*contradict)++;
    }

    // Efetivamente excluí a primeira linha e coluna para o próximo passo recursivo.
    cur_step++;
    // Faz o próximo passo recursivo.
    DetectContradicitons(eq_system, eq_num, coef_num, cur_step, contradict);

}

// Faz uma subtração entre dois números racionais na forma de fração.
rationalNumber SubtractRationals(rationalNumber a, rationalNumber b) {

    rationalNumber result;

    // Caso o numerador do segundo número seja 0 não é necessário executar a operação.
    if(b.num == 0)
        return a;

    // Consegue o mínimo múltiplo comum entre os dois números.
    int mmc = MMC(a.den, b.den);

    // Coloca as frações sobre o mesmo denominador (MMC).

    a.num *= (mmc / a.den);
    b.num *= (mmc / b.den);

    // Faz a subtração.
    result.num = a.num - b.num;
    result.den = mmc;

    return result;
}

// Faz uma multiplicação entre dois números racionais na forma de fração.
rationalNumber MultiplyRationals(rationalNumber a, rationalNumber b) {

    rationalNumber result;

    result.num = a.num * b.num;
    result.den = a.den * b.den;

    return result;
}

// Faz uma divisão entre dois números racionais na forma de fração.
rationalNumber DivideRationals(rationalNumber a, rationalNumber b) {

    rationalNumber result;

    result.num = a.num * b.den;
    result.den = a.den * b.num;

    return result;
}

// Simplifica um número racional.
rationalNumber SimplifyRational(rationalNumber r) {

    if(r.num % r.den == 0) {
        r.num  /= r.den;
        r.den /= r.den;
    }

    return r;
}

// Calcula o MMC a partir do MDC.
int MMC(int a, int b) {

    return (a*b) / MDC (a, b);

}

// Função recursiva que calcula o MMC entre dois números.
int MDC(int a, int b) {

    if(a == b)
        return a;
    else if(a > b)
        return MDC(a-b, b);
    else
        return MDC(a, b-a);

}

// Printa um sistema de equações.
void PrintEqSystem(rationalNumber** eq_system, int eq_num, int coef_num){

    for(int i = 0; i < eq_num; i++) { // Printa a equação i.
        for(int j = 0; j < coef_num; j++) { // Printa os coeficientes da equação i.

            if(eq_system[i][j].den == 1 || eq_system[i][j].num == 0) { // Printa apenas o numerador caso o
                printf("%d\t", eq_system[i][j].num);                   // denominador seja 1 ou o numerador 0.
            } else if(eq_system[i][j].den == -1) {      // Printa apenas o oposto do numerador caso o
                printf("%d\t", (-eq_system[i][j].num)); // denominador seja -1;
            } else {
                printf("%d/%d\t", eq_system[i][j].num, eq_system[i][j].den);
            }

        }
        printf("\n");
    }
}
