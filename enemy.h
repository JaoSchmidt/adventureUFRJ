//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA7.5
//ESSE PROGRAMA NÃO USA VARIÁVEIS GLOBAIS AFIM DE GARANTIR PORTABILIDADE
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#define qinimigos 50
#define distanciainimigos 2

//STRUCTS GLOBAIS

typedef struct estrutura_inimigo{ //estrutura para inimigo
    int x,y; //coordenadas do inimigo
    unsigned short int tempo; //essa flag vai controlar a velocidade do inimigo (indiretamente)
    unsigned short int vivo; //essa flag indica se o bicho está vivo (bool)
} inimigo;

inimigo inicializainimigo(inimigo i,int cont,int altura,int largura){
    i.tempo=cont;i.vivo=1; //cada um nasce com o tempo diferente
    i.x=distanciainimigos*cont+40;i.y=distanciainimigos*cont;
    return i;
}

inimigo controleinimigo(inimigo i,jogador p){
    if(i.x>p.x)i.x-=2;
    if(i.x<p.x)i.x+=2;
    if(i.x==p.x){
    if(i.y>p.y)i.y--;
    if(i.y<p.y)i.y++;
    }
    return i;
}

void desenhainimigo(inimigo i){
    if(i.vivo==1)
        mvprintw(i.y,i.x,"\\o/");
}

inimigo colisaotiro(jogador p,inimigo i,int *tirocimax,int *tiroesquerday,int *tirobaixox,int *tirodireitay,int *score){ 
    int cont;
    for(cont=0;cont<p.qtiroscima;cont++) //aqui encontrei um problema pois era necessario retornar dois valores: p e i
        if(p.tirocimax[cont]==i.x+1&&i.vivo==1)
            if(p.tirocimay[cont]==i.y||p.tirocimay[cont]==i.y-1||p.tirocimay[cont]==i.y+1){
                i.vivo=0;*(tirocimax+cont)=1000;(*score)++;
            }
    for(cont=0;cont<p.qtirosbaixo;cont++)
        if(p.tirobaixox[cont]==i.x+1&&i.vivo==1)
            if(p.tirobaixoy[cont]==i.y||p.tirobaixoy[cont]==i.y-1||p.tirobaixoy[cont]==i.y+1){
                i.vivo=0;*(tirobaixox+cont)=1000;(*score)++;
            }
    for(cont=0;cont<p.qtirosesquerda;cont++)
        if(p.tiroesquerday[cont]==i.y&&i.vivo==1)
            if(p.tiroesquerdax[cont]==i.x+1||p.tiroesquerdax[cont]==i.x||p.tiroesquerdax[cont]==i.x-1){
                i.vivo=0;*(tiroesquerday+cont)=1000;(*score)++;
            }
    
    for(cont=0;cont<p.qtirosdireita;cont++)
        if(p.tirodireitay[cont]==i.y&&i.vivo==1)
            if(p.tirodireitax[cont]==i.x+1||p.tirodireitax[cont]==i.x||p.tirodireitax[cont]==i.x-1){
                i.vivo=0;*(tirodireitay+cont)=1000;(*score)++;
            }
    return i;
}


