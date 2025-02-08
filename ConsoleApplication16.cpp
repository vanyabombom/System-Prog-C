#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tchar.h>
using namespace std;

bool isPalindrome(_TCHAR* str)
{
	int lenght = _tcslen(str);
	for (int i = 0; i < lenght / 2; i++)
	{
		if (str[i] != str[lenght - i - 1])
		{
			return false;
		}
	}
	return true;
}

int countWords(_TCHAR* str)
{
	int count = 0;
	bool inWord = false;

	for (int i = 0; str[i] != _T('\0'); i++)
	{
		if (str[i] != _T(' '))
		{
			if (inWord == false)
			{
				count++;
				inWord = true;
			}
		}
		else
		{
			inWord = false;
		}
	}

	return count;
}

void searchAndReplace(_TCHAR* text, _TCHAR* find, _TCHAR* replace)
{
	_TCHAR* ind = _tcsstr(text, find);
	if (ind == false)
	{
		return;
	}
	_TCHAR newText[255] = _TEXT("");
	_tcsncat(newText, text, ind - text);
	_tcscat(newText, replace);
	_tcscat(newText, ind + _tcslen(find));

	_tcscpy(text, newText);
	wcout << text << endl;
}

int main()
{
	_TCHAR szBuf[255];
	wcout << L"Enter string: " << endl;
	wcin.getline(szBuf, 255);

	if (isPalindrome(szBuf) == true)
	{
		wcout << L"Palindrome." << endl;
	}
	else
	{
		wcout << L"Not Palindrome" << endl;
	}

	int counter = countWords(szBuf);
	wcout << L"Words number: " << counter << endl;

	_TCHAR text[255] = _TEXT("Hello, world!");
	_TCHAR find[] = _TEXT("Hello");
	_TCHAR replace[] = _TEXT("byeeee");
	searchAndReplace(text, find, replace);
}