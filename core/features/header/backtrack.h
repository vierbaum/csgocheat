#pragma once
#include "pch.h"
#include "includes.h"

struct LagRecord {
	Player* pTargetPlayer;
	Matrix boneMat[MAXSTUDIOBONES], tempMat[MAXSTUDIOBONES];
	Vec3D vAbsOrigin, vAbsAngles, vOrigin, vAngles;
	Vec3D vHitBoxPos[HitboxMax];
	float flSimTime;

	// overload constructor
	LagRecord() = default;

	LagRecord(Player* pPlayer) {
		pTargetPlayer = pPlayer;
		pPlayer->SetupBones(boneMat, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0.f);

		for (int i = 0; i < HitboxMax; i++) {
			vHitBoxPos[i] = pPlayer->vGetHitboxPos(i);
		}

		vAbsOrigin = pPlayer->vAbsOrigin();
		vAbsAngles = pPlayer->vAbsAngles();

		vOrigin = pPlayer->vOrigin();
		vAngles = pPlayer->vEyeAngles();

		flSimTime = pPlayer->flSimTime();
	}

	Vec3D GetHitboxPos(int idx) {
		return this->vHitBoxPos[idx];
	}

	void ApplyToPlayer(Player* pPlayer) {
		pPlayer->SetAngles(vAbsAngles);
		pPlayer->SetPosition(vAbsOrigin);

		pPlayer->vOrigin() = vOrigin;
		pPlayer->vEyeAngles() = vAngles;
		
		pPlayer->SetupBones(tempMat, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0.f);
		memcpy(tempMat, boneMat, sizeof(Matrix) * MAXSTUDIOBONES);
	}
};

class Backtrack {
private:
	ConVar* pUpdateRate;
	ConVar* pMaxUpdateRate;
	ConVar* pInterp;
	ConVar* pInterpRatio;
	ConVar* pMinInterpRatio;
	ConVar* pMaxInterpRatio;
	ConVar* pMaxUnlag;

public:
	std::deque<LagRecord> deqLagRecords[MAX_PLAYERS];

	bool ValidTick(LagRecord& pRecord);
	float GetLerpTime();
	void RecordData();
	LagRecord* Lagcompensation(CUserCmd* cmd);
	void ApplyRecord(CUserCmd* cmd, LagRecord* record);

	__forceinline void Init() {
		deqLagRecords->clear();

		pUpdateRate = g_Interface.pICVar->FindVar(XOR("cl_updaterate"));
		pMaxUpdateRate = g_Interface.pICVar->FindVar(XOR("sv_maxupdaterate"));
		pInterp = g_Interface.pICVar->FindVar(XOR("cl_interp"));
		pInterpRatio = g_Interface.pICVar->FindVar(XOR("cl_interp_ratio"));
		pMinInterpRatio = g_Interface.pICVar->FindVar(XOR("sv_client_min_interp_ratio"));
		pMaxInterpRatio = g_Interface.pICVar->FindVar(XOR("sv_client_max_interp_ratio"));
		pMaxUnlag = g_Interface.pICVar->FindVar(XOR("sv_maxunlag"));
	}
};

extern Backtrack g_Backtrack;