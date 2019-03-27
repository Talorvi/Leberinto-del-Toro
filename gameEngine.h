#pragma once

#include <time.h>
#include <windows.h>

#include "config.h"
#include "gameTable.h"

void initGame(GameBoard *t, Player *p, Minotaur *m, Key *k);
int losuj(int liczbaOd, int liczbaDo);
void playerMovement(GameBoard *t, Player *p, char c);
void minotaurMovement(GameBoard *t, Minotaur *m, Key *k, Player *p);
void playerFoundKey(GameBoard *t, Player *p, Minotaur *m, Key *k);
void checkIfEndGame(GameBoard *t, Player *p);
int gameEngine(GameBoard *t, Player *p, Minotaur *m, Key *k);
