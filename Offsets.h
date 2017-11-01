/*
* A jours le 20/03/2017
* Il y a certaines variables a supprimer, qui m'on aider lors de la creation de cet aimbot.
*/

#pragma once
#include <string>
#include <iostream>

using namespace std;
int oLocalPlayer = 0xAAD704;
int oEntityList = 0x4AD0884;
int oHealth = 0xFC;
int oTeam = 0xF0;
int oEntityLoopDistance = 0x00000010;
int dw_ClientState = 0x5CB524;
int dw_ViewAngles = 0x4D0C;


int LocalPlayer;
int entitys[11];
int enemyHealth[11];
int enemyTeam[11];
int MyTeam;
float boneMatrix[3][4];



string process = "csgo";
string stateBunny = "[Off]";
string stateTrigger = "[Off]";
string stateGlow = "[Off]";

int toggleBunny = 0;
int toggleTrigger = 0;
int toggleGlow = 0;
int toggleAimBot = 0;
int index = 1;

float myPosition[3];
float enemyPosition[20][3];
float angRotation[2];
int angSub;
int  m_VecOrigin = 0x134;
float enemy[20][3];


int dbis[10];
int val1, val2, val3, val4, val5, val6, val7, val8, val9, val10;
float Distance[20];
int closest = 0;
