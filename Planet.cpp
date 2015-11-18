// Filename: Planet.cpp
// Name: Eliasar Gandara
// Date: 4 November 2015

#include "Planet.h"
#include <cassert>
#include <iostream>

Planet::Planet()
{
	// The defalut constructor will set data's values to empty strings
	this -> clearPlanet();
}

ostream& operator <<(ostream& out, const Planet& planet)
{

	out << "Name: " << planet.data[1] << endl;
	out << "Letter: " << planet.data[2] << endl;
	out << "Discovery Method: " << planet.data[3] << endl;
	out << "Number of Planets: " << planet.data[4] << endl;
	out << "Orbital Period: " << planet.data[5] << endl;
	out << "Mass: " << planet.data[6] << endl;
	out << "Radius: " << planet.data[7] << endl;
	out << "Density: " << planet.data[8] << endl;
	out << "Keplar Flag: " << planet.data[9] << endl;
	out << "Degrees: " << planet.data[10] << endl;
	out << "Distance: " << planet.data[11] << endl;
	out << "Temperature: " << planet.data[12] << endl;
	out << "Stellar Mass: " << planet.data[13] << endl;
	out << "Stellar Radius: " << planet.data[14] << endl;
	out << "Last Update: " << planet.data[15] << endl;

}

void Planet::clearPlanet()
{
	for (int i = 0; i < 16; i++) {
		data[i] = "";
	}
}

void Planet::initPlanet(string info[])
{
	// info[] is an array that contains the data that from the planets.csv file
	// all the data in infor[i] is exactly what should go into data[i] from the planet object
	for (int i = 0; i < 16; i++) {
		data[i] = info[i];
	}
}
