// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: jewel.h
#ifndef JEWEL_H
#define JEWEL_H


#include <iostream>
using namespace std;

class Jewel {
private:
	// member variables
	int value;
	int coordinate[2];
	bool found;
	int ID;
public:
	// member functions 

  // function that sets the value of the jewel
  //Pre: jewels must be in the grid
  //Post: jewel value is set
	void setValue(const int val);

  // function that gets the value of the jewel
  //Pre: Jewel must have a value // must have setValue function called first
  //Post: returns the value of the jewel
	int getValue() const;

  //function that returns true if the jewel has been found, false if not
  //Pre: Jewel must be initialized
  //Post: returns true if the jewel has been found, false if not
	bool getFound() const;

  //function that sets the found status of the jewel
  //Pre: Jewel must be initialized
  //Post: sets the found status of the jewel
	void setFound(const bool val);

  //function that gets the x coordinate of the jewel
  //Pre: Jewel must be initialized and in grid 
  //Post: returns the x coordinate of the jewel
	int getX() const;

  //function that gets the y coordinate of the jewel
  //Pre: Jewel must be initialized and in grid
  //Post: returns the y coordinate of the jewel
	int getY() const;

  //function that gets the ID of the jewel
  //Pre: Jewel must be initialized
  //Post: returns the ID of the jewel
	int getID() const;
  // constructor for Jewel class 
	Jewel(const int x, const int y);
	Jewel(const int x, const int y, const int id);
	Jewel() {};
};


#endif