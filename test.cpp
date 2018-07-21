#include <iostream>
#include <assert.h>
#include "source codes/inf.h"
using namespace std;
int main() {
	cout << boolalpha;
	inf a(255i8);
	a += a;
	cout << "255 + 255 = 510\t" << (a == inf(510)) << endl;
	a = 255i8;
	a *= a;
	cout << "255 * 255 = 65025\t" << (a == inf(65025)) << endl;
	system("PAUSE");
	_CrtDumpMemoryLeaks();
	return 0;
}