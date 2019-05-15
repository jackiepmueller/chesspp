#ifndef CHESS_TYPES_HPP
#define CHESS_TYPES_HPP

#include "bit_manipulation.hpp"
#include "game_state.hpp"

#include <boost/core/noncopyable.hpp>

#include <cassert>
#include <functional>
#include <stdexcept>

namespace Chess {

using StateChangeEvent = std::function<void()>;

enum class Side {
    White,
    Black
};

struct Black;

struct White {
    using OtherSide = Black;

    static constexpr Side side = Side::White;

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

    static constexpr Side side = Side::Black;

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
    PieceBase(Side side, BoardField startingPos, GameState & gameState)
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

    void setPos(Rank rank, File file) {
        setPos(rankAndFileToBoardField(rank, file));
    }

    void setPos(BoardField pos) {
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

    BoardField pos() const {
        return pos_;
    }

    Rank rank() const {
        return rankFromBoardField(pos());
    }

    File file() const {
        return fileFromBoardField(pos());
    }

    bool alive() const {
        return pos() != 0;
    }

    Side side() const {
        return side_;
    }

    StateChangeEvent & onSetPos() {
        return onSetPos_;
    }

    char identifier() const {
        return identifier_;
    }

    void setIdentifier(char id) {
        identifier_ = id;
    }

    virtual bool move(BoardField) = 0;
    virtual bool move(Rank rank, File file) = 0;

protected:
    BoardField board() const {
        return gameState_.board();
    }

    BoardField & board() {
        return gameState_.board();
    }

    Side const side_;
    BoardField pos_; // never modify directly
    BoardField const startingPos_;
    char identifier_;

private:
    StateChangeEvent onSetPos_;

    GameState & gameState_;
};

using TryResult = std::pair<bool, BoardField>;

template <typename SideType>
struct Piece : PieceBase {
    Piece(BoardField startingPos, GameState & gameState)
        : PieceBase(SideType::side, startingPos, gameState)
    { 
    }

    BoardField forward(Rank n);
    BoardField back(Rank n);
    BoardField left(File n);
    BoardField right(File n);

    TryResult tryForward(Rank n, bool canTake = true);
    TryResult tryBack(Rank n, bool canTake = true);
    TryResult tryLeft(File n, bool canTake = true);
    TryResult tryRight(File n, bool canTake = true);

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

template <typename SideType>
BoardField Piece<SideType>::forward(Rank n) {
    assert(n <= 7);
    pos_ = SideType::forwardShift(pos_, n * 8);
    return pos_;
}

template <typename SideType>
BoardField Piece<SideType>::back(Rank n) {
    assert(n <= 7);
    pos_ = SideType::backShift(pos_, n * 8);
    return pos_;
}

template <typename SideType>
TryResult Piece<SideType>::tryForward(Rank n, bool canTake) {
    TryResult res { false, 0 };
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = SideType::forwardShift(pos_, i * 8);
        if (!SideType::forwardCompare(tmp, pos_)) {
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

template <typename SideType>
TryResult Piece<SideType>::tryBack(Rank n, bool canTake) {
    TryResult res { false, 0 };
    if (n > 7) {
        return res;
    }

    // sweep up to just before the destination
    BoardField tmp;
    for (Rank i = 1; i <= n; ++i) {
        tmp = SideType::backShift(pos_, i * 8);
        if (!SideType::backCompare(tmp, pos_)) {
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
    Pawn() {
        auto & derived = static_cast<Derived &>(*this);
        derived.setIdentifier('P');
    }

    BoardField validMoves() {
        auto & derived = static_cast<Derived &>(*this);

        BoardField bf = 0;
        auto res = derived.tryForward(1, /* canTake */false);
        if (res.first) bf |= res.second;
        if (!derived.moved()) {
            res = derived.tryForward(2, /* canTake */false);
            if (res.first) bf |= res.second;
        }
        // TODO check for diagonal attacks
        return bf;
    }

    bool move(BoardField pos) {
        assert(validPosition(pos));
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
    WhitePawn(BoardField startingPos, GameState & gameState)
        : Piece<White>(startingPos, gameState)
    { }

    virtual bool move(BoardField bf) override {
        return Pawn<WhitePawn>::move(bf);
    }

    virtual bool move(Rank rank, File file) override {
        return Pawn<WhitePawn>::move(rank, file);
    }
};

struct BlackPawn
    : Piece<Black>
    , Pawn<BlackPawn>
{
    BlackPawn(BoardField startingPos, GameState & gameState)
        : Piece<Black>(startingPos, gameState)
    { }

    virtual bool move(BoardField bf) override {
        return Pawn<BlackPawn>::move(bf);
    }

    virtual bool move(Rank rank, File file) override {
        return Pawn<BlackPawn>::move(rank, file);
    }
};

} // namespace Chess

#endif
