#include "stdafx.h"
#include "Controller.h"

void CheckFirstStart();

int LogIn(Controller &ctrl);
int SignUp( Controller &ctrl);
void Exit(Controller &ctrl, char foreground, char background);

void LogOut(Controller &ctrl, int index, bool &flag);
void PrintActiveVouchers(Controller &ctrl, int index);
void ChangeProfile(Controller &ctrl, int index);
void BuyVoucher(Controller &ctrl, int index);
void ChangeVoucher(Controller &ctrl, int index);
void ReturnVoucher(Controller &ctrl, int index);
void BookVoucher(Controller &ctrl, int index);
void AppSettings(char &foreground, char &background);
void SetColor(char foreground, char background);
void ReadColor(char &foreground, char &background);
void WriteColor(char foreground, char background);

tm SetDate();
Address SetAddress();

int main(int argc, char** argv) {
	CheckFirstStart();
	int index, choice;
	char foreground, background;
	ReadColor(foreground, background);
	SetColor(foreground, background);
	Controller TourOpApp = Controller();
	bool isfail;
	while (true) {


		do {
			cout << "Enter the number of the needed event!\n" << endl;
			cout << "1) Log In" << endl;
			cout << "2) Sign Up" << endl;
			cout << "3) Exit" << endl;

			cin >> choice;
			system("cls");
			isfail = CinFail();
		} while (choice < 1 || choice > 3 || isfail);
		
		
		switch (choice)
		{
		case 1: index = LogIn(TourOpApp);
			if (index == -1) continue;
			break;
		case 2: index = SignUp(TourOpApp);
			if (index == -1) continue;
			break;
		case 3: Exit(TourOpApp, foreground, background);
			break;
		default: abort();
			break;
		}
		// When it's needs to log out from menu set value as false.
		bool menu = true;
		while (menu) {
			do {
				CinFail();
				cout << "Enter the number of the needed event!\n" << endl;
				cout << "1) Buy voucher." << endl;
				cout << "2) Application settings." << endl;
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
			case 1: BuyVoucher(TourOpApp, index);
				break;
			case 2: AppSettings(foreground, background);
				break;
			case 3: BookVoucher(TourOpApp, index);
				break;
			case 4:	ReturnVoucher(TourOpApp, index);
				break;
			case 5: ChangeVoucher(TourOpApp, index);
				break;
			case 6: system("cls"); 
				PrintActiveVouchers(TourOpApp, index);
				CleanScreen();
				break;
			case 7: ChangeProfile(TourOpApp, index);
					break;
			case 8: LogOut(TourOpApp, index, menu);
			}
		}

	}

	return 0;
}
void CheckFirstStart() {
	ifstream iids;
	ifstream iuser;
	iids.open("_IDS.txt");
	iuser.open("_Users.txt");
	ifstream isettings("_Settings.txt");

	if (!isettings.is_open()) {
		ofstream osettings("_Settings.txt");

		osettings << 7 << 0;

		osettings.close();
	}

	if (!iids.is_open() || !iuser.is_open()) {
		ofstream oids("_IDS.txt");
		ofstream ouser("_Users.txt");
		oids << 1;
		oids.close();
		ouser.close();
	}
	iids.close();
	iuser.close();
	isettings.close();
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
void Exit(Controller &ctrl, char foreground, char background) {
	ctrl.WriteUsers();
	ctrl.WriteNextID();
	WriteColor(foreground, background);
	exit(0);
}

void LogOut(Controller &ctrl, int index, bool &flag) {
	ctrl.GetUser(index).WriteVouchers();
	flag = false;
}
void PrintActiveVouchers(Controller &ctrl, int index) {
	User user = ctrl.GetUser(index);
	int size = user.GetVoucherCount();
	for (int i = 0; i < size; i++) {
		Voucher vch = user.GetVoucher(i);
		if (vch.GetFlag() == Status::active || vch.GetFlag() == Status::preodered) {
			cout << "\n";
			cout << "Index:\t\t" << i << endl;
			cout << "Kids:\t\t" << vch.GetKids() << endl;
			cout << "Adults:\t\t" << vch.GetAdults() << endl;
			WriteLine("Country:\t" + vch.GetAddress().country);
			WriteLine("Region:\t\t" + vch.GetAddress().region);
			WriteLine("City:\t\t" + vch.GetAddress().city);
			WriteLine("Hotel:\t\t" + vch.GetAddress().hotel);
			cout << "Room:\t\t";
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
			cout << "Date:\t\t" << vch.GetTime().tm_mday << "." << vch.GetTime().tm_mon + 1 << "." << vch.GetTime().tm_year + 1900 << endl;
			cout << "Price:\t\t$" << vch.GetPrice() << endl;
			switch (vch.GetFlag()) {
			case Status::active: cout << "Active" << endl;
				break;
			case Status::preodered: cout << "Pre-odered" << endl;
				break;
			default: cout << "Status: error" << endl;
				break;
			}
			cout << "\n";
		}
	}
}
void ChangeProfile(Controller &ctrl, int index) {
	try {
		string name, surname, oldpass, newpass1, newpass2;
		cout << "New name: ";
		cin >> name;
		cout << "New surname: ";
		cin >> surname;
		cout << "Old password: ";
		cin >> oldpass;
		cout << "New password: ";
		cin >> newpass1;
		cout << "Repeat new password: ";
		cin >> newpass2;
		if (newpass1 != newpass2) throw invalid_argument("\nSecond password is not correspond to first.\n");
		ctrl.GetUser(index).ChangeUserData(name, surname, oldpass, newpass1);
		system("cls");
		cout << "Profile was changed seccessfully!" << endl;
		CleanScreen();
	}
	catch (invalid_argument exc) {
		cout << exc.what();
		CleanScreen();
	}
	catch (...) {
		cout << "Unknown error" << endl;
		CleanScreen();
	}
}
void BuyVoucher(Controller &ctrl, int index) {
	short kids, adults;
	Address address;
	tm date;
	try {
		cout << "Kids: ";
		cin >> kids;
		if (CinFail()) throw invalid_input("\nInvalid data type.\n");
		cout << "Adults: ";
		cin >> adults;
		if (CinFail()) throw invalid_input("\nInvalid data type.\n");
		address = SetAddress();
		date = SetDate();
		ctrl.GetUser(index).BuyVoucher(kids, adults, address, date);
		system("cls");
		cout << "Voucher was bought." << endl;
		CleanScreen();
	}
	catch (invalid_date exc) {
		cout << exc.what();
		CleanScreen();
		ctrl.GetUser(index).DeleteLastVoucher();
	}
	catch (invalid_argument exc) {
		cout << exc.what();
		CleanScreen();
		ctrl.GetUser(index).DeleteLastVoucher();
	}
	catch (invalid_input exc) {
		cout << exc.what();
		CleanScreen();
	}
	catch (...) {
		cout << "Unknown error" << endl;
		CleanScreen();
	}

}
void ChangeVoucher(Controller &ctrl, int index)  {
	short choise, kids, adults;
	Address address;
	tm date;

	if (ctrl.GetUser(index).GetVoucherCount() == 0) {
		cout << "You do not have any vouchers." << endl;
		CleanScreen();
		return;
	}

	try {
		cout << "Choose index of voucher" << endl;
		PrintActiveVouchers(ctrl, index);
		cin >> choise;
		if (choise < 0 || choise >= ctrl.GetUser(index).GetVoucherCount()) throw invalid_argument("\nIncorrect index of voucher.\n");
		system("cls");

		cout << "Kids: ";
		cin >> kids;
		if (CinFail()) throw invalid_input("\nInvalide data type.\n");
		cout << "Adults: ";
		cin >> adults;
		if (CinFail()) throw invalid_input("\nInvalide data type.\n");

		address = SetAddress();
		date = SetDate();
		
		ctrl.GetUser(index).ChangeVoucher(choise, kids, adults, address, date, ctrl.GetUser(index).GetVoucher(choise).GetFlag());

		system("cls");
		cout << "Voucher was altered.";
		CleanScreen();
		
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
		CleanScreen();
	}
	catch (invalid_date exc) {
		cout << exc.what() << endl;
		CleanScreen();
	}
	catch (invalid_input exc) {
		cout << exc.what() << endl;
		CleanScreen();
	}
	catch (...) {
		cout << "Unknown error" << endl;
		CleanScreen();
	}

}
void ReturnVoucher(Controller &ctrl, int index) {
	system("cls");

	try {
		int choise;
		cout << "Choose index of Voucher" << endl;
		PrintActiveVouchers(ctrl, index);
		cin >> choise;
		if (choise < 0 || choise >= ctrl.GetUser(index).GetVoucherCount()) throw invalid_argument("\nIncorrect index of voucher.\n");
		ctrl.GetUser(index).GetVoucher(choise).SetFlag(Status::inactive);
		system("cls");
		cout << "Voucher was returned." << endl;
		CleanScreen();
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
		CleanScreen();
	}
}
void BookVoucher(Controller &ctrl, int index) {
	short kids, adults;
	Address address;
	tm date;
	try {
		cout << "Kids: ";
		cin >> kids;
		if (CinFail()) throw invalid_input("\nInvalid data type.\n");
		cout << "Adults: ";
		cin >> adults;
		if (CinFail()) throw invalid_input("\nInvalid data type.\n");
		address = SetAddress();
		date = SetDate();
		ctrl.GetUser(index).ReservVoucher(kids, adults, address, date);
		system("cls");
		cout << "Voucher was booked." << endl;
		CleanScreen();
	}
	catch (invalid_date exc) {
		cout << exc.what();
		CleanScreen();
		ctrl.GetUser(index).DeleteLastVoucher();
	}
	catch (invalid_argument exc) {
		cout << exc.what();
		CleanScreen();
		ctrl.GetUser(index).DeleteLastVoucher();
	}
	catch (invalid_input exc) {
		cout << exc.what();
		CleanScreen();
	}
	catch (...) {
		cout << "Unknown error" << endl;
		CleanScreen();
	}
}
void AppSettings(char &foreground, char &background) {
	char color[9] = "color tb";
	char textColor, backColor;
	cout << "Choose color of the text:\n";
	cout << "0 = Black\n1 = Blue\n2 = Green\n3 = Aqua\n4 = Red\n5 = Purple\n6 = Yellow\n7 = White\n8 = Gray\n";
	cout << "9 = Light Blue\nA = Light Green\nB = Light Aqua\nC = Light Red\nD = Light Purple\nE = Light Yellow\nF = Bright White\n";
	cin >> textColor;
	system("cls");
	cout << "Choose color of the background:\n";
	cout << "0 = Black\n1 = Blue\n2 = Green\n3 = Aqua\n4 = Red\n5 = Purple\n6 = Yellow\n7 = White\n8 = Gray\n";
	cout << "9 = Light Blue\nA = Light Green\nB = Light Aqua\nC = Light Red\nD = Light Purple\nE = Light Yellow\nF = Bright White\n";
	cin >> backColor;

	toupper(textColor);
	toupper(backColor);

	color[7] = textColor;
	color[6] = backColor;

	system(color);
	system("cls");
	foreground = textColor;
	background = backColor;
}
void SetColor(char foreground, char background) {
	char color[9] = "color fb";

	color[7] = foreground;
	color[6] = background;

	system(color);
}
void ReadColor(char &foreground, char &background) {
	ifstream isett("_Settings.txt");

	isett >> foreground;
	isett >> background;
}
void WriteColor(char foreground, char background) {
	ofstream osett("_Settings.txt");

	osett << foreground << background;
}

tm SetDate() {
	tm date;

	cout << "Day: ";
	cin >> date.tm_mday;
	cout << "Month: ";
	cin >> date.tm_mon;
	date.tm_mon--;
	cout << "Year: ";
	cin >> date.tm_year;
	date.tm_year -= 1900;

	return date;
}
Address SetAddress() {
	Address address;
	int type;
	cout << "Country: ";
	ReadLine(address.country);
	cout << "Region: ";
	ReadLine(address.region);
	cout << "City: ";
	ReadLine(address.city);
	cout << "Hotel: ";
	ReadLine(address.hotel);
	cout << "Rooms:\t1) One room;\n\t2) Two rooms;\n\t3) Three rooms;\n\t4) Four or more rooms;" << endl;
	cin >> type;
	if (CinFail()) throw invalid_input("\nIncorrect type of entered data.\n");
	address.room = RoomType(type);

	return address;
}