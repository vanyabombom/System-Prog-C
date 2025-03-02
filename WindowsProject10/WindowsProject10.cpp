#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // создаём главное окно приложения на основе модального диалога
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int score = 0;
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1)
        {
            if (IsDlgButtonChecked(hWnd, IDC_RADIO3) == BST_CHECKED)
            {
                score += 20;
            }
            if (IsDlgButtonChecked(hWnd, IDC_RADIO8) == BST_CHECKED)
            {
                score += 20;
            }
            if (IsDlgButtonChecked(hWnd, IDC_RADIO10) == BST_CHECKED)
            {
                score += 20;
            }
            if (IsDlgButtonChecked(hWnd, IDC_CHECK6) == BST_CHECKED && IsDlgButtonChecked(hWnd, IDC_CHECK8) == BST_CHECKED)
            {
                score += 30;
            }
            if (IsDlgButtonChecked(hWnd, IDC_CHECK3) == BST_CHECKED && IsDlgButtonChecked(hWnd, IDC_CHECK4) == BST_CHECKED)
            {
                score += 30;
            }

            wchar_t buff[50];
            swprintf(buff, 50, L"%d/100", score);
            SetWindowText(GetDlgItem(hWnd, IDC_STATIC), buff);
        }
        break; // Добавлен break после обработки WM_COMMAND

    case WM_SHOWWINDOW:
        //MessageBox(0, TEXT("Test"), 0, MB_OK);
        return TRUE;

    case WM_CLOSE:
        EndDialog(hWnd, 0); // закрываем модальный диалог
        return TRUE;
    }

    return FALSE; // Возвращаем FALSE для сообщений, которые не обработаны
}
