/**
 * Pandemic Game Assignment
 * C++ Course @Ariel_University
 * Part A
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

//Include
#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"

/**
 *  A Medic reduces the level of a disease to 0 when he treats it.
 *  Moreover, if a cure has already been discovered for a disease, the Medic
 *  Automatically reduces the level of the disease to 0 just by being in the city,
 *  Without needing to treat it.
**/

namespace pandemic{

  class Medic : public Player{
    private:

    public:
    //Constructor using Initialization List
    Medic(Board& board_player_,City city_) : Player(board_player_,city_,"Medic"){}

    // Special method that reduces the level of disease to 0.
    Player& treat(City city_);
  };
}
