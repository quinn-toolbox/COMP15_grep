/*
 * Quinn Pham
 * Filename: Index.cpp
 * Contains: Implementation of the Index class
 * Does: Reads in files and indexes all words into a hash table
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include "Index.h"
#include "Word.h"

using namespace std;

/* Function: constructor
 * Input: string - directory name
 * Output: none
 * Does: constructs the FSTree from a directory name
 */
Index::Index(string directory) {
// initialize the tree with the directory name
	FSTree init_tree(directory);
	tree = init_tree;
	init_tree.burnTree();
	root = tree.getRoot(); // get root
	dir = directory; // save directory name
}

/* Function: destructor
 * Input: none
 * Output: none
 * Does: deallocates all memory and gets rid of the index
 */
Index::~Index() {
	root = NULL;
}

/* Function: run
 * Input: none
 * Output: none
 * Does: builds the entire index
 */
void Index::run() {
	process();
	cout << "Query? ";
	string query;
	while (cin >> query) {
		if (query == "@q" || query == "@quit") {
			break; // exit out of loop if quit
		}
		else if (query == "@i" || query == "@insensitive") {
			cin >> query; // read again for key
			string stripped = strip(query);
			string low = lower(stripped);
			map.iQuery(low, stripped);
		}
		else {
			string stripped = strip(query);
			string low = lower(stripped);
			map.sQuery(low, stripped);
		}
		cout << "Query? ";
	}
	cout << endl << "Goodbye! Thank you and have a nice day." << endl;
}

/* Function: process
 * Input: none
 * Output: none
 * Does: traverses through the tree and processes files
 */
void Index::process() {
	process(root, dir);
}

/* Function: process (recursive)
 * Input: a pointer to a DirNode, a string 
 * Output: none
 * Does: traverses through the tree and processes files, RECURSIVELY
 */
void Index::process(DirNode *curr, string prev) {
	// edge case
	if (curr == NULL) {
		return;
	}
	// recur through sub-directories 
	for (int i = 0; i < curr->numSubDirs(); i++) {
		// in each dir, go to its files + subdirs
		string subdir = prev + "/" + curr->getSubDir(i)->getName();
		process(curr->getSubDir(i), subdir);
	}

	// recur through files to read lines
	for (int i = 0; i < curr->numFiles(); i++) {
		string file = prev+ "/" + curr->getFile(i); // here is the filename
		read_file(file);
	}
}

/* Function: read_file
 * Input: a string (full file name) 
 * Output: none
 * Does: reads the file and processes lines and words
 */
void Index::read_file(string file) {
// first add the file to the linked list
	NodeType<string> *file_pointer = all_files.insert(file);
	ifstream inputFile;
	inputFile.open(file);
	if (not inputFile.is_open()) {
		cerr << "Unable to open file " << file << endl;
		exit(1);
	}
	// run through to get each line, parse through read_line
	string entire_line;
	int count = 0; // line number
	while (getline(inputFile, entire_line)) {
		count++;
		read_line(file_pointer, entire_line, count);
	}
	inputFile.close();
}

/* Function: read_line
 * Input: string (file name), string (line), int (line number)
 * Output: none
 * Does: reads the line and processes words
 */
void Index::read_line(NodeType<string> *file, string entire_line, int count) {
	// add the line to the LL 
	NodeType<string> *line_pointer = all_lines.insert(entire_line);
	// simple array to keep track of words in line
	Word array[100]; // assuming that no line has more than 100 words
	// parse the line
	istringstream iss(entire_line);
	string ind_word;
	while (iss >> ind_word) {
		string stripped = strip(ind_word);
		string low = lower(stripped);
		// create the Word
		Word new_word(low, stripped, count, file, line_pointer);
		// add word to hash table
		map.insert(new_word);
	}
}

/* Function: strip
 * Input: a string
 * Output: a string
 * Does: strips a string of leading/ trailing non-alphanumeric chars
 */
string Index::strip(string input) {
	int len = input.length();
	string final;
	int start, finish = 0;
	// strip all until first alphanumeric char
	for (int i = 0; i < len; i++) {
		if (isAN(input[i]) == true) {
			start = i;
			break;
		}
	}
	// strip all (from back) until last alphanumeric char
	for (int i = len - 1; i > -1; i--) {
		if (isAN(input[i]) == true) {
			finish = i;
			break;
		}
	}
	// go from start to finish to isolate alphanumeric string
	for (int i = start; i <= finish; i++) {
		final = final + input[i];
	}
	return final;
}

/* Function: isAN
 * Input: a char
 * Output: a boolean value
 * Does: checks if a char is alphanumeric, using ASCII table
 */
bool Index::isAN(char x) {
	int y = x;
	if ((y > 64 && y < 91) || (y > 96 && y < 123) || (y > 47 && y < 58)) {
		return true;
	}
	return false;
}

/* Function: lower
 * Input: a string
 * Output: a string
 * Does: changes a string to completely lowercase, using ASCII values
 */
string Index::lower(string str) {
	string result;
	int len = str.length();

	for (int i = 0; i < len; i++) {
		if (str[i] > 64 && str[i] < 91) { // if uppercase, switch to lower
			char x = str[i] + 32;
			result = result + x;
		}
		else {
			result = result + str[i];
		}
	}
	return result;
}