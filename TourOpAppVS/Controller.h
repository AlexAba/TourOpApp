#pragma once
#include "User.h"

class Controller {
private:
	int nextUserID;
	vector<User> users;
public:

	Controller();
	~Controller();

	void Exit(int uid);
	bool LoginUnique(string ulogin);
	// Use this for find user by login and check password. If all data is true method will return index of user or -1 otherwise.
	int FindUser(string ulogin, string upass);
	void ReadUsers();
	void WriteUsers();
	void ReadNextID();
	void WriteNextID();
	// Use this to create new user. If login unique it'll return index of user otherwise -1.
	int SignUp(string login, string password, string name, string surname);
	User GetUser(int id);
	//void SetVouchID(User &user);
};


