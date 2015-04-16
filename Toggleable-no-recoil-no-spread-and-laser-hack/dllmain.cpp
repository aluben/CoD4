// This no recoil, no spread and no laser hack for Call of Duty 4: Modern Warfare was created by Aluben.
// Include files and libraries
#include "stdafx.h"
#include <Windows.h>
#include <iostream>

// Byte addresses
BYTE NoSpread[]= {0x74, 0x15};
BYTE Spread[]= {0x75, 0x15};
BYTE NoRecoil[]= {0x75, 0x8};
BYTE Recoil[]= {0x74, 0x8};
BYTE Laser[]= {0x74, 0x04}; 
BYTE NoLaser[]= {0x75, 0x04};

// Setting 'hackoff' to '0'
static bool hackoff = 0;

// Setting the byteadress for 'LASER'
DWORD LASER	= 0x400000 + 0x0056E78;   

// Creating a method with the name 'ReadF7' which get toggled when F7 is pressed
DWORD WINAPI ReadF7(LPVOID)
{ 
	for (;;Sleep(500))
	{
		if(GetAsyncKeyState(VK_F7))
		{
			if (hackoff==0)
			{
				// This is where the hack gets enabled
				// Changing the value of the byte in your memory
				WriteProcessMemory(GetCurrentProcess(),(void*)0x00416C7B, &NoSpread, 2, 0);
				WriteProcessMemory(GetCurrentProcess(),(void*)0x0041A7BD, &NoRecoil, 2, 0);
				WriteProcessMemory(GetCurrentProcess(),(void*)LASER, &Laser, 2, 0);
				// Making a little beep so it's possible to hear when the hack gets enabled
				Beep(2000,500);
				// Setting 'hackoff' to '1'
				hackoff = 1;
			}
			else if (hackoff ==1)
			{
				// This is where the hack gets disabled
				// Changing the value of the byte in your memory
				WriteProcessMemory(GetCurrentProcess(),(void*)0x00416C7B, &Spread, 2, 0);
				WriteProcessMemory(GetCurrentProcess(),(void*)0x0041A7BD, &Recoil, 2, 0);
				WriteProcessMemory(GetCurrentProcess(),(void*)LASER, &NoLaser, 2, 0);
				// Making a little beep so it's possible to hear when the hack gets disabled
				Beep(2000,500);
				// Setting 'hackoff' to '0'
				hackoff = 0;
			}
		}
	}
}
// The method gets executed
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,LPVOID IpReserved)
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		// Execute 'ReadF7'
		CreateThread(NULL, NULL, ReadF7, NULL, NULL, NULL);
		// Making a little beep so it's possible to hear when the hack gets enabled
		Beep(2000,500);
		return true;
	}
}
