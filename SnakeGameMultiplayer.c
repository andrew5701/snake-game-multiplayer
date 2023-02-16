#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>

int i, k, x, y, r, length = 2, length2 = 2, ch = 4, ch2 = 4, check = 10, keycheck = 10, keycheck2 = 10;
int oldx, oldy;
int trophyx, trophyy;
int timer;
int step = +1, step2 = +1;
int speed = 100000;
int count1 = 0;
int randomtime = 0;
int direction = 0, direction2 = 0;

char body[] = "0";
int xarray[300] = {0}, yarray[300] = {0};
int xarray2[300] = {0}, yarray2[300] = {0};

bool xcheck, ycheck, begincheck = true, gameover = false;
bool xcheck2,ycheck2 = true, p2check = false;


struct snake{
    int x, y;
    struct snake *next;
};

// Create Borders
void borders() {
    initscr(); // Start Screen
    clear(); // Clear screen and start drawing

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    
    attron(A_BOLD);

    // Rows
    for(i = 0; i < LINES; i++) {
        // Left Column
        move(i, 0);
        addstr("|");

        /// Right Column
        move(i, COLS-1);
        addstr("|");
    }

    // Columns
    for (i = 0; i < COLS; i++) {
        // Top Row
        move(0, i);
        addstr("-");

        // Bottom Row
        move(LINES-1, i);
        addstr("-");
    }
    refresh();
    // attroff(COLOR_PAIR(1));
    // attroff(A_BOLD);

    // Top Corners
    move(0, 0);
    addstr("#");
    move(0, COLS-1);
    addstr("#");

    // Bottom Corners
    move(LINES-1, 0);
    addstr("#");
    move(LINES-1, COLS-1);
    addstr("#");
}

void placetrophy() {
    if(timer == 0){
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    r = rand() % 9 + 1;
    randomtime = rand() % 9 + 1;

    trophyx = rand()%(LINES - 1);
    trophyy = rand()%(COLS - 1);

    for(k = 1; k < length; k++){    
        while(trophyy == 0 || trophyy == COLS-1 || trophyx == 0 || trophyx == LINES-1 || trophyx > LINES-1 || trophyx < 0 || trophyy > COLS-1 || trophyy < 0 || xarray[k] == trophyx || yarray[k] == trophyy){
            trophyx = rand()%(LINES - 1);
            trophyy = rand()%(COLS - 1);
        }
        if(trophyy == 0 && trophyy == COLS-1 && trophyx == 0 && trophyx == LINES-1 && trophyx > LINES-1 && trophyx < 0 && trophyy > COLS-1 && trophyy < 0 && xarray[k] != trophyx && yarray[k] != trophyy){
            break;
        }
    }
    for(k = 1; k < length2; k++){    
        while(trophyy == 0 || trophyy == COLS-1 || trophyx == 0 || trophyx == LINES-1 || trophyx > LINES-1 || trophyx < 0 || trophyy > COLS-1 || trophyy < 0 || xarray2[k] == trophyx || yarray2[k] == trophyy){
            trophyx = rand()%(LINES - 1);
            trophyy = rand()%(COLS - 1);
        }
        if(trophyy == 0 && trophyy == COLS-1 && trophyx == 0 && trophyx == LINES-1 && trophyx > LINES-1 && trophyx < 0 && trophyy > COLS-1 && trophyy < 0 && xarray2[k] != trophyx && yarray2[k] != trophyy){
            break;
        }
    }
    char ran[1];

    sprintf(ran, "%d", r);    
    attron(A_BOLD);
    move(trophyx,trophyy);
    addstr(ran);
    refresh();
    // attroff(A_BOLD);
    }
}

