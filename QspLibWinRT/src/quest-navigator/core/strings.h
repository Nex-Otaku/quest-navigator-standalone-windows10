#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {

	// Утилиты для обработки строк

	// Отсекаем пробелы в начале и конце строки
	string trim(string text);
	// Начинается ли строка с последовательности символов
	bool startsWith(string source, string prefix);
	// Оканчивается ли строка последовательностью символов
	bool endsWith(string source, string suffix);
	// Преобразовываем обратные косые черты в прямые ("\" -> "/")
	string backslashToSlash(string text);
	// Преобразовываем прямые косые черты в обратные ("/" -> "\")
	string slashToBackslash(string text);
	// Заменяем все вхождения подстроки в строке
	string replaceAll(string source, char pattern, char replacement);
	void replaceAll(string &s, const string &search, const string &replace);
	// Заменяем "&" на "&amp;", не трогая "HTML entities".
	void replaceAmp(string &s);
	// Заменяем переводы строк, но только вне HTML-тегов.
	void replaceNewlines(string &s);
	// Переводим все символы в верхний регистр
	string toUpper(string str);
	// Переводим все символы в нижний регистр
	string toLower(string str);
	// Преобразование URL ссылки вида <a href="EXEC:...">...</a> в код QSP
	string unescapeHtml(string text);
	// Обратное преобразование URL в "сырой" вид
	string decodeUrl(string url);
	// Преобразовываем целое число в строку.
	string intToString(int value);
}