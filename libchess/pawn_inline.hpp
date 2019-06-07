template <typename Derived>
Pawn<Derived>::Pawn()
{
    auto & derived = static_cast<Derived &>(*this);
    derived.setIdentifier('P');
}

template <typename Derived>
BoardField Pawn<Derived>::validMoves()
{
    auto & derived = static_cast<Derived &>(*this);

    BoardField bf = 0;
    auto res = derived.tryForward(1, !Bool::CanTake);
    if (res.valid) bf |= res.bf;
    if (derived.isFirstMove()) {
        res = derived.tryForward(2, !Bool::CanTake);
        if (res.valid) bf |= res.bf;
    }

    // diagonal attack, must take
    res = derived.tryForwardLeft(1, Bool::CanTake);
    if (res.valid && res.took) bf |= res.bf;
    res = derived.tryForwardRight(1, Bool::CanTake);
    if (res.valid && res.took) bf |= res.bf;

    return bf;
}

template <typename Derived>
bool Pawn<Derived>::move(BoardField pos)
{
    assert(validPosition(pos));
    auto const validMoves = this->validMoves();
    auto & derived = static_cast<Derived &>(*this);
    if (pos & validMoves) {
        auto & pieceMap = derived.pieceMap();
        auto piece = pieceMap[pos];
        if (piece) {
            piece->setPos(0);
        }
        derived.setPos(pos);
        if (derived.isFirstMove()) {
            derived.setMoved();
        }
        return true;
    }
    return false;
}

template <typename Derived>
bool Pawn<Derived>::move(Rank rank, File file)
{
    return move(rankAndFileToBoardField(rank, file));
}

WhitePawn::WhitePawn(BoardField startingPos, GameState & gameState)
    : Piece<White>(startingPos, gameState)
{
}

inline bool WhitePawn::move(BoardField bf)
{
    return Pawn<WhitePawn>::move(bf);
}

inline bool WhitePawn::move(Rank rank, File file)
{
    return Pawn<WhitePawn>::move(rank, file);
}

BlackPawn::BlackPawn(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

inline bool BlackPawn::move(BoardField bf)
{
    return Pawn<BlackPawn>::move(bf);
}

inline bool BlackPawn::move(Rank rank, File file)
{
    return Pawn<BlackPawn>::move(rank, file);
}
