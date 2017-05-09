#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {

	// ������� ��� ��������� �����

	// �������� ������� � ������ � ����� ������
	string trim(string text);
	// ���������� �� ������ � ������������������ ��������
	bool startsWith(string source, string prefix);
	// ������������ �� ������ ������������������� ��������
	bool endsWith(string source, string suffix);
	// ��������������� �������� ����� ����� � ������ ("\" -> "/")
	string backslashToSlash(string text);
	// ��������������� ������ ����� ����� � �������� ("/" -> "\")
	string slashToBackslash(string text);
	// �������� ��� ��������� ��������� � ������
	string replaceAll(string source, char pattern, char replacement);
	void replaceAll(string &s, const string &search, const string &replace);
	// �������� "&" �� "&amp;", �� ������ "HTML entities".
	void replaceAmp(string &s);
	// �������� �������� �����, �� ������ ��� HTML-�����.
	void replaceNewlines(string &s);
	// ��������� ��� ������� � ������� �������
	string toUpper(string str);
	// ��������� ��� ������� � ������ �������
	string toLower(string str);
	// �������������� URL ������ ���� <a href="EXEC:...">...</a> � ��� QSP
	string unescapeHtml(string text);
	// �������� �������������� URL � "�����" ���
	string decodeUrl(string url);
	// ��������������� ����� ����� � ������.
	string intToString(int value);
}