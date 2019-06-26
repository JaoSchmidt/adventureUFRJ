#ifndef ENEMY_HEADER
#define PLAYER_HEADER

typedef struct _INIMIGO{ //estrutura para inimigo
    int x,y; //coordenadas do inimigo
    unsigned short int tempo; //essa flag vai controlar a velocidade do inimigo (indiretamente)
    unsigned short int vivo; //essa flag indica se o bicho está vivo (bool)
} inimigo;

inimigo *inicializa_inimigo(int vivo,int altura,int largura){
    inimigo *i = (inimigo*) malloc(sizeof(inimigo));
    i->vivo=vivo; 
    i->x=largura;
    i->y=altura;
    return i;
}

////ENEMY MOVEMENT AND DRAW
void controle_inimigo0(inimigo *i,jogador *p){
    if(i->vivo==1){
        mvwprintw(p->curWin,i->y,i->x,"   ");
        float tg = ((float)(i->y-p->locY))/(i->x-p->locX);
        float cotg = 1/tg;
        if(i->x-p->locX>=0 && tg>=-1 && tg<=1){
            i->y += tg*(-2);
            i->x-=2;
        }else if(i->x-p->locX<=0 && tg>=-1 && tg<=1){
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

void controle_inimigo_2(inimigo *i,jogador *p){
    if(i->vivo==1){
        mvwaddch(p->curWin,i->y-1,i->x,' ');
        mvwaddch(p->curWin,i->y,i->x,' ');
        mvwaddch(p->curWin,i->y+1,i->x,' ');
        if(i->x>p->locX){
            i->x-=2;
        }
        if(i->x<p->locX){
            i->x+=2;
        }
        if(i->x==p->locX||i->x==p->locX-1||i->x==p->locX+1){
            if(i->y>p->locY){
                i->y--;
            }
            if(i->y<p->locY){
                i->y++;
            }
        }
        mvwaddch(p->curWin,i->y-1,i->x,'^');
        mvwaddch(p->curWin,i->y,i->x,'O');
        mvwaddch(p->curWin,i->y+1,i->x,'v');
    }
}

void controle_inimigo_1(inimigo *i,jogador *p){
    if(i->vivo==1){
        mvwprintw(p->curWin,i->y,i->x,"   ");
        if(i->y>p->locY){
            i->y--;
        }
        if(i->y<p->locY){
            i->y++;
        }
        if(i->y==p->locY){
            if(i->x>p->locX){
                i->x-=2;
            }
            if(i->x<p->locX){
                i->x+=2;
            }
        }
        mvwprintw(p->curWin,i->y,i->x,"<O>");
    }
}
////COLISION ENEMY WITH SHOTS
void colisao_tiro_inimigo_0e1(tiro *t[],inimigo *i,int *score,int maxY,int maxX,int *enemy_number,WINDOW *stats){ 
    if(i->vivo==1){
        int cont;
        for(cont=0;cont<MAX_SHOTS;cont++){
            if(t[cont]->vivo==1){
                if(t[cont]->locx==i->x+1 && t[cont]->locy==i->y){
                    t[cont]->vivo=0;
                    i->vivo=0;
                    mvwprintw(t[cont]->curWin,i->y,i->x,"   ");
                    //STATS WINDOW MODIFICATION
                    int maxx,maxy;
                    getmaxyx(stats,maxy,maxx);
                    *score+=3;
                    if(*score<0){
                        *score = -*score;
                        mvwprintw(stats,getmaxy(stats)/2-1,8,"-%d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
                        *score = -*score;
                    }else{
                        mvwprintw(stats,getmaxy(stats)/2-1,8," %d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
                    }
                    wrefresh(stats);
                    *enemy_number-=1;
                    mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_number)/10)%10,(*enemy_number)%10);
                }
            }
        }
    }
}

void colisao_tiro_inimigo_2(tiro *t[],inimigo *i,int *score,int maxY,int maxX,int *enemy_number,WINDOW*stats){ 
    if(i->vivo==1){
        int cont;
        for(cont=0;cont<MAX_SHOTS;cont++){
            if(t[cont]->vivo==1){
                if(t[cont]->locx==i->x && t[cont]->locy==i->y){
                    mvwaddch(t[cont]->curWin,i->y+0,i->x,' ');
                    mvwaddch(t[cont]->curWin,i->y-1,i->x,' ');
                    mvwaddch(t[cont]->curWin,i->y+1,i->x,' ');
                    t[cont]->vivo=0;
                    i->vivo=0;
                    //STATS WINDOW MODIFICATION
                    int maxx,maxy;
                    getmaxyx(stats,maxy,maxx);
                    *score+=3;
                    if(*score<0){
                        *score = -*score;
                        mvwprintw(stats,getmaxy(stats)/2-1,8,"-%d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
                        *score = -*score;
                    }else{
                        mvwprintw(stats,getmaxy(stats)/2-1,8," %d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
                    }
                    wrefresh(stats);
                    *enemy_number-=1;
                    mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_number)/10)%10,(*enemy_number)%10);
                }
            }
        }
    }
}
////COLISION ENEMY WITH PLAYER
void colisao_player_inimigos_0e1(jogador *pcolisao,inimigo *icolisao,int *score,int *enemy_number,WINDOW *stats,int *pc){
    if(icolisao->vivo==1){
        if((icolisao->x+1==pcolisao->locX+1)&&icolisao->y == pcolisao->locY){
            icolisao->vivo=0;
            mvwprintw(pcolisao->curWin,icolisao->y,icolisao->x,"   ");
            pcolisao->vida--;
            //STATS WINDOW MODIFICATION
            int maxx,maxy;
            getmaxyx(stats,maxy,maxx);
            *score-=10;
            if(*score<0){
                *score = -*score;
                mvwprintw(stats,maxy/2-1,8,"-%d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
                *score = -*score;
            }else{
                mvwprintw(stats,maxy/2-1,8," %d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
            }
            mvwprintw(stats,maxy/2+1,8+pcolisao->vida," ");
            if(pcolisao->vida == 9)
                mvwprintw(stats,maxy/2+1,21," ");
            if(pcolisao->vida == 0)
                *pc=112;
            mvwprintw(stats,maxy/2+1,22,"%d",pcolisao->vida);
            wrefresh(stats);
            *enemy_number-=1;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_number)/10)%10,(*enemy_number)%10);
        }
    }
}
void colisao_player_inimigos2(jogador *pcolisao,inimigo *icolisao,int *score,int *enemy_number,WINDOW *stats,int *pc){
    if(icolisao->vivo==1){
        if(icolisao->x==pcolisao->locX&&icolisao->y == pcolisao->locY){
            icolisao->vivo=0;
            mvwaddch(pcolisao->curWin,icolisao->y+0,icolisao->x,' ');
            mvwaddch(pcolisao->curWin,icolisao->y-1,icolisao->x,' ');
            mvwaddch(pcolisao->curWin,icolisao->y+1,icolisao->x,' ');
            pcolisao->vida--;
            //STATS WINDOW MODIFICATION
            int maxy, maxx;
            getmaxyx(stats,maxy,maxx);
            *score-=10;
            if(*score<0){
                *score = -*score;
                mvwprintw(stats,maxy/2-1,8,"-%d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
                *score = -*score;
            }else{
                mvwprintw(stats,maxy/2-1,8," %d%d%d%d",((*score)/1000)%10,((*score)/100)%10,((*score)/10)%10,(*score)%10);
            }
            mvwprintw(stats,maxy/2+1,8+pcolisao->vida," ");
            if(pcolisao->vida == 9)
                mvwprintw(stats,maxy/2+1,21," ");
            if(pcolisao->vida == 0)
                *pc=112;
            mvwprintw(stats,maxy/2+1,22,"%d",pcolisao->vida);
            wrefresh(stats);
            *enemy_number-=1;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_number)/10)%10,(*enemy_number)%10);
        }
    }
}
#endif
