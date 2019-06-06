#include <stdio.h>
#include <ncurses.h>

void tiro(float x1,float y1,float x2,float y2){
    int x = 0;
    float tg = (y2-y1)/(x2-x1);
    while (x!=x2-x1){
        mvprintw(x1 + x,y1 + tg*(x1+x),"X");
        x++;
    }
}
