#pragma once
#include "windows.h"
#include <iostream>
#include <TlHelp32.h>


using namespace std;
DWORD getPID(LPCWSTR windowName) {

	HWND windowHandle = FindWindowW(NULL, windowName);
	DWORD* processID = new DWORD;

	if (!GetWindowThreadProcessId(windowHandle, processID)) {
		wcout << "Impossible de trouver: " << windowName << endl;
	}
	else {
		return *processID;
	}


}

DWORD Module(LPCWSTR ModuleName, LPCWSTR windowName) {

	DWORD dwPID = getPID(windowName);
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);
	do
		if (!lstrcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	while (Module32Next(hModule, &mEntry));

	cout << "Impossible de se ratacher a: Client.dll ." << endl;
	return 0;
}

HANDLE hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, getPID(L"Counter-Strike: Global Offensive"));
HWND TargetWnd = FindWindow(0, L"Counter-Strike: Global Offensive");
HDC HDC_Desktop = GetDC(TargetWnd);
