#include "stdafx.h"
#include "Voucher.h"

Voucher::Voucher() {
	kids = 0;
	adults = 0;
	price = 0;
	address = Address();
	vouchTime = tm();
	flag = inactive;
}
void Voucher::ChangeVoucher(short kids, short adults, Address address, tm date, Status status) {

	address.ChangeAddress(address.country, address.region, address.city, address.hotel, address.room);
	ChangeTime(date);
	SetPrice(1000);

}
void Voucher::ChangeTime(tm time) {
	vouchTime = time;
}
bool Voucher::DateIsCorrect() {
	return true;
}
Status Voucher::GetFlag() {
	return flag;
}
Address Voucher::GetAddress() {
	return address;
}
void Voucher::SetFlag(int flag) {
	this->flag = ((Status)flag);		// 0-inactive, 1-pre-odered, 2-active.
}
void operator <<(ostream &os, tm &time) {
	os << time.tm_year << " " << time.tm_mon << " " << time.tm_mday;
}
void operator >>(istream &is, tm &time) {
	is >> time.tm_year >> time.tm_mon >> time.tm_mday;
}
void operator << (ostream &os, Voucher &voucher) {
	os << /*voucher.vchrID << " " << voucher.userID << " " << */voucher.kids << " " << voucher.adults << " " << voucher.price << " " << voucher.address;
	os << " " << voucher.vouchTime;
	os << " " << voucher.flag << "\n";
}
void operator >>(istream &is, Voucher &voucher) {
	int iflag;
	is >> /*voucher.vchrID >> voucher.userID >> */voucher.kids >> voucher.adults >> voucher.price >> voucher.address;
	is >> voucher.vouchTime;
	is >> iflag;
	voucher.SetFlag(iflag);
}
void Voucher::ShowVoucher() {
	cout << "The number of kids:\t" << kids << endl;
	cout << "The number of adults:\t" << adults << endl;
	address.PrintAddress();
	PrintDate();
	cout << "Price:\t\t\t$" << price << endl;
}
float Voucher::PriceRate() {
	time_t now = time(0);
	tm * currentTime = new tm();
	gmtime_s(currentTime, &now);
	currentTime->tm_year += 1900;

	if (vouchTime.tm_year - currentTime->tm_year < 1) {
		if (vouchTime.tm_mon - currentTime->tm_mon >= 6) return .99f;
		else if (vouchTime.tm_mon - currentTime->tm_mon >= 3) return .6f;
		else if (vouchTime.tm_mon - currentTime->tm_mon >= 1) return .25f;
		else return .1f;
	}
	else return 1.f;

}
float Voucher::GetPrice() {
	return price;
}
void Voucher::SetPrice(float factor) {

	price = float(((int)address.room * 1.5 * adults + (int)address.room * kids * 0.8f) * factor);

}
void Voucher::PrintDate() {
	cout << "Date:\t\t\t" << vouchTime.tm_mday << "." << vouchTime.tm_mon + 1 << "." << vouchTime.tm_year << endl;
}
