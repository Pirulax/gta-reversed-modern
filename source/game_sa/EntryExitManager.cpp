#include "StdInc.h"

#include "EntryExitManager.h"

void CEntryExitManager::InjectHooks() {
    RH_ScopedClass(CEntryExitManager);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x43F880);
    RH_ScopedInstall(Shutdown, 0x440B90);
    RH_ScopedInstall(AddEntryExitToStack, 0x43E410);
    RH_ScopedInstall(Update, 0x440D10);
    RH_ScopedInstall(ShutdownForRestart, 0x440C40);
    RH_ScopedInstall(DeleteOne, 0x43FD50);
    RH_ScopedInstall(AddOne, 0x43FA00);
    RH_ScopedInstall(FindNearestDoor, 0x43F630);
    RH_ScopedInstall(FindNearestEntryExit, 0x43F4B0);
    RH_ScopedInstall(EnableBurglaryHouses, 0x43F180);
    RH_ScopedInstall(GetPositionRelativeToOutsideWorld, 0x43F150);
    RH_ScopedInstall(PostEntryExitsCreation, 0x43F0A0);
    RH_ScopedInstall(LinkEntryExit, 0x43F050);
    RH_ScopedInstall(GetEntryExitIndex, 0x43EFD0);
    RH_ScopedInstall(ResetAreaCodeForVisibleObjects, 0x43ED80);
    RH_ScopedInstall(SetAreaCodeForVisibleObjects, 0x43ECF0);
    RH_ScopedInstall(Load, 0x5D55C0);
    RH_ScopedInstall(Save, 0x5D5970);
}

// 0x43F880
void CEntryExitManager::Init() {
    mp_QuadTree = new CQuadTreeNode(WORLD_BOUNDS, 4);

    ms_exitEnterState = 0;
    ms_bDisabled = false;
    ms_entryExitStackPosn = 0;
    ms_bBurglaryHousesEnabled = false;

    mp_poolEntryExits = new CPool<CEntryExit>(400u, "Entry exits");
    mp_poolEntryExits->m_bIsLocked = true;
}

// 0x440B90
void CEntryExitManager::Shutdown() {
    for (auto i = 0; i < mp_poolEntryExits->GetSize(); i++) {
        if (const auto enex = mp_poolEntryExits->GetAt(i)) {
            mp_QuadTree->DeleteItem(enex);
        }
    }

    delete mp_poolEntryExits; // Flush() called in destructor
    mp_poolEntryExits = nullptr;

    delete mp_QuadTree;
    mp_QuadTree = nullptr;

    ms_entryExitStackPosn = 0;
}

// 0x440C40
void CEntryExitManager::ShutdownForRestart() {
    for (auto i = 0; i < mp_poolEntryExits->GetSize(); i++) {
        if (const auto enex = mp_poolEntryExits->GetAt(i)) {
            enex->bEnableAccess = true;
            if (enex->bDeleteEnex) {
                DeleteOne(i);
            }
        }
    }

    EnableBurglaryHouses(false);
    if (mp_Active) {
        ResetAreaCodeForVisibleObjects();
        ms_exitEnterState = 0;
        mp_Active = nullptr;
    }
    ms_entryExitStackPosn = 0;
    ms_bDisabled = false;

}

