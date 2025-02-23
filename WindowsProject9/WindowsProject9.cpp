#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void CreateStatic(HWND, int, int, int, int);

POINT startPoint;
bool isPressed = false;
int staticCounter = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)
    {
    case WM_LBUTTONDOWN:
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isPressed = true;
        return TRUE;

    case WM_LBUTTONUP:
        if (isPressed == true)
        {
            int x1 = startPoint.x;
            int y1 = startPoint.y;
            int x2 = LOWORD(lParam);
            int y2 = HIWORD(lParam);

            int left = min(x1, x2);
            int top = min(y1, y2);
            int width = max(10, abs(x2 - x1));
            int height = max(10, abs(y2 - y1));

            if (width == 10 || height == 10)
            {
                MessageBox(hWnd, _T("Слишком маленький квадрат"), _T("Ошибка"), MB_OK);
            }
            else
            {
                CreateStatic(hWnd, left, top, width, height);
            }

            isPressed = false;
        }
        return TRUE;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}

void CreateStatic(HWND hWnd, int x, int y, int width, int height)
{
    TCHAR buffer[100];
    wsprintf(buffer, _T("%d"), staticCounter++);

    CreateWindow(_T("STATIC"), buffer, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
        x, y, width, height, hWnd, NULL, GetModuleHandle(NULL), NULL);
}
