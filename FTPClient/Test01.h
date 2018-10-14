#include "stdafx.h"

#include "FTPCore.h"
#include <iostream>

class Test01 : public FTPCore {
public:
	Test01(const wchar_t * addr) : FTPCore(addr) {}

	virtual void onReturn() {
		FTPStatus lastStatus = this->returnStatus.front();
		this->returnStatus.pop();

		cout << lastStatus.getCode() << ":\n";
		cout << lastStatus.getMsg() << "\n\n";
	}

	virtual void onThrow() {

	}
};