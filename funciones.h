#pragma once
#include "Enemigos.h"
#include "Jugador.h"
#include "shoot.h"
#include "VarGlobs.h"

using namespace std;

void Menu();
void HUD(jugador& j1);
void BordesMapa();
void Victoria(jugador& j1);
void Derrota(jugador& j1);

void IniEnemigos(Enemigo* enemigos[]);
void DibEnemigos(Enemigo* enemigos[], int n);
Enemigo* SelectShooter(Enemigo* enemigos[]);
void behavior(Enemigo* enemigos[], int n, shoot& sh2);

void Timers();
void Loop(jugador& j1, Enemigo* enemigos[], shoot& sh1, shoot& sh2);
