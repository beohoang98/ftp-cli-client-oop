#pragma once

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class FTPStatus {
private:
	int code;
	string msg;

public:
	FTPStatus(const char * buffer) {
		this->code = 0;
		this->msg = "";

		stringstream ss(buffer);
		string tmpMsg;
		char isNext = '-';

		while (isNext == '-' && !ss.eof()) {
			ss >> this->code;
			ss >> isNext;
			getline(ss, tmpMsg);
			// ss.ignore(1);
			this->msg += tmpMsg;
		}
	}

	int getCode() {
		return this->code;
	}

	string getMsg() {
		return this->msg;
	}

	~FTPStatus() {

	}
};