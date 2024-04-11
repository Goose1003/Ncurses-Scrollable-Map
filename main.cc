#include <ncurses.h>

char tiles[100][100];

struct Player {
    int y;
    int x;
    WINDOW* win;
    Player(WINDOW* w) : win(w), x(50), y(50) {}
    void display() {
        wclear(win);
        box(win, (int)'|', (int)'-');
        mvwprintw(win, 1, 1, "y: %d", y);
        mvwprintw(win, 2, 1, "x: %d", x);
        wrefresh(win);
    }
    void mvup() { if (y > 0) y--; }
    void mvdown() { if (y < 100) y++; }
    void mvright() { if (x < 100) x++; }
    void mvleft() { if (x > 0) x--; }
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
    tiles[50][50] = '0';
    WINDOW* mainwin = newwin(25, 80, 0, 0);
    Player* p = new Player(mainwin);
    refresh();
    do {
        p->display();
    } while(getmv(p) != 'z');

    endwin();
}