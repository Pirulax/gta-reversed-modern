#include "StdInc.h"
#include "TaskSimpleDoHandSignal.h"
#include "TaskComplexPlayHandSignalAnim.h"

void CTaskSimpleDoHandSignal::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleDoHandSignal, 0x86fa68, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x660880);

    RH_ScopedInstall(Destructor, 0x6608B0);

    RH_ScopedVMTInstall(Clone, 0x6608C0);
    RH_ScopedVMTInstall(GetTaskType, 0x6608A0);
    RH_ScopedVMTInstall(MakeAbortable, 0x660930);
    RH_ScopedVMTInstall(ProcessPed, 0x660940);
}

CTaskSimpleDoHandSignal::CTaskSimpleDoHandSignal(const CTaskSimpleDoHandSignal& o) :
    m_initialised{ o.m_initialised }
{
}

// 0x660940
bool CTaskSimpleDoHandSignal::ProcessPed(CPed* ped) {
    if (!ped->GetIsOnScreen()) {
        return true;
    }

    const auto partialAnimTask = ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);

    if (m_initialised) {
        return !partialAnimTask || CTask::IsA<TASK_COMPLEX_HANDSIGNAL_ANIM>(partialAnimTask);
    }

    if (partialAnimTask) {
        if (CTask::IsA<TASK_COMPLEX_HANDSIGNAL_ANIM>(partialAnimTask)) {
            return true;
        }
        partialAnimTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr);
        return false;
    }

    ped->GetTaskManager().SetTaskSecondary(
        new CTaskComplexPlayHandSignalAnim{},
        TASK_SECONDARY_PARTIAL_ANIM
    );
    m_initialised = true;
    return false;
}
