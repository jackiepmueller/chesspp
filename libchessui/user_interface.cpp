#include "user_interface.hpp"

#include <functional>

using namespace Chess::UI;

UserInterface::UserInterface(Game & game)
    : game_(game)
{
    for (auto & piece : game.pieces()) {
        piece->onSetPos() = std::bind(&UserInterface::redraw, this);
    }
}

void UserInterface::run()
{
    initscr();                  /* Start curses mode                */
    printw("Hello World !!!");  /* Print Hello World                */
    refresh();                  /* Print it on to the real screen   */
    getch();                    /* Wait for user input              */
    endwin();                   /* End curses mode                  */
}

void UserInterface::redraw()
{
    for (auto const * piece : game_.pieces()) {
        (void)piece;
        // TODO: draw the piece
    }
}
