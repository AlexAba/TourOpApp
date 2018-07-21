#pragma once
#include "User.h"

class Controller {
private:
	int nextUserID;
	vector<User> users;
public:

	Controller();
	//int nextVoucherID;

	void Menu(int uid);
	int Autorization();
	void Exit(int uid);
	bool LoginUnique(string ulogin);
	int FindUser(string ulogin, string upass);
	void ReadUsers();
	void WriteUsers();
	void ReadNextID();
	void WriteNextID();
	void Greet(User user);
	int LogIn();
	int SignUp();
	User GetUser(int id);
	//void SetVouchID(User &user);
};


