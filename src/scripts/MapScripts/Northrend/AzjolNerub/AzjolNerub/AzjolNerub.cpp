/*
Copyright (c) 2014-2017 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#include "Setup.h"
#include "AzjolNerub.h"

class AzjolNerub : public InstanceScript
{
public:

    AzjolNerub(MapMgr* pMapMgr) : InstanceScript(pMapMgr)
    {
        generateBossDataState();
    }

    static InstanceScript* Create(MapMgr* pMapMgr) { return new AzjolNerub(pMapMgr); }

    void OnCreatureDeath(Creature* pCreature, Unit* pUnit)
    {
        setData(pCreature->GetEntry(), Finished);
    }
};


void AzjolNerubScripts(ScriptMgr* scriptMgr)
{
    scriptMgr->register_instance_script(601, &AzjolNerub::Create);
}