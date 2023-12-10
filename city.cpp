// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: city.cpp
#include "city.h"
//
// City Class
//
City::City() {
	// randomly scatter jewels
	for (int i = 0; i < 30; i++) { // for each jewel
		int x;
		int y;
		do { // while the current vals arent available, make new ones
			x = rand() % 7;
			y = rand() % 7;
		} while (city_grid[x][y] == 'J');

		jewels[i] = Jewel(x, y);
		city_grid[x][y] = 'J';
		//cout << "Jewel " << i << " created at (" << y << ", " << x << ")" << endl;
	}

	// initialize robbers
	int used_x_cords[5];
	int used_y_cords[5];
		for (int i = 0; i < 4; i++) {
		bool same = false;
		// get random coordinates that havent been used
		int x = rand() % 7;
		int y = rand() % 7;
		for (int j = 0; j < i; j++) {
			if (x == used_x_cords[j] && y == used_y_cords[j]) {
				same = true;
			}
		}
		for (int j = 0; j < 30; j++) {
			if (jewels[j].getX() == x && jewels[j].getY() == y) {
				same = true;
			}
		}
		while (same) { // if its the same as a previous robber
			same = false;
			x = rand() % 7;
			y = rand() % 7;
			for (int j = 0; j < i; j++) {
				if (x == used_x_cords[j] && y == used_y_cords[j]) {
					same = true;
				}
			}
			for (int j = 0; j < 30; j++) {
				if (jewels[j].getX() == x && jewels[j].getY() == y) {
					same = true;
				}
			}
		}
		used_x_cords[i] = x;
		used_y_cords[i] = y;
		bool greedy = true;
		if (i > 1) {
			greedy = false;
		}
		robbers[i] = Robber(x, y, greedy);
			//cout << "Robber " << i << " created at (" << y << ", " << x << ")" << endl;
	}
	// initialize cops
		for (int i = 0; i < 2; i++) {
		bool same = false;
		// get random coordinates that havent been used
		int x = rand() % 7;
		int y = rand() % 7;
		for (int j = 0; j < i + 4; j++) {
			if (x == used_x_cords[j] && y == used_y_cords[j]) {
				same = true;
			}
		}
		for (int j = 0; j < 30; j++) {
			if (jewels[j].getX() == x && jewels[j].getY() == y) {
				same = true;
			}
		}
		while (same) { // if its the same as a previous robber
			same = false;

			x = rand() % 7;
			y = rand() % 7;
			for (int j = 0; j < i; j++) {
				if (x == used_x_cords[j] && y == used_y_cords[j]) {
					same = true;
				}
			}
			for (int j = 0; j < 30; j++) {
				if (jewels[j].getX() == x && jewels[j].getY() == y) {
					same = true;
				}
			}
		}
		used_x_cords[i + 4] = x;
		used_y_cords[i + 4] = y;
		police[i] = Police(x, y);
	}
	// display the starting grid
	display_grid();
}
void City::setcurrent_count(const int val) { current_count = val; }
int City::getcurrent_count() const {
	cout << "Current count: " << current_count << endl;
	return current_count;
}

void City::display_grid() {
	// reset grid

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			city_grid[i][j] = '.';
		}
	}

	// display jewls
	for (int i = 0; i < 30; i++) {
		if (!jewels[i].getFound()) {
			city_grid[jewels[i].getX()][jewels[i].getY()] = 'J';
		}
		else {
			city_grid[jewels[i].getX()][jewels[i].getY()] = '.';
		}
	}

	/*for (int i = 0; i < 2; i++) {
		cout << police[i].getX() << " " << police[i].getY() << endl;
		city_grid[police[i].getX()][police[i].getY()] = 'P';
	}*/

	// display robber
	for (int i = 0; i < 4; i++) {
		if (robbers[i].getActive()) {
			city_grid[robbers[i].getX()][robbers[i].getY()] = 'r'; //single robber on square
			for (int j = 0; j < 4; j++) {
				if (j != i) { // make sure they are not the same robber
					if (robbers[j].getX() == robbers[i].getX() && robbers[j].getY() == robbers[i].getY()) {
						city_grid[robbers[i].getX()][robbers[i].getY()] = 'R'; //If 2 robbers are on same square then capital "R"
					}
					else {
						city_grid[robbers[i].getX()][robbers[i].getY()] = 'r';
					}
					
				}
			}
		}
		else {
			city_grid[robbers[i].getX()][robbers[i].getY()] = 'A';
		}
	}
    //display police
    for (int i = 0; i < 2; i++) {
		if (city_grid[police[i].getX()][police[i].getY()] != '.') {
			city_grid[police[i].getX()][police[i].getY()] = 'P';
		}
		else {
			city_grid[police[i].getX()][police[i].getY()] = 'p';
		}
	}

	// print the grid
	cout << "The City:" << endl;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			cout << city_grid[i][j] << " ";
		}
		cout << endl;
	}

}

