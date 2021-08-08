#include "StdInc.h"

CFireManager& gFireManager = *reinterpret_cast<CFireManager*>(0xB71F80);

void CFireManager::InjectHooks() {
    //ReversibleHooks::Install("CFireManager", "Constructor", 0x539DA0, &CFireManager::Constructor);
    //ReversibleHooks::Install("CFireManager", "Destructor", 0x538BB0, &CFireManager::Destructor);
    ReversibleHooks::Install("CFireManager", "Init", 0x538BC0, &CFireManager::Init);
    ReversibleHooks::Install("CFireManager", "GetNumOfNonScriptFires", 0x538F10, &CFireManager::GetNumOfNonScriptFires);
    //ReversibleHooks::Install("CFireManager", "FindNearestFire", 0x538F40, &CFireManager::FindNearestFire);
    ReversibleHooks::Install("CFireManager", "PlentyFiresAvailable", 0x539340, &CFireManager::PlentyFiresAvailable);
    //ReversibleHooks::Install("CFireManager", "ExtinguishPoint", 0x539450, &CFireManager::ExtinguishPoint);
    //ReversibleHooks::Install("CFireManager", "ExtinguishPointWithWater", 0x5394C0, &CFireManager::ExtinguishPointWithWater);
    //ReversibleHooks::Install("CFireManager", "IsScriptFireExtinguished", 0x5396E0, &CFireManager::IsScriptFireExtinguished);
    ReversibleHooks::Install("CFireManager", "RemoveScriptFire", 0x539700, &CFireManager::RemoveScriptFire);
    //ReversibleHooks::Install("CFireManager", "RemoveAllScriptFires", 0x539720, &CFireManager::RemoveAllScriptFires);
    //ReversibleHooks::Install("CFireManager", "ClearAllScriptFireFlags", 0x5397A0, &CFireManager::ClearAllScriptFireFlags);
    //ReversibleHooks::Install("CFireManager", "SetScriptFireAudio", 0x5397B0, &CFireManager::SetScriptFireAudio);
    //ReversibleHooks::Install("CFireManager", "GetScriptFireCoords", 0x5397E0, &CFireManager::GetScriptFireCoords);
    //ReversibleHooks::Install("CFireManager", "GetNumFiresInRange", 0x5397F0, &CFireManager::GetNumFiresInRange);
    //ReversibleHooks::Install("CFireManager", "GetNumFiresInArea", 0x539860, &CFireManager::GetNumFiresInArea);
    //ReversibleHooks::Install("CFireManager", "DestroyAllFxSystems", 0x539D10, &CFireManager::DestroyAllFxSystems);
    //ReversibleHooks::Install("CFireManager", "CreateAllFxSystems", 0x539D50, &CFireManager::CreateAllFxSystems);
    //ReversibleHooks::Install("CFireManager", "Shutdown", 0x539DD0, &CFireManager::Shutdown);
    //ReversibleHooks::Install("CFireManager", "GetNextFreeFire", 0x539E50, &CFireManager::GetNextFreeFire);
    //ReversibleHooks::Install("CFireManager", "StartFire", 0x539F00, &CFireManager::StartFire);
    //ReversibleHooks::Install("CFireManager", "StartFire", 0x53A050, &CFireManager::StartFire);
    //ReversibleHooks::Install("CFireManager", "StartScriptFire", 0x53A270, &CFireManager::StartScriptFire);
    //ReversibleHooks::Install("CFireManager", "Update", 0x53AF00, &CFireManager::Update);
}

CFireManager::CFireManager() {
}

CFireManager::~CFireManager() {
}

CFireManager* CFireManager::Destructor() {
    this->CFireManager::~CFireManager();
    return this;
}

CFireManager* CFireManager::Constructor() {
    this->CFireManager::CFireManager();
    return this;
}

void CFireManager::Init() {
    for (auto& fire : m_aFires) {
        fire.Initialise();
    }
    m_nMaxFireGenerationsAllowed = 1'000'000 - 1;
}

uint32_t CFireManager::GetNumOfNonScriptFires() {
    uint32_t c = 0;
    for (auto& fire : m_aFires)
        if (fire.m_nFlags.bActive && !fire.m_nFlags.bCreatedByScript)
            c++;
    return c;
}

CFire * CFireManager::FindNearestFire(CVector const& point, bool bCheckWasExtinguished, bool bCheckWasCreatedByScript) {
    return plugin::CallMethodAndReturn<CFire *, 0x538F40, CFireManager*, CVector const&, bool, bool>(this, point, bCheckWasExtinguished, bCheckWasCreatedByScript);
}

bool CFireManager::PlentyFiresAvailable() {
    uint32_t c = 0;
    for (auto& fire : m_aFires) {
        if (fire.m_nFlags.bActive) 
            c++;
        if (c >= 6)
            return true;
    }
    return false;
}

void CFireManager::ExtinguishPoint(CVector point, float fRadiusSq) {
    return plugin::CallMethod<0x539450, CFireManager*, CVector, float>(this, point, fRadiusSq);
}

bool CFireManager::ExtinguishPointWithWater(CVector point, float fRadiusSq, float fFireSize) {
    return plugin::CallMethodAndReturn<bool, 0x5394C0, CFireManager*, CVector, float, float>(this, point, fRadiusSq, fFireSize);
}

bool CFireManager::IsScriptFireExtinguished(short id) {
    return plugin::CallMethodAndReturn<bool, 0x5396E0, CFireManager*, short>(this, id);
}

void CFireManager::RemoveScriptFire(uint16_t fireID) {
    CFire& fire = Get(fireID);
    if (fire.m_nFlags.bCreatedByScript) {
        fire.m_nFlags.bCreatedByScript = false;
        fire.Extinguish();
    }
}

void CFireManager::RemoveAllScriptFires() {
    return plugin::CallMethod<0x539720, CFireManager*>(this);
}

void CFireManager::ClearAllScriptFireFlags() {
    return plugin::CallMethod<0x5397A0, CFireManager*>(this);
}

void CFireManager::SetScriptFireAudio(short fireID, bool bFlag) {
    return plugin::CallMethod<0x5397B0, CFireManager*, short, bool>(this, fireID, bFlag);
}

const CVector& CFireManager::GetScriptFireCoords(short fireID) {
    return plugin::CallMethodAndReturn<const CVector&, 0x5397E0, CFireManager*, short>(this, fireID);
}

uint32_t CFireManager::GetNumFiresInRange(const CVector& point, float fRadiusSq) {
    return plugin::CallMethodAndReturn<uint32_t, 0x5397F0, CFireManager*, const CVector&, float>(this, point, fRadiusSq);
}

uint32_t CFireManager::GetNumFiresInArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    return plugin::CallMethodAndReturn<uint32_t, 0x539860, CFireManager*, float, float, float, float, float, float>(this, minX, minY, minZ, maxX, maxY, maxZ);
}

void CFireManager::DestroyAllFxSystems() {
    return plugin::CallMethod<0x539D10, CFireManager*>(this);
}

int8_t CFireManager::CreateAllFxSystems() {
    return plugin::CallMethodAndReturn<int8_t, 0x539D50, CFireManager*>(this);
}

void CFireManager::Shutdown() {
    return plugin::CallMethod<0x539DD0, CFireManager*>(this);
}

CFire * CFireManager::GetNextFreeFire(uint8_t bUnused) {
    return plugin::CallMethodAndReturn<CFire *, 0x539E50, CFireManager*, uint8_t>(this, bUnused);
}

CFire * CFireManager::StartFire(CVector pos, float size, uint8_t unused, CEntity * creator, uint time, signed char numGenerations, uint8_t unused_) {
    return plugin::CallMethodAndReturn<CFire *, 0x539F00, CFireManager*, CVector, float, uint8_t, CEntity *, uint, signed char, uint8_t>(this, pos, size, unused, creator, time, numGenerations, unused_);
}

CFire * CFireManager::StartFire(CEntity * target, CEntity * creator, float size, uint8_t unused, uint lifetime, signed char numGenerations) {
    return plugin::CallMethodAndReturn<CFire *, 0x53A050, CFireManager*, CEntity *, CEntity *, float, uint8_t, uint, signed char>(this, target, creator, size, unused, lifetime, numGenerations);
}

int32_t CFireManager::StartScriptFire(CVector const& pos, CEntity * pTarget, float _fUnused, uint8_t _nUnused, signed char nAllowedGenerations, int32_t nStrength) {
    return plugin::CallMethodAndReturn<int32_t, 0x53A270, CFireManager*, CVector const&, CEntity *, float, uint8_t, signed char, int32_t>(this, pos, pTarget, _fUnused, _nUnused, nAllowedGenerations, nStrength);
}

void CFireManager::Update() {
    return plugin::CallMethod<0x53AF00, CFireManager*>(this);
}
