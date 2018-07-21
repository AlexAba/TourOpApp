#include "stdafx.h"
#include "invalid_date.h"



invalid_date::invalid_date(){
	message = "Invalid date";
}

invalid_date::invalid_date(string message) {
	this->message = message;
}

string invalid_date::GetMessage() {
	return message;
}