#include "files.h"
#include <Windows.h>
#include "configuration.h"
#include "utils.h"
#include "dialogs.h"

namespace QuestNavigator {

	// Получаем URL из полного пути к файлу
	string getUrlFromFilePath(string filePath)
	{
		//TCHAR szString[1024];
		//PTSTR szUrl = szString;
		//wstring wFilePath = widen(filePath);
		//PTSTR FileName = (PTSTR)wFilePath.c_str();
		//DWORD sUrl = 1024;
		//HRESULT res = UrlCreateFromPath(FileName, szUrl, &sUrl, NULL);
		//if (res != S_OK) {
		//	showError("Не удалось преобразовать в URL путь вида: [" + filePath + "]");
		//	return "";
		//}
		//wstring wUrl = szUrl;
		//string url = narrow(wUrl);
		//return url;
	}

	// URL к содержимому
	string getContentUrl()
	{
		string contentPath = Configuration::getString(ecpSkinFilePath);
		return getUrlFromFilePath(contentPath);
	}

	// Проверяем файл на существование и читаемость
	bool fileExists(string path)
	{
		DWORD dwAttrib = GetFileAttributes(widen(path).c_str());
		return ((dwAttrib != INVALID_FILE_ATTRIBUTES) &&
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}

	// Проверяем папку на существование и читаемость
	bool dirExists(string path)
	{
		DWORD dwAttrib = GetFileAttributes(widen(path).c_str());
		return ((dwAttrib != INVALID_FILE_ATTRIBUTES) &&
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}

	// Получаем путь к папке плеера
	string getPlayerDir()
	{
		//TCHAR buffer[MAX_PATH];
		//PTSTR szDir = buffer;

		//DWORD res = GetModuleFileName(NULL, szDir, (DWORD)MAX_PATH);
		//if (res == 0) {
		//	showError("Не могу прочесть путь к плееру");
		//	return "";
		//}
		//if (res == MAX_PATH) {
		//	showError("Путь к плееру не помещается в буфер");
		//	return "";
		//}

		//// Удаляем имя исполняемого файла, оставляем только путь к нему, без слэша в конце.
		//res = PathRemoveFileSpec(szDir);
		//if (res == 0) {
		//	showError("Ошибка при обработке пути к плееру");
		//	return "";
		//}

		//wstring wDir = szDir;
		//string dir = narrow(wDir);
		//return dir;
	}

	// Преобразовываем путь к файлу сохранения.
	string getRealSaveFile(string file)
	{
		// "D:\MySaveDirForCoolGame"
		string saveDir = Configuration::getString(ecpSaveDir);
		// "D:\CoolGame\saves\save1.sav"
		string originalSaveFilePath = getRightPath(file);
		// "D:\CoolGame\game.qsp"
		string gameFilePath = getRightPath(Configuration::getString(ecpGameFilePath));
		// "game.qsp"
		string gameFileName = Configuration::getString(ecpGameFileName);
		// "D:\CoolGame\"
		string gameDir = gameFilePath.substr(0, gameFilePath.length() - gameFileName.length());
		// "saves\save1.sav"
		string relativeSavePath = originalSaveFilePath.substr(gameDir.length());
		// "D:\MySaveDirForCoolGame\saves\save1.sav"
		string saveFile = getRightPath(saveDir + PATH_DELIMITER + relativeSavePath);
		return saveFile;
	}

	// Меняем слэши в пути к файлу в зависимости от системы
	string getRightPath(string path)
	{
		// Вызывая эту функцию для обработки пути,
		// мы будем уверены что слэши всегда направлены в нужную сторону.
		string result = path;
#ifdef WIN32
		result = slashToBackslash(path);
#endif
		return result;
	}

	// Преобразовываем относительный путь в абсолютный
	string relativePathToAbsolute(string relative)
	{
		//// Если путь не относительный, сразу возвращаем.
		//wstring wRelative = widen(relative);
		//BOOL res = PathIsRelative(wRelative.c_str());
		//if (res == FALSE) {
		//	return relative;
		//}

		//// Получаем рабочую директорию.
		//TCHAR buffer[MAX_PATH];
		//PTSTR szDir = buffer;
		//DWORD curDirLen = GetCurrentDirectory((DWORD)MAX_PATH, szDir);
		//if (curDirLen == 0) {
		//	showError("Не могу прочесть текущую директорию");
		//	return "";
		//}
		//if (curDirLen >= MAX_PATH) {
		//	showError("Путь к текущей директории не помещается в буфер");
		//	return "";
		//}

		//// Совмещаем путь к рабочей директории и относительный путь.
		//TCHAR bufferAbsolute[MAX_PATH];
		//PTSTR szAbsolute = bufferAbsolute;
		//PTSTR szCombined = PathCombine(szAbsolute, szDir, wRelative.c_str());
		//if (szCombined == NULL) {
		//	showError("Не удалось получить абсолютный путь");
		//	return "";
		//}
		//wstring wAbsolute = szCombined;
		//string absolute = narrow(wAbsolute);

		//return absolute;
	}

	// Приводим путь к каноничной форме.
	string canonicalizePath(string path)
	{
		//wstring wPathSrc = widen(path);
		//TCHAR buffer[MAX_PATH];
		//PTSTR szCanonicalizedPath = buffer;
		//BOOL res = PathCanonicalize(buffer, wPathSrc.c_str());
		//if (res == FALSE) {
		//	showError("Не удалось привести путь к каноническому виду");
		//	return "";
		//}
		//wstring wCanonicalizedPath = szCanonicalizedPath;
		//string result = narrow(wCanonicalizedPath);
		//return result;
	}

	// Загружаем файл в память
	bool loadFileToBuffer(string path, void** bufferPtr, int* bufferLength)
	{
		//// Открываем файл для чтения
		//wstring wPath = widen(path);
		//HANDLE hFile = CreateFile(wPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//if (hFile == INVALID_HANDLE_VALUE)
		//	return false;
		//// Узнаём размер файла
		//DWORD dwFileSize = GetFileSize(hFile, NULL);
		//if (dwFileSize == INVALID_FILE_SIZE) {
		//	CloseHandle(hFile);
		//	return false;
		//}
		//// В буфере будет завершающий нулевой байт.
		//int totalBufferLength = dwFileSize + 1;
		//// Выделяем блок памяти
		//char* pFileChunk = NULL;
		//// Может не хватить памяти (если файл слишком большой)
		//try {
		//	pFileChunk = new char[totalBufferLength];
		//} catch (...) {
		//	CloseHandle(hFile);
		//	return false;
		//}
		//// Читаем файл в память
		//DWORD dwBytesRead = 0;
		//BOOL res = ReadFile(hFile, pFileChunk, dwFileSize, &dwBytesRead, NULL);
		//if ((res == FALSE) || (dwBytesRead != dwFileSize)) {
		//	CloseHandle(hFile);
		//	delete pFileChunk;
		//	return false;
		//}
		//// Закрываем файл
		//res = CloseHandle(hFile);
		//if (res == 0) {
		//	delete pFileChunk;
		//	return false;
		//}
		//// Записываем завершающий нулевой байт в буфер, для корректного чтения.
		//pFileChunk[dwFileSize] = 0;
		//// Возвращаем результат
		//*bufferPtr = pFileChunk;
		//*bufferLength = totalBufferLength;
		//// Не забываем освободить память вызовом "delete" после использования!
		//return true;
	}

	// Создаём папки
	bool buildDirectoryPath(string path)
	{
		//if (dirExists(path))
		//	return true;
		//wstring wPath = widen(path);
		//int res = SHCreateDirectoryEx(NULL, wPath.c_str(), NULL);
		//return res == ERROR_SUCCESS;
	}

	// Удаляем папку со всем содержимым.
	bool deleteDirectory(string path)
	{
		//if (!dirExists(path))
		//	return true;
		//wstring wPath = widen(path);

		//// Making the directory name double null terminated.
		//int nFolderPathLen = (int)wPath.length();
		//WCHAR *pszFrom = new WCHAR[nFolderPathLen + 2];
		//wcscpy(pszFrom, wPath.c_str());
		//pszFrom[nFolderPathLen] = 0;
		//pszFrom[++nFolderPathLen] = 0;
		//SHFILEOPSTRUCT stSHFileOpStruct = { 0 };
		//// Delete operation.
		//stSHFileOpStruct.wFunc = FO_DELETE;
		//// Folder name as double null terminated string.
		//stSHFileOpStruct.pFrom = pszFrom;
		//// Do not prompt the user.
		//stSHFileOpStruct.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
		//// Will read this to check for any operation is aborted.
		//stSHFileOpStruct.fAnyOperationsAborted = FALSE;
		//int nFileDeleteOprnRet = SHFileOperation(&stSHFileOpStruct);
		//delete[] pszFrom;

		//return (0 == nFileDeleteOprnRet) && (stSHFileOpStruct.fAnyOperationsAborted == FALSE);
	}

	// Возвращаем список файлов либо папок
	bool _getFilesOrFoldersList(string directory, string mask, vector<string>& list, bool bFileMode)
	{
		vector<string> result;

		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		DWORD dwError = 0;

		wstring wDir = widen(getRightPath(directory + PATH_DELIMITER + mask));
		if (wDir.size() + 1 > MAX_PATH) {
			showError("Слишком длинный путь");
			return false;
		}
		LPCWSTR szDir = wDir.c_str();

		string label = bFileMode ? "файла" : "папки";

		// Find the first file in the directory.

		hFind = FindFirstFile(szDir, &ffd);

		if (INVALID_HANDLE_VALUE == hFind)
		{
			dwError = GetLastError();
			if (dwError == ERROR_FILE_NOT_FOUND) {
				list = result;
				return true;
			}
			else {
				showError("Не удалось осуществить поиск " + label + " в папке " + directory + " по заданной маске " + mask);
				return false;
			}
		}

		// List all the files in the directory with some info about them.

		do
		{
			if (!bFileMode == ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)) {
				string fileName = narrow(ffd.cFileName);
				if ((fileName != ".") && (fileName != ".."))
					result.push_back(fileName);
			}
		} while (FindNextFile(hFind, &ffd) != 0);

		dwError = GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
		{
			showError("Не удалось осуществить повторный поиск " + label + " в папке " + directory + " по заданной маске " + mask);
			return false;
		}

		BOOL res = FindClose(hFind);
		if (res == 0) {
			showError("Не удалось высвободить дескриптор поиска");
			return false;
		}

		list = result;
		return true;
	}

	// Возвращаем список файлов
	bool getFilesList(string directory, string mask, vector<string>& list)
	{
		return _getFilesOrFoldersList(directory, mask, list, true);
	}

	// Возвращаем список папок
	bool getFoldersList(string directory, vector<string>& list)
	{
		return _getFilesOrFoldersList(directory, "*.*", list, false);
	}

	// Копируем файл
	bool copyFile(string from, string to)
	{
		//wstring wFrom = widen(from);
		//wstring wTo = widen(to);
		//// Копируем файл на новое место.
		//BOOL res = CopyFileW(wFrom.c_str(), wTo.c_str(), FALSE);
		//if (res == 0) {
		//	return false;
		//}
		//// Сбрасываем атрибут "только для чтения" с файла назначения.
		//// Если этого не сделать, 
		//// позже будут сбои при попытке перезаписать этот файл.
		//DWORD dwAttrs = GetFileAttributes(wTo.c_str()); 
		//if (dwAttrs == INVALID_FILE_ATTRIBUTES) {
		//	return false;
		//}
		//if ((dwAttrs & FILE_ATTRIBUTE_READONLY) != 0) { 
		//	res = SetFileAttributes(wTo.c_str(), dwAttrs ^ FILE_ATTRIBUTE_READONLY); 
		//	if (res == 0) {
		//		return false;
		//	}
		//} 
		//return true;
	}

	// Копируем дерево файлов
	bool copyFileTree(string from, string to)
	{
		return copyFileTree(from, to, "*.*");
	}
	bool copyFileTree(string from, string to, string mask)
	{
		if (from == to) {
			showError("Нельзя копировать папку в саму себя: \"" + to + "\"");
			return false;
		}
		// Если папка назначения не существует, создаём.
		if (!buildDirectoryPath(to)) {
			showError("Не удалось создать папку \"" + to + "\"");
			return false;
		}
		// Выясняем, какие файлы находятся в папке.
		vector<string> vecFiles;
		if (!getFilesList(from, mask, vecFiles))
			return false;
		// Копируем все найденные файлы.
		for (int i = 0; i < (int)vecFiles.size(); i++) {
			string source = from + PATH_DELIMITER + vecFiles[i];
			string dest = to + PATH_DELIMITER + vecFiles[i];
			if (!copyFile(source, dest)) {
				showError("Не удалось скопировать файл из \"" + source +
					"\" в \"" + dest + "\".");
				return false;
			}
		}
		// Получаем список вложенных папок.
		vector<string> vecFolders;
		if (!getFoldersList(from, vecFolders))
			return false;
		// Проходим по всем вложенным папкам.
		for (int i = 0; i < (int)vecFolders.size(); i++) {
			// Для каждой вложенной папки рекурсивно вызываем функцию копирования.
			string source = from + PATH_DELIMITER + vecFolders[i];
			string dest = to + PATH_DELIMITER + vecFolders[i];
			if (!copyFileTree(source, dest, mask))
				return false;
		}
		return true;
	}

	// Ищем первый файл "*.qsp" в папке.
	bool findGameFile(string dir, string &gameFileName) {
		// Ищем все QSP-файлы в корне указанной папки
		vector<string> gameFileList;
		if (!getFilesList(dir, "*.qsp", gameFileList))
			return false;
		int count = (int)gameFileList.size();
		if (count == 0) {
			showError("Не найден файл игры в папке " + dir);
			return false;
		}
		else if (count > 1) {
			showError("В корневой папке игры должен находиться только один файл с расширением \"*.qsp\". Папка: " + dir);
			return false;
		}
		gameFileName = gameFileList[0];
		return true;
	}

}