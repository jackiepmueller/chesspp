#include "util.hpp"

#include <cassert>

namespace Chess {

char const * rankToString(Rank rank)
{
    switch (rank) {
    case One:
        return "1";
    case Two:
        return "2";
    case Three:
        return "3";
    case Four:
        return "4";
    case Five:
        return "5";
    case Six:
        return "6";
    case Seven:
        return "7";
    case Eight:
        return "8";
    default:
        assert(false);
        return "#";
    }
}

char const * fileToString(File file)
{
    switch (file) {
    case A:
        return "A";
    case B:
        return "B";
    case C:
        return "C";
    case D:
        return "D";
    case E:
        return "E";
    case F:
        return "F";
    case G:
        return "G";
    case H:
        return "H";
    default:
        assert(false);
        return "#";
    }
}

bool isFile(char c)
{
    c = std::toupper(c);
    return c >= 'A' && c <= 'H';
}

bool isRank(char c)
{
    return c >= '1' && c <= '7';
}

File fileFromChar(char c)
{
    assert(isFile(c));
    c = std::toupper(c);
    return c - 65;
}

Rank rankFromChar(char c)
{
    assert(isRank(c));
    return c - 49;
}

} // namespace Chess
