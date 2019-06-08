template <typename Derived>
King<Derived>::King()
{
    auto & derived = static_cast<Derived &>(*this);
    derived.setIdentifier('K');
}

template <typename Derived>
BoardField King<Derived>::validMoves()
{
    auto & derived = static_cast<Derived &>(*this);

    BoardField bf = 0;
    TryResult res;

    bf |= derived.tryForward(1).bf;
    bf |= derived.tryBack(1).bf;
    bf |= derived.tryLeft(1).bf;
    bf |= derived.tryRight(1).bf;
    bf |= derived.tryForwardLeft(1).bf;
    bf |= derived.tryForwardRight(1).bf;
    bf |= derived.tryBackLeft(1).bf;
    bf |= derived.tryBackRight(1).bf;

    return bf;
}

template <typename Derived>
bool King<Derived>::move(BoardField pos)
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
bool King<Derived>::move(Rank rank, File file)
{
    return move(rankAndFileToBoardField(rank, file));
}

WhiteKing::WhiteKing(BoardField startingPos, GameState & gameState)
    : Piece<White>(startingPos, gameState)
{
}

inline bool WhiteKing::move(BoardField bf)
{
    return King<WhiteKing>::move(bf);
}

inline bool WhiteKing::move(Rank rank, File file)
{
    return King<WhiteKing>::move(rank, file);
}

BlackKing::BlackKing(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

inline bool BlackKing::move(BoardField bf)
{
    return King<BlackKing>::move(bf);
}

inline bool BlackKing::move(Rank rank, File file)
{
    return King<BlackKing>::move(rank, file);
}
