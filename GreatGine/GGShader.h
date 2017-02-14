#pragma once

#include "GGRenderer.h"
#include <vector>

class GGShader
{
public:
	GGShader()
	{}

private:
	friend class GGRenderer;
	GGShader(GGDirectX& directX);

private:
	void Set(const GGDirectX& directX) const;

	static std::vector<char> ReadFile(const std::string& fileName);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};