#include "stdafx.h"
#include "QRUtils.h"
#pragma pack(pop)
//	-------------------------------------------------------


//	-------------------------------------------------------
//	Main
//	-------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	char* info="ssssss";
	char* filepath="c:\ljm.bmp";
	QRUtils::createQR(info,filepath);
	return 0;
}
//	-------------------------------------------------------

