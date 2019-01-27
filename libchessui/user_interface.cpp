#include "user_interface.hpp"

#include <functional>

using namespace Chess::UI;

static constexpr Position TITLE(1, 13);
static constexpr Position PROMPT(34, 1);
static constexpr Position ENTRY(34, 3);
static constexpr Position TOPFILES(3, 5);
static constexpr Position BOTFILES(30, 5);

static void drawTitle()
{
    mvprintw(TITLE.row, TITLE.col, "Chess!");
}

static void drawPrompt()
{
    mvprintw(PROMPT.row, PROMPT.col, "> ");
}

static void drawFiles()
{
    const char * files = "A  B  C  D  E  F  G  H";
    mvprintw(TOPFILES.row, TOPFILES.col, files);
    mvprintw(BOTFILES.row, BOTFILES.col, files);
}

static void drawRanks()
{
    Position left (27, 1);
    Position right(27, 29);

    char c = '1';

    auto draw = [& c](Position & pos) {
        mvprintw(pos.row, pos.col, "%c", c);
        pos.row -= 3;
    };

    for (auto i = 0; i < 8; ++i) {
        draw(left);
        draw(right);
        c++;
    }
}

UserInterface::UserInterface(GameContext & gc)
    : gc_(gc)
{
    for (auto & piece : gc_.gameState.pieces()) {
        piece->onSetPos() = std::bind(&UserInterface::redraw, this);
    }
}

void UserInterface::run()
{
//    redraw();
//    gc_.wP1.move(Three, A);
//    gc_.wP1.move(Four, A);
    initscr();
    //cbreak();             // Don't intercept ctrl keys
    //noecho();             // Don't echo keys
    keypad(stdscr, true); // enable F1, F2, arrow keys etc..

    redraw();

    while (true) {
        auto c = getch();
        if (c == 10) {
            runCommand();
        }
        else {
            cmd_.push_back(static_cast<char>(c));
        }

        redraw();

    }
}

void UserInterface::redraw()
{
    clear();

    drawTitle();
    drawPrompt();
    drawFiles();
    drawRanks();
    drawCommand();

    for (auto const * piece : gc_.gameState.pieces()) {
        (void)piece;
        //std::cout << piece->identifier() << ": " << fileToString(piece->file()) << rankToString(piece->rank()) << std::endl;
        // TODO: draw the piece
    }

    move(ENTRY.row, ENTRY.col + cmd_.size());
    refresh();
}

void UserInterface::runCommand()
{
    cmd_.clear();
}

void UserInterface::drawCommand()
{
    mvprintw(ENTRY.row, ENTRY.col, cmd_.c_str());
}

