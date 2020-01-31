#include "phook.h"

PTR SwapBuffersAddr;
wglSwapBuffers oSwapBuffers;

bool init = false;
BOOL __stdcall PHook::hkSwapBuffers(_In_ HDC hdc)
{
	if (!init)
	{
		MessageBox(NULL, "Success!", "SwapBuffers Hook", MB_OK);
		init = true;
	}
	PHook::SetupOrtho();
	//Draw Here
	PHook::Restore();
	return oSwapBuffers(hdc);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Init, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Shutdown, hMod, 0, nullptr);
		break;
	}
	return TRUE;
}