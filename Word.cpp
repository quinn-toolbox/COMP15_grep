/*
 * Quinn Pham
 * Filename: Word.cpp
 * Contains: Word implementation: simple functions
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#include "Word.h"
#include "NodeType.h"

/* Function: default constructor
 * Input: none
 * Output: none
 * Does: initializes an empty word
 */
Word::Word() {
}

/* Function: custom constructor
 * Input: 2 strings, an int, 2 pointers to NodeType<string>
 * Output: none
 * Does: initializes a word with all necessary private vars
 */
Word::Word(string a, string b, int c, 
		   NodeType<string> *d, NodeType<string> *e) {
	key = a;
	original = b;
	num = c;
	filename = d;
	line = e;
}

/* Function: overloaded ==
 * Input: a const Word
 * Output: a boolean value
 * Does: checks if 2 Words are exactly the same
 */
bool Word::operator==(const Word &other) const {
	if (key == other.key && original == other.original && num == other.num
		&& filename == other.filename && line == other.line) {
		return true;
	}
	return false;
}

/* Function: overloaded !=
 * Input: a const Word
 * Output: a boolean value
 * Does: checks if 2 Words are different
 */
bool Word::operator!=(const Word &other) const {
	if (key == other.key && original == other.original && num == other.num
		&& filename == other.filename && line == other.line) {
		return false;
	}
	return true;
}

/* Function: overloaded <<
 * Input: reference to ostream, a Word
 * Output: reference to ostream
 * Does: prints the Word's attributes to ostream
 */
ostream &operator<<(ostream &out, Word word) {
	out << word.get_file_name() << ":"
		<< word.get_line_num() << ": "
		<< word.get_line();
	return out;
}
