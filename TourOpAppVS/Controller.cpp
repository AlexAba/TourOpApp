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

Controller::~Controller() {
	WriteNextID();
	WriteUsers();
}

User Controller::GetUser(int index) {
	return users[index];
}
int Controller::SignUp(string login, string password, string name, string surname) {
	if (!LoginUnique(login)) return -1;
	users.resize(nextUserID++);
	int index = nextUserID - 2;
	users[index] = User();
	users[index].SetID(nextUserID - 1);
	users[index].SetLogin(login);
	users[index].SetPass(password);
	users[index].SetName(name);
	users[index].SetSurname(surname);

	string log = login + ".txt";

	ofstream tempfile(log);
	tempfile.close();

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
