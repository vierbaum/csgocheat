#pragma once
#include "pch.h"
#include "includes.h"

class LegitBot {
private:
	LagRecord* pTargetRecord;

	float ApplyBezierSmoothingValues(Vec3D& vViewAngles, Vec3D& vAngle, Vec2D* pBezierVals);
	void CompensateRecoil(Vec3D& vAngle, Vec3D vAimPunch, float flRCS, float flSmoothing);

public:
	Vec2D vAimbotCurve[100];
	bool bGraphExtended = false;
	int iSelWeapon = 0;

	LagRecord* GetTargetRecord(CUserCmd* cmd);
	void RunAimbot(CUserCmd* cmd);
};

extern LegitBot g_LegitBot;