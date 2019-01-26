#ifndef CHESS_TYPES_HPP
#define CHESS_TYPES_HPP

#include "bit_manipulation.hpp"
#include "game.hpp"

#include <boost/core/noncopyable.hpp>

#include <cassert>

namespace Chess {

struct Black;

struct White {
    using OtherSide = Black;

    static BoardField forwardShift(BoardField bf, size_t n) {
        return bf << n;
    }

    // is a further forward than b?
    static bool forwardCompare(BoardField a, BoardField b) {
        return a > b;
    }

    static BoardField backShift(BoardField bf, size_t n) {
        return bf >> n;
    }

    // is a further back than b?
    static bool backCompare(BoardField a, BoardField b) {
        return a < b;
    }
};

struct Black {
    using OtherSide = White;
    static BoardField forwardShift(BoardField bf, size_t n) {
        return bf >> n;
    }

    // is a further forward than b?
    static bool forwardCompare(BoardField a, BoardField b) {
        return a < b;
    }

    static BoardField backShift(BoardField bf, size_t n) {
        return bf << n;
    }

    // is a further back than b?
    static bool backCompare(BoardField a, BoardField b) {
        return a > b;
    }
};

enum class Diagonal : uint8_t {
    ForwardLeft,
    ForwardRight,
    BackLeft,
    BackRight

};

struct PieceBase : private boost::noncopyable {
    PieceBase(BoardField startingPos, Game & game)
        : pos_(startingPos)
        , startingPos_(startingPos)
        , game_(game)
    { 
        game_.board() |= pos();
        game_.pieces().push_back(this);
    }

    void setPos(Rank rank, File file) {
        setPos(rankAndFileToBoardField(rank, file));
    }

    void setPos(BoardField pos) {
        auto & board = this->board();
        board &= ~pos_;
        board |= pos;
        pos_ = pos;
    }

    BoardField pos() const {
        return pos_;
    }

    Rank rank() const {
        return rankFromBoardField(pos_);
    }

    File file() const {
        return fileFromBoardField(pos_);
    }

    bool alive() const {
        return pos() != 0;
    }

protected:
    BoardField board() const {
        return game_.board();
    }

    BoardField & board() {
        return game_.board();
    }

    BoardField pos_;
    BoardField const startingPos_;

private:
    Game & game_;
};

using TryResult = std::pair<bool, BoardField>;

template <typename Side>
struct Piece : PieceBase {
    Piece(BoardField startingPos, Game & game)
        : PieceBase(startingPos, game)
    { 
    }

    BoardField forward(Rank n);
    BoardField back(Rank n);
    BoardField left(File n);
    BoardField right(File n);

    TryResult tryForward(Rank n, bool canTake = false);
    TryResult tryBack(Rank n, bool canTake = false);
    TryResult tryLeft(File n, bool canTake = false);
    TryResult tryRight(File n, bool canTake = false);

    BoardField diagonal(uint8_t n, Diagonal diagonal) {
        switch (diagonal) {
        case Diagonal::ForwardLeft:
            forward(n);
            left(n);
            break;
        case Diagonal::ForwardRight:
            forward(n);
            right(n);
            break;
        case Diagonal::BackLeft:
            back(n);
            left(n);
            break;
        case Diagonal::BackRight:
            back(n);
            right(n);
            break;
        }
        return pos();
    }
};

template <typename Side>
BoardField Piece<Side>::forward(Rank n) {
    assert(n <= 7);
    pos_ = Side::forwardShift(pos_, n * 8);
    return pos_;
}

template <typename Side>
BoardField Piece<Side>::back(Rank n) {
    assert(n <= 7);
    pos_ = Side::backShift(pos_, n * 8);
    return pos_;
}

template <typename Side>
TryResult Piece<Side>::tryForward(Rank n, bool canTake) {
    TryResult res { false, 0 };
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = Side::forwardShift(pos_, i * 8);
        if (!Side::forwardCompare(tmp, pos_)) {
            return res;
        }
        if (tmp & this->board()) {
            if (i != n || !canTake) {
                return res;
            }
            else {
                // TODO, we can take but we have to check if the piece being taken is on the other side
            }
        }
    }
    res.first = true;
    res.second = tmp;
    return res;
}

template <typename Side>
TryResult Piece<Side>::tryBack(Rank n, bool canTake) {
    TryResult res { false, 0 };
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = Side::backShift(pos_, i * 8);
        if (!Side::backCompare(tmp, pos_)) {
            return res;
        }
        if (tmp & this->board()) {
            if (i != n || !canTake) {
                return res;
            }
            else {
                // TODO, we can take but we have to check if the piece being taken is on the other side
            }
        }
    }
    res.first = true;
    res.second = tmp;
    return res;
}

struct FirstMoveConcept {
    bool moved() const { return moved_; }
    void setMoved()    { moved_ = true; }
private:
    bool moved_ = false;
};

struct NoFirstMoveConcept {
    static constexpr bool moved() { return true; }
};

template <typename Derived>
struct Pawn : FirstMoveConcept {
    BoardField validMoves() {
        auto & derived = static_cast<Derived &>(*this);

        BoardField bf = 0;
        auto res = derived.tryForward(1);
        if (res.first) bf |= res.second;
        if (!derived.moved()) {
            res = derived.tryForward(2);
            if (res.first) bf |= res.second;
        }
        // TODO check for diagonal attacks
        return bf;
    }

    bool move(BoardField pos) {
        auto const validMoves = this->validMoves();
        auto & derived = static_cast<Derived &>(*this);
        if (pos & validMoves) {
            derived.setPos(pos);
            derived.setMoved();
            return true;
        }
        return false;
    }

    bool move(Rank rank, File file) {
        return move(rankAndFileToBoardField(rank, file));
    }
};

struct WhitePawn
    : Piece<White>
    , Pawn<WhitePawn>
{
    WhitePawn(BoardField startingPos, Game & game)
        : Piece<White>(startingPos, game)
    { }
};

struct BlackPawn
    : Piece<Black>
    , Pawn<BlackPawn>
{
    BlackPawn(BoardField startingPos, Game & game)
        : Piece<Black>(startingPos, game)
    { }
};

} // namespace Chess

#endif
