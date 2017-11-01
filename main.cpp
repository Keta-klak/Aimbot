// aimbot.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "Offsets.h"
#include "windows.h"
#include "apps.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <cmath>

//my pos = localplayer (playerbase) + m_VecOrigin
//vEyePosition[0] = vecOrigin[0] + vecView[0];
//x = "engine.dll" + dwClientState] 
//viewAng = read( x + dwViewAngles ) ;
using namespace std;

float CalcAngle(float *src, float *dst)
{
	float angles[3];

	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	angles[0] = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
	angles[1] = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;

	if (delta[0] >= 0.0)
	{
		angles[1] += 180.0f;
	}

	if (angles[0] != angles[0])
	{
		angles[0] = 0;
	}
	if (angles[1] != angles[1])
	{
		angles[1] = 0;
	}
	while (angles[0] > 89)
	{
		angles[0] = 89;
	}
	while (angles[0] < -89)
	{
		angles[0] = -89;
	}
	while (angles[1] > 180)
	{
		angles[1] = angles[1] - 360;
	}
	while (angles[1] < -180)
	{
		angles[1] = angles[1] + 360;
	}

	angles[2] = 0;
	return angles[0];
}
float CalcAngle2(float *src, float *dst)
{
	float angles[3];

	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	angles[0] = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
	angles[1] = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;

	if (delta[0] >= 0.0)
	{
		angles[1] += 180.0f;
	}

	if (angles[0] != angles[0])
	{
		angles[0] = 0;
	}
	if (angles[1] != angles[1])
	{
		angles[1] = 0;
	}
	while (angles[0] > 89)
	{
		angles[0] = 89;
	}
	while (angles[0] < -89)
	{
		angles[0] = -89;
	}
	while (angles[1] > 180)
	{
		angles[1] = angles[1] - 360;
	}
	while (angles[1] < -180)
	{
		angles[1] = angles[1] + 360;
	}

	angles[2] = 0;
		return angles[1];
}
float Get3dDistance(float myCoordsX, float myCoordsZ, float myCoordsY,float eNx, float eNz, float eNy)
{
	//Use the 3d distance formula to get a resulting Floating distance value POW!!
	return sqrt(
		pow(double(eNx - myCoordsX), 2.0) +
		pow(double(eNy - myCoordsY), 2.0) +
		pow(double(eNz - myCoordsZ), 2.0));
}

int main()
{
	DWORD dwBoneMatrices;
	do {

		int bClient = Module(L"client.dll", L"Counter-Strike: Global Offensive");
		int bEngine = Module(L"engine.dll", L"Counter-Strike: Global Offensive");
		int address;

		address = bClient + oLocalPlayer;
		ReadProcessMemory(hProcHandle, (int*)address, &LocalPlayer, sizeof(LocalPlayer), NULL);

		address = LocalPlayer + m_VecOrigin;
		ReadProcessMemory(hProcHandle, (int*)address, &myPosition, sizeof(myPosition), NULL);

		address = (bEngine + dw_ClientState);
		ReadProcessMemory(hProcHandle, (int*)address, &angSub, sizeof(angSub), NULL);

		address = angSub + dw_ViewAngles;
		ReadProcessMemory(hProcHandle, (int*)address, &angRotation, sizeof(angRotation), NULL);

		address = LocalPlayer + oTeam;
		ReadProcessMemory(hProcHandle, (int*)address, &MyTeam, sizeof(MyTeam), NULL);

		for (int i = 0; i <= 10; i++) {

			address = bClient + oEntityList + (i * 0x10);
			ReadProcessMemory(hProcHandle, (int*)address, &entitys[i], sizeof(entitys[i]), NULL);

			address = entitys[i] + oTeam;
			ReadProcessMemory(hProcHandle, (int*)address, &enemyTeam[i], sizeof(enemyTeam[i]), NULL);

			address = entitys[i] + oHealth;
			ReadProcessMemory(hProcHandle, (int*)address, &enemyHealth[i], sizeof(enemyHealth[i]), NULL);

			address = entitys[i] + m_VecOrigin;
			ReadProcessMemory(hProcHandle, (int*)address, &enemyPosition[i], sizeof(enemyPosition[i]), NULL);


			//BoneNumber:[14] = [Head1]
			float matrix[3][4];
			float vecBone[3];
			DWORD dwBoneMatrices;
			float boneMatrix[3][4]; // matrix3x4_t

			
			address = entitys[i] + 0x2698; //boneMatrixOffset
			ReadProcessMemory(hProcHandle, (int*)address, &dwBoneMatrices, sizeof(dwBoneMatrices), NULL);
			
			address = dwBoneMatrices + (0x30 * 6);
			ReadProcessMemory(hProcHandle, (int*)address, &boneMatrix, 3 * 4 * sizeof(float), NULL);	

			if (MyTeam != enemyTeam[i] && enemyHealth[i] > 0) {

				 enemy[i][0] = boneMatrix[0][3];
				 enemy[i][1] = boneMatrix[1][3] ;
				 enemy[i][2] = boneMatrix[2][3] - 52.f;

				 Distance[i] = Get3dDistance(myPosition[0], myPosition[1], myPosition[2], enemy[i][0], enemy[i][1], enemy[i][2]);

				 index = Distance[0];
				 for (int j = 0; j <= 10; j++) {
					 if (enemyHealth[j] <= 0 || Distance[j] <= 0) {
						 Distance[j] = 9999;
					 }
					 if (Distance[j] < index  && Distance[j] > 0 || index <= 0 && enemyTeam[j] != MyTeam && enemyTeam[j] > 1) {
					
						 index = Distance[j];
						 closest = j;
					 }
				 }


	
				if (GetAsyncKeyState(VK_XBUTTON2)){
					

					angRotation[0] = CalcAngle(myPosition, enemy[closest]);
					angRotation[1] = CalcAngle2(myPosition, enemy[closest]);

					address = angSub + dw_ViewAngles;
					WriteProcessMemory(hProcHandle, (int*)address, &angRotation, sizeof(angRotation), NULL);	
				}
								
			}			

		}
		system("cls");

	} while (true);
	return 0;
}

