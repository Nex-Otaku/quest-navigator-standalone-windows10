#pragma once

#include <string>
#include <vector>

using namespace std;

namespace QuestNavigator {
	// ������� ��� ������ � �������� ��������

	// �������� URL �� ������� ���� � �����
	string getUrlFromFilePath(string filePath);
	// URL � �����������
	string getContentUrl();
	// ��������� ���� �� ������������� � ����������
	bool fileExists(string path);
	// ��������� ����� �� ������������� � ����������
	bool dirExists(string path);
	// �������� ���� � ����� ������
	string getPlayerDir();
	// ��������������� ���� � ����� ����������
	string getRealSaveFile(string file);
	// ������ ����� � ���� � ����� � ����������� �� �������
	string getRightPath(string path);
	// ��������������� ������������� ���� � ����������
	string relativePathToAbsolute(string relative);
	// �������� ���� � ���������� �����.
	string canonicalizePath(string path);
	// ��������� ���� � ������
	bool loadFileToBuffer(string path, void** bufferPtr, int* bufferLength);
	// ������ �����
	bool buildDirectoryPath(string path);
	// ������� ����� � �� � ����������.
	bool deleteDirectory(string path);
	// ���������� ������ ������
	bool getFilesList(string directory, string mask, vector<string>& list);
	// ���������� ������ �����
	bool getFoldersList(string directory, vector<string>& list);
	// �������� ����
	bool copyFile(string from, string to);
	// �������� ������ ������
	bool copyFileTree(string from, string to);
	bool copyFileTree(string from, string to, string mask);
	// ���� ������ ���� "*.qsp" � �����.
	bool findGameFile(string dir, string &gameFileName);
}
