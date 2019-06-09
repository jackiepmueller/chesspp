#ifndef SAN_PARSER_HPP
#define SAN_PARSER_HPP

#include "bit_manipulation.hpp"
#include "game_context.hpp"

#include <string>

// Parse standard algebraic notation (SAN) into a from/to move pair.
//
// Implementation notes:
//
//      * More verbose instructions are accepted even when a terser version
//      would be sufficient. e.g. Ra1a3 instead of Ra3.
//      * Pawn captures such as ed5 are accepted even in a non capturing
//      scenario. e.g. ee5 
//      * Captures are not notated differently. (typically seen as Bxe5 or B:e5)

namespace Chess {
namespace SANParser {

enum Reason {
    Success,
    Ambiguous,
    Invalid,
    Fail
};

struct Result {
    BoardField from = 0;
    BoardField to = 0;
    Reason reason = Fail;

};

Result parse(GameContext & gc, std::string s);
Result parse(std::string from, std::string to);

} // namespace SANParser
} // namespace Chess

#endif
