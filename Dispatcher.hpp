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
 *  When a Dispatcher is in a city that has a Research Station.
 * he can fly directly to any destination without needing the proper card 
**/

namespace pandemic{

  class Dispatcher : public Player{
    
    private:

    public:
    // Constructor using Initialization List
    Dispatcher(Board& board_player_,City city_) : Player(board_player_,city_,"Dispatcher"){}

    // Special fly_direct method that allows a dispatcher to fly directly to any city without needing the proper
    // card, only when the current city he is in has a Research Station
    Player& fly_direct(City city_);
  };
}
