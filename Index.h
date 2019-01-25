/*
 * Quinn Pham
 * Filename: Index.h
 * Contains: Interface of the Index class
 * Does: Reads in files and indexes all words into a hash table
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include "Word.h"
#include "LinkedList.h"
#include "FSTree.h"
#include "DirNode.h"
#include "HashTable.h"

using namespace std;

class Index {
private:
	string dir; // name of directory
	FSTree tree; // tree that contains directory contents
	DirNode *root; // root of the FSTree
	HashTable map; // a hash table associated with the index

	LinkedList<string> all_lines; // all lines of all files
	LinkedList<string> all_files; // all file paths
	// hash table element
	
	void process(); // traverses through tree and reads files
	void process(DirNode *, string); // recursive process

	void read_file(string); // reads the file and parses words

	void read_line(NodeType<string> *, string, int); 
	// reads line, processes words

	string strip(string);
	bool isAN(char);
	string lower(string);

public:
	Index(string dir);
	~Index();

	void run(); // can be called on by driver
};

#endif