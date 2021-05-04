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
 *  A Field Doctor can treat diseases not only in the city he is in but also in all the nearby ones,
 *  without needing the proper card.
**/

namespace pandemic{

  class FieldDoctor : public Player{
    private:

    public:
    // Constructor using Initialization List
    FieldDoctor(Board& board_player_,City current_) : Player(board_player_,current_,"FieldDoctor"){}

    // Special treat method than can treat a disease not only in current city but also in nearby ones.
    Player& treat(City city_);
  };
}
