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
	int vchrCount;
	vector<Voucher> vouchers;
public:
	User();								// Constructor.
	bool BuyVoucher(short kids, short adults, Address address, tm date);					//	Buy new Voucher.
	bool BuyExistedVoucher(short choose);			//	Buy reserved Voucher.	
	bool ReservVoucher(short kids, short adults, Address address, tm date);				//	Reserv Voucher.
	void RefundMoney();					//	Refund money for the voucher, including date.
	string GetLogin();					//	Return user login.
	string GetName();					//	Return user name.
	string GetSurname();				//	Return user surname.
	int GetUId();
	string EncryptPass(string pass);	//	This method encripting user pass.
	bool PassIsCorrect(string pass);		//	Check encrytped password, and return true if pass is right.
	void SetPass(string pass);
	void SetLogin(string log);
	void SetName(string uname);
	void SetSurname(string usurname);
	void SetID(int uid);
	void ReadVouchers();				//	Read Voucher from the file. 
	void WriteVouchers();
	Voucher GetVoucher(int index);			//	Return one Voucher.
	void ChangeUserData();				//	This method change user data.
	void ChangeVoucher();
	void PrintActivVouchers();
	void PrintPreoderedVouchers();
	//void SetVouchID(int val);
	friend void operator << (ostream &os, User &user);
	friend void operator >> (istream &is, User &user);
};


