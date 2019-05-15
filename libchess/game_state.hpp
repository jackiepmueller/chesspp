#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "bit_manipulation.hpp"

#include <unordered_map>
#include <vector>

namespace Chess {

struct PieceBase;

using PieceMap = std::unordered_map<BoardField, PieceBase *>;
using PieceVector = std::vector<PieceBase *>;

struct GameState {
    BoardField board() const {
        return board_;
    }

    BoardField & board() {
        return board_;
    }

    PieceVector const & pieces() const {
        return pieces_;
    }

    PieceVector & pieces() {
        return pieces_;
    }

    PieceMap const & pieceMap() const {
        return pieceMap_;
    }

    PieceMap & pieceMap() {
        return pieceMap_;
    }

    // true = white, false = black
    bool turn() const {
        return turn_;
    }

private:
    PieceMap pieceMap_;
    PieceVector pieces_;
    BoardField board_ = 0;
    bool turn_ = true;
};

} // namespace Chess

#endif
