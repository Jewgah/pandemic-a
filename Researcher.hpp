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
 *  A Researcher can discover a cure in any city, without needing to be a Researcher Station there.
**/

namespace pandemic{
  class Researcher : public Player{
    private:

    public:
    //Constructor using Initialization List
    Researcher(Board& board_player_,City city_) : Player(board_player_,city_,"Researcher"){}

    // A special method to discover a cure without needing a Researcher Station in the city
    Player& discover_cure(Color color_);
  };
}
