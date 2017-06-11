#pragma once

namespace QuestNavigator
{
	class ConfigurationBuilder
	{
	public:
		ConfigurationBuilder();
		~ConfigurationBuilder();

		// ������������� ������������ ������ ��� ������
		bool build();

	private:
		// ��������� ��������� ���� �� ����� config.xml
		bool loadGameConfig();
	};
}