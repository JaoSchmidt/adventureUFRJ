#ifndef ENEMY_HEADER
#define PLAYER_HEADER

typedef struct _INIMIGO{ //estrutura para inimigo
    int x,y; //coordenadas do inimigo
    unsigned short int tempo; //essa flag vai controlar a velocidade do inimigo (indiretamente)
    unsigned short int vivo; //essa flag indica se o bicho está vivo (bool)
} inimigo;

inimigo *inicializainimigo(int cont,int altura,int largura){
    inimigo *i = (inimigo*) malloc(sizeof(inimigo));
    i->tempo=cont;
    i->vivo=1; //cada um nasce com o tempo diferente
    i->x=distanciainimigos*cont+40;
    i->y=distanciainimigos*cont;
    return i;
}

void controleinimigo(inimigo *i,jogador *p){
    if(i->vivo==1){
        mvwprintw(p->curWin,i->y,i->x,"   ");
        if(i->x>p->locX){
            i->x-=2;
        }
        if(i->x<p->locX){
            i->x+=2;
        }
        if(i->x==p->locX){
            if(i->y>p->locY){
                i->y--;
            }
            if(i->y<p->locY){
                i->y++;
            }
        }
    }
}

void desenhainimigo(inimigo *i,jogador *p){
    if(i->vivo==1)
        mvwprintw(p->curWin,i->y,i->x,"\\o/");
}

void colisaotiro(jogador *p,inimigo *i,int *score){ 
    if(i->vivo==1){
        int cont;
        mvwprintw(p->curWin,1,1,"aaaaaaaa");
        for(cont=0;cont<p->qtiroscima;cont++) //aqui encontrei um problema pois era necessario retornar dois valores: p e i
            if(p->tirocimax[cont]==i->x+1)
                if(p->tirocimay[cont]==i->y||p->tirocimay[cont]==i->y-1||p->tirocimay[cont]==i->y+1){
                    i->vivo=0;*(p->tirocimax+cont)=1000;(*score)++;
                    mvwprintw(p->curWin,i->y,i->x,"   ");
                }
        for(cont=0;cont<p->qtirosbaixo;cont++)
            if(p->tirobaixox[cont]==i->x+1)
                if(p->tirobaixoy[cont]==i->y||p->tirobaixoy[cont]==i->y-1||p->tirobaixoy[cont]==i->y+1){
                    i->vivo=0;*(p->tirobaixox+cont)=1000;(*score)++;
                    mvwprintw(p->curWin,i->y,i->x,"   ");
                }
        for(cont=0;cont<p->qtirosesquerda;cont++)
            if(p->tiroesquerday[cont]==i->y)
                if(p->tiroesquerdax[cont]==i->x+1||p->tiroesquerdax[cont]==i->x||p->tiroesquerdax[cont]==i->x-1){
                    i->vivo=0;*(p->tiroesquerday+cont)=1000;(*score)++;
                    mvwprintw(p->curWin,i->y,i->x,"   ");
                }
        
        for(cont=0;cont<p->qtirosdireita;cont++)
            if(p->tirodireitay[cont]==i->y)
                if(p->tirodireitax[cont]==i->x+1||p->tirodireitax[cont]==i->x||p->tirodireitax[cont]==i->x-1){
                    i->vivo=0;*(p->tirodireitay+cont)=1000;(*score)++;
                    mvwprintw(p->curWin,i->y,i->x,"   "); 
                    
                }
    }
}

#endif
