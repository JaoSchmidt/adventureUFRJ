#include <ncurses.h>
#include <stdio.h>

#include "jao.h"

int main(){
    //Ncurses start
    initscr();
    cbreak();
    noecho();

    //habilitar as setas do telcado
    keypad(stdscr,TRUE);
    //get screen size for player
    int maxY, maxX,c;
    getmaxyx(stdscr,maxY,maxX);

    //create new window in function of standart window
    //function newwin(height, width, start_y,stat_x)
    WINDOW *playerWin = newwin(maxY*3/5,maxX*3/5,maxY*1/5,maxX*1/5);
    box(playerWin,0,0);
    refresh();
    jogador player;
    jogador player =
    player = initialize_player(playerWin,2,2,player);
    wrefresh(playerWin);
    keypad(playerWin,TRUE);//habilitar as setas do telcado
    //do{
    //    movPlayer(player);
    //}while(Display(player)!='p');
    do{
        c = Display(player);
        movPlayer(player);
        wrefresh(playerWin);
    }while(c!='p');
    
    
    endwin();
}
