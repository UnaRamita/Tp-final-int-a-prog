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

	int eShCount=0;

	clock_t rit;
	clock_t countR;

	clock_t jRit;
	clock_t jCountR;

	clock_t shRit;
	clock_t shCountR;

	clock_t shErit;
	clock_t shEcountR;

	char ad;
	char shKey;

	bool pEnd= false;

	//clases principal y subclase de enemigos

	class Enemigo{
		protected:
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
		void dead ();
		
		bool act = true;
		bool actShooter=false;
		
		int points;
		int getX(){return x;}
		int getY(){return y;}
	};
	// Enemigos forma color y puntos(puntos no se si lo voy a dejar vere cuando haga el sistema de puntos)
	class EnemigoH : public Enemigo{
	public:
		EnemigoH(int x, int y);
		//char forma = 'H';
		//int color = 5;
	};

	class EnemigoM : public Enemigo{	
	public:
		EnemigoM(int x, int y);
		//char forma = 'M';
		//int color = 10;
	};

	class EnemigoW : public Enemigo{
	public:
		//char forma = 'W;
		//int color = 12;
		EnemigoW(int x, int y);
	};
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
		gotoxy (x,y); //coordenadas a dibujar(con un espacio en blanco)
		cout << ' ';
	}
	void Enemigo::dibujar(){
			gotoxy(x,y);
			textcolor(color);
			cout<< forma;
	}

	void Enemigo::move(int mX, int mY){ //la idea de eso seria en el behavior decirle directamente que se muevan en el eje x o en el y
		if (act==true){
			borrar();
			x = x+mX;
			y = y+mY;
			dibujar();
		}
	}
	//esto y que este en publico es para que el disparo corrobore si esta colisionando con un Enemigo en la posicion en la que esta y llame a esto y tmb se elimine a si mismo
	void Enemigo::dead(){ 		
		borrar();
		act = false;
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
		int points = 0;
		
		void borrar();
		void dibujar();
		void jShoot();
	public:
		jugador(int jX, int jY);
		
		void setJhp(int h){jHp+=h;}
		int getJhp(){return jHp;}
		
		int getX(){return x;}
		
		void setPoints(int h){points+=h;}
		int getPoints(){return points;}
		
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
	  Enemigo*SelectShooter(Enemigo*enemigos[]){
		//la idea para los disparos va a ser recorrer la fila de enfrente y si no estan muertos agregarlos a los que pueden disparar, en caso contrario 
		//ir al enemigo anterior en la columna que por como los organize esta 8 puestos atras en la lista.
		Enemigo*pShooter[8];
		int Count=0;
		
		for (int i=16; i<24;i++){
			Enemigo* tem = enemigos[i];
			if(tem->act==false){
				tem=enemigos[i-8];
				if (tem->act==false){
					tem=enemigos[i-16];
				}
			}
			if(tem->act==true){
				pShooter[Count]=tem;
				Count++;
			}
		}
		int pSh = rand()%Count;
		return pShooter[pSh];
	}
	//Void general, lista de enemigos y n es el numero de enemigos
	void behavior(Enemigo*enemigos[],int n, shoot& sh2){
		
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
				if(enemigos[i]->act==true){
					int x= enemigos[i]-> getX();
					if (x < enemigoL){
						enemigoL=x;
					}
					if (x > enemigoR){
						enemigoR=x;
					}
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
				if(enemigos[i]->act==true){
					int x= enemigos[i]-> getX();
					if (x < enemigoL){
						enemigoL=x;
					}
					if (x > enemigoR){
						enemigoR=x;
					}
				}
			}
		}
		else if (moveX==-1){
			for(int i=0;i<n;i++){
				enemigos[i]-> move(-1,0);
			}
			//detectar la coordenada x de el enemigo mas a la izq y a la derecha.
			for (int i=0; i<n; i++){
				if(enemigos[i]->act==true){
					int x= enemigos[i]-> getX();
					if (x < enemigoL){
						enemigoL=x;
					}
					if (x > enemigoR){
						enemigoR=x;
					}
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
		eShCount++;
		if (eShCount>=2 && sh2.activo()==false){
			Enemigo*shooter = SelectShooter(enemigos);
			sh2.spawn(shooter->getX(),shooter->getY()+1);
			eShCount=0;
		}
	}
    //Menu de incio
	void Menu(){
		textcolor(WHITE);
		gotoxy(15, 3);
		cout << "TRABAJO PRACTICO - INTRODUCCION A LA PROGRAMACION";
		
		gotoxy(15, 5);
		cout << "Alumno: Zelmar Amaru Rodriguez Droz";
		
		textcolor(LIGHTRED);
		gotoxy(20, 8);
		cout << "=== SPACE INVADERS ===";
		
		textcolor(LIGHTGREEN);
		gotoxy(10, 12);
		cout << "Controles:";
		gotoxy(12, 13);
		cout << "a -> Mover a la izquierda";
		gotoxy(12, 14);
		cout << "d -> Mover a la derecha";
		gotoxy(12, 15);
		cout << "ESPACIO -> Disparar";
		
		gotoxy(10, 17);
		cout << "Objetivo:";
		gotoxy(12, 18);
		cout << "Sobrevive, destruye a los enemigos y evita que lleguen a tu linea.";
		
		textcolor(YELLOW);
		gotoxy(15, 22);
		cout << "Presiona cualquier tecla para comenzar...";
		
		// Espera una tecla
		getch();
		clrscr(); // limpia antes de empezar el juego
	}
	
	//dibuja los bordes del mapa 
	void BordesMapa(){
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
	}

	void Victoria(jugador& j1) {
		clrscr(); // limpia la pantalla
		textcolor(LIGHTGREEN);
		
		gotoxy(20, 8);
		cout << "===== VICTORIA =====";
		
		textcolor(WHITE);
		gotoxy(18, 12);
		cout << "Has derrotado a todos los invasores!";
		
		gotoxy(18, 14);
		cout << "Puntuacion final: " << j1.getPoints();
		
		textcolor(YELLOW);
		gotoxy(15, 18);
		cout << "Gracias por jugar Space Invaders!";
		
		getch(); // espera tecla antes de salir
	}
	
	void Derrota(jugador& j1) {
		clrscr(); // limpia la pantalla
		textcolor(RED);
		
		gotoxy(20, 8);
		cout << "===== GAME OVER =====";
		
		textcolor(WHITE);
		gotoxy(18, 12);
		cout << "Has sido derrotado...";
		
		gotoxy(18, 14);
		cout << "Puntuacion final: " << j1.getPoints();
		
		textcolor(YELLOW);
		gotoxy(15, 18);
		cout << "Gracias por jugar Space Invaders!";
		
		getch(); // espera tecla antes de salir
	}

	int main (int argc, char *argv[]) {
		Menu();
		BordesMapa();
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
		
		gotoxy(4,1);
		cout<<"Hp "<<j1.getJhp();
		
		gotoxy(12,1);
		cout<<"Points "<<j1.getPoints();
		
		shoot sh1(1,1,0);
		shoot sh2(1,1,0);
		
		rit = CLOCKS_PER_SEC/1; //uno es con lo que vario la velocidad podria poner una variable para cambiarlo pero por ahora va a quedar asi
		countR = clock();
		
		jRit = CLOCKS_PER_SEC/5;
		jCountR = clock();	
		//dsp capaz cambio esto para el disparo
		shRit = CLOCKS_PER_SEC/10;
		shCountR = clock();
		
		shErit = CLOCKS_PER_SEC/10;
		shEcountR = clock();

		while(pEnd==false){
			
			if (rit+countR<clock()){
				behavior(enemigos,24,sh2);
				countR = clock();
			}
			
			if(kbhit()){
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
			
			if(kbhit()){
				shKey=_getch();
			}
			
			if(shRit+shCountR<clock()){
				if (shKey == ' ' && sh1.activo()==false){
					sh1.spawn (j1.getX(),bordeInf-1);
					sh1.shMove(-1);
					shCountR = clock();
				}
				else if (sh1.activo()==true){
					sh1.shMove(-1);
					sh1.collision(enemigos,24,j1);
					shCountR = clock();
				}
			}
			
			if(shErit+shEcountR<clock()){
				if(sh2.activo()==true){
					sh2.shMove(1);
					sh2.collision(enemigos,24,j1);
					shEcountR = clock();
				}
			}
			ad='p';
			shKey='p';
			for(int i=0; i<24;i++){//for para pasar por los enemigos
				if (enemigos[i]->getY()==bordeInf){
					Derrota(j1);
					pEnd=true;
				}
			}
			if (j1.getPoints()>=4800){
				Victoria(j1);
				pEnd=true;
			}
			if (j1.getJhp()<=0){
				Derrota(j1);
				pEnd=true;
			}
		}
		
		return 0;
}

