template <typename Derived>
Bishop<Derived>::Bishop()
{
    auto & derived = static_cast<Derived &>(*this);
    derived.setIdentifier('B');
}

template <typename Derived>
BoardField Bishop<Derived>::validMoves()
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
bool Bishop<Derived>::move(BoardField pos)
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
        return true;
    }
    return false;
}

template <typename Derived>
bool Bishop<Derived>::move(Rank rank, File file)
{
    return move(rankAndFileToBoardField(rank, file));
}

WhiteBishop::WhiteBishop(BoardField startingPos, GameState & gameState)
    : Piece<White>(startingPos, gameState)
{
}

inline bool WhiteBishop::move(BoardField bf)
{
    return Bishop<WhiteBishop>::move(bf);
}

inline bool WhiteBishop::move(Rank rank, File file)
{
    return Bishop<WhiteBishop>::move(rank, file);
}

BlackBishop::BlackBishop(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

inline bool BlackBishop::move(BoardField bf)
{
    return Bishop<BlackBishop>::move(bf);
}

inline bool BlackBishop::move(Rank rank, File file)
{
    return Bishop<BlackBishop>::move(rank, file);
}
