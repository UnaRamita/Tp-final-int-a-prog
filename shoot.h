#pragma once
#include "Jugador.h"
#include "Enemigos.h"
#include "VarGlobs.h"
using namespace std;

class shoot{
private:
	char forma = '|';
	
	int color=1;
	int moveY;
	int x;
	int y;
	
	bool act = false;
	
	void borrar();
	void dibujar();
public:
	shoot( int shX, int shY, int shDmove);
	
	bool activo(){return act;}
	
	void shMove (int moveY);	
	void spawn (int shX, int shY);
	void collision(Enemigo*enemigos[],int n,jugador& j1);
};
