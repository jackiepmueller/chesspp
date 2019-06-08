#include "chesspp.hpp"

#include <iostream>
#include <exception>

namespace Chess {

ChessPP::ChessPP()
    : gc_()
    , ui_(gc_)
{
}

void ChessPP::run()
{
    try {
        ui_.run();
    }
    catch (std::runtime_error const & e) {
        std::cerr << "caught runtime exception: " << e.what() << std::endl;
    }
    catch (std::exception const & e) {
        std::cerr << "caught exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "caught unknown exception" << std::endl;
    }
}

} // namespace Chess
