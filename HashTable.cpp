/*
 * Quinn Pham
 * Filename: HashTable.cpp
 * Contains: Implementation of the HashTable class
 * Does: Implements a hash table with insert, search
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#include <iostream>
#include <functional>
#include "HashTable.h"
#include "Word.h"

using namespace std;

/* Function: constructor
 * Input: none
 * Output: none
 * Does: constructs the hash table with an initial capacity
 */
HashTable::HashTable() {
	capacity = 90000; // initial capacity
	size = 0;
	table = new LinkedList<Word>[capacity];
}

/* Function: destructor
 * Input: none
 * Output: none
 * Does: deallocates all memory and gets rid of the hash table
 */
HashTable::~HashTable() {
	for (int i = 0; i < capacity; i++) {
		table[i].make_empty();
	}
	delete [] table;
}

/* Function: insert
 * Input: a Word
 * Output: none
 * Does: inserts a Word into the hash table
 */
void HashTable::insert(Word word) {
	int index = myHash(word.get_key()); // find the index
	// check if full
	if (is_full()) {
		expand();
	}
	// traversing, making sure duplicates go in same bucket
	while (not table[index].is_empty() &&
		   table[index].get_value_at(0).get_key() != word.get_key()) {
		index = increment(index);
	}
	if (table[index].is_empty()) { // only increase size if new bucket
		size++;
		table[index].insert(word);
		return;
	}
	/* if the Word matches Word just inserted (means word appears multiple
		times in line) then don't insert*/
	if (table[index].get_value_at(0) == word) { 
		return;
	}
	table[index].insert(word); // insert, but don't increase size
}

/* Function: iQuery (insensitive query)
 * Input: 2 strings (lowercase key and original key)
 * Output: none
 * Does: finds the key in the hash table
 		 insensitive query prints all Words in the bucket
 */
void HashTable::iQuery(string key, string orig) {
	int index = myHash(key);
	while (index < capacity && not table[index].is_empty()) {
		if (table[index].get_value_at(0).get_key() == key) { // found
			(table[index]).print(cout);
			return;
		}
		index = increment(index);
	}
	cout << orig << " Not Found." << endl;
}

/* Function: sQuery (sensitive query)
 * Input: 2 strings (lowercase key and original key)
 * Output: none
 * Does: finds the key in the hash table
 		 sensitive query prints only exact matches from the bucket
 */
void HashTable::sQuery(string key, string orig) {
	int index = myHash(key);
	while (index < capacity && not table[index].is_empty()) {
		if (table[index].get_value_at(0).get_key() == key) {
			sPrint(table[index], orig); // call on sPrint 
			return;
		}
		index = increment(index);
	}
	cout << orig << " Not Found. Try with @insensitive or @i." << endl;
}

/* Function: sPrint (sensitive print)
 * Input: a LL and a string (the original key)
 * Output: none
 * Does: finds and prints the original key in the bucket
 */
void HashTable::sPrint(LinkedList<Word> &ll, string orig) {
	int len = ll.get_length();
	bool found;
	for (int i = 0; i < len; i++) { // traverse the LL
		if (ll.get_value_at(i).get_original() == orig) {
			cout << ll.get_value_at(i) << endl;
			found = true;
		}
	}
	if (found == false) { // did not find exact match
		cout << orig << " Not Found. Try with @insensitive or @i." << endl;
	}
}

/* Function: expand
 * Input: none
 * Output: none
 * Does: expands the hash table and rehashes all keys
 		 new capacity set as capacity * 3 / 2 in order to avoid rehashing to 
 		 	the same bucket due to divisibility
 */
void HashTable::expand() {
	capacity = capacity * 3 / 2;
	LinkedList<Word> *new_table = new LinkedList<Word>[capacity];
	// Rehash
	for (int i = 0; i < capacity * 2 / 3; i++) {
		if (not table[i].is_empty()) {
			string curr_str = table[i].get_value_at(0).get_key();
			int index = myHash(curr_str);
			// checking to make sure no overlaps
			while (not new_table[index].is_empty() &&
		   		   new_table[index].get_value_at(0).get_key() != curr_str) {
				index = increment(index);
			}
			new_table[index] = table[i];
		}
	}
	delete [] table;
	table = new_table;
}

/* Function: myHash
 * Input: a string
 * Output: an int
 * Does: hashes and compresses the key
 */
int HashTable::myHash(string key) {
	// hash first
	hash<string> hashed;
	size_t result = hashed(key);
	// then compress
	return result % capacity;
}

/* Function: is_full
 * Input: none
 * Output: a boolean value
 * Does: checks load factor to see if table is "full"
 */
bool HashTable::is_full() {
	if (size / capacity >= 0.75) {
		return true;
	}
	return false;
}

/* Function: increment
 * Input: an int
 * Output: an int
 * Does: increments an index, wraps around to front if last index
 */
int HashTable::increment(int i) {
	i++;
	if (i >= capacity) {
		i = 0;
	}
	return i;
}