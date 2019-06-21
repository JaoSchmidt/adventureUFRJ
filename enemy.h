#ifndef ENEMY_HEADER
#define PLAYER_HEADER

typedef struct _INIMIGO{ //estrutura para inimigo
    int x,y; //coordenadas do inimigo
    unsigned short int tempo; //essa flag vai controlar a velocidade do inimigo (indiretamente)
    unsigned short int vivo; //essa flag indica se o bicho está vivo (bool)
} inimigo;

inimigo *inicializa_inimigo(int cont,int altura,int largura){
    inimigo *i = (inimigo*) malloc(sizeof(inimigo));
    i->tempo=cont;
    i->vivo=1; //cada um nasce com o tempo diferente
    i->x=DISTANCIA_INIMIGOS*cont+60;
    i->y=DISTANCIA_INIMIGOS*cont;
    return i;
}

void controleinimigo(inimigo *i,jogador *p){
    if(i->vivo==1){
        mvwprintw(p->curWin,i->y,i->x,"   ");
        float tg = ((float)(i->y-p->locY))/(i->x-p->locX);
        float cotg = 1/tg;
        mvwprintw(p->curWin,7,2,"%f",tg);
        if(i->x-p->locX>=0 && tg>=-1 && tg<=1){
            mvwprintw(p->curWin,5,2,"1f = %d %f",i->x-p->locX,tg);
            i->y += tg*(-2);
            i->x-=2;
        }else if(i->x-p->locX<=0 && tg>=-1 && tg<=1){
            mvwprintw(p->curWin,5,2,"2f = %d %f",i->x-p->locX,tg);
            i->y += tg*2;
            i->x+=2;
        }else if(i->y-p->locY>0 && cotg<1 && cotg>-1){
            i->x +=cotg*(-1);
            i->y--;
        }else if(i->y-p->locY<0 && cotg<1 && cotg>-1){
            i->x +=cotg;
            i->y++;
        }
        mvwprintw(p->curWin,i->y,i->x,"OoO");
    }
}

void colisaotiro(tiro *t[],inimigo *i,int *score,jogador *p,int maxY,int maxX){ 
    if(i->vivo==1){
        int cont;
        for(cont=0;cont<p->qtiros;cont++){
            if(t[cont]->vivo==1){
                if(t[cont]->locx==i->x+1 && t[cont]->locy==i->y){
                    t[cont]->vivo=0;
                    i->vivo=0;
                    mvwprintw(t[cont]->curWin,i->y,i->x,"   ");
                }
                if(t[cont]->locx<0||t[cont]->locx>maxX||t[cont]->locy<0||t[cont]->locy>maxY){
                    t[cont]->vivo=0;
                    mvwaddch(t[cont]->curWin,t[cont]->locy,t[cont]->locx,' ');
                }
            }
        }
    }
}

#endif
