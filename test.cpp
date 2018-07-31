#include <iostream>
#include <assert.h>
#include <chrono>
#include <string>
#include "source codes/inf.h"
using namespace std;
uint64_t func(uint64_t& input) {
	do {
		if (!cin) {
			cin.clear();
			cin.ignore();
		}
		cout << "Please enter a number\n";
		cin >> input;
	} while (!cin);
	cout << endl;
	return input;
}
void AtExit() {
	_CrtDumpMemoryLeaks();
}
int main() {
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	atexit(AtExit);
	{
		using namespace std::chrono;
		cout << boolalpha << hex;
		string user;
		inf a;
		a.size_set(8);
		high_resolution_clock::time_point start, end;
		while (1) {
			cout << "^2\tTimes itself\n";
			cout << "HTN\tHexadecimal to number\n";
			cout << "Output\tOutput number\n";
			cout << "Exit\tExit\n";
			getline(cin, user);
			if (user == "^2") {
				cout << a << " * " << a << " = ";
				start = high_resolution_clock::now();
				a *= a;
				end = high_resolution_clock::now();
				cout << a << endl;
				cout << "operator* tooks " << duration<long double, nano>(end - start).count() << " nanoseconds\n\n";
			}
			else if (user == "Output") {
				start = high_resolution_clock::now();
				cout << a << endl;
				end = high_resolution_clock::now();
				cout << "ostream& operator<< tooks " << duration<long double, nano>(end - start).count() << " nanoseconds\n\n";
			}
			else if (user == "HTN") {
				do {
					printf("Please enter a hex string without 0x\n");
					getline(cin, user);
				} while (user.find_first_not_of("0123456789AaBbCcDdEeFf") != string::npos);
				start = high_resolution_clock::now();
				a.hex(user);
				end = high_resolution_clock::now();
				cout << "a.hex tooks " << duration<long double, nano>(end - start).count() << " nanoseconds\n\n";
			}
			else if (user == "Exit") {
				break;
			}
			/*if (func(user) > UINT32_MAX) {
			cout << "Sorry! Higher than 32 bit is not checkable.\nBut, if you don't want to check, enter 1\n";
			if (func(user)) {
			a = func(user);
			cout << user << " * " << user << " = ";
			start = high_resolution_clock::now();
			a *= a;
			end = high_resolution_clock::now();
			cout << "Not implement yet!" << endl;
			cout << "It tooks " << duration<long double, nano>(end - start).count() << " nanoseconds\n\n";
			}
			}
			else {
			a = user;
			cout << user << " * " << user << " = ";
			start = high_resolution_clock::now();
			a *= a;
			end = high_resolution_clock::now();
			cout << (user *= user) << endl;
			cout << (a == inf(user)) << "\tIt tooks " << duration<long double, nano>(end - start).count() << " nanoseconds\n\n";
			}*/
		}
	}
	return 0;
}