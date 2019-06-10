//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA7.5
//ESSE PROGRAMA NÃO USA VARIÁVEIS GLOBAIS AFIM DE GARANTIR PORTABILIDADE
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#define qinimigos 50
#define distanciainimigos 2

typedef struct estrutura_jogador{ //estrutura para jogador
    int x,y;//cordenadas do cara
    unsigned short int direcao;//direção da seta presa no jogador;
    unsigned short int tirodisponivel; //essa flag impede que o jogador segure o tiro
    unsigned short int vivo; //vivo ou n
    int qtirosdireita,qtirosesquerda,qtiroscima,qtirosbaixo;//q indica quantidade de tiros em cada direção
    int tirodireitax[50],tirodireitay[50];//cada tiro possui um x e y, el
    int tiroesquerdax[50],tiroesquerday[50];
    int tirocimax[50],tirocimay[50];
    int tirobaixox[50],tirobaixoy[50];
} jogador;

typedef struct estrutura_inimigo{ //estrutura para inimigo
    int x,y; //coordenadas do inimigo
    unsigned short int tempo; //essa flag vai controlar a velocidade do inimigo (indiretamente)
    unsigned short int vivo; //essa flag indica se o bicho está vivo (bool)
} inimigo;

jogador inicializajogador(jogador p)
{
    p.x=0;p.y=0;
    p.qtirosdireita=0;
    p.qtirosesquerda=0;
    p.qtirosbaixo=0;
    p.qtiroscima=0;
    p.direcao='>';
    p.tirodisponivel=0;
    p.vivo=1;
    return p;
}

inimigo inicializainimigo(inimigo i,int cont,int altura,int largura){
    i.tempo=cont;i.vivo=1; //cada um nasce com o tempo diferente
    i.x=distanciainimigos*cont+40;i.y=distanciainimigos*cont;
    return i;
}

jogador limite(jogador p,int altura,int largura){// limite de tela. Se o player passar, volta do outro lado
    if(p.y>altura)p.y=altura;
    if(p.x>largura-3)p.x=largura-3;
    if(p.y<0)p.y=0;
    if(p.x<0)p.x=0;
    if(p.qtirosdireita>50)p.qtirosdireita=0;
    if(p.qtirosesquerda>50)p.qtirosesquerda=0;
    if(p.qtiroscima>50)p.qtiroscima=0;
    if(p.qtirosbaixo>50)p.qtirosbaixo=0;
    if(p.tirodisponivel<5)p.tirodisponivel++;
    return p;
}

jogador direcaodotiro(jogador p){
    if(p.direcao=='^'){//tiroacimax eh função
        p.tirocimax[p.qtiroscima]=p.x+1;//esses dois fazem o tiro surgir nas coord do player
        p.tirocimay[p.qtiroscima]=p.y-2;//y-1,x-2,x+1,etc dizem sobre a posição que o tiro surge em função do tamanho do personagem, lembrando que ele é "\O/"
        p.qtiroscima++;// aumenta quantidade de tiros em 1
    }
    if(p.direcao=='<'){
        p.tiroesquerdax[p.qtirosesquerda]=p.x-3;
        p.tiroesquerday[p.qtirosesquerda]=p.y;
        p.qtirosesquerda++;
    }
    if(p.direcao=='v'){
        p.tirobaixox[p.qtirosbaixo]=p.x+1;
        p.tirobaixoy[p.qtirosbaixo]=p.y+2;
        p.qtirosbaixo++;
    }
    if(p.direcao=='>'){
        p.tirodireitax[p.qtirosdireita]=p.x+5;
        p.tirodireitay[p.qtirosdireita]=p.y;
        p.qtirosdireita++;
    }
    return p;
}

jogador controle1(jogador p,int c){ //aqui é onde ocorre o controle do player 1;
    int cont;
    if(c=='w'){p.y--;p.direcao='^';}
    if(c=='a'){p.x-=2;p.direcao='<';}
    if(c=='s'){p.y++;p.direcao='v';}
    if(c=='d'){p.x+=2;p.direcao='>';}
    if(c==32)
        if(p.tirodisponivel==5){
            p=direcaodotiro(p);//barra de espaço
            p.tirodisponivel=0;
    }
    return p;
}

jogador controle2(jogador p,int c){ //aqui é onde ocorre o controle do player 2;
    if(c=='8'){p.y--;p.direcao='^';}
    if(c=='4'){p.x-=2;p.direcao='<';}
    if(c=='5'){p.y++;p.direcao='v';}
    if(c=='6'){p.x+=2;p.direcao='>';}
    if(c=='0')
        if(p.tirodisponivel==5){
            p=direcaodotiro(p);
            p.tirodisponivel=0;
    }
    return p;
}

void desenhaplayer(jogador p,int num){ //desenha o jogador no terminal
    mvprintw(p.y,p.x,"\\%d/",num); //print das setas q acompanham cada player
    if(p.direcao=='^')
        mvprintw(p.y-1,p.x+1,"^",num);
    if(p.direcao=='<')
        mvprintw(p.y,p.x-2,"<",num);
    if(p.direcao=='v')
        mvprintw(p.y+1,p.x+1,"v",num);
    if(p.direcao=='>')
        mvprintw(p.y,p.x+4,">",num);
    return;
}

jogador desenhatiro(jogador p){// desenha tiros no terminal
    int cont;
    for(cont=0;cont<p.qtiroscima;cont++){
        mvprintw(p.tirocimay[cont],p.tirocimax[cont],"^");
        p.tirocimay[cont]--;
    }
    for(cont=0;cont<p.qtirosesquerda;cont++){
        mvprintw(p.tiroesquerday[cont],p.tiroesquerdax[cont],"<");
        p.tiroesquerdax[cont]-=2;
    }
    for(cont=0;cont<p.qtirosbaixo;cont++){
        mvprintw(p.tirobaixoy[cont],p.tirobaixox[cont],"v");
        p.tirobaixoy[cont]++;
    }
    for(cont=0;cont<p.qtirosdireita;cont++){
        mvprintw(p.tirodireitay[cont],p.tirodireitax[cont],">");
        p.tirodireitax[cont]+=2;
    }
    return p;
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
            if(p.tirocimay[cont]==i.y||p.tirocimay[cont]==i.y-1){
                i.vivo=0;*(tirocimax+cont)=1000;(*score)++;
            }
    for(cont=0;cont<p.qtirosesquerda;cont++)
        if(p.tiroesquerday[cont]==i.y&&i.vivo==1)
            if(p.tiroesquerdax[cont]==i.x+1||p.tiroesquerdax[cont]==i.x){
                i.vivo=0;*(tiroesquerday+cont)=1000;(*score)++;
            }
    for(cont=0;cont<p.qtirosbaixo;cont++)
        if(p.tirobaixox[cont]==i.x+1&&i.vivo==1)
            if(p.tirobaixoy[cont]==i.y||p.tirobaixoy[cont]==i.y-1){
                i.vivo=0;*(tirobaixox+cont)=1000;(*score)++;
        }
    for(cont=0;cont<p.qtirosdireita;cont++)
        if(p.tirodireitay[cont]==i.y&&i.vivo==1)
            if(p.tirodireitax[cont]==i.x+1||p.tirodireitax[cont]==i.x){
                i.vivo=0;*(tirodireitay+cont)=1000;(*score)++;
        }
    return i;
}

jogador morte(jogador p,inimigo i){
    if(p.x==i.x&&p.y==i.y&&i.vivo==1)
        p.vivo=0;
    return p;
}


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
