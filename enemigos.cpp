#include "Enemigos.h"

Enemigo::Enemigo(int cX,int cY){
	x = cX;
	y = cY;
}
EnemigoH::EnemigoH(int x,int y) : Enemigo(x,y) {
	forma = 'H';
	color = 5;
	points = 100;
	actShooter=true;
}

EnemigoM::EnemigoM(int x,int y) : Enemigo(x,y) {
	forma = 'M';
	color = 10;
	points = 200;
}

EnemigoW::EnemigoW(int x,int y) : Enemigo(x,y) {
	forma = 'W';
	color = 12;
	points = 300;
}

void Enemigo::borrar(){
	gotoxy (x,y);
	cout << ' ';
}
void Enemigo::dibujar(){
	gotoxy(x,y);
	textcolor(color);
	cout<< forma;
}

void Enemigo::move(int mX, int mY){ 
	if (act==true){
		borrar();
		x = x+mX;
		y = y+mY;
		dibujar();
	}
}

void Enemigo::dead(){ 		
	borrar();
	act = false;
}
