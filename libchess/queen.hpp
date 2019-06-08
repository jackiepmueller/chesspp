#ifndef CHESS_QUEEN_HPP
#define CHESS_QUEEN_HPP

#include "piece.hpp"

namespace Chess {

template <typename Derived>
struct Queen
{
    inline Queen();

    inline BoardField validMoves();

    inline bool move(BoardField pos);
    inline bool move(Rank rank, File file);
};

struct WhiteQueen
    : Piece<White>
    , Queen<WhiteQueen>
{
    inline WhiteQueen(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

struct BlackQueen
    : Piece<Black>
    , Queen<BlackQueen>
{
    inline BlackQueen(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

#include "queen_inline.hpp"

} // namespace Chess

#endif
