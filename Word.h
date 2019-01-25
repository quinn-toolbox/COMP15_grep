/*
 * Quinn Pham
 * Filename: Word.h
 * Contains: Word interface stores a word and values associated with it
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include "NodeType.h"

using namespace std;

class Word {
private:
	string key; // the lowercase word
	string original; // the original word
	int num; // the line number
	NodeType<string> *filename; // the address of the file
	NodeType<string> *line; // the actual line
public:
	Word();
	Word(string, string, int, NodeType<string> *, NodeType<string> *);
	string get_key() { // gets the key
		return key;
	}
	string get_original() { // gets the original word
		return original;
	}
	int get_line_num() { // gets the line number
		return num;
	}
	string get_file_name() { // gets the file name
		return filename->info;
	}
	string get_line() { // gets the entire line
		return line->info;
	}

	bool operator==(const Word&) const;
	bool operator!=(const Word&) const;

};
	ostream &operator<<(ostream &, Word word);

#endif