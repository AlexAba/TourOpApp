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
	if (kids < 0 || adults < 0) throw invalid_argument("\nInvalid number of humans.\n");
	ChangeTime(date);
	this->kids = kids;
	this->adults = adults;
	this->address.ChangeAddress(address.country, address.region, address.city, address.hotel, address.room);
	this->flag = status;
	SetPrice(1000);

}
void Voucher::ChangeTime(tm date) {
	time_t now = time(0);
	tm currentTime = tm();
	gmtime_s(&currentTime, &now);

	if (!DateIsCorrect(date, currentTime)) throw invalid_date("\nDate is impossible.\n");
	vouchTime = date;
}
bool Voucher::DateIsCorrect(tm date, tm currentTime) {
	if (date.tm_mday < 1 || date.tm_mday > 31 || date.tm_mon < 0 || date.tm_mon > 11) return false;
	if (date.tm_year < currentTime.tm_year) return false;
	else if (date.tm_year == currentTime.tm_year) {
		if (date.tm_mon < currentTime.tm_mon) return false;
		else if (date.tm_mon == currentTime.tm_mon) {
			if (date.tm_mday <= currentTime.tm_mon) return false;
		}
	}
	
	return true;
}
Status Voucher::GetFlag() {
	return flag;
}
Address Voucher::GetAddress() {
	return address;
}
void Voucher::SetFlag(int flag) {
	if (flag < 0 || flag > 2) throw invalid_argument("\nUnknown status of voucher.\n");
	this->flag = ((Status)flag);		// 0-inactive, 1-pre-odered, 2-active.
}
void operator <<(ostream &os, tm &time) {
	os << time.tm_year << " " << time.tm_mon << " " << time.tm_mday;
}
void operator >>(istream &is, tm &time) {
	is >> time.tm_year >> time.tm_mon >> time.tm_mday;
}
void operator << (ostream &os, Voucher &voucher) {
	os << voucher.kids << " " << voucher.adults << " " << voucher.price << " " << voucher.address;
	os << " " << voucher.vouchTime;
	os << " " << voucher.flag << "\n";
}
void operator >>(istream &is, Voucher &voucher) {
	int iflag;
	is >> voucher.kids >> voucher.adults >> voucher.price >> voucher.address;
	is >> voucher.vouchTime;
	is >> iflag;
	voucher.SetFlag(iflag);
}
float Voucher::PriceRate() {
	time_t now = time(0);
	tm currentTime = tm();
	gmtime_s(&currentTime, &now);

	if (vouchTime.tm_year - currentTime.tm_year < 1) {
		if (vouchTime.tm_mon - currentTime.tm_mon >= 6) return .99f;
		else if (vouchTime.tm_mon - currentTime.tm_mon >= 3) return .6f;
		else if (vouchTime.tm_mon - currentTime.tm_mon >= 1) return .25f;
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
int Voucher::GetKids() {
	return kids;
}
int Voucher::GetAdults() {
	return adults;
}
tm Voucher::GetTime() {
	return vouchTime;
}