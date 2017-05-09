#include "strings.h"
#include <algorithm>

namespace QuestNavigator {
	// �������� ������� � ������ � ����� ������
	string trim(string text)
	{
		size_t pos = text.find_first_not_of(' ');
		if (pos == string::npos)
			return "";
		string trimmed = text.substr(pos);
		pos = text.find_last_not_of(' ');
		if (pos == string::npos)
			return "";
		trimmed = text.substr(0, pos + 1);
		return trimmed;
	}

	// ���������� �� ������ � ������������������ ��������
	bool startsWith(string source, string prefix)
	{
		return (source.length() > 0) &&
			(prefix.length() > 0) &&
			(source.find(prefix) == 0);
	}

	// ������������ �� ������ ������������������� ��������
	bool endsWith(string source, string suffix)
	{
		return (source.length() > 0) &&
			(suffix.length() > 0) &&
			(source.rfind(suffix) == source.length() - suffix.length());
	}

	// ��������������� �������� ����� ����� � ������ ("\" -> "/")
	string backslashToSlash(string text)
	{
		return replaceAll(text, '\\', '/');
	}

	// ��������������� ������ ����� ����� � �������� ("/" -> "\")
	string slashToBackslash(string text)
	{
		return replaceAll(text, '/', '\\');
	}

