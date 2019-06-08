#ifndef CHESS_KING_HPP
#define CHESS_KING_HPP

#include "piece.hpp"

namespace Chess {

template <typename Derived>
struct King
{
    inline King();

    inline BoardField validMoves();

    inline bool move(BoardField pos);
    inline bool move(Rank rank, File file);
};

struct WhiteKing
    : Piece<White>
    , King<WhiteKing>
{
    inline WhiteKing(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

struct BlackKing
    : Piece<Black>
    , King<BlackKing>
{
    inline BlackKing(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

#include "king_inline.hpp"

} // namespace Chess

#endif
