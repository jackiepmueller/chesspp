#ifndef CHESS_ROOK_HPP
#define CHESS_ROOK_HPP

#include "piece.hpp"

namespace Chess {

template <typename Derived>
struct Rook : FirstMoveConcept {
    inline Rook();

    inline BoardField validMoves();

    inline bool move(BoardField pos);
    inline bool move(Rank rank, File file);
};

struct WhiteRook
    : Piece<White>
    , Rook<WhiteRook>
{
    inline WhiteRook(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
};

struct BlackRook
    : Piece<Black>
    , Rook<BlackRook>
{
    inline BlackRook(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
};

#include "rook_inline.hpp"

} // namespace Chess

#endif
