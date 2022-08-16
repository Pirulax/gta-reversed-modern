#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexDestroyCarMelee : public CTaskComplex {
public:
    bool      byteC;
    bool      byteD;
    CVehicle* m_Vehicle;
    CVector   m_VehiclePos;
    float     m_DistSq0;
    float     m_fY;
    float     m_DistSq1;
    int32     dword2C;
    int32     m_nTime;

public:
    static constexpr eTaskType Type = TASK_COMPLEX_DESTROY_CAR_MELEE;

    explicit CTaskComplexDestroyCarMelee(CVehicle* vehToDestroy);
    ~CTaskComplexDestroyCarMelee() override;

    void CalculateSearchPositionAndRanges(CPed* ped);
    CTask* CreateSubTask(eTaskType taskType, CPed* ped);

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexDestroyCarMelee(m_Vehicle); } // 0x6235A0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    static void InjectHooks();
    CTaskComplexDestroyCarMelee* Constructor(CVehicle* vehToDestroy) { this->CTaskComplexDestroyCarMelee::CTaskComplexDestroyCarMelee(vehToDestroy); return this; }
    CTaskComplexDestroyCarMelee* Destructor() { this->CTaskComplexDestroyCarMelee::~CTaskComplexDestroyCarMelee(); return this; }
};
VALIDATE_SIZE(CTaskComplexDestroyCarMelee, 0x34);
