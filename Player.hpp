/**
 * Pandemic Game Assignment
 * C++ Course @Ariel_University
 * Part A
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

#pragma once

//Includes
#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include <vector>

using namespace std;

namespace pandemic{
  class Player{

    private:
        Board& board_player;
        vector<int> cards;
        City current_city;
        string role_player;

    public:
      //Player Constructor as Initialization List
      Player(Board& board_player_,City current_,string role_player_):board_player(board_player_),current_city(current_),role_player(role_player_){}
      
      //Methods returning Player&
      Player& drive(City city_);
      Player& fly_charter(City city_);
      Player& fly_shuttle(City city_);
      Player& take_card(City city_);
      
      //Virtual Methods overriden in specific roles
      virtual Player& fly_direct(City city_);
      virtual Player& build();
      virtual Player& discover_cure(Color city_);
      virtual Player& treat(City city_);

      //Special Player's role
      string role();

  };
}
