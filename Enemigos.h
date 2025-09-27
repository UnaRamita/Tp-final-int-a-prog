#pragma once
#include "VarGlobs.h"
using namespace std;

class Enemigo{
protected:
	int velocidad;
	int color;
	int x;
	int y;
	char forma;
	
	void borrar();
	void dibujar();
	void shoot();
	
public:
	
	Enemigo(int cX,int cY);
	void move(int mX, int mY);
	void dead ();
	
	bool act = true;
	bool actShooter=false;
	
	int points;
	int getX(){return x;}
	int getY(){return y;}
};

class EnemigoH : public Enemigo{
public:
	EnemigoH(int x, int y);
};

class EnemigoM : public Enemigo{	
public:
	EnemigoM(int x, int y);
};

class EnemigoW : public Enemigo{
public:
	EnemigoW(int x, int y);
};
