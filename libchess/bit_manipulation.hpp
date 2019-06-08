#ifndef BIT_MANIPULATION_HPP
#define BIT_MANIPULATION_HPP

#include <cassert>
#include <cstdint>
#include <iostream>

namespace Chess {

using BoardField = uint64_t;
using Rank = uint8_t;
using File = uint8_t;
using Diag = uint8_t;

static constexpr Rank One   = 0;
static constexpr Rank Two   = 1;
static constexpr Rank Three = 2;
static constexpr Rank Four  = 3;
static constexpr Rank Five  = 4;
static constexpr Rank Six   = 5;
static constexpr Rank Seven = 6;
static constexpr Rank Eight = 7;

static constexpr File A = 0;
static constexpr File B = 1;
static constexpr File C = 2;
static constexpr File D = 3;
static constexpr File E = 4;
static constexpr File F = 5;
static constexpr File G = 6;
static constexpr File H = 7;

static constexpr Rank InvalidRank = 8;
static constexpr File InvalidFile = 8;

// 1 and only 1 bit set
inline bool validPosition(BoardField bf)
{
    return (bf == 0) || (bf && !(bf & (bf - 1)));
}

inline std::size_t rankAndFileToOrdinal(Rank rank, File file)
{
    return rank * 8 + file;
}

inline BoardField rankAndFileToBoardField(Rank rank, File file)
{
    return uint64_t(1) << rankAndFileToOrdinal(rank, file);
}

inline std::size_t boardFieldToOrdinal(BoardField bf)
{
    assert(bf);
    if (!bf) throw std::runtime_error("error trying to take the ordinal of a dead board");

    assert(validPosition(bf));
    if (!validPosition(bf)) throw std::runtime_error("error trying to take the ordinal of an invald position");

    std::size_t ordinal = 0;
    while (bf = bf >> uint64_t(1), bf) ++ordinal;
    return ordinal;
}

inline Rank rankFromBoardField(BoardField bf)
{
    auto ord = boardFieldToOrdinal(bf);
    return ord / 8;
}

inline File fileFromBoardField(BoardField bf)
{
    auto ord = boardFieldToOrdinal(bf);
    return ord % 8;
}

inline BoardField positionFromString(std::string s)
{
    char file = std::toupper(s[0]) - 65;
    char rank = std::toupper(s[1]) - 49;

    return rankAndFileToBoardField(rank, file);
}

inline std::string positionToString(BoardField bf)
{
    auto rank = rankFromBoardField(bf);
    auto file = fileFromBoardField(bf);

    std::string s;
    s.push_back(file + 65);
    s.push_back(rank + 49);

    return s;
}

inline constexpr BoardField fileMask(File file)
{
    return 0b00000001000000010000000100000001000000010000000100000001 << file;
}

inline constexpr BoardField rankMask(Rank rank) {
    return 0b00000000000000000000000000000000000000000000000011111111 << (rank * 8);
}

} // namespace Chess

#endif
