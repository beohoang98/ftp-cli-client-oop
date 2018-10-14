#pragma once
#include "stdafx.h"

enum FTPCode {
	OK = 200,

	LOGIN_FAIL = 530
};

#define FTP_PORT 21