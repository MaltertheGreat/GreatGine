#pragma once

#include <DirectXMath.h>

class GGCamera
{
public:
	GGCamera(float fov, float aspect);

	void Set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot);
	void Move(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot);
	void Update();

	DirectX::XMFLOAT4X4 GetMatrix() const;

private:
	DirectX::XMFLOAT3 m_pos{0.0f, 0.0f, 0.0f};
	DirectX::XMFLOAT3 m_rot{0.0f, 0.0f, 0.0f};
	DirectX::XMFLOAT4X4 m_proj;
	DirectX::XMFLOAT4X4 m_projView;
};
