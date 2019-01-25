/*
 * Quinn Pham
 * Filename: FSTreeTraversal.cpp
 * Contains: A program that traverses through the file system
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#include <iostream>
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

void postOrderPrint(DirNode *curr, string prev);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Please include a directory." << endl;
		return 1;
	}
	string dir = argv[1];
	FSTree tree(dir);
	DirNode *root = tree.getRoot();
	postOrderPrint(root, dir);
	return 0;

}

void postOrderPrint(DirNode *curr, string prev) {
	// edge case
	if (curr == NULL) {
		return;
	}
	// recur through sub-directories 
	for (int i = 0; i < curr->numSubDirs(); i++) {
		string dir = "/" + curr->getSubDir(i)->getName();
		postOrderPrint(curr->getSubDir(i), prev + dir);
		cerr << prev << dir << endl;

	}
	// recur through files
	for (int i = 0; i < curr->numFiles(); i++) {
		cerr << prev << "/" << curr->getFile(i) << endl;
	}

}