#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "piece.hpp"
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

    BlackPawn bP1;
    BlackPawn bP2;
    BlackPawn bP3;
    BlackPawn bP4;
    BlackPawn bP5;
    BlackPawn bP6;
    BlackPawn bP7;
    BlackPawn bP8;

    GameContext() 
        : wP1(rankAndFileToBoardField(Two, A), gameState)
        , wP2(rankAndFileToBoardField(Two, B), gameState)
        , wP3(rankAndFileToBoardField(Two, C), gameState)
        , wP4(rankAndFileToBoardField(Two, D), gameState)
        , wP5(rankAndFileToBoardField(Two, E), gameState)
        , wP6(rankAndFileToBoardField(Two, F), gameState)
        , wP7(rankAndFileToBoardField(Two, G), gameState)
        , wP8(rankAndFileToBoardField(Two, H), gameState)

        , bP1(rankAndFileToBoardField(Seven, H), gameState)
        , bP2(rankAndFileToBoardField(Seven, G), gameState)
        , bP3(rankAndFileToBoardField(Seven, F), gameState)
        , bP4(rankAndFileToBoardField(Seven, E), gameState)
        , bP5(rankAndFileToBoardField(Seven, D), gameState)
        , bP6(rankAndFileToBoardField(Seven, C), gameState)
        , bP7(rankAndFileToBoardField(Seven, B), gameState)
        , bP8(rankAndFileToBoardField(Seven, A), gameState)
    { }

};

} // namespace Chess

#endif
