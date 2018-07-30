#pragma once
#include "User.h"

class Controller {
private:
	int nextUserID;
	vector<User> users;
public:

	Controller();
	//int nextVoucherID;

	void Exit(int uid);
	bool LoginUnique(string ulogin);
	int FindUser(string ulogin, string upass);
	void ReadUsers();
	void WriteUsers();
	void ReadNextID();
	void WriteNextID();
	int LogIn(string login, string pass);
	int SignUp(string login, string password, string name, string surname);
	User GetUser(int id);
	//void SetVouchID(User &user);
};


