#include <ncurses.h>

struct Player {
    int y;
    int x;
    WINDOW* win;
    Player(WINDOW* w) : win(w), x(0), y(0) {}
    void display() {
        wclear(win);
        box(win, (int)'|', (int)'-');
        mvwprintw(win, 1, 1, "y: %d", y);
        mvwprintw(win, 2, 1, "x: %d", x);
        wrefresh(win);
    }
};

int getmv(Player* p){
    int choice;
    choice = getch();
    switch (choice) {
        case (int)'w':
            p->y--;
            break;
        case (int)'s':
            p->y++;
            break;
        case (int)'a':
            p->x--;
            break;
        case (int)'d':
            p->x++;
            break;
        default:
            break;
    }
    return choice;
}

int main (){
    initscr();
    noecho();
    WINDOW* mainwin = newwin(25, 80, 0, 0);
    Player* p = new Player(mainwin);
    refresh();
    do {
        p->display();
    } while(getmv(p) != 'z');

    endwin();
}