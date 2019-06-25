#ifndef JOGO_HEADER
#define JOGO_HEADER

void execute_wave(int *waveNum,float *time0,int *smallW,int *enemy_amount,
inimigo *enemy0[],inimigo *enemy1[],inimigo *enemy2[],inimigo *enemy3[],
int Y,int X){
    if(*waveNum == 0){
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
        if(time_elapsed(time0,2)&&(*smallW==1)){
            enemy0[0] = inicializa_inimigo(1,Y/2+0,X/2+0);
            enemy0[1] = inicializa_inimigo(1,Y/2+1,X/2+1);
            enemy0[2] = inicializa_inimigo(1,Y/2+2,X/2+2);
            enemy0[3] = inicializa_inimigo(1,Y/2+3,X/2+3);
            enemy0[4] = inicializa_inimigo(1,Y/2+4,X/2+4);
            *enemy_amount+=5;
            *smallW = 0;
            *waveNum = 1;

        }
    }
    if((*waveNum == 1) && *enemy_amount == 0){
        if(*smallW==0){
            enemy0[0] = inicializa_inimigo(1, Y/4, X/4);
            enemy0[1] = inicializa_inimigo(1, Y/4+1, X/4+1);
            enemy0[2] = inicializa_inimigo(1, Y/4+2, X/4+2);
            enemy0[3] = inicializa_inimigo(1, Y/4+3, X/4+3);
            enemy0[4] = inicializa_inimigo(1, Y/4+4, X/4+4);
            enemy0[5] = inicializa_inimigo(1, Y/4+5, X/4);
            enemy0[6] = inicializa_inimigo(1, Y/4+6, X/4);
            enemy0[7] = inicializa_inimigo(1, Y/4+7, X/4);
            enemy2[0] = inicializa_inimigo(1,Y+1,10);
            enemy2[1] = inicializa_inimigo(1,Y+2,10);
            enemy2[2] = inicializa_inimigo(1,Y+3,10);
            enemy2[3] = inicializa_inimigo(1,Y+4,10);
            enemy2[4] = inicializa_inimigo(1,Y+5,10);
            *enemy_amount+=13;
            *smallW=1;
            *waveNum = 2;
        }
    }
    if((*waveNum == 2) && *enemy_amount == 0){
        if(*smallW=1){

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
        if(isalnum(c) || c == ' '){
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
    float enemy0_instant,enemy1_instant,enemy2_instant,enemy3_instant
    ,controle_instant,tiros_velocidadeY,controle_tiro,tiros_velocidadeX
    ,enemy_spawn;
    //spec.tv_sec = time in seconds, spec.tv_nsec = time in nanoseg
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
    mvwprintw(statsWin,stat_maxy/2+1,2,"Vida [==========]  %d",player1->vida);
    mvwprintw(statsWin,stat_maxy/2-1,2,"Score: 0");

    
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
        execute_wave(&wave_number,&enemy_spawn,&small_wave,&enemy_amount,i0,i1,i2,i3,maxY*15/20,maxX*9/10);//INITATE FIRST WAVE
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
            colisao_tiro_inimigo_0e1(tiros_jogador,i0[cont],&score,player1,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos_0e1(player1,i0[cont],&score,&enemy_amount,statsWin,&c);
        }
        for(cont=0;cont<ENEMYTYPE1MAX;cont++){
            colisao_tiro_inimigo_0e1(tiros_jogador,i1[cont],&score,player1,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos_0e1(player1,i1[cont],&score,&enemy_amount,statsWin,&c);
        }
        for(cont=0;cont<ENEMYTYPE2MAX;cont++){
            colisao_tiro_inimigo_2(tiros_jogador,i2[cont],&score,player1,maxY,maxX,&enemy_amount,statsWin);
            colisao_player_inimigos2(player1,i2[cont],&score,&enemy_amount,statsWin,&c);
        }
    }while(c!='p');
    
    int y=0, x=0;
    if(player1->vida<=0){
        clear();
        //printem uma tela de game over maneira na stdscr aqui;
        mvprintw(y++, x,"       XXXXXXXNNNNXXXKXXNXXXXXXXXXNNNNNNNNNNNNNNNWWNNNWWWWWWWWNNWWWWNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       XXNNNNNNNNNNNXXXXXXXNNNXXNNNNNNNNNNNNNNNNNNWWNNWNNWN0dlccldOKXNNWNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNXNNNNNNNNNNNNNNNNNNWWWWNX0xoc'.... ..';lxKNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWXkl;..        ......,cx0XNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWNXk;.              ........,:lOXXNNWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWNXx'             ..............,ldxkKNWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWN0o'   ..',,''...';::::;;,'......,;;;cONWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWWNNKc. ..;okOOOkkxxxkkkxxddddlc:,'..'...;dKNWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNWNNWWWWWWWWWWWWWWWWWNX0l..,oOKXXKKKKKKKKKK00000000OOkxl,....;oOXWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNWWNWWNNWWWWWWWWWWWWWWWWNOc'..c0XXXXXXXKKKKKKKKKKKKKKKKKXXXXO;. ..:dOXWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWKl.  .cKXXXXXXXKKKK00000KKKKKKKKXXXNNNx.  ..':xNMWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWXd.   .xXXXXXXXXKKKK0000KKKKKKKXXXXXNNWK;  ...'cONWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWNo.   'kXXXXXXXXKKKK0000KK0KKKKXXXXXNNNKl.  ...;dXMWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNWNNWWWWWWWWWWWWWWWWWWWWNK0o.   ,OXXXXKK00000OOOO000kkxoloodk0XNWXl.. ..';xNWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWNKx;.   ,0KOdl::;:clldxkkkkkoc;,',;:cd0NWXo'....',dXWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWNKl.   ;0Olccc:;,;:coxOOOkxo:;;:looodkOKXx,....';OWWWWWWWWMWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWXc.  .'cdddol:,..',clloollc,....';lxko,cd;....':OWWWWMMWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWNk,  ..;xkl;,....',cloxkdccc,''..,coxkdkxl,..;oONWWWMWWMWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWNO,  'okxololccloddlxKK0ocxdollloxkkkKWXo..'lkXNWMWWMMWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNWWWNNNNNNNNNWNWWWWWWWWWWWWXd..:OOO0OkkxkkOOkOKKKKKOxddxxddxk0XNWNk,'o00XWWWWWWWWWMMWWMMWWWW");
        mvprintw(y++, x,"       NNNNNNNNWWWWWNNNNNWWWWWWWWWWWWWWWWWWKc.,0XKK00OkxxxkKKK00KXX0xlldkkOKXNWWWk;cOXNWWWWWWWWWWWMWMMMWWWW");
        mvprintw(y++, x,"       NNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW0::ONNNXKOdldkkxdxxxxdx0klcdkO0KXNWWNkox0XWWWWWWWWWWWWWWMMMMWWM");
        mvprintw(y++, x,"       NNNNNNWNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWNOlkNXX0xlcoxxo;,;;;'..,colccdk0KXNNXdo0XNWWWWWWWWWWWWWWMMMWWMM");
        mvprintw(y++, x,"       NNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWKod000x:,;::;,...',....,;;,',:dOKKX0ldNNNWWWWWWWWWWWWWWMMMWWMM");
        mvprintw(y++, x,"       NNNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWOldkxc...:odoccllll::codo;'..:x00OdlkNNWWWWWWWWWWWWWWWMMMWWWW");
        mvprintw(y++, x,"       NNNNNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWKo:ldl,,::;:lxxxxxkxddxo;,;::okkkxlcOXWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNWWWWWWWWWWWWWWNX0kk0XNNWWWWWWWNd,,colldo:;oOkOK000kkkl:loldkxoddclKWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNWNNNNWWWWWWWNKd:,....,coOXWWWWWW0:'':oox00OkkxkkxxxxxkO00xodo::oc;xNWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNWWWNKd,.       ..'dNWWWWWNk,..;lxOKK00Okxdoddx0XK0kl;',;,,oKWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNNNNNNNNNNN0c.           .;0NNNWWWNk,..;oO0K0Okxl:;;coxOkd:,,,,',dKWWWWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       XXXXXXXXXXXXXXXXXKd'            .'d0KNNKKXN0:..'o0KKK0Oo::ldddoc;..'',cxXWNNNWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       XXXXXXXXXXXXXXXXK0x:.          ..'oO0XKddKNNKl. .lxk00ko::ccc:,''.':ox0XNWNNNWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNNNNNNNXXNNNNNNNXX0o,.         .:0XXNKolKNNNKo'...';:;'..'''....;d0KKKNNWNKXWWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       NNKkdlc:::cd0XNXXXX0xo:.        ,ONWWWNOxKWNNXKxc,.............,lxOOO0KNWMNdlKWWWWWWWWWWWWWWWWWWWWWW");
        mvprintw(y++, x,"       Kk:....;::c:lk0KKK0kodko,.   ..;kNWWNWNXKXNNNNX0kddoc;'.....';clodO0KXXWWWWx.,dKNWWWWWNWWWWWWWWWWWWW");
        mvprintw(y++, x,"       d'  .cx0KKXXKKKKK000OxO0Odc''cxOXNNNNNNXXNNNNNWXKOkkxxxolccloodxOKNNNXNNWWMx...,oONNNNNNNWWWWWWWWWWW");
        mvprintw(y++, x,"       ;   'looddxxdodkkxk0K0KKOo,...',lkKXXXXXXXKdl0WNNNNXK0OOkkkkOKXNNNXXNNNWWMWl......:oxO0XXNNNNNNNNNNN");
        mvprintw(y++, x,"       ;   'loloc....,od:,,::c:.      ...:dO0Odc;;:o0WNNNNNNNX0kk0XNNNNNNNNNNWWWW0, ....    .';:loxk0000KXN");
        mvprintw(y++, x,"       l.  .cdxxl'. .l00o. ...         .....'.   ,0NXNXXXXXNXKKKKXNNNNNNNNNNNNWNNx.               ..,;cokXN");
        mvprintw(y++, x,"       kc....,cdxdoc';c:'.         ......        .dNXK00000KKXXXXXNNNWNNNNNNNNNXKo.                    ..,:");
        mvprintw(y++, x,"       kxl;'...ck0x;.            .....            'kNKKKKKKKK000O0KXNNNXXXXNNXXKKc                         ");
        mvprintw(y++, x,"       ;'..  ..:xd;.       .......                 lNNXXXKK0000000KKKXXXK0KXNXKKO,                         ");
        mvprintw(y++, x,"               .,,.     ......                     oNXKKKKK0OO00KK0000KNK0KXXXKKO,                         ");
        mvprintw(y++, x,"       llllllooodddddc.                           .dNXXKXXNXXKXXXXXXXXXKKKXNXKKXO;                         ");
        mvprintw(y++, x,"       NNNNNNNNNNNNNK:.                        .. .kNNXXXXNNNXNNNNNNNXXXXNNNKKXXk.                         ");
        mvprintw(y++, x,"       NNNNNNNNNNNNNd.                       ...  ;0NNXXXXXNNNNNNNNNNNNNNNNXKXXNo.         . .             ");
        mvprintw(y++, x,"       NNNNNNNNNNNNXc                 .     .... .lXNNNNXXXXNNNNNNNNNNNNNNXXXXNXc           ..             ");
        mvprintw(y++, x,"       NNNNNNNNNNNKl.                 .     .... .xNNNNNXXXXXNNNNNNNNNNNNXXXXXN0;                          ");
        mvprintw(y++, x,"       NNNNNNNNNNKc.                 ..  ....... 'OWNNNNXXXXXNNNNNNNNNNNXXXXXNWO'                          ");
        mvprintw(y++, x,"       NNNNNNNNNXo.                  .. ........ ;KWNNNNXXXXXNNNNNNNNNNXXXXXXNWk.                          ");
        //printem o score estilisado se quiserem tbm;
        mvprintw(maxY-2, -70+maxX/2,"Fim de Jogo! Infelizmente, não foi possível provar suas habilidades...");
        getch();
        sleep(10);    
    }
    
    return score;
}

#endif

