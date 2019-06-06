//COMPILAR: gcc c.c -o c -Wall -lncurses
////
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

typedef struct estrutura_jogador{
    int x,y,tiro,tirox,tiroy;
} jogador; /// usaremos p como jogador

jogador limiteDeTela(jogador p,int altura,int largura) 
{
    if(p.y>altura)p.y=0;
    if(p.x>largura-3)p.x=0;
    if(p.y<0)p.y=altura;
    if(p.x<0)p.x=largura-3;
    return p;
}

void desenhaPlayer(jogador p,int num)
{
    mvprintw(0,p.x,"X%d Y%d",p.x,p.y);
    mvprintw(p.y,p.x,"\\%d/",num);
}

jogador desenhaTiro(jogador p,int largura) 
{
    mvprintw(p.tiroy,p.tirox,"0");
    if(p.tirox>=largura)p.tiro=0;
    p.tirox++;
    return p;
}

int main()
{
    int c=0,altura,largura;
    initscr();
    raw();
    getmaxyx(stdscr,altura,largura);
	nodelay(stdscr,TRUE);
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    jogador p1,p2;p1.x=0;p1.y=0;p2.x=largura-3;p2.y=0;p1.tiro=0;p2.tiro=0;
    while(c!=127){
    c=getch();
    if(c=='w'){p1.y--;}
    if(c=='a'){p1.x-=2;}
    if(c=='s'){p1.y++;}
    if(c=='d'){p1.x+=2;}
    if(c==32){;p1.tiro=1;p1.tirox=p1.x+3;p1.tiroy=p1.y;}
    if(c=='8'){p2.y--;}
    if(c=='4'){p2.x-=2;}
    if(c=='5'){p2.y++;}
    if(c=='6'){p2.x+=2;}
    if(c=='0'){p2.tiro=1;}
    p1=limiteDeTela(p1,altura,largura);
    p2=limiteDeTela(p2,altura,largura);
    clear();
    attron(COLOR_PAIR(1));
    desenhaPlayer(p1,1);
    attron(COLOR_PAIR(2));
    desenhaPlayer(p2,2);
    attron(COLOR_PAIR(3));
    if(p1.tiro)p1=desenhaTiro(p1,largura);
    usleep(10000); 
    move(0,0);
    }
    endwin();
    return 0;
}
