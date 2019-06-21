#ifndef PLAYER_HEADER
#define PLAYER_HEADER

typedef struct _TIROS{// estrutura para tiro
    WINDOW *curWin;
    int vivo,locx,locy;
    int direcaotiro;
} tiro;

tiro * inicializa_tiro(WINDOW *win){
    tiro *t = (tiro*) malloc(sizeof(tiro));
    t->curWin = win;
    t->locx = 0;
    t->locy = 0;
    t->vivo = 0;
    t->direcaotiro = '>';
    return t;
}

typedef struct _JOGADOR{ //estrutura para jogador
    WINDOW *curWin;
    int locX,locY,maxX,maxY;//cordenadas do cara //cordendas máximas
    unsigned short int direcao;//direção da seta presa no jogador;
    unsigned short int tirodisponivel; //essa flag impede que o jogador segure o tiro
    unsigned short int vivo; //vivo ou n
    int qtiros;
} jogador;


jogador *inicializajogador(WINDOW *win,int y,int x)//inicia-se com as coordenadas do jogador em questão
{
    jogador *p = (jogador*) malloc(sizeof(jogador));
    p->curWin = win;
    p->locX=x;p->locY=y;
    p->direcao='>';
    p->vivo=1;
    p->qtiros=0;
    // (*p).vivo = 1;
    //essa função escreve os máximos na janela win como maxY e maxX
    getmaxyx(p->curWin,p->maxY,p->maxX);
    return p;
}


void adciona_tiro_ao_jogador(jogador *p,tiro *t){
    p->qtiros++;
    t->curWin=p->curWin;
    switch (p->direcao)
    {
    case '^':
        t->direcaotiro = '^';
        t->locx=p->locX+1;//esses dois fazem o tiro surgir nas coord do player
        t->locy=p->locY;//y-1,x-2,x+1,etc dizem sobre a posição que o tiro surge em função do tamanho do personagem, lembrando que ele é "\O/"
        break;
    case '<':
        t->direcaotiro = '<';
        t->locx=p->locX-3;
        t->locy=p->locY;
        break;
    case 'v':
        t->direcaotiro = 'v';
        t->locx=p->locX+1;
        t->locy=p->locY+2;
        break;
    case '>':
        t->direcaotiro = '>';
        t->locx=p->locX+5;
        t->locy=p->locY;
        break;
    default:
        break;
    }
    t->vivo=1;
}
void clearPlayerTrack(jogador *p1){
    if(p1->direcao == '^'){
        mvwprintw(p1->curWin,p1->locY-1,p1->locX+1," ");
        mvwprintw(p1->curWin,p1->locY,p1->locX,"   ");
    }else if(p1->direcao == 'v'){
        mvwprintw(p1->curWin,p1->locY+1,p1->locX+1," ");
        mvwprintw(p1->curWin,p1->locY,p1->locX,"   ");
    }else if(p1->direcao == '>'){
        mvwprintw(p1->curWin,p1->locY,p1->locX,"     ");
    }else if(p1->direcao == '<'){
        mvwprintw(p1->curWin,p1->locY,p1->locX-2,"     ");
        if(p1->locX == 0){
        mvwprintw(p1->curWin,p1->locY,p1->locX,"   ");
        }
    }
}
/*cada uma das funções controla p.direcao e p.locY e p.locX
a localização e coordenada máximas estão declaradas na janela cirada em main()
e são usadas aqui*/
void movUp(jogador *p1){
    if(p1->locY>0){
        clearPlayerTrack(p1);
        p1->locY--;
        p1->direcao = '^';
    }
}
void movLeft(jogador *p1){
    if(p1->locX>0){
        clearPlayerTrack(p1);
        p1->locX-=2;
        p1->direcao = '<';
    }
}
void movRight(jogador *p1){
    if(p1->locX<p1->maxX-4){
        clearPlayerTrack(p1);
        p1->locX+=2;
        p1->direcao = '>';
    }
}
void movDown(jogador *p1){
    if(p1->locY<p1->maxY-1){
        clearPlayerTrack(p1);
        p1->locY++;
        p1->direcao = 'v';
    }
    
}


void desenhaplayer(jogador *p,int num){ //desenha o jogador no terminal
    mvwprintw(p->curWin,p->locY,p->locX,"\\%d/",num); //print das setas q acompanham cada player
    switch (p->direcao)
    {
    case '^':
        mvwprintw(p->curWin,p->locY-1,p->locX+1,"^",num);
        break;
    case '<':
        mvwprintw(p->curWin,p->locY,p->locX-2,"<",num);
        break;
    case 'v':
        mvwprintw(p->curWin,p->locY+1,p->locX+1,"v",num);
        break;
    case '>':
        mvwprintw(p->curWin,p->locY,p->locX+4,">",num);
        break;
    default:
        break;
    }
    return;
}

int controle(jogador *p,float *tatirar,float *tandar,tiro *t[]){ //aqui é onde ocorre o controle do player1 e player2;
    int choice = wgetch(p->curWin);
    switch (choice)
    {
    case ERR:
        break;
    case '8':
    case 'w':
        if(time_elapsed(tandar,0.08))
            movUp(p);
        break;
    case '4':
    case 'a':
        if(time_elapsed(tandar,0.08)) 
            movLeft(p);
        break;
    case '5':
    case 's':
        if(time_elapsed(tandar,0.08))
            movDown(p);
        break;
    case '6':
    case 'd':
        if(time_elapsed(tandar,0.08))
            movRight(p);
        break;
    case 32 ://barra de espaço
    case '0':
        if(time_elapsed(tatirar,0.2)){
            for(int i=0;i<MAX_SHOOT;i++){
                if(t[i]->vivo==0){
                    adciona_tiro_ao_jogador(p,t[i]);
                    break;
                }
            }
        }
    default:
        break;
    }
    return choice;
}

void desenhatiro(tiro * t[],jogador *p){// desenha tiros no terminal
    int cont;
    for(cont=0;cont<p->qtiros;cont++){//MAX_SHOOT eh o numero de tiros definido em main
        if(t[cont]->vivo==1){
            if(t[cont]->direcaotiro=='^'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locy--;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'^');
            }else if(t[cont]->direcaotiro=='<'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locx-=2;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'<');
            }else if(t[cont]->direcaotiro=='v'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locy++;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'v');
            }else if(t[cont]->direcaotiro=='>'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locx+=2;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'>');
            }
        }
    }
}


//lembrar de checar por morte em cada movimento do inimigo
/*void morte(jogador *p,inimigo i){
    if(p->locX==i.x&&p->locY==i.y&&i.vivo==1)
        p->vivo=0;
}*/

#endif
