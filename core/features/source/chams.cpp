#include "pch.h"
#include "includes.h"

Chams g_Chams;

void Chams::OverrideMaterial(int iMatIndex, bool bIgnoreZ, Color col) {
	pMats.at(iMatIndex)->AlphaModulate(col.rgba[3]);
	pMats.at(iMatIndex)->ColorModulate(col.rgba[0], col.rgba[1], col.rgba[2]);

	pMats.at(iMatIndex)->SetMaterialVarFlag(MaterialVarFlags_t::MATERIAL_VAR_IGNOREZ, bIgnoreZ);
	g_Interface.pModelRender->OverrideMaterial(pMats.at(iMatIndex));
}

void Chams::DrawChams(void* pEcx, void* pEdx, DrawModelResults* pResults, const DrawModelInfo& info, Matrix* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, const Vec3D& modelOrigin, int flags) {
	// sanity check
	if (!Game::g_pLocal || !info.m_pClientEntity) {
		return;
	}
	
	Entity* pEntity = reinterpret_cast<Entity*>(info.m_pClientEntity);

	if (!pEntity)
		return;

	// we have found a player
	if (pEntity->iTeamNum() == 2 || pEntity->iTeamNum() == 3) {

		Player* pPlayer = reinterpret_cast<Player*>(pEntity);

		bool bEnemy = pPlayer->bIsEnemy(Game::g_pLocal);

		// enemy chams
		if (bEnemy) {

			// xqz chams
			if (Variables::bEnemyChamsInvis) {
				OverrideMaterial(Variables::iChamType, true, Variables::cInvisColor.ToPercent());
				c_oDrawModel(pEcx, pEdx, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
			}

			g_Interface.pModelRender->OverrideMaterial(nullptr); // change overwritten material to default

			if (Variables::bEnemyChamsVis) {
				OverrideMaterial(Variables::iChamType, false, Variables::cVisColor.ToPercent());
				c_oDrawModel(pEcx, pEdx, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
			}
		}

		// team chams
		if (!bEnemy) {

		}

		// local chams
		if (pPlayer == Game::g_pLocal) {

		}
	}
}