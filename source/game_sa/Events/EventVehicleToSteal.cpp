#include "StdInc.h"

#include "EventVehicleToSteal.h"

#include "TaskComplexEnterCar.h"
#include "TheScripts.h"

void CEventVehicleToSteal::InjectHooks()
{
    RH_ScopedClass(CEventVehicleToSteal);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AF670);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AF760);
}

CEventVehicleToSteal::CEventVehicleToSteal(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    CEntity::SafeRegisterRef(m_vehicle);
}

CEventVehicleToSteal::~CEventVehicleToSteal()
{
    CEntity::SafeCleanUpRef(m_vehicle);
}

// 0x4AF670
CEventVehicleToSteal* CEventVehicleToSteal::Constructor(CVehicle* vehicle)
{
    this->CEventVehicleToSteal::CEventVehicleToSteal(vehicle);
    return this;
}

// 0x4AF760
bool CEventVehicleToSteal::AffectsPed(CPed* ped)
{
    return CEventVehicleToSteal::AffectsPed_Reversed(ped);
}

bool CEventVehicleToSteal::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && m_vehicle) {
        auto enterCarAsDriverTask = reinterpret_cast<CTaskComplexEnterCar*>(FindPlayerPed()->GetTaskManager().FindTaskByType(
            TASK_PRIMARY_PRIMARY, TASK_COMPLEX_ENTER_CAR_AS_DRIVER));
        if (!enterCarAsDriverTask || !enterCarAsDriverTask->m_pTargetVehicle) {
            if (m_vehicle == FindPlayerPed()->m_pVehicle
                && (CTheScripts::IsPlayerOnAMission() || CPad::GetPad(0)->bPlayerSafe))
            {
                return false;
            }
            return ped->m_nPedType == PED_TYPE_CRIMINAL && ped->m_pVehicle != m_vehicle
                || ped->m_nPedType == PED_TYPE_COP && m_vehicle == ped->m_pVehicle;
        }
    }
    return false;
}
