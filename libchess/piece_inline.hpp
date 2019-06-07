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
    TryResult res;
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = SideType::forwardShift(pos(), i * 8);
        if (!SideType::forwardCompare(tmp, pos())) {
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

template <typename SideType>
TryResult Piece<SideType>::tryBack(Rank n, bool canTake)
{
    TryResult res;
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = SideType::backShift(pos(), i * 8);
        if (!SideType::backCompare(tmp, pos())) {
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

template <typename SideType>
TryResult Piece<SideType>::tryRight(File n, bool canTake)
{
    TryResult res;
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (File i = 1; i <= n; ++i) {
        tmp = SideType::forwardShift(pos(), i);
        if (!SideType::forwardCompare(tmp, pos())) {
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

template <typename SideType>
TryResult Piece<SideType>::tryLeft(File n, bool canTake)
{
    TryResult res;
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (File i = 1; i <= n; ++i) {
        tmp = SideType::backShift(pos(), i);
        if (!SideType::backCompare(tmp, pos())) {
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
