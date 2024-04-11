#include <ncurses.h>

int main (){
    initscr();
    noecho();
    WINDOW* mainwin = newwin(25, 80, 0, 0);
    box(mainwin, (int)'|', (int)'-');
    refresh();
    wrefresh(mainwin);
    getch();

    endwin();
}