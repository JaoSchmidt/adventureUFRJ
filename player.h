#ifndef PLAYER_HEADER
#define PLAYER_HEADER

typedef struct _TIROS{//shot struct
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
    int locX,locY,maxX,maxY;//player coord //maximum coordinate
    unsigned short int direcao;//player arrow direction;
    int vida; //alive or not
    int qtiros;
} jogador;


jogador *inicializajogador(WINDOW *win,int y,int x)//initialize with specificated coordinates
{
    jogador *p = (jogador*) malloc(sizeof(jogador));
    p->curWin = win;
    p->locX=x;p->locY=y;
    p->direcao='>';
    p->vida=10;
    p->qtiros=0;
    // (*p).vivo = 1;
    //this function write the curWin limits on maxX and maxY
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
        t->locx=p->locX+1;//those 2 make the shots appear on the player coord
        t->locy=p->locY;//the small variations on locY and locX are to make the shots appear in the right position 
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
/*each one of those functions controls p.direcao, p.locY and p.locX, the moviment limit
that is defined on game(), is also used here*/
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
        p1->locX--;
        p1->direcao = '<';
    }
}
void movRight(jogador *p1){
    if(p1->locX<p1->maxX-4){
        clearPlayerTrack(p1);
        p1->locX++;
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


void desenhaplayer(jogador *p,int num){ //draw the player on terminal
    mvwprintw(p->curWin,p->locY,p->locX,"\\%d/",num); //print the keys that follow the player
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

int controle(jogador *p,float *tatirar,float *tandar,tiro *t[]){ //here is the controler for player1
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
        if(time_elapsed(tandar,0.06)) 
            movLeft(p);
        break;
    case '5':
    case 's':
        if(time_elapsed(tandar,0.08))
            movDown(p);
        break;
    case '6':
    case 'd':
        if(time_elapsed(tandar,0.06))
            movRight(p);
        break;
    case 32 ://space key
    case '0':
        if(time_elapsed(tatirar,0.2)){
            for(int i=0;i<MAX_SHOTS;i++){
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

void desenhatiroY(tiro * t[],jogador *p){//draw shots on terminal
    int cont;
    for(cont=0;cont<MAX_SHOTS;cont++){//MAX_SHOTS is number of shots defined in main
        if(t[cont]->vivo==1){
            if(t[cont]->direcaotiro=='^'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locy--;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'^');
            }else if(t[cont]->direcaotiro=='v'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locy++;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'v');
            }
        }
    }
}
void desenhatiroX(tiro * t[],jogador *p){//draw shots on terminal
    int cont;
    for(cont=0;cont<MAX_SHOTS;cont++){//MAX_SHOTS is number of shots defined in main
        if(t[cont]->vivo==1){
            if(t[cont]->direcaotiro=='<'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locx--;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'<');
            }else if(t[cont]->direcaotiro=='>'){
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                t[cont]->locx++;
                mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,'>');
            }
        }
    }
}
void colisao_tiro(tiro *t[],int maxY,int maxX){ 
    int cont;
    for(cont=0;cont<MAX_SHOTS;cont++){
        if(t[cont]->locx<0||t[cont]->locx>maxX||t[cont]->locy<0||t[cont]->locy>maxY){
            t[cont]->vivo=0;
            mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
        }
    }
}


#endif
