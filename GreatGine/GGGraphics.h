#pragma once

#include "GGRenderer.h"
#include "GGMesh.h"
#include "GGShader.h"
#include "GGCamera.h"

class GGGraphics
{
public:
	GGGraphics(HWND hWnd, int width, int height);

public:
	void Update();

private:
	void Render();

private:
	GGRenderer m_renderer;
	GGCamera m_camera;
	GGShader m_testShader;
	GGMesh m_testMesh;
};