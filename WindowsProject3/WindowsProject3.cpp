#include <windows.h>
#include <tchar.h>
#include <string>
#include "resource.h"

using namespace std;

BOOL CALLBACK GameDialogProc(HWND, UINT, WPARAM, LPARAM);
void CreateGameButton(HWND hWnd, int x, int y, int width, int height, int id, LPCWSTR text);
void UpdateGameButtonText(HWND hWnd, int id);
bool CheckForWinner();
void ResetGameBoard(HWND hWnd);

bool isPlayerX = true;
int moves = 0;
wstring gameButtonText[9] = { L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?" };

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)GameDialogProc);
}

BOOL CALLBACK GameDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        CreateGameButton(hWnd, 50, 50, 100, 100, 1, L"?");
        CreateGameButton(hWnd, 50, 170, 100, 100, 2, L"?");
        CreateGameButton(hWnd, 50, 290, 100, 100, 3, L"?");
        CreateGameButton(hWnd, 170, 50, 100, 100, 4, L"?");
        CreateGameButton(hWnd, 170, 170, 100, 100, 5, L"?");
        CreateGameButton(hWnd, 170, 290, 100, 100, 6, L"?");
        CreateGameButton(hWnd, 290, 50, 100, 100, 7, L"?");
        CreateGameButton(hWnd, 290, 170, 100, 100, 8, L"?");
        CreateGameButton(hWnd, 290, 290, 100, 100, 9, L"?");

        if (isPlayerX == true)
        {
            SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_SETCHECK, BST_CHECKED, 0);
        }
        else
        {
            SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
        }
        return TRUE;

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);

        if (id >= 1 && id <= 9 && gameButtonText[id - 1] == L"?")
        {
            UpdateGameButtonText(hWnd, id - 1);
            moves++;

            if (CheckForWinner())
            {
                MessageBox(hWnd, isPlayerX ? L"Player O wins" : L"Player X wins", L"Game Over", MB_OK);
                ResetGameBoard(hWnd);
            }
            else if (moves == 9)
            {
                MessageBox(hWnd, L"Draw", L"Game Over", MB_OK);
                ResetGameBoard(hWnd);
            }
        }

        if (id == IDC_BUTTON1)
        {
            ResetGameBoard(hWnd);
        }

        if (id == IDC_CHECK1)
        {
            if (moves > 0)
            {
                return TRUE;
            }
            isPlayerX = (SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED);
        }

        return TRUE;
    }

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}

void CreateGameButton(HWND hWnd, int x, int y, int width, int height, int id, LPCWSTR text)
{
    CreateWindow(
        L"BUTTON", text, WS_CHILD | WS_VISIBLE | BS_CENTER | WS_BORDER,
        x, y, width, height, hWnd,
        (HMENU)id, GetModuleHandle(NULL), NULL);
}

void UpdateGameButtonText(HWND hWnd, int id)
{
    if (gameButtonText[id] != L"?") return;

    gameButtonText[id] = isPlayerX ? L"X" : L"O";
    HWND hButton = GetDlgItem(hWnd, id + 1);
    SetWindowText(hButton, gameButtonText[id].c_str());

    isPlayerX = false;
}

int winCombinations[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
};

bool CheckForWinner()
{
    for (int i = 0; i < 8; i++)
    {
        int* combo = winCombinations[i];

        if (gameButtonText[combo[0]] != L"?" &&
            gameButtonText[combo[0]] == gameButtonText[combo[1]] &&
            gameButtonText[combo[0]] == gameButtonText[combo[2]])
        {
            return true;
        }
    }
    return false;
}

void ResetGameBoard(HWND hWnd)
{
    for (int i = 0; i < 9; i++)
    {
        gameButtonText[i] = L"?";
        HWND hButton = GetDlgItem(hWnd, i + 1);
        SetWindowText(hButton, L"?");
    }

    isPlayerX = (SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED);
    moves = 0;
}
