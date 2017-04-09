#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <array>

struct GGDirectX
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
};

class GGRenderer
{
public:
	GGRenderer(HWND hWnd, int width, int height);

	template <typename Resource, typename... Types>
	Resource Make(Types ... args)
	{
		return Resource(m_directX, args...);
	}

	template <typename Resource, typename... Types>
	void Set(Resource& resource, Types ... args)
	{
		resource.Set(m_directX, args...);
	}

	template <typename Resource, typename... Types>
	void Update(Resource& resource, Types ... args)
	{
		resource.Update(m_directX, args...);
	}

	template <typename Resource, typename... Types>
	void Render(const Resource& resource, Types ... args)
	{
		resource.Render(m_directX, args...);
	}

	void StartFrame(const std::array<float, 4> color) const;
	void EndFrame() const;

private:
	GGDirectX m_directX;
};
