#include "chesspp.hpp"

using namespace Chess;

ChessPP::ChessPP()
    : gc_()
    , ui_(gc_)
{
}

void ChessPP::run()
{
    ui_.run();
}
