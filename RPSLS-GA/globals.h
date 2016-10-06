#ifndef GLOBALS
#define GLOBALS

#include <random>
using std::mt19937;

enum Hand{rock, paper, scissors, lizard, spock};
enum {rockWin = 5, paperWin = 5, scissorWin = 5,
      lizardWin = 5, spockWin = 5, tie = 1};
//enum {rockWin = 10, paperWin = 11, scissorWin = 12,
//      lizardWin = 13, spockWin = 14, tie = 2};
//enum {rockWin = 10, paperWin = 9, scissorWin = 12,
//      lizardWin = 5, spockWin = 14, tie = 2};
//enum {rockWin = 10, paperWin = 3, scissorWin = 3,
//      lizardWin = 3, spockWin = 3, tie = 2};
extern mt19937 rmt;


#endif // GLOBALS
