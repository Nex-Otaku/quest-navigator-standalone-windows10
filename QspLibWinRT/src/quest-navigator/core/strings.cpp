#include "strings.h"
#include <algorithm>

namespace QuestNavigator {
	// Отсекаем пробелы в начале и конце строки
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

	// Начинается ли строка с последовательности символов
	bool startsWith(string source, string prefix)
	{
		return (source.length() > 0) &&
			(prefix.length() > 0) &&
			(source.find(prefix) == 0);
	}

	// Оканчивается ли строка последовательностью символов
	bool endsWith(string source, string suffix)
	{
		return (source.length() > 0) &&
			(suffix.length() > 0) &&
			(source.rfind(suffix) == source.length() - suffix.length());
	}

	// Преобразовываем обратные косые черты в прямые ("\" -> "/")
	string backslashToSlash(string text)
	{
		return replaceAll(text, '\\', '/');
	}

	// Преобразовываем прямые косые черты в обратные ("/" -> "\")
	string slashToBackslash(string text)
	{
		return replaceAll(text, '/', '\\');
	}

	// Заменяем все вхождения символа в строке
	string replaceAll(string source, char pattern, char replacement)
	{
		replace(source.begin(), source.end(), pattern, replacement);
		return source;
	}
	// Заменяем все вхождения подстроки в строке
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
	// Заменяем "&" на "&amp;", не трогая "HTML entities".
	void replaceAmp(string &s)
	{
		// /&(?:[a-z\d]+|#\d+|#x[a-f\d]+);/i
		// 1. Находим "&".
		// 2. Проверяем следующий символ. 
		// Это должен быть строчный символ латинского алфавита, либо решётка.
		// 3. Проверяем остальные символы, пока не встретится ";".
		// 4. Если последовательность символов не удовлетворяет условиям, заменяем "&" на "&amp;".
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
				// Возможна замена.
				// Для HTML-entity, в запасе после "&" должно оставаться минимум два символа.
				entityPossible = pos < (len - 2);
				if (entityPossible) {
					// Первым символом после "&" 
					// должен быть строчный символ латинского алфавита, либо решётка.
					entityPossible = validFirstEntityChar.find(s[pos + 1]) != string::npos;
					if (entityPossible) {
						// После этого допускаются цифры и символы латинского алфавита 
						// в произвольном количестве.
						t = s.find_first_not_of(validMainEntityChar, pos + 2);
						entityPossible = t != string::npos;
						if (entityPossible) {
							// Следующим символом должен быть ";".
							entityPossible = s[t] == ';';
						}
					}
				}
				// Мы определили, 
				// находится ли в строке 
				// правильная последовательность HTML-entity.

				// Записываем часть от last_pos до вхождения "&".
				replaced += s.substr(last_pos, pos - last_pos);

				// Работаем с проанализированным куском.
				if (!entityPossible) {
					// Это не HTML-entity.
					// Выполняем замену.
					replaced += "&amp;";
					pos = pos + 1;
				}
				else {
					// Это HTML-entity.
					// Записываем кусок "как есть".
					replaced += s.substr(pos, t - pos);
					pos += t - pos;
				}
			}
			else {
				// Заменять нечего.
				// Записываем оставшийся кусок.
				replaced += s.substr(last_pos, len - last_pos);
				break;
			}
		}
		s = replaced;
	}
	// Заменяем переводы строк, но только вне HTML-тегов.
	void replaceNewlines(string &s)
	{
		// 1. Ищем открывающую скобку тега.
		// 2. Если не найдена, делаем замену по всей оставшейся строке. Выход из цикла.
		// 3. Если найдена, делаем замену по строке до скобки.
		// 4. Ищем закрывающую скобку.
		// 5. Если закрывающая скобка не найдена, выходим из цикла.
		// 6. Позиция устанавливается на следующий символ после закрывающей скобки.
		// 7. Переход на п. 1.
		string startTag = "<";
		string endTag = ">";
		size_t last_pos = 0;
		size_t pos = 0;
		size_t len = s.length();
		string replaced = "";
		string token = "";
		while (pos < len) {
			last_pos = pos;
			// Ищем открывающую скобку.
			pos = s.find(startTag, pos);
			bool bTag = pos != string::npos;
			// Определяем, до какого символа делать замену.
			token = bTag ? s.substr(last_pos, pos - last_pos) : s.substr(last_pos);
			// Выполняем замену.
			replaceAll(token, "\r\n", "<br />");
			replaceAll(token, "\r", "<br />");
			replaceAll(token, "\n", "<br />");
			// Записываем обработанную часть текста.
			replaced += token;
			// Если тег не найден, прерываем цикл.
			if (!bTag)
				break;
			// Ищем закрывающую скобку.
			last_pos = pos;
			pos = s.find(endTag, pos);
			if (pos != string::npos) {
				// Устанавливаем позицию на следующий за закрывающей скобкой символ.
				pos++;
				// Записываем тело тега.
				replaced += s.substr(last_pos, pos - last_pos);
			}
			else {
				// Заменять нечего.
				// Записываем оставшийся кусок.
				replaced += s.substr(last_pos);
				break;
			}
		}
		s = replaced;
	}
	// Переводим все символы в верхний регистр
	string toUpper(string str)
	{
		string strUpper = str;
		transform(str.begin(), str.end(), strUpper.begin(), ::toupper);
		return strUpper;
	}
	// Переводим все символы в нижний регистр
	string toLower(string str)
	{
		string strLower = str;
		transform(str.begin(), str.end(), strLower.begin(), ::tolower);
		return strLower;
	}

	// Преобразование URL ссылки вида <a href="EXEC:...">...</a> в код QSP
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

	// Обратное преобразование URL в "сырой" вид
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

	// Преобразовываем целое число в строку.
	string intToString(int value)
	{
		char buff[100];
		sprintf(buff, "%d", value);
		string sInteger = buff;
		return sInteger;
	}
}