#include <iostream>
#include "stdio.h"
#include <fstream>
#include <errno.h>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <sys/types.h>
#include "CBitReader.h"

class LocalListener {

public:

	void SendPacketFilter(LPBYTE pBuf, int nBufLen);
	void readfile(char* filename);
	unsigned char* hexstr_to_char(const char* hexstr);
	char* chartobin(unsigned char c);
};