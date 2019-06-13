//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA7.5
//ESSE PROGRAMA NÃO USA VARIÁVEIS GLOBAIS AFIM DE GARANTIR PORTABILIDADE
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#include "player.h"
#include "enemy.h"

int main()
{
    int c=0,altura,largura,qplayers,cont,cont2,score=0;
    printf("Insira a qnt de jogadores: ");
    scanf("%d",&qplayers);
    initscr();
    cbreak();
    noecho();
	curs_set(FALSE);
    getmaxyx(stdscr,altura,largura);
    largura=largura-1;
    altura=altura-1;
    nodelay(stdscr,TRUE);
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    attron(A_BOLD);
    jogador p[qplayers];
    inimigo i[qinimigos];
    p[0]=inicializajogador(p[0]);
    if(qplayers==2)
        inicializajogador(p[1]);
    for(cont=0;cont<qinimigos;cont++)
        i[cont]=inicializainimigo(i[cont],cont,altura,largura);
    while(c!=127){//loop de tempo, conforme o comando passa, o jogo resume.
        c=getch();
        if(c=='r')
            for(cont=0;cont<qinimigos;cont++)
                i[cont]=inicializainimigo(i[cont],cont,altura,largura);
        p[0]=controle1(p[0],c);
        if(qplayers==2)
            p[1]=controle2(p[1],c);
        p[0]=limite(p[0],altura,largura);
        if(qplayers==2)
            p[1]=limite(p[1],altura,largura);
        clear(); //LIMPA A TELA*****
        if(p[0].vivo==0)mvprintw(0,0,"vose morreu :(");
        if(p[1].vivo==0&&qplayers==2)mvprintw(0,largura-15,"vose morreu :(");
        mvprintw(0,largura-10,"pontos: %d",score);
        attron(COLOR_PAIR(1));
        desenhaplayer(p[0],1);
        attron(COLOR_PAIR(2));
        if(qplayers==2)
            desenhaplayer(p[1],2);
        attron(COLOR_PAIR(4));
        for(cont=0;cont<qinimigos;cont++){
            if(i[cont].tempo>5){ //esse numero indica quantos ticks levam pros bots se mexerem
                i[cont]=controleinimigo(i[cont],p[0]); 
                i[cont].tempo=0;
            }
            desenhainimigo(i[cont]);
            i[cont].tempo++;
        }
        attron(COLOR_PAIR(3));
        p[0]=desenhatiro(p[0]);
        if(qplayers==2)
            p[1]=desenhatiro(p[1]);
        for(cont2=0;cont2<qplayers;cont2++) //roda o(s) doi(s) jogadores pela função de colisão 
            for(cont=0;cont<qinimigos;cont++)
            i[cont]=colisaotiro(p[cont2],i[cont],p[cont2].tirocimax,p[cont2].tiroesquerday,p[cont2].tirobaixox,p[cont2].tirodireitay,&score);
        for(cont2=0;cont2<qplayers;cont2++) //roda o(s) doi(s) jogadores pela função de morte 
            for(cont=0;cont<qinimigos;cont++)
                p[cont2]=morte(p[cont2],i[cont]);
        usleep(50000);
    }
    endwin();
    return 0;
}
