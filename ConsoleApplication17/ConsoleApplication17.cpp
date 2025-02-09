#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>

using namespace std;

void vowelsWordCounter(_TCHAR* text) {
    _TCHAR vowels[] = { 'a', 'e' , 'o' , 'u' , 'i', 'y', 'f', 'g' };
    int counter = 0;
    for (int i = 0; i < _tcslen(text); i++) {
        if ((text[i] != ' ' and text[i + 1] != ' ') or (i == _tcslen(text) - 1 and text[i] != ' ')) {
            for (_TCHAR c : vowels) {
                if (text[i] == c) counter++;
            }
        }
    }
    cout << counter << endl;
}

int main() {
    setlocale(LC_ALL, "");

    _TCHAR text[256] = _TEXT("");
    _fgetts(text, 256, stdin);

    vowelsWordCounter(text);
}