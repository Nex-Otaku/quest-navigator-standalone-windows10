#pragma once

namespace QuestNavigator {
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
}