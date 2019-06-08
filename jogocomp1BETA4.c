//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA6
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

typedef struct estrutura_jogador{ //estrutura para jogador
    int x,y;//cordenadas do cara
    int direcao;//direção da seta presa no jogador;
    int qtirosdireita,qtirosesquerda,qtiroscima,qtirosbaixo;//q indica quantidade de tiros em cada direção
    int tirodireitax[50],tirodireitay[50];//cada tiro possui um x e y, el
    int tiroesquerdax[50],tiroesquerday[50];
    int tirocimax[50],tirocimay[50];
    int tirobaixox[50],tirobaixoy[50];
} jogador;

jogador limite(jogador p,int altura,int largura){// limite de tela. Se o player passar, volta do outro lado
    if(p.y>altura-1)p.y=0;
    if(p.x>largura-3)p.x=0;
    if(p.y<0)p.y=altura-1;
    if(p.x<0)p.x=largura-3;
    if(p.qtirosdireita>50)p.qtirosdireita=0;
    if(p.qtirosesquerda>50)p.qtirosesquerda=0;
    if(p.qtiroscima>50)p.qtiroscima=0;
    if(p.qtirosbaixo>50)p.qtirosbaixo=0;
    return p;
}

jogador direcaodotiro(jogador p){
    if(p.direcao=='^'){//tiroacimax eh função
        p.tirocimax[p.qtiroscima]=p.x+1;//esses dois fazem o tiro surgir nas coord do player
        p.tirocimay[p.qtiroscima]=p.y-1;//y-1,x-2,x+1,etc dizem sobre a posição que o tiro surge em função do tamanho do personagem, lembrando que ele é "\O/"
        p.qtiroscima++;// aumenta quantidade de tiros em 1
    }
    if(p.direcao=='<'){
        p.tiroesquerdax[p.qtirosesquerda]=p.x-2;
        p.tiroesquerday[p.qtirosesquerda]=p.y;
        p.qtirosesquerda++;
    }
    if(p.direcao=='v'){
        p.tirobaixox[p.qtirosbaixo]=p.x+1;
        p.tirobaixoy[p.qtirosbaixo]=p.y+1;
        p.qtirosbaixo++;
    }
    if(p.direcao=='>'){
        p.tirodireitax[p.qtirosdireita]=p.x+4;
        p.tirodireitay[p.qtirosdireita]=p.y;
        p.qtirosdireita++;
    }
    return p;
}

jogador controle1(jogador p,int c){ //aqui é onde ocorre o controle do player 1;
    if(c=='w'){p.y--;p.direcao='^';}
    if(c=='a'){p.x-=2;p.direcao='<';}
    if(c=='s'){p.y++;p.direcao='v';}
    if(c=='d'){p.x+=2;p.direcao='>';}
    if(c==32)p=direcaodotiro(p);//barra de espaço
    return p;
}

jogador controle2(jogador p,int c){ //aqui é onde ocorre o controle do player 2;
    if(c=='8'){p.y--;p.direcao='^';}
    if(c=='4'){p.x-=2;p.direcao='<';}
    if(c=='5'){p.y++;p.direcao='v';}
    if(c=='6'){p.x+=2;p.direcao='>';}
    if(c=='0')p=direcaodotiro(p);//barra de espaço
    return p;
}

void desenhaplayer(jogador p,int num,int direcao){//desenha o jogador no terminal
    mvprintw(p.y,p.x,"\\%d/",num);
    //print das setas q acompanham cada player
    if(direcao=='^')
    mvprintw(p.y-1,p.x+1,"^",num);
    if(direcao=='<')
    mvprintw(p.y,p.x-2,"<",num);
    if(direcao=='v')
    mvprintw(p.y+1,p.x+1,"v",num);
    if(direcao=='>')
    mvprintw(p.y,p.x+4,">",num);
    return;
}

jogador desenhatiro(jogador p){// desenha tiros no terminal,
    int i;
    for(i=0;i<p.qtiroscima;i++){
        mvprintw(p.tirocimay[i],p.tirocimax[i],"^");
        p.tirocimay[i]-=5;
    }
    for(i=0;i<p.qtirosesquerda;i++){
        mvprintw(p.tiroesquerday[i],p.tiroesquerdax[i],"<");
        p.tiroesquerdax[i]-=5;
    }
    for(i=0;i<p.qtirosbaixo;i++){
        mvprintw(p.tirobaixoy[i],p.tirobaixox[i],"v");
        p.tirobaixoy[i]+=5;
    }
    for(i=0;i<p.qtirosdireita;i++){
        mvprintw(p.tirodireitay[i],p.tirodireitax[i],">");
        p.tirodireitax[i]+=5;
    }
    return p;
}

int main()
{
    int c=0,altura,largura,qplayers;
    printf("Insira a qnt de jogadores: ");
    scanf("%d",&qplayers);
    initscr();
    raw();
    noecho();
	curs_set(FALSE);
    getmaxyx(stdscr,altura,largura);
    nodelay(stdscr,TRUE);
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    jogador p[qplayers]; 
    p[0].x=0;p[0].y=0;
    p[1].x=largura-3;p[1].y=0;
    p[0].qtirosdireita=0;p[1].qtirosdireita=0;
    p[0].qtirosesquerda=0;p[1].qtirosesquerda=0;
    p[0].qtirosbaixo=0;p[1].qtirosbaixo=0;
    p[0].qtiroscima=0;p[1].qtiroscima=0;
    p[0].direcao='>';p[1].direcao='<';
    while(c!=127){//loop de tempo, conforme o comando passa, o jogo resume.
    c=getch();
    p[0]=controle1(p[0],c);
    if(qplayers==2) p[1]=controle2(p[1],c);
    p[0]=limite(p[0],altura,largura);
    if(qplayers==2)p[1]=limite(p[1],altura,largura);
    clear();
    attron(COLOR_PAIR(1));
    desenhaplayer(p[0],1,p[0].direcao);
    attron(COLOR_PAIR(2));
    if(qplayers==2) desenhaplayer(p[1],2,p[1].direcao);
    attron(COLOR_PAIR(3));
    p[0]=desenhatiro(p[0]);
    if(qplayers==2)p[1]=desenhatiro(p[1]);
    usleep(40000);
    }
    endwin();
    return 0;
}
