#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "invalid_date.h"

using namespace std;


bool CinFail();
inline void CleanScreen() {
	cout << "\n\n";
	system("pause");
	system("cls");
}

