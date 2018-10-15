#pragma once

#include "resource.h"
#include "Test01.h"
#include <conio.h>

class App {

private:

public:

	void start() {
		Test01 * test = new Test01(L"127.0.0.1");
		test->startListen();
		
		system("pause");
	}

	void end() {

	}

};