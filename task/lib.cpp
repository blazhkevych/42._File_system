#include <iostream>
#include <windows.h>
#include <io.h>
using namespace std;

// Меню
void Menu(char ptr[][16], int row)
{
	for (int i = 0; i < row; i++)
	{
		cout << ptr[i];
		cout << endl;
	}
}

// Копировать папку
void CopyFolder(char* oldPath, char* newPath)
{
	char* find = new char[MAX_PATH];
	strcpy_s(find, MAX_PATH, oldPath);
	strcat_s(find, MAX_PATH, "\\*");
	_finddata_t* f = new _finddata_t;
	int handle = _findfirst(find, f);
	int result = handle;
	while (result != -1)
	{
		if (f->attrib & _A_SUBDIR) // если папка, то ...
		{
			strcpy_s(find, MAX_PATH, oldPath);
			strcat_s(find, MAX_PATH, "\\");
			strcat_s(find, MAX_PATH, f->name);
			size += DirectorySize(find); // тут по идее должна создаватся папка по новому адресу
		}
	}

}

// Переместить папку
void MoveFolder(char* oldPath, char* newPath)
{

}

// Удалить папку
void DeleteFolder(char* path)
{

}