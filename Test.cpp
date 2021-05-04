/**
 * Pandemic Game Assignment
 * C++ Course @Ariel_University
 * Part A
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

//Includes
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"

#include "doctest.h"

#include "OperationsExpert.hpp"
#include "GeneSplicer.hpp"
#include "Researcher.hpp"
#include "FieldDoctor.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <stdexcept>

using namespace pandemic;
using namespace std;


TEST_CASE("Drive")
{
  Board board;
  Player jordi {board, City::Atlanta, "Medic"};

  CHECK_NOTHROW(jordi.drive(City::Miami)); // Miami is linked to Atalanta
  CHECK_NOTHROW(jordi.drive(City::Bogota)); // Bogota is linked to Miami
  CHECK_THROWS(jordi.drive(City::Delhi)); // Delhi isn't directly connected to Miami
  CHECK_THROWS(jordi.drive(City::Karachi)); // Karachi is directly connected to Delhi but isn't directly connected to Miami
}

TEST_CASE("Fly Direct")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Player jordi {board, City::Atlanta, "Medic"};

  CHECK_THROWS(jordi.fly_direct(City::LosAngeles)); // Illegal: need the card Los Angeles
  jordi.take_card(City::LosAngeles); // Picks the card Los Angeles
  CHECK_NOTHROW(jordi.fly_direct(City::LosAngeles)); // Legal: uses the card Los Angeles
  CHECK_THROWS(jordi.fly_direct(City::LosAngeles)); // Illegal: no card + already in city
  jordi.take_card(City::LosAngeles); // Picks the card Los Angeles
  CHECK_THROWS(jordi.fly_direct(City::LosAngeles)); // Illegal: already in city ??????????????????????
}

TEST_CASE("Fly Charter")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Player jordi {board, City::Atlanta, "Medic"};
  CHECK_THROWS(jordi.fly_charter(City::LosAngeles)); // Illegal: need the card Atlanta
  jordi.take_card(City::Atlanta); // Picks the card Atlanta
  CHECK_NOTHROW(jordi.fly_charter(City::LosAngeles)); // Legal: uses the card Atlanta
  CHECK_THROWS(jordi.fly_charter(City::LosAngeles)); // Illegal: no card + already in city
  jordi.take_card(City::LosAngeles); // Picks the card Los Angeles
  CHECK_THROWS(jordi.fly_charter(City::LosAngeles)); // Illegal: already in city??????????????????
}

TEST_CASE("Fly Shuttle")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).

  Medic jordi{board, City::LosAngeles};
  Medic sachou{board, City::Paris};

  jordi.take_card(City::LosAngeles); // Picks the card Los Angeles
  CHECK_NOTHROW(jordi.build()); // legal, uses Los Angeles card to build RS

  CHECK_THROWS(jordi.fly_shuttle(City::Paris)); // Illegal: need RS in Paris
  
  sachou.take_card(City::Paris); // Picks the card Paris
  CHECK_NOTHROW(sachou.build()); // legal, uses Paris card to build RS


  CHECK_NOTHROW(jordi.fly_shuttle(City::Paris)); // Legal since there are RS in Los Angeles and Paris
  CHECK_NOTHROW(jordi.fly_shuttle(City::LosAngeles)); // Legal since there are RS in Los Angeles and Paris

  CHECK_NOTHROW(sachou.fly_shuttle(City::Paris)); // Legal since there are RS in Los Angeles and Paris
  CHECK_NOTHROW(sachou.fly_shuttle(City::LosAngeles)); // Legal since there are RS in Los Angeles and Paris
}

TEST_CASE("Build")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).

  Medic jordi{board, City::LosAngeles};

  CHECK_THROWS(jordi.build()); // illegal, doesn't have the proper card

  jordi.take_card(City::LosAngeles); // Picks the card Los Angeles

  CHECK_NOTHROW(jordi.build()); // legal, uses Los Angeles card to build RS
  CHECK_THROWS(jordi.build()); // Illegal, card used + RS already built
}

TEST_CASE("Discover Cure - City of same Disease Color")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).

  Medic jordi{board, City::LosAngeles}; // Los Angeles is Yellow

  CHECK_THROWS(jordi.discover_cure(Color::Yellow)); // Illegal: No RS and no cards
  jordi.take_card(City::Miami).take_card(Bogota).take_card(MexicoCity).take_card(Lima).take_card(Lagos); //pick 5 yellow cards
  CHECK_THROWS(jordi.discover_cure(Color::Yellow)); // Illegal: Still no RS


  jordi.take_card(City::LosAngeles);
  jordi.build();   //building RS using Los Angeles card

  CHECK_NOTHROW(jordi.discover_cure(Color::Yellow)); // Successful
}

TEST_CASE("Discover Cure - City of different Disease Color")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Medic jordi{board, City::Cairo}; // Cairo is Black

  CHECK_THROWS(jordi.discover_cure(Color::Yellow)); // Illegal: No RS and no cards
  jordi.take_card(City::Miami).take_card(Bogota).take_card(MexicoCity).take_card(Lima).take_card(Lagos); //pick 5 yellow cards
  CHECK_THROWS(jordi.discover_cure(Color::Yellow)); // Illegal: Still no RS


  jordi.take_card(City::Cairo);
  jordi.build();   //building RS using Cairo card

  CHECK_NOTHROW(jordi.discover_cure(Color::Yellow)); // Successful
}

TEST_CASE("Discover Cure - Cards not the same color")
{
    Board board;  // Initialize an empty board (with 0 disease cubes in any city).
    Medic jordi{board,City::Madrid}; // Madrid is blue

    jordi.take_card(City::Madrid);
    jordi.build(); // builds a RS at Madrid by using the Madrid card

    //Now let's pick 5 cards of different colors:
    jordi.take_card(City::Miami).take_card(Bogota); //pick 2 yellow cards
    jordi.take_card(City::Karachi); // pick 1 black card
    jordi.take_card(City::Atlanta); // Pick 1 blue card
    jordi.take_card(City::Seoul); // pick 1 red card
    
    CHECK_THROWS(jordi.discover_cure(Color::Blue)); // Illegal since 5 cards aren't the same color
}

TEST_CASE("operator[] overload")
{
  Board board;  // Initialize an empty board (with 0 disease cubes in any city).

  board[City::Kinshasa] = 3;      // put 3 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago

  CHECK(board[City::Kinshasa] == 2);
  CHECK(board[City::MexicoCity] == 3);
  CHECK(board[City::HoChiMinhCity] == 1);
  CHECK(board[City::Chicago] == 1);
}

TEST_CASE("Treat without cure")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city)
  OperationsExpert jordi{board, City::Cairo};

  CHECK_THROWS(jordi.treat(City::Cairo)); // Illegal: level of disease is 0 in Cairo

  board[City::Kinshasa] = 2; // put 2 yellow disease cubes in Kinshasa
  CHECK_THROWS(jordi.treat(City::Kinshasa)); // Illegal since jordi isn't in Kinshasa

  board[City::Cairo]= 3; // put 3 black disease cubes in Cairo
  CHECK_NOTHROW(jordi.treat(City::Cairo)); // Successful
  CHECK(board[City::Cairo] == 1);

  CHECK_NOTHROW(jordi.treat(City::Cairo)); // Successful
  CHECK(board[City::Cairo] == 0);

  CHECK_THROWS(jordi.treat(City::Cairo)); // Illegal since level of disease in Cairo is 0

}

TEST_CASE("Treat with cure")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  OperationsExpert jordi{board, City::Cairo}; // Cairo is Black

  //Before the Cure:
  board[City::Cairo] = 3; // put 3 black disease cubes in Cairo
  CHECK_NOTHROW(jordi.treat(City::Cairo)); // treats disease in Cairo (reduces it by 1)
  CHECK(board[City::Cairo] == 2);


  //After the Cure:
  jordi.take_card(City::Miami).take_card(Bogota).take_card(MexicoCity).take_card(Lima).take_card(Lagos); //pick 5 yellow cards
  jordi.take_card(City::Cairo);
  jordi.build();   //building RS using Cairo card
  CHECK_NOTHROW(jordi.discover_cure(Color::Yellow)); // Successfully found a cure for yellow disease

  CHECK_NOTHROW(jordi.treat(City::Cairo)); // treats disease in Cairo (reduces it by 1 since disease is black)
  CHECK(board[City::Cairo] == 1);

  OperationsExpert sachou{board, City::BuenosAires}; // Buenos Aires is Yellow
  board[City::BuenosAires] = 4; // put 4 yellow disease cubes in Buenos Aires
  CHECK_NOTHROW(sachou.treat(City::BuenosAires));
  CHECK(board[City::BuenosAires] == 0); // Successful
}

TEST_CASE("is Clean")
{
  Board board;  // Initialize an empty board (with 0 disease cubes in any city).

  CHECK(board.is_clean()); // is_clean() returns true

	board[City::Kinshasa] = 3;      // put 3 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago

  CHECK_FALSE(board.is_clean()); // is_clean() returns false
  board.remove_cures(); //Remove all cures
  CHECK(board.is_clean()); // is_clean() returns true

}

TEST_CASE("role()")
{
  Board board;  // Initialize an empty board (with 0 disease cubes in any city).

  OperationsExpert jordi{board, City::Madrid};
  Medic sachou{board, City::Paris};
  Scientist pouch{board, City::LosAngeles, 4};
  Researcher val{board, City::Chicago};
  Virologist nat{board, City::NewYork};
  Dispatcher sara{board, City::Tokyo};
  FieldDoctor vaness{board, City::Sydney};
  GeneSplicer ella{board, City::London};

  CHECK(jordi.role() == "OperationsExpert");
  CHECK(sachou.role() == "Medic");
  CHECK(pouch.role() == "Scientist");
  CHECK(val.role() == "Researcher");
  CHECK(nat.role() == "Virologist");
  CHECK(sara.role() == "Dispatcher");
  CHECK(vaness.role() == "FieldDoctor");
  CHECK(ella.role() == "GeneSplicer");
}

TEST_CASE("Operations Expert")
{
  Board board;  // Initialize an empty board (with 0 disease cubes in any city).
  OperationsExpert jordi {board, City::LosAngeles};
  CHECK_NOTHROW(jordi.build()); // Legal without proper card since role is Operations Expert. Successfully builds RS
}

TEST_CASE("Dispatcher")
{
  Board board;  // Initialize an empty board (with 0 disease cubes in any city).

  //Before building RS
  Dispatcher sara{board, City::Tokyo};
  CHECK_THROWS(sara.fly_direct(City::LosAngeles)); // Illegal, need Los Angeles Card

  //After building RS
  sara.take_card(City::Tokyo);
  sara.build();

  // Success even without card, since sara is a Dispatcher and there is a RS in cureent city (Tokyo)
  CHECK_NOTHROW(sara.fly_direct(City::LosAngeles));  
}

TEST_CASE("Field Doctor")
{
  Board board;  // Initialize an empty board (with 0 disease cubes in any city).

  FieldDoctor vaness{board, City::Sydney};
  OperationsExpert jordi{board, City::Sydney};

  board[City::Jakarta] = 3; // Jakarta is linked to Sydney. Put 3 red disease cubes in Jakarta

  CHECK_THROWS(jordi.treat(Jakarta)); // Illegal since jordi isn't in Jakarta
  CHECK_NOTHROW(vaness.treat(Jakarta)); // Successful since vaness is a FieldDoctor and Jakarta is linked to Sydney
  CHECK(board[City::Jakarta] == 2);
}

TEST_CASE("Gene Splicer")
{
    Board board;  // Initialize an empty board (with 0 disease cubes in any city).
    GeneSplicer jordi{board,City::Madrid}; // Madrid is blue

    jordi.take_card(City::Madrid);
    jordi.build(); // builds a RS at Madrid by using the Madrid card

    //Now let's pick 5 cards of different colors:
    jordi.take_card(City::Miami).take_card(Bogota); //pick 2 yellow cards
    jordi.take_card(City::Karachi); // pick 1 black card
    jordi.take_card(City::Atlanta); // Pick 1 blue card
    jordi.take_card(City::Seoul); // pick 1 red card
    
    CHECK_NOTHROW(jordi.discover_cure(Color::Blue)); // Successful since jordi is a Gene Splicer
}

TEST_CASE("Medic treat")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Medic jordi{board, City::Cairo};

  board[City::Cairo] = 4;  // put 4 black disease cubes in Cairo
  jordi.treat(City::Cairo);

  CHECK(board[City::Cairo] == 0); // True since jordi is a Medic
}

TEST_CASE("Medic drives")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Medic jordi{board, City::LosAngeles};

  board[City::Chicago] = 4;  // put 4 blue disease cubes in Chicago
  jordi.drive(City::Chicago); // Chicago is directly linked to Los Angeles

  CHECK(board[City::Chicago] == 0); // True since jordi is a Medic
}

TEST_CASE("Medic flies directly")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Medic jordi{board, City::LosAngeles};

  board[City::Seoul] = 3; // put 3 red disease cubes in Seoul

  jordi.take_card(City::Seoul);
  jordi.fly_direct(City::Seoul); // directly flies to Seoul using Seoul card

  CHECK(board[City::Seoul] == 0); // True since jordi is a Medic
}

TEST_CASE("Medic flies with charter")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Medic jordi{board, City::LosAngeles};

  board[City::Seoul] = 3; // put 3 red disease cubes in Seoul

  jordi.take_card(City::LosAngeles);
  jordi.fly_charter(City::Seoul); // flies with charter to Seoul using Los Angeles card

  CHECK(board[City::Seoul] == 0); // True since jordi is a Medic
}

TEST_CASE("Medic flies with shuttle")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Medic jordi{board, City::LosAngeles};
  Researcher nat{board, City::Bangkok};


  jordi.take_card(City::LosAngeles);
  jordi.build();  //Building RS in Los Angeles
  nat.take_card(City::Bangkok);
  nat.build();  //Building RS in Bangkok

  board[City::Bangkok] = 3; // put 3 red disease cubes in Bangkok

  jordi.fly_shuttle(City::Bangkok); // flies with shuttle to Bangkok

  CHECK(board[City::Bangkok] == 0); // True since jordi is a Medic
}

TEST_CASE("Creating new Medic in infected City")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  board[City::Bangkok] = 3; // put 3 red disease cubes in Bangkok

  Medic jordi{board, City::Bangkok};

  CHECK(board[City::Bangkok] == 0); // True since jordi is a Medic????????????????
}

TEST_CASE("Researcher")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Researcher jordi{board, City::HongKong};
  
  jordi.take_card(City::Miami).take_card(Bogota).take_card(MexicoCity).take_card(Lima).take_card(Lagos); //pick 5 yellow cards

  CHECK_NOTHROW(jordi.discover_cure(Color::Yellow)); // Successful even if there is no RS since jordi is a Researcher
}

TEST_CASE("Scientist")
{
  Board board; // Initialize an empty board (with 0 disease cubes in any city).
  Scientist jordi{board, City::Taipei, 3}; // 3 means that jordi only need 3 cards of the same color to find a cure
  
  jordi.take_card(City::Miami).take_card(Bogota).take_card(MexicoCity); //pick 3 yellow cards

  CHECK_NOTHROW(jordi.discover_cure(Color::Yellow)); // Successful even if there is no RS since jordi is a Researcher
}

TEST_CASE("Virologist")
{
    Board board; // Initialize an empty board (with 0 disease cubes in any city).
    Virologist sachou{board, City::Lima};

    board[City::Paris] = 3; // put 3 blue disease cubes in Paris
    CHECK_THROWS(sachou.treat(City::Paris)); //Illegal since Paris card is needed

    sachou.take_card(City::Paris);

    // Successfully treats and reduces diseas by one by using the proper card since sachou is a Virologist
    CHECK_NOTHROW(sachou.treat(City::Paris));
    CHECK(board[City::Paris] == 2);

}