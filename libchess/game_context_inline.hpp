GameContext::GameContext() 
    : wP1(rankAndFileToBoardField(Two, A), gameState)
    , wP2(rankAndFileToBoardField(Two, B), gameState)
    , wP3(rankAndFileToBoardField(Two, C), gameState)
    , wP4(rankAndFileToBoardField(Two, D), gameState)
    , wP5(rankAndFileToBoardField(Two, E), gameState)
    , wP6(rankAndFileToBoardField(Two, F), gameState)
    , wP7(rankAndFileToBoardField(Two, G), gameState)
    , wP8(rankAndFileToBoardField(Two, H), gameState)

    , wR1(rankAndFileToBoardField(One, A), gameState)
    , wR2(rankAndFileToBoardField(One, H), gameState)

    , wN1(rankAndFileToBoardField(One, B), gameState)
    , wN2(rankAndFileToBoardField(One, G), gameState)

    , wB1(rankAndFileToBoardField(One, C), gameState)
    , wB2(rankAndFileToBoardField(One, F), gameState)

    , wQ (rankAndFileToBoardField(One, D), gameState)
    , wK (rankAndFileToBoardField(One, E), gameState)

    , bP1(rankAndFileToBoardField(Seven, H), gameState)
    , bP2(rankAndFileToBoardField(Seven, G), gameState)
    , bP3(rankAndFileToBoardField(Seven, F), gameState)
    , bP4(rankAndFileToBoardField(Seven, E), gameState)
    , bP5(rankAndFileToBoardField(Seven, D), gameState)
    , bP6(rankAndFileToBoardField(Seven, C), gameState)
    , bP7(rankAndFileToBoardField(Seven, B), gameState)
    , bP8(rankAndFileToBoardField(Seven, A), gameState)

    , bR1(rankAndFileToBoardField(Eight, H), gameState)
    , bR2(rankAndFileToBoardField(Eight, A), gameState)

    , bN1(rankAndFileToBoardField(Eight, G), gameState)
    , bN2(rankAndFileToBoardField(Eight, B), gameState)

    , bB1(rankAndFileToBoardField(Eight, C), gameState)
    , bB2(rankAndFileToBoardField(Eight, F), gameState)

    , bQ (rankAndFileToBoardField(Eight, D), gameState)
    , bK (rankAndFileToBoardField(Eight, E), gameState)
{
}

PieceVector GameContext::pawns(Side side)
{
    switch (side) {
    case Side::White: return PieceVector { &wP1, &wP2, &wP3, &wP4, &wP5, &wP6, &wP7, &wP8 };
    case Side::Black: return PieceVector { &bP1, &bP2, &bP3, &bP4, &bP5, &bP6, &bP7, &bP8 };
    }
}

PieceVector GameContext::pawns()
{
    return pawns(gameState.turn());
}

PieceVector GameContext::rooks(Side side)
{
    switch (side) {
    case Side::White: return PieceVector { &wR1, &wR2 };
    case Side::Black: return PieceVector { &bR1, &bR2 };
    }
}

PieceVector GameContext::rooks()
{
    return rooks(gameState.turn());
}

PieceVector GameContext::knights(Side side)
{
    switch (side) {
    case Side::White: return PieceVector { &wN1, &wN2 };
    case Side::Black: return PieceVector { &bN1, &bN2 };
    }
}

PieceVector GameContext::knights()
{
    return knights(gameState.turn());
}

PieceVector GameContext::bishops(Side side)
{
    switch (side) {
    case Side::White: return PieceVector { &wB1, &wB2 };
    case Side::Black: return PieceVector { &bB1, &bB2 };
    }
}

PieceVector GameContext::bishops()
{
    return bishops(gameState.turn());
}

PieceVector GameContext::queen(Side side)
{
    switch (side) {
    case Side::White: return PieceVector { &wQ };
    case Side::Black: return PieceVector { &bQ };
    }
}

PieceVector GameContext::queen()
{
    return queen(gameState.turn());
}

PieceVector GameContext::king(Side side)
{
    switch (side) {
    case Side::White: return PieceVector { &wK };
    case Side::Black: return PieceVector { &bK };
    }
}

PieceVector GameContext::king()
{
    return king(gameState.turn());
}
