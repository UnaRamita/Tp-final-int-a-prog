#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <conio2.h>
using namespace std;
//bordes
const int bordeSup = 3;
const int bordeIzq = 3;
const int bordeDer = 54;
const int bordeInf = 29;

clock_t rit;
clock_t countR;

clock_t jRit;
clock_t jCountR;

clock_t shRit;
clock_t shCountR;

char ad;
char shKey;

bool shJ = false;
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
	/* aca estaban las variables
	clock_t rit;
	clock_t countR
	dsp revisar que no me quede nada de codigo de esto colgado por ahi esto incluye la velocidad que tenian puesta los enemigos
	*/
	//los voids los aclaro mas adelante
	void borrar();
	void dibujar();
	void shoot();
	
public:
	
	Enemigo(int cX,int cY); // posicion del Enemigo// ese vel dsp sacarlo, es para probar velocidades dsp lo dejo ya puesto en el construct
	void move(int mX, int mY);
	int getX(){return x;}
	int getY(){return y;}// por el momento lo agrego de onda, no se si lo voy a usar
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
Enemigo::Enemigo(int cX,int cY){
	x = cX;
	y = cY;
}
EnemigoH::EnemigoH(int x,int y) : Enemigo(x,y) {
	forma = 'H';
	color = 5;
}

EnemigoM::EnemigoM(int x,int y) : Enemigo(x,y) {
	forma = 'M';
	color = 10;
}

EnemigoW::EnemigoW(int x,int y) : Enemigo(x,y) {
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

void Enemigo::move(int mX, int mY){ //la idea de eso seria en el behavior decirle directamente que se muevan en el eje x o en el y
	borrar();
	x = x+mX;
	y = y+mY;
	dibujar();
}
//Clase jugador (saque los puntos ed jugador, no se si contarlos aparte o no lo vere dsp)		
class jugador{	
private:
	int jHp=3;
	char forma='A';
	int color = 2;
	int JmoveX;
	int x;
	int y; 
	
	void borrar();
	void dibujar();
	void jShoot();
public:
	jugador(int jX, int jY);
	
	void setJhp(int h){jHp=h;}
	int getJhp(){return jHp;}
	int getX(){return x;}
	
	void jMove(int mX);
	
};

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
class shoot{
private:
	char forma = '|';
	
	int color=1;
	int moveY;
    int x;
	int y;
	
	bool act = true;
	
	void borrar();
	void dibujar();
public:
	shoot( int shX, int shY, int shDmove);
	
	void shMove (int moveY);
	
};

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
	borrar();
	y = y+moveY;
	dibujar();
	shCountR = clock();
	if(y == bordeSup){
		borrar();
		shJ=false;
	}
	
}

//Void general, lista de enemigos y n es el numero de enemigos
void behavior(Enemigo*enemigos[],int n){
	
	static int moveX= 1;
	
	static bool down = false;
	static bool edgeD=false;
	
	int enemigoR = INT_MIN;
	int enemigoL = INT_MAX;	
	
	//cuando itere si tocamos borde en la anterior iteracion baja
	if(down== true){
	 
		for(int i=0; i<n; i++){
			enemigos[i]-> move(0,1);
		}
		moveX = -moveX;//cambia la diereccion del movimiento
		down = false;
		edgeD = false;
		countR = clock();//REINICIA EL CONTADOR para que baje y no se mueva enseguida dsp
		
		//detectar la coordenada x de el enemigo mas a la izq y a la derecha.
		for (int i=0; i<n; i++){
			int x= enemigos[i]-> getX();	
			if (x < enemigoL){
				enemigoL=x;
			}
			if (x > enemigoR){
				enemigoR=x;
			}
		}
		
		return;
	}

	//si no estan sobre un borde se mueven en la direccion de moveX
	if (moveX==1 && down== false){
		for (int i=0; i<n; i++){
			enemigos[i]-> move(1,0);
		}
		//detectar la coordenada x de el enemigo mas a la izq y a la derecha.
		for (int i=0; i<n; i++){
			int x= enemigos[i]-> getX();	
			if (x < enemigoL){
				enemigoL=x;
			}
			if (x > enemigoR){
				enemigoR=x;
			}
		}
	}
	else if (moveX==-1){
		for(int i=0;i<n;i++){
			enemigos[i]-> move(-1,0);
		}
		//detectar la coordenada x de el enemigo mas a la izq y a la derecha.
		for (int i=0; i<n; i++){
			int x= enemigos[i]-> getX();	
			if (x < enemigoL){
				enemigoL=x;
			}
			if (x > enemigoR){
				enemigoR=x;
			}
		}
	}
	// si estamos en un borde pone edgeD en true y eso pone down en true;
	if (enemigoL == bordeIzq){
		edgeD=true;
	}
	else if (enemigoR == bordeDer){
		edgeD=true;
	}
	else {edgeD=false;}

	if (edgeD==true){
		down=true;
	}
}

