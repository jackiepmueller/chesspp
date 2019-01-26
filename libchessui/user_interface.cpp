#include "user_interface.hpp"

using namespace Chess::UI;

void UserInterface::run()
{
    initscr();                  /* Start curses mode                */
    printw("Hello World !!!");  /* Print Hello World                */
    refresh();                  /* Print it on to the real screen   */
    getch();                    /* Wait for user input              */
    endwin();                   /* End curses mode                  */
}
