#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <conio2.h>
using namespace std;
//bordes
const int bordeSup = 3;
const int bordeIzq = 1;
const int bordeDer = 43;
const int bordeInf = 63;
//la idea de este bool es que cuando un enemigo toque el borde cambien todos de direccion
bool borde=false;
bool cMborde=false;
//a ver si esto soluciona el problema del movimiento en bloque
int moveX;
int moveY;

//clases principal y subclase de enemigos
class Enemigo{
protected:
	int hp = 1; //vida
	int velocidad;
	//int moveX;// movimiento en eje x
	//int moveY;// movimiento en eje y
	int color;
	int x;
	int y;
	char forma;
	clock_t rit;//tics
	clock_t countR;//contador de tics
	//los voids los aclaro mas adelante
	void borrar();
	void dibujar();
	void move();
	void shoot();
public:
	Enemigo(int cX,int cY, int vel); // posicion del Enemigo// ese vel dsp sacarlo, es para probar velocidades dsp lo dejo ya puesto en el construct
	void behavior();
};
// Enemigos forma color y puntos(puntos no se si lo voy a dejar vere cuando haga el sistema de puntos)
class EnemigoH : public Enemigo{
public:
	EnemigoH(int x, int y);
	int getPoints() {return points;}
	//char forma = 'H';
	int points = 100;
	//int color = 5;
};

class EnemigoM : public Enemigo{	
public:
	EnemigoM(int x, int y);
	//char forma = 'M';
	int points = 200;
	//int color = 10;
};

class EnemigoW : public Enemigo{
public:
	//char forma = 'W;
	//int color = 12;
	
	int points = 300;
    EnemigoW(int x, int y);
};
//Clase jugador (saque los puntos ed jugador, no se si contarlos aparte o no lo vere dsp)		
class jugador{	
private:
	int jHp=3;
	char jForma='A';
	int color = 2;
	int moveX;
	int moveY;
	int x,y;
	//despues probar si al jugador me conviene hacerle voids a parte con otros nombres o es indiferente
	void borrar();
	void dibujar();
	void move();
	void jShoot();
public:
	
	void setJhp(int h){jHp=h;}
	int getJhp(){return jHp;}
	
	jugador(int velocidad);
	
};
//	
//aca van los contrctr (por el momento lo primero va a ser hacer un enemigo y hacerle el comportamiento, despes vere de)
//
Enemigo::Enemigo(int cX,int cY, int vel){
	velocidad= vel; //velocidad de prueba, despues probar
	moveX=1;
	moveY=0;
	x = cX;
	y = cY;
	
	
	//estos 2 chequearlos por que creo q entendi lo que hacen pero no estoy 100 seguro
	rit= CLOCKS_PER_SEC/velocidad;
	countR=clock();
	//
	
}
EnemigoH::EnemigoH(int x,int y) : Enemigo(x,y,1) {
	forma = 'H';
	color = 5;
}

EnemigoM::EnemigoM(int x,int y) : Enemigo(x,y,1) {
	forma = 'M';
	color = 10;
}

EnemigoW::EnemigoW(int x,int y) : Enemigo(x,y,1) {
	forma = 'W';
	color = 12;
}

void Enemigo::borrar(){
	gotoxy (x,y); //coordenadas a dibujar(con un espacio en blanco)
	cout << ' ';
}
void Enemigo::dibujar(){
gotoxy(x,y);
textcolor(color);
cout<< forma;
}
void Enemigo::move(){
	
	if (moveX==1 && moveY ==0){
		x++;
		cMborde=false;
	}
	else if (moveX==-1 && moveY==0){
		x--;
		cMborde=false;
	}
	else if(moveY==1 && cMborde==false){
		y++;
		moveY=0;
		cMborde=true;
	}
}
void Enemigo::behavior(){
	if(rit+countR<clock()){
		
		borrar();
		move();
		dibujar();
		
		
		//borde
		if (x==bordeIzq+1 || x==bordeDer-1){
			borde=true;
		}
		else {borde=false;}
		//baja uno
		if (borde==true && cMborde==false){
			moveY=1;
		}
		else{moveY=0;}
		//cambio de direccion dsp de hacer lo anterior
		if (moveX ==1 && borde==true && cMborde==true){
			moveX= -1;
		}
		else if (moveX ==-1 && borde==true && cMborde==true){
			moveX= 1;
		}
		
		countR = clock();//importante xd
	}
}

int main (int argc, char *argv[]) {
	EnemigoM *em1= new EnemigoM(2,4);
	EnemigoH *em2= new EnemigoH(2,6);
	while(true){
		em1 ->behavior();
		em2 ->behavior();
	}
	
	return 0;
}

