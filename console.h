#pragma once

#include <windows.h>
#include <conio.h>


void setActiveColor( unsigned short k );
void initScreen();
void setConsole(int x, int y);
void putCharXY(int x, int y, unsigned char z);
void putIntXY(int x, int y, unsigned int z);
void putStrXY(int x, int y, const char *s);
void setConsoleSize(int width, int height);
