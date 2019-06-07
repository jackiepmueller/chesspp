PieceBase::PieceBase(Side side, BoardField startingPos, GameState & gameState)
    : side_(side)
    , pos_(0)
    , startingPos_(startingPos)
    , gameState_(gameState)
{
    bool const occupied = (gameState_.board() & pos());
    assert(!occupied);
    if (occupied) {
        throw std::runtime_error("error trying to place piece on occupied spot");
    }

    setPos(startingPos);

    gameState_.board() |= pos();
    gameState_.pieces().push_back(this);
}

void PieceBase::setPos(Rank rank, File file)
{
    setPos(rankAndFileToBoardField(rank, file));
}

void PieceBase::setPos(BoardField pos)
{
    assert(validPosition(pos));
    auto & board = gameState_.board();
    auto & pieceMap = gameState_.pieceMap();

    pieceMap[pos_] = nullptr;
    board &= ~pos_;
    board |= pos;
    pos_ = pos;

    if (alive()) pieceMap[pos_] = this;

    if (onSetPos_) onSetPos_();
}

template <typename SideType>
Piece<SideType>::Piece(BoardField startingPos, GameState & gameState)
    : PieceBase(SideType::side, startingPos, gameState)
{
}

template <typename SideType>
TryResult Piece<SideType>::tryForward(Rank n, bool canTake)
{
    return impl<8, Bool::Forward>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryBack(Rank n, bool canTake)
{
    return impl<8, Bool::Back>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryRight(File n, bool canTake)
{
    return impl<1, Bool::Forward>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryLeft(File n, bool canTake)
{
    return impl<1, Bool::Back>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryForwardLeft(Diag n, bool canTake)
{
    return impl<7, Bool::Forward>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryForwardRight(Diag n, bool canTake)
{
    return impl<9, Bool::Forward>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryBackLeft(Diag n, bool canTake)
{
    return impl<9, Bool::Back>(n, canTake);
}

template <typename SideType>
TryResult Piece<SideType>::tryBackRight(Diag n, bool canTake)
{
    return impl<7, Bool::Back>(n, canTake);
}

template <typename SideType>
template <typename Functor>
void Piece<SideType>::sweep(BoardField & bf, Functor const & f)
{
    int dist = 0;
    TryResult res;
    do {
        ++dist;
        res = f(dist);
        if (res.valid) bf |= res.bf;
    } while (res.valid && !res.took);
}

template <typename SideType>
template <uint8_t ShiftDistance, bool Forward>
TryResult Piece<SideType>::impl(uint8_t n, bool canTake)
{
    TryResult res;
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = Forward ? SideType::forwardShift(pos(), i * ShiftDistance)
                      : SideType::   backShift(pos(), i * ShiftDistance);

        bool const comp = Forward ? SideType::forwardCompare(tmp, pos())
                                  : SideType::   backCompare(tmp, pos());
        if (!comp) {
            return res;
        }
        if (tmp & this->board()) {
            if (i != n || !canTake) {
                return res;
            }
            else {
                auto piece = this->pieceMap()[tmp];
                assert(piece); // must be true since we determined a collision above
                if (piece->side() == this->side()) {
                    return res;
                }
                res.took = true;
            }
        }
    }
    res.valid = true;
    res.bf = tmp;
    return res;
}
