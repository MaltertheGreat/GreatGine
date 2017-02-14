#include "GGShader.h"
#include <fstream>
#include <string>
#include <array>
using namespace std;

GGShader::GGShader(GGDirectX& directX)
{
	vector<char> shaderFile = ReadFile("VertexShader.cso");
	HRESULT hr = directX.device->CreateVertexShader(shaderFile.data(), shaderFile.size(), nullptr, m_vertexShader.GetAddressOf());
	if FAILED(hr) throw std::exception();

	array<D3D11_INPUT_ELEMENT_DESC, 1> layout =
	{
		D3D11_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = directX.device->CreateInputLayout(layout.data(), layout.size(), shaderFile.data(), shaderFile.size(), m_inputLayout.GetAddressOf());
	if FAILED(hr) throw std::exception();

	shaderFile = ReadFile("PixelShader.cso");
	hr = directX.device->CreatePixelShader(shaderFile.data(), shaderFile.size(), nullptr, m_pixelShader.GetAddressOf());
	if FAILED(hr) throw std::exception();
}

void GGShader::Set(const GGDirectX& directX) const
{
	directX.deviceContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	directX.deviceContext->IASetInputLayout(m_inputLayout.Get());
	directX.deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}

vector<char> GGShader::ReadFile(const string& fileName)
{
	std::ifstream shaderFile(fileName.c_str(), std::ifstream::binary);
	if (!shaderFile) throw std::exception();

	shaderFile.seekg(0, shaderFile.end);
	UINT length = static_cast<UINT>(shaderFile.tellg());
	shaderFile.seekg(0, shaderFile.beg);

	vector<char> buffer(length);
	shaderFile.read(buffer.data(), length);
	if (!shaderFile) throw std::exception();

	return buffer;
}