int main (int argc, char *argv[]) {

	
	for(int x = bordeIzq; x <= bordeDer; x++){
		gotoxy(x,bordeSup -1);
		cout <<"-";
	}
	for(int x = bordeIzq; x <= bordeDer; x++){
		gotoxy(x,bordeInf +1);
		cout <<"-";
	}
	for(int y = bordeSup; y <= bordeInf; y++){
		gotoxy (bordeIzq-1,y);
		cout<<"|";
	}
	for(int y = bordeSup; y <= bordeInf; y++){
		gotoxy (bordeDer+1,y);
		cout<<"|";
	}
	//orden de enemigos W arriba, M medio ,H abajo
	//x y
	Enemigo* enemigos[24]; 
	
	// Fila de EnemigoW (arriba)
	enemigos[0] = new EnemigoW(4,3);
	enemigos[1] = new EnemigoW(8,3);
	enemigos[2] = new EnemigoW(12,3);
	enemigos[3] = new EnemigoW(16,3);
	enemigos[4] = new EnemigoW(20,3);
	enemigos[5] = new EnemigoW(24,3);
	enemigos[6] = new EnemigoW(28,3);
	enemigos[7] = new EnemigoW(32,3);
	
	// Fila de EnemigoM (al medio)
	enemigos[8] = new EnemigoM(4,5);
	enemigos[9] = new EnemigoM(8,5);
	enemigos[10] = new EnemigoM(12,5);
	enemigos[11] = new EnemigoM(16,5);
	enemigos[12] = new EnemigoM(20,5);
	enemigos[13] = new EnemigoM(24,5);
	enemigos[14] = new EnemigoM(28,5);
	enemigos[15] = new EnemigoM(32,5);
	
	// Fila de EnemigoH (abajo)
	enemigos[16] = new EnemigoH(4,7);
	enemigos[17] = new EnemigoH(8,7);
	enemigos[18] = new EnemigoH(12,7);
	enemigos[19] = new EnemigoH(16,7);
	enemigos[20] = new EnemigoH(20,7);
	enemigos[21] = new EnemigoH(24,7);
	enemigos[22] = new EnemigoH(28,7);
	enemigos[23] = new EnemigoH(32,7);	
	
	//dibuja en posicion inicial
	for(int i=0;i<24;i++){
		enemigos[i]->move(0,0); 
	}
	
	jugador j1(26,bordeInf);
	j1.jMove(0);
	
	shoot sh1(j1.getX(),bordeInf-1,0);
	
	rit = CLOCKS_PER_SEC/1; //uno es con lo que vario la velocidad podria poner una variable para cambiarlo pero por ahora va a quedar asi
	countR = clock();
	
	jRit = CLOCKS_PER_SEC/3;
	jCountR = clock();	
	//dsp capaz cambio esto para el disparo
	shRit = CLOCKS_PER_SEC/5;
	shCountR = clock();
	while(true){
		
		if (rit+countR<clock()){
			behavior(enemigos,24);
			countR = clock();
		}
		
		if(knhit()){
		    ad = _getch();
		}
		
		if (jRit+jCountR<clock()){
			if (ad == 'd'){
				j1.jMove(1);
			}
			if(ad== 'a'){
				j1.jMove(-1);
			}
		}
		
		if(knhit()){
			shKey=_getch();
		}
		
		if(shRit+shCountR<clock()){
			if (shKey == ' ' && shJ == false){
				shoot sh1(j1.getX(),bordeInf-1,0);
				sh1.shMove(-1);
				shJ=true;
			}
			else if (shJ==true){
				sh1.shMove(-1);
			}
			
		}
	}
	
	return 0;
}

