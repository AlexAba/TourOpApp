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
void Voucher::ChangeVoucher() {

	do {
		cout << "Entre, please, the number of kids ";
		cin >> kids;
		if (CinFail()) kids = -1;
	} while (kids < 0);
	do {
		cout << "Entre, please, the number of adults ";
		cin >> adults;
		if (CinFail()) adults = -1;
	} while (adults < 0);
	address.ChangeAddress();
	ChangeTime();

}
void Voucher::ChangeTime() {
	do {
		do {
			cout << "Enter year ";
			cin >> vouchTime.tm_year;
			if (CinFail()) {
				vouchTime.tm_year = -1;
			}
		} while (vouchTime.tm_year < 0);
		int temp;
		do {
			cout << "Enter month ";
			cin >> temp;
			if (CinFail()) {
				temp = -1;
			}
			vouchTime.tm_mon = temp - 1;

		} while (vouchTime.tm_mon < 0 || vouchTime.tm_mon > 11);
		do {
			cout << "Enter day ";
			cin >> vouchTime.tm_mday;
			if (CinFail()) {
				vouchTime.tm_mday = -1;
			}
		} while (vouchTime.tm_mday < 1 || vouchTime.tm_mday > 31);
	} while (!DateIsCorrect());

}
bool Voucher::DateIsCorrect() {
	time_t now = time(0);
	tm * currentTime = new tm();
	gmtime_s(currentTime, &now);
	int year = 1900 + currentTime->tm_year;
	if (vouchTime.tm_year < year) {
		return false;
	}
	else if (vouchTime.tm_year == year) {
		if (vouchTime.tm_mon < currentTime->tm_mon) {
			return false;
		}
		else if (vouchTime.tm_mon == currentTime->tm_mon) {
			if (vouchTime.tm_mday <= currentTime->tm_mday) {
				return false;
			}
			else return true;
		}
		else return true;
	}
	else return true;
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
