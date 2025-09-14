#include "BitBlt.h"

void Test_BitBlt(HDC hdc,HDC MemDC, HINSTANCE g_hinst ,int Image, int x, int y)
{
	int cx;
	int cy;

	HBITMAP MyBitMap, OldBitMap;
	BITMAP bit;
	
	MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(Image));
	OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap);

	GetObject(MyBitMap, sizeof(BITMAP), &bit);

	cx = bit.bmWidth;
	cy = bit.bmHeight;

	BitBlt(hdc, x, y, cx, cy, MemDC, 0, 0, SRCCOPY);
	//BitBlt(hdc, x, y + 10 + cy, cx, cy / 2, hdc, 0, cy / 2, SRCCOPY);

	SelectObject(MemDC, OldBitMap);
	
	DeleteObject(MyBitMap);
}