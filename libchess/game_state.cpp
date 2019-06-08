#include "game_state.hpp"
#include "piece.hpp"

namespace Chess {

GameState::Reason GameState::move(BoardField from, BoardField to)
{
    auto res = Success;
    auto piece = pieceMap_[from];
    if (piece) {
        if (piece->side() != turn_) {
            res = WrongSide;
        }
        else if (!piece->move(to)) {
            res = InvalidMove;
        }
        else {
            turn_ = otherSide(turn_);
        }
    }
    else {
        res = NoPiece;
    }

    return res;
}

} // namespace Chess