bool City::turn() {
	string direction[2];

	// done - if robbers moved 5 turns (including current) without finding jewels, they are imoblized 2 rounds 
	direction[0] = robbers[0].moveRobber(jewels); // normal robbers
	robber_with_police(0); // checks if robber is with the police

	// pick up jewel if thers a jewel
	int jewel_index = robber_with_jewel(0);
	if (jewel_index > -1) {
		robbers[0].pickUpLoot(jewels[jewel_index]);
	}

	direction[1] = robbers[1].moveRobber(jewels); 
	robber_with_police(1); // checks if robber is with the police
	jewel_index = robber_with_jewel(1);
	if (jewel_index > -1) {
		robbers[1].pickUpLoot(jewels[jewel_index]);
	}


	// * while robber finds loot of even value or max of 3 times (greedy)
	int count = 0; // how many times robber moved
	int picked_jewel_val; // value of the jewel robber picked up
	do {
		robbers[2].moveRobber(jewels); // greedy robbers
		robber_with_police(0); // checks if robber is with the police
		robber_with_robber(2);

		jewel_index = robber_with_jewel(2); // index of jewel if robber landed on jewel

		if (jewel_index > -1) {
			picked_jewel_val = robbers[2].pickUpLoot(jewels[jewel_index]);
		}
		else {
			picked_jewel_val = -1; // if jewel isnt found
		}
		count++;

	} while (count <= 3 && picked_jewel_val % 2 == 0);
	// pick up jewels



	// * while robber finds loot of even value or max of 3 times (greedy)
	count = 0; // how many times robber moved
	picked_jewel_val = -1; // value of the jewel robber picked up
	do {
		robbers[3].moveRobber(jewels); // greedy robbers
		robber_with_police(0); // checks if robber is with the police
		robber_with_robber(3);

		jewel_index = robber_with_jewel(3); // index of jewel if robber landed on jewel

		if (jewel_index > -1) {
			picked_jewel_val = robbers[3].pickUpLoot(jewels[jewel_index]);
		}
		else {
			picked_jewel_val = -1; // if jewel isnt found
		}
		count++;

	} while (count <= 3 && picked_jewel_val % 2 == 0);


	int p1 = rand() % 2; // choice for which robber it should follow
	int p2 = rand() % 2; // choice for which robber police 2 should follow

	// TODO: fix if robbers dont move from inactive police movement 
	police[0].move(direction[p1]); // randomly move the cop in the same direction as one of the normal robbers
	police_with_robber(0); // checks if police landed on robbers square
	police_with_jewel(0); // police find jewels, collect but dont report

	police[1].move(direction[p2]); // randomly move the cop in the same direction as one of the normal robbers
	police_with_robber(1); // checks if police landed on robbers square
	police_with_jewel(1); // police find jewels, collect but dont report





	// end of turn TODO: add if robbers get enoguh wealth
	display_grid();

	static int round_count = 0;
		round_count++;
	int total_bag_sum = 0;
	int robbers_active = 0;
	for (int i = 0; i < 4; i++) {
		total_bag_sum += robbers[i].getBagSum();
		if (!robbers[i].getActive()) {
			robbers_active++;
		}
	}

		if (round_count > 49) {
		summary("Robbers win from maxiumum number of turns (50).");
			return false;
	}
	else if (total_bag_sum >= 2023) {
		summary("Robbers win from reaching $2023 in Jewels."); //? release robbers what does that mean ? 
		return false;
	}
	else if (robbers_active == 4) {
		summary("Police win for catching all the robbers.");
		return false;
	}




	return  true; // value for if the game should continue
}