	// �������� ��� ��������� ������� � ������
	string replaceAll(string source, char pattern, char replacement)
	{
		replace(source.begin(), source.end(), pattern, replacement);
		return source;
	}
	// �������� ��� ��������� ��������� � ������
	void replaceAll(string &s, const string &search, const string &replace)
	{
		for (size_t pos = 0; ; pos += replace.length()) {
			// Locate the substring to replace
			pos = s.find(search, pos);
			if (pos == string::npos)
				break;
			// Replace by erasing and inserting
			s.erase(pos, search.length());
			s.insert(pos, replace);
		}
	}
	// �������� "&" �� "&amp;", �� ������ "HTML entities".
	void replaceAmp(string &s)
	{
		// /&(?:[a-z\d]+|#\d+|#x[a-f\d]+);/i
		// 1. ������� "&".
		// 2. ��������� ��������� ������. 
		// ��� ������ ���� �������� ������ ���������� ��������, ���� �������.
		// 3. ��������� ��������� �������, ���� �� ���������� ";".
		// 4. ���� ������������������ �������� �� ������������� ��������, �������� "&" �� "&amp;".
		string az = "abcdefghijklmnopqrstuvwxyz";
		string digits = "0123456789";
		string validFirstEntityChar = az + "#";
		string validMainEntityChar = az + digits;
		size_t last_pos = 0;
		size_t pos = 0;
		size_t t = 0;
		size_t len = s.length();
		bool entityPossible = false;
		string replaced = "";
		while (pos < len) {
			last_pos = pos;
			pos = s.find('&', pos);
			if (pos != string::npos) {
				// �������� ������.
				// ��� HTML-entity, � ������ ����� "&" ������ ���������� ������� ��� �������.
				entityPossible = pos < (len - 2);
				if (entityPossible) {
					// ������ �������� ����� "&" 
					// ������ ���� �������� ������ ���������� ��������, ���� �������.
					entityPossible = validFirstEntityChar.find(s[pos + 1]) != string::npos;
					if (entityPossible) {
						// ����� ����� ����������� ����� � ������� ���������� �������� 
						// � ������������ ����������.
						t = s.find_first_not_of(validMainEntityChar, pos + 2);
						entityPossible = t != string::npos;
						if (entityPossible) {
							// ��������� �������� ������ ���� ";".
							entityPossible = s[t] == ';';
						}
					}
				}
				// �� ����������, 
				// ��������� �� � ������ 
				// ���������� ������������������ HTML-entity.

				// ���������� ����� �� last_pos �� ��������� "&".
				replaced += s.substr(last_pos, pos - last_pos);

				// �������� � ������������������ ������.
				if (!entityPossible) {
					// ��� �� HTML-entity.
					// ��������� ������.
					replaced += "&amp;";
					pos = pos + 1;
				}
				else {
					// ��� HTML-entity.
					// ���������� ����� "��� ����".
					replaced += s.substr(pos, t - pos);
					pos += t - pos;
				}
			}
			else {
				// �������� ������.
				// ���������� ���������� �����.
				replaced += s.substr(last_pos, len - last_pos);
				break;
			}
		}
		s = replaced;
	}
	// �������� �������� �����, �� ������ ��� HTML-�����.
	void replaceNewlines(string &s)
	{
		// 1. ���� ����������� ������ ����.
		// 2. ���� �� �������, ������ ������ �� ���� ���������� ������. ����� �� �����.
		// 3. ���� �������, ������ ������ �� ������ �� ������.
		// 4. ���� ����������� ������.
		// 5. ���� ����������� ������ �� �������, ������� �� �����.
		// 6. ������� ��������������� �� ��������� ������ ����� ����������� ������.
		// 7. ������� �� �. 1.
		string startTag = "<";
		string endTag = ">";
		size_t last_pos = 0;
		size_t pos = 0;
		size_t len = s.length();
		string replaced = "";
		string token = "";
		while (pos < len) {
			last_pos = pos;
			// ���� ����������� ������.
			pos = s.find(startTag, pos);
			bool bTag = pos != string::npos;
			// ����������, �� ������ ������� ������ ������.
			token = bTag ? s.substr(last_pos, pos - last_pos) : s.substr(last_pos);
			// ��������� ������.
			replaceAll(token, "\r\n", "<br />");
			replaceAll(token, "\r", "<br />");
			replaceAll(token, "\n", "<br />");
			// ���������� ������������ ����� ������.
			replaced += token;
			// ���� ��� �� ������, ��������� ����.
			if (!bTag)
				break;
			// ���� ����������� ������.
			last_pos = pos;
			pos = s.find(endTag, pos);
			if (pos != string::npos) {
				// ������������� ������� �� ��������� �� ����������� ������� ������.
				pos++;
				// ���������� ���� ����.
				replaced += s.substr(last_pos, pos - last_pos);
			}
			else {
				// �������� ������.
				// ���������� ���������� �����.
				replaced += s.substr(last_pos);
				break;
			}
		}
		s = replaced;
	}
	// ��������� ��� ������� � ������� �������
	string toUpper(string str)
	{
		string strUpper = str;
		transform(str.begin(), str.end(), strUpper.begin(), ::toupper);
		return strUpper;
	}
	// ��������� ��� ������� � ������ �������
	string toLower(string str)
	{
		string strLower = str;
		transform(str.begin(), str.end(), strLower.begin(), ::tolower);
		return strLower;
	}

	// �������������� URL ������ ���� <a href="EXEC:...">...</a> � ��� QSP
	string unescapeHtml(string text)
	{
		if (text == "")
			return "";
		replaceAll(text, "&quot;", "\"");
		replaceAll(text, "&#39;", "'");
		replaceAll(text, "&lt;", "<");
		replaceAll(text, "&gt;", ">");
		replaceAll(text, "&amp;", "&");
		return text;
	}

	// �������� �������������� URL � "�����" ���
	string decodeUrl(string url)
	{
		string decoded = "";
		char ch;
		int i, ii;
		for (i = 0; i < (int)url.length(); i++) {
			if (int(url[i]) == 37) {
				sscanf(url.substr(i + 1, 2).c_str(), "%x", &ii);
				ch = static_cast<char>(ii);
				decoded += ch;
				i = i + 2;
			}
			else {
				decoded += url[i];
			}
		}
		return decoded;
	}

	// ��������������� ����� ����� � ������.
	string intToString(int value)
	{
		char buff[100];
		sprintf(buff, "%d", value);
		string sInteger = buff;
		return sInteger;
	}
}