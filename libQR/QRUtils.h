#pragma once

// Output file name
#define OUT_FILE_PIXEL_PRESCALER	8											// Prescaler (number of pixels in bmp file for each QRCode pixel, on each dimension)

//默认是黑色
#define PIXEL_COLOR_R				0											// Color of bmp pixels
#define PIXEL_COLOR_G				0
#define PIXEL_COLOR_B				0

// BMP defines

typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef signed long		LONG;

#define BI_RGB			0L

#pragma pack(push, 2)

typedef struct  
	{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
	} BITMAPFILEHEADER;

typedef struct 
	{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
	} BITMAPINFOHEADER;

// 这样做就直接完成了类的导入和导出，在使用处需要定义宏 ,做实验的结果是顶部定义都可以运行
#ifdef DLL_FILE   
class _declspec(dllexport) QRUtils; //导出类QRUtils 
#else   
class _declspec(dllimport) QRUtils; //导入类QRUtils 
#endif 
class QRUtils
{
public:
	QRUtils(void);
	~QRUtils(void);
	static int createQR(const char* info,const char* filepath);
		

};

