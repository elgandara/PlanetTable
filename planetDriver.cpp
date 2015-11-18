// Filename: planetDriver.cpp
// Name: Eliasar Gandara
// Date 4 November 2015

#include <cstdlib>
#include <iostream>
#include "Planet.h"
#include "Table.h"
#include "PlanetTable.h"

char menu();
void action(char choice, PlanetTable table);

using namespace std;

int main()
{
	PlanetTable planetTable;
	char choice;
	cout << "Planet Table: " << endl << endl;

	planetTable.readPlanetFile();

	do {
		choice = menu();
		action(choice, planetTable);

		cout << endl;

	} while (toupper(choice) != 'Q');

	return EXIT_SUCCESS;
}

char menu()
{
	char choice;

	cout << "D - Search by discovery" << endl;
	cout << "# - Search by number of planets in system" << endl;
	cout << "T - Search by effective temperature" << endl;
	cout << "N - Search by planet name" << endl;
	cout << "Q - Quit application" << endl;

	cin >> choice;

	return choice;
}

void action(char choice, PlanetTable table)
{
	// Ignore the last cin that was entered
	cin.ignore();

	// Based on the value of choice, search for the desired value in the chosen table
	string value;
	switch(toupper(choice)) {

	case 'D':
		cout << "Enter the value to search by: " << endl;
		getline(cin, value);
		cout << endl;
		table.searchByDiscoveryMethod(value);
		break;

	case '#':
		cout << "Enter the value to search by: " << endl;
		getline(cin, value);
		cout << endl;
		table.searchByNumberOfPlanets(value);
		break;

	case 'T':
		cout << "Enter the value to search by: " << endl;
		getline(cin, value);
		cout << endl;
		table.searchByTemperature(value);
		break;

	case 'N':
		cout << "Enter the value to search by: " << endl;
		getline(cin, value);
		cout << endl;
		table.searchByName(value);
		break;

	case 'Q':
		break;

	default:
		cout << toupper(choice) << " is not an option!" << endl;

	}
}
