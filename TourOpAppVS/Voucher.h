#pragma once
#include "Status.h"
#include "Address.h"

class Voucher {
private:
	short kids;
	short adults;
	float price;
	Address address;
	tm vouchTime;
	Status flag;
public:
	Voucher();					
	void ChangeTime(tm date) throw(invalid_date, bad_exception);
	void ChangeVoucher(short kids, short adults, Address address, tm date, Status voucherStatus);
	Status GetFlag();			
	Address GetAddress();
	void SetFlag(int flag);			
	float PriceRate();
	void SetPrice(float factor);
	float GetPrice();
	static bool DateIsCorrect(tm date, tm currentTime);
	friend void operator << (ostream &os, Voucher &voucher);
	friend void operator >> (istream &is, Voucher &voucher);
	friend void operator << (ostream &os, tm &time);
	friend void operator >> (istream &is, tm &time);
};


