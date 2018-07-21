#pragma once
#include "Status.h"
#include "Address.h"

class Voucher {
private:
	//int vchrID;
	//int userID;
	short kids;
	short adults;
	float price;
	Address address;
	tm vouchTime;
	Status flag;
public:
	Voucher();							// Constructor.
	void ChangeTime();
	void ChangeVoucher();				//	Change Voucher settings.
	//int GetVchrID();					//	Return Voucher ID.
	Status GetFlag();					//	Return flag of Status of voucher.
	Address GetAddress();
	void SetFlag(int flag);				//	Lead int type to Status type.
	void ShowVoucher();					//	This method print Voucher.
	void PrintDate();
	float PriceRate();
	void SetPrice(float factor);
	float GetPrice();
	bool DateIsCorrect();
	//void SetIDs(int user, int vouch);
	friend void operator << (ostream &os, Voucher &voucher);
	friend void operator >> (istream &is, Voucher &voucher);
	friend void operator << (ostream &os, tm &time);
	friend void operator >> (istream &is, tm &time);
};


