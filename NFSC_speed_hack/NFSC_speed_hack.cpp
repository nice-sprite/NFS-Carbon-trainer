// Very simple NFS Carbon speed hack trainer, works on 1.3 and 1.4 Collectors edition (that I was able to test)
// however I am pretty sure that the addresses didnt even change in 1.2 through 1.4, and I dont think they changed 
// between the CE version and non-CE version of the game so this would probably work on all versions of the game 

#include <iostream>
#include <windows.h>

DWORD procID;
HWND hwnd = FindWindow(NULL, TEXT("Need for Speed™ Carbon"));

HANDLE pHandle; 

void SetCarSpeed(float targetSpeed)
{
	double convertedSpeed = targetSpeed * .45454545454545454545;
	float vX;
	float vY;
	float vZ;
	ReadProcessMemory(pHandle, (LPVOID)0xAAB1C0, &vX, sizeof(vX), NULL);
	ReadProcessMemory(pHandle, (LPVOID)0xAAB1C4, &vY, sizeof(vX), NULL);
	ReadProcessMemory(pHandle, (LPVOID)0xAAB1C8, &vZ, sizeof(vX), NULL);
	vX *= convertedSpeed;
	vY *= convertedSpeed;
	vZ *= convertedSpeed;
	WriteProcessMemory(pHandle, (LPVOID)0xAAB150, &vX, sizeof(vX), NULL);
	WriteProcessMemory(pHandle, (LPVOID)0xAAB154, &vY, sizeof(vX), NULL);
	WriteProcessMemory(pHandle, (LPVOID)0xAAB158, &vZ, sizeof(vX), NULL);
}

void DoubleCurrentSpeed()
{
	float vX;
	float vY;
	float vZ;
	ReadProcessMemory(pHandle, (LPVOID)0xAAB150, &vX, sizeof(vX), NULL);
	ReadProcessMemory(pHandle, (LPVOID)0xAAB154, &vY, sizeof(vX), NULL);
	ReadProcessMemory(pHandle, (LPVOID)0xAAB158, &vZ, sizeof(vX), NULL);
	vX *= 2;
	vY *= 2;
	vZ *= 2;
	WriteProcessMemory(pHandle, (LPVOID)0xAAB150, &vX, sizeof(vX), NULL);
	WriteProcessMemory(pHandle, (LPVOID)0xAAB154, &vY, sizeof(vX), NULL);
	WriteProcessMemory(pHandle, (LPVOID)0xAAB158, &vZ, sizeof(vX), NULL);
}

void SuperBrakes()
{
	SetCarSpeed(0.0);
	float newVel = 0.0f;
	WriteProcessMemory(pHandle, (LPVOID)0xAAB160, &newVel, sizeof(newVel), NULL);
	WriteProcessMemory(pHandle, (LPVOID)0xAAB164, &newVel, sizeof(newVel), NULL);
	WriteProcessMemory(pHandle, (LPVOID)0xAAB168, &newVel, sizeof(newVel), NULL);
}

void InstantSpeedAndBrake()
{
	SetCarSpeed(1000.0);
	Sleep(50u);
	SuperBrakes();
}

void CarJump(float warpAmount)
{
	float newPosition;
	ReadProcessMemory(pHandle, (LPVOID)0xAAB144, &newPosition, sizeof(newPosition), NULL);
	newPosition += warpAmount;
	WriteProcessMemory(pHandle, (LPVOID)0xAAB144, &newPosition, sizeof(newPosition), NULL);
}


int main()
{
	GetWindowThreadProcessId(hwnd, &procID);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	while (!GetAsyncKeyState(VK_END) & 1)
	{
		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			SetCarSpeed(500.0);
		}

		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			DoubleCurrentSpeed();
		}

		if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		{
			InstantSpeedAndBrake();
		}

		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
		{
			SuperBrakes();
		}

		if (GetAsyncKeyState('J') & 1)
		{
			CarJump(5.0f);
		}

		
	}
	return 0;
	
}

