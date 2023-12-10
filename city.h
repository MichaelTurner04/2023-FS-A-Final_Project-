// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: city.h
#ifndef CITY_H
#define CITY_H

#include <iostream>
#include "robber.h"
#include "police.h"
#include "jewel.h"

using namespace std;



class City {
private:
	// member variables
	char city_grid[7][7]; //(x,y)
	int current_count;    // number of gems on the city grid
	Robber robbers[4];
	Police police[2];
	Jewel jewels[30];

public:
	// member functions

  //function that gets the current count of jewels in the grid
  //Pre: jewels must exist in grid
  //Post: returns the current count of jewels in the grid
	int getcurrent_count() const;

  //funciton that sets the cuurent count of jewels in the grid
  //Pre: jewels must exist in grid
  //post: updates current count of jewels in the grid
	void setcurrent_count(const int val);

  //funciton takes the scattered jewels, robbers, and police and dispays the grid
  //Pre: jewels, robbers, and police must exist/ have coordinates
  //Post: displays the grid with the jewels, robbers, and police
	void display_grid();

  //funciton that lets each robber and police officer have a turn to move on the grid and check for jewels caught by each robber and checks if each robber was caught by a police officer 
  //Pre: jewels must exist in grid
  //post: updates the value of the coordinate for robbers and police and returns bool if the game is still going
	bool turn();

  //function that prints the summary of the chase for each rober and police officer
  //Pre: game must be over, police and robbers must exist
  //post: prints the summary of the chase for each robber and police officer
	void summary(string winner_and_reason);

  //function that returns the index of jewel that is at the same coordinate as that robber, and if no jewel then returns -1
  //Pre: robbers coordinates must exist and jewels coordinates must exist
  //Post: returns index of jewel that robber is on, if no jewel, returns -1
	int robber_with_jewel(int robber_num); 

  //function that returns the index of jewel that is at the same coordinate as that police officer, and if no jewel then returns -1
  //Pre: police coordinates must exist and jewels coordinates must exist
  //Post: returns index of jewel that police is on, if no jewel, returns -1
	int police_with_jewel(int police_num); 

  //function that gets the policeman's number for which caught the robber
  //Pre: robber must exist, police must exist
  //Post: // param is which police officer (0 or 1), returns index of robber its with, otherwise -1
	void police_with_robber(int police_num);

  //function that gets the robber's number for which was caught by the police officer 
  //Pre: robber must exist, police must exist
  //Post: // param is which robber (0-3), returns index of police officer its with, otherwise -1
	void robber_with_police(int robber_num);

  //function that compares the coordinates of each robber with each other
  //Pre: robbers must exist
  //returns true if robber in square of another robber, false if not
	bool robber_with_robber(int robber_num); 

  //function that if police officers are on the same square they share they're confiscated loot 
  //Pre: police must have same coordinates as each other
  //Post: adds the total loot of each officer together and splits in half for each officer//distribute equally
	void police_with_police();

  //function that if a greedy robber bumps into another active robber, they lose half of their loot and the jewels are redistributed back to their original location.
  //Pre: must be a greedy robber, must be active robber, must be on the same square as another active robber
  //Post:  greedy robber loses half of their loot and jewels are redistributed back to their original location
	void robber_drops_jewels(int robber_num);

  //function that finds an open space on the grid to redistribute the jewels in robber_drops_jewels
  //Pre: none, but used with robber_drops_jewels to find open space on play grid 
  //Post: returns true if open space is found, false if not
	bool open_space(int x, int y);

	City();
};

#endif