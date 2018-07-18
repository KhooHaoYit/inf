#include <iostream>
#include <assert.h>
#include "source codes/inf.h"
using namespace std;
int main() {
	cout << boolalpha;
	inf a(255i8);
	a += a;
	cout << "255 + 255 = 510\t" << (a == inf(510i16)) << endl;	//Passed
	a = 255i8;
	a *= a;
	cout << "255 * 255 = 65025\t" << (a == inf(65025i16)) << endl;
	system("PAUSE");
	_CrtDumpMemoryLeaks();
	return 0;
}