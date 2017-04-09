#include "GGFreeView.h"
#include <array>
using namespace std;

enum KEYS
{
	LEFT = 'E',
	RIGHT = 'Q'
};

constexpr WPARAM KEY_FORWARD = 'W';
constexpr WPARAM KEY_BACKWARD = 'S';
constexpr WPARAM KEY_RIGHTWARD = 'D';
constexpr WPARAM KEY_LEFTWARD = 'A';
constexpr WPARAM KEY_UPWARD = VK_SPACE;
constexpr WPARAM KEY_DOWNWARD = VK_SHIFT;
constexpr WPARAM KEY_RIGHT = 'Q';
constexpr WPARAM KEY_LEFT = 'E';

GGFreeView::GGFreeView(GGInput& input)
{
	input.ListenForKey(KEY_FORWARD);
	input.ListenForKey(KEY_BACKWARD);
	input.ListenForKey(KEY_RIGHTWARD);
	input.ListenForKey(KEY_LEFTWARD);
	input.ListenForKey(KEY_UPWARD);
	input.ListenForKey(KEY_DOWNWARD);
	input.ListenForKey(KEY_RIGHT);
	input.ListenForKey(KEY_LEFT);
}

void GGFreeView::Update(GGInput& input)
{
	if (input.IsKeyPressed(KEY_FORWARD))
	{
		m_pos.z += 0.01f;
	}
	if (input.IsKeyPressed(KEY_BACKWARD))
	{
		m_pos.z -= 0.01f;
	}
	if (input.IsKeyPressed(KEY_RIGHTWARD))
	{
		m_pos.x += 0.01f;
	}
	if (input.IsKeyPressed(KEY_LEFTWARD))
	{
		m_pos.x -= 0.01f;
	}
	if (input.IsKeyPressed(KEY_UPWARD))
	{
		m_pos.y += 0.01f;
	}
	if (input.IsKeyPressed(KEY_DOWNWARD))
	{
		m_pos.y -= 0.01f;
	}

	if (input.IsKeyPressed(KEY_RIGHT))
	{
		m_rot.y -= 0.01f;
	}
	if (input.IsKeyPressed(KEY_LEFT))
	{
		m_rot.y += 0.01f;
	}
}

DirectX::XMFLOAT3 GGFreeView::GetPosition() const
{
	return m_pos;
}

DirectX::XMFLOAT3 GGFreeView::GetRotation() const
{
	return m_rot;
}
