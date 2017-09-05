#pragma once

#include <DirectXMath.h>

#include "GGInput.h"

class GGFreeView
{
public:
	explicit GGFreeView(GGInput& input);

	void Update(GGInput& input);

	DirectX::XMFLOAT3 GetPosition() const;
	DirectX::XMFLOAT3 GetRotation() const;

private:
	DirectX::XMFLOAT3 m_pos{0.0f, 0.0f, 0.0f};
	DirectX::XMFLOAT3 m_rot{0.0f, 0.0f, 0.0f};
};
