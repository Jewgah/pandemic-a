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
#include <iostream>
#include <map>
#include "City.hpp"

using namespace std;

namespace pandemic{

  class Board{

    private:
      map<City,int> board_; //map containg cities (City) as keys and level of disease (int) as values

    public:
      bool is_clean();
      void remove_cures();
      int & operator[]( City city_ );
      friend ostream& operator<<(ostream& os,const Board& board_);
  };
}
