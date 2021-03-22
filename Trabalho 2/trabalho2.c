# include <stdio.h>
# include <math.h>

// =====================================================================================================================

// Funcoes:

// Funçao que faz a predição das notas de um usuario, sera declarada por completo apos a main().
void FazerPredicaoUsuario(int usuario);
// Funçao que calcula a similaridade entre dois usuarios, sera declarada por completo apos a main().
double SimilaridadeEntreAeB(int usuarioA, int usuarioB);
// Funçao que calcula a media das notas de um usuario, sera declarada por completo apos a main().
double MediaUsuario(int usuario);
// Funçao que prediz e printa a nota de um filme para um determinado usuario, sera declarada por completo apos a main().
void PredizerFilme(int usuario, int filme, double similaridades[15], double medias[15]);

// =====================================================================================================================

// Variaveis globais:

// Guarda o numero de usuarios.
int n;
// Guarda o numero de itens
int i;
// Gurda o limiar de selecao.
double t;
// Guarda a matriz nota x usuario.
int MatrizNotaUsuario[15][15];

// =====================================================================================================================

int main (int argc, char* argv[]) {
	
	// Recebe o numero de usuarios e guarda ele em n.
	scanf(" %d", &n);

	// Recebe o numero de itens e guarda ele em i.
	scanf(" %d", &i);

	// Recebe o limiar de selecao e guarda ele em t.
	scanf(" %lf", &t);

	// Recebe os inputs da matriz nota x usario.
	int a;
	for (a = 0; a < n; a++) { // Percorre os usuarios.
		int b;
		for (b = 0; b < i; b++) { // Percorre os itens.
			scanf (" %d", &MatrizNotaUsuario[a][b]);
		}
	}

	// Faz a predicao das notas necessarias para todos os usuarios.
	int u;
	for (u = 0; u < n; u++) {

		FazerPredicaoUsuario(u);

	}

	return 0;
}

void FazerPredicaoUsuario(int usuario) {    
    
    // Verifica se ha notas ah calcular.
	int nF;
	for (nF = 0; nF <= i; nF++)
	{
        
		if(nF == i)
			return;
        else if(MatrizNotaUsuario[usuario][nF] == 0) {
			break;
		}
		
	}

	
	// Guarda a similaridades entre esse usuario e os outros.
	double similaridade[n];

	// Calcula a similaridade entre esse usuario e os outros.
	int s;
	for (s = 0; s < n; s++)
	{
        
		if(usuario == s) // Detecta quando a matriz passou pelo proprio usuario e marca ele na matriz com o valor 0.
			similaridade[s] = 0;
		else // Faz o calculo da similaridade com os outros usuarios.
			similaridade[s] = SimilaridadeEntreAeB(usuario, s);
        
	}

	// Guarda a media das notas dos usuarios.
	double media[n];

	// Calcula a media das notas dos usuarios.
	int m;
	for (m = 0; m < n; m++)
        media[m] = MediaUsuario(m);

    
    // Passa pelos filmes e calcula as notas daqueles que ainda não foram avaliados.
	for (int f = 0; f < i; f++) {
		if(MatrizNotaUsuario[usuario][f] == 0) {
            
            // Prediz e printa a nota do filme.
            PredizerFilme(usuario, f, similaridade, media);
        }
	}
  
    printf("\n");
    
    return;
    
}

double SimilaridadeEntreAeB(int usuarioA, int usuarioB) {

	// Guarda o escalar entre as notas dos usuarios.
	double escalarUsAB = 0;

	// Calcula o escalar entre as notas dos usuarios.
	int i_escAB;
	for (i_escAB = 0; i_escAB < i; i_escAB++)
         escalarUsAB += (MatrizNotaUsuario[usuarioA][i_escAB] * MatrizNotaUsuario[usuarioB][i_escAB]);



	// Guarda a raiz da soma dos quadrados das notas dos usuarios A e B.
	double sqrt_somQuadA = 0;
	double sqrt_somQuadB = 0;


	// Calcula a raiz da soma dos quadrados das notas do usuario A.
	int i_SQ_A;
	for (i_SQ_A = 0; i_SQ_A < i; i_SQ_A++)
        sqrt_somQuadA += pow(MatrizNotaUsuario[usuarioA][i_SQ_A], 2);

	sqrt_somQuadA = sqrt(sqrt_somQuadA);



	// Calcula a raiz da soma dos quadrados das notas do usuario B.
	int i_SQ_B;
	for (i_SQ_B = 0; i_SQ_B < i; i_SQ_B++)
        sqrt_somQuadB += pow(MatrizNotaUsuario[usuarioB][i_SQ_B], 2);

	sqrt_somQuadB = sqrt(sqrt_somQuadB);
    
	// Calcula e retorna a similaridade.
    if((sqrt_somQuadA * sqrt_somQuadB) != 0)
        return (escalarUsAB / (sqrt_somQuadA * sqrt_somQuadB));
    else
        return 0;

}

double MediaUsuario(int usuario) {
    
    // Guarda a somatoria das notas.
    double somNotas = 0;
    // Guarda quantas notas sao diferentes de zero.
    int notasNZero = 0;
        
        int m;
        for (m = 0; m < i; m++) {
            
            somNotas += MatrizNotaUsuario[usuario][m];
            
            if(MatrizNotaUsuario[usuario][m] != 0)
                notasNZero++;
        }
            
            
        // Retorna a media das notas do usuario.
        if(notasNZero > 0)
            return somNotas / (double)notasNZero;
        else
            return 0;
    
}

void PredizerFilme(int usuario, int filme, double similaridades[15], double medias[15]) {
	
	// Verifica se esse usuario fez pelo menos uma avaliacao.
	int av;
	for (av = 0; av <= i; av++)
	{
		if(av == i) {
            printf("DI ");
			return;
        } else if(MatrizNotaUsuario[usuario][av] != 0) {
			break;
		} 
	}
    
    // Verifica se a similaridade com ao menos um dos usuarios esta dentro do limiar.
	int v;
	for (v = 0; v <= n; v++) {
		if(similaridades[v] >= t) {
			break;
		} else if(v == n) {

			printf("DI ");
			return;
		}
	}
    
    // Guarda a somatoria das notas dos outros usuarios para o filme subtraidas de suas medias e multiplicadas pela similaridade com o usuario atual.
    double somatoriaSimNotas = 0;
    // Guarda a somatoria das similaridades entre os usuarios.
    double somatoriaSimilaridades = 0;
    
    int s;
    for (s = 0; s < n; s++) {
        
        if(usuario != s && MatrizNotaUsuario[s][filme] != 0 && similaridades[s] >= t) {
            
            somatoriaSimNotas += similaridades[s] * (MatrizNotaUsuario[s][filme] - medias[s]);
            somatoriaSimilaridades += similaridades[s];
            
        }
        
    }
    
    // Calcula e printa a predicao da nota do filme.
    if(somatoriaSimilaridades != 0)
        printf("%0.2lf ", medias[usuario] + somatoriaSimNotas / somatoriaSimilaridades);
    else
        printf("DI ");
    
}
