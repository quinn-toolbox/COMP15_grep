/*
 * Quinn Pham
 * Filename: main.cpp
 * Contains: Driver of gerp
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#include <iostream>
#include "Index.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Please include one directory." << endl;
		return 1;
	}
	// create an index with the directory given
	Index index(argv[1]);
	index.run(); // run commands
	return 0;
}