#include <ncurses.h>
#include <stdio.h>

typedef struct infoJogador{
    WINDOW *curWin;
    int locX,locY,maxY,maxX;
}jogador;

jogador initialize_player(WINDOW *win,int y,int x,jogador p1){
    p1.locY = y;
    p1.locX = x;
    p1.curWin = win;
    getmaxyx(p1.curWin,p1.maxY,p1.maxX);
    return p1;
}
/*
void movUp(jogador *pp1){
    if(pp1->locY>0){
        pp1->locY--;
    }
}
void movLeft(jogador *pp1){
    if(pp1->locX>0){
        pp1->locX-=2;
    }
}
void movRight(jogador *pp1){
    if(pp1->locX<pp1->maxX){
        pp1->locX+=2;
    }
}
void movDown(jogador *pp1){
    if(pp1->locY<pp1->maxY){
        pp1->locY++;
    }
}
int Display(jogador p1){
    int choice = wgetch(p1.curWin);
    switch (choice)
    {
    case KEY_UP:
        movUp(&p1);
        break;
    case KEY_DOWN:
        movDown(&p1);
        break;
    case KEY_LEFT:
        movLeft(&p1);
        break;
    case KEY_RIGHT:
        movRight(&p1);
        break;
    default:
        break;
    }
    return choice;
}
*/
jogador movPlayer(jogador p1){
    mvwprintw(p1.curWin,p1.locY,p1.locX,"aa");
    return p1;
}