int City::robber_with_jewel(int robber_num) {
	for (int i = 0; i < 30; i++) {
		if ( !jewels[i].getFound() && (robbers[robber_num].getX() == jewels[i].getX() && robbers[robber_num].getY() == jewels[i].getY())) { // if jewel hasnt been found and is in the same location
			return i;
		}
	}
	return -1;
}


int City::police_with_jewel(int police_num) {
	for (int i = 0; i < 30; i++) {
		if ( !jewels[i].getFound() && (police[police_num].getX() == jewels[i].getX() && police[police_num].getY() == jewels[i].getY())) { // if jewel hasnt been found and is in the same location
			jewels[i].setFound(true);
			return i;
		}
	}
	return -1;
}

void City::police_with_robber(int police_num) {
	for (int i = 0; i < 4; i++) {
		if (robbers[i].getActive() && police[police_num].getX() == robbers[i].getX() && police[police_num].getY() == robbers[i].getY()) {
			police[police_num].arrest(robbers[i]);
		}
	}
}

void City::robber_with_police(int robber_num) {
	for (int i = 0; i < 2; i++) {
		if (robbers[robber_num].getActive() && robbers[robber_num].getX() == police[i].getX() && robbers[robber_num].getY() == police[i].getY()) {
			police[i].arrest(robbers[robber_num]);
		}
	}
}

bool City::robber_with_robber(int robber_num) {
	for (int i = 0; i < 4; i++) {
		if (i != robber_num) { // make sure they arenet the same robber
			if (robbers[i].getX() == robbers[robber_num].getX() && robbers[i].getY() == robbers[robber_num].getY()) {
				return true;
			}
		}
	}
	return false;
}

void City::police_with_police() {
	if (police[0].getX() == police[1].getX() && police[0].getY() == police[1].getY()) {
		// redistribute wealth
		int total = police[1].get_loot_confiscated() + police[2].get_loot_confiscated();
		if (total % 2 == 0) {
			police[0].set_loot_confiscated(total/2);
			police[1].set_loot_confiscated(total/2);
		}
		else {
			police[0].set_loot_confiscated(total/2);
			police[1].set_loot_confiscated(total/2 + 1);
		}
	}
}

bool City::open_space(int x, int y) {
	for (int i = 0; i < 30; i++) {
		if (x == jewels[i].getX() && y == jewels[i].getY()) { // if a jewel is already there
			return false;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (x == robbers[i].getX() && y == robbers[i].getY()) { // if a robber is there
			return false;
		}
	}

	for (int i = 0; i < 2; i++) {
		if (x == police[i].getX() && y == police[i].getY()) {
			return false;
		}
	}

	return true;
}

// friend function
void City::robber_drops_jewels(int robber_num) {
	int jewel_count = robbers[robber_num].getBagCount(); // how many jewels they have
	for (int i = 0; i < jewel_count/2; i++) {
		int jewel_index = robbers[robber_num].resetJewel(); // jewel to reset

		int cur_x = jewels[jewel_index].getX();
		int cur_y = jewels[jewel_index].getY();

		jewels[jewel_index] = Jewel();

		while (!open_space(cur_x, cur_y)) {
			cur_x = rand() % 7;
			cur_y = rand() % 7;
		}

		jewels[jewel_index] = Jewel(cur_x, cur_y, jewel_index);
	}
}


void City::summary(string winner_and_reason) {
	cout << "SUMMARY OF THE CHASE: " << endl;
	cout << winner_and_reason << endl;
	for (int i = 0; i < 2; i++) { // display police
		cout << "Police id: " << police[i].getID() << endl;
		cout << "\tConfiscated jewels amount: $" << police[i].get_loot_confiscated() << endl;
		cout << "\tFinal number of robbers caught: " << police[i].get_robbers_caught() << endl;
	}
	for (int i = 0; i < 4; i++) { // display robbers
		if (i < 2) {
			cout << "Ordinary Robber id: " << robbers[i].getID() << endl;
		}
		else {
			cout << "Greedy Robber id: " << robbers[i].getID() << endl;
		}
		cout << "\tFinal number of jewels picked up: " << robbers[i].getBagCount() << endl;
		cout << "\tTotal jewel worth: $" << robbers[i].getBagSum() << endl;
	}
}
