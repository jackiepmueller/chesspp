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

    derived.sweep(bf, std::bind(&Derived::tryForwardLeft,  &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryForwardRight, &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryBackLeft,     &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryBackRight,    &derived, std::placeholders::_1, Bool::CanTake));

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

bool WhiteBishop::move(BoardField bf)
{
    return Bishop<WhiteBishop>::move(bf);
}

bool WhiteBishop::move(Rank rank, File file)
{
    return Bishop<WhiteBishop>::move(rank, file);
}

BoardField WhiteBishop::validMoves()
{
    return Bishop<WhiteBishop>::validMoves();
}

BlackBishop::BlackBishop(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

bool BlackBishop::move(BoardField bf)
{
    return Bishop<BlackBishop>::move(bf);
}

bool BlackBishop::move(Rank rank, File file)
{
    return Bishop<BlackBishop>::move(rank, file);
}

BoardField BlackBishop::validMoves()
{
    return Bishop<BlackBishop>::validMoves();
}
