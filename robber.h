// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: robber.h
#ifndef ROBBER_H
#define ROBBER_H

#include <iostream>
#include "jewel.h"
using namespace std;
class Robber {
private:
	// member variables
	int ID;
	int coordinate[2]; //(x,y)
	int bag[10] = {0};
	int jewel_indexs[10] = {-1}; // stores the index of each jewel robber found
	bool active;
	bool isGreedy;
	int turns_since_jewel;
	int immobalized; // how many rounds the robber cant move
public:
	// member functions

  //function to set the ID of the robber
  //Pre: robber must exist
  //Post: robber ID is set to the passed in ID
	void setID(const int val);

  //function to get the ID of the robber
  //Pre: robber must have setID
  //Post: returns the ID of the robber
	int getID() const;

  //function to move the robber in a valid direction
  //Pre: robber must be active and must move in a valid direction
  //Post: robber is moved in a valid direction
	string moveRobber(Jewel jewels[]);

  //function to get the x coordinate of the robber
  //Pre: robber must be active and in grid
  //Post: returns the x coordinate of the robber
	int getX() const;

  //function to get the y coordinate of the robber
  //Pre: robber must be active and in grid
  //Post: returns the y coordinate of the robber
	int getY() const;

  //function to pick up the jewel on the square and put it in the robber's bag
  //Pre: robber must be active, jewel must be on the square, and the robber must not be carrying more than 10 jewels
  //Post: the jewel is picked up and added to the robber's bag
	int pickUpLoot(Jewel& jewel);

  //function to set the robber's active status
  //Pre: robbers must exist
  //Post: robber's active status is set to the passed in status
	void setActive(const bool val);

  //function to get the robber's active status
  //pre: robber must exist 
  //post: returns the robber's active status
	bool getActive() const;

  //function to display the robber's ID and the value of jewels in the robber's bag
  //pre: robber must be caught by the police officer ie: police officer must arrest robber
  //post: robber's ID and the value of jewels in the robber's bag are displayed
	void caught();

  //function to get the value of the jewels in the robber's bag
  //pre: robber must be active
  //post: returns the value of the jewels in the robber's bag
	int getBagSum() const;

  //function to get the number of jewels in the robber's bag
  //pre: robber must be active
  //post: returns the number of jewels in the robber's bag
	int getBagCount() const;

  //function to get the jewel at a specific index in the robber's bag and empty/ set to 0
  //pre: bag must have jewels
  //post: each time the function is called, it resets a jewel in the robber's bag to 0, and returns the jewel at the index
	int resetJewel();

  // function that returns the number of gems that havent been found
  //Pre: none
  //Post: int represent number of gems not found
  int getJewelsLeft(Jewel jewels[]);

  // function that returns what direction the jewel is in
  // pre: jewel is active and on the board
  // post: string containing the direction of the jewel is returned
  string findDirectionOfJewel(Jewel& jewel);

  //constructor for Robber
	Robber(const int x, const int y, const bool greedy);
	Robber(){};
};

#endif