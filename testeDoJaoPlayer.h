#include <ncurses.h>

typedef struct infoJogador{
    WINDOW *curWin;
    int locX,locY,maxY,maxX;
}jogador;

int initialize_player(WINDOW *win,int y,int x,jogador p1){
    p1.locY = y;
    p1.locX = x;
    p1.curWin = win;
    getmaxyx(p1.curWin,p1.maxY,p1.maxX);
}

void movUp(jogador p1){
    if(p1.locY>0){
        p1.locY--;
    }
}
void movLeft(jogador p1){
    if(p1.locX>0){
        p1.locX-=2;
    }
}
void movRight(jogador p1){
    if(p1.locX<p1.maxX){
        p1.locX+=2;
    }
}
void movDown(jogador p1){
    if(p1.locY<p1.maxY){
        p1.locY++;
    }
}
int Display(jogador p1){
    int choice = wgetch(p1.curWin);
    switch (choice)
    {
    case KEY_UP:
        movUp(p1);
        break;
    case KEY_DOWN:
        movDown(p1);
        break;
    case KEY_LEFT:
        movLeft(p1);
        break;
    case KEY_RIGHT:
        movRight(p1);
        break;
    default:
        break;
    }
    return choice;
}

void movPlayer(jogador p1){
    mvwprintw(p1.curWin,p1.locY,p1.locX,"\\1/");
    wrefresh(p1.curWin);
}