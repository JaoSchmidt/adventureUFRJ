#include <ncurses.h>

#include "testeDoJaoPlayer.h"

int main(){
    //Ncurses start
    initscr();
    cbreak();
    noecho();

    //get screen size for player
    int maxY, maxX;
    getmaxyx(stdscr,maxY,maxX);

    //create new window in function of standart window
    //function newwin(height, width, start_y,stat_x)
    WINDOW *playerWin = newwin(maxY*3/5,maxX*3/5,maxY*1/5,maxX*1/5);
    box(playerWin,0,0);
    refresh();
    jogador player;
    initialize_player(playerWin,1,1,player);
    wrefresh(playerWin);
    do{
        movPlayer(player);
    }while(Display(player) != KEY_DC);
    
    
    getch();
    endwin();
}