#ifndef CHESS_BISHOP_HPP
#define CHESS_BISHOP_HPP

#include "piece.hpp"

namespace Chess {

template <typename Derived>
struct Bishop
{
    inline Bishop();

    inline BoardField validMoves();

    inline bool move(BoardField pos);
    inline bool move(Rank rank, File file);
};

struct WhiteBishop
    : Piece<White>
    , Bishop<WhiteBishop>
{
    inline WhiteBishop(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

struct BlackBishop
    : Piece<Black>
    , Bishop<BlackBishop>
{
    inline BlackBishop(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

#include "bishop_inline.hpp"

} // namespace Chess

#endif