// 0x440D10
void CEntryExitManager::Update() {
    const bool bDontShowMarkers =
         CCutsceneMgr::ms_cutsceneProcessing
      || CPad::GetPad()->DisablePlayerControls
      || CGameLogic::IsCoopGameGoingOn()
      || CReplay::Mode == eReplayMode::MODE_PLAYBACK
      || CEntryExitManager::ms_bDisabled;

    if (!bDontShowMarkers && ms_exitEnterState == 0) { // Moved `bDontShowMarkers` here from inner loop
        CPtrListSingleLink matches{};

        auto x = TheCamera.m_mCameraMatrix.GetForward().x * 30.0f + TheCamera.GetPosition().x;
        auto y = TheCamera.m_mCameraMatrix.GetForward().y * 30.0f + TheCamera.GetPosition().y;
        CRect rect(x - 30.0f, y - 30.0f, x + 30.0f, y + 30.0f);
        mp_QuadTree->GetAllMatching(rect, matches);

        for (CPtrNode* it = matches.m_node, *next{}; it; it = next) {
            next = it->GetNext();

            auto* enex = it->ItemAs<CEntryExit>();
            if (enex->bEnableAccess) {
                if (   enex->m_pLink && enex->m_nArea == CGame::currArea  // Has link and link is in current area
                    || !enex->m_pLink && enex->m_nArea != CGame::currArea // Has no link, and is not in current area
                ) {
                    // !bDontShowMarkers check moved before the loop, as doing all this would be useless if bDontShowMarkers was false
                    if (const auto enexCenter = enex->GetPosition();  TheCamera.IsSphereVisible(enexCenter, 1.f)) {
                        if (!CClock::GetIsTimeInRange(enex->m_nTimeOn, enex->m_nTimeOff)) {
                            continue;
                        }

                        if ((enexCenter - TheCamera.GetPosition()).SquaredMagnitude() >= 40.f * 40.f) {
                            continue;
                        }

                        CVector markerPos{ enexCenter.x, enexCenter.y, enexCenter.z + 1.f };
                        C3dMarkers::PlaceMarkerCone((uint32)enex, markerPos, 2.0, 255, 255, 0, 255, 1024, 1.0, 5, 0);
                    }
                }
            }
        }
    }

    const auto& player = FindPlayerPed();
    if (mp_Active) {
        if (mp_Active->TransitionFinished(player)) {
            CEntryExitManager::mp_Active = nullptr;
        }
    } else {
        const auto& playerPos = FindPlayerEntity()->GetPosition();
        const auto pos = CVector2D{ playerPos.x, playerPos.y }; // todo: refactor
        CPtrListSingleLink matches{};
        mp_QuadTree->GetAllMatching(pos, matches);

        bool wasAnyMarkerInArea{};
        for (CPtrNode* it = matches.m_node, *next{}; it; it = next) {
            next = it->GetNext();

            auto* enex = it->ItemAs<CEntryExit>();
            if (enex->bEnableAccess && enex->IsInArea(playerPos)) {
                wasAnyMarkerInArea = true;
                if (!bDontShowMarkers && enex->TransitionStarted(player)) {
                    mp_Active = enex;
                    return;
                }
            }
        }

        if (!wasAnyMarkerInArea) {
            ms_exitEnterState = ms_exitEnterState != 3 ? 0 : 4; // TODO: Missing enum
        }

        // matches.Flush(); - Called in it's destructor
    }
}

// 0x43E410
void CEntryExitManager::AddEntryExitToStack(CEntryExit* enex) {
    if (enex->m_pLink)
        enex = enex->m_pLink;

    if (ms_entryExitStackPosn > 0 && ms_entryExitStack[ms_entryExitStackPosn - 1] == enex) {
        ms_entryExitStackPosn--;
    } else if (enex->m_nArea != AREA_CODE_NORMAL_WORLD) {
        ms_entryExitStack[ms_entryExitStackPosn++] = enex;
    } else {
        ms_entryExitStackPosn = 0;
    }
}

