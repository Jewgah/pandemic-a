/**
 * Pandemic Game Assignment
 * C++ Course @Ariel_University
 * Part A
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

#include "Player.hpp"

/* Each action should update the board status and player position accordingly.
   If the operation is invalid, an appropriate exception must be thrown.
   There can be more than one player in a city. */
   
namespace pandemic{

  // Move from the current city to a nearby city (according to the map)
  Player& Player::drive(City city_){

    //TODO
    return *this;
  }
  
  // Uses the card of a city and move there.
  // The card is then thrown.
  Player& Player::fly_direct(City city_){

    //TODO
    return *this;
  }

  // Uses the card of the city the player is currently in to fly anywhere.
  // The card is then thrown.
  Player& Player::fly_charter(City city_){

    //TODO
    return *this;
  }

  // If there is a Research Station in the city the player is currently in, then he can fly to any other
  // city which also has a Research Station.
  Player& Player::fly_shuttle(City city_){

    //TODO
    return *this;
  }

  // Builds a Research Station in the city the player is currently in by using the card of this current city.
  // The card is then thrown.
  Player& Player::build(){

    //TODO
  return *this;
  }

  // Discovers a cure for a disease of a certain color.
  // To do this, you must be in a city that has a research station, and throw 5 colored cards of the disease.
  // The color of the city they are in does not matter.
  Player& Player::discover_cure(Color color_){

    //TODO
    return *this;
  }

  // Reduces the level of the disease in the current city by 1.
  // 1-If a cure for the disease has already been discovered in the color of the city, then the disease level is 
  // reduced to 0.
  // 2- If there is no infection at all in the city (disease level already at 0) then throws exception
  Player& Player::treat(City city_){

    //TODO
    return *this;
  }

  // Returns the role of the player
  string Player::role(){

    //TODO
    return "";
  }

  // Provides a random city card to the player.
  // There is only a single card for each city.
  // Thus, if we try to provide a card that is already in the hand of another player then
  // there won't be any change. -There is no need to check the correctness of this method: no need to check if
  // the card picked is indeed still in the deck, nor that the card was given twice. This method always succeeds
  Player& Player::take_card(City city_){

    //TODO
    return *this;
  }
}
