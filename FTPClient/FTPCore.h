#pragma once
#include "stdafx.h"

#include <string>
#include "FTPCode.h"
#include "FTPStatus.h"
#include <afxsock.h>
#include <thread>
#include <queue>


#define BUFFER_LENGTH 1024

using namespace std;

class FTPCore {
protected:
	CSocket * conn;

	thread * listenThread;
	bool isContinueListen;

public:
	FTPCore(const wchar_t * addr);

	void send(std::string cmd);
	
	void startListen();
	void endListen();

	~FTPCore();

protected:
	std::string cmd;
	queue<FTPStatus> returnStatus;

	void listenOnReturn();

	void triggerReturn(const char * buffer) {
		this->fetchReturn(buffer);
		onReturn();
	}

	virtual void onReturn(){};
	virtual void onThrow(){};

	void fetchReturn(const char * buffer);
};
