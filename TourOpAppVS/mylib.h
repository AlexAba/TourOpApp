#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "invalid_date.h"
#include "invalid_input.h"

using namespace std;


bool CinFail();
void ReadLine(string &str);
void WriteLine(string str);
inline void CleanScreen() {
	cout << "\n\n";
	system("pause");
	system("cls");
}

