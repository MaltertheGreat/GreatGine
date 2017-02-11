#include "GGRenderer.h"
#include <fstream>
#include <string>
using Microsoft::WRL::ComPtr;
using std::array;
using std::vector;
using std::string;

GGRenderer::GGRenderer(HWND hWnd, int width, int height)
{
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	const array<D3D_FEATURE_LEVEL, 1> featureLevels = { D3D_FEATURE_LEVEL_11_0 };

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels.data(), featureLevels.size(), D3D11_SDK_VERSION, &sd, m_swapChain.GetAddressOf(), m_device.GetAddressOf(), nullptr, m_deviceContext.GetAddressOf());
	if FAILED(hr) throw std::exception();

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if FAILED(hr) throw std::exception();

	hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_renderTargetView);
	if FAILED(hr) throw std::exception();

	m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &vp);
}

GGShader GGRenderer::MakeShader()
{
	GGShader shader;

	vector<char> shaderFile = ReadFile("VertexShader.cso");
	HRESULT hr = m_device->CreateVertexShader(shaderFile.data(), shaderFile.size(), nullptr, shader.vertexShader.GetAddressOf());
	if FAILED(hr) throw std::exception();

	array<D3D11_INPUT_ELEMENT_DESC, 1> layout =
	{
		D3D11_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = m_device->CreateInputLayout(layout.data(), layout.size(), shaderFile.data(), shaderFile.size(), shader.inputLayout.GetAddressOf());
	if FAILED(hr) throw std::exception();

	shaderFile = ReadFile("PixelShader.cso");
	hr = m_device->CreatePixelShader(shaderFile.data(), shaderFile.size(), nullptr, shader.pixelShader.GetAddressOf());
	if FAILED(hr) throw std::exception();

	return shader;
}

GGMesh GGRenderer::MakeMesh(vector<GGMesh::GGVertex>& vertices, vector<GGMesh::GGIndex>& indices)
{
	GGMesh mesh;

	mesh.indexCount = indices.size();
	mesh.vertexBuffer = MakeVertexBuffer(vertices);
	mesh.indexBuffer = MakeIndexBuffer(indices);

	return mesh;
}

void GGRenderer::SetShader(const GGShader& shader)
{
	m_deviceContext->VSSetShader(shader.vertexShader.Get(), nullptr, 0);
	m_deviceContext->IASetInputLayout(shader.inputLayout.Get());
	m_deviceContext->PSSetShader(shader.pixelShader.Get(), nullptr, 0);
}

void GGRenderer::SetMesh(GGMesh& mesh)
{
	UINT stride = sizeof(GGMesh::GGVertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, mesh.vertexBuffer.GetAddressOf(), &stride, &offset);
	m_deviceContext->IASetIndexBuffer(mesh.indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}

void GGRenderer::RenderMesh(GGMesh& mesh)
{
	m_deviceContext->DrawIndexed(mesh.indexCount, 0, 0);
}

void GGRenderer::StartFrame(const array<float, 4> color)
{
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color.data());
}

void GGRenderer::EndFrame()
{
	m_swapChain->Present(0, 0);
}

vector<char> GGRenderer::ReadFile(const string& fileName)
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

ComPtr<ID3D11Buffer> GGRenderer::MakeVertexBuffer(vector<GGMesh::GGVertex>& vertices) const
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertices.size() * sizeof(GGMesh::GGVertex);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices.data();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	ComPtr<ID3D11Buffer> vertexBuffer;

	HRESULT hr = m_device->CreateBuffer(&bufferDesc, &initData, vertexBuffer.GetAddressOf());
	if FAILED(hr) throw std::exception();

	return vertexBuffer;
}

ComPtr<ID3D11Buffer> GGRenderer::MakeIndexBuffer(vector<GGMesh::GGIndex>& indices) const
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = indices.size() * sizeof(GGMesh::GGIndex);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = indices.data();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	ComPtr<ID3D11Buffer> indexBuffer;

	HRESULT hr = m_device->CreateBuffer(&bufferDesc, &initData, indexBuffer.GetAddressOf());
	if FAILED(hr) throw std::exception();

	return indexBuffer;
}