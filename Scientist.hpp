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
 *  A Scientist can discover a cure by using only n cards instead of 5 (n is passed as parameter in the constructor)
**/

namespace pandemic{

  class Scientist : public Player{

    private:
      int n;

    public:
    //Constructor using Initialization List
    Scientist(Board& board_player_,City city_,int n_) : Player(board_player_,city_,"Scientist"),n(n_){}
    
    // A special method to discover a cure by using only n cards instead of 5
    Player& discover_cure(Color color_);
  };
}