/*!
* @address 0x43FA00
* @brief Add a new entry exit
*
* @param timeOn If flag `BURGLARY_ACCESS` is not set it's going to define the value of enex->timeOn
* @param timeOff Unused
* @param name Name of the entry exit, may be nullptr. If flag `CREATE_LINKED_PAIR is set it is also used to identify the linked pair. (In this case it can't be nullptr)
*
* @returns The pool index of the created entry exit, 0 if failed.
*/
int32 CEntryExitManager::AddOne(float centerX, float centerY, float centerZ, float entranceAngle, float entranceRangeX, float entranceRangeY, float fUnused, float exitX,
                                float exitY, float exitZ, float exitAngle, int32 area, CEntryExit::eFlags flags, int32 skyColor, int32 timeOn, int32 timeOff, int32 numberOfPeds,
                                const char* name
) {
    const auto enex = mp_poolEntryExits->New();
    if (!enex) {
        assert(0); // NOTSA: Returns an actually valid index, instead of -1, so let's add an assert..
        return 0;
    }

    enex->m_nFlags = flags; // Set here, this way we can directly use the flag fields instead of using the enum

    // Deal with on/off (visibility) intervals
    if (enex->bBurglaryAccess) {
        enex->m_nTimeOn = 0;
        enex->m_nTimeOff = 24;
    } else {
        enex->m_nTimeOn = timeOn;
        enex->m_nTimeOff = timeOff;
    }

    if (enex->bUnknownBurglary && (CGeneral::GetRandomNumber() < RAND_MAX / 2)) {
        enex->m_nTimeOn = 0;
        enex->m_nTimeOff = 0;
    } else {
        enex->m_nTimeOff = timeOff;
    }

    if (ms_bBurglaryHousesEnabled || !enex->bBurglaryAccess) {
        enex->bEnableAccess = true;
    }

    enex->m_vecExitPos.Set(exitX, exitY, exitZ + 1.f);
    enex->m_nArea = (uint8)area;
    enex->m_nNumberOfPeds = (uint8)numberOfPeds;
    enex->m_fExitAngle = exitAngle;
    enex->m_nSkyColor = (uint8)skyColor;
    enex->m_pLink = nullptr;

    enex->m_fEntranceZ = centerZ + 1.f;
    enex->m_fEntranceAngle = DegreesToRadians(entranceAngle);

    if (name){
        strncpy_s(enex->m_szName, name, sizeof(enex->m_szName));
    } else {
        enex->m_szName[0] = 0;
    }

    enex->m_recEntrance = {
        centerX - entranceRangeX / 2.f,
        centerY - entranceRangeY / 2.f,
        centerX + entranceRangeX / 2.f,
        centerY + entranceRangeY / 2.f,
    };

    // Add EnEx to QuadTree
    {
        // Calculate bounding rectangle for it
        CMatrix enexmat;
        enexmat.SetRotateZ(entranceAngle);
        enexmat.GetPosition().Set(centerX, centerY, 0.f); // They didn't use this, but it's nicer this way, so lets do it.

        // Calculate corner positions
        const CVector2D corners[]{
            {  entranceRangeX / 2.f,  entranceRangeY / 2.f },
            { -entranceRangeX / 2.f, -entranceRangeY / 2.f },
        };

        // Now rotate these points by the rotation angle (`entranceAngle`) (Using the matrix)
        CVector2D rotatedCorners[std::size(corners)];
        rng::transform(corners, rotatedCorners, [&](auto&& p) { return CVector2D{ MultiplyMatrixWithVector(enexmat, CVector{ p.x, p.y, 0.0f }) }; });

        // Find min, max for the rect
        const auto [minX, maxX] = rng::minmax(rotatedCorners | rng::views::transform([](auto&& p) -> float { return p.x; })); // TODO: Use Vector operator[] and refactor this
        const auto [minY, maxY] = rng::minmax(rotatedCorners | rng::views::transform([](auto&& p) -> float { return p.y; }));

        // Add it to the QuadTree using the calculated bounding rect
        mp_QuadTree->AddItem(enex, {minX, minY, maxX, maxY});
    }

    LinkEntryExit(enex);

    return mp_poolEntryExits->GetIndex(enex);
}

// 0x43FD50
void CEntryExitManager::DeleteOne(int32 index) {
    if (const auto enex = mp_poolEntryExits->GetAt(index)) {
        mp_QuadTree->DeleteItem(enex);
        mp_poolEntryExits->Delete(enex);
    }
}

