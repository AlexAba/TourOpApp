#pragma once
#include "RoomType.h"
#include "mylib.h"

struct Address {
	string country;
	string region;
	string city;
	string hotel;
	RoomType room;
	Address();							// Constructor.
	void ChangeAddress();				// Change Address data.
	void PrintAddress();				// Print Address data.
	friend void operator << (ostream &os, Address &address);
	friend void operator >> (istream &is, Address &address);
};




