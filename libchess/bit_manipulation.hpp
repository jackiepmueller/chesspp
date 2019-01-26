#ifndef BIT_MANIPULATION_HPP
#define BIT_MANIPULATION_HPP

#include <cstdint>
#include <iostream>

namespace Chess {

using BoardField = uint64_t;
using Rank = uint8_t;
using File = uint8_t;

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

std::size_t rankAndFileToOrdinal(Rank rank, File file)
{
    return rank * 8 + file;
}

BoardField rankAndFileToBoardField(Rank rank, File file)
{
    return uint64_t(1) << rankAndFileToOrdinal(rank, file);
}

std::size_t boardFieldToOrdinal(BoardField bf)
{
    std::size_t ordinal = 0;
    while (bf = bf >> uint64_t(1), bf) ++ordinal;
    return ordinal;
}

Rank rankFromBoardField(BoardField bf)
{
    auto ord = boardFieldToOrdinal(bf);
    return ord / 8;
}

File fileFromBoardField(BoardField bf)
{
    auto ord = boardFieldToOrdinal(bf);
    return ord % 8;
}

bool validPosition(BoardField bf)
{
    return (bf == 0) || (bf && !(bf & (bf - 1)));
}

} // namespace Chess

#endif