// 0x43F630
CObject* CEntryExitManager::FindNearestDoor(CEntryExit const& exit, float radius) {
    const auto entranceCenter = exit.GetPosition();

    CEntity* objsInRange[100]{};
    int16 numObjsInRange{};
    CWorld::FindObjectsInRange(entranceCenter, radius, false, &numObjsInRange, (int16)std::size(objsInRange), objsInRange, false, false, false, true, false);

    if (numObjsInRange) {
        float closestDistSq{ FLT_MAX };
        CObject* closest{};

        for (auto&& entity : std::span{ objsInRange, (size_t)numObjsInRange }) {
            const auto object = entity->AsObject();
            if (object->physicalFlags.bDisableMoveForce) {
                const auto distSq = (object->GetPosition() - entranceCenter).SquaredMagnitude(); // Using `SqMag` instead of `Mag`
                if (distSq < closestDistSq) {
                    closest = object;
                    closestDistSq = distSq;
                }
            }
        }
        return closest;
    }
    return nullptr;
}

// 0x43F4B0
int32 CEntryExitManager::FindNearestEntryExit(const CVector2D& position, float range, int32 ignoreArea) {
    CRect rect(position.x - range, position.y - range, position.x + range, position.y + range);
    CPtrListSingleLink enexInRange{};
    mp_QuadTree->GetAllMatching(rect, enexInRange);

    float closestDist2D{ 2.f * range };
    CEntryExit* closest{};
    for (CPtrNode* it = enexInRange.m_node, *next{}; it; it = next) {
        next = it->GetNext();

        auto* enex = it->ItemAs<CEntryExit>();
        if (enex->GetMyOrLinkedArea() != ignoreArea) {
            const auto dist = (enex->GetPosition2D() - position).Magnitude(); // TODO: Use SqMag
            if (dist < closestDist2D) {
                closest = enex;
                closestDist2D = dist;
            }
        }
    }

    return closest ? mp_poolEntryExits->GetIndex(closest) : -1;
}

// 0x43F180
void CEntryExitManager::EnableBurglaryHouses(bool enable) {
    ms_bBurglaryHousesEnabled = enable;
    for (auto i = 0; i < mp_poolEntryExits->GetSize(); i++) {
        if (const auto enex = mp_poolEntryExits->GetAt(i)) {
            enex->bBurglaryAccess = enable;
        }
    }
}

// 0x43F150
void CEntryExitManager::GetPositionRelativeToOutsideWorld(CVector& pos) {
    for (auto i = ms_entryExitStackPosn; i; i--) {
        ms_entryExitStack[i - 1]->GetPositionRelativeToOutsideWorld(pos);
    }
}

// 0x43F0A0
void CEntryExitManager::PostEntryExitsCreation() {
    for (auto i = 0; i < mp_poolEntryExits->GetSize(); i++) {
        if (const auto enex = mp_poolEntryExits->GetAt(i)) {
            if (enex->bCreateLinkedPair && !enex->m_pLink) {
                LinkEntryExit(enex);
            }
        }
    }
}

// 0x43F050
void CEntryExitManager::LinkEntryExit(CEntryExit* enex) {
    if (!enex->bCreateLinkedPair) {
        return;
    }

    const auto linkedEnExIdx{ GetEntryExitIndex(enex->m_szName, 0, CEntryExit::eFlags::CREATE_LINKED_PAIR) };
    if (linkedEnExIdx == -1) {
        return;
    }

    if (const auto linkedEnEx{ mp_poolEntryExits->GetAt(linkedEnExIdx) }) {
        enex->m_pLink = linkedEnEx;
        if (linkedEnEx->m_pLink) {
            linkedEnEx->m_pLink = enex;
        }
        linkedEnEx->m_nTimeOn = 0;
        linkedEnEx->m_nTimeOff = 24;
    }
}

// 0x43EFD0
int32 CEntryExitManager::GetEntryExitIndex(const char* name, uint16 enabledFlags, uint16 disabledFlags) {
    for (auto i = 0; i < mp_poolEntryExits->GetSize(); i++) {
        if (const auto enex = mp_poolEntryExits->GetAt(i)) {
            // Remember: cast to `uint8` == mask by 0xFF
            if (   (uint8)(enex->m_nFlags & enabledFlags) == (uint8)enabledFlags
                && (uint8)(enex->m_nFlags & disabledFlags) == 0
            ) {
                if (!_strnicmp(enex->m_szName, name, std::size(enex->m_szName))) {
                    return i;
                }
            }
        }
    }
    return -1;
}

