#pragma once

#include "TaskSimple.h"

class CVehicle;
class CTaskUtilityLineUpPedWithCar;

class CTaskSimpleCarDrive : public CTaskSimple {
public:
    CVehicle*                     m_pVehicle{};
    CAnimBlendAssociation*        m_pAnimCloseDoorRolling{};
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar{};
    int32                         field_14{};
    int32                         field_18{};
    char                          field_1C{};
    char                          field_1D{};
    int32                         m_nBoppingStartTime{-1};
    int32                         field_24{};
    int32                         m_nBoppingEndTime{}; // Seemingly not a tick count, but rather the bopping interval 
    float                         m_fBoppingProgress; // 0.0 to 1.0
    int32                         m_nBoppingCompletedTimes{};
    int32                         m_nHeadBoppingStartTime{};
    int32                         m_nHeadBoppingDirection{};
    float                         m_fHeadBoppingOrientation{};
    float                         m_fRandomHeadBoppingMultiplier{};
    float                         m_fHeadBoppingFactor{};
    int32                         m_nArmBoppingStartTime{};
    int32                         m_nTimePassedSinceCarUpSideDown{};
    CTaskTimer                    m_copCarStolenTimer{};

    // Inited according to: 0x63C3AE
    uint8 m_flag0x1 : 1{};
    uint8 m_flag0x2 : 1{};
    uint8 m_bUpdateCurrentVehicle : 1; // Updates m_pVehicle pointer to the current occupied vehicle by ped - Set in ctor
    uint8 m_flag0x8 : 1{true};
    uint8 m_flag0x10 : 1{};
    uint8 m_flag0x20 : 1{};

public:
    static constexpr auto Type = TASK_SIMPLE_CAR_DRIVE;

    CTaskSimpleCarDrive(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask, bool updateCurrentVehicle);

    void TriggerIK(CPed* ped);
    void UpdateBopping();
    void StartBopping(CPed* ped);
    void ProcessHeadBopping(CPed* ped, uint8 a3, float a4);
    void ProcessArmBopping(CPed* pPed, uint8 a3, float a4);
    void ProcessBopping(CPed* a2, uint8 a3);

    eTaskType GetTaskType() override { return TASK_SIMPLE_CAR_DRIVE; }
    CTask* Clone() override;
    bool ProcessPed(class CPed* ped) override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool SetPedPosition(CPed* ped) override;

    auto GetVehicle() const { return m_pVehicle; }

private: // Wrappers for hooks
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleCarDrive* Constructor(CVehicle* pVehicle, CTaskUtilityLineUpPedWithCar* pUtilityTask, int8_t bUpdateCurrentVehicle) {
        this->CTaskSimpleCarDrive::CTaskSimpleCarDrive(pVehicle, pUtilityTask, bUpdateCurrentVehicle);
        return this;
    }

    CTaskSimpleCarDrive* Destructor() {
        this->CTaskSimpleCarDrive::~CTaskSimpleCarDrive();
        return this;
    }

    CTask* Clone_Reversed() { return CTaskSimpleCarDrive::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleCarDrive::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleCarDrive::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleCarDrive::ProcessPed(ped); }
    bool SetPedPosition_Reversed(CPed* ped) { return CTaskSimpleCarDrive::SetPedPosition(ped); }
};
VALIDATE_SIZE(CTaskSimpleCarDrive, 0x60);
