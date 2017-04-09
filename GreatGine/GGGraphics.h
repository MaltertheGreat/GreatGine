#pragma once

#include "GGRenderer.h"
#include "GGMesh.h"
#include "GGShader.h"
#include "GGCamera.h"
#include "GGFreeView.h"

class GGInput;

class GGGraphics
{
public:
	GGGraphics(GGInput& input, HWND hWnd, int width, int height);

	void Update(GGInput& input);

private:
	void Render();

	GGRenderer m_renderer;
	GGCamera m_camera;
	GGFreeView m_viewer;
	GGShader m_testShader;
	GGMesh m_testMesh;
};
