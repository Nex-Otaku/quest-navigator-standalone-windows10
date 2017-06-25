#pragma once

#include <string>
#include <vector>

using namespace std;

namespace QuestNavigator {
	// Утилиты для работы с файловой системой

	// Получаем URL из полного пути к файлу
	string getUrlFromFilePath(string filePath);
	// URL к содержимому
	//string getContentUrl();
	// Проверяем файл на существование и читаемость
	bool fileExists(string path);
	// Проверяем папку на существование и читаемость
	bool dirExists(string path);
	// Получаем путь к папке плеера
	string getPlayerDir();
	// Преобразовываем путь к файлу сохранения
	string getRealSaveFile(string file);
	// Меняем слэши в пути к файлу в зависимости от системы
	string getRightPath(string path);
	// Преобразовываем относительный путь в абсолютный
	string relativePathToAbsolute(string relative);
	// Приводим путь к каноничной форме.
	string canonicalizePath(string path);
	// Загружаем файл в память
	bool loadFileToBuffer(string path, void** bufferPtr, int* bufferLength);
	// Создаём папки
	bool buildDirectoryPath(string path);
	// Удаляем папку и всё её содержимое.
	bool deleteDirectory(string path);
	// Возвращаем список файлов
	bool getFilesList(string directory, string mask, vector<string>& list);
	// Возвращаем список папок
	bool getFoldersList(string directory, vector<string>& list);
	// Копируем файл
	bool copyFile(string from, string to);
	// Копируем дерево файлов
	bool copyFileTree(string from, string to);
	bool copyFileTree(string from, string to, string mask);
	// Ищем первый файл "*.qsp" в папке.
	bool findGameFile(string dir, string &gameFileName);
}
