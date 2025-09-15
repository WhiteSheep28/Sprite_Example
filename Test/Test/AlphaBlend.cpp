#include <Windows.h>
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "Msimg32.lib")


bool Test_AlphaBlend(HDC hdc, HDC MemDC, HINSTANCE g_hinst, int Alpha, int Image, int x, int y)
{
	int cx;
	int cy;

	HBITMAP MyBitMap, OldBitMap;
	BITMAP bit;
	BLENDFUNCTION bf;

	MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(Image));
	OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap);
	GetObject(MyBitMap, sizeof(BITMAP), &bit);

	cx = bit.bmWidth;
	cy = bit.bmHeight;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;							
	bf.AlphaFormat = 0;				
	bf.SourceConstantAlpha = Alpha;

	AlphaBlend(hdc, x, y, cx, cy, MemDC, 0, 0, cx, cy, bf);

	SelectObject(MemDC, OldBitMap);

	DeleteObject(MyBitMap);

	if (GetObject == 0) return FALSE;
	else return TRUE;
}