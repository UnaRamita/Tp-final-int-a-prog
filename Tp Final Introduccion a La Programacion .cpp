#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <conio2.h>
using namespace std;

class Enemigo{
private:
	int hp = 1;
public:
	void setHp(int h) {hp=h;}
	int getHp(){return hp;}
	
	virtual char getForma(){return' ';}
	virtual int getPoints(){return 0;}
};

class EnemigoH : public Enemigo{
private:
	char forma = 'H';
	int points = 100;
public:
	char getForma() override {return forma;}
	int getPoints() override {return points;}
};

class EnemigoM : public Enemigo{
private:
	char forma = 'M';
	int points = 200;
public:
	char getForma() override {return forma;}
	int getPoints() override {return points;}
};

class EnemigoW : public Enemigo{
private:
	char forma = 'W';
	int points = 300;
public:
	char getForma() override {return forma;}
	int getPoints() override {return points;}
};

class jugador{
private:
	int jHp=3;
	int jPoints=0;
	char jForma='A';
public:
	
	void setJhp(int h){jHp=h;}
	int getJhp(){return jHp;}
	
	void setJpoints(int p){jPoints=p;}
	int getJpoints(){return jPoints;}
	
};
int main (int argc, char *argv[]) {
	
	
	return 0;
}

