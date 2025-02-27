#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "resource.h"
#include <time.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("CURSOR");

HCURSOR cursor1;
HCURSOR cursor2;
HCURSOR cursor3;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDC_CURSOR2));
	wcl.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	cursor1 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
	cursor2 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));
	cursor3 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR3));
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("CURSOR"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static time_t t;
	static TCHAR str[100];
	t = time(NULL);	
	lstrcpy(str, _tctime(&t));	
	str[lstrlen(str) - 1] = '\0';
	SetWindowText(hwnd, str);	

	RECT rect;
	GetWindowRect(hwnd, &rect);
	SetWindowPos(hwnd, nullptr, rect.left + 5, rect.top, 0, 0, SWP_NOSIZE);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (x >= 0 && x <= rect.right / 3) {
			SetCursor(cursor2);
		}
		else if (x >= 2 * rect.right / 3 && x <= rect.right) {
			SetCursor(cursor3);
		}
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
