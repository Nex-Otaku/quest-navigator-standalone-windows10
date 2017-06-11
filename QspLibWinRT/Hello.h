#pragma once

namespace QspLibWinRT
{
    public ref class Hello sealed
    {
    public:
        Hello();
		Platform::String^ GetMessage();
		Platform::String^ GetModifiedMessage(Platform::String^ message);
	};
}
