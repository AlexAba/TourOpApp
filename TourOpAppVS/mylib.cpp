#include "stdafx.h"
#include "mylib.h"

bool CinFail() {
	if (cin.fail()) {
		cin.clear();
		cin.sync();
		return true;
	}
	return false;
}

void ReadLine(string &str) {
	cin.sync();
	getline(cin, str);

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') str[i] = '¤';
	}

}

void WriteLine(string str) {

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '¤') str[i] = ' ';
	}
	cout << str << endl;

}