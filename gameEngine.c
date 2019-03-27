#include "gameEngine.h"

int chooseLanguage(GameBoard *t, Player *p, Minotaur *m, Key *k){
    setConsoleSize(MENUWIDTH+1,MENUHEIGHT+5);
    system("cls");
    drawWindow(1,1,MENUWIDTH,MENUHEIGHT+2,0x3f,"Labyrinth X");
    putStrXY((MENUWIDTH-13)/2,3,"Wybierz jezyk: ");
    putStrXY((MENUWIDTH-16)/2,4,"Choose language: ");

    int position=0;
    int poschanged=0;

    while(1){
        char z;
        int pressed=0;
        //if(poschanged!=0){
        //    clrWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f);
        //}
        if(position==0){
            setActiveColor(0x3f);
            putStrXY(10,6,"> Polski");
            putStrXY(10,7,"  English");
        }
        else if(position==1){
            setActiveColor(0x3f);
            putStrXY(10,6,"  Polski");
            putStrXY(10,7,"> English");
        }

        poschanged=0;

        //if(kbhit()){
            z=getch();
            if(z=='Ó'){
                z=getch();
            }
            setActiveColor(0x0f);
            if(z=='w'||z=='H'){
                position--;
                poschanged=1;
            }
            else if(z=='s'||z=='P'){
                position++;
                poschanged=1;
            }
            else if(z==13||z==' '){
                if(position==0){
                    return 0;
                }
                else if(position==1){
                    return 1;
                }
            }
            if(poschanged==1){
                clrWindow(1,6,MENUWIDTH-1,MENUHEIGHT-1);
                poschanged=0;
            }
            if(position<0) position=1;
            else if(position>1) position=0;
        //}
        /*if(pressed==1){
            setConsoleSize(MENUWIDTH+1, MENUHEIGHT+3);
            drawWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f,"Labirynth X");
        }*/
    }

    setConsole(0,13);
    setActiveColor(0x0f);
    system("pause");
}

int mainMenu(GameBoard *t, Player *p, Minotaur *m, Key *k){
    int position=0;
    int poschanged=0;

    setConsoleSize(MENUWIDTH+1, MENUHEIGHT+3);
    system("cls");
    drawWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f,"Labirynth X");

    while(1){
        char z;
        int pressed=0;
        if(poschanged!=0){
            clrWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f);
        }
        if(position==0){
            setActiveColor(0x3f);
            if(t->language==0){
                putStrXY(4,3,"> Nowa gra");
                putStrXY(4,5,"Pomoc");
                putStrXY(4,7,"Wyjscie");
            }
            else if(t->language==1){
                putStrXY(4,3,"> New game");
                putStrXY(4,5,"Help");
                putStrXY(4,7,"Exit");
            }
            setConsole(0,MENUHEIGHT+1);
        }
        else if(position==1){
            setActiveColor(0x3f);
            if(t->language==0){
                putStrXY(4,3,"Nowa gra");
                putStrXY(4,5,"> Pomoc");
                putStrXY(4,7,"Wyjscie");
            }
            else if(t->language==1){
                putStrXY(4,3,"New game");
                putStrXY(4,5,"> Help");
                putStrXY(4,7,"Exit");
            }
            setConsole(0,MENUHEIGHT+1);
        }
        else if(position==2){
            setActiveColor(0x3f);
            if(t->language==0){
                putStrXY(4,3,"Nowa gra");
                putStrXY(4,5,"Pomoc");
                putStrXY(4,7,"> Wyjscie");
            }
            else if(t->language==1){
                putStrXY(4,3,"New game");
                putStrXY(4,5,"Help");
                putStrXY(4,7,"> Exit");
            }
            setConsole(0,MENUHEIGHT+1);
        }

        poschanged=0;

        //if(kbhit()){
            z=getch();
            if(z=='Ó'){
                z=getch();
            }
            setActiveColor(0x0f);
            if(z=='w'||z=='H'){
                position--;
                poschanged=1;
            }
            else if(z=='s'||z=='P'){
                position++;
                poschanged=1;
            }
            else if(z==13||z==' '){
                if(position==0){
                    pressed=1;
                    setConsoleSize(WIDTH+2, HEIGHT+4);
                    setActiveColor(0x0f);
                    drawWindow(0,0,WIDTH+3,HEIGHT+3,0x3f," Labyrinth X ");
                    t->firstTime=1;
                    initGame(t,p,m,k);
                    createEmptyLabyrinth(t);
                    createMaze(t, p, m);
                    gameEngine(t, p, m, k);
                }
                else if(position==1){

                }
                else if(position==2){
                    system("exit");
                    return 0;
                }
            }
            if(position<0) position=2;
            else if(position>2) position=0;
        //}
        if(pressed==1){
            setConsoleSize(MENUWIDTH+1, MENUHEIGHT+3);
            drawWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f,"Labirynth X");
        }
    }
}

void delay(unsigned int msecs){
    clock_t goal = msecs + clock();
    while (goal > clock());
}

void initGame(GameBoard *t, Player *p, Minotaur *m, Key *k){
    t->actX=0;
    t->actY=0;
    t->done=0;
    t->vis=0;
    t->zmiennaX=0;
    t->zmiennaY=0;
    t->endGame=0;
    t->firstTime=1;

    p->key=0; //czy gracz ma klucz
    //player->name=" ";
    p->pozX=0;
    p->pozY=0;

    m->pozX=0;
    m->pozY=0;
    m->lastDir=0;

    k->pozX=0;
    k->pozY=0;
    k->prvX=0;
    k->prvY=0;
}

int losuj(int liczbaOd, int liczbaDo){
    int liczba=0;

    liczba= liczbaOd + rand() % liczbaDo;

    return liczba;
}

void playerMovement(GameBoard *t, Player *p, char c){
    if(c=='w'||c=='H'){
        //poruszanie siê do góry
        if(t->labyrinth[p->pozX][p->pozY-1]==VISITED||t->labyrinth[p->pozX][p->pozY-1]==KEY){
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,VISITED, p);
            t->labyrinth[p->pozX][p->pozY]=VISITED;
            t->labyrinth[p->pozX][p->pozY-1]=PLAYER;
            p->pozY-=1;
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,PLAYER, p);
        }
    }else if(c=='s'||c=='P'){
        //poruszanie siê na dó³
        if(t->labyrinth[p->pozX][p->pozY+1]==VISITED||t->labyrinth[p->pozX][p->pozY+1]==KEY){
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,VISITED, p);
            t->labyrinth[p->pozX][p->pozY]=VISITED;
            t->labyrinth[p->pozX][p->pozY+1]=PLAYER;
            p->pozY+=1;
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,PLAYER, p);
        }
    }else if(c=='a'||c=='K'){
        //poruszanie siê w lewo
        if(t->labyrinth[p->pozX-1][p->pozY]==VISITED||t->labyrinth[p->pozX-1][p->pozY]==KEY){
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,VISITED, p);
            t->labyrinth[p->pozX][p->pozY]=VISITED;
            t->labyrinth[p->pozX-1][p->pozY]=PLAYER;
            p->pozX-=1;
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,PLAYER, p);
        }
    }else if(c=='d'||c=='M'){
        if(t->labyrinth[p->pozX+1][p->pozY]==VISITED||t->labyrinth[p->pozX+1][p->pozY]==KEY){
        //poruszanie siê w prawo
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,VISITED, p);
            t->labyrinth[p->pozX][p->pozY]=VISITED;
            t->labyrinth[p->pozX+1][p->pozY]=PLAYER;
            p->pozX+=1;
            putLabXY(p->pozX+PRAWO,p->pozY+DOL,PLAYER, p);
        }
    }
}

void minotaurMovement(GameBoard *t, Minotaur *m, Key *k, Player *p){
    int kierunek=0; //1- prawo, 2- lewo, 3- góra, 4- dó³
    //sprawdzenie w któr¹ stronê mo¿e iœc
    int canRight=0, canLeft=0, canUp=0, canDown=0;
    int oppDir; //przeciwny kierunek

    if(t->labyrinth[m->pozX+1][m->pozY]==VISITED){
        canRight=1;
    }
    if(t->labyrinth[m->pozX-1][m->pozY]==VISITED){
        canLeft=1;
    }
    if(t->labyrinth[m->pozX][m->pozY-1]==VISITED){
        canUp=1;
    }
    if(t->labyrinth[m->pozX][m->pozY+1]==VISITED){
        canDown=1;
    }
    //przeciwny kierunek
    if(m->lastDir==1){
        oppDir=2;
    }else if(m->lastDir==2){
        oppDir=1;
    }else if(m->lastDir==3){
        oppDir=4;
    }else if(m->lastDir==4){
        oppDir=3;
    }

    //losowanie kierunku

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
                if(kierunek==1&&oppDir==kierunek){
                    kierunek=2;
                }
                else if(kierunek==2&&oppDir==kierunek){
                    kierunek=1;
                }
            }
            else if(canRight==1&&canUp==1){
                kierunek=losuj(1,2);
                if(kierunek==2) kierunek=3;

                if(kierunek==1&&oppDir==kierunek){
                    kierunek=3;
                }
                else if(kierunek==3&&oppDir==kierunek){
                    kierunek=1;
                }
            }
            else if(canRight==1&&canDown==1){
                kierunek=losuj(1,2);
                if(kierunek==2) kierunek=4;

                if(kierunek==1&&oppDir==kierunek){
                    kierunek=4;
                }
                else if(kierunek==4&&oppDir==kierunek){
                    kierunek=1;
                }
            }
            else if(canLeft==1&&canUp==1){
                kierunek=losuj(1,2);
                if(kierunek==1){
                    kierunek=2;
                }else if(kierunek==2){
                    kierunek=3;
                }

                if(kierunek==2&&oppDir==kierunek){
                    kierunek=3;
                }
                else if(kierunek==3&&oppDir==kierunek){
                    kierunek=2;
                }
            }
            else if(canLeft==1&&canDown==1){
                kierunek=losuj(1,2);
                if(kierunek==1) kierunek=2;
                else if(kierunek==2) kierunek=4;

                if(kierunek==2&&oppDir==kierunek){
                    kierunek=4;
                }
                else if(kierunek==4&&oppDir==kierunek){
                    kierunek=2;
                }
            }
            else if(canDown==1&&canUp==1){
                kierunek=losuj(1,2);
                if(kierunek==1) kierunek=4;
                else if(kierunek==2) kierunek=3;

                if(kierunek==3&&oppDir==kierunek){
                    kierunek=4;
                }
                else if(kierunek==4&&oppDir==kierunek){
                    kierunek=3;
                }
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

        m->lastDir=kierunek;
        if(kierunek==1){
            k->prvX=k->pozX;
            k->prvY=k->pozY;
            k->pozX=m->pozX;
            k->pozY=m->pozY;
            t->labyrinth[k->pozX][k->pozY]=KEY;
            t->labyrinth[k->prvX][k->prvY]=VISITED;
            t->labyrinth[m->pozX+1][m->pozY]=MINOTAUR;
            m->pozX+=1;
        }else if(kierunek==2){
            k->prvX=k->pozX;
            k->prvY=k->pozY;
            k->pozX=m->pozX;
            k->pozY=m->pozY;
            t->labyrinth[k->pozX][k->pozY]=KEY;
            t->labyrinth[k->prvX][k->prvY]=VISITED;
            t->labyrinth[m->pozX-1][m->pozY]=MINOTAUR;
            m->pozX-=1;
        }else if(kierunek==3){
            k->prvX=k->pozX;
            k->prvY=k->pozY;
            k->pozX=m->pozX;
            k->pozY=m->pozY;
            t->labyrinth[k->pozX][k->pozY]=KEY;
            t->labyrinth[k->prvX][k->prvY]=VISITED;
            t->labyrinth[m->pozX][m->pozY-1]=MINOTAUR;
            m->pozY-=1;
        }else if(kierunek==4){
            k->prvX=k->pozX;
            k->prvY=k->pozY;
            k->pozX=m->pozX;
            k->pozY=m->pozY;
            t->labyrinth[k->pozX][k->pozY]=KEY;
            t->labyrinth[k->prvX][k->prvY]=VISITED;
            t->labyrinth[m->pozX][m->pozY+1]=MINOTAUR;
            m->pozY+=1;
        }else if(canDown==0&&canUp==0&&canLeft==0&&canRight==0){
            if(t->labyrinth[m->pozX+1][m->pozY]==KEY){
                kierunek=1;
                k->prvX=k->pozX;
                k->prvY=k->pozY;
                k->pozX=m->pozX;
                k->pozY=m->pozY;
                t->labyrinth[k->pozX][k->pozY]=KEY;
                t->labyrinth[k->prvX][k->prvY]=VISITED;
                t->labyrinth[m->pozX+1][m->pozY]=MINOTAUR;
                m->pozX+=1;
            }
            else if(t->labyrinth[m->pozX-1][m->pozY]==KEY){ //To jest dobrze
                kierunek=2;
                k->prvX=k->pozX;
                k->prvY=k->pozY;
                k->pozX=m->pozX;
                k->pozY=m->pozY;
                t->labyrinth[k->pozX][k->pozY]=KEY;
                t->labyrinth[k->prvX][k->prvY]=VISITED;
                t->labyrinth[m->pozX-1][m->pozY]=MINOTAUR;
                m->pozX-=1;
            }
            else if(t->labyrinth[m->pozX][m->pozY-1]==KEY){
                kierunek=3;
                k->prvX=k->pozX;
                k->prvY=k->pozY;
                k->pozX=m->pozX;
                k->pozY=m->pozY;
                t->labyrinth[k->pozX][k->pozY]=KEY;
                t->labyrinth[k->prvX][k->prvY]=VISITED;
                t->labyrinth[m->pozX][m->pozY-1]=MINOTAUR;
                m->pozY-=1;
            }
            else if(t->labyrinth[m->pozX][m->pozY+1]==KEY){
                kierunek=4;
                k->prvX=k->pozX;
                k->prvY=k->pozY;
                k->pozX=m->pozX;
                k->pozY=m->pozY;
                t->labyrinth[k->pozX][k->pozY]=KEY;
                t->labyrinth[k->prvX][k->prvY]=VISITED;
                t->labyrinth[m->pozX][m->pozY+1]=MINOTAUR;
                m->pozY+=1;
            }
        }

}

void playerFoundKey(GameBoard *t, Player *p, Minotaur *m, Key *k){
    if(p->key!=1){
        if(t->labyrinth[p->pozX+1][p->pozY]==KEY){
            p->key=1;
        }
        else if(t->labyrinth[p->pozX-1][p->pozY]==KEY){
            p->key=1;
        }
        else if(t->labyrinth[p->pozX][p->pozY+1]==KEY){
            p->key=1;
        }
        else if(t->labyrinth[p->pozX][p->pozY-1]==KEY){
            p->key=1;
        }
    }
    else if(p->key==1){
        setActiveColor(0x00);
        int x=0, y=0;
        for(y=0;y<=HEIGHT;y++){
            for(x=0;x<=WIDTH;x++){
                if(t->labyrinth[x][y]==ACTUALPOSITION){
                    //t->labyrinth[x][y]=EXIT;
                    putLabXY(x+PRAWO,y+DOL,ACTUALPOSITION,p);
                }
            }
        }
    }
}

void checkIfEndGame(GameBoard *t,Player *p){
    if(t->labyrinth[p->pozX+1][p->pozY]==MINOTAUR){
        t->endGame=2;
    }
    else if(t->labyrinth[p->pozX-1][p->pozY]==MINOTAUR){
        t->endGame=2;
    }
    else if(t->labyrinth[p->pozX][p->pozY+1]==MINOTAUR){
        t->endGame=2;
    }
    else if(t->labyrinth[p->pozX][p->pozY-1]==MINOTAUR){
        t->endGame=2;
    }

    if(t->labyrinth[p->pozX+1][p->pozY]==ACTUALPOSITION&&p->key==1){
        t->endGame=3;
    }
    else if(t->labyrinth[p->pozX-1][p->pozY]==ACTUALPOSITION&&p->key==1){
        t->endGame=3;
    }
    else if(t->labyrinth[p->pozX][p->pozY+1]==ACTUALPOSITION&&p->key==1){
        t->endGame=3;
    }
    else if(t->labyrinth[p->pozX][p->pozY-1]==ACTUALPOSITION&&p->key==1){
        t->endGame=3;
    }
}

int gameEngine(GameBoard *t, Player *p, Minotaur *m, Key *k){
    unsigned int i=0;

    while(t->endGame==0){
        char c;
        if(kbhit()){
            c=getch();
            if(c=='Ó'){
                c=getch();
            }
            playerMovement(t, p, c);
            if(c=='q') t->endGame=1;
        }
        playerFoundKey(t,p,m,k);
        delay(50);
        i++;
        if(i%7==0){
            i=0;
            minotaurMovement(t, m, k, p);
        }
        checkIfEndGame(t, p);
        drawGameTable(t, p, m, k);
        if(t->endGame==1){
            system("cls");
            return 0;
        }
        else if(t->endGame==2){
            system("cls");
            setConsoleSize(MENUWIDTH+1,MENUHEIGHT+5);
            drawWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f,"Koniec");
            if(t->language==0){
                putStrXY((MENUWIDTH-8)/2,5,"Przegrales");
                setActiveColor(0x0f);
            }
            else if(t->language==1){
                putStrXY((MENUWIDTH-6)/2,5,"You lost");
                setActiveColor(0x0f);
            }
            setConsole(0,MENUHEIGHT+3);
            system("pause");
            system("cls");
        }
        else if(t->endGame==3){
            system("cls");
            setConsoleSize(MENUWIDTH+1,MENUHEIGHT+5);
            drawWindow(1,1,MENUWIDTH,MENUHEIGHT,0x3f,"Koniec");
            if(t->language==0){
                putStrXY((MENUWIDTH-6)/2,5,"Wygrales");
                setActiveColor(0x0f);
            }
            else if(t->language==1){
                putStrXY((MENUWIDTH-4)/2,5,"You won");
                setActiveColor(0x0f);
            }
            setConsole(0,MENUHEIGHT+3);
            system("pause");
            system("cls");
        }
    }
    return 0;
}
