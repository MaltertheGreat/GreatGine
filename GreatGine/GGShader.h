#pragma once

#include <DirectXMath.h>
#include <array>
#include "GGRenderer.h"

class GGShader
{
	struct GGConstantBufferPerShader
	{
		DirectX::XMFLOAT4X4 viewProjMatrix;
	};

	struct GGConstantBufferPerMesh
	{
		DirectX::XMFLOAT4X4 worldMatrix;
	};

public:
	GGShader()
	{}

private:
	friend GGRenderer;
	GGShader(GGDirectX& directX);

private:
	void Set(const GGDirectX& directX, DirectX::XMFLOAT4X4 viewProjMatrix) const;
	void Render(const GGDirectX& directX, DirectX::XMFLOAT4X4 worldMatrix) const;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 2> m_constantBuffers;
};