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
 *  A Virologist can treat a disease not only in the city he is in, but also in any city by using
 *  The proper card.
**/

namespace pandemic{

  class Virologist : public Player{
    private:

    public:
    //Constructor using Initialization List
    Virologist(Board& board_player_,City city_) : Player(board_player_,city_,"Virologist"){}

    // A special method allowing to treat a disease regardless of the city the Virologist is in
    // By using the proper card.
    Player& treat(City city_);
  };
}
