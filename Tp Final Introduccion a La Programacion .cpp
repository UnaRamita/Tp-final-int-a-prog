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
const int bordeDer = 43;
const int bordeInf = 29;




clock_t rit;
clock_t countR;



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
	
	Enemigo(int cX,int cY, int vel); // posicion del Enemigo// ese vel dsp sacarlo, es para probar velocidades dsp lo dejo ya puesto en el construct
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
//Clase jugador (saque los puntos ed jugador, no se si contarlos aparte o no lo vere dsp)		
class jugador{	
private:
	int jHp=3;
	char jForma='A';
	int color = 2;
	int JmoveX;
	int moveY;
	int x,y;
	//despues probar si al jugador me conviene hacerle voids a parte con otros nombres o es indiferente
	void borrar();
	void dibujar();
	void jmove();
	void jShoot();
public:
	
	void setJhp(int h){jHp=h;}
	int getJhp(){return jHp;}
	
	jugador(int velocidad);
	
};

Enemigo::Enemigo(int cX,int cY, int vel){
	velocidad= vel; //velocidad de prueba, despues probar
	x = cX;
	y = cY;
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

void Enemigo::move(int mX, int mY){ //la idea de eso seria en el behavior decirle directamente que se muevan en el eje x o en el y
	borrar();
	x = x+mX;
	y = y+mY;
	dibujar();
}
//Void general, lista de enemigos y n es el numero de enemigos
void behavior(Enemigo*enemigos[],int n){ // viendo que esto no fuciono como esperaba voy a cambiarlo por un comportamiento centralizado que le diga a todos los enemigos como moverse
	
	static int moveX= 1;
	
	static bool down = false;
	static bool edgeD=false;
	
	int enemigoR = INT_MIN;
	int enemigoL = INT_MAX;	
	
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
	//cuando itere si tocamos borde en la anterior iteracion baja
	if(down== true){
	 
		for(int i=0; i<n; i++){
			enemigos[i]-> move(0,1);
		}
		moveX = -moveX;//cambia la diereccion del movimiento
		down = false;
		edgeD = false;
		countR = clock();//REINICIA EL CONTADOR, tengo que dejar de olvidarme esto
		return;
	}

	//si no estan sobre un borde se mueven en la direccion de moveX
	if (moveX==1 && down== false){
		for (int i=0; i<n; i++){
			enemigos[i]-> move(1,0);
		}
	}
	else if (moveX==-1){
		for(int i=0;i<n;i++){
			enemigos[i]-> move(-1,0);
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
	countR = clock();//REINICIA EL CONTADOR, tengo que dejar de olvidarme esto
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
		gotoxy (bordeIzq-2,y);
		cout<<"|";
	}
	for(int y = bordeSup; y <= bordeInf; y++){
		gotoxy (bordeDer+1,y);
		cout<<"|";
	}
	//orden de enemigos W arriba, M medio ,H abajo
	//x y
    Enemigo* enemigos[3]; //puebo con 3 uno de cada tipo
	enemigos[0] = new EnemigoW (4,3);
	enemigos[1] = new EnemigoM (6,5);
	enemigos[2] = new EnemigoH (8,7);
	
	//dibuja en posicion inicial
	for(int i=0;i<3;i++){
		enemigos[i]->move(0,0); 
	}
	
	rit = CLOCKS_PER_SEC/3; //uno con lo que vario la velocidad podria poner una variable para cambiarlo pero por ahora va a quedar asi
	countR = clock();

	while(true){
		//no se si ponerlo aca, provare
		if (rit+countR<clock()){
			behavior(enemigos,3);
		}
	}
	
	return 0;
}