// 0x43ED80
void CEntryExitManager::ResetAreaCodeForVisibleObjects() {
    while (ms_numVisibleEntities) {
        ms_visibleEntityList[--ms_numVisibleEntities]->m_nAreaCode = (eAreaCodes)ms_oldAreaCode;
    }
}

// 0x43ECF0
void CEntryExitManager::SetAreaCodeForVisibleObjects() {
    ms_numVisibleEntities = 0;

    auto objsInFrustum = (CEntity**)&PC_Scratch[256];
    const auto numObjsInFrustum = CRenderer::GetObjectsInFrustum(objsInFrustum, 6.f, nullptr);

    const auto playerPed{ FindPlayerPed() };

    for (auto&& entity : std::span{ objsInFrustum, (size_t)numObjsInFrustum }) {
        if (entity->m_nAreaCode == CGame::currArea && entity != playerPed) {
            ms_visibleEntityList[ms_numVisibleEntities++] = entity;
            entity->m_nAreaCode = AREA_CODE_13;

            if (ms_numVisibleEntities >= 32) {
                break;
            }
        }
    }

    ms_oldAreaCode = CGame::currArea;
}

// 0x5D55C0
bool CEntryExitManager::Load() {
    // Load entry exit stack
    CGenericGameStorage::LoadDataFromWorkBuffer(&ms_entryExitStackPosn, sizeof(ms_entryExitStackPosn));
    for (auto i = 0u; i < ms_entryExitStackPosn; i++) {
        uint16 enexIdx{};
        CGenericGameStorage::LoadDataFromWorkBuffer(&enexIdx, sizeof(enexIdx));
        ms_entryExitStack[i] = mp_poolEntryExits->GetAt(enexIdx);
    }

    // Load entry exits
    int16 enexIdx{};
    CGenericGameStorage::LoadDataFromWorkBuffer(&enexIdx, sizeof(enexIdx));
    while (enexIdx != -1) {
        uint16 flags{};
        CGenericGameStorage::LoadDataFromWorkBuffer(&flags, sizeof(flags));

        int16 linkedIdx{};
        CGenericGameStorage::LoadDataFromWorkBuffer(&linkedIdx, sizeof(linkedIdx));

        if (auto enex = mp_poolEntryExits->GetAt(enexIdx)) {
            if (linkedIdx == -1) {
                enex->m_pLink = nullptr;
            } else if (const auto linked = mp_poolEntryExits->GetAt(linkedIdx)) {
                enex->m_pLink = linked;
            } else {
                enex->m_pLink = nullptr;
            }
        } else {
            assert(0); // NOTSA - Probably corrupted save file or something.
        }

        CGenericGameStorage::LoadDataFromWorkBuffer(&enexIdx, sizeof(enexIdx));
    }

    return true;
}

// 0x5D5970
bool CEntryExitManager::Save() {
    // Save entry exit stack
    CGenericGameStorage::SaveDataToWorkBuffer(&ms_entryExitStackPosn, sizeof(ms_entryExitStackPosn));
    for (auto&& enex : std::span{ ms_entryExitStack, ms_entryExitStackPosn}) {
        CGenericGameStorage::SaveDataToWorkBuffer((uint16)mp_poolEntryExits->GetIndex(enex));
    }

    // Save entry exits
    for (auto i = 0; i < mp_poolEntryExits->GetSize(); i++) {
        if (const auto enex = mp_poolEntryExits->GetAt(i)) {
            CGenericGameStorage::SaveDataToWorkBuffer((uint16)i); // Enex idx in pool
            CGenericGameStorage::SaveDataToWorkBuffer((uint16)(enex->m_pLink ? mp_poolEntryExits->GetIndex(enex->m_pLink) : -1)); // Linked enex idx in pool
            CGenericGameStorage::SaveDataToWorkBuffer((uint16)enex->m_nFlags);
        }
    }

    return true;
}

bool CEntryExitManager::WeAreInInteriorTransition() {
    return plugin::CallAndReturn<bool, 0x43E400>();
}
