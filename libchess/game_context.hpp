#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "piece.hpp"
#include "game.hpp"

#include <vector>

namespace Chess {

struct GameContext {
    Game game;

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
        : wP1(rankAndFileToBoardField(Two, A), game)
        , wP2(rankAndFileToBoardField(Two, B), game)
        , wP3(rankAndFileToBoardField(Two, C), game)
        , wP4(rankAndFileToBoardField(Two, D), game)
        , wP5(rankAndFileToBoardField(Two, E), game)
        , wP6(rankAndFileToBoardField(Two, F), game)
        , wP7(rankAndFileToBoardField(Two, G), game)
        , wP8(rankAndFileToBoardField(Two, H), game)

        , bP1(rankAndFileToBoardField(Seven, H), game)
        , bP2(rankAndFileToBoardField(Seven, G), game)
        , bP3(rankAndFileToBoardField(Seven, F), game)
        , bP4(rankAndFileToBoardField(Seven, E), game)
        , bP5(rankAndFileToBoardField(Seven, D), game)
        , bP6(rankAndFileToBoardField(Seven, C), game)
        , bP7(rankAndFileToBoardField(Seven, B), game)
        , bP8(rankAndFileToBoardField(Seven, A), game)
    { }

};

} // namespace Chess

#endif
