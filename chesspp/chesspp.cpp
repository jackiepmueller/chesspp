#include "chesspp.hpp"

using namespace Chess;

ChessPP::ChessPP()
    : ui_(gc_.game)
{
}

void ChessPP::run()
{
    ui_.run();
}
