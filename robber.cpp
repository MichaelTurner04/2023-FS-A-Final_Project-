// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: robber.cpp

//
// Robber class
//
#include "robber.h"
Robber::Robber(const int x, const int y, const bool greedy) {
	static int id = 0;
	id++;
	ID = id;
	coordinate[0] = x;
	coordinate[1] = y;
	isGreedy = greedy;
	active = true;
	immobalized = 0;
	turns_since_jewel = 0;
}

void Robber::setID(const int val) { ID = val; }
int Robber::getID() const { return ID; }

string Robber::moveRobber(Jewel jewels[]) {
	if (immobalized > 0) {
		immobalized--;
		return "NA";
	}
	else {
		turns_since_jewel++;
	}
	if (turns_since_jewel == 5) {
		turns_since_jewel = 0;
		immobalized = 2;
	}

	if (!active) {
		return "NA";
	}


	// bonus pt 1
	int count_of_jewels = getJewelsLeft(jewels);
	if (count_of_jewels) {
		string jewel_indexs = "";
		for (int i = 0; i < 30; i++) {
			if (!jewels[i].getFound()) {
				jewel_indexs += to_string(i);
			}
		}
		// pick random elemtent
		int random_index = rand() % count_of_jewels;
		int rand_index = stoi(jewel_indexs.substr(random_index, 1));

		// return direction of jewel
		string direction = findDirectionOfJewel(jewels[rand_index]);
		if (direction == "NW") {        // North West
			coordinate[0] -= 1;     // x coordinate
			coordinate[1] -= 1;     // y coordinate
		} else if (direction == "N") { // North
			coordinate[1] -= 1;     // y coordinate
		} else if (direction == "NE") { // North East
			coordinate[0] += 1;     // x coordinate
			coordinate[1] -= 1;     // y coordinate
		} else if (direction == "W") { // West
			coordinate[0] -= 1;     // x coordinate
		} else if (direction == "E") { // East
			coordinate[0] += 1;     // x coordinate
		} else if (direction == "SW") { // Southwest
			coordinate[0] -= 1;     // x coordinate
			coordinate[1] += 1;     // y coordinate
		} else if (direction == "S") { // South
			coordinate[1] += 1;     // y coordinate
		} else if (direction == "SE") { // Southeast
			coordinate[0] += 1;     // x coordinate
			coordinate[1] += 1;     // y coordinate
		}
		return direction;

	}


	string possibilities = "";
	bool x_small = false;
	bool x_big = false;
	bool y_small = false;
	bool y_big = false;
  
	// determin if its on any edges
	if (coordinate[0] == 0) {
		x_small = true;
	} else if (coordinate[0] == 6) {
		x_big = true;
	}
	if (coordinate[1] == 0) {
		y_small = true;
	} else if (coordinate[1] == 6) {
		y_big = true;
	}

	// add top row to posible directions
	if (!(x_small || y_small || x_big)) {
		possibilities += "012";
	} else if (!(x_small || y_small)) {
		possibilities += "01";
	} else if (!(y_small || x_big)) {
		possibilities += "12";
	}

	// add left and right
	if (!x_small) {
		possibilities += "3";
	}
	if (!x_big) {
		possibilities += "4";
	}

	// add bottom row
	if (!(x_small || y_big || x_big)) {
		possibilities += "567";
	} else if (!(x_small || y_big)) {
		possibilities += "56";
	} else if (!(y_big || x_big)) {
		possibilities += "67";
	}
	int length_of_poss = possibilities.length();
	int random_index = rand() % length_of_poss;
	int random = stoi(possibilities.substr(random_index, 1));
	if (random == 0) {        // North West
		coordinate[0] -= 1;     // x coordinate
		coordinate[1] -= 1;     // y coordinate
		return "NW";
	} else if (random == 1) { // North
		coordinate[1] -= 1;     // y coordinate
		return "N";
	} else if (random == 2) { // North East
		coordinate[0] += 1;     // x coordinate
		coordinate[1] -= 1;     // y coordinate
		return "NE";
	} else if (random == 3) { // West
		coordinate[0] -= 1;     // x coordinate
		return "W";
	} else if (random == 4) { // East
		coordinate[0] += 1;     // x coordinate
		return "E";
	} else if (random == 5) { // Southwest
		coordinate[0] -= 1;     // x coordinate
		coordinate[1] += 1;     // y coordinate
		return "SW";
	} else if (random == 6) { // South
		coordinate[1] += 1;     // y coordinate
		return "S";
	} else if (random == 7) { // Southeast
		coordinate[0] += 1;     // x coordinate
		coordinate[1] += 1;     // y coordinate
		return "SE";
	}
	return "NA";
}

int Robber::getX() const {
	return coordinate[0];
}
int Robber::getY() const {
	return coordinate[1];
}

int Robber::pickUpLoot(Jewel& jewel) {
	for (int i = 0; i < 10; i++) {
		if (bag[i] == 0) {
			bag[i] = jewel.getValue();
			jewel.setFound(true);
			jewel_indexs[i] = jewel.getID();
			return bag[i]; // returns value of jewel
		}
	}
	return 0;
}
void Robber::setActive(const bool val) { active = val; }
bool Robber::getActive() const { return active; }
void Robber::caught() {

	cout << "Robber " << ID << " has been caught!" << endl;
	cout << "Robber " << ID << " has " << getBagSum() << "$ jewels worth" << endl;
	active = false;
	for (int i = 0; i < 10; i++) {
		bag[i] = 0;
	}
}
int Robber::getBagSum() const {
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		sum += bag[i];
	}
	return sum;
}

int Robber::getBagCount() const {
	int count = 0;
	for (int i = 0; i < 10; i++) {
		if (bag[i] != 0) {
			count++;
		}
	}
	return count;
}

int Robber::resetJewel() {
	for (int i = 9; i >= 0; i--) {
		if (bag[i] != 0) { // set index and bag to 0 its time to remove jewl
			bag[i] = 0;
			int temp = jewel_indexs[i];
			jewel_indexs[i] = 0;
			return temp;
		}
	}
	return -1;
}

int Robber::getJewelsLeft(Jewel jewels[]) {
	int count = 0; // number of gems
	for (int i = 0; i < 30; i++) {
		if (!jewels[i].getFound()) {
			count++;
		}
	}
	return count;
}

string Robber::findDirectionOfJewel(Jewel& jewel) {
	double slope = static_cast<double>(coordinate[1] - jewel.getY()) / (coordinate[0] - jewel.getX()); // slope
	// robber is left of jewel
	// slope > 2 = N
	// .5 < slope < 2 = NE
	// -.5 < slope <  .5 = E
	// -2 < slope < -.5 = SE
	// slope < -2 = S
	
	if (jewel.getX() - coordinate[0] == 0){
		if (jewel.getY() - coordinate[1] > 0) {
			return "S";
		}
		else if (jewel.getY() - coordinate[1] < 0) {
			return "N";
		}
	}
	
	if ((jewel.getX() - coordinate[0]) >= 0) { // if robber is on the left of the jewel
		if (slope > 2) {
			return "S";
		}
		else if (slope > .5) {
			return "SE";
		}
		else if (slope > -.5) {
			return "E";
		}
		else if (slope > -2) {
			return "NE";
		}
		else {
			return "N";
		}
	}
	else { // if robber is on the right of the jewel
		slope = slope*-1;
		if (slope > 2) {
			return "S";
		}
		else if (slope > .5) {
			return "SW";
		}
		else if (slope > -.5) {
			return "W";
		}
		else if (slope > -2) {
			return "NW";
		}
		else {
			return "N";
		}
	}
}
