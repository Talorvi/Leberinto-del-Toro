#pragma once

#include "config.h"

typedef struct {
    int labyrinth[WIDTH+1][HEIGHT+1]; //deklaracja labiryntu o wymiarach x, y. Dla pola: 0- powietrze, 1- œciana
    int elements[WIDTH+1][HEIGHT+1]; //elementy stałe
    int actX, actY; //aktualna pozycja
    int zmiennaX, zmiennaY; //pomocnicze zmienne x, y
    int vis;//czy labirynt już jest cały zwiedzony
    int done;//czy wykonał jakieś zadanie, czy nie
    int endGame; //czy jest koniec gry
    int exitX, exitY; //pozycja wyjścia
    int firstTime;
    int language;
} GameBoard;

typedef struct{
    char name[32];
    int pozX, pozY;
    int key;
} Player;

typedef struct{
    int pozX, pozY, lastDir;
} Minotaur;

typedef struct{
    int pozX, pozY, prvX, prvY;
} Key;

void putLabXY( int x, int y, unsigned char z, Player *p );
void createEmptyLabyrinth(GameBoard *t);
void checkIfAllVisited(GameBoard *t);
void lookForActualPosition(GameBoard *t);
void digging(GameBoard *t, Player *p, Minotaur *m);
void hunting(GameBoard *t, Player *p, Minotaur *m);
void createMaze(GameBoard *t, Player *p, Minotaur *m);
void drawGameTable(GameBoard *t, Player *p, Minotaur *m, Key *k);
