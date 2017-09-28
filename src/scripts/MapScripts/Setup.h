/*
Copyright (c) 2014-2017 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#pragma once

#include "Units/Creatures/AIInterface.h"
#include "Management/Item.h"
#include "Map/MapMgr.h"
#include "Management/ItemInterface.h"
#include "Storage/MySQLDataStore.hpp"
#include <Management/QuestLogEntry.hpp>
#include "Map/MapScriptInterface.h"
#include "Spell/Customization/SpellCustomizations.hpp"
#include "../Common/Instance_Base.h"
#include "../Common/Base.h"


void AlteracValleyScripts(ScriptMgr* scriptMgr);
void BlackrockDepthsScripts(ScriptMgr* scriptMgr);
void BlackrockSpireScripts(ScriptMgr* scriptMgr);
void BlackwingLairScripts(ScriptMgr* scriptMgr);
void MoltenCoreScripts(ScriptMgr* scriptMgr);
void DeadminesScripts(ScriptMgr* scriptMgr);
void GnomreganScripts(ScriptMgr* scriptMgr);
void KarazhanScripts(ScriptMgr* scriptMgr);
void MagisterTerraceScripts(ScriptMgr* scriptMgr);
void ScarletEnclaveScripts(ScriptMgr* scriptMgr);
void ScarletMonasteryScripts(ScriptMgr* scriptMgr);
void ScholomanceScripts(ScriptMgr* scriptMgr);
void ShadowfangKeepScripts(ScriptMgr* scriptMgr);
void StratholmeScripts(ScriptMgr* scriptMgr);
void SunkenTempleScripts(ScriptMgr* scriptMgr);
void SunwellPlateauScripts(ScriptMgr* scriptMgr);
void TheStockadeScripts(ScriptMgr* scriptMgr);
void UldamanScripts(ScriptMgr* scriptMgr);
void ZulAmanScripts(ScriptMgr* scriptMgr);
void ZulGurubScripts(ScriptMgr* scriptMgr);

void BlackfathomDeepsScripts(ScriptMgr* scriptMgr);
void BattleForMountHyjalScripts(ScriptMgr* scriptMgr);
void CullingOfStratholmScripts(ScriptMgr* scriptMgr);
void TheBlackMorassScripts(ScriptMgr* scriptMgr);
void OldHillsbradFoothillsScripts(ScriptMgr* scriptMgr);
void DireMaulScripts(ScriptMgr* scriptMgr);
void MaraudonScripts(ScriptMgr* scriptMgr);
void OnyxiasLairScripts(ScriptMgr* scriptMgr);
void RagefireChasmScripts(ScriptMgr* scriptMgr);
void RazorfenDownsScripts(ScriptMgr* scriptMgr);
void RazorfenKraulScripts(ScriptMgr* scriptMgr);
void RuinsOfAhnQirajScripts(ScriptMgr* scriptMgr);
void TempleOfAhnQirajScripts(ScriptMgr* scriptMgr);
void WailingCavernsScripts(ScriptMgr* scriptMgr);
void ZulFarrakScripts(ScriptMgr* scriptMgr);

void IcecrownCitadel(ScriptMgr* scriptMgr);

void TheArcatrazScripts(ScriptMgr* scriptMgr);
void TheBotanicaScripts(ScriptMgr* scriptMgr);
void TheEyeScripts(ScriptMgr* scriptMgr);
void TheMechanarScripts(ScriptMgr* scriptMgr);

void AuchenaiCryptsScripts(ScriptMgr* scriptMgr);
void ManaTombsScripts(ScriptMgr* scriptMgr);
void SethekkHallsScripts(ScriptMgr* scriptMgr);
void ShadowLabyrinthScripts(ScriptMgr* scriptMgr);