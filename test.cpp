#include <iostream>
#include <functional>

using namespace std;

int main() {
	// testing hash
	hash<string> hashed;
	size_t result = hashed("bearded");
	cerr << result << endl;
	cerr << result % 50000 << endl;
	cerr << result % (50000*3/2) << endl;
}