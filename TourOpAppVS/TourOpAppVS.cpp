#include "stdafx.h"
#include "Controller.h"

void CheckFirstStart();
int LogIn(Controller &ctrl);
int SignUp(Controller &ctrl);
int main(int argc, char** argv) {

	CheckFirstStart();
	
	while (true) {

		int choice;

		do {
			cout << "Enter the number of the needed event!\n" << endl;
			cout << "1) Log In" << endl;
			cout << "2) Sign Up" << endl;
			cout << "3) Exit" << endl;

			cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 3);
		
		int index;
		Controller TourOpApp = Controller();
		switch (choice)
		{
		case 1: index = LogIn(TourOpApp);
			break;
		case 2: index = SignUp(TourOpApp);
			break;
		case 3: exit(0);
			break;
		default: abort();
			break;
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
	cout << "Pass: ";
	cin >> upass;
	while(index == -1){
		index = ctrl.LogIn(ulogin, upass); 
	}
	return 0;
}
int SignUp(Controller &ctrl) {
	cout << "Signed up" << endl;
	return 0;
}
