//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA7.5
//ESSE PROGRAMA NÃO USA VARIÁVEIS GLOBAIS AFIM DE GARANTIR PORTABILIDADE
//#define _POSIX_C_SOURCE 200809L//define o CLOCK_MONOLITIC
//#include <stdio.h>
//#include <ncurses.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <time.h>
//#define QINIMIGOS 2
//#define DISTANCIA_INIMIGOS 2
//#define MAX_SHOOT 5
//
//#include "time_elapsed.h"//declare this before anything else
//#include "player.h"
//#include "enemy.h"

#ifndef JOGO_HEADER
#define JOGO_HEADER

void write_your_initials(char *destino){
    mvprintw(1,2,"Escreva o nome do jogador\n");
    char a[50],*pa;
    pa = a;
    char c;
    move(2,2);
    while((c = getch())!='\n'){
        refresh();
        addch(c);
        *pa = c;
        *destino = *pa;
        destino++;
        pa++;
    }
}

int jogo(){   
    //start input c
    int c=0;
    //ask number of players [1/2]
    //int qplayers;
    //printf("Insira a qnt de jogadores: ");
    //scanf("%d",&qplayers);
    int score;
    //INITIATE time counting
    clock_gettime(CLOCK_MONOTONIC,&spec); //isso define a função agora
    float enemy_instant, controle_instant,tiros_velocidade,controle_tiro;
    //spec.tv_sec = tempo em segundos, spec.tv_nsec = tempo em nanoseg
    enemy_instant = spec.tv_sec + ((float)spec.tv_nsec/1.0e9);
    controle_instant = enemy_instant;
    tiros_velocidade = enemy_instant;
    controle_tiro = enemy_instant;

    //INITIATE new windows in function of standart window
    //function newwin(height, width, start_y,stat_x)
    int maxY, maxX;
    getmaxyx(stdscr,maxY,maxX);
    WINDOW *playerWin = newwin(maxY*8/10,maxX*8/10,maxY*1/10,maxX*1/10);
    WINDOW *borderPlayerWin = newwin(maxY*8/10+2,maxX*8/10+2,maxY*1/10-1,maxX*1/10-1);
    wborder(borderPlayerWin,'#','#','#','#','#','#','#','#');
    //atualiza as janelas
    wrefresh(borderPlayerWin);
    //novo jogador player1
    jogador *player1 = inicializajogador(playerWin,2,2);

    keypad(stdscr,TRUE);//allow keyboard arrows
	curs_set(FALSE);//torna o cursor invisível
    //nodelay(playerWin,TRUE);//permite getch() ser pulado caso n exista input
    
    //cores do jogo, em pares
    //init_pair(index, foreground, background);
    use_default_colors();//allow default background color with -1
    start_color();
    init_pair(1,COLOR_GREEN,-1);
    init_pair(2,COLOR_BLUE,-1);
    init_pair(3,COLOR_WHITE,-1);
    init_pair(4,COLOR_RED,-1);
    //attron(A_BOLD);
    inimigo *i[QINIMIGOS];
    tiro *tiros_jogador[MAX_SHOOT];
    int cont;
    for(cont=0;cont<MAX_SHOOT;cont++){
        tiros_jogador[cont] = inicializa_tiro(playerWin);
    }
    for(cont=0;cont<QINIMIGOS;cont++){
        i[cont]=inicializainimigo(cont,maxY*3/5,maxX*3/5);
    }
    desenhaplayer(player1,1);
    wtimeout(playerWin,1);
    do{//loop de tempo, conforme o comando passa, o jogo resume.
        mvwprintw(playerWin,1,2,"{%d,%d,%d,%d,%d}",tiros_jogador[0]->vivo,tiros_jogador[1]->vivo,tiros_jogador[2]->vivo,tiros_jogador[3]->vivo,tiros_jogador[4]->vivo);
        c = controle(player1,&controle_tiro,&controle_instant,tiros_jogador);
        
        desenhaplayer(player1,1);
        if(time_elapsed(&tiros_velocidade,0.05)){
            desenhatiro(tiros_jogador,player1);//desenha os tiros
        }
        
        if(c=='r')
            for(cont=0;cont<QINIMIGOS;cont++)
                i[cont]=inicializainimigo(cont,maxY,maxX);
        
        //if(p[0].vivo==0)mvprintw(0,0,"vose morreu :(");
        //if(p[1].vivo==0&&qplayers==2)mvprintw(0,largura-15,"vose morreu :(");
        //mvprintw(0,largura-10,"pontos: %d",score);

        
        //wattron(playerWin,COLOR_PAIR(2));
        wattron(playerWin,COLOR_PAIR(4));
        if(time_elapsed(&enemy_instant,0.5)){
            for(cont=0;cont<QINIMIGOS;cont++){//controle de inimigos
                controleinimigo(i[cont],player1);
            }
        }
        //wattron(playerWin,COLOR_PAIR(3));
        
        for(cont=0;cont<QINIMIGOS;cont++)
            colisaotiro(tiros_jogador,i[cont],&score,player1,maxY,maxX);
        //    for(cont=0;cont<QINIMIGOS;cont++)
        //        morte(player1,i[cont]);
        //        morte(player2,i[cont]);
        
    }while(c!='p');
    return score;
}

#endif

/*//===========================================================================//
coisas que nota-se que tem q fazer ainda:
1.Definir o sistema de ondas. Toda vez que os inimigos morrem surge outra onda
cada onda terá os inimigos em posições e tempos definidos.
2.Fazer função que faz surgir os inimigos de forma controlada(espaço/tempo). Eu penso
em usar argumentos variaveis.
3.precisamos resetar os tiros quando eles somem
*///===========================================================================//
