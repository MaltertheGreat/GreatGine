#include "GGRenderer.h"
using Microsoft::WRL::ComPtr;
using namespace std;

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

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels.data(), featureLevels.size(), D3D11_SDK_VERSION, &sd, m_directX.swapChain.GetAddressOf(), m_directX.device.GetAddressOf(), nullptr, m_directX.deviceContext.GetAddressOf());
	if FAILED(hr) throw std::exception();

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = m_directX.swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if FAILED(hr) throw std::exception();

	hr = m_directX.device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_directX.renderTargetView);
	if FAILED(hr) throw std::exception();

	m_directX.deviceContext->OMSetRenderTargets(1, m_directX.renderTargetView.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_directX.deviceContext->RSSetViewports(1, &vp);
}

void GGRenderer::StartFrame(const array<float, 4> color)
{
	m_directX.deviceContext->ClearRenderTargetView(m_directX.renderTargetView.Get(), color.data());
}

void GGRenderer::EndFrame()
{
	m_directX.swapChain->Present(1, 0);
}