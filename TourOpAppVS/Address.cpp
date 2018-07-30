#include "stdafx.h"
#include "Address.h"

Address::Address() {
	country = " ";
	region = " ";
	city = " ";
	hotel = " ";
	room = undefine;
}
void Address::ChangeAddress(string country, string region, string city, string hotel, RoomType roomType) {
	this->country = country;
	this->region = region;
	this->city = city;
	this->hotel = hotel;
	if (roomType < 0 || roomType > 4) throw invalid_argument("\nBad roomType argument.\n");
	room = roomType;
}
void operator<< (ostream& os, Address& address) {
	os << address.country << " " << address.region << " " << address.city << " " << address.hotel << " " << address.room;
}
void operator>> (istream& is, Address& address) {
	int temp;
	is >> address.country >> address.region >> address.city >> address.hotel >> temp;
	address.room = (RoomType)temp;
}


