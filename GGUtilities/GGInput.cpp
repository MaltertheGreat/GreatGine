#include "GGInput.h"

void GGInput::PressKey(WPARAM key)
{
	const auto it = m_keys.find(key);

	if (it != m_keys.end())
	{
		it->second = true;
	}
}

void GGInput::ReleaseKey(WPARAM key)
{
	const auto it = m_keys.find(key);

	if (it != m_keys.end())
	{
		it->second = false;
	}
}

void GGInput::ProcessMessage(const MSG* msg)
{
	switch (msg->message)
	{
	case WM_KEYDOWN:
		PressKey(msg->wParam);
		break;

	case WM_KEYUP:
		ReleaseKey(msg->wParam);
		break;

	default:
		break;
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
