#include "GGCamera.h"
using namespace DirectX;

GGCamera::GGCamera(float fov, float aspect)
{
	XMStoreFloat4x4(&m_proj,
	                XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), aspect, 0.01f, 1000.0f));

	Update();
}

void GGCamera::Set(XMFLOAT3 pos, XMFLOAT3 rot)
{
	m_pos = pos;
	m_rot = rot;
}

void GGCamera::Move(XMFLOAT3 pos, XMFLOAT3 rot)
{
	auto tmp = XMLoadFloat3(&m_pos) + XMLoadFloat3(&pos);
	XMStoreFloat3(&m_pos, tmp);

	tmp = XMLoadFloat3(&m_rot) + XMLoadFloat3(&rot);
	XMStoreFloat3(&m_rot, tmp);
}

// Recalculates camera's matrices based on position and rotation
void GGCamera::Update()
{
	auto pos = XMLoadFloat3(&m_pos);
	auto rot = XMLoadFloat3(&m_rot);
	rot = XMQuaternionRotationRollPitchYawFromVector(rot);

	auto lookDir = XMVector3Rotate(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rot);
	auto upDir = XMVector3Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rot);

	const auto view = XMMatrixLookToLH(pos, lookDir, upDir);
	const auto proj = XMLoadFloat4x4(&m_proj);

	XMStoreFloat4x4(&m_projView, view * proj);
}

XMFLOAT4X4 GGCamera::GetMatrix() const
{
	return m_projView;
}
