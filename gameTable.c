#include "gameTable.h"
#include "console.h"

int arrHeight=HEIGHT+1;
int arrWidth=WIDTH+1;

void printLabyrinth(GameBoard *t){
    setConsole(0,0);
    int x=0, y=0;
    for(y=0;y<=HEIGHT;y++){
        for(x=0;x<=WIDTH;x++){
            printf("%d ", t->labyrinth[x][y]);
        }
        printf("\n");
    }
}

void putLabXY( int x, int y, unsigned char z, Player *p ){
    COORD a;
    a.X = x;
    a.Y = y;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), a );

    if(z==ACTUALPOSITION&&p->key==0){
            setActiveColor(0x00);
            printf("X");
        }
        else if(z==ACTUALPOSITION&&p->key==1){
            setActiveColor(0x0a);
            printf("X");
        }
        else if(z==VISITED){
            setActiveColor(0x0f);
            printf(" ");
        }
        else if(z==WALL){
            setActiveColor(0x60);
            printf(" ");
        }
        else if(z==AIR){
            setActiveColor(0xff);
            printf("O");
        }
        else if(z==PLAYER){
            setActiveColor(0x0b);
            printf("@");
        }
        else if(z==MINOTAUR){
            setActiveColor(0x0c);
            printf("M");
        }
        else if(z==KEY&&p->key==0){
            setActiveColor(0x0f);
            printf("*");
        }
        else if(z==KEY&&p->key==1){
            setActiveColor(0x00);
            printf(" ");
        }
        else{
            printf("%d", z);
        }
}

void createEmptyLabyrinth(GameBoard *t){
    int x=0,y=0;
    t->vis=0;
    t->done=0;

    for(y=0;y<=HEIGHT;y++){
        for(x=0;x<=WIDTH;x++){
            if(y%2==0){
                t->labyrinth[x][y]=WALL;
            }
            else if(x%2==0){
                t->labyrinth[x][y]=WALL;
            }
            else{
                t->labyrinth[x][y]=AIR;
            }
        }
    }
}

void checkIfAllVisited(GameBoard *t){
    int allEmpty=(HEIGHT/2)*(WIDTH/2);
    int x=0, y=0, licznik=0;

    for(y=0;y<=HEIGHT;y++){
        for(x=0;x<=WIDTH;x++){
            if(t->labyrinth[x][y]==AIR){
                licznik++;
            }
        }
    }

    if(licznik==0){
        t->vis=1;
        for(y=0;y<=HEIGHT;y++){
            for(x=0;x<=WIDTH;x++){
                t->elements[x][y]=t->labyrinth[x][y];
            }
        }

    }

}

void lookForActualPosition(GameBoard *t){
    t->actX=0;
    t->actY=0;
    int x=0, y=0;
    for(y=0;y<=HEIGHT;y++){
        for(x=0;x<=WIDTH;x++){
            if(t->labyrinth[x][y]==ACTUALPOSITION){
                t->actX=x;
                t->actY=y;
            }
        }
    }
}

