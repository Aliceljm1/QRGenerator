// TestLIBQR_Dll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

using namespace std;
#pragma comment(lib,"libQR.lib") //ӳ��������У����ʵ����dll�У�
#include "QRUtils.h"
int _tmain(int argc, _TCHAR* argv[])
{
		char* info="ssssss";
	char* filepath="c:\ljm2.bmp";
	QRUtils::createQR(info,filepath);
	return 0;
}

