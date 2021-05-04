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
 *  An Operations Expert can build a Research Station in the city he currently is without needing the proper card *
**/

namespace pandemic{
  class OperationsExpert : public Player{
    private:

    public:

    //Constructor using Initialization List
    OperationsExpert(Board& board_player_,City city_) : Player(board_player_,city_,"OperationsExpert"){}

    //Special build method which doesn't need to throw the proper card after building the Research Station
    Player& build();
  };
}
