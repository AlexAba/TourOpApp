#include "stdafx.h"
#include "Controller.h"

void CheckFirstStart();
int LogIn(Controller &ctrl);
int SignUp( Controller &ctrl);
void Exit(Controller &ctrl);
void LogOut(Controller &ctrl, int index);
void PrintActiveVouchers(Controller &ctrl, int index);
int main(int argc, char** argv) {

	CheckFirstStart();
	
	int index, choice;;
	Controller TourOpApp = Controller();

	while (true) {


		do {
			cout << "Enter the number of the needed event!\n" << endl;
			cout << "1) Log In" << endl;
			cout << "2) Sign Up" << endl;
			cout << "3) Exit" << endl;

			cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 3);
		
		
		switch (choice)
		{
		case 1: index = LogIn(TourOpApp);
			if (index == -1) continue;
			break;
		case 2: index = SignUp(TourOpApp);
			if (index == -1) continue;
			break;
		case 3: Exit(TourOpApp);
			break;
		default: abort();
			break;
		}

		do {
			cout << "Enter the number of the needed event!\n" << endl;
			cout << "1) Buy voucher." << endl;
			cout << "2) Pay money for the booked voucher." << endl;
			cout << "3) Book voucher." << endl;
			cout << "4) Return voucher." << endl;
			cout << "5) Change voucher." << endl;
			cout << "6) Show vouchers." << endl;
			cout << "7) Change profile." << endl;
			cout << "8) Log Out." << endl;
			cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 8);

		switch (choice) {
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: PrintActiveVouchers(TourOpApp, index);
			break;
		case 7: break;
		case 8: LogOut(TourOpApp, index);
		}

	}

	return 0;
}
void CheckFirstStart() {
	ifstream iids;
	ifstream iuser;
	iids.open("_IDS.txt");
	iuser.open("_Users.txt");

	if (!iids.is_open() || !iuser.is_open()) {
		ofstream oids("_IDS.txt");
		ofstream ouser("_Users.txt");
		oids << 1;
		oids.close();
		ouser.close();
	}
	iids.close();
	iuser.close();
}


int LogIn(Controller &ctrl) {
	string ulogin, upass;
	int index = -1;
	cout << "Login: ";
	cin >> ulogin;
	cout << "Password: ";
	cin >> upass;
	index = ctrl.FindUser(ulogin, upass); 
	if (index == -1) {
		cout << "Incorect login or password.";
		CleanScreen();
		return -1;
	}
	system("cls");
	cout << "You was logged in seccessfully!" << endl;
	CleanScreen();
	return index;
}
int SignUp(Controller &ctrl) {
	int index;
	string name, surname, login, pass1, pass2;
	system("cls");
	cout << "Name: ";
	cin >> name;
	cout << "Surname: ";
	cin >> surname;
	cout << "Login: ";
	cin >> login;
	cout << "Password: ";
	cin >> pass1;
	cout << "Repeat password: ";
	cin >> pass2;
	if (pass1 != pass2) { 
		cout << "Second password is not correspond to first." << endl; 
		CleanScreen();
		return -1;
	}  

	index = ctrl.SignUp(login, pass1, name, surname);
	if (index == -1) {
		cout << "This login is not unique." << endl;
		CleanScreen();
		return -1;
	}
	system("cls");
	cout << "You was signed up successfully!" << endl;
	CleanScreen();
	return index;
}

void Exit(Controller &ctrl) {
	ctrl.WriteUsers();
	ctrl.WriteNextID();
	exit(0);
}

void LogOut(Controller &ctrl, int index) {
	ctrl.GetUser(index).WriteVouchers();
}
void PrintActiveVouchers(Controller &ctrl, int index) {
	User user = ctrl.GetUser(index);
	int size = user.GetVoucherCount();
	for (int i = 0; i < size; i++) {
		Voucher vch = user.GetVoucher(i);
		if (vch.GetFlag == Status::active) {
			cout << "\n";
			cout << "\t\t\t" << i << endl;
			cout << "Kids:\t\t\t" << vch.GetKids() << endl;
			cout << "Adults:\t\t\t" << vch.GetAdults() << endl;
			WriteLine("Country:\t\t\t" + vch.GetAddress().country);
			WriteLine("Region:\t\t\t" + vch.GetAddress().region);
			WriteLine("City:\t\t\t" + vch.GetAddress().city);
			WriteLine("Hotel:\t\t\t" + vch.GetAddress().hotel);
			cout << "Room:\t\t\t";
			switch (vch.GetAddress().room) {
			case RoomType::undefine: cout << "Room type is unknown" << endl;
				break;
			case RoomType::oneRoom: cout << "one room" << endl;
				break;
			case RoomType::twoRooms: cout << "two rooms" << endl;
				break;
			case RoomType::threeRooms: cout << "three rooms" << endl;
				break;
			case RoomType::greatType: cout << "four or more rooms" << endl;
			}
			cout << "Date:\t\t\t" << vch.GetTime().tm_yday + 1 << "." << vch.GetTime().tm_mon + 1 << "." << vch.GetTime().tm_year + 1900 << endl;
			cout << "Price:\t\t\t$" << vch.GetPrice() << endl;
			cout << "\n";
		}
	}
}
