#ifndef _DLL_H_
#define _DLL_H_
#include <windows.h>
#define DLLEXPORT __declspec(dllexport)

DLLEXPORT DWORD Initialize(LPCSTR port, DWORD x, DWORD y);
DLLEXPORT DWORD KeyboardKey(DWORD key);
DLLEXPORT DWORD MouseMove(DWORD x, DWORD y);
DLLEXPORT DWORD MouseClick(DWORD x, DWORD y);
DWORD WriteCom(LPSTR lpBuffer, DWORD dwSize);

#endif
