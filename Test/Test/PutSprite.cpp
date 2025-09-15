#include <Windows.h>

#include "resource1.h"

BOOL PutSprite(HDC hdc, int x, int y, HDC memDc, COLORREF colorkey, HINSTANCE g_hInst)
{
	HBITMAP MyBitMap, OldBitMap;
	HBITMAP hBit[5];
	BITMAP bit;

	int Frame = 0;

	int bx = 0;
	int by = 0;

	hBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	hBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	hBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	hBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	hBit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	
	while (Frame < 5)
	{
		OldBitMap = (HBITMAP)SelectObject(memDc, hBit[Frame]);
		GetObject(hBit[Frame], sizeof(BITMAP), &bit);
		
		bx = bit.bmWidth;
		by = bit.bmHeight;

		TransparentBlt(hdc, x, y, bx, by, memDc, 0, 0, bx, by, RGB(255, 255, 255));

		//BitBlt(hdc, x, y, 52, 52, memDc, 0, 0, SRCCOPY)

		SelectObject(memDc, OldBitMap);

		Frame++;

		DeleteObject(hBit[Frame]);

		Sleep(100);
	}

	if (GetObject == 0) return FALSE;
	else return TRUE;
}

