#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include "bit_manipulation.hpp"
#include "game_state.hpp"

#include <boost/core/noncopyable.hpp>

#include <cassert>
#include <functional>
#include <stdexcept>

namespace Chess {

using StateChangeEvent = std::function<void()>;

namespace Bool {
    static constexpr bool CanTake = true;
    static constexpr bool Forward = true;
    static constexpr bool Back    = false;
} // namespace Bool

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
    inline PieceBase(Side side, BoardField startingPos, GameState & gameState);

    inline void setPos(Rank rank, File file);
    inline void setPos(BoardField pos);

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

    BoardField board() const {
        return gameState_.board();
    }

    BoardField & board() {
        return gameState_.board();
    }

    PieceMap const & pieceMap() const {
        return gameState_.pieceMap();
    }

    PieceMap & pieceMap() {
        return gameState_.pieceMap();
    }

private:
    Side const side_;
    BoardField pos_; // never modify directly
    BoardField const startingPos_;
    char identifier_;
    StateChangeEvent onSetPos_;
    GameState & gameState_;
};

struct TryResult {
    bool valid    = false;
    bool took     = false;
    BoardField bf = 0;
};

template <typename SideType>
struct Piece : PieceBase {
    using Side = SideType;

    inline Piece(BoardField startingPos, GameState & gameState);

    inline TryResult tryForward(Rank n, bool canTake = Bool::CanTake);
    inline TryResult tryBack   (Rank n, bool canTake = Bool::CanTake);
    inline TryResult tryRight  (File n, bool canTake = Bool::CanTake);
    inline TryResult tryLeft   (File n, bool canTake = Bool::CanTake);

    inline TryResult tryForwardLeft (Diag n, bool canTake = Bool::CanTake);
    inline TryResult tryForwardRight(Diag n, bool canTake = Bool::CanTake);
    inline TryResult tryBackLeft    (Diag n, bool canTake = Bool::CanTake);
    inline TryResult tryBackRight   (Diag n, bool canTake = Bool::CanTake);

    template <typename Functor>
    inline void sweep(BoardField & bf, Functor const & f);

private:
    template <uint8_t ShiftDistance, bool Forward>
    inline TryResult impl(uint8_t n, bool canTake);
};

struct FirstMoveConcept {
    bool isFirstMove() const { return !moved_; }
    void setMoved() { assert(!moved_); moved_ = true; }
private:
    bool moved_ = false;
};

#include "piece_inline.hpp"

} // namespace Chess

#endif
