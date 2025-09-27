#include "Enemigos.h"
#include "Jugador.h"
#include "shoot.h"
#include "funciones.h"
#include "VarGlobs.h"
using namespace std;

int main (int argc, char *argv[]) {
	Menu();
	BordesMapa();
	
	Enemigo* enemigos[24];
	IniEnemigos(enemigos);
	DibEnemigos(enemigos, 24);
	
	jugador j1(26,bordeInf);
	j1.jMove(0);
	HUD(j1);	
	
	shoot sh1(1,1,0);
	shoot sh2(1,1,0);
	
	Timers();
	
	Loop(j1,enemigos,sh1,sh2);
	
	return 0;
}

