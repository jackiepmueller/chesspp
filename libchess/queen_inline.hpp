template <typename Derived>
Queen<Derived>::Queen()
{
    auto & derived = static_cast<Derived &>(*this);
    derived.setIdentifier('Q');
}

template <typename Derived>
BoardField Queen<Derived>::validMoves()
{
    auto & derived = static_cast<Derived &>(*this);

    BoardField bf = 0;

    derived.sweep(bf, std::bind(&Derived::tryForward,      &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryBack,         &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryLeft,         &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryRight,        &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryForwardLeft,  &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryForwardRight, &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryBackLeft,     &derived, std::placeholders::_1, Bool::CanTake));
    derived.sweep(bf, std::bind(&Derived::tryBackRight,    &derived, std::placeholders::_1, Bool::CanTake));

    return bf;
}

template <typename Derived>
bool Queen<Derived>::move(BoardField pos)
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
bool Queen<Derived>::move(Rank rank, File file)
{
    return move(rankAndFileToBoardField(rank, file));
}

WhiteQueen::WhiteQueen(BoardField startingPos, GameState & gameState)
    : Piece<White>(startingPos, gameState)
{
}

inline bool WhiteQueen::move(BoardField bf)
{
    return Queen<WhiteQueen>::move(bf);
}

inline bool WhiteQueen::move(Rank rank, File file)
{
    return Queen<WhiteQueen>::move(rank, file);
}

BlackQueen::BlackQueen(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

inline bool BlackQueen::move(BoardField bf)
{
    return Queen<BlackQueen>::move(bf);
}

inline bool BlackQueen::move(Rank rank, File file)
{
    return Queen<BlackQueen>::move(rank, file);
}