void digging(GameBoard *t, Player *p, Minotaur *m){
    /*
        Losowanie kierunku:
        1-prawo, 2- lewo, 3-góra, 4-dó³
        Je¿eli trafi na visited- zmieñ kierunek, je¿eli nie ma inncyh kierunków, rozpocznij polowanie
    */
    int x=0,y=0,kierunek=0,canRight=0,canLeft=0,canUp=0,canDown=0;
    lookForActualPosition(t);
    //Sprawdzanie którêdy mo¿na iœæ
    int pomocniczaXright=t->actX+2;
    int pomocniczaXleft=t->actX-2;
    int pomocniczaYup=t->actY-2;
    int pomocniczaYdown=t->actY+2;

    if(pomocniczaXright<arrWidth){
        if(t->labyrinth[pomocniczaXright][t->actY]==0){
            canRight=1;
            //printf("Mozna isc w prawo.\n");
        }
    }
    if(pomocniczaXleft>0){
        if(t->labyrinth[pomocniczaXleft][t->actY]==0){
            canLeft=1;
            //printf("Mozna isc w lewo.\n");
        }
    }
    if(pomocniczaYup>0){
        if(t->labyrinth[t->actX][pomocniczaYup]==0){
            canUp=1;
            //printf("Mozna isc do gory.\n");
        }
    }
    if(pomocniczaYdown<arrHeight){
        if(t->labyrinth[t->actX][pomocniczaYdown]==0){
            canDown=1;
            //printf("Mozna isc na dol.\n");
        }
    }

    //Obranie kierunku

    if(canRight==0&&canLeft==0&&canUp==0&&canDown==0){
        hunting(t, p, m);
    }
    else{
        if(canRight==1&&canLeft==1&&canUp==1&&canDown==1){
            kierunek=losuj(1,4);
        }
        else if(canRight==1&&canLeft==1&&canUp==1){
            kierunek=losuj(1,3);
        }
        else if(canRight==1&&canUp==1&&canDown==1){
            kierunek=losuj(1,3);
            if(kierunek==2) kierunek=4;
        }
        else if(canLeft==1&&canUp==1&&canDown==1){
            kierunek=losuj(1,3);
            if(kierunek==1) kierunek=4;
        }
        else if(canRight==1&&canLeft==1){
            kierunek=losuj(1,2);
        }
        else if(canRight==1&&canUp==1){
            kierunek=losuj(1,2);
            if(kierunek==2) kierunek=3;
        }
        else if(canRight==1&&canDown==1){
            kierunek=losuj(1,2);
            if(kierunek==2) kierunek=4;
        }
        else if(canLeft==1&&canUp==1){
            kierunek=losuj(1,2);
            if(kierunek==1){
                kierunek=2;
            }else if(kierunek==2){
                kierunek=3;
            }
        }
        else if(canLeft==1&&canDown==1){
            kierunek=losuj(1,2);
            if(kierunek=1) kierunek=2;
            else if(kierunek=2) kierunek=4;
        }
        else if(canDown==1&&canUp==1){
            kierunek=losuj(1,2);
            if(kierunek==1) kierunek=4;
            else if(kierunek==2) kierunek=3;
        }
        else if(canRight==1){
            kierunek=1;
        }
        else if(canLeft==1){
            kierunek=2;
        }
        else if(canUp==1){
            kierunek=3;
        }
        else if(canDown==1){
            kierunek=4;
        }

        if(kierunek==1){
            t->labyrinth[t->actX][t->actY]=VISITED;
            t->labyrinth[t->actX+1][t->actY]=VISITED;
            t->labyrinth[t->actX+2][t->actY]=ACTUALPOSITION;
        }
        else if(kierunek==2){
            t->labyrinth[t->actX][t->actY]=VISITED;
            t->labyrinth[t->actX-1][t->actY]=VISITED;
            t->labyrinth[t->actX-2][t->actY]=ACTUALPOSITION;
        }
        else if(kierunek==3){
            t->labyrinth[t->actX][t->actY]=VISITED;
            t->labyrinth[t->actX][t->actY-1]=VISITED;
            t->labyrinth[t->actX][t->actY-2]=ACTUALPOSITION;
        }
        else if(kierunek==4){
            t->labyrinth[t->actX][t->actY]=VISITED;
            t->labyrinth[t->actX][t->actY+1]=VISITED;
            t->labyrinth[t->actX][t->actY+2]=ACTUALPOSITION;
        }

    }
    //if(kierunek==0) t->vis=1;
}

void hunting(GameBoard *t, Player *p, Minotaur *m){
    //Poszukiwanie od góry pierwszego pola granicz¹cego z odwiedzonym korytarzem
    int posYup=0, posYdown=0, posXright=0, posXleft=0;
    int x=0,y=0,canRight=0,canLeft=0,canUp=0,canDown=0;
    int visRight=0,visLeft=0,visUp=0,visDown=0;
    int kierunek=0;
    t->done=0;
    for(y=0;y<=HEIGHT;y++){
        posYup=y-2;
        posYdown=y+2;
        for(x=0;x<=WIDTH;x++){
            if(t->done==0){
                //Sprawdzanie pól wokó³ danego punktu labiryntu, je¿eli istnieje taki, który
                //graniczy z punktem odwiedzonym- tworzy przjœcie z nim --> punkt P(x,y) bêdzie
                //ACTUALPOSITION
            if(t->labyrinth[x][y]==AIR){
                //czy mo¿na iœæ do góry, na dó³, na lewo, na prawo (canup, candown, canleft, canright)
                posXright=x+2;
                posXleft=x-2;

                if(posXright<arrWidth){
                    canRight=1;
                }
                if(posXleft>0){
                    canLeft=1;
                }
                if(posYup>0){
                    canUp=1;
                }
                if(posYdown<arrHeight){
                    canDown=1;
                }

                if(canRight==1&&canLeft==1&&canUp==1&&canDown==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1&&canLeft==1&&canUp==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1&&canLeft==1&&canDown==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1&&canUp==1&&canDown==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canLeft==1&&canUp==1&&canDown==1){
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1&&canLeft==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1&&canUp==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1&&canDown==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canLeft==1&&canUp==1){
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canLeft==1&&canDown==1){
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canUp==1&&canDown==1){
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canRight==1){
                    if(t->labyrinth[x+2][y]==VISITED){
                        visRight=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canLeft==1){
                    if(t->labyrinth[x-2][y]==VISITED){
                        visLeft=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canUp==1){
                    if(t->labyrinth[x][y-2]==VISITED){
                        visUp=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(canDown==1){
                    if(t->labyrinth[x][y+2]==VISITED){
                        visDown=1;
                    }
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }

                //RESZTA

                if(visRight==1&&visLeft==1&&visUp==1&&visDown==1){
                    kierunek=losuj(1,4);
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(visRight==1&&visLeft==1&&visUp==1){
                    kierunek=losuj(1,3);
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }
                else if(visRight==1&&visLeft==1&&visDown==1){
                    kierunek=losuj(1,3);
                    if(kierunek==3){
                        kierunek=4;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visRight==1&&visUp==1&&visDown==1){
                    kierunek=losuj(1,3);
                    if(kierunek==2){
                        kierunek=4;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visLeft==1&&visUp==1&&visDown==1){
                    kierunek=losuj(1,3);
                    if(kierunek==1){
                        kierunek=4;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visRight==1&&visLeft==1){
                    kierunek=losuj(1,2);
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visRight==1&&visUp==1){
                    kierunek=losuj(1,2);
                    if(kierunek==2){
                        kierunek=3;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visRight==1&&visDown==1){
                    kierunek=losuj(1,2);
                    if(kierunek==2){
                        kierunek=4;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visLeft==1&&visUp==1){
                    kierunek=losuj(1,2);
                    if(kierunek==1){
                        kierunek=3;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visLeft==1&&visDown==1){
                    kierunek=losuj(1,2);
                    if(kierunek==1){
                        kierunek=4;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visUp==1&&visDown==1){
                    kierunek=losuj(1,2);
                    if(kierunek==1){
                        kierunek=3;
                    }
                    else if(kierunek==2){
                        kierunek=4;
                    }
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visRight==1){
                    kierunek=1;
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visLeft==1){
                    kierunek=2;
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visUp==1){
                    kierunek=3;
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }else if(visDown==1){
                    kierunek=4;
                    t->done=1;
                    t->zmiennaX=x;
                    t->zmiennaY=y;
                }

            }
        }
        }
    }
    lookForActualPosition(t);
    //printf("X: %d,Y: %d\nKierunek: %d\n", t->zmiennaX, t->zmiennaY, kierunek);
    //printf("Aktualna pozycja: X: %d, Y: %d\n", t->actX, t->actY);

    if(kierunek==1){
    //prawo
        t->labyrinth[t->actX][t->actY]=VISITED;
        t->labyrinth[t->zmiennaX][t->zmiennaY]=ACTUALPOSITION;
        t->labyrinth[t->zmiennaX+1][t->zmiennaY]=VISITED;
    }else if(kierunek==2){
    //lewo
        t->labyrinth[t->actX][t->actY]=VISITED;
        t->labyrinth[t->zmiennaX][t->zmiennaY]=ACTUALPOSITION;
        t->labyrinth[t->zmiennaX-1][t->zmiennaY]=VISITED;
    }else if(kierunek==3){
    //góra
        t->labyrinth[t->actX][t->actY]=VISITED;
        t->labyrinth[t->zmiennaX][t->zmiennaY-1]=VISITED;
        t->labyrinth[t->zmiennaX][t->zmiennaY]=ACTUALPOSITION;
    }else if(kierunek==4){
    //dó³
        t->labyrinth[t->actX][t->actY]=VISITED;
        t->labyrinth[t->zmiennaX][t->zmiennaY]=ACTUALPOSITION;
        t->labyrinth[t->zmiennaX][t->zmiennaY+1]=VISITED;
    }
    //system("PAUSE");
}

void createMaze(GameBoard *t, Player *p, Minotaur *m){
    int x=0,y=0;
    createEmptyLabyrinth(t);
    do{
        x=losuj(0,WIDTH);
        y=losuj(0, HEIGHT);
    }while(!(t->labyrinth[x][y]==AIR));
    t->labyrinth[x][y]=ACTUALPOSITION;//Wejœcie do labiryntu
    t->actX=x;
    t->actY=y;
    p->pozX=x;
    p->pozY=y;

    //printf("\n");
    //printLabirynth(t);
    //printf("\n");

    while(t->vis==0){
        //system("cls");
        digging(t, p, m);
        //system("PAUSE");
        //printLabirynth(t);
        //system("PAUSE");
        checkIfAllVisited(t);
    }
    if(t->vis==1){
        do{
            x=losuj(0,WIDTH);
            y=losuj(0,HEIGHT);
        }while(!(t->labyrinth[x][y]==VISITED));
        m->pozX=x;
        m->pozY=y;
        t->labyrinth[m->pozX][m->pozY]=MINOTAUR;
    }

}

void drawGameTable(GameBoard *t, Player *p, Minotaur *m, Key *k){
    int x=0,y=0;
    int tmp=0;
    static int cache[WIDTH+1][HEIGHT+1];

    for(y=0;y<=HEIGHT;y++){
        for(x=0;x<=WIDTH; x++){
            tmp=t->elements[x][y];
            if(t->firstTime==1){
                int x1=0, y1=0;
                for(y1=0;y1<=HEIGHT;y1++){
                    for(x1=0;x1<=WIDTH;x1++){
                        cache[x1][y1]=t->labyrinth[x1][y1];
                        putLabXY(x1+PRAWO,y1+DOL,t->elements[x1][y1], p);
                        putLabXY(p->pozX+PRAWO,p->pozY+DOL,PLAYER, p);
                        putLabXY(m->pozX+PRAWO,m->pozY+DOL,MINOTAUR, p);
                        putLabXY(k->pozX+PRAWO,k->pozY+DOL,KEY, p);
                        //putLabXY(t->actX,t->actY,ACTUALPOSITION, p);
                    }
                }
                t->firstTime=0;
            }else{
                if(cache[x][y]!=t->labyrinth[x][y]){
                    cache[x][y]=t->labyrinth[x][y];
                    putLabXY(x+PRAWO,y+DOL,t->elements[x][y], p);
                    putLabXY(p->pozX+PRAWO,p->pozY+DOL,PLAYER, p);
                    putLabXY(m->pozX+PRAWO,m->pozY+DOL,MINOTAUR, p);
                    putLabXY(k->pozX+PRAWO,k->pozY+DOL,KEY, p);
                    //putLabXY(t->actX,t->actY,ACTUALPOSITION, p);
                }
            }
        }
    }
}
