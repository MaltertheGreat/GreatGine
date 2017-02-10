#pragma once

#include <d3d11.h>
#include <wrl.h>

class GGGraphics
{
public:
	GGGraphics(HWND hWnd, int width, int height);

public:
	void Update();

private:
	void MakeD3D(HWND hWnd, int width, int height);
	void Render();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
};