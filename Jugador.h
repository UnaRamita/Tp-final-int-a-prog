#pragma once
#include "VarGlobs.h"
using namespace std;

class jugador{	
private:
	int jHp=3;
	char forma='A';
	int color = 2;
	int JmoveX;
	int x;
	int y; 
	int points = 0;
	
	void borrar();
	void dibujar();
public:
	jugador(int jX, int jY);
	
	void setJhp(int h){jHp+=h;}
	int getJhp(){return jHp;}
	
	int getX(){return x;}
	
	void setPoints(int h){points+=h;}
	int getPoints(){return points;}
	
	void jMove(int mX);
	
};
