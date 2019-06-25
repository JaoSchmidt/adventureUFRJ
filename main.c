//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA7.5
//ESSE PROGRAMA NÃO USA VARIÁVEIS GLOBAIS AFIM DE GARANTIR PORTABILIDADE
#define _POSIX_C_SOURCE 200809L//define o CLOCK_MONOLITIC
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#define ENEMYTYPE0MAX 15
#define ENEMYTYPE1MAX 15
#define ENEMYTYPE2MAX 15
#define ENEMYTYPE3MAX 0
#define MAX_SHOTS 20//shots

#include "time_elapsed.h"//declare this before anything else
#include "player.h"
#include "enemy.h"
#include "jogo.h"

typedef struct _PLAYER_SCORE{
    int score;
    char name[50];
} pontuacao;

void organize_score(pontuacao pts[]){//organize score from biggest to smallest
    char temp_char[50];
    int temp_int;
    for (int i = 0;i<11;i++){
        for (int j = i + 1; j < 11; j++){
            if (pts[i].score<=pts[j].score){
                temp_int = pts[i].score;
                pts[i].score = pts[j].score;
                pts[j].score = temp_int;
                strcpy(temp_char,pts[i].name);
                strcpy(pts[i].name,pts[j].name);
                strcpy(pts[j].name,temp_char);
            }
        }
    }
}

int main() {
    WINDOW *w;
    char list[6][100] = { "SELECIONE USANDO AS TECLAS W-S; ENTER PARA CONFIRMAR", "Jogar", "Score", "Créditos", "Sair"};
    //char item[7];
    int ch, i = 0;

    initscr(); // initialize Ncurses
    noecho(); // disable echoing of characters on the screen
    cbreak();
    int maxY,maxX;
    getmaxyx(stdscr,maxY,maxX);//maxY is the height of stdscr
    w = newwin( 7, maxX-1, maxY-10, 1 ); // create a new window
    box( w, 0, 0 ); // sets default borders for the window

     
    //now print all the menu items and highlight the first one
    for( i=0; i<5; i++ ) {
        if( i == 1 ) 
            wattron( w, A_STANDOUT ); // highlights the first item.
        
        //sprintf(item, "%-6s",  list[i]);
        mvwprintw( w, i+1, 2, "%s", list[i] );
        wattroff( w, A_STANDOUT );
    }
    mvprintw((maxY/4), -27+maxX/2, "  ____                      __        __              ");
    mvprintw((maxY/4)+1, -27+maxX/2, " / ___| _   _ _ __   ___ _ _\\ \\      / /_ ___   _____ ");
    mvprintw((maxY/4)+2, -27+maxX/2, " \\___ \\| | | | '_ \\ / _ \\ '__\\ \\ /\\ / / _` \\ \\ / / _ \\");
    mvprintw((maxY/4)+3, -27+maxX/2, "  ___) | |_| | |_) |  __/ |   \\ V    / (_| |\\ V /  __/");
    mvprintw((maxY/4)+4, -27+maxX/2, " |____/ \\__,_| .__/ \\___|_|    \\_/\\_/ \\__,_| \\_/ \\___|");
    mvprintw((maxY/4)+5, -27+maxX/2, "             |_|                                      ");
 
    refresh();
    wrefresh( w ); // update the terminal screen (standard and *w)
 
    i = 1;
    keypad(w,TRUE); // enable keyboard input for the window,allow keyboard arrows.
    curs_set(0); // hide the default screen cursor.

    //score data: name and score of player
    pontuacao score_player[11],recent_score;//score_player[10] will be the recent player
    strcpy(recent_score.name,"None");
    recent_score.score = 0;

    // get the input
    do{
        ch=wgetch(w);//get ch
        //// right pad with spaces to make the items appear with even width.
        //sprintf(item, "%-6s",  list[i]); 
        mvwprintw(w,i+1,2,"%s",list[i]);
        box(w,0,0); 
        ////use ch to increase or decrease the value i based on the input.
        switch(ch) {
            case 'w':
            case 'W':
            case KEY_UP:
                i--;
                i = ( i<1 ) ? 4 : i;
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                i++;
                i = ( i>4 ) ? 1 : i;
                break;
            case '\n':
                switch (i){
                case 1:
                    clear();//will clear the window stdscr after refresh
                    refresh();//will refresh to apply clear()
                    curs_set(1);
                    getch();
                    write_your_initials(recent_score.name);
                    curs_set(0);
                    clear();
                    refresh();
                    recent_score.score = game();
                    FILE *parq1;
                    parq1 = fopen("score.txt","r");
                    for(int i=0;i<10;i++){
                        fscanf(parq1,"%d %s\n",&score_player[i].score,score_player[i].name);
                    }
                    fclose(parq1);
                    strcpy(score_player[10].name,recent_score.name);
                    score_player[10].score = recent_score.score;
                    parq1 = fopen("score.txt","w+");
                    organize_score(score_player);
                    for(int i=0;i<10;i++){
                        fprintf(parq1,"%d %s\n",score_player[i].score,score_player[i].name);
                    }
                    fclose(parq1);
                    clear();
                    refresh();
                    break;
                case 2:
                    clear();
                    refresh();
                    int k=0,scoreName;
                    char name[4];
                    FILE *parq2;
                    parq2 = fopen("score.txt","r");
                    while(!feof(parq2)){
                        fscanf(parq2,"%d %[A-Z a-z]\n",&scoreName,name);
                        mvprintw(2+k,30,"%d",scoreName);
                        mvprintw(2+k,2,"%s",name);
                        k++;
                    }
                    getch();
                    fclose(parq2);
                    clear();
                    refresh();
                    break;
                case 3:
                    clear();
                    refresh();
                    mvprintw(5,-5+maxX/2, "CREDITOS");
                    mvprintw(-6+maxY/2,-7+maxX/2, "Desenvolvedores:");
                    mvprintw(1+maxY/2,-5+maxX/2,"-João Henrique Schmidt");
                    mvprintw(-1+maxY/2,-5+maxX/2,"-Diego Malta");
                    mvprintw(-3+maxY/2,-5+maxX/2,"-André Uziel");
                    mvprintw(+3+maxY/2,-5+maxX/2,"-Thalles Nonato");
                    mvprintw(7+maxY/2, -15+maxX/2, "Agradecimentos Especiais: hugonobrega.com");
                    mvprintw(9+maxY/2, -21+maxX/2, "Todos os direitos de imagem foram devidamente obtidos");
                    getch();//has refresh "inside" of it, therefore will refresh
                    clear();
                    refresh();
	                break;
                case 4:
                    ch = 27;
                    break;
                }
                break;
        }
        ////now highlight the next item in the list.
        wattron( w, A_STANDOUT );
        //sprintf(item, "%-6s",  list[i]);
        mvwprintw( w, i+1, 2, "%s", list[i]);
        wattroff( w, A_STANDOUT );
    }while(ch!=27);
 
    endwin();
    return 0;
}
