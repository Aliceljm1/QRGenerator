// TestLIBQR_Dll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;
#pragma comment(lib,"libQR.lib") //映射包含其中，类的实现在dll中，
#include "QRUtils.h"
int _tmain(int argc, _TCHAR* argv[])
{
		char* info="ssssss";
	char* filepath="c:\ljm2.bmp";
	QRUtils::createQR(info,filepath);
	return 0;
}

