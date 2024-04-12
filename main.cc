#include <ncurses.h>
#include "map.h"

struct Player {
    int y;
    int x;
    WINDOW* win;
    Player(WINDOW* w, int newY, int newX) : win(w), y(newY), x(newX) {};
    void mvup() { if (y < 99) y++; }
    void mvdown() { if (y > 0) y--; }
    void mvright() { if (x > 0) x--; }
    void mvleft() { if (x < 99) x++; }
    void scrollMap() {
        int xOffSet = 42, yOffSet = 11;
        wclear(win);
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < 98; j++) {
                mvwaddch(win, (y - yOffSet) + i, (x - xOffSet) + j, s[i].at(j));
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