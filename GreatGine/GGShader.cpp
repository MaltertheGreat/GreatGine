#include "GGShader.h"
#include <vector>
#include <fstream>
#include <string>
#include <array>
using Microsoft::WRL::ComPtr;
using namespace std;
using namespace DirectX;

vector<char> ReadFile(const std::string& fileName);

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

	//Constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(GGConstantBufferPerShader);

	hr = directX.device->CreateBuffer(&bd, nullptr, &m_constantBuffers[0]);
	if FAILED(hr) throw std::exception();

	bd.ByteWidth = sizeof(GGConstantBufferPerMesh);

	hr = directX.device->CreateBuffer(&bd, nullptr, &m_constantBuffers[1]);
	if FAILED(hr) throw std::exception();
}

void GGShader::Set(const GGDirectX& directX, DirectX::XMFLOAT4X4 viewProjMatrix) const
{
	directX.deviceContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	directX.deviceContext->IASetInputLayout(m_inputLayout.Get());
	directX.deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	directX.deviceContext->VSSetConstantBuffers(0, 1, m_constantBuffers[0].GetAddressOf());
	directX.deviceContext->VSSetConstantBuffers(1, 1, m_constantBuffers[1].GetAddressOf());

	GGConstantBufferPerShader buffer = { viewProjMatrix };

	directX.deviceContext->UpdateSubresource(m_constantBuffers[0].Get(), 0, nullptr, &buffer, 0, 0);
}

void GGShader::Render(const GGDirectX& directX, DirectX::XMFLOAT4X4 worldMatrix) const
{
	GGConstantBufferPerShader buffer = { worldMatrix };

	directX.deviceContext->UpdateSubresource(m_constantBuffers[1].Get(), 0, nullptr, &buffer, 0, 0);
}

vector<char> ReadFile(const string& fileName)
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