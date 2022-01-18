/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TaskSimple.h"

void CTaskSimple::InjectHooks() {
    ReversibleHooks::Install("CTaskSimple", "GetSubTask", 0x43E300, &CTaskSimple::GetSubTask_Reversed);
    ReversibleHooks::Install("CTaskSimple", "IsSimple", 0x43E310, &CTaskSimple::IsSimple_Reversed);
    ReversibleHooks::Install("CTaskSimple", "SetPedPosition", 0x43E320, &CTaskSimple::SetPedPosition_Reversed);
}

// 0x61A390
CTaskSimple::CTaskSimple() {
    m_pParentTask = nullptr;
}

// 0x43E300
CTask* CTaskSimple::GetSubTask() {
    return CTaskSimple::GetSubTask_Reversed();
}

// 0x43E310
bool CTaskSimple::IsSimple() {
    return CTaskSimple::IsSimple_Reversed();
}

// 0x43E320
bool CTaskSimple::SetPedPosition(CPed* ped) {
    return CTaskSimple::SetPedPosition_Reversed(ped);
}
