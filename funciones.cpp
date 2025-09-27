#include "funciones.h"
#include "shoot.h"
#include "VarGlobs.h"

Enemigo*SelectShooter(Enemigo*enemigos[]){
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

	
void IniEnemigos(Enemigo* enemigos[]){
	//EnemigoW
	enemigos[0] = new EnemigoW(4, 3);
	enemigos[1] = new EnemigoW(8, 3);
	enemigos[2] = new EnemigoW(12, 3);
	enemigos[3] = new EnemigoW(16, 3);
	enemigos[4] = new EnemigoW(20, 3);
	enemigos[5] = new EnemigoW(24, 3);
	enemigos[6] = new EnemigoW(28, 3);
	enemigos[7] = new EnemigoW(32, 3);
	
	//EnemigoM
	enemigos[8] = new EnemigoM(4, 5);
	enemigos[9] = new EnemigoM(8, 5);
	enemigos[10] = new EnemigoM(12, 5);
	enemigos[11] = new EnemigoM(16, 5);
	enemigos[12] = new EnemigoM(20, 5);
	enemigos[13] = new EnemigoM(24, 5);
	enemigos[14] = new EnemigoM(28, 5);
	enemigos[15] = new EnemigoM(32, 5);
	
	//EnemigoH
	enemigos[16] = new EnemigoH(4, 7);
	enemigos[17] = new EnemigoH(8, 7);
	enemigos[18] = new EnemigoH(12, 7);
	enemigos[19] = new EnemigoH(16, 7);
	enemigos[20] = new EnemigoH(20, 7);
	enemigos[21] = new EnemigoH(24, 7);
	enemigos[22] = new EnemigoH(28, 7);
	enemigos[23] = new EnemigoH(32, 7);
}
void DibEnemigos(Enemigo* enemigos[], int n) {
	for (int i = 0; i < n; i++) {
		enemigos[i]->move(0, 0);
	}
	}
void Timers() {
	rit = CLOCKS_PER_SEC / 1;
	countR = clock();
	
	jRit = CLOCKS_PER_SEC / 5;
	jCountR = clock();
	
	shRit = CLOCKS_PER_SEC / 10;
	shCountR = clock();
	
	shErit = CLOCKS_PER_SEC / 10;
	shEcountR = clock();
}
void behavior(Enemigo*enemigos[],int n, shoot& sh2){
	static int moveX= 1;
	
	static bool down = false;
	static bool edgeD=false;
	
	int enemigoR = INT_MIN;
	int enemigoL = INT_MAX;	
	
	if(down== true){
		
		for(int i=0; i<n; i++){
			enemigos[i]-> move(0,1);
		}
		moveX = -moveX;
		down = false;
		edgeD = false;
		countR = clock();
		
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
	
	if (moveX==1 && down== false){
		for (int i=0; i<n; i++){
			enemigos[i]-> move(1,0);
		}
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
	
	getch();
	clrscr(); 
	}	
void HUD(jugador& j1){
	gotoxy(4,1);
	cout<<"Hp "<<j1.getJhp();
	
	gotoxy(12,1);
	cout<<"Points "<<j1.getPoints();
}
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
	
	void Loop(jugador& j1, Enemigo* enemigos[], shoot& sh1, shoot& sh2) {
		while (!pEnd) {
			if (rit + countR < clock()) {
				behavior(enemigos, 24, sh2);
				countR = clock();
			}
			
			if (kbhit()) { ad = _getch(); }
			if (jRit + jCountR < clock()) {
				if (ad == 'd') j1.jMove(1);
				if (ad == 'a') j1.jMove(-1);
			}
			
			if (kbhit()) { shKey = _getch(); }
			if (shRit + shCountR < clock()) {
				if (shKey == ' ' && sh1.activo() == false) {
					sh1.spawn(j1.getX(), bordeInf - 1);
					sh1.shMove(-1);
					shCountR = clock();
				}
				else if (sh1.activo() == true) {
					sh1.shMove(-1);
					sh1.collision(enemigos, 24, j1);
					shCountR = clock();
				}
			}
			
			if (shErit + shEcountR < clock()) {
				if (sh2.activo() == true) {
					sh2.shMove(1);
					sh2.collision(enemigos, 24, j1);
					shEcountR = clock();
				}
			}
			
			ad = 'p';
			shKey = 'p';
			
			for (int i = 0; i < 24; i++) {
				if (enemigos[i]->getY() == bordeInf) {
					Derrota(j1);
					pEnd = true;
				}
			}
			if (j1.getPoints() >= 4800) {
				Victoria(j1);
				pEnd = true;
			}
			if (j1.getJhp() <= 0) {
				Derrota(j1);
				pEnd = true;
			}
		}
	}
	
void Victoria(jugador& j1) {
	clrscr();
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
	
	getch();
}
void Derrota(jugador& j1) {
	clrscr();
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
	
	getch();	
}
