#include "HandleString.h"

wchar_t* multi_Byte_To_Wide_Char(string& pKey)
{
	//string ת char*
	char pCStrKey[1024];
	pKey.copy(pCStrKey, pKey.size(), 0);
	pCStrKey[pKey.size()] = '\0';
	//��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t* pWCStrKey = new wchar_t[pSize];
	//�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
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