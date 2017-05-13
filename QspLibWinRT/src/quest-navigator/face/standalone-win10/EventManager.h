#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		// JsListener
		void executeAction(int pos);
		void selectObject(int pos);
		void loadSlotSelected(int index);
		void saveSlotSelected(int index);
		void msgClosed();
		void errorClosed();
		void menuClosed(int pos);
		void inputClosed(string text);
		void mute(bool flag);
		void inputStringChanged(string text);
		void inputStringEntered();

		// App
		void runGame(string fileName, int gameIsStandalone);
		void stopGame();

		// Работа с потоками и синхронизацией.
		
		// Ожидаем, пока поток библиотеки не будет готов к получению сообщений.
		void waitForLibIsReady();

	private:
		// Список событий для синхронизации потоков
		enum eSyncEvent
		{
			// Ui -> Библиотека
		
			evRunGame = 0,			// Запустить игру.
			evStopGame,				// Остановить игру.
			evShutdown,				// Завершить работу потока.
			evExecuteCode,			// Выполнить строку кода.
			evExecuteAction,		// Выполнить действие.
			evSelectObject,			// Выбрать предмет.
			evMute,					// Включить / выключить звук.
		
			evJsExecuted,			// JS-запрос выполнен.
			evMsgClosed,			// Диалог MSG был закрыт.
			evMenuClosed,			// Выбран пункт пользовательского меню.
			evInputClosed,			// Диалог INPUT вернул результат.
			evErrorClosed,			// Диалог с сообщением об ошибке был закрыт.
			evLoadSlotSelected,		// Был выбран слот для загрузки.
			evSaveSlotSelected,		// Был выбран слот для сохранения.
			evInputStringChanged,	// Изменился текст в строке ввода.
			evInputStringEntered,	// Нажали Enter в строке ввода.
		
			evTimer,				// Сработал таймер
		
			evLastUi,				// Маркер для разделения событий на две части.
		
			// Библиотека -> Ui
		
			evJsCommitted,			// Выполнить JS-запрос.
		
			evGameStopped,			// Игра остановлена.
		
			evLibIsReady,			// Библиотека завершила выполнение кода 
			// и ожидает следующей команды.
		
			evLast
		};

		// Создаём объект ядра для синхронизации потоков,
		// событие с автосбросом, инициализированное в занятом состоянии.
		HANDLE CreateSyncEvent();
		// Создаём таймер.
		HANDLE CreateTimer();
		// Получаем HANDLE события по его индексу
		HANDLE getEventHandle(eSyncEvent ev);
		// Запускаем событие
		void runSyncEvent(eSyncEvent ev);
		// Высвобождаем описатель и ругаемся если что не так.
		void freeHandle(HANDLE handle);
		// Входим в критическую секцию
		void lockData();
		// Выходим из критической секции
		void unlockData();
		// Ожидаем события
		bool waitForSingle(HANDLE handle);
		bool waitForSingle(eSyncEvent ev);
		bool waitForSingleLib(eSyncEvent ev);
		bool checkForSingle(eSyncEvent ev);
	};
}
