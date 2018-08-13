#include "stdafx.h"
#include "User.h"
User::User() {
	userID = 0;
	login = "";
	password = "";
	name = "";
	surname = "";
	vchrCount = 0;
	vouchers = vector<Voucher>();
}
string User::GetLogin() {
	return login;
}
string User::GetName() {
	return name;
}
string User::GetSurname() {
	return surname;
}
void User::ReadVouchers() {
	vouchers.resize(vchrCount);
	ifstream ifVouch;

	string log = login + ".txt";

	ifVouch.open(log.c_str());
	Voucher vouchTemp;
	for (int i = 0; i < vchrCount; i++) {
		ifVouch >> vouchers[i];
	}
	ifVouch.close();
}
void User::WriteVouchers() {
	ofstream ofVouch;

	string log = login + ".txt";

	ofVouch.open(log);
	for (int i = 0; i < vouchers.size(); i++) {
		if (vouchers[i].GetFlag() != Status::inactive) {
			ofVouch << vouchers[i]; 
		}
	}
	ofVouch.close();
}
void User::ChangeUserData(string name, string surname, string previousPass, string newPass) {
	
	this->name = name;
	this->surname = surname;
	if (password != EncryptPass(previousPass)) throw invalid_argument("\nIncorect data: previous password.\n");
	SetPass(newPass);
}
void User::ChangeVoucher(short choose, short kids, short adults, Address address, tm date, Status status) {

		vouchers[choose].ChangeVoucher(kids, adults, address, date, status);
}
string User::EncryptPass(string pass) {
	int key = userID * 2 + userID % 26;
	string newPass;
	newPass.resize(pass.length());
	for (int i = 0; i < newPass.length(); i++) {
		newPass[i] = 'a' + (pass[i] + key - 'a') % 26;
	}
	return newPass;
}
Voucher User::GetVoucher(int index) {
	return vouchers[index];
}
bool User::PassIsCorrect(string pass) {
	if (password == EncryptPass(pass)) {
		return true;
	}
	return false;
}
int User::RefundMoney(short choose) {
	
	float retMoney = 0;
	vouchers[choose].SetFlag(0);
	vchrCount--;
	retMoney = vouchers[choose].GetPrice() * vouchers[choose].PriceRate();
	return retMoney;

}
void User::DeleteLastVoucher() {
	vouchers.resize(--vchrCount);
}
void User::BuyVoucher(short kids, short adults, Address address, tm date) {
	vouchers.resize(++vchrCount);

	vouchers[vchrCount - 1].ChangeVoucher(kids, adults, address, date, active);
}
void User::BuyExistedVoucher(short choose) {

	vouchers[choose].SetFlag(2);
}
void User::ReservVoucher(short kids, short adults, Address address, tm date) {
	vouchers.resize(++vchrCount);

	vouchers[vchrCount - 1].ChangeVoucher(kids, adults, address, date, preodered);
}
void User::SetID(int uid) {
	if (!userID) userID = uid;
}
void User::SetName(string uname) {
	name = uname;
}
void User::SetSurname(string usurname) {
	surname = usurname;
}
void User::SetLogin(string ulogin) {
	if (!login[0])login = ulogin;
}
void User::SetPass(string pass) {
	password = EncryptPass(pass);
}
int User::GetUId() {
	return userID;
}
int User::GetVoucherCount() {
	return vchrCount;
}
void operator << (ostream &os, User &user) {
	os << user.userID << " " << user.login << " " << user.password << " " << user.name << " " << user.surname << " " << user.vchrCount << "\n";
}
void operator >> (istream &is, User &user) {
	is >> user.userID >> user.login >> user.password >> user.name >> user.surname >> user.vchrCount;
}
