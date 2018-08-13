#include "stdafx.h"
#include "invalid_input.h"

invalid_input::invalid_input() {
	message = "Invalid input";
}

invalid_input::invalid_input(string message) {
	this->message = message;
}

string invalid_input::what() {
	return message;
}
