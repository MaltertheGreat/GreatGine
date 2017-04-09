#include "GGInput.h"

void GGInput::PressKey(WPARAM key)
{
	auto it = m_keys.find(key);

	if (it != m_keys.end())
	{
		it->second = true;
	}
}

void GGInput::ReleaseKey(WPARAM key)
{
	auto it = m_keys.find(key);

	if (it != m_keys.end())
	{
		it->second = false;
	}
}

void GGInput::ListenForKey(WPARAM key)
{
	m_keys.insert({key, false});
}

bool GGInput::IsKeyPressed(WPARAM key)
{
	return m_keys.at(key);
}
