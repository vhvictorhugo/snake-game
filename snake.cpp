#include "snake.h"

int main(){
	inicializa();
	while(!fimdojogo) {
		desenha();
		entrada();
		logica();
	}	
	finaliza();
}