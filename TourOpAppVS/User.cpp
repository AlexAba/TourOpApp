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

	ofVouch.open(log.c_str());
	for (int i = 0; i < vouchers.size(); i++) {
		if (vouchers[i].GetFlag() != inactive) { ofVouch << vouchers[i]; }
	}
	ofVouch.close();
}
void User::ChangeUserData() {
	string pass;
	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your surname: ";
	cin >> surname;
	do {
		cout << "Enter your previous password: ";
		cin >> pass;
	} while (!PassIsCorrect(pass));
	cout << "Enter your new pass: ";
	cin >> pass;
	SetPass(pass);
	CleanScreen();

	cout << "Mr/Ms " << name << " " << surname << " your data was changed successful\n";
	CleanScreen();

}
void User::ChangeVoucher() {
	int choose = -1;
	cout << "Choose voucher.\n";
	PrintActivVouchers();
	if (vchrCount > 0) {
		do {
			cout << "Enter number of your voucher: " << endl;
			cin >> choose;
		} while (choose < 0 || choose >= vouchers.size());
		CleanScreen();
		vouchers[choose].ChangeVoucher();

	}
	else { cout << "You do not have any voucher"; }
	CleanScreen();
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
void User::PrintActivVouchers() {
	for (int i = 0; i < vouchers.size(); i++) {
		if (vouchers[i].GetFlag() != inactive) {
			cout << "\n\n";
			cout << "\t" << i << "\n";
			vouchers[i].ShowVoucher();
		}
		cout << "\n\n";
	}
}
void User::PrintPreoderedVouchers() {
	for (int i = 0; i < vouchers.size(); i++) {
		cout << "\n\n";
		cout << "\t" << i << "\n";
		if (vouchers[i].GetFlag() == preodered) {
			vouchers[i].ShowVoucher();
		}
		cout << "\n\n";
	}
}
bool User::PassIsCorrect(string pass) {
	if (password == EncryptPass(pass)) {
		return true;
	}
	return false;
}
void User::RefundMoney() {

	int choose = -1;
	cout << "Choose voucher.\n";
	PrintActivVouchers();
	if (vchrCount > 0) {
		do {
			cout << "Enter number of your voucher: " << endl;
			cin >> choose;
		} while (choose < 0 || choose >= vouchers.size());
		if (vouchers[choose].GetFlag() == inactive) {
			cout << "Incorrect voucher index" << endl;
			CleanScreen();
			return;
		}
		float retMoney = 0;
		vouchers[choose].SetFlag(0);
		vchrCount--;
		retMoney = vouchers[choose].GetPrice() * vouchers[choose].PriceRate();
		cout << "We will return you:\t$" << retMoney << endl;

	}
	else { cout << "You do not have any voucher"; }
	CleanScreen();

}
void User::BuyVoucher() {

	string cardNum;
	vouchers.resize(++vchrCount);
	vouchers[vchrCount - 1];
	//int vchrID = nextVouchID++;

	vouchers[vchrCount - 1].SetFlag(2);
	//vouchers[vchrCount - 1].SetIDs(userID, vchrID);
	vouchers[vchrCount - 1].ChangeVoucher();
	vouchers[vchrCount - 1].SetPrice(1000);

	cout << "Price:\t$" << vouchers[vchrCount - 1].GetPrice() << endl;

	do {
		cout << "Enter, please your card details: ";
		cin >> cardNum;

	} while (cardNum.size() != 16);
	cout << "Voucher was bought successful.\n";
	CleanScreen();
}
void User::BuyExistedVoucher() {
	string cardNum;

	int choose = -1;
	cout << "Choose voucher.\n";
	PrintPreoderedVouchers();
	if (vchrCount > 0) {
		do {
			cout << "Enter number of your voucher: " << endl;
			cin >> choose;
		} while (choose < 0 || choose >= vouchers.size());
		if (vouchers[choose].GetFlag() == active || vouchers[choose].GetFlag() == inactive) {
			cout << "Incorrect voucher index" << endl;
			CleanScreen();
			return;
		}
		vouchers[choose].SetFlag(2);

		do {
			cout << "Enter, please your card details: ";
			cin >> cardNum;

		} while (cardNum.size() != 16);
		cout << "Voucher was bought successful.\n";

	}
	else { cout << "You do not have any voucher"; }
	CleanScreen();
}
void User::ReservVoucher() {
	vouchers.resize(++vchrCount);
	vouchers[vchrCount - 1];

	vouchers[vchrCount - 1].SetFlag(1);
	//vouchers[vchrCount - 1].SetIDs(userID, nextVouchID++);
	vouchers[vchrCount - 1].ChangeVoucher();
	vouchers[vchrCount - 1].SetPrice(1000);

	cout << "Price:\t$" << vouchers[vchrCount - 1].GetPrice() << endl;
	CleanScreen();
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
void operator << (ostream &os, User &user) {
	os << user.userID << " " << user.login << " " << user.password << " " << user.name << " " << user.surname << " " << user.vchrCount << "\n";
}
void operator >> (istream &is, User &user) {
	is >> user.userID >> user.login >> user.password >> user.name >> user.surname >> user.vchrCount;
}
