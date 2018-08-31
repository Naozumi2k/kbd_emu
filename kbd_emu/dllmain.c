#include "dll.h"
#include <windows.h>

HANDLE hCom;

DLLEXPORT DWORD Initialize(LPCSTR zsPort, DWORD x, DWORD y){
	extern HANDLE hCom;
	TCHAR zsComPort[32] = {0};
	TCHAR szBuffer[128] = {0};
	TCHAR szCoordBuffer[32] = {0};
	COMMTIMEOUTS CommTimeOuts;
	DCB dcb;
	DWORD SizeBuffer = 1200;
	
    if(hCom)
    	return 1;
	
	lstrcat(zsComPort, "\\\\.\\");
	lstrcat(zsComPort, zsPort);
	
	hCom = CreateFile(zsComPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	SetupComm(hCom, SizeBuffer, SizeBuffer);
    GetCommState(hCom, &dcb);
 
    if(hCom == INVALID_HANDLE_VALUE){
       return 0;
    }
 
    dcb.BaudRate = CBR_115200;
    dcb.fBinary = TRUE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fNull = FALSE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError = FALSE;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = 1;
    SetCommState(hCom, &dcb);
 
    CommTimeOuts.ReadIntervalTimeout= 10;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 2;	
    CommTimeOuts.ReadTotalTimeoutConstant = 100;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(hCom, &CommTimeOuts);
    
	lstrcat(szBuffer, "ST ");
	_itoa(x, szCoordBuffer, 10);
	lstrcat(szBuffer, szCoordBuffer);
	lstrcat(szBuffer, " ");
	_itoa(y, szCoordBuffer, 10);
	lstrcat(szBuffer, szCoordBuffer);
    
	return WriteCom(szBuffer, strlen(szBuffer)+1);
}

DLLEXPORT DWORD KeyboardKey(DWORD key){
	TCHAR szBuffer[128] = {0};
	TCHAR szKeyBuffer[32] = {0};
	
	lstrcat(szBuffer, "KB ");
	_itoa(key, szKeyBuffer, 10);
	lstrcat(szBuffer, szKeyBuffer);

	return WriteCom(szBuffer, strlen(szBuffer)+1);
}

DLLEXPORT DWORD MouseMove(DWORD x, DWORD y){
	TCHAR szBuffer[128] = {0};
	TCHAR szCoordBuffer[32] = {0};
	
	lstrcat(szBuffer, "MV ");
	_itoa(x, szCoordBuffer, 10);
	lstrcat(szBuffer, szCoordBuffer);
	lstrcat(szBuffer, " ");
	_itoa(y, szCoordBuffer, 10);
	lstrcat(szBuffer, szCoordBuffer);

	return WriteCom(szBuffer, strlen(szBuffer)+1);
}

DLLEXPORT DWORD MouseClick(DWORD x, DWORD y){
	TCHAR szBuffer[128] = {0};
	TCHAR szCoordBuffer[32] = {0};
	
	lstrcat(szBuffer, "MC ");
	_itoa(x, szCoordBuffer, 10);
	lstrcat(szBuffer, szCoordBuffer);
	lstrcat(szBuffer, " ");
	_itoa(y, szCoordBuffer, 10);
	lstrcat(szBuffer, szCoordBuffer);

	return WriteCom(szBuffer, strlen(szBuffer)+1);
}

DWORD WriteCom(LPSTR lpBuffer, DWORD dwSize){
	extern HANDLE hCom;
	DWORD dwWritten;
    COMSTAT ComState;
    
    if(!hCom || hCom == INVALID_HANDLE_VALUE) return 0;
    
    WriteFile(hCom, lpBuffer, dwSize, &dwWritten, NULL);

	return dwWritten;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
	switch(fdwReason){
		case DLL_PROCESS_ATTACH:{
			break;
		}
		case DLL_PROCESS_DETACH:{
			break;
		}
		case DLL_THREAD_ATTACH:{
			break;
		}
		case DLL_THREAD_DETACH:{
			break;
		}
	}
	
	return TRUE;
}
