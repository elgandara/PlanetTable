// Filename: PlanetTable.cpp
// Name: Eliasar Gandara
// Date: 4 November 2015

#include "PlanetTable.h"
#include "Table.h"
#include "Planet.h"
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iostream>

PlanetTable::PlanetTable()
{

}

void PlanetTable::searchByDiscoveryMethod(string key)
{
	// index is the first planet that has a discovery method with a value of key
	int index = discoveryTable[key].data.first;

	// If the index is negative, then no matching planets were found
	// A message will be displayed to tell the user that there are no matchin planets
	if (index < 0) {
		cout << "No matching planets" << endl;
	}

	// While there is still planets in the chain with the matching value,
	// they will be displayed on the screen
	while (index >= 0) {
		cout << planets[index].planet << endl;
		index = planets[index].nextDiscoveryIndex;
	}

}

void PlanetTable::searchByNumberOfPlanets(string key)
{
	int index = numberTable[key].data.first;

	if (index < 0) {
		cout << "No matching planets" << endl;
	}

	while (index >= 0) {
		cout << planets[index].planet << endl;
		index = planets[index].nextPlanetNumIndex;
	}
}

void PlanetTable::searchByTemperature(string key)
{
	int index = temperatureTable[key].data.first;

	if (index < 0) {
		cout << "No matching planets" << endl;
	}

	while (index >= 0) {
		cout << planets[index].planet << endl;
		index = planets[index].nextTemperatureIndex;
	}
}

void PlanetTable::searchByName(string key)
{
	int index = nameTable[key].data.first;

	if (index < 0) {
		cout << "No matching planets" << endl;
	}

	while (index >= 0) {
		cout << planets[index].planet << endl;
		index = planets[index].nextNameIndex;
	}
}

PlanetRecord& PlanetTable::operator [] (int index)
{
	assert(index >= 0 && index < planets.size());
	return planets[index];
}

void PlanetTable::readPlanetFile()
{
	int columns = 16;
	fstream fin;


	fin.open("planets.csv");

	if (fin.fail()) {
		cout << "Error opening file." << endl;
		exit(0);
	}
	else {

		string line;
		string info[16];
		int arr_index;
		int vector_index = 0;
		Planet planet;

		while (getline(fin, line)) {

			if (line[0] != '#' && isdigit(line[0])) {
				// Extract the information from the line and place it in the corresponding array position
				arr_index = 0;
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == ',') {
						arr_index++;
					}
					else {
						info[arr_index] += line[i];
					}
				}

				// Initialize the planet object with the planet data from info[]
				planet.initPlanet(info);

				// Create the record that will be contain the planet and the indexes to the next planet
				// with a matchin index
				PlanetRecord planetRecord;
				planetRecord.planet = planet;
				planetRecord.nextDiscoveryIndex = -1;
				planetRecord.nextPlanetNumIndex = -1;
				planetRecord.nextTemperatureIndex = -1;
				planetRecord.nextNameIndex = -1;

				// Creat a RecordType to store into the corresponding Table or update the existing values
				RecordType tempRecord;
				string discoveryMethod = planet.getDiscoveryMethod();
				string numPlanets = planet.getNumPlanets();
				string temperature = planet.getTemperature();
				string planetName = planet.getHostName() + " " + planet.getPlanetLetter();

				// Get the pair with the matching values for the search value and update the values
				tempRecord = discoveryTable[discoveryMethod];
				updateDiscoveryTable(tempRecord, discoveryMethod, vector_index);

				tempRecord = numberTable[numPlanets];
				updateNumberTable(tempRecord, numPlanets, vector_index);

				tempRecord = temperatureTable[temperature];
				updateTemperatureTable(tempRecord, temperature, vector_index);

				tempRecord = nameTable[planetName];
				updateNameTable(tempRecord, planetName, vector_index);

				// Insert the planet record into the vector at the next available position
				planets.insert(planets.begin() + vector_index, planetRecord);
				vector_index++;

				// This will set all values in info[] to the defalut value of ""
				for (int i = 0; i < columns; i++) {
					info[i] = "";
				}

				// Reset the values inside of the temporary planet object
				planet.clearPlanet();

			}
		}

	}

	fin.close();
}

