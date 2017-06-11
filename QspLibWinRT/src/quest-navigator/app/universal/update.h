#pragma once

namespace QuestNavigator {
	// Проверяем наличие апдейта при старте
	void checkUpdate();
	// Завершаем работу апдейтера по выходу из приложения
	void finishUpdate();
}