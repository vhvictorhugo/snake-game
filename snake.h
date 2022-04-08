#include <stdio.h>
#include <stdlib.h>
// contém funções próprias para capturar o teclado sem a necessidade da tecla enter
#include <conio.h>
// usaremos uma semente para mostrar as frutinhas na tela em diferentes "tempos"
#include <time.h>
#include <string.h>

// direções
#define STOP 0
#define ESQD 1
#define DIRT 2
#define CIMA 3
#define BAIX 4
// os valores dos defines abaixo representam caracteres específicos na tabela ASCII
#define MURO 178
#define COBR 219
#define FRUT 149

int fimdojogo = 0;
// definição do tabuleiro
const int largura = 20;
const int altura = 20;
// posicao da cobra
int x, y;
// posicao de uma fruta
int frutax, frutay;
// características do game (pontuação e direção de movimento)
int pontos, direcao;
// corpo da cobra
int rcobrax[100], rcobray[100];
// tamanho do resto da cobra
int tamrcobra;

// inicializa o jogo
void inicializa() {
	time_t t;

	fimdojogo = 0;	// falso
	direcao = STOP;
	x = largura / 2;
	y = altura / 2;
	pontos = 0;

	// cria semente para aquela execução
	srand(time(&t));

	frutax = rand() % largura + 1;
	frutay = rand() % altura + 1;

	tamrcobra = 0;
}
// apresentação da interface para o usuário
void desenha() {
	// limpa a tela no windows
	system("cls");

	// primeira linha
	for (int i = 0; i <= largura + 2; i++) {
		// char(MURO) efetua o typecast do inteiro 178 para caracter
		printf("%c", char(MURO));
	}

	for (int j = 1; j <= altura + 1; j++) {
		printf("\n");
		for (int i = 0; i <= largura + 2; i++) {
			if (i == 0 || i == largura + 2) {
				printf("%c", char(MURO));
			}
			else {
				if (i == x && j == y) {
					printf("%c", char(COBR));
				}
				else if (i == frutax && j == frutay) {
					printf("%c", char(FRUT));
				}
				else {
					int flag = 0;	// falso para mostrar a cobra
					// laço para mostrar o corpo da cobra
					for (int k = 0; k < tamrcobra; k++){
						if (rcobrax[k] == i && rcobray[k] == j) {
							printf("%c", char(COBR));
							flag = 1;	// o corpo da cobra foi mostrado
						}
					}
					if(!flag)
						printf(" ");
				}
			}
		}
	}
	printf("\n");
	// última linha
	for (int i = 0; i <= largura + 2; i++) {
		// char(MURO) efetua o typecast do inteiro 178 para caracter
		printf("%c", char(MURO));
	}
	printf("\npontos = %d", pontos);
}
// captura os dados digitados pelo usuário
void entrada() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			direcao = CIMA;
			break;
		case 'W':
			direcao = CIMA;
			break;
		case 'a':
			direcao = ESQD;
			break;
		case 'A':
			direcao = ESQD;
			break;
		case 's':
			direcao = BAIX;
			break;
		case 'S':
			direcao = BAIX;
			break;
		case 'd':
			direcao = DIRT;
			break;
		case 'D':
			direcao = DIRT;
			break;
		case 'x':
			fimdojogo = 1;
			break;
		case 'X':
			fimdojogo = 1;
			break;
			// pro caso do usuário usar as setas do teclado
		case 224:
			if (_kbhit()) {
				switch (_getch()) {
				case 72:
					direcao = CIMA;
					break;
				case 75:
					direcao = ESQD;
					break;
				case 80:
					direcao = BAIX;
					break;
				case 77:
					direcao = DIRT;
					break;
				}
			}
		}
	}
}
// executa a logica do jogo
void logica() {
	int rcantx = rcobrax[0];
	int rcanty = rcobray[0];
	int auxx, auxy;

	rcobrax[0] = x;
	rcobray[0] = y;
	for (int i = 1; i < tamrcobra; i++){
		auxx = rcobrax[i];
		auxy = rcobray[i];
		rcobrax[i] = rcantx;
		rcobray[i] = rcanty;
		rcantx = auxx;
		rcanty = auxy;
	}
	switch (direcao) {
	case CIMA:
		y--;
		break;
	case ESQD:
		x--;
		break;
	case BAIX:
		y++;
		break;
	case DIRT:
		x++;
		break;
	case STOP:
		direcao = rand() % 4 + 1;	// seleciona uma direcao aleatoria
		break;
	}

	// lógica quando a cobra encontra com as paredes
	if (x == 0 || x == largura + 2 || y == 0 || y == altura + 2) {
		fimdojogo = 1;
	}
	// lógica quando a cobra encontra seu corpo
	for (int i = 0; i < tamrcobra; i++){
		if (rcobrax[i] == x && rcobray[i] == y) {
			fimdojogo = 1;
		}
	}
	// lógica quando a cobra encontra a fruta
	if (x == frutax && y == frutay) {
		pontos += 10;
		frutax = rand() % largura + 1;
		frutay = rand() % largura + 1;
		tamrcobra++;
	}
}
// finaliza o jogo
void finaliza() {
	system("cls");
	printf("\n\n\n*** FIM DE JOGO ***\n\n\nSua pontuacao foi: %d\n\n", pontos);
}