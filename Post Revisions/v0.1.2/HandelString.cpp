#include "HandleString.h"

wchar_t* multi_Byte_To_Wide_Char(string& pKey)
{
	//string 转 char*
	char pCStrKey[1024];
	pKey.copy(pCStrKey, pKey.size(), 0);
	pCStrKey[pKey.size()] = '\0';
	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t* pWCStrKey = new wchar_t[pSize];
	//第二次调用将单字节字符串转换成双字节字符串
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}

string Int_To_String(int x) {
	string res;
	while (x) {
		res += (x % 10) + '0';
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}