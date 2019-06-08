#ifndef SAN_PARSER_HPP
#define SAN_PARSER_HPP

#include "bit_manipulation.hpp"
#include "game_context.hpp"

#include <string>

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
