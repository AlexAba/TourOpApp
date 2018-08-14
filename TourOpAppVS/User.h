#pragma once
#include "Voucher.h"

class User {
private:
	//int nextVouchID;
	int userID;
	string login;
	string password;
	string name;
	string surname;
	// This field needs to create vector of corect size every time, when programm is starting.
	int vchrCount;
	vector<Voucher> vouchers;
public:
	User();								// Constructor.
	void BuyVoucher(short kids, short adults, Address address, tm date);					//	Buy new Voucher.
	void BuyExistedVoucher(short choose);			//	Buy reserved Voucher.	
	void ReservVoucher(short kids, short adults, Address address, tm date);				//	To reserve Voucher.
	int RefundMoney(short choose);					//	Refund money for the voucher, including date.
	string GetLogin();					//	Return user login.
	string GetName();					//	Return user name.
	string GetSurname();				//	Return user surname.
	int GetUId();
	int GetVoucherCount();
	string EncryptPass(string pass);	//	This method encripting user pass.
	bool PassIsCorrect(string pass);		//	Check encrytped password, and return true if pass is right.
	void SetPass(string pass);
	void SetLogin(string log);
	void SetName(string uname);
	void SetSurname(string usurname);
	void SetID(int uid);
	void ReadVouchers();				//	Read Voucher from the file. 
	void WriteVouchers();
	Voucher &GetVoucher(int index);			//	Return one Voucher.
	void ChangeUserData(string name, string surname, string previousPass, string newPass);
	void ChangeVoucher(short choose, short kids, short adults, Address address, tm date, Status status);
	void DeleteLastVoucher();
	friend void operator << (ostream &os, User &user);
	friend void operator >> (istream &is, User &user);
};


