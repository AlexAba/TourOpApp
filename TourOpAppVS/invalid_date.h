#pragma once
#include <string>

using namespace std;

class invalid_date{
	string message;
public:
	invalid_date();
	invalid_date(string message);
	string what();
};

