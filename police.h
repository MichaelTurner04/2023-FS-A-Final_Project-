// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: police.h
#ifndef POLICE_H
#define POLICE_H

#include <iostream>
using namespace std;

#include "robber.h"

class Police {
private:
	// member variables
	int coordinate[2]; //(x,y)
	int ID;
	int loot_confiscated;
	int robbers_caught;

public:
	// member functions

  //function to set the ID of police
  //pre: police must exist
  //post: police ID is set
	void setID(const int val);

  //function to return police ID
  //pre: police must have id// setID must be called first
  //post: returns police ID
	int getID() const;

  //function to get the x coordinate of the police officer
  //pre: police must exist and be in grid
  //post: returns x coordinate of police officer
	int getX() const;

  //function to get the y coordinate of the police officer
  //pre: police must exist and be in grid
  //post: returns y coordinate of police officer
	int getY() const;

  //function to get the number of loot confiscated by the police officer from the robber
  //pre: police will need to have confiscated loot from the robbers to work as intended
  //post: returns the number of loot confiscated by the police officer
	int get_loot_confiscated() const;

  //function to get the number of robbers caught by the police officer
  //pre: police and robber need to be on the same spot
  //post: returns the number of robbers caught by the police officer
	int get_robbers_caught() const;

  //function to set the loot confiscated by the police officer from the robber
  //pre: police and robber need to be on the same spot
  //post: sets the number of loot confiscated by the police officer
	void set_loot_confiscated(const int val);

  //function to move the police officer in a valid direction
  //pre: police must exist and be in grid, must move in a valid direction
  //post: police officer is moved in a valid direction
	void move(string direction);

  //function to arrest a robber and deactivate the robber(Robber::setActive), confiscate its loot(police::set_loot_confiscated),  and increment robbers caught 
  //pre: police and robber must be on the same spot to call this function
  //post: robber is deactivated and loot is confiscated by police officer
	void arrest(Robber& robber);
  // constructor for police officer
	Police(const int x, const int y);
	Police(){};
};

#endif