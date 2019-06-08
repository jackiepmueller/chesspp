#ifndef UTIL_HPP
#define UTIL_HPP

#include "bit_manipulation.hpp"

namespace Chess {

char const * rankToString(Rank rank);
char const * fileToString(File file);

bool isFile(char c);
bool isRank(char c);

File fileFromChar(char c);
Rank rankFromChar(char c);

}

#endif