void controls() {
    curs_set(0);
    keypad(stdscr, TRUE);

    if(begincheck == false){
        nodelay(stdscr, true);

        // sleep(1);

        usleep(speed);
    }
    ch = getch();
    char buf[100];

    // Controls, use Arrow/WASD
    if(ch != keycheck) {
        switch(ch) {
            case KEY_UP:
                step = -1;
                if(direction == 2){
                    gameover = true;
                }
                direction = 1;
                keycheck = ch;
                count1++;
                
                //addstr("UP Key pressed.                                   ");
                xcheck = true;
                ycheck = false;
                break;
            case 'w':
            case 'W':
                step2 = -1;
                if(direction2 == 2) {
                    gameover = true;
                    p2check = true;
                }
                direction2 = 1;
                keycheck = ch;
                count1++;
                
                //addstr("UP Key pressed.                                   ");
                xcheck2 = true;
                ycheck2 = false;
                break;
            case 'a':
            case 'A':
                step2 = -1;
                if(direction2 == 4) {
                    gameover = true;
                    p2check = true;
                }
                direction2 = 3;
                keycheck = ch;
                count1++;
                
                //addstr("UP Key pressed.                                   ");
                xcheck2 = false;
                ycheck2 = true;
                break;
            case 's':
            case 'S':
                step2 = 1;
                if(direction2 == 1) {
                    gameover = true;
                    p2check = true;
                }
                direction2 = 2;
                keycheck = ch;
                count1++;
                
                //addstr("UP Key pressed.                                   ");
                xcheck2 = true;
                ycheck2 = false;
                break;
            case 'd':
            case 'D':
                step2 = 1;
                if(direction2 == 3) {
                    gameover = true;
                    p2check = true;
                }
                direction2 = 4;
                keycheck = ch;
                count1++;
                
                //addstr("UP Key pressed.                                   ");
                xcheck2 = false;
                ycheck2 = true;
                break;
            case KEY_DOWN:
                step = 1;
                if(direction == 1) {
                    gameover = true;
                }
                direction = 2;
                keycheck = ch;
                
                // addstr("DOWN Key pressed.                                 ");
                xcheck = true;
                ycheck = false;
                break;
            case KEY_LEFT:
                step = -1;
                if(direction == 4) {
                    gameover = true;
                }
                direction = 3;
                keycheck = ch;
                
                // addstr("LEFT Key pressed.                                 ");
                xcheck = false;
                ycheck = true;
                break;
            case KEY_RIGHT:
                step = 1;
                if(direction == 3) {
                    gameover = true;
                }
                direction = 4;
                keycheck = ch;
                
                // addstr("RIGHT Key pressed.                                ");
                xcheck = false;
                ycheck = true;
                break;
            case 'x':
            case 'X':
                // addstr("Goodbye!                                          ");
                gameover = true;
                return;
            default:
                // sprintf(buf, "You typed a \"%c\" key. ASCII code %d...", (char)key, key);
                // addstr(buf);        
                break;
        }
    }
    else{
        if(begincheck == false) {
            nodelay(stdscr, false);
            count1++;
        }
        return;
    }

    if(begincheck == false) {
        nodelay(stdscr, false);
        count1++;
    }
    if(gameover == true) {
        if(p2check == true) {
            char len[1];
            sprintf(len, "%d", length+1);    
            clear();   
            
            mvprintw(15, 42, "Player 1");
            mvprintw(16, 42, len);
            sprintf(len, "%d", length2+1); 
            mvprintw(17, 42, "Player 2");
            mvprintw(18, 42, len);

            mvprintw(11, 42, "Game Over, Player 2 went backwards!");
            mvprintw(12, 42, "Hit any key to close game.");
            mvprintw(14, 42, "Your final lengths are: ");  
            refresh();
        }
        else {
            char len[1];
            sprintf(len, "%d", length+1);    
            clear();   
            
            mvprintw(15, 42, "Player 1");
            mvprintw(16, 42, len);
            sprintf(len, "%d", length2+1); 
            mvprintw(17, 42, "Player 2");
            mvprintw(18, 42, len);

            mvprintw(11, 42, "Game Over, Player 1 went backwards!");
            mvprintw(12, 42, "Hit any key to close game.");
            mvprintw(14, 42, "Your final lengths are: ");  
            refresh();
        }
    }  
}

void guide(){
    for(k = 5; k > 1; k--) {
        xarray[k] = xarray[1-k];
        yarray[k] = yarray[1-k];
    }

    for(k = 2; k <= 5; k++) {
        move(xarray[y], yarray[y]);
        addstr(body);
        refresh();
    }
}

