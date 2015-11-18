// Filename: RecordType.h
// Name: Eliasar Gandara
// Date: 3 November 2015



#ifndef PLANET_TYPE_H
#define PLANET_TYPE_H

#include <string>
using namespace std;

class Planet
{
 public:
	// Constructors
	Planet();

	// Getter methods for all of the data values
	string getRowId() const {return data[0];}
	string getHostName() const {return data[1];}
	string getPlanetLetter() const {return data[2];}
	string getDiscoveryMethod() const {return data[3];}
	string getNumPlanets() const {return data[4];}
	string getOrbitalPeriod() const {return data[5];}
	string getMass() const {return data[6];}
	string getRadius() const {return data[7];}
	string getDensity() const {return data[8];}
	string getKeplarField() const {return data[9];}
	string getDegrees() const {return data[10];}
	string getDistance() const {return data[11];}
	string getTemperature() const {return data[12];}
	string getStellarMass() const {return data[13];}
	string getStellarRadius() const {return data[14];}
	string getLastUpdateDate() const {return data[15];}

	string setRowId(string value) {data[0] = value;}
	string setHostName(string value) {data[1] = value;}
	string setPlanetLetter(string value) {data[2] = value;}
	string setDiscoveryMethods(string value) {data[3] = value;}
	string setNumPlanets(string value) {data[4] = value;}
	string setOrbitalPeriod(string value) {data[5] = value;}
	string setMass(string value) {data[6] = value;}
	string setRadius(string value) {data[7] = value;}
	string setDensity(string value) {data[8] = value;}
	string setKeplarField(string value) {data[9] = value;}
	string setDegrees(string value) {data[10] = value;}
	string setDistance(string value) {data[11] = value;}
	string setTemperature(string value) {data[12] = value;}
	string setStellarMass(string value) {data[13] = value;}
	string setStellarRadius(string value) {data[14] = value;}
	string setLastUpdateDate(string value) {data[15] = value;}


	// Member functions
	void clearPlanet();
	void initPlanet(string info[]);

	// Overlaoded output stream
	friend ostream& operator <<(ostream& out, const Planet& record);

 private:
	string data[16];
};


#endif
