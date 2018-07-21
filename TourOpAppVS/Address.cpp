#include "stdafx.h"
#include "Address.h"

Address::Address() {
	country = " ";
	region = " ";
	city = " ";
	hotel = " ";
	room = undefine;
}
void Address::ChangeAddress() {
	cout << "Enter country ";
	cin >> country;
	cout << "Enter region ";
	cin >> region;
	cout << "Enter city ";
	cin >> city;
	cout << "Enter hotel name ";
	cin >> hotel;
	int tempType;
	do {
		cout << "Choose room type: \n1)One room.\n2)Two rooms.\n3)Three rooms.\n4)More than three rooms.\n";
		cin >> tempType;
		if (CinFail()) {
			tempType = -1;
		}
	} while (tempType < 1 || tempType > 4);
	room = (RoomType)tempType;
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

