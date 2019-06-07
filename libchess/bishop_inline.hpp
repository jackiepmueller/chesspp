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

    // forward left
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryForwardLeft(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    // forward right
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryForwardRight(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    // back left
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryBackLeft(dist, Bool::CanTake);
            if (res.valid) bf |= res.bf;
        } while (res.valid && !res.took); // stop if we would take the piece
    }

    // back right
    {
        int dist = 0;
        TryResult res;
        do {
            ++dist;
            res = derived.tryBackRight(dist, Bool::CanTake);
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