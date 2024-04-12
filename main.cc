#include <ncurses.h>
#include "map.h"

struct Player {
    int y;
    int x;
    WINDOW* win;
    Player(WINDOW* w, int newY, int newX) : win(w), y(newY), x(newX) {};
    void mvup() { y--; }
    void mvdown() { y++; }
    void mvright() { x++; }
    void mvleft() { x--; }
    void scrollMap() {
        int xOffSet = 43, yOffSet = 12;
        wclear(win);
        for (int i = 0; i < map1.size(); i++) {
            for (int j = 0; j < map1[i].size(); j++) {
                mvwaddch(win, (-1 * y + yOffSet) + i, (-1 * x + xOffSet) + j, map1[i][j]);
            }
        }
    }
    void display() {
        displaypos();
        scrollMap();
        box(win, (int)'|', (int)'-');
        mvwaddch(win, 12, 43, '@');
        wmove(win, 12, 43);
        wrefresh(win);
    }
    void displaypos() {
        WINDOW* debug = newwin(4, 12, 0, 88);
        box(debug, (int)'|', (int)'-');
        mvwprintw(debug, 1, 1, "y: %d", y);
        mvwprintw(debug, 2, 1, "x: %d", x);
        wrefresh(debug);
    }
};

int getmv(Player* p){
    int choice;
    choice = getch();
    switch (choice) {
        case (int)'w':
            p->mvup();
            break;
        case (int)'a':
            p->mvleft();
            break;
        case (int)'s':
            p->mvdown();
            break;
        case (int)'d':
            p->mvright();
            break;
        default:
            break;
    }
    return choice;
}

int main (){
    initscr();
    noecho();
    WINDOW* mainwin = newwin(25, 87, 0, 0);
    Player* p = new Player(mainwin, 0, 0);
    refresh();
    do {
        p->display();
    } while(getmv(p) != 'z');

    endwin();
}