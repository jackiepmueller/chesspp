#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"
#include "game_state.hpp"

#include <vector>

namespace Chess {

struct GameContext {
    GameState gameState;

    WhitePawn wP1;
    WhitePawn wP2;
    WhitePawn wP3;
    WhitePawn wP4;
    WhitePawn wP5;
    WhitePawn wP6;
    WhitePawn wP7;
    WhitePawn wP8;

    WhiteRook wR1;
    WhiteRook wR2;

    WhiteKnight wN1;
    WhiteKnight wN2;

    WhiteBishop wB1;
    WhiteBishop wB2;

    WhiteQueen wQ;
    WhiteKing  wK;

    BlackPawn bP1;
    BlackPawn bP2;
    BlackPawn bP3;
    BlackPawn bP4;
    BlackPawn bP5;
    BlackPawn bP6;
    BlackPawn bP7;
    BlackPawn bP8;

    BlackRook bR1;
    BlackRook bR2;

    BlackKnight bN1;
    BlackKnight bN2;

    BlackBishop bB1;
    BlackBishop bB2;

    BlackQueen bQ;
    BlackKing  bK;

    inline GameContext();

    inline PieceVector pawns(Side side);
    inline PieceVector pawns();

    inline PieceVector rooks(Side side);
    inline PieceVector rooks();

    inline PieceVector knights(Side side);
    inline PieceVector knights();

    inline PieceVector bishops(Side side);
    inline PieceVector bishops();

    inline PieceVector queen(Side side);
    inline PieceVector queen();

    inline PieceVector king(Side side);
    inline PieceVector king();
};

#include "game_context_inline.hpp"

} // namespace Chess

#endif
