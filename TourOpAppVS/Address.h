#pragma once
#include "RoomType.h"
#include "mylib.h"

struct Address {
	string country;
	string region;
	string city;
	string hotel;
	RoomType room;
	// Constructor.
	Address();
	// Change Address data.
	void ChangeAddress(string country, string region, string city, string hotel, RoomType roomType) 
		throw(invalid_argument, bad_exception);
	// Print Address data.				
	friend void operator << (ostream &os, Address &address);
	friend void operator >> (istream &is, Address &address);
};




