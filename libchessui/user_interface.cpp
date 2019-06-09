#include "user_interface.hpp"
#include "game_state.hpp"
#include "san_parser.hpp"

#include <boost/algorithm/string.hpp>

#include <functional>

namespace Chess {
namespace UI {

auto help = R"*^*^*(

 Chesspp, a command line chess game     

 Moves can be entered using standard
 algebraic notation:

    d4  (moves pawn at d2 to d4)
    Rd3 (moves rook to d3)

 Ambiguous moves can be disambiguated by
 supplying a rank and/or file:

    Rad3  (moves rook on file A to d3)
    R1d3  (moves rook on rank 1 to d3)
    Ra1d3 (moves rook at A1 to d3)

 Alternatively, a from/to pair can be supplied:

    d2 d4 (moves the piece at d2 to d4)

 * press any key to return.

)*^*^*";

static constexpr Position TITLE(1, 13);
static constexpr Position PROMPT(34, 1);
static constexpr Position ENTRY(34, 3);
static constexpr Position TOPFILES(3, 5);
static constexpr Position BOTFILES(30, 5);
static constexpr Position WHITE_TURN(32, 3);
static constexpr Position BLACK_TURN(32, 8);
static constexpr Position MESSAGE(32, 13);

static constexpr int WHITE_PAIR = 1;
static constexpr int BLACK_PAIR = 2;

static void drawHelp()
{
    mvprintw(0, 0, help);
}

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

static void drawBoard()
{
    attron(COLOR_PAIR(WHITE_PAIR));
    {
        auto drawWhiteGrid = [](Position pos) {
            for (size_t k = 0; k < 4; ++k) {
                for (size_t j = 0; j < 4; ++j) {
                    for (size_t i = 0; i < 3; ++i) {
                        mvprintw(pos.row + i - k * 6, pos.col + j * 6, "   ");
                    }
                }
            }
        };

        drawWhiteGrid(Position(26, 4)); // from A1
        drawWhiteGrid(Position(23, 7)); // from B2
    }
    attroff(COLOR_PAIR(WHITE_PAIR));

    attron(COLOR_PAIR(BLACK_PAIR));
    attroff(COLOR_PAIR(BLACK_PAIR));
}

static void drawTurnIndicators(Side turn)
{
    mvprintw(32, 1, "W( ) B( ) : ");

    auto pos = turn == Side::White ? WHITE_TURN : BLACK_TURN;
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
    try {
        initscr();
        //cbreak();             // Don't intercept ctrl keys
        noecho();             // Don't echo keys
        keypad(stdscr, true); // enable F1, F2, arrow keys etc..
        start_color();

        // black on white for white pieces
        init_pair(WHITE_PAIR, COLOR_BLACK, COLOR_WHITE);

        // white on black for black pieces
        init_pair(BLACK_PAIR, COLOR_WHITE, COLOR_BLACK);

        while (running_) {
            redraw();

            auto c = getch();
            if (showingHelp_) {
                showingHelp_ = false;
                continue;
            }
            if (c == 10) {
                runCommand();
            }
            else if (c == KEY_BACKSPACE) {
                if (!cmd_.empty()) {
                    cmd_.pop_back();
                }
            }
            else {
                cmd_.push_back(static_cast<char>(c));
            }
        }
    }
    catch (...) {
        endwin();
        throw;
    }

    endwin();
}

void UserInterface::redraw()
{
    clear();

    if (showingHelp_) {
        drawHelp();
        return;
    }

    // static content
    drawTitle();
    drawPrompt();
    drawFiles();
    drawRanks();
    drawBoard();
    drawTurnIndicators(gc_.gameState.turn());

    // dynamic content
    drawCommand();
    drawMessage();

    for (auto const * piece : gc_.gameState.pieces()) {
        if (!piece->alive()) continue;

        if (piece->side() == Side::White) {
            attron(COLOR_PAIR(WHITE_PAIR));
        }
        else {
            attron(COLOR_PAIR(BLACK_PAIR));
        }

        auto pos = positionFromBoardField(piece->pos());
        mvprintw(pos.row, pos.col, "%c", piece->identifier());

        if (piece->side() == Side::White) {
            attroff(COLOR_PAIR(WHITE_PAIR));
        }
        else {
            attroff(COLOR_PAIR(BLACK_PAIR));
        }
    }

    move(ENTRY.row, ENTRY.col + cmd_.size());
    refresh();
}

void UserInterface::runCommand()
{
    std::vector<std::string> tokens;
    boost::trim(cmd_);
    boost::split(tokens, cmd_, boost::is_any_of(" "), boost::token_compress_on);

    SANParser::Result result;

    if (tokens.size() == 1) {
        auto cmd = boost::to_upper_copy<std::string>(tokens[0]);
        if (cmd == "Q" || cmd == "QUIT" || cmd == "EXIT") {
            running_ = false;
        }
        else if (cmd == "H" || cmd == "HELP") {
            showingHelp_ = true;
            cmd_.clear();
            return;
        }
        else if (cmd.empty()) {
            cmd_.clear();
            return;
        }
        else {
            result = SANParser::parse(gc_, tokens[0]);
        }
    }
    else if (tokens.size() == 2) {
        auto from = tokens[0];
        auto to   = tokens[1];

        result = SANParser::parse(from, to);
    }

    switch (result.reason) {
    case SANParser::Success:
    {
        auto from = positionToString(result.from);
        auto to   = positionToString(result.to);

        switch (gc_.gameState.move(result.from, result.to)) {
        case GameState::Success:
            msg_ = "Move " + from + " to " + to;
            break;
        case GameState::WrongSide:
            msg_ = "Wrong side";
            break;
        case GameState::InvalidMove:
            msg_ = "Couldn't move to " + to;
            break;
        case GameState::NoPiece:
            msg_ = "No piece at " + from;
            break;
        }
        break;
    }
    case SANParser::Ambiguous:
        msg_ = "Ambiguous move";
        break;
    case SANParser::Invalid:
        msg_ = "Invalid move";
        break;
    case SANParser::Fail:
        msg_ = "Parse failure";
        break;
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
    Position pos (
        27 - rankFromBoardField(bf) * 3,
        5  + fileFromBoardField(bf) * 3
    );

    return pos;
}

} // namespace UI
} // namespace Chess
