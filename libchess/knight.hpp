#ifndef CHESS_KNIGHT_HPP
#define CHESS_KNIGHT_HPP

#include "piece.hpp"

namespace Chess {

template <typename Derived>
struct Knight
{
    inline Knight();

    inline BoardField validMoves();

    inline bool move(BoardField pos);
    inline bool move(Rank rank, File file);
};

struct WhiteKnight
    : Piece<White>
    , Knight<WhiteKnight>
{
    inline WhiteKnight(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

struct BlackKnight
    : Piece<Black>
    , Knight<BlackKnight>
{
    inline BlackKnight(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

#include "knight_inline.hpp"

} // namespace Chess

#endif
