// Filename: Table.cpp
// Name: Eliasar Gandara
// Date: 6 November 2015

#include "Table.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

Table::Table()
{
	used = 0;
	for (std::size_t i = 0; i < CAPACITY; i++) {
		data[i].int_key = NEVER_USED;
	}
}

void Table::insert(const RecordType& entry)
{
	bool already_present;
	size_t index;
	assert(entry.int_key >= 0);

	// Locate index of key
	findIndex(entry.key, already_present, index);

	// If key is not in table, then we find a location for it
	if (!already_present) {
		assert(size() < CAPACITY);
		index = hash(entry.key); // Use hashed key as starting point
		while (!isVacant(index)) {
			index = nextIndex(index); // Find the next available spot (open address hashing)
		}
		used++; // Increment the count of the records
	}
	data[index] = entry; // Assign entry
}

void Table::update(const RecordType& entry)
{
	bool already_present;
	size_t index;
	assert(entry.int_key >= 0);

	// Locate index of key
	findIndex(entry.key, already_present, index);

	// If the key is in the table, the value will be updated
	if (already_present) {
		index = hash(entry.key); // Use the key to find its location
		data[index] = entry;
	}

	// Otherwise, nothing will be done
}

void Table::remove(string key)
{
	bool is_found;
	size_t index;
	int int_key = generateIntKey(key);
	assert(int_key >= 0); // Make sure the key is valid

	findIndex(key, is_found, index);

	// If the key is found, then it will be removed
	if (is_found) {
		data[index].int_key = PREVIOUSLY_USED; // Int key now becomes a negative value
		data[index].key = ""; // Set the record's key to an empty string
		used--; // Update the number of items
	}
}

bool Table::isPresent(string key)
{
	size_t index;
	bool found;
	int int_key = generateIntKey(key);
	assert(int_key >= 0);
	findIndex(key, found, index);

	return found;
}

void Table::find(string key, bool& found, RecordType& entry)
{
	size_t index;
	int int_key = generateIntKey(key);
	assert(int_key >= 0);
	findIndex(key, found, index);

	if (found) {
		entry = data[index];
	}
	else {
		entry.int_key = NEVER_USED; // Set int_key to negative to show it is invalid
		entry.key = "";
	}
}

std::size_t Table::hash(string key)
{
	int int_key = generateIntKey(key);

	return int_key % CAPACITY;
}

std::size_t Table::nextIndex(std::size_t index)
{
	return (index + 1) % CAPACITY; // Loop back to begginning if value is equal to CAPACITY
}

void Table::findIndex(string key, bool& found, std::size_t& index)
{
	size_t count = 0; // Keeps track of the number of spots visited
	index = hash(key); // Start looking at expected hash value

	while ( (count < CAPACITY) && (!neverUsed(index)) && (data[index].key != key) ) {
		count++; // Increase the number of spots that have been visited
		index = nextIndex(index);
	}

	found = (data[index].key == key);
}

bool Table::neverUsed(std::size_t index) const
{
	// Returns true if the int_key is equivalent to NEVER_USED, false otherwise
	return (data[index].int_key == NEVER_USED);
}

bool Table::isVacant(std::size_t index) const
{
	// If the int_key is negative,then it is vacant
	return (data[index].int_key == NEVER_USED || data[index].int_key == PREVIOUSLY_USED);
}

int generateIntKey(string key)
{
	int int_key = 0;
	int multiplier = 1;

	for (int i = 0; i < key.length(); i++) {
		int_key += (key[i] * multiplier);
		multiplier++;
	}

	return int_key;
}

RecordType Table::operator [] (string key)
{
	bool found;
	RecordType record;

	find(key, found, record);

	if (!found) {
		record.data.first = -1;
		record.data.second = -1;
		record.key = "";
		record.int_key = NEVER_USED;
	}

	return record;
}

ostream& operator << (ostream& out, const RecordType& record)
{
	out << "First: " << record.data.first << endl;
	out << "Second: " << record.data.second << endl;
	out << "Key: " << record.key << endl;
	out << "Int Key: " << record.int_key << endl;

	return out;
}
