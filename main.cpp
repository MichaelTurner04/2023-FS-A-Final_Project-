// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: main.cpp
#include <iostream>
#include "city.h"
using namespace std;

int main() {
	srand(100); // required seed for assingment
	City city;
	bool playing = true;
		while(playing){
			playing = city.turn();
		}
}