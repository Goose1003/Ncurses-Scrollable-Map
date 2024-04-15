#include <ncurses.h>
#include "map.h"
using namespace std;

struct Player {
    int y;
    int x;
    Player(int newY, int newX) : y(newY), x(newX) {};
    void mvup() { y--; }
    void mvdown() { y++; }
    void mvright() { x++; }
    void mvleft() { x--; }
    void scrollMap(vector<string> mapname) {
        int yOffSet = 12 - y, xOffSet = 43 - x;
        clear();
        for (int i = 0; i < mapname.size(); i++) {
            mvprintw(yOffSet + i, xOffSet, "%s", mapname[i].c_str());
        }
        mvprintw(0, 0, "yOffset: %d", yOffSet);
        mvprintw(1, 0, "xOffset: %d", xOffSet);
    }
    void display() {
        displaypos();
        scrollMap(map1);
        //box(win, (int)'|', (int)'-');
        mvaddch(12, 43, '@');
        move(12, 43);
        refresh();
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
    Player* p = new Player(0, 0);
    refresh();
    do {
        p->display();
    } while(getmv(p) != 'z');

    endwin();
}