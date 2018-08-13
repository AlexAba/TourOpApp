#pragma once
#include <string>

using namespace std;

class invalid_input
{
	string message;
public:
	invalid_input();
	invalid_input(string message);
	string what();
};

