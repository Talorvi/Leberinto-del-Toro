#include "console.h"
#include "gameTable.h"

void setActiveColor( unsigned short k ){
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), k );
}

void initScreen(){
    CONSOLE_CURSOR_INFO cciInfo;
    cciInfo.dwSize = 1;
    cciInfo.bVisible = 0;
    SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo );
    SMALL_RECT windowSize = {0 , 0 ,MENUWIDTH+1 ,MENUHEIGHT+4}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

void setConsole(int x, int y){
    COORD a;
    a.X=x;
    a.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void putCharXY(int x, int y, unsigned char z){
    COORD a;
    a.X=x;
    a.Y=y;

    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), a );
    printf("%c", z);
}

void putIntXY(int x, int y, unsigned int z){
    COORD a;
    a.X=x;
    a.Y=y;

    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), a );
    printf("%d", z);
}

void putStrXY(int x, int y, const char *s){
   while(*s)
      putCharXY(x++, y, *s++);
}

void setConsoleSize(int width, int height){
    SMALL_RECT windowSize = {0 , 0 ,width , height};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}
