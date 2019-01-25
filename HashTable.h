/*
 * Quinn Pham
 * Filename: HashTable.h
 * Contains: Interface of the HashTable class
 * Does: Implements a hash table with insert, search
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include "Word.h"
#include "LinkedList.h"

using namespace std;

class HashTable {
private:
	LinkedList<Word> *table; // table: dynamic array of linked lists (bucket)
	int capacity; 
	int size;
	int myHash(string key); // hash function
	void expand(); // expand when full
	bool is_full(); // check if full
	int increment(int i); // increment index
	void sPrint(LinkedList<Word> & ll, string orig); // print, sensitive case

public:
	HashTable();
	~HashTable();
	void insert(Word word); // insert a Word
	void iQuery(string key, string orig); // insensitive query
	void sQuery(string key, string orig); // sensitive query
};

#endif