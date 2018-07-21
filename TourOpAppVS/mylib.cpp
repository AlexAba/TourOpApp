#include "stdafx.h"
#include "mylib.h"

bool CinFail() {
	if (cin.fail()) {
		cin.clear();
		cin.sync();
		return true;
	}
	return false;
}
