#include "GGApplication.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nShowCmd)
{
	try
	{
		GGApplication app(hInstance, L"GreatGine");
		app.Run(nShowCmd);
	}
	catch (std::exception& err)
	{
		MessageBoxA(NULL, err.what(), "An error ocurred!", MB_ICONERROR);
	}

	return 0;
}