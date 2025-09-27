#include "Shoot.h"
#include "Jugador.h"
#include "Enemigos.h"
#include "VarGlobs.h"

shoot::shoot(int shX, int shY, int shDmove){
	x = shX;
	y = shY;
	moveY = shDmove;
}

void shoot::borrar(){
	gotoxy (x,y); 
	cout << ' ';
}
void shoot::dibujar(){
	gotoxy(x,y);
	textcolor(color);
	cout<< forma;
}
void shoot::shMove(int moveY){
	if(y <= bordeSup){
		borrar();
		act = false;
	}
	if(y >= bordeInf){
		borrar();
		act = false;
	}
	if (act == true){
		borrar();
		y = y+moveY;
		dibujar();
	}
}
void shoot::spawn(int shX,int shY){
	borrar();
	x = shX;
	y = shY;
	dibujar();
	act=true;
}
void shoot::collision(Enemigo*enemigos[],int n, jugador& j1){
	if(act==true){
		for (int i=0; i<n; i++){
			if (enemigos[i]->act==true && enemigos[i]->getX()==x && enemigos[i]->getY()==y){
				enemigos[i]->dead();
				borrar();
				act=false;
				j1.setPoints(enemigos[i]->points);
				textcolor(2);
				gotoxy(12,1);
				cout<<"Points "<<j1.getPoints();
			}
		}
		if(j1.getX()==x && y== bordeInf){
			j1.setJhp(-1);
			borrar();
			act=false;
			textcolor(2);
			gotoxy(4,1);
			cout<<"Hp "<<j1.getJhp();
		}
	}
}