// Will update the discovery table
void PlanetTable::updateDiscoveryTable(RecordType& record, string discoveryMethod, int index)
{
	// If the discovery method does not exist
	if (record.int_key < 0) {
		RecordType discoveryRecord;

		// Set the key to the discovery method and generate an int_key
		discoveryRecord.key = discoveryMethod;
		discoveryRecord.int_key = generateIntKey(discoveryRecord.key);

		// Since the record is the first one being entered,
		// the first and last index will be equivalent to the current vector_index
		discoveryRecord.data.first = index;
		discoveryRecord.data.second = index;

		// Insert the new record into the discovery table
		discoveryTable.insert(discoveryRecord);
	}
	// If the discovery method already exists, the values in the table will be updated
	else {
		// lastRecordIndex is the index of the last planet that had the specified discoveryMethod
		int lastRecordIndex = record.data.second;
		planets[lastRecordIndex].nextDiscoveryIndex = index;

		// Update the last record index of the record for the specified discovery method and reenter it into the table
		record.data.second = index;
		discoveryTable.update(record);
	}
}

void PlanetTable::updateNumberTable(RecordType& record, string numPlanets, int index)
{
	// If the numPlanets value is not in the numberTable, then it will be inserted
	if (record.int_key < 0) {
		RecordType numberRecord;

		// Set the key to the number of planets and generate an int_key
		numberRecord.key = numPlanets;
		numberRecord.int_key = generateIntKey(numberRecord.key);

		// First and second will be equivalent to the current index
		// since this is the first record with this key being entered
		numberRecord.data.first = index;
		numberRecord.data.second = index;

		numberTable.insert(numberRecord);
	}
	// If the number of planets already exits, the indexes in the table will be updated
	else {
		// lastRecordIndex is the index of the last planet that had the specified numPlanets
		int lastRecordIndex = record.data.second;
		planets[lastRecordIndex].nextPlanetNumIndex = index;

		// Update the last record index for the record and the reenter it into the table
		record.data.second = index;
		numberTable.update(record);
	}
}

void PlanetTable::updateTemperatureTable(RecordType& record, string temperature, int index)
{
	// If the numPlanets value is not in the numberTable, then it will be inserted
	if (record.int_key < 0) {
		RecordType temperatureRecord;

		// Set the key to the number of planets and generate an int_key
		temperatureRecord.key = temperature;
		temperatureRecord.int_key = generateIntKey(temperatureRecord.key);

		// First and second will be equivalent to the current index
		// since this is the first record with this key being entered
		temperatureRecord.data.first = index;
		temperatureRecord.data.second = index;

		temperatureTable.insert(temperatureRecord);
	}
	// If the number of planets already exits, the indexes in the table will be updated
	else {
		// lastRecordIndex is the index of the last planet that had the specified numPlanets
		int lastRecordIndex = record.data.second;
		planets[lastRecordIndex].nextTemperatureIndex = index;

		// Update the last record index for the record and the reenter it into the table
		record.data.second = index;
		temperatureTable.update(record);
	}
}

void PlanetTable::updateNameTable(RecordType& record, string planetName, int index)
{
	// If the numPlanets value is not in the numberTable, then it will be inserted
	if (record.int_key < 0) {
		RecordType nameRecord;

		// Set the key to the number of planets and generate an int_key
		nameRecord.key = planetName;
		nameRecord.int_key = generateIntKey(nameRecord.key);

		// First and second will be equivalent to the current index
		// since this is the first record with this key being entered
		nameRecord.data.first = index;
		nameRecord.data.second = index;

		nameTable.insert(nameRecord);
	}
	// If the number of planets already exits, the indexes in the table will be updated
	else {
		// lastRecordIndex is the index of the last planet that had the specified numPlanets
		int lastRecordIndex = record.data.second;
		planets[lastRecordIndex].nextNameIndex = index;

		// Update the last record index for the record and the reenter it into the table
		record.data.second = index;
		nameTable.update(record);
	}
}

ostream& operator <<(ostream& out, const PlanetRecord record)
{
	// Output the data in the planet and the next index of each searchable index
	out << record.planet << endl;
	out << "Discovery Index: "  << record.nextDiscoveryIndex << endl;
	out << "Number Index: "  << record.nextPlanetNumIndex << endl;
	out << "Temperature Index: "  << record.nextTemperatureIndex << endl;
	out << "Name Index: "  << record.nextNameIndex << endl;

	return out;
}
