// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: police.cpp

//
// Police Class
//
#include "police.h"
Police::Police(const int x, const int y) {
	static int id = 0;
	id++;
	ID = id;
	coordinate[0] = x;
	coordinate[1] = y;
	robbers_caught = 0;
}

int Police::getX() const {
	return coordinate[0];
}

int Police::getY() const {
	return coordinate[1];
}


void Police::setID(const int val) { ID = val; }
int Police::getID()   const { return ID; }
void Police::move(string direction) {
	if (direction == "NW" && (coordinate[0] != 0 && coordinate[1] != 0)) {        // North West
		coordinate[0] -= 1;     // x coordinate
		coordinate[1] -= 1;     // y coordinate
	} else if (direction == "N" && (coordinate[1] != 0)) { // North
		coordinate[1] -= 1;     // y coordinate
	} else if (direction == "NE" && (coordinate[0] != 6 && coordinate[1] != 0)) { // North East
		coordinate[0] += 1;     // x coordinate
		coordinate[1] -= 1;     // y coordinate
	} else if (direction == "W" && (coordinate[0] != 0)) { // West
		coordinate[0] -= 1;     // x coordinate
	} else if (direction == "E" && (coordinate[0] != 6)) { // East
		coordinate[0] += 1;     // x coordinate
	} else if (direction == "SW" && (coordinate[0] != 0 && coordinate[1] != 6)) { // Southwest
		coordinate[0] -= 1;     // x coordinate
		coordinate[1] += 1;     // y coordinate
	} else if (direction == "S" && (coordinate[1] != 6)) { // South
		coordinate[1] += 1;     // y coordinate
	} else if (direction == "SE" && (coordinate[0] != 6 && coordinate[1] != 6)) { // Southeast
		coordinate[0] += 1;     // x coordinate
		coordinate[1] += 1;     // y coordinate
	}
}
void Police::arrest(Robber& robber) {
	robber.setActive(false);
	loot_confiscated += robber.getBagSum();
	robbers_caught++;
	robber.caught();
}

int Police::get_loot_confiscated() const {
	return loot_confiscated;
}

void Police::set_loot_confiscated(const int val) {
	loot_confiscated = val;
}

int Police::get_robbers_caught() const {
	return robbers_caught;
}
