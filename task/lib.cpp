﻿#include <iostream>
#include <windows.h>
#include <io.h>
#include <direct.h> // для _mkdir

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

bool rootDirFolder = true; // для создания корневого каталога

// Копировать папку
void CopyFolder(char* oldPath, char* newPath)
{
	char* find = new char[MAX_PATH];
	strcpy_s(find, MAX_PATH, oldPath);
	strcat_s(find, MAX_PATH, "\\*");
	_finddata_t* f = new _finddata_t;
	int handle = _findfirst(find, f);
	int result = handle;

	if (rootDirFolder) // для создания корневого каталога(один раз)
	{
		char* RootDirName = new char[MAX_PATH];
		char* pch = strrchr(oldPath, '\\'); // последнее вхождение "\" в строке старого адреса

		strcpy_s(RootDirName, MAX_PATH, newPath);
		strcat_s(RootDirName, MAX_PATH, pch); // получен новый путь к корневой папке
		if (_mkdir(RootDirName) == -1) // создание вложенной папки, если возвращает 0
		{
			perror("Error");
			system("pause");
			system("cls");
			exit(0);
		}
		strcat_s(newPath, MAX_PATH, pch);
		rootDirFolder = false;
		delete[]RootDirName;
	}

	while (result != -1)
	{
		if (strcmp(f->name, ".") == 0 || strcmp(f->name, "..") == 0)
		{
			result = _findnext(handle, f);
			continue;
		}
		if (f->attrib & _A_SUBDIR) // если папка, то ...
		{
			strcpy_s(find, MAX_PATH, newPath);
			strcat_s(find, MAX_PATH, "\\");
			strcat_s(find, MAX_PATH, f->name); // получен новый путь к вложенной папке
			if (_mkdir(find) == -1) // создание вложенной папки, если возвращает 0
			{
				perror("Error");
				system("pause");
				system("cls");
				exit(0);
			}
			// продолжить сравнивать 2 запущенных программы, мою и преподавателя, пошагово (есть проблема с передачей адреса в внутренний вызов функциия копифолдер)
			/*strcat_s(oldPath, MAX_PATH, "\\");
			strcat_s(oldPath, MAX_PATH, f->name);
			strcat_s(newPath, MAX_PATH, "\\");
			strcat_s(newPath, MAX_PATH, f->name);*/

			CopyFolder(find, newPath);
		}
		else
		{
			FILE* readFile = nullptr;
			char fileNameOld[MAX_PATH];
			strcpy_s(fileNameOld, MAX_PATH, oldPath);
			strcat_s(fileNameOld, MAX_PATH, "\\");
			strcat_s(fileNameOld, MAX_PATH, f->name);
			fopen_s(&readFile, fileNameOld, "rb");
			if (readFile == nullptr)
			{
				perror("Error opening");
				exit(0);
			}
			int lenght = _filelength(_fileno(readFile)); // _fileno (получает дескриптор), _filelength (дает размер файла в байтах)
			char* buffer = new char[lenght]; // буфер на вычитку файла
			memset(buffer, 0, lenght);
			FILE* writeFile = nullptr;

			char fileNameNew[MAX_PATH];
			strcpy_s(fileNameNew, MAX_PATH, newPath);
			strcat_s(fileNameNew, MAX_PATH, "\\");
			strcat_s(fileNameNew, MAX_PATH, f->name);

			fopen_s(&writeFile, fileNameNew, "wb");
			fwrite(buffer, lenght, 1, writeFile);
			fclose(writeFile);
			delete[]buffer;
			fclose(readFile);
		}
		result = _findnext(handle, f);
	}
	_findclose(handle);
	delete[] find;
	delete f;
}

// Переместить папку
void MoveFolder(char* oldPath, char* newPath)
{

}

// Удалить папку
void DeleteFolder(char* path)
{

}