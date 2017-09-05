#pragma once

#include <Windows.h>
#include <map>

class GGInput
{
public:
	void ProcessMessage(const MSG* msg);

	void ListenForKey(WPARAM key);
	bool IsKeyPressed(WPARAM key);

private:
	void PressKey(WPARAM key);
	void ReleaseKey(WPARAM key);

private:
	std::map<WPARAM, bool> m_keys;
};
