#ifndef CHESSPP_HPP
#define CHESSPP_HPP

#include "chess.hpp"
#include "user_interface.hpp"

namespace Chess {
struct ChessPP {
    void run();

private:
    GameContext gc_;
    UI::UserInterface ui_;
};

} // namespace Chess

#endif
