/*
 * Quinn Pham
 * Filename: StringProcessing.cpp
 * Contains: A program that strips non-alphanumeric chars
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 */

#include <iostream>
#include <string>

using namespace std;

string strip(string input);
bool isAN(char x);
bool isSame(char x, char y);
bool parse(string a, string b);

int main() {
	string input1, input2;

	while (cin >> input1 >> input2) {
		if (parse(input1, input2)) {
			cerr << "Same string!" << endl;
		}
		else {
			cerr << "Different string!" << endl;
		}
	}
}

string strip(string input) {
	int len = input.length();
	string final;
	int start, finish = 0;
	for (int i = 0; i < len; i++) {
		if (isAN(input[i]) == true) {
			start = i;
			break;
		}
	}
	for (int i = len - 1; i > -1; i--) {
		if (isAN(input[i]) == true) {
			finish = i;
			break;
		}
	}
	for (int i = start; i <= finish; i++) {
		final = final + input[i];
	}
	return final;
}

bool isAN(char x) {
	int y = x;
	if ((y > 64 && y < 91) || (y > 96 && y < 123) || (y > 47 && y < 58)) {
		return true;
	}
	return false;
}

bool isSame(char x, char y) {
	if (x == y) {
		return true;
	}
	int a = x;
	int b = y;
	cerr << a << " " << b << endl;
	if (a - b == 32 || b - a == 32) {
		return true;
	}
	return false;
}

bool parse(string a, string b) {
	int len1 = a.length();
	int len2 = b.length();

	if (len1 != len2) {
		return false;
	}

	for (int i = 0; i < len1; i++) {
		if (isSame(a[i], b[i]) == false) {
			return false;
		}
	}
	return true;
}