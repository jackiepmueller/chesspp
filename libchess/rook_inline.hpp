template <typename Derived>
Rook<Derived>::Rook()
{
    auto & derived = static_cast<Derived &>(*this);
    derived.setIdentifier('R');
}

template <typename Derived>
BoardField Rook<Derived>::validMoves()
{
    auto & derived = static_cast<Derived &>(*this);

    BoardField bf = 0;

    // forward
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryForward(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    // backward
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryBack(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    // left
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryLeft(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    // right
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryRight(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    return bf;
}

template <typename Derived>
bool Rook<Derived>::move(BoardField pos)
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
bool Rook<Derived>::move(Rank rank, File file)
{
    return move(rankAndFileToBoardField(rank, file));
}

WhiteRook::WhiteRook(BoardField startingPos, GameState & gameState)
    : Piece<White>(startingPos, gameState)
{
}

inline bool WhiteRook::move(BoardField bf)
{
    return Rook<WhiteRook>::move(bf);
}

inline bool WhiteRook::move(Rank rank, File file)
{
    return Rook<WhiteRook>::move(rank, file);
}

BlackRook::BlackRook(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

inline bool BlackRook::move(BoardField bf)
{
    return Rook<BlackRook>::move(bf);
}

inline bool BlackRook::move(Rank rank, File file)
{
    return Rook<BlackRook>::move(rank, file);
}
