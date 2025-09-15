#include <windows.h>
#include <cstring>
#include <tchar.h>

#include "BitBlt.h"
#include "AlphaBlend.h"
#include "PutSprite.h"

void __Animate(HWND hWnd);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
TCHAR lpszClass[] = _T("TestProject"); // Use TCHAR for Unicode compatibility

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = (WNDPROC)WndProc;
    WndClass.lpszClassName = lpszClass; // Compatible with TCHAR
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&WndClass);

    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    hWndMain = hWnd;

    /*
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    */

    while (TRUE)
    {
        if (PeekMessage(&Message, NULL, 0, 0,
            PM_REMOVE)) // 메시지 큐에서 메시지 제거
        {
            if (Message.message == WM_QUIT)
                break;

            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
        //// 메시지가 없으면
        else
        {
            __Animate(hWnd);
        }
    }


    return Message.wParam;
}

#include "resource.h"

static HBITMAP OldBitmap = NULL;
static HDC MemDC;
static int x = 0;
static int y = 300;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    static int Alpha = 128;
    static int Count = 0;

    switch (iMessage)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        MemDC = CreateCompatibleDC(hdc);

        Test_BitBlt(hdc, MemDC, g_hInst, IDB_BITMAP1, 500, 0);

        Test_AlphaBlend(hdc, MemDC,g_hInst, Alpha, IDB_BITMAP1, 0, 0);

        DeleteDC(MemDC);

        EndPaint(hWnd, &ps);
        return 0;

    case WM_LBUTTONDOWN:
        Alpha -= 20;
        if (Alpha < 0) Alpha = 0;
        InvalidateRect(hWnd, NULL, TRUE);
        return TRUE;

    case WM_RBUTTONDOWN:
        Alpha += 20;
        if (Alpha > 255) Alpha = 255;
        InvalidateRect(hWnd, NULL, TRUE);
        return TRUE;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT: x -= 10; break;
        case  VK_RIGHT: x += 10; break;
        case VK_UP: y -= 10; break;
        case VK_DOWN: y += 10; break;
        }

        InvalidateRect(hWnd, NULL, TRUE);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void __Animate(HWND hWnd)
{
    HDC hdc;
    PAINTSTRUCT ps;
    
    hdc = GetDC(hWnd);

    MemDC = CreateCompatibleDC(hdc);

    PutSprite(hdc, x, y, MemDC, 0, g_hInst);

    DeleteDC(MemDC);

    ReleaseDC(hWnd,hdc);

    return;
}