#include "QRUtils.h"
#include "stdafx.h"
#include <string.h>
#include <errno.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>

#include "qrencode.h"
//	-------------------------------------------------------


//	-------------------------------------------------------
//	DEFines
//	-------------------------------------------------------



QRUtils::QRUtils(void)
{
}

int QRUtils::createQR(const char* info,const char* filepath)
{
	unsigned int	unWidth, x, y, l, n, unWidthAdjusted, unDataBytes;
	unsigned char*	pRGBData, *pSourceData, *pDestData;
	QRcode*			pQRC;
	FILE*			f;

	/*
	* Create a symbol from the string. The library automatically parses the input
	* string and encodes in a QR Code symbol.
	* @warning This function is THREAD UNSAFE when pthread is disabled.
	* @param string input string. It must be NUL terminated.
	* @param version version of the symbol. If 0, the library chooses the minimum
	*                version for the given input data.
	* @param level error correction level.
	* @param hint tell the library how non-alphanumerical characters should be
	*             encoded. If QR_MODE_KANJI is given, kanji characters will be
	*             encoded as Shif-JIS characters. If QR_MODE_8 is given, all of
	*             non-alphanumerical characters will be encoded as is. If you want
	*             to embed UTF-8 string, choose this.
	* @param casesensitive case-sensitive(1) or not(0).
	* @return an instance of QRcode class. The version of the result QRcode may
	*         be larger than the designated version. On error, NULL is returned,
	*         and errno is set to indicate the error. See Exceptions for the
	*         details.
	* @throw EINVAL invalid input object.
	* @throw ENOMEM unable to allocate memory for input objects.
	* @throw ERANGE input data is too large.
	*/

	// Compute QRCode

	if (pQRC = QRcode_encodeString(info, 0, QR_ECLEVEL_H, QR_MODE_8, 1))
	{
		unWidth = pQRC->width;
		unWidthAdjusted = unWidth * OUT_FILE_PIXEL_PRESCALER * 3;
		if (unWidthAdjusted % 4)
			unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
		unDataBytes = unWidthAdjusted * unWidth * OUT_FILE_PIXEL_PRESCALER;

		// Allocate pixels buffer

		if (!(pRGBData = (unsigned char*)malloc(unDataBytes)))
		{
			printf("Out of memory");
			exit(-1);
		}

		// Preset to white

		memset(pRGBData, 0xff, unDataBytes);


		// Prepare bmp headers

		BITMAPFILEHEADER kFileHeader;
		kFileHeader.bfType = 0x4d42;  // "BM"
		kFileHeader.bfSize =	sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER) +
			unDataBytes;
		kFileHeader.bfReserved1 = 0;
		kFileHeader.bfReserved2 = 0;
		kFileHeader.bfOffBits =	sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER);

		BITMAPINFOHEADER kInfoHeader;
		kInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		kInfoHeader.biWidth = unWidth * OUT_FILE_PIXEL_PRESCALER;
		kInfoHeader.biHeight = -((int)unWidth * OUT_FILE_PIXEL_PRESCALER);
		kInfoHeader.biPlanes = 1;
		kInfoHeader.biBitCount = 24;
		kInfoHeader.biCompression = BI_RGB;
		kInfoHeader.biSizeImage = 0;
		kInfoHeader.biXPelsPerMeter = 0;
		kInfoHeader.biYPelsPerMeter = 0;
		kInfoHeader.biClrUsed = 0;
		kInfoHeader.biClrImportant = 0;


		// Convert QrCode bits to bmp pixels

		pSourceData = pQRC->data;
		for(y = 0; y < unWidth; y++)
		{
			pDestData = pRGBData + unWidthAdjusted * y * OUT_FILE_PIXEL_PRESCALER;
			for(x = 0; x < unWidth; x++)
			{
				if (*pSourceData & 1)
				{
					for(l = 0; l < OUT_FILE_PIXEL_PRESCALER; l++)
					{
						for(n = 0; n < OUT_FILE_PIXEL_PRESCALER; n++)
						{
							*(pDestData +		n * 3 + unWidthAdjusted * l) =	PIXEL_COLOR_B;
							*(pDestData + 1 +	n * 3 + unWidthAdjusted * l) =	PIXEL_COLOR_G;
							*(pDestData + 2 +	n * 3 + unWidthAdjusted * l) =	PIXEL_COLOR_R;
						}
					}
				}
				pDestData += 3 * OUT_FILE_PIXEL_PRESCALER;
				pSourceData++;
			}
		}


		// Output the bmp file

		if (!(fopen_s(&f, filepath, "wb")))
		{
			fwrite(&kFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
			fwrite(&kInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
			fwrite(pRGBData, sizeof(unsigned char), unDataBytes, f);

			fclose(f);
		}
		else
		{
			printf("Unable to open file");
			exit(-1);
		}

		// Free data

		free(pRGBData);
		QRcode_free(pQRC);
	}
	else
	{
		return -1;
	}
	return 1;
}


QRUtils::~QRUtils(void)
{
}
