#include "stdafx.h"
#include "FTPCore.h"

#include <string>
#include <sstream>
#include <wchar.h>

using namespace std;

FTPCore::FTPCore(const wchar_t * addr)
{
	this->conn = new CSocket();
	this->listenThread = NULL;

	if (!this->conn->Create()) {
		throw new runtime_error("Cannot create socket");
	}

	if (!this->conn->Connect(addr, FTP_PORT)) {
		throw new runtime_error("Cannot connect to server");
	}
}

FTPCore::~FTPCore()
{
	this->isContinueListen = false;
	free(this->listenThread);
	this->conn->Close();
	// free(this->conn);
}

void FTPCore::send(string cmd)
{
	this->cmd = cmd;
	this->conn->Send(cmd.c_str(), cmd.length());
}


void FTPCore::listenOnReturn() {
	while (true) {
		if (this->isContinueListen) {
			char buffer[BUFFER_LENGTH] = { 0 };

			char * oneChar = new char[1];
			*oneChar = 0;

			int len = 0;
			while (this->conn->Receive(oneChar, 1) > 0) {
				buffer[len++] = *oneChar;
				if (*oneChar == '\n' || *oneChar == '\0' || len == BUFFER_LENGTH - 1) break;
				*oneChar = 0;
			}

			if (len > 0) this->triggerReturn(buffer);
			memset(buffer, 0, BUFFER_LENGTH);
			free(oneChar);
		}
	}
}

void FTPCore::fetchReturn(const char * buffer)
{
	FTPStatus status(buffer);
	this->returnStatus.push(status);
}

void FTPCore::startListen()
{
	this->isContinueListen = true;

	// re assign thread
	if (this->isContinueListen) {
		this->listenThread = new thread(&FTPCore::listenOnReturn, this);
		this->listenThread->join();
	}
}

void FTPCore::endListen()
{
	this->isContinueListen = false;
}