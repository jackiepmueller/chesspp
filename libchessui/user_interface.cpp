#include "user_interface.hpp"

#include <functional>

using namespace Chess::UI;

static constexpr Position TITLE(1, 13);
static constexpr Position PROMPT(34, 1);
static constexpr Position ENTRY(34, 3);
static constexpr Position TOPFILES(3, 5);
static constexpr Position BOTFILES(30, 5);
static constexpr Position WHITE_TURN(32, 3);
static constexpr Position BLACK_TURN(32, 8);
static constexpr Position MESSAGE(32, 13);

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

static void drawTurnIndicators(bool turn)
{
    mvprintw(32, 1, "W( ) B( ) : ");

    auto pos = turn ? WHITE_TURN : BLACK_TURN;
    mvprintw(pos.row, pos.col, "*");
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

    // static content
    drawTitle();
    drawPrompt();
    drawFiles();
    drawRanks();
    drawTurnIndicators(gc_.gameState.turn());

    // dynamic content
    drawCommand();
    drawMessage();

    for (auto const * piece : gc_.gameState.pieces()) {
        (void)piece;
        auto pos = positionFromBoardField(piece->pos());
        mvprintw(pos.row, pos.col, "%c", piece->identifier());
    }

    move(ENTRY.row, ENTRY.col + cmd_.size());
    refresh();
}

void UserInterface::runCommand()
{
    if (cmd_ == "test") {
        gc_.wP1.move(Three, A);
        gc_.bP3.move(Five, F);
        msg_ = "the message";
    }
    cmd_.clear();
}

void UserInterface::drawCommand()
{
    mvprintw(ENTRY.row, ENTRY.col, cmd_.c_str());
}

void UserInterface::drawMessage()
{
    mvprintw(MESSAGE.row, MESSAGE.col, msg_.c_str());
}

Position UserInterface::positionFromBoardField(BoardField bf)
{
    Position pos {
        27 - rankFromBoardField(bf) * 3,
        5  + fileFromBoardField(bf) * 3
    };

    return pos;
}
