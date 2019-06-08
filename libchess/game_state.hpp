#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "bit_manipulation.hpp"
#include "piece_map.hpp"

#include <unordered_map>
#include <vector>

namespace Chess {

enum class Side {
    White,
    Black
};

inline Side otherSide(Side side) {
    return side == Side::White ? Side::Black : Side::White;
}

struct PieceBase;

using PieceVector = std::vector<PieceBase *>;
using PieceVectorConst = std::vector<PieceBase const *>;

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

    Side turn() const {
        return turn_;
    }

    enum Reason {
        Success,
        InvalidMove,
        WrongSide,
        NoPiece
    };

    Reason move(BoardField from, BoardField to);

private:
    PieceMap pieceMap_;
    PieceVector pieces_;
    BoardField board_ = 0;
    Side turn_ = Side::White;
};

} // namespace Chess

#endif
