// Programers: Michael Turner, Colin Smith
// GitHub User: mjt6yf, cashpg
// Date: 12/8/2023
// Assignment: Final Project
// File name: jewel.cpp

//
// Jewel Class
//
#include "jewel.h"
Jewel::Jewel(const int x, const int y) {
	static int id = -1;
	id++;
	ID = id;
	value = x+y;
	value *= value;
	coordinate[0] = x;
	coordinate[1] = y;
	found = false;
}

Jewel::Jewel(const int x, const int y, const int id) {
	ID = id;
	value = x+y;
	value *= value;
	coordinate[0] = x;
	coordinate[1] = y;
	found = false;
}


bool Jewel::getFound() const {
	return found;
}

void Jewel::setFound(const bool val) {
	found = val;
}

int Jewel::getX() const {
	return coordinate[0];
}

int Jewel::getY() const {
	return coordinate[1];
}

int Jewel::getID() const {
	return ID;
}


void Jewel::setValue(const int val) { value = val; }
int Jewel::getValue() const { return value; }