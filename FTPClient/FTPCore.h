#pragma once
#include <string>
#include "FTPCode.h"

class FTPCore {
private:
	std::string cmd;
	int code;
	std::string msg;

public:
	void send(std::string cmd);
	virtual void onReturn(int code, std::string msg);
	virtual void onThrow(int code, std::string msg);
};
