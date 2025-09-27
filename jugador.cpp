#include "Jugador.h"
#include "VarGlobs.h"

jugador::jugador(int jX,int jY){
	x = jX;
	y = jY;
}
void jugador::borrar(){
	gotoxy (x,y); 
	cout << ' ';
}
void jugador::dibujar(){
	gotoxy(x,y);
	textcolor(color);
	cout<< forma;
}

void jugador::jMove(int mX){
	if(x==bordeDer && mX == 1){return;}
	else if(x==bordeIzq && mX == -1){return;}
	borrar();
	x = x+mX;
	dibujar();
	jCountR = clock();
}
