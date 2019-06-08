#ifndef PIECE_MAP_HPP
#define PIECE_MAP_HPP

#include "bit_manipulation.hpp"

#include <array>

namespace Chess {

struct PieceBase;

struct PieceMap {
    using value_type = PieceBase *;

    PieceMap() : pieces_() { }

    value_type & operator[](BoardField bf)
    {
        auto key = boardFieldToOrdinal(bf) - 1;
        return pieces_[key];
    }

    value_type const & operator[](BoardField bf) const
    {
        auto key = boardFieldToOrdinal(bf) - 1;
        return pieces_[key];
    }

private:
    std::array<value_type, 64> pieces_;
};

} // namespace Chess

#endif
