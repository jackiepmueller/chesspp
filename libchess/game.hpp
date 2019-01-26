#ifndef GAME_HPP
#define GAME_HPP

#include "bit_manipulation.hpp"

#include <vector>

namespace Chess {

struct PieceBase;

using PieceVector = std::vector<PieceBase *>;

struct Game {
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

private:
    PieceVector pieces_;
    BoardField board_ = 0;
};

} // namespace Chess

#endif
