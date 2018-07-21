#include "stdafx.h"
#include "Controller.h"

void CheckFirstStart();
int main(int argc, char** argv) {

	CheckFirstStart();
	Controller bug = Controller();
	int index = 0;
	do {
		index = bug.Autorization();
	} while (index <= -1);
	while (1) {
		bug.Menu(index);
	}
	return 0;
}
void CheckFirstStart() {
	ifstream iids;
	ifstream iuser;
	iids.open("_IDS.txt");
	iuser.open("_Users.txt");

	if (!iids.is_open() || !iuser.is_open()) {
		ofstream oids("_IDS.txt");
		ofstream ouser("_Users.txt");
		oids << 1;
		oids.close();
		ouser.close();
	}
	iids.close();
	iuser.close();
}

