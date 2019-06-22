#ifndef JOGO_HEADER
#define JOGO_HEADER

void execute_wave(int waveN,float *time0,int *smallW,int *enemy_amount,
inimigo *enemy0[],inimigo *enemy1[],inimigo *enemy2[],inimigo *enemy3[],
int Y,int X){
    if(waveN == 0){
        if(*smallW==0){
            enemy1[0] = inicializa_inimigo(1,10,10-0);
            enemy1[1] = inicializa_inimigo(1,11,10-1);
            enemy1[2] = inicializa_inimigo(1,12,10-2);
            enemy1[3] = inicializa_inimigo(1,13,10-3);
            enemy1[4] = inicializa_inimigo(1,14,10-4);
            enemy2[0] = inicializa_inimigo(1,20,10);
            enemy2[1] = inicializa_inimigo(1,21,11);
            enemy2[2] = inicializa_inimigo(1,22,12);
            enemy2[3] = inicializa_inimigo(1,23,13);
            enemy2[4] = inicializa_inimigo(1,24,14);
            *enemy_amount+=10;
            *smallW = 1;
            
        }
        if(time_elapsed(time0,4)&&(*smallW==1)){
            enemy0[0] = inicializa_inimigo(1,Y/2+0,X/2+0);
            enemy0[1] = inicializa_inimigo(1,Y/2+1,X/2+1);
            enemy0[2] = inicializa_inimigo(1,Y/2+2,X/2+2);
            enemy0[3] = inicializa_inimigo(1,Y/2+3,X/2+3);
            enemy0[4] = inicializa_inimigo(1,Y/2+4,X/2+4);
            *enemy_amount+=5;
            *smallW = 2;
        }
    }
}

void write_your_initials(char *destino){
    mvprintw(1,2,"Escreva o nome do jogador\n");
    char a[50],*pa;
    pa = a;
    char c;
    move(2,2);
    while((c = getch())!='\n'){
        refresh();
        addch(c);
        *pa = c;
        *destino = *pa;
        destino++;
        pa++;
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
    float enemy0_instant,enemy1_instant,enemy2_instant,enemy3_instant
    ,controle_instant,tiros_velocidadeY,controle_tiro,tiros_velocidadeX
    ,enemy_spawn;
    //spec.tv_sec = tempo em segundos, spec.tv_nsec = tempo em nanoseg
    //those varivables control the time of each entity
    enemy0_instant = spec.tv_sec + ((float)spec.tv_nsec/1.0e9);
    enemy1_instant = enemy0_instant;
    enemy2_instant = enemy0_instant;
    enemy3_instant = enemy0_instant;
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
    int remaning_enemies = 25;//please put the number of enemies in wave 0;
    mvwprintw(statsWin,stat_maxy/2+1,2,"Vida [==========]  %d",player1->vida);
    mvwprintw(statsWin,stat_maxy/2-1,2,"Score: 0");
    mvwprintw(statsWin,stat_maxy/2-1,stat_maxx/2 +2,"remaning_enemies %d",remaning_enemies);

    
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
    inimigo *i3[ENEMYTYPE3MAX];
    for(cont=0;cont<ENEMYTYPE0MAX;cont++)//INITIATE ENEMY0
        i0[cont]=inicializa_inimigo(0,0,0);
    for(cont=0;cont<ENEMYTYPE1MAX;cont++)//INITIATE ENEMY1
        i1[cont]=inicializa_inimigo(0,0,0);
    for(cont=0;cont<ENEMYTYPE2MAX;cont++)//INITIATE ENEMY2
        i2[cont]=inicializa_inimigo(0,0,0);
    for(cont=0;cont<ENEMYTYPE3MAX;cont++)//INITIATE ENEMY3
        i3[cont]=inicializa_inimigo(0,0,0);

    wtimeout(playerWin,1);
    do{//time loop, as time passes, the game run
        c = controle(player1,&controle_tiro,&controle_instant,tiros_jogador);
        execute_wave(wave_number,&enemy_spawn,&small_wave,&enemy_amount,i0,i1,i2,i3,maxY*15/20,maxX*9/10);//INITATE FIRST WAVE
        ////MOVIMENTO JOGADOR
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
        //MOVIMENTO INIMIGO
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
        //COLISAO ENTRE TIRO E PLAYER
        for(cont=0;cont<ENEMYTYPE0MAX;cont++){
            colisao_tiro_inimigo_0e1(tiros_jogador,i0[cont],&score,player1,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos_0e1(player1,i0[cont],&score,&enemy_amount,statsWin);
        }
        for(cont=0;cont<ENEMYTYPE1MAX;cont++){
            colisao_tiro_inimigo_0e1(tiros_jogador,i1[cont],&score,player1,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos_0e1(player1,i1[cont],&score,&enemy_amount,statsWin);
        }
        for(cont=0;cont<ENEMYTYPE2MAX;cont++){
            colisao_tiro_inimigo_2(tiros_jogador,i2[cont],&score,player1,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos2(player1,i2[cont],&score,&enemy_amount,statsWin);
        }
    }while(c!='p');

    if(player1->vida==0){
        //printem uma tela de game over maneira na stdscr aqui;
        //printem o score estilisado se quiserem tbm;
        getch();
    }
    return score;
}

#endif

