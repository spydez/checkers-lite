//*****************************************************************************
//
// Reference the class description in Game.h.
//
//*****************************************************************************

#include "Game.h"
#include "controller/Player/Player.h"
#include "controller/Player/Human.h"
#include "controller/Player/AiRand.h"
#include "model/Board.h"
#include "view/AsciiView.h"

using namespace std;

namespace CheckersLite {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : Game
//*****************************************************************************
Game::Game(PlayerChoice whitePlayer, PlayerChoice blackPlayer):
  _players()
{
   // create the board
   _board = new Board();

   // create the view
   _view = new AsciiView(_board);

   // And now, the players!
   addPlayer(whitePlayer, Board::WHITE_PIECE);
   addPlayer(blackPlayer, Board::BLACK_PIECE);
}


//*****************************************************************************
// DESTRUCTOR : Game
//*****************************************************************************
Game::~Game(void)
{
   // free up memory in the vector
   while (!_players.empty())
   {
      delete _players.back();
      _players.pop_back();
   }

   // free up other pointers
   delete _view;
   delete _board;
}


//*****************************************************************************
// PUBLIC METHOD : play
//*****************************************************************************
Game::PlayErrors Game::play(void)
{
   // Assume success, change when error is encountered.
   PlayErrors retVal = PLAY_OK;

   // initial display of UI
   _view->newGame(_players[0]->color());
   _view->draw();

   // Main gameplay loop
   bool done = false;
   vector<Player*>::iterator it = _players.begin();
   while (!done)
   {
      // reset to first player if off the end of the vector
      if (it == _players.end())
      {
        it = _players.begin();
      }

      // is turn possible?
      if (_board->turnPossible((*it)->color()))
      {
         // let player take turn
         bool turnResult = (*it)->turn();
         if (turnResult)
         {
            // only move to next player if turn was valid move
            it++;
         }
      }
      else
      {
         // That player's currently stuck. Let the next guy try.
         it++;
      }
        
      // check for end-of-game conditions (win/stalemate)
      if (_board->state() < Board::GAME_PLAYABLE)
      {
         done = true;
      }

      // update UI
      _view->draw();
   }

   // return whatever retVal is set to now
   return retVal;
}


//*****************************************************************************
// PRIVATE METHOD : addPlayer
//*****************************************************************************
void Game::addPlayer(PlayerChoice player, Board::BoardToken playerColor)
{
   Player* newPlayer = NULL;
   switch (player)
   {
      case HUMAN:
         newPlayer = (Player*) new Human(_board, playerColor);
         break;
     case AI_RAND:
         newPlayer = (Player*) new AiRand(_board, playerColor);
         break;
      default:
         // Do nothing. Already NULL...
         break;
   }

   if (newPlayer != NULL)
   {
     _players.push_back(newPlayer);
   }
   else
   {
      throw 42;
   }
}



} // end namespace CheckersLite

