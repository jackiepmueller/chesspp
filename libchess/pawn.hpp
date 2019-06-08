#ifndef CHESS_PAWN_HPP
#define CHESS_PAWN_HPP

#include "piece.hpp"

namespace Chess {

template <typename Derived>
struct Pawn
    : FirstMoveConcept
{
    inline Pawn();

    inline BoardField validMoves();

    inline bool move(BoardField pos);
    inline bool move(Rank rank, File file);
};

struct WhitePawn
    : Piece<White>
    , Pawn<WhitePawn>
{
    inline WhitePawn(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

struct BlackPawn
    : Piece<Black>
    , Pawn<BlackPawn>
{
    inline BlackPawn(BoardField startingPos, GameState & gameState);

    inline virtual bool move(BoardField bf) override;
    inline virtual bool move(Rank rank, File file) override;
    inline virtual BoardField validMoves() override;
};

#include "pawn_inline.hpp"

} // namespace Chess

#endif
