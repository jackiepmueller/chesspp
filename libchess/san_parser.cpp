#include "san_parser.hpp"
#include "util.hpp"

namespace Chess {
namespace SANParser {

Result parse(GameContext & gc, std::string s)
{
    Result result;

    if (s.size() < 2) {
        return result;
    }

    if (s == "0-0") {
        // TODO king side castle
        return result;
    }

    if (s == "0-0-0") {
        // TODO queen side castle
        return result;
    }

    // dest is in the last two characters
    auto dest = positionFromString(s.substr(s.size() - 2, 2));
    if (!validPosition(dest)) {
        return result;
    }

    // remove dest
    s.pop_back();
    s.pop_back();

    PieceVector potentials;

    // simple pawn movement
    if (s.empty()) {
        auto pawns = gc.pawns();
        auto file = fileFromBoardField(dest);
        for (auto pawn : gc.pawns()) {
            if (pawn->file() == file) {
                potentials.push_back(pawn);
            }
        }
    }
    else {
        switch (s[0]) {
        case 'R':
            potentials = gc.rooks();
            break;
        case 'N':
            potentials = gc.knights();
            break;
        default:
            break;
        }

        // TODO: do this with rank and file masking
        if (s.size() == 2) {
            if (isFile(s[1])) {
                auto file = fileFromChar(s[1]);
                auto it = potentials.begin();
                while (it != potentials.end()) {
                    auto piece = *it;
                    if (piece->file() != file) {
                        it = potentials.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
            else if (isRank(s[1])) {
                auto rank = rankFromChar(s[1]);
                auto it = potentials.begin();
                while (it != potentials.end()) {
                    auto piece = *it;
                    if (piece->rank() != rank) {
                        it = potentials.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
            else {
                return result;
            }
        }
    }

    /////////////////////////////////
    // Here down should be generic //
    /////////////////////////////////
    auto it = potentials.begin();
    while (it != potentials.end()) {
        auto piece = *it;
        if (!(piece->validMoves() & dest)) {
            it = potentials.erase(it);
        }
        else {
            ++it;
        }
    }

    if (potentials.empty()) {
        result.reason = Invalid;
    }
    else if (potentials.size() != 1) {
        result.reason = Ambiguous;
    }
    else {
        result.from = potentials[0]->pos();
        result.to   = dest;
        result.reason = Success;
    }

    return result; 
}

Result parse(std::string from, std::string to)
{
    Result result;
    result.from   = positionFromString(from);
    result.to     = positionFromString(to);
    result.reason = Success;
    return result; 
}

} // namespace SANParser
} // namespace Chess