void movesnake() {
    for(k = 0; k <= length; k++) {
        move(xarray[k], yarray[k]);
        if(xarray[k] != 0 && yarray[k] != 0){
        addstr(" ");
        }
        refresh();
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
        

    if(xcheck) {
        if(length > 1) {
            for(k = length; k > 1; k--) {
                int a = k-1;
                xarray[k] = xarray[a];
                yarray[k] = yarray[a];

                if(((xarray[k] != 0) && (xarray[k] != LINES-1)) && ((yarray[k] != 0) && (yarray[k] != COLS-1))) {
                    move(xarray[k], yarray[k]);
                    addstr(body);
                    refresh();
                }
            }
        }
            
        //Change head
        x = xarray[0];
        xarray[0] += step;
        move(xarray[0], yarray[0]);
        addstr(body);
        refresh();

        //Change second body part below head
        if(length > 0) {
            xarray[1] = x;
            yarray[1] = yarray[0];

            move(xarray[1], yarray[1]);
            addstr(body);
            refresh();
        }
               
                 
    }
    else if (ycheck) {
        if(length > 1){
            for(k = length; k > 1; k--) {
                int a = k-1;
                xarray[k] = xarray[a];
                yarray[k] = yarray[a];

                if(((xarray[k] != 0) && (xarray[k] != LINES-1)) && ((yarray[k] != 0) && (yarray[k] != COLS-1))) {
                    move(xarray[k], yarray[k]);
                    addstr(body);
                    refresh();
                }

                

            }
        }
            
        //Change head
        y = yarray[0];
        yarray[0] += step;
        move(xarray[0], yarray[0]);
        addstr(body);
        refresh();
           
        //Change second body part below head
        if(length > 0) {
            xarray[1] = xarray[0];
            yarray[1] = y;

            move(xarray[1], yarray[1]);
            addstr(body);
            refresh();
        }
    }
    // attroff(A_BOLD);
}

void movesnake2() {
    for(k = 0; k <= length2; k++) {        
        move(xarray2[k], yarray2[k]);
        if(xarray2[k] != 0 && yarray2[k] != 0){
        addstr(" ");
        }
        refresh();
    }
    // start_color();
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    if(xcheck2) {
        if(length2 > 1) {
            for(k = length2; k > 1; k--) {
                int a = k-1;
                xarray2[k] = xarray2[a];
                yarray2[k] = yarray2[a];

                if(((xarray2[k] != 0) && (xarray2[k] != LINES-1)) && ((yarray2[k] != 0) && (yarray2[k] != COLS-1))) {
                    move(xarray2[k], yarray2[k]);
                    addstr(body);
                    refresh();
                }
            }
        }
            
        //Change head
        oldx = xarray2[0];    
        xarray2[0] += step2;
        move(xarray2[0], yarray2[0]);
        addstr(body);
        refresh();

        //Change second body part below head
        if(length2 > 0) {
            xarray2[1] = oldx;
            yarray2[1] = yarray2[0];

            move(xarray2[1], yarray2[1]);
            addstr(body);
            refresh();
        }   
    }
    else if (ycheck2) {
        if(length2 > 1) {
            for(k = length2; k > 1; k--) {
                int a = k-1;
                xarray2[k] = xarray2[a];
                yarray2[k] = yarray2[a];

                if(((xarray2[k] != 0) && (xarray2[k] != LINES-1)) && ((yarray2[k] != 0) && (yarray2[k] != COLS-1))) {
                    move(xarray2[k], yarray2[k]);
                    addstr(body);
                    refresh();
                }
            }
        }

        //Change head
        oldy = yarray2[0];
        yarray2[0] += step2;
        move(xarray2[0], yarray2[0]);
        addstr(body);
        refresh();
        
        //Change second body part below head
        if(length > 0) {
            xarray2[1] = xarray2[0];
            yarray2[1] = oldy;

            move(xarray2[1], yarray2[1]);
            addstr(body);
            refresh();
        }
    }
    // attroff(COLOR_PAIR(2));    
}

void trophyexpire() {
    if(randomtime == 1) {
        if(timer == 10) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 2) {
        if(timer == 20) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 3) {
        if(timer == 30) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 4) {
        if(timer == 40) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 5) {
        if(timer == 50) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 6) {
        if(timer == 60) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 7) {
        if(timer == 70) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 8) {
        if(timer == 80) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 9) {
        if(timer == 90) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
}

void bordercollide() {
    if(!gameover) {
        if(xarray[0] == LINES-1 || xarray[0] == 0 || yarray[0] == COLS-1 || yarray[0] == 0) {
            gameover = true;
            char len[1];
            sprintf(len, "%d", length+1);
            clear();

            mvprintw(15, 42, "Player 1");
            mvprintw(16, 42, len);
            sprintf(len, "%d", length2+1);
            mvprintw(17, 42, "Player 2");
            mvprintw(18, 42, len);

            mvprintw(11, 42, "Game Over, you collided with the border!");
            mvprintw(12, 42, "Hit any key to close game.");
            mvprintw(14, 42, "Your final lengths are: ");
            refresh();
        }
        else if(xarray2[0] == LINES-1 || xarray2[0] == 0 || yarray2[0] == COLS-1 || yarray2[0] == 0) {
            gameover = true;
            char len[1];
            sprintf(len, "%d", length+1);
            clear();
            
            mvprintw(15, 42, "Player 1");
            mvprintw(16, 42, len);
            sprintf(len, "%d", length2+1);
            mvprintw(17, 42, "Player 2");
            mvprintw(18, 42, len);

            mvprintw(11, 42, "Game Over, you collided with the border!");
            mvprintw(12, 42, "Hit any key to close game.");
            mvprintw(14, 42, "Your final lengths are: ");
            refresh();
        }
    }
}

void collidegameover() {
    gameover = true;
    char len[1];
    sprintf(len, "%d", length+1); 
    clear();
    
    mvprintw(15, 42, "Player 1");
    mvprintw(16, 42, len);
    sprintf(len, "%d", length2+1);
    mvprintw(17, 42, "Player 2");
    mvprintw(18, 42, len);

    mvprintw(11, 42, "Game Over, you collided with each other!");
    mvprintw(12, 42, "Hit any key to close game.");
    mvprintw(14, 42, "Your final lengths are: ");
    refresh();
}

void playercollide() {
    if(!gameover) {
        for(k = 0; k <= length; k++) {
            if((xarray2[0] == xarray[k] && yarray2[0] == yarray[k])) {
                collidegameover();
                break;
            }
        }
        for(k = 0; k <= length2; k++) {
            if((xarray[0] == xarray2[k] && yarray[0] == yarray2[k])) {
                collidegameover();
                break;
            }
        }
    }
}

// Main Driver
int main() {
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    attron(A_BOLD);
    borders(); // Draw the borders
    noecho();  
    
    xarray[0] = LINES/2, yarray[0] = COLS/2;
    xarray2[0] = LINES/2+5, yarray2[0] = COLS/2+5;
    
    keypad(stdscr, TRUE);
    int halfperimeter = (LINES+COLS)/2;

    curs_set(0);
    nodelay(stdscr, true);
    char buf[100];
    //ycheck = true;

    srand(time(NULL));

    //Start snake in random direction
    r = rand() % 4 + 1;
    if(r == 1) {
        step = -1;
        direction = 3;
        direction2 = 3;
        ycheck = true;
        ycheck2 = true;
    }
    else if(r == 2) {
        step = -1;
        direction = 1;
        direction2 = 1;
        xcheck = true;
        xcheck2 = true;
    }
    else if(r == 3) {
        step = 1;
        direction = 4;
        direction2 = 4;
        ycheck = true;
        ycheck2 = true;
    }
    else if(r == 4) {
        step = 1;
        direction = 2;
        direction2 = 2;
        xcheck = true;
        xcheck2 = true;
    }

    while(direction == 0 || direction2 == 0) { 
        
        
        movesnake();
        movesnake2();
        attron(COLOR_PAIR(1));

        if(!gameover){
        usleep(speed);

        controls();
        placetrophy();
        timer++;
        
        /*
        if(timer == 100) {
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
        */
        trophyexpire();

        

        bordercollide();
        playercollide();
        }
        

        if(gameover) {
            nodelay(stdscr, false);
            break;
        }
    }

    if(!gameover) {
        begincheck = false;
        nodelay(stdscr, false);
    }


    while(!gameover) {
        //sleep(1);

        movesnake();
        keypad(stdscr, FALSE);
        movesnake2();
        keypad(stdscr, FALSE);
        
        attron(COLOR_PAIR(1));
        
        // begincheck = false;
        controls();

        
       
        placetrophy();
        timer++;
        
        /*
        if(timer == 100){
            move(trophyx,trophyy);
            addstr(" ");
            refresh();
            timer = 0;
        }
        */

        trophyexpire();

        if(xarray[0] == trophyx && yarray[0] == trophyy) {
            if(r == 1) {
                length++;
            }
            else if(r == 2) {
                length += 2;
            }
            else if(r == 3) {
                length += 3;
            }
            else if(r == 4) {
                length += 4;
            }
            else if(r == 5) {
                length += 5;
            }
            else if(r == 6) {
                length += 6;
            }
            else if(r == 7) {
                length += 7;
            }
            else if(r == 8) {
                length += 8;
            }
            else if(r == 9) {
                length += 9;
            }
            timer = 0;
        }
        else if(xarray2[0] == trophyx && yarray2[0] == trophyy) {
            if(r == 1) {
                length2++;
            }
            else if(r == 2) {
                length2 += 2;
            }
            else if(r == 3) {
                length2 += 3;
            }
            else if(r == 4) {
                length2 += 4;
            }
            else if(r == 5) {
                length2 += 5;
            }
            else if(r == 6) {
                length2 += 6;
            }
            else if(r == 7) {
                length2 += 7;
            }
            else if(r == 8) {
                length2 += 8;
            }
            else if(r == 9) {
                length2 += 9;
            }
            timer = 0;
        }

        if(length > 40 || length2 > 40) {
            speed = 50000;
            
        }
        if(length > 90 || length2 > 90) {
            speed = 30000;
            
        }

        bordercollide();

        if(gameover) {
            break;
        }
       
        //Add winning screen here
        if(((length >= 150) || (length2 >= 150))&& !gameover) {
            gameover = true;

            if(length >= 150) {
                char len[1];
                sprintf(len, "%d", length+1);
                clear();
                
                mvprintw(15, 42, "Player 1");
                mvprintw(16, 42, len);
                sprintf(len, "%d", length2+1);
                mvprintw(17, 42, "Player 2");
                mvprintw(18, 42, len);

                mvprintw(11, 42, "Player 1 won!!!");
                mvprintw(12, 42, "Hit any key to close game.");
                mvprintw(14, 42, "Your final lengths are: ");
                refresh();
            }
            else if(length2 >= 150) {
                char len[1];
                sprintf(len, "%d", length+1);
                clear();
                
                mvprintw(15, 42, "Player 1");
                mvprintw(16, 42, len);
                sprintf(len, "%d", length2+1);
                mvprintw(17, 42, "Player 2");
                mvprintw(18, 42, len);

                mvprintw(11, 42, "Player 2 won!!!");
                mvprintw(12, 42, "Hit any key to close game.");
                mvprintw(14, 42, "Your final length are: ");
                refresh();
            }
        }

        if(!gameover) {
            for(k = 1; k <= length; k++) {
                if((xarray[0] == xarray[k] && yarray[0] == yarray[k])) {
                    gameover = true;
                    char len[1];
                    sprintf(len, "%d", length+1);
                    clear();
                    
                    mvprintw(15, 42, "Player 1");
                    mvprintw(16, 42, len);
                    sprintf(len, "%d", length2+1);
                    mvprintw(17, 42, "Player 2");
                    mvprintw(18, 42, len);

                    mvprintw(11, 42, "Game Over, Player 1 collided with themself!");
                    mvprintw(12, 42, "Hit any key to close game.");
                    mvprintw(14, 42, "Your final lengths are: ");
                    refresh();
                    break;      
                }
            }

            for(k = 1; k <= length2; k++) {
                if((xarray2[0] == xarray2[k] && yarray2[0] == yarray2[k])) {    
                    gameover = true;
                    char len[1];
                    sprintf(len, "%d", length+1); 
                    clear();
                    
                    mvprintw(15, 42, "Player 1");
                    mvprintw(16, 42, len);
                    sprintf(len, "%d", length2+1);
                    mvprintw(17, 42, "Player 2");
                    mvprintw(18, 42, len);

                    mvprintw(11, 42, "Game Over, Player 2 collided with themself!");
                    mvprintw(12, 42, "Hit any key to close game.");
                    mvprintw(14, 42, "Your final lengths are: ");
                    refresh();
                    break;
                }
            }
        }
        playercollide();       
    }
    getch();

    endwin(); // End Game
    return 0;
}