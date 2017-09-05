#include "GGGraphics.h"
#include <array>
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using std::vector;
using std::array;

GGGraphics::GGGraphics(GGInput& input, HWND hWnd, int width, int height)
	:
	m_renderer(hWnd, width, height),
	m_camera(80.0f, width / static_cast<float>(height)),
	m_viewer(input)
{
	m_testShader = m_renderer.Make<GGShader>();

	vector<GGMesh::GGVertex> vertices{
		{{0.5f, 0.5f, 0.5f}},
		{{0.5f, -0.5f, 0.5f}},
		{{-0.5f, -0.5f, 0.5f}}};

	vector<GGMesh::GGIndex> indices{0, 1, 2};

	m_testMesh = m_renderer.Make<GGMesh>(vertices, indices);
}

void GGGraphics::Update(GGInput& input)
{
	m_viewer.Update(input);
	m_camera.Set(m_viewer.GetPosition(), m_viewer.GetRotation());
	m_camera.Update();

	Render();
}

void GGGraphics::Render()
{
	array<float, 4> color{0.2f, 0.2f, 0.8f, 1.0f};
	m_renderer.StartFrame(color);

	m_renderer.Set(m_testShader, m_camera.GetMatrix());
	m_renderer.Set(m_testMesh);

	XMFLOAT4X4 identity;
	XMStoreFloat4x4(&identity, XMMatrixIdentity());
	m_renderer.Render(m_testShader, identity);
	m_renderer.Render(m_testMesh);

	m_renderer.EndFrame();
}
