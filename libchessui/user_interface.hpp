#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include "chess.hpp"

#include <ncurses.h>

//            012345678901234567890
//   013456789111111111122222222223
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
// 32 W(*) B( )                    
// 33                              
// 34 >                            
// 35                              

namespace Chess {
namespace UI {

struct UserInterface {
    UserInterface(Game & game);

    void run();
    void redraw();

private:
    Game const & game_;
};

} // namespace UI
} // namespace Chess

#endif
