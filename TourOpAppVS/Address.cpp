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
	if (roomType < 0 || roomType > 4) { throw &invalid_argument("Bad roomType argument"); }
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
void Address::PrintAddress() {
	cout << "Country:\t\t" << country << endl;
	cout << "Region:\t\t\t" << region << endl;
	cout << "City:\t\t\t" << city << endl;
	cout << "Hotel name:\t\t" << hotel << endl;
	cout << "Room type:\t\t";

	switch (room) {
	case undefine: cout << "no info" << endl;
		break;
	case oneRoom: cout << "one room" << endl;
		break;
	case twoRooms: cout << "two rooms" << endl;
		break;
	case threeRooms: cout << "three rooms" << endl;
		break;
	case greatType: cout << "more than three rooms" << endl;
	}

}

