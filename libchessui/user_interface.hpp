#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include "chess.hpp"

#include <ncurses.h>

#include <string>

//             012345678901234567890
//   0123456789111111111122222222223
//  0                              
//  1            Chess!            
//  2                              
//  3    A  B  C  D  E  F  G  H    
//  4                              
//  5   bbb                        
//  6 8 bRb N  B  Q  K  B  N  R  8 
//  7   bbb                        
//  8   www                        
//  9 7 wpw p  p  p  p  p  p  p  7 
// 10   www                        
// 11   bbb                        
// 12 6 bbb                      6 
// 13   bbb                        
// 14   www                        
// 15 5 www                      5 
// 16   www                        
// 17   bbb                        
// 18 4 bbb                      4 
// 19   bbb                        
// 20   www                        
// 21 3 www                      3 
// 22   www                        
// 23   bbb                        
// 24 2 bpb p  p  p  p  p  p  p  2 
// 25   bbb                        
// 26   wwwbbb               bbb   
// 27 1 wRwbNb B  Q  K  B  N bRb 1 
// 28   wwwbbb               bbb   
// 29                              
// 30    A  B  C  D  E  F  G  H    
// 31                              
// 32 W(*) B( ) : xx message area xxxxxxxxxxxx
// 33                              
// 34 >                            
// 35                              

// A1 : 27, 5
// B1 : 27, 8
// A2 : 24, 5
//
// rank to row: 27 - rank * 3
// file to col: 5 + file * 3

namespace Chess {
namespace UI {

struct Position {
    constexpr Position(size_t row, size_t col) : row(row), col(col) { }
    size_t row;
    size_t col;
};

struct UserInterface {
    UserInterface(GameContext & gc);

    void run();
    void redraw();

private:
    void runCommand();
    void drawCommand();
    void drawMessage();

    Position positionFromBoardField(Chess::BoardField bf);

    bool running_ = true;
    bool showingHelp_ = false;
    std::string cmd_;
    std::string msg_;
    GameContext & gc_;
};

} // namespace UI
} // namespace Chess

#endif
