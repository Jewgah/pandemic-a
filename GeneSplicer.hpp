/**
 * Pandemic Game Assignment
 * C++ Course @Ariel_University
 * Part A
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

//Includes
#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"

/**
 *  A Gene Splicer can discover a cure by using any 5 cards, not necessarily of the same disease's color.
**/

namespace pandemic{

  class GeneSplicer : public Player{
    private:

    public:
    // Constructor using Initialization List
    GeneSplicer(Board& board_player_,City current_) : Player(board_player_,current_,"GeneSplicer"){}

    // A special method allowing the discovery of a cure by using any 5 cards, not necessarily of the same disease's color
    Player& discover_cure(Color color_);
  };
}
