#include "GGApplication.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	try
	{
		GGApplication app(hInstance, L"GreatGine");
		app.Run(nCmdShow);
	}
	catch (std::exception& err)
	{
		MessageBoxA(NULL, err.what(), "An error ocurred!", MB_ICONERROR);
	}

	return 0;
}