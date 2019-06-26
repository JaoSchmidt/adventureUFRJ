#ifndef JOGO_HEADER
#define JOGO_HEADER
 
void execute_wave(int *waveNum,float *time0,int *smallW,int *enemy_amount,
inimigo *enemy0[],inimigo *enemy1[],inimigo *enemy2[],
int Y,int X, WINDOW *stats,int maxy,int maxx,int *pc){
    if(*waveNum == 0){
        if(*smallW==0){
            enemy1[0] = inicializa_inimigo(1,10+0,10-2*0);
            enemy1[1] = inicializa_inimigo(1,10+1,10-2*1);
            enemy1[2] = inicializa_inimigo(1,10+2,10-2*2);
            enemy1[3] = inicializa_inimigo(1,10+3,10-2*3);
            enemy1[4] = inicializa_inimigo(1,10+4,10-2*4);
            enemy2[0] = inicializa_inimigo(1,20-3*0,10);
            enemy2[1] = inicializa_inimigo(1,20-3*1,11);
            enemy2[2] = inicializa_inimigo(1,20-3*2,12);
            enemy2[3] = inicializa_inimigo(1,20-3*3,13);
            enemy2[4] = inicializa_inimigo(1,20-3*4,14);
            *enemy_amount+=10;
            *smallW = 1;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
        if(time_elapsed(time0,3)&&(*smallW==1)){
            enemy0[0] = inicializa_inimigo(1,Y/2+0,X/2+0);
            enemy0[1] = inicializa_inimigo(1,Y/2+1,X/2+1);
            enemy0[2] = inicializa_inimigo(1,Y/2+2,X/2+2);
            enemy0[3] = inicializa_inimigo(1,Y/2+3,X/2+3);
            enemy0[4] = inicializa_inimigo(1,Y/2+4,X/2+4);
            *enemy_amount+=5;
            *smallW = 0;
            *waveNum = 1;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
    }
    if((*waveNum == 1) && *enemy_amount == 0){
        if(*smallW==0){
            enemy0[0] = inicializa_inimigo(1, Y/4, X/4);
            enemy0[1] = inicializa_inimigo(1, 2+Y/4, X/4);
            enemy0[2] = inicializa_inimigo(1, 5+Y/4, X/4);
            enemy0[3] = inicializa_inimigo(1, 7+Y/4, X/4);
            enemy0[4] = inicializa_inimigo(1, 10+Y/4, X/4);
            enemy0[5] = inicializa_inimigo(1, 12+Y/4, X/4);
            enemy0[6] = inicializa_inimigo(1, 15+Y/4, X/4);
            enemy0[7] = inicializa_inimigo(1, 17+Y/4, X/4);
            enemy2[0] = inicializa_inimigo(1,Y-1,10);
            enemy2[1] = inicializa_inimigo(1,Y-3,15);
            enemy2[2] = inicializa_inimigo(1,Y-5,20);
            enemy2[3] = inicializa_inimigo(1,Y-7,25);
            enemy2[4] = inicializa_inimigo(1,Y-9,30);
            *enemy_amount+=13;
            *smallW=1;
            *waveNum = 2;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
    }
    if((*waveNum == 2) && *enemy_amount == 0){
        if(*smallW==1){
            enemy1[0] = inicializa_inimigo(1, Y/2, X/3);
            enemy1[1] = inicializa_inimigo(1, -3+Y/2, 1+X/3);
            enemy1[2] = inicializa_inimigo(1, -6+Y/2, 2+X/3);
            enemy1[3] = inicializa_inimigo(1, -9+Y/2, 3+X/3);
            enemy2[0] = inicializa_inimigo(1, -12+Y/2, 4+X/3);
            enemy2[1] = inicializa_inimigo(1, -15+Y/2, 5+X/3);
            enemy2[2] = inicializa_inimigo(1, -18+Y/2, 6+X/3);
            enemy2[3] = inicializa_inimigo(1, -21+Y/2, 7+X/3);
            *enemy_amount+=8;
            *smallW = 0;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
        if(time_elapsed(time0,3)&&(*smallW==0)){
            enemy1[4] = inicializa_inimigo(1, Y/2, X/3);
            enemy1[5] = inicializa_inimigo(1, -3+Y/2, 1+X/3);
            enemy1[6] = inicializa_inimigo(1, -6+Y/2, 2+X/3);
            enemy1[7] = inicializa_inimigo(1, -9+Y/2, 3+X/3);
            enemy2[4] = inicializa_inimigo(1, -12+Y/2, 4+X/3);
            enemy2[5] = inicializa_inimigo(1, -15+Y/2, 5+X/3);
            enemy2[6] = inicializa_inimigo(1, -18+Y/2, 6+X/3);
            enemy2[7] = inicializa_inimigo(1, -21+Y/2, 7+X/3);
            *enemy_amount+=8;
            *smallW = 1;
            *waveNum = 3;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
    }
    if((*waveNum == 3) && *enemy_amount == 0){
        if(*smallW==1){
            enemy2[0] = inicializa_inimigo(1, Y/2, X/2);
            enemy2[1] = inicializa_inimigo(1, 3+Y/4, X/2);
            enemy2[2] = inicializa_inimigo(1, 3-Y/4, X/2);
            enemy2[3] = inicializa_inimigo(1, 6+Y/4, X/2);
            enemy2[4] = inicializa_inimigo(1, 6-Y/4, X/2);
            enemy0[0] = inicializa_inimigo(1, 9+Y/4, X/4);
            enemy0[1] = inicializa_inimigo(1, 9-Y/4, X/4);
            enemy0[2] = inicializa_inimigo(1, 12+Y/2, X/4);
            enemy0[3] = inicializa_inimigo(1, 12-Y/2, X/4);
            enemy0[4] = inicializa_inimigo(1, 15+Y/2, X/4);
            enemy1[0] = inicializa_inimigo(1, 15-Y/2, X/2);
            enemy1[1] = inicializa_inimigo(1, 18+Y/2, X/2);
            enemy1[2] = inicializa_inimigo(1, 18-Y/2, X/2);
            enemy1[3] = inicializa_inimigo(1, 21+Y/2, X/2);
            enemy1[4] = inicializa_inimigo(1, 21-Y/2, X/2);
            *enemy_amount+=15;
            *smallW = 0;
            *waveNum = 4;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
    }
    if((*waveNum == 4) && *enemy_amount == 0){
        if(*smallW==0){
            enemy1[0] = inicializa_inimigo(1,Y/2, X/3);
            enemy1[1] = inicializa_inimigo(1,Y/4, X/3);
            enemy1[2] = inicializa_inimigo(1,Y/8, X/3);
            enemy1[3] = inicializa_inimigo(1,Y/16, X/6);
            enemy1[4] = inicializa_inimigo(1,Y/2, X/6);
            enemy1[5] = inicializa_inimigo(1,Y/4, X/6);
            enemy1[6] = inicializa_inimigo(1,Y/8, X/9);
            enemy1[7] = inicializa_inimigo(1,Y/16, X/9);
            enemy1[8] = inicializa_inimigo(1, -5+Y/2, X/9);
            enemy1[9] = inicializa_inimigo(1, -10+Y/2, X/9);
            enemy1[10] = inicializa_inimigo(1,Y/3, 10);
            enemy1[11] = inicializa_inimigo(1,Y/5, 15);
            enemy1[12] = inicializa_inimigo(1,Y/7, 20);
            enemy1[13] = inicializa_inimigo(1,Y/9, 25);
            *enemy_amount+=14;
            *smallW = 1;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
        if(time_elapsed(time0,5)&&(*smallW==1)){
            enemy2[0] = inicializa_inimigo(1, 17, 13);
            enemy2[1] = inicializa_inimigo(1, 2, 10);
            enemy2[2] = inicializa_inimigo(1, 5, 10);
            enemy2[3] = inicializa_inimigo(1, 7, 10);
            enemy2[4] = inicializa_inimigo(1, 9, 10);
            enemy2[5] = inicializa_inimigo(1, 10, 15);
            enemy2[6] = inicializa_inimigo(1, 2, 20);
            enemy2[7] = inicializa_inimigo(1, 5, 20);
            enemy2[8] = inicializa_inimigo(1, 7, 20);
            enemy2[9] = inicializa_inimigo(1, 9, 20);
            enemy2[10] = inicializa_inimigo(1, 25, 15);
            enemy2[11] = inicializa_inimigo(1, 20, 15);
            enemy2[12] = inicializa_inimigo(1, 15, 15);
            enemy2[13] = inicializa_inimigo(1, 13, 15);
            *enemy_amount+=14;
            enemy0[0] = inicializa_inimigo(1, 5, 1);
            enemy0[1] = inicializa_inimigo(1, 5, 5);
            enemy0[2] = inicializa_inimigo(1, 5, 9);
            enemy0[3] = inicializa_inimigo(1, 5, 13);
            enemy0[4] = inicializa_inimigo(1, 5, 17);
            enemy0[5] = inicializa_inimigo(1, 5, 21);
            enemy0[6] = inicializa_inimigo(1, 5, 25);
            enemy0[7] = inicializa_inimigo(1, 5, 29);
            enemy0[8] = inicializa_inimigo(1, 5, 33);
            enemy0[9] = inicializa_inimigo(1, 5, 37);
            enemy0[10] = inicializa_inimigo(1, 5, 3);
            enemy0[11] = inicializa_inimigo(1, 10, 3);
            enemy0[12] = inicializa_inimigo(1, 15, 3);
            enemy0[13] = inicializa_inimigo(1, 20, 3);
            *enemy_amount+=14;
            *waveNum = 5;
            mvwprintw(stats,maxy/2+1,maxx/2,"Enemies alive: %d%d",((*enemy_amount)/10)%10,(*enemy_amount)%10);
            wrefresh(stats);
        }
    }
    if((*waveNum == 5) && *enemy_amount == 0){
        *pc = 'p';  
    }
}
 
 
 
void write_your_initials(char *destino){
    mvprintw(1,2,"Olá! O hugonobrega.com está em apuros! Quem irá tentar salvá-lo? (Pressione 'p' para voltar durante o jogo)\n");
    refresh();
    char a[50],*pa;
    pa = a;
    char c;
    move(2,2);
    while((c = getch())!='\n'){
        if(isalnum(c)){
            refresh();
            addch(c);
            *pa = c;
            *destino = *pa;
            destino++;
            pa++;
        }
    }
}
 
int game(){  
    //start input c
    int c=0;
    int score=0;
    int wave_number = 0;
    int small_wave = 0;
    int enemy_amount = 0;
 
    //INITIATE time counting
    clock_gettime(CLOCK_MONOTONIC,&spec); //this define the time function
    float enemy0_instant,enemy1_instant,enemy2_instant
    ,controle_instant,tiros_velocidadeY,controle_tiro,tiros_velocidadeX
    ,enemy_spawn;
    //spec.tv_sec = time in seconds, spec.tv_nsec = time in nanoseg
    //those varivables control the time of each entity
    enemy0_instant = spec.tv_sec + ((float)spec.tv_nsec/1.0e9);
    enemy1_instant = enemy0_instant;
    enemy2_instant = enemy0_instant;
    controle_instant = enemy0_instant;
    tiros_velocidadeY = enemy0_instant;
    controle_tiro = enemy0_instant;
    enemy_spawn = enemy0_instant;
    tiros_velocidadeX = enemy0_instant;
 
    //INITIATE new windows in function of standart window
    //function newwin(height, width, start_y,stat_x)
    int maxY, maxX,stat_maxx,stat_maxy;
    getmaxyx(stdscr,maxY,maxX);
    WINDOW *playerWin = newwin(maxY*15/20,maxX*9/10,maxY*1/20,maxX*1/20);
    WINDOW *borderPlayerWin = newwin(maxY*15/20+2,maxX*9/10+2,maxY*1/20-1,maxX*1/20-1);
    WINDOW *statsWin = newwin(maxY*3/20,maxX*9/10+2,maxY*16/20+1,maxX*1/20-1);
    getmaxyx(statsWin,stat_maxy,stat_maxx);
    wborder(borderPlayerWin,'#','#','#','#','#','#','#','#');
    wrefresh(borderPlayerWin);//refresh the window
   
 
    //INITIATE STATS AND PLAYER
    jogador *player1 = inicializajogador(playerWin,15,50);//newplayer player1
    desenhaplayer(player1,1);
    mvwprintw(statsWin,stat_maxy/2+1,2,"Vida [=====]  %d",player1->vida);
    mvwprintw(statsWin,stat_maxy/2-1,2,"Score: 0");
    mvwprintw(statsWin,stat_maxy/2+1,stat_maxx/2,"Enemies alive: 10");
 
   
    wrefresh(statsWin);
 
    keypad(stdscr,TRUE);//allow keyboard arrows
    curs_set(FALSE);//make cursor invisible
    //nodelay(playerWin,TRUE);//allow getch() be skiped case no input is recived
   
    //game colors, in pairs
    //init_pair(index, foreground, background);
    use_default_colors();//allow default background color with -1
    start_color();
    init_pair(1,COLOR_GREEN,-1);
    init_pair(2,COLOR_BLUE,-1);
    init_pair(3,COLOR_WHITE,-1);
    init_pair(4,COLOR_RED,-1);
    //attron(A_BOLD);
    //INITIATE shots
    tiro *tiros_jogador[MAX_SHOTS];
    int cont;
    for(cont=0;cont<MAX_SHOTS;cont++){
        tiros_jogador[cont] = inicializa_tiro(playerWin);
    }
 
    //INITIATE ENEMIES
    inimigo *i0[ENEMYTYPE0MAX];
    inimigo *i1[ENEMYTYPE1MAX];
    inimigo *i2[ENEMYTYPE2MAX];
    for(cont=0;cont<ENEMYTYPE0MAX;cont++)//INITIATE ENEMY0
        i0[cont]=inicializa_inimigo(0,0,0);
    for(cont=0;cont<ENEMYTYPE1MAX;cont++)//INITIATE ENEMY1
        i1[cont]=inicializa_inimigo(0,0,0);
    for(cont=0;cont<ENEMYTYPE2MAX;cont++)//INITIATE ENEMY2
        i2[cont]=inicializa_inimigo(0,0,0);
 
    wtimeout(playerWin,1);
    do{//time loop, as time passes, the game run
        c = controle(player1,&controle_tiro,&controle_instant,tiros_jogador);
        execute_wave(&wave_number,&enemy_spawn,&small_wave,&enemy_amount,i0,i1,i2,maxY*15/20,maxX*9/10,statsWin,stat_maxy,stat_maxx,&c);//INITATE FIRST WAVE
        ////PLAYER MOVMENT
        wattron(playerWin,COLOR_PAIR(2));
        desenhaplayer(player1,1);
        colisao_tiro(tiros_jogador,maxY,maxX);
        if(time_elapsed(&tiros_velocidadeY,0.05)){
            desenhatiroY(tiros_jogador,player1);//draw the shots on y axis
        }
        if(time_elapsed(&tiros_velocidadeX,0.025)){
            desenhatiroX(tiros_jogador,player1);//draw the shots on x axis
        }
        wattroff(playerWin,COLOR_PAIR(2));
        //ENEMY MOVMENT
        wattron(playerWin,COLOR_PAIR(4));
        if(time_elapsed(&enemy0_instant,0.6)){
            for(cont=0;cont<ENEMYTYPE0MAX;cont++){//enemies0 control
                controle_inimigo0(i0[cont],player1);
            }
        }
        if(time_elapsed(&enemy1_instant,0.4)){
            for(cont=0;cont<ENEMYTYPE1MAX;cont++){//enemies1 control
                controle_inimigo_1(i1[cont],player1);
            }
        }
        if(time_elapsed(&enemy2_instant,0.4)){
            for(cont=0;cont<ENEMYTYPE1MAX;cont++){//enemies2 control
                controle_inimigo_2(i2[cont],player1);
            }
        }
        wattroff(playerWin,COLOR_PAIR(4));
        //SHOTS AND PLAYER COLISION
        for(cont=0;cont<ENEMYTYPE0MAX;cont++){
            colisao_tiro_inimigo_0e1(tiros_jogador,i0[cont],&score,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos_0e1(player1,i0[cont],&score,&enemy_amount,statsWin,&c);
        }
        for(cont=0;cont<ENEMYTYPE1MAX;cont++){
            colisao_tiro_inimigo_0e1(tiros_jogador,i1[cont],&score,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos_0e1(player1,i1[cont],&score,&enemy_amount,statsWin,&c);
        }
        for(cont=0;cont<ENEMYTYPE2MAX;cont++){
            colisao_tiro_inimigo_2(tiros_jogador,i2[cont],&score,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos2(player1,i2[cont],&score,&enemy_amount,statsWin,&c);
        }
    }while(c!='p');
    if(wave_number==5){
        clear();
        mvprintw(-47+maxY/2,-47+maxX/2,"Vitória! Você provou, por absurdo, que é digno de criptografar!");
        refresh();
        sleep(2);
    }
    int y=0, x=0;
    if(player1->vida<=0){
        clear();
 
        mvprintw(y++, x,"           XXXXXXXNNNNXXXKXXNXXXXXXXXXNNNNNNNNNNNNNNNWWNNNWWWWWWWWNNWWWWNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           XXNNNNNNNNNNNXXXXXXXNNNXXNNNNNNNNNNNNNNNNNNWWNNWNNWN0dlccldOKXNNWNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNXNNNNNNNNNNNNNNNNNNWWWWNX0xoc'.... ..';lxKNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWXkl;..        ......,cx0XNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWNXk;.              ........,:lOXXNNWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWNXx'             ..............,ldxkKNWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWN0o'   ..',,''...';::::;;,'......,;;;cONWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWWNNKc. ..;okOOOkkxxxkkkxxddddlc:,'..'...;dKNWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNWNNWWWWWWWWWWWWWWWWWNX0l..,oOKXXKKKKKKKKKK00000000OOkxl,....;oOXWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNWWNWWNNWWWWWWWWWWWWWWWWNOc'..c0XXXXXXXKKKKKKKKKKKKKKKKKXXXXO;. ..:dOXWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWKl.  .cKXXXXXXXKKKK00000KKKKKKKKXXXNNNx.  ..':xNMWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWXd.   .xXXXXXXXXKKKK0000KKKKKKKXXXXXNNWK;  ...'cONWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWNo.   'kXXXXXXXXKKKK0000KK0KKKKXXXXXNNNKl.  ...;dXMWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNWNNWWWWWWWWWWWWWWWWWWWWNK0o.   ,OXXXXKK00000OOOO000kkxoloodk0XNWXl.. ..';xNWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWNKx;.   ,0KOdl::;:clldxkkkkkoc;,',;:cd0NWXo'....',dXWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWNKl.   ;0Olccc:;,;:coxOOOkxo:;;:looodkOKXx,....';OWWWWWWWWMWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWXc.  .'cdddol:,..',clloollc,....';lxko,cd;....':OWWWWMMWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWNk,  ..;xkl;,....',cloxkdccc,''..,coxkdkxl,..;oONWWWMWWMWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWNO,  'okxololccloddlxKK0ocxdollloxkkkKWXo..'lkXNWMWWMMWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNWWWNNNNNNNNNWNWWWWWWWWWWWWXd..:OOO0OkkxkkOOkOKKKKKOxddxxddxk0XNWNk,'o00XWWWWWWWWWMMWWMMWWWW");
        mvprintw(y++, x,"           NNNNNNNNWWWWWNNNNNWWWWWWWWWWWWWWWWWWKc.,0XKK00OkxxxkKKK00KXX0xlldkkOKXNWWWk;cOXNWWWWWWWWWWWMWMMMWWWW");
        mvprintw(y++, x,"           NNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW0::ONNNXKOdldkkxdxxxxdx0klcdkO0KXNWWNkox0XWWWWWWWWWWWWWWMMMMWWM");
        mvprintw(y++, x,"           NNNNNNWNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWNOlkNXX0xlcoxxo;,;;;'..,colccdk0KXNNXdo0XNWWWWWWWWWWWWWWMMMWWMM");
        mvprintw(y++, x,"           NNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWKod000x:,;::;,...',....,;;,',:dOKKX0ldNNNWWWWWWWWWWWWWWMMMWWMM");
        mvprintw(y++, x,"           NNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWOldkxc...:odoccllll::codo;'..:x00OdlkNNWWWWWWWWWWWWWWWMMMWWWW");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWKo:ldl,,::;:lxxxxxkxddxo;,;::okkkxlcOXWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNWWWWWWWWWWWWWWNX0WW0XNNWWWWWWWNd,,colldo:;oOkOK000kkkl:loldkxoddclKWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNWNNNNWWWWWWWWWWWWWWWWWWWWXWWWWWW0:'':oox00OkkxkkxxxxxkO00xodo::oc;xNWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWNk,..;lxOKK00Okxdoddx0XK0kl;',;,,oKWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNXXXXXXXXXXXXXXXXXNNNWWWNk,..;oO0K0Okxl:;;coxOkd:,,,,',dKWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           XXXXXXXXXXXXXXXXXKXXXXXXXXXXXXXXXXX0KNNKKXN0:..'o0KKK0Oo::ldddoc;..'',cxXWNNNWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXO0XKddKNNKl. .lxk00ko::ccc:,''.':ox0XNWNNNWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWW0XXNKolKNNNKo'...';:;'..'''....;d0KKKNNWNKXWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWONWWWNOxKWNNXKxc,.............,lxOOO0KNWMNdlKWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWNWWNWNXKXNNNNX0kddoc;'.....';clodO0KXXWWWWx.,dKNWWWWWNWWWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWNNNNNNXXNNNNNWXKOkkxxxolccloodxOKNNNXNNWWMx...,oONNNNNNNWWWWWWWWWWW");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWlkKXXXXXXXKdl0WNNNNXK0OOkkkkOKXNNNXXNNNWWMWl......:oxO0XXNNNNNNNNNNN");
        mvprintw(y++, x,"           NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWW:dO0Odc;;:o0WNNNNNNNX0kk0XNNNNNNNNNNWWWW0, ....    .';:loxk0000KXN");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNKWWWWWWWWWW.....'.   ,0NXNXXXXXNXKKKKXNNNNNNNNNNNNWNNx.               ..,;cokXN");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNKWWWWWWWWW......        .dNXK00000KKXXXXXNNNWNNNNNNNNNXKo.                    ..,:");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNNNNK.....            'kNKKKKKKKK000O0KXNNNXXXXNNXXKKc                         ");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNNNK.......                 lNNXXXKK0000000KKKXXXK0KXNXKKO,                         ");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNNNK......                     oNXKKKKK0OO00KK0000KNK0KXXXKKO,                         ");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNNNK.                           .dNXXKXXNXXKXXXXXXXXXKKKXNXKKXO;                         ");
        mvprintw(y++, x,"           NNNNNNNNNNNNNNK:.                        .. .kNNXXXXNNNXNNNNNNNXXXXNNNKKXXk.                         ");
        mvprintw(y++, x,"           NNNNNNNNNNNNNd.                       ...  ;0NNXXXXXNNNNNNNNNNNNNNNNXKXXNo.         . .             ");
        mvprintw(y++, x,"           NNNNNNNNNNNNXc                 .     .... .lXNNNNXXXXNNNNNNNNNNNNNNXXXXNXc           ..             ");
        mvprintw(y++, x,"           NNNNNNNNNNNKl.                 .     .... .xNNNNNXXXXXNNNNNNNNNNNNXXXXXN0;                          ");
        mvprintw(y++, x,"           NNNNNNNNNNKc.                 ..  ....... 'OWNNNNXXXXXNNNNNNNNNNNXXXXXNWO'                          ");
        mvprintw(y++, x,"           NNNNNNNNNXo.                  .. ........ ;KWNNNNXXXXXNNNNNNNNNNXXXXXXNWk.                          ");
        wattroff(stdscr, COLOR_PAIR(2));
        mvprintw(maxY-2, -70+maxX/2,"       Fim de Jogo! Infelizmente, não foi possível provar suas habilidades...");
        refresh();
        sleep(4);
        getch();
    }
   
    return score;
}
 
#endif
