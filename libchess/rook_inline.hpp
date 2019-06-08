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

    derived.sweep(bf, std::bind(&Derived::tryForward,      &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryBack,         &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryLeft,         &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryRight,        &derived, std::placeholders::_1, Bool::CanTake));

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

bool WhiteRook::move(BoardField bf)
{
    return Rook<WhiteRook>::move(bf);
}

bool WhiteRook::move(Rank rank, File file)
{
    return Rook<WhiteRook>::move(rank, file);
}

BoardField WhiteRook::validMoves()
{
    return Rook<WhiteRook>::validMoves();
}

BlackRook::BlackRook(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

bool BlackRook::move(BoardField bf)
{
    return Rook<BlackRook>::move(bf);
}

bool BlackRook::move(Rank rank, File file)
{
    return Rook<BlackRook>::move(rank, file);
}

BoardField BlackRook::validMoves()
{
    return Rook<BlackRook>::validMoves();
}
