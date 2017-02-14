#include "GGCamera.h"
using namespace DirectX;

GGCamera::GGCamera(float fov, float aspect)
{
	XMStoreFloat4x4(&m_proj,
		XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), aspect, 0.01f, 1000.0f));

	Update();
}

void GGCamera::Set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot)
{
	m_pos = pos;
	m_rot = rot;
}

void GGCamera::Move(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot)
{
	XMVECTOR tmp;
	tmp = XMLoadFloat3(&m_pos) + XMLoadFloat3(&pos);
	XMStoreFloat3(&m_pos, tmp);

	tmp = XMLoadFloat3(&m_rot) + XMLoadFloat3(&rot);
	XMStoreFloat3(&m_rot, tmp);
}

void GGCamera::Update()
{
	XMVECTOR pos = XMLoadFloat3(&m_pos);
	XMVECTOR rot = XMLoadFloat3(&m_rot);
	rot = XMQuaternionRotationRollPitchYawFromVector(rot);

	XMVECTOR lookDir = XMVector3Rotate(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rot);
	XMVECTOR upDir = XMVector3Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rot);

	const XMMATRIX view = XMMatrixLookToLH(pos, lookDir, upDir);
	const XMMATRIX proj = XMLoadFloat4x4(&m_proj);

	XMStoreFloat4x4(&m_projView, view * proj);
}

DirectX::XMFLOAT4X4 GGCamera::GetMatrix() const
{
	return m_projView;
}