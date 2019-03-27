#include "console.h"
#include "gameTable.h"
#include "gameEngine.h"

int main(){
    int a;
    srand(time(NULL));

    initScreen();

    GameBoard gameBoard;
    Player player;
    Minotaur minotaur;
    Key key;

    gameBoard.language=chooseLanguage(&gameBoard, &player, &minotaur, &key);

    while(1){
        a=mainMenu(&gameBoard, &player, &minotaur, &key);
        if(a==0) break;
    }

    setActiveColor(0x0f);
    return 0;
}
