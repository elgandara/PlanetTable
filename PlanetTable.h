// Filename: PlanetTable.h
// Name: Eliasar Gandara
// Date: 3 November 2015

#ifndef PLANET_TABLE_H
#define PLANET_TABLE_H

#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "Table.h"
#include "Planet.h"
using namespace std;

struct PlanetRecord {
	Planet planet;
	int nextDiscoveryIndex;
	int nextPlanetNumIndex;
	int nextTemperatureIndex;
	int nextNameIndex;
};

class PlanetTable
{
 public:

	// Constructor
	typedef vector<PlanetRecord> Planets;
	PlanetTable();

	// Search for planets that have a discovery method equivalent to value
	void searchByDiscoveryMethod(string key);
	// Search for planets that have the same number of planets as value
	void searchByNumberOfPlanets(string key);
	// Search for planets that have a matching temperature with the passed in value
	void searchByTemperature(string key);

	// Searches for planets that matched the passed in name
	void searchByName(string key);

	// Reads the planet.csv file that contains the data on the planets
	void readPlanetFile();

	PlanetRecord& operator [] (int index);

 private:
	Table discoveryTable;
	Table numberTable;
	Table temperatureTable;
	Table nameTable;
	Planets planets;

	// Private Member Functions
	void updateDiscoveryTable(RecordType& record, string discoveryMethod, int index);
	void updateNumberTable(RecordType& record, string numPlanets, int index);
	void updateTemperatureTable(RecordType& record, string temperature, int index);
	void updateNameTable(RecordType& record, string planetName, int index);
};

ostream& operator <<(ostream& out, const PlanetRecord record);

#endif
