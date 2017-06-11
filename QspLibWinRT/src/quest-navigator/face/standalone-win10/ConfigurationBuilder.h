#pragma once

namespace QuestNavigator
{
	class ConfigurationBuilder
	{
	public:
		ConfigurationBuilder();
		~ConfigurationBuilder();

		// Устанавливаем конфигурацию плеера при старте
		bool build();

	private:
		// Загружаем настройки игры из файла config.xml
		bool loadGameConfig();
	};
}