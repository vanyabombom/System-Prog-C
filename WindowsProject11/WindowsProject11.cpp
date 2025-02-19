#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR login[100];
    static TCHAR pass[100];

    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1)
        {
            GetDlgItemText(hWnd, IDC_EDIT1, login, 100);
            GetDlgItemText(hWnd, IDC_EDIT2, pass, 100);

            if (_tcscmp(login, _T("admin")) == 0 && _tcscmp(pass, _T("admin")) == 0)
            {
                MessageBox(hWnd, _T("Admin"), _T("Admin"), MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hWnd, _T("User"), _T("User"), MB_OK | MB_ICONERROR);
            }
        }
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }

    return FALSE;
}
