#include "game_state.hpp"
#include "piece.hpp"

using namespace Chess;

GameState::Result GameState::move(BoardField from, BoardField to)
{
    auto res = Result::Success;
    auto piece = pieceMap_[from];
    if (piece) {
        if (piece->side() != turn_) {
            res = Result::WrongSide;
        }
        else if (!piece->move(to)) {
            res = Result::InvalidMove;
        }
        else {
            turn_ = otherSide(turn_);
        }
    }
    else {
        res = Result::NoPiece;
    }

    return res;
}
