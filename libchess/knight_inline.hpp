template <typename Derived>
Knight<Derived>::Knight()
{
    auto & derived = static_cast<Derived &>(*this);
    derived.setIdentifier('N');
}

template <typename Derived>
BoardField Knight<Derived>::validMoves()
{
    auto & derived = static_cast<Derived &>(*this);
    using Side = typename Derived::Side;

    BoardField bf = 0;

//              FILE
//      A  B  C  D  E  F  G  H
//                             
//            50    52         
// R       41          45      
// A             35            
// N       25          29      
// K          18    20         
//                             
//                             
// 
    auto jumpAndTest = [&derived](uint8_t shiftDistance, bool forward) {
        BoardField tmp;
        tmp = forward ? Side::forwardShift(derived.pos(), shiftDistance)
                      : Side::   backShift(derived.pos(), shiftDistance);

        bool const comp = forward ? Side::forwardCompare(tmp, derived.pos())
                                  : Side::   backCompare(tmp, derived.pos());
        if (!comp) {
            return BoardField();
        }
        if (tmp & derived.board()) {
            auto piece = derived.pieceMap()[tmp];
            assert(piece); // must be true since we determined a collision above
            if (piece->side() == derived.side()) {
                return BoardField();
            }
        }
        return tmp;
    };

    bf |= jumpAndTest(6,  Bool::Forward);
    bf |= jumpAndTest(10, Bool::Forward);
    bf |= jumpAndTest(15, Bool::Forward);
    bf |= jumpAndTest(17, Bool::Forward);

    bf |= jumpAndTest(6,  Bool::Back);
    bf |= jumpAndTest(10, Bool::Back);
    bf |= jumpAndTest(15, Bool::Back);
    bf |= jumpAndTest(17, Bool::Back);

    return bf;
}

template <typename Derived>
bool Knight<Derived>::move(BoardField pos)
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
bool Knight<Derived>::move(Rank rank, File file)
{
    return move(rankAndFileToBoardField(rank, file));
}

WhiteKnight::WhiteKnight(BoardField startingPos, GameState & gameState)
    : Piece<White>(startingPos, gameState)
{
}

bool WhiteKnight::move(BoardField bf)
{
    return Knight<WhiteKnight>::move(bf);
}

bool WhiteKnight::move(Rank rank, File file)
{
    return Knight<WhiteKnight>::move(rank, file);
}

BoardField WhiteKnight::validMoves()
{
    return Knight<WhiteKnight>::validMoves();
}

BlackKnight::BlackKnight(BoardField startingPos, GameState & gameState)
    : Piece<Black>(startingPos, gameState)
{
}

bool BlackKnight::move(BoardField bf)
{
    return Knight<BlackKnight>::move(bf);
}

bool BlackKnight::move(Rank rank, File file)
{
    return Knight<BlackKnight>::move(rank, file);
}

BoardField BlackKnight::validMoves()
{
    return Knight<BlackKnight>::validMoves();
}
