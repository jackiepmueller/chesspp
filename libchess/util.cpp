#include "util.hpp"

#include <cassert>

char const * Chess::rankToString(Rank rank)
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

char const * Chess::fileToString(File file)
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
