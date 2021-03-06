//*****************************************************************************
//
// Reference the class description in AiRand.h.
//
//*****************************************************************************

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "AiRand.h"

using namespace std;

// because having just one sleep function is insane
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

  #include <windows.h>

  inline void delay( unsigned long ms )
  {
    Sleep( ms );
  }

#else  // presume POSIX

  #include <unistd.h>

  inline void delay( unsigned long ms )
  {
    usleep( ms * 1000 );
  }

#endif

namespace CheckersLite {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : AiRand
//*****************************************************************************
AiRand::AiRand(Board* checkersBoard, Board::BoardToken playerColor):
  Player(checkersBoard, playerColor)
{
   // initialize random number generator
   srand((unsigned int)time(0));
}


//*****************************************************************************
// DESTRUCTOR : AiRand
//*****************************************************************************
AiRand::~AiRand(void)
{
   // Intentionally left blank.
}

//*****************************************************************************
// PUBLIC METHOD : turn
//*****************************************************************************
bool AiRand::turn(void)
{
   // pretend to think really hard...
   static const unsigned long THINK_TIME_MS = 750; // almost a second
   cout << "The computer is thinking..." << endl;
   delay(THINK_TIME_MS);

   // get the possible moves
   vector<Board::BoardPos> moves;
   _board->turnPossible(_color, &moves);

   // randomly choose one
   unsigned int x = rand() % moves.size();
   cout << "The computer found " << moves.size() << " moves and chose "
        << "#" << x << "." << endl;

   // execute the move
   return _board->move(_color, moves[x]._row, moves[x]._col)
                ->to(moves[x]._toRow, moves[x]._toCol);
}


} // end namespace CheckersLite

