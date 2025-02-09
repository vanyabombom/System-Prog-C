#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
using namespace std;

int vowelsCounter(_TCHAR* text) {
    _TCHAR vowels[] = { 'a', 'e' , 'o' , 'u' , 'i', 'y'};
    int counter = 0;
    for (int i = 0; i < _tcslen(text); i++)
    {
        if ((text[i] != ' ' && text[i + 1] != ' ') || (i == _tcslen(text) - 1 && text[i] != ' ')) 
        {
            for (_TCHAR symbol : vowels) 
            {
                if (text[i] == symbol)
                {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int main() 
{
    _TCHAR text[100] = _TEXT("");
    _fgetts(text, 100, stdin);

    int counter = vowelsCounter(text);
    cout << counter;
}