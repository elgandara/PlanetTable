// Filename: Table.h
// Name: Eliasar Gandara
// Date: 6 November 2015

#ifndef TABLE_H
#define TABLE_H

#include <cstdlib>
#include <string>
#include <utility>
#include <iostream>
using namespace std;

struct RecordType{
	pair<int,int> data;
	string key;
	int int_key;
};

class Table
{
 public:
	static const size_t CAPACITY = 3000;

	Table();

	void insert(const RecordType& entry);
	void update(const RecordType& entry);
	void remove(string key);

	bool isPresent(string key);
	void find(string key, bool& found, RecordType& entry);
	std::size_t size() const {return used;}

	RecordType operator [] (string key);

 private:
	static const int NEVER_USED = -1;
	static const int PREVIOUSLY_USED = -2;

	RecordType data[CAPACITY];
	std::size_t used;

	// Helper functions
	std::size_t hash(string key);
	std::size_t nextIndex(std::size_t index);
	void findIndex(string key, bool& found, std::size_t& index);
	bool neverUsed(std::size_t index) const;
	bool isVacant(std::size_t index) const;

};

int generateIntKey(string key);
ostream& operator <<(ostream& out, const RecordType& record);

#endif
