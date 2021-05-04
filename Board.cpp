/**
 * Pandemic Game Assignment
 * C++ Course @Ariel_University
 * Part A
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

#include "Board.hpp"

namespace pandemic{

  //returns true if and only if the whole board is clean (no disease on board)
  bool Board::is_clean(){
    
    //TODO
    return false;
    }

  //Removes all the cures that have been discovered so far from the board
  //This method is intended for the purpose of writing tests
  //It never throws an exception, and there is no need to check it in a special way.
  void Board::remove_cures(){

    //TODO
  }

  //operator[] overloading: Reads and Updates the level of disease in the given city
  int & Board::operator[]( City city_ ){
    return this->board_[city_];
  }

  //Displays the status of the board including:
  // 1- The level of disease in each city
  // 2- The cures discovered so far
  // 3- The Research Stations built so far
  ostream& operator<<(ostream& os,const Board& board_){

    //TODO
    return os;
  }
}
