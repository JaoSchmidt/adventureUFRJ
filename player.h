#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#define MAXSHOOT 10

typedef struct _JOGADOR{ //estrutura para jogador
    WINDOW *curWin;
    int locX,locY,maxX,maxY;//cordenadas do cara //cordendas máximas
    unsigned short int direcao;//direção da seta presa no jogador;
    unsigned short int tirodisponivel; //essa flag impede que o jogador segure o tiro
    unsigned short int vivo; //vivo ou n
    int qtirosdireita,qtirosesquerda,qtiroscima,qtirosbaixo;//q indica quantidade de tiros em cada direção
    int tirodireitax[MAXSHOOT],tirodireitay[MAXSHOOT];//cada tiro possui um x e y, el
    int tiroesquerdax[MAXSHOOT],tiroesquerday[MAXSHOOT];
    int tirocimax[MAXSHOOT],tirocimay[MAXSHOOT];
    int tirobaixox[MAXSHOOT],tirobaixoy[MAXSHOOT];
} jogador;


jogador *inicializajogador(WINDOW *win,int y,int x)//inicia-se com as coordenadas do jogador em questão
{
    jogador *p = (jogador*) malloc(sizeof(jogador));
    p->curWin = win;
    p->locX=x;p->locY=y;
    p->qtirosdireita=0;
    p->qtirosesquerda=0;
    p->qtirosbaixo=0;
    p->qtiroscima=0;
    p->direcao='>';
    p->vivo=1;
    // (*p).vivo = 1;
    //essa função escreve os máximos na janela win como maxY e maxX
    getmaxyx(p->curWin,p->maxY,p->maxX);
    return p;
}


void direcaodotiro(jogador *p){
    switch (p->direcao)
    {
    case '^':
        if(p->qtiroscima<MAXSHOOT){//os tiros n ultrapassam MAXSHOOT
            p->tirocimax[p->qtiroscima]=p->locX+1;//esses dois fazem o tiro surgir nas coord do player
            p->tirocimay[p->qtiroscima]=p->locY;//y-1,x-2,x+1,etc dizem sobre a posição que o tiro surge em função do tamanho do personagem, lembrando que ele é "\O/"
            p->qtiroscima++;// aumenta quantidade de tiros em 1
            break;
        }
        break;
    case '<':
        if(p->qtirosesquerda<MAXSHOOT){
            p->tiroesquerdax[p->qtirosesquerda]=p->locX-3;
            p->tiroesquerday[p->qtirosesquerda]=p->locY;
            p->qtirosesquerda++;
            break;
        }
        break;
    case 'v':
        if(p->qtirosbaixo<MAXSHOOT){
            p->tirobaixox[p->qtirosbaixo]=p->locX+1;
            p->tirobaixoy[p->qtirosbaixo]=p->locY+2;
            p->qtirosbaixo++;
            break;
        }
        break;
    case '>':
        if(p->qtirosdireita<MAXSHOOT){
            p->tirodireitax[p->qtirosdireita]=p->locX+5;
            p->tirodireitay[p->qtirosdireita]=p->locY;
            p->qtirosdireita++;
            break;
        }
        break;
    default:
        break;
    }
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

int controle(jogador *p,float *tatirar,float *tandar){ //aqui é onde ocorre o controle do player1 e player2;
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
            direcaodotiro(p);
        }
        break;
    default:
        break;
    }
    return choice;
}

void desenhatiro(jogador *p){// desenha tiros no terminal
    int cont;
    for(cont=0;cont<p->qtiroscima;cont++){
        mvwprintw(p->curWin,p->tirocimay[cont],p->tirocimax[cont]," ");
        p->tirocimay[cont]--;
        mvwprintw(p->curWin,p->tirocimay[cont],p->tirocimax[cont],"^");
    }
    for(cont=0;cont<p->qtirosesquerda;cont++){
        mvwprintw(p->curWin,p->tiroesquerday[cont],p->tiroesquerdax[cont]," ");
        p->tiroesquerdax[cont]-=2;
        mvwprintw(p->curWin,p->tiroesquerday[cont],p->tiroesquerdax[cont],"<");
    }
    for(cont=0;cont<p->qtirosbaixo;cont++){
        mvwprintw(p->curWin,p->tirobaixoy[cont],p->tirobaixox[cont]," ");
        p->tirobaixoy[cont]++;
        mvwprintw(p->curWin,p->tirobaixoy[cont],p->tirobaixox[cont],"v");
    }
    for(cont=0;cont<p->qtirosdireita;cont++){
        mvwprintw(p->curWin,p->tirodireitay[cont],p->tirodireitax[cont]," ");
        p->tirodireitax[cont]+=2;
        mvwprintw(p->curWin,p->tirodireitay[cont],p->tirodireitax[cont],">");
    }
}

//lembrar de checar por morte em cada movimento do inimigo
/*void morte(jogador *p,inimigo i){
    if(p->locX==i.x&&p->locY==i.y&&i.vivo==1)
        p->vivo=0;
}*/

#endif
