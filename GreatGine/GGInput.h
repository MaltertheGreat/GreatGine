#pragma once

#include <Windows.h>
#include <map>

class GGInput
{
public:
	void PressKey(WPARAM key);
	void ReleaseKey(WPARAM key);

	void ListenForKey(WPARAM key);
	bool IsKeyPressed(WPARAM key);

private:
	std::map<WPARAM, bool> m_keys;
};
