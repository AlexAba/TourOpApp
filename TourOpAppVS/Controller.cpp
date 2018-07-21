#include "stdafx.h"
#include "Controller.h"

void Controller::ReadNextID() {
	ifstream ifIDs;
	ifIDs.open("_IDS.txt");
	if (ifIDs.is_open()) {
		ifIDs >> nextUserID;// >> nextVoucherID;

		ifIDs.close();
	}


}
void Controller::WriteNextID() {
	ofstream ofIDs;
	ofIDs.open("_IDS.txt");
	ofIDs << nextUserID;// << " " << nextVoucherID;
	ofIDs.close();
}
void Controller::ReadUsers() {
	users.resize(nextUserID - 1);

	ifstream ifuser;
	ifuser.open("_Users.txt");
	for (int i = 0; i < users.size(); i++) {
		ifuser >> users[i];
	}

}
void Controller::WriteUsers() {
	ofstream ofuser;
	ofuser.open("_Users.txt");

	for (int i = 0; i < users.size(); i++) {
		ofuser << users[i];
	}
}

Controller::Controller() {
	ReadNextID();
	ReadUsers();
}

User Controller::GetUser(int index) {
	return users[index];
}
void Controller::Greet(User user) {


	cout << "\n\tWelcome Mr/Ms " << user.GetName() << " " << user.GetSurname() << "\n" << endl;

	CleanScreen();

}
int Controller::SignUp() {
	string login;
	string password;
	string name;
	string surname;
	users.resize(nextUserID++);
	int index = nextUserID - 2;
	users[index] = User();
	users[index].SetID(nextUserID - 1);
	//users[index].SetVouchID(nextVoucherID);
	do {
		cout << "Enter your login: ";
		cin >> login;
		if (LoginUnique(login)) break;
		else {
			cout << "This login is not unique. Try to enter another login.\n";
			CleanScreen();
		}
	} while (true);
	cout << "Enter your password: ";
	cin >> password;
	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your surname: ";
	cin >> surname;
	users[index].SetLogin(login);
	users[index].SetPass(password);
	users[index].SetName(name);
	users[index].SetSurname(surname);

	string log = login + ".txt";

	ofstream tempfile(log.c_str());
	tempfile.close();
	cout << "You was signed up successful.\n";
	CleanScreen();

	return index;
}
int Controller::FindUser(string ulogin, string upass) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].GetLogin().size() == ulogin.size())
			if (users[i].GetLogin() == ulogin) {
				if (users[i].PassIsCorrect(upass)) {
					return i;
				}
			}
	}
	return -1;
}
int Controller::LogIn() {
	string ulogin;
	string upass;
	int UID = 0;
	cout << "Enter your login: ";
	cin >> ulogin;
	cout << "Enter your password: ";
	cin >> upass;
	UID = FindUser(ulogin, upass);
	if (~UID) {
		users[UID].ReadVouchers();
		Greet(users[UID]);
		return UID;
	}
	else {
		//cout << (users[0].GetLogin()) << endl;
		cout << "Your data are incorrect!" << endl;
		CleanScreen();

		return -1;
	}
	system("cls");
}
int Controller::Autorization() {
	int short choose;
	int id;
	do {
		cout << "1) Log In.\n";
		cout << "2) Sign Up.\n";
		cout << "3) Exit.\n";
		cin >> choose;
		if (CinFail()) choose = -1;

	} while (choose < 1 || choose > 3);

	system("cls");

	switch (choose)
	{
	case 1: id = LogIn();
		break;
	case 2: id = SignUp();
		break;
	case 3: {
		Exit(-1);
		return -1;
		break; }
	default: cout << "Error!!!";
		break;
	}

	return id;
}
void Controller::Menu(int index) {
	int short choose = 0;

	do {
		cout << "1) Buy voucher.\n";
		cout << "2) Pay money for the booked voucher.\n";
		cout << "3) Book voucher.\n";
		cout << "4) Return voucher.\n";
		cout << "5) Change voucher.\n";
		cout << "6) Show all vouchers.\n";
		cout << "7) Change profile.\n";
		cout << "8) Exit.\n";
		cin >> choose;
		if (CinFail()) {
			choose = -1;
		}

	} while (choose < 1 || choose > 8);

	system("cls");
	switch (choose) {
	case 1: users[index].BuyVoucher();
		break;
		return;
	case 2: users[index].BuyExistedVoucher();
		break;
		return;
	case 3: users[index].ReservVoucher();
		break;
		return;
	case 4: users[index].RefundMoney();
		break;
		return;
	case 5: users[index].ChangeVoucher();;
		break;
		return;
	case 6: users[index].PrintActivVouchers();
		CleanScreen();
		break;
		return;
	case 7: users[index].ChangeUserData();
		break;
		return;
	case 8: Exit(index);
		break;
		return;
	default: cout << "Error!!!\n";
		break;
		return;
	}


}
void Controller::Exit(int uindex) {
	if (~uindex) {
		WriteUsers();
		WriteNextID();
		users[uindex].WriteVouchers();
	}
	exit(0);

	return;
}
bool Controller::LoginUnique(string ulogin) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].GetLogin() == ulogin) return false;
	}
	return true;
}
