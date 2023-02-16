#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <time.h>

// Instantiate variables
int i, k, x, y, r, length = 2, ch = 4, check = 10, keycheck = 10; // Create borders and movement variables
int oldx, oldy; // Unused placeholder variables
int trophy_x, trophy_y; // Fruit variables
int timer; // Timer for fruit
int step = +1; // Increment movement
int speed = 100000; // Change speed of snake
int counter = 0; //  Movement counter
int randomtime = 0; // Random spawn time for fruit
int direction = 0; // Direction variable for snake

char body[] = "0"; // Body of the snake
int xarray[300] = { 0 }, yarray[300] = { 0 }; // For adding and creating snake segments
bool xcheck, ycheck, begincheck = true, gameover = false; // Check for change in movement and win/lose events

// Snake structure
struct snake{
    int x, y;
    struct snake *next;
};

// Create Borders
void borders() {
    initscr(); // Start Screen
    clear(); // Clear screen and start drawing

    // Change character colors
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    
    attron(A_BOLD);

    // Columns
    for(i = 0; i < LINES; i++) {
        // Left Column
        move(i, 0);
        addstr("|");

        /// Right Column
        move(i, COLS-1);
        addstr("|");
    }

    // Rows
    for (i = 0; i < COLS; i++) {
        // Top Row
        move(0, i);
        addstr("-");

        // Bottom Row
        move(LINES-1, i);
        addstr("-");
    }
    refresh();
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

// Spawn and change fruit position
void placetrophy() {
    if(timer == 0) {
        // Change fruit spawn randomly at random ticks
        r = rand() % 9 + 1;
        randomtime = rand() % 9 + 1;

        trophy_x = rand()%(LINES - 1);
        trophy_y = rand()%(COLS - 1);

    for(k = 1; k < length; k++){    
        while(trophy_y == 0 || trophy_y == COLS-1 || trophy_x == 0 || trophy_x == LINES-1 || trophy_x > LINES-1 || trophy_x < 0 || trophy_y > COLS-1 || trophy_y < 0 || xarray[k] == trophy_x || yarray[k] == trophy_y){
            trophy_x = rand()%(LINES - 1);
            trophy_y = rand()%(COLS - 1);
        }
        if(trophy_y == 0 && trophy_y == COLS-1 && trophy_x == 0 && trophy_x == LINES-1 && trophy_x > LINES-1 && trophy_x < 0 && trophy_y > COLS-1 && trophy_y < 0 && xarray[k] != trophy_x && yarray[k] != trophy_y){
            break;
        }
    }
        char ran[1];

        sprintf(ran, "%d", r);
        attron(A_BOLD);
        move(trophy_x,trophy_y);
        addstr(ran);
        refresh();
        // attroff(A_BOLD);
    }           
}

// Game controls
void controls() {
    curs_set(0); // Hide cursor
    keypad(stdscr, TRUE); // Activate keypad controls

    // Delay start speed
    if(begincheck == false) {
        nodelay(stdscr, true);

        // sleep(1);
    
        usleep(speed);
    }

    // Instantiate user input as variable
    ch = getch();
    char buf[100];

    // Controls, use Arrow/WASD
    // Check if key is pressed and change snake movement for specific keypress
    if(!gameover){
    if(ch != keycheck) {
        switch(ch) {
            // Go Up
            case KEY_UP:
            case 'w':
            case 'W':
                step = -1;
                // addstr("UP Key pressed.                                   ");
                if(direction == 2) {
                    gameover = true;
                }
                direction = 1;
                keycheck = ch;
                counter++;

                xcheck = true;
                ycheck = false;
                break;
            // Go Down
            case KEY_DOWN:
            case 's':
            case 'S':
                step = 1;
                // addstr("DOWN Key pressed.                                 ");
                if(direction == 1) {
                    gameover = true;
                }
                direction = 2;
                keycheck = ch;

                xcheck = true;
                ycheck = false;
                break;
            // Go Left
            case KEY_LEFT:
            case 'a':
            case 'A':
                step = -1;
                // addstr("LEFT Key pressed.                                 ");
                if(direction == 4) {
                    gameover = true;
                }
                
                direction = 3;
                keycheck = ch;

                xcheck = false;
                ycheck = true;
                break;
            // Go Right
            case KEY_RIGHT:
            case 'd':
            case 'D':
                step = 1;
                // addstr("RIGHT Key pressed.                                ");
                if(direction == 3) {
                    gameover = true;
                }
                direction = 4;
                keycheck = ch;

                xcheck = false;
                ycheck = true;
                break;
            // Quit Game
            case 'x':
            case 'X':
                // addstr("Goodbye!                                          ");
                gameover = true;
                return;
            default:
                // sprintf(buf, "You typed a \"%c\" key. ASCII code %d...", (char)key, key);
                // addstr(buf);          
                // return;
                break;
        }
    }
    else {
        if(begincheck == false) {
            nodelay(stdscr, false);
            counter++;
        }
        return;
    }
    
    if(begincheck == false) {
        nodelay(stdscr, false);
        counter++;
    }
    }
    // Check to see when snake goes backwards for loss
    if(gameover == true) {
        char len[1];

        sprintf(len, "%d", length+1);
        clear();

        mvprintw(12, 42, "Game Over, snakes can't go backwards!");
        mvprintw(13, 42, "Hit any key to close game.");

        move(15,42);
        addstr("Your final length is: ");
        addstr(len);

        refresh();
    }
}

// Snake guidance
void guide() {
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

// Snake movement mechanics
void movesnake() {
    for(k = 0; k <= length; k++) {
        move(xarray[k], yarray[k]);

        if(xarray[k] != 0 && yarray[k] != 0){
        addstr(" ");
        }

        refresh();
    }
    attron(A_BOLD);

    // Check for x-axis movement
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

        // Change second body part below head
        if(length > 0) {
            xarray[1] = x;
            yarray[1] = yarray[0];

            move(xarray[1], yarray[1]);
            addstr(body);
            refresh();
        }
    }
    // Check for y-axis movement
    else if (ycheck) {
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
        y = yarray[0];
        yarray[0] += step;

        move(xarray[0], yarray[0]);
        addstr(body);
        refresh();
           
        // Change second body part below head
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

// Fruit expiration timer
void trophyexpire() {
    // Trophy Spawn Timer (Seconds: 1-9)
    if(randomtime == 1) {
        if(timer == 10) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 2) {
        if(timer == 20) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 3) {
        if(timer == 30) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 4) {
        if(timer == 40) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 5) {
        if(timer == 50) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 6) {
        if(timer == 60) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 7) {
        if(timer == 70) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 8) {
        if(timer == 80) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
    else if(randomtime == 9) {
        if(timer == 90) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
    }
}

// Border collision detecion
void bordercollide() {
    // Check if player hit the border and lose the game
    if(!gameover) {
        if(xarray[0] == LINES-1 || xarray[0] == 0 || yarray[0] == COLS-1 || yarray[0] == 0) {
            gameover = true;
            char len[1];
            length += 1;

            clear();  
            sprintf(len, "%d", length);  

            mvprintw(12, 42, "Game Over, you collided with the border!");
            mvprintw(13, 42, "Hit any key to close game.");

            move(15,42);
            addstr("Your final length is: ");
            addstr(len);

            refresh();
        }
    }
}

// Main Driver
int main() {
    attron(A_BOLD);
    borders(); // Draw the borders
    noecho();

    // x = LINES/2, y = COLS/2;
    xarray[0] = LINES/2, yarray[0] = COLS/2;
    keypad(stdscr, TRUE);
    int halfperimeter = (LINES+COLS)/2;

    curs_set(0); // Hide cursor
    nodelay(stdscr, true); // Add no dealy to screen
    
    char buf[100];
    srand(time(NULL));

    //Start snake in random direction
    r = rand() % 4 + 1;
    if(r == 1) {
        step = -1;
        direction = 3;
        ycheck = true;
    }
    else if(r == 2) {
        step = -1;
        direction = 1;
        xcheck = true;
    }
    else if(r == 3) {
        step = 1;
        direction = 4;
        ycheck = true;
    }
    else if(r == 4) {
        step = 1;
        direction = 2;
        xcheck = true;
    }

    // Loop for when game begins
    while(direction == 0){
        movesnake(); // Start snake movement
        if(!gameover){
        usleep(speed);

        // Start controls and fruit spawn
        controls();
        placetrophy();
        timer++;
        
        /*
        if(timer == 100) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
        */

        trophyexpire(); // Activate trophy timer

        

        bordercollide(); // Check for border collision
        }
        // Check for gameover
        if(gameover) {
            nodelay(stdscr, false);
            break;
        }
    }
        

    // Check to make sure game doesn't end when startup
    if(!gameover) {
        begincheck = false;
        nodelay(stdscr, false);
    }
    
    
    // Loop for game movement
    while(!gameover) {
        //sleep(1);
        
        movesnake();
        
        begincheck = false;
        controls();

        

        placetrophy();
        timer++;
        
        /*
        if(timer == 100) {
            move(trophy_x,trophy_y);
            addstr(" ");
            refresh();
            timer = 0;
        }
        */

        trophyexpire();

        // When player touches trophy, add segements to the  corrosponding number given
        if(xarray[0] == trophy_x && yarray[0] == trophy_y) {
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

        // Increase snake speed as snake gets bigger for increase challenge
        if(length > 40) {
            speed = 50000;
            
        }
        if(length > 90) {
            speed = 30000;
            
        }
        
        bordercollide();

        // Add winning screen here
        if(length >= 100 && !gameover) {
            gameover = true;
            char len[1];

            sprintf(len, "%d", length+1);
            clear();

            mvprintw(12, 42, "You won!!!");
            mvprintw(13, 42, "Hit any key to close game.");

            move(15,42);
            addstr("Your final length is: ");
            addstr(len);

            refresh();
        }

        // End game when player hits themself
        if(!gameover) {
            if(length > 0) {
                for(k = 1; k <= length; k++) {
                    if(xarray[0] == xarray[k] && yarray[0] == yarray[k]) {
                        gameover = true;
                        char len[1];
                        sprintf(len, "%d", length+1);

                        
                        clear();
                        
                        mvprintw(12, 42, "Game Over, you collided with yourself!");
                        mvprintw(13, 42, "Hit any key to close game.");

                        move(15,42);
                        addstr("Your final length is: ");
                        addstr(len);
                        
                        

                        refresh();
                    }
                }
            }
        }
    }
    getch(); // Get input

    endwin(); // End Game
    return 0;
}