#include "StdInc.h"

#include "Radar.h"

uint32& CStreaming::ms_memoryAvailable = *reinterpret_cast<uint32*>(0x8A5A80);
int32& CStreaming::desiredNumVehiclesLoaded = *reinterpret_cast<int32*>(0x8A5A84);
bool& CStreaming::ms_bLoadVehiclesInLoadScene = *reinterpret_cast<bool*>(0x8A5A88);
int32* CStreaming::ms_aDefaultCopCarModel = reinterpret_cast<int32*>(0x8A5A8C);
int32& CStreaming::ms_DefaultCopBikeModel = *reinterpret_cast<int32*>(0x8A5A9C);
int32* CStreaming::ms_aDefaultCopModel = reinterpret_cast<int32*>(0x8A5AA0);
int32& CStreaming::ms_DefaultCopBikerModel = *reinterpret_cast<int32*>(0x8A5AB0);
uint32& CStreaming::ms_nTimePassedSinceLastCopBikeStreamedIn = *reinterpret_cast<uint32*>(0x9654C0);
signed int* CStreaming::ms_aDefaultAmbulanceModel = reinterpret_cast<signed int*>(0x8A5AB4);
signed int* CStreaming::ms_aDefaultMedicModel = reinterpret_cast<signed int*>(0x8A5AC4);
signed int* CStreaming::ms_aDefaultFireEngineModel = reinterpret_cast<signed int*>(0x8A5AD4);
signed int* CStreaming::ms_aDefaultFiremanModel = reinterpret_cast<signed int*>(0x8A5AE4);
CDirectory*& CStreaming::ms_pExtraObjectsDir = *reinterpret_cast<CDirectory**>(0x8E48D0);
tStreamingFileDesc (&CStreaming::ms_files)[TOTAL_IMG_ARCHIVES] = *(tStreamingFileDesc(*)[TOTAL_IMG_ARCHIVES])0x8E48D8;
bool& CStreaming::ms_bLoadingBigModel = *reinterpret_cast<bool*>(0x8E4A58);
// There are only two channels within CStreaming::ms_channel
tStreamingChannel* CStreaming::ms_channel = reinterpret_cast<tStreamingChannel*>(0x8E4A60);
signed int& CStreaming::ms_channelError = *reinterpret_cast<signed int*>(0x8E4B90);
bool& CStreaming::m_bHarvesterModelsRequested = *reinterpret_cast<bool*>(0x8E4B9C);
bool& CStreaming::m_bStreamHarvesterModelsThisFrame = *reinterpret_cast<bool*>(0x8E4B9D);
uint32& CStreaming::ms_numPriorityRequests = *reinterpret_cast<uint32*>(0x8E4BA0);
int32& CStreaming::ms_lastCullZone = *reinterpret_cast<int32*>(0x8E4BA4);
uint16& CStreaming::ms_loadedGangCars = *reinterpret_cast<uint16*>(0x8E4BA8);
uint16& CStreaming::ms_loadedGangs = *reinterpret_cast<uint16*>(0x8E4BAC);
int32& CStreaming::ms_numPedsLoaded = *reinterpret_cast<int32*>(0x8E4BB0);
int32* CStreaming::ms_pedsLoaded = reinterpret_cast<int32*>(0x8E4C00);
int32* CStreaming::ms_NextPedToLoadFromGroup = reinterpret_cast<int32*>(0x8E4BB8);
int32& CStreaming::ms_currentZoneType = *reinterpret_cast<int32*>(0x8E4C20);
CLoadedCarGroup& CStreaming::ms_vehiclesLoaded = *reinterpret_cast<CLoadedCarGroup*>(0x8E4C24);
CStreamingInfo*& CStreaming::ms_pEndRequestedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C54);
CStreamingInfo*& CStreaming::ms_pStartRequestedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C58);
CStreamingInfo*& CStreaming::ms_pEndLoadedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C5C);
CStreamingInfo*& CStreaming::ms_startLoadedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C60);
int32& CStreaming::ms_lastImageRead = *reinterpret_cast<int32*>(0x8E4C64);
signed int* CStreaming::ms_imageOffsets = reinterpret_cast<signed int*>(0x8E4C8C);
bool& CStreaming::ms_bEnableRequestListPurge = *reinterpret_cast<bool*>(0x8E4CA4);
uint32& CStreaming::ms_streamingBufferSize = *reinterpret_cast<uint32*>(0x8E4CA8);
uint8** CStreaming::ms_pStreamingBuffer = reinterpret_cast<uint8**>(0x8E4CAC);
uint32& CStreaming::ms_memoryUsed = *reinterpret_cast<uint32*>(0x8E4CB4);
int32& CStreaming::ms_numModelsRequested = *reinterpret_cast<int32*>(0x8E4CB8);
CStreamingInfo* CStreaming::ms_aInfoForModel = reinterpret_cast<CStreamingInfo*>(0x8E4CC0);
bool& CStreaming::ms_disableStreaming = *reinterpret_cast<bool*>(0x9654B0);
int32& CStreaming::ms_bIsInitialised = *reinterpret_cast<int32*>(0x9654B8);
bool& CStreaming::m_bBoatsNeeded = *reinterpret_cast<bool*>(0x9654BC);
bool& CStreaming::ms_bLoadingScene = *reinterpret_cast<bool*>(0x9654BD);
bool& CStreaming::m_bCopBikeLoaded = *reinterpret_cast<bool*>(0x9654BE);
bool& CStreaming::m_bDisableCopBikes = *reinterpret_cast<bool*>(0x9654BF);
CLinkList<CEntity*>& CStreaming::ms_rwObjectInstances = *reinterpret_cast<CLinkList<CEntity*>*>(0x9654F0);
CLink<CEntity*>*& CStreaming::ms_renderEntityLink = *reinterpret_cast<CLink<CEntity*>**>(0x8E48A0);
RwStream& gRwStream = *reinterpret_cast<RwStream*>(0x8E48AC);
bool& CStreaming::m_bLoadingAllRequestedModels = *reinterpret_cast<bool*>(0x965538);
bool& CStreaming::m_bModelStreamNotLoaded = *reinterpret_cast<bool*>(0x9654C4);
static int32& CurrentGangMemberToLoad = *(int32*)0x9654D4;

void CStreaming::InjectHooks()
{
    using namespace ReversibleHooks;
    Install("CStreaming", "AddEntity",0x409650, &CStreaming::AddEntity);
    Install("CStreaming", "AddImageToList",0x407610, &CStreaming::AddImageToList);
    Install("CStreaming", "AddLodsToRequestList",0x40C520, &CStreaming::AddLodsToRequestList);
    Install("CStreaming", "AddModelsToRequestList",0x40D3F0, &CStreaming::AddModelsToRequestList);
    Install("CStreaming", "AreAnimsUsedByRequestedModels",0x407AD0, &CStreaming::AreAnimsUsedByRequestedModels);
    Install("CStreaming", "AreTexturesUsedByRequestedModels",0x409A90, &CStreaming::AreTexturesUsedByRequestedModels);
    Install("CStreaming", "ClearFlagForAll",0x407A40, &CStreaming::ClearFlagForAll);
    Install("CStreaming", "ClearSlots",0x40BAA0, &CStreaming::ClearSlots);
    Install("CStreaming", "GetNextFileOnCd",0x408E20, &CStreaming::GetNextFileOnCd);
    Install("CStreaming", "HasSpecialCharLoaded",0x407F00, &CStreaming::HasSpecialCharLoaded);
    Install("CStreaming", "HasVehicleUpgradeLoaded",0x407820, &CStreaming::HasVehicleUpgradeLoaded);
    Install("CStreaming", "ConvertBufferToObject",0x40C6B0, &CStreaming::ConvertBufferToObject);
    Install("CStreaming", "DeleteAllRwObjects",0x4090A0, &CStreaming::DeleteAllRwObjects);
    Install("CStreaming", "DeleteLeastUsedEntityRwObject",0x409760, &CStreaming::DeleteLeastUsedEntityRwObject);
    Install("CStreaming", "DeleteRwObjectsAfterDeath",0x409210, &CStreaming::DeleteRwObjectsAfterDeath);
    Install("CStreaming", "DeleteRwObjectsBehindCamera",0x40D7C0, &CStreaming::DeleteRwObjectsBehindCamera);
    Install("CStreaming", "DeleteRwObjectsBehindCameraInSectorList",0x409940, &CStreaming::DeleteRwObjectsBehindCameraInSectorList);
    Install("CStreaming", "DeleteRwObjectsInSectorList",0x407A70, &CStreaming::DeleteRwObjectsInSectorList);
    Install("CStreaming", "DeleteRwObjectsNotInFrustumInSectorList",0x4099E0, &CStreaming::DeleteRwObjectsNotInFrustumInSectorList);
    Install("CStreaming", "RemoveReferencedTxds",0x40D2F0, &CStreaming::RemoveReferencedTxds);
    Install("CStreaming", "DisableCopBikes",0x407D10, &CStreaming::DisableCopBikes);
    Install("CStreaming", "IsVeryBusy",0x4076A0, &CStreaming::IsVeryBusy);
    Install("CStreaming", "Load",0x5D29E0, &CStreaming::Load);
    Install("CStreaming", "LoadAllRequestedModels",0x40EA10, &CStreaming::LoadAllRequestedModels);
    Install("CStreaming", "LoadCdDirectory_char", 0x5B6170, (void(*)(const char*, int32)) & CStreaming::LoadCdDirectory);
    Install("CStreaming", "LoadCdDirectory_void", 0x5B82C0, (void(*)()) & CStreaming::LoadCdDirectory);
    Install("CStreaming", "LoadInitialPeds",0x40D3D0, &CStreaming::LoadInitialPeds);
    Install("CStreaming", "LoadInitialWeapons",0x40A120, &CStreaming::LoadInitialWeapons);
    Install("CStreaming", "LoadScene",0x40EB70, &CStreaming::LoadScene);
    Install("CStreaming", "LoadSceneCollision",0x40ED80, &CStreaming::LoadSceneCollision);
    Install("CStreaming", "LoadZoneVehicle",0x40B4B0, &CStreaming::LoadZoneVehicle);
    Install("CStreaming", "PossiblyStreamCarOutAfterCreation",0x40BA70, &CStreaming::PossiblyStreamCarOutAfterCreation);
    Install("CStreaming", "RenderEntity",0x4096D0, &CStreaming::RenderEntity);
    Install("CStreaming", "RequestBigBuildings",0x409430, &CStreaming::RequestBigBuildings);
    Install("CStreaming", "RequestFile",0x40A080, &CStreaming::RequestFile);
    Install("CStreaming", "RequestFilesInChannel",0x409050, &CStreaming::RequestFilesInChannel);
    Install("CStreaming", "RequestModel",0x4087E0, &CStreaming::RequestModel);
    Install("CStreaming", "RequestTxdModel",0x407100, &CStreaming::RequestTxdModel);
    Install("CStreaming", "RequestVehicleUpgrade",0x408C70, &CStreaming::RequestVehicleUpgrade);
    Install("CStreaming", "FindMIPedSlotForInterior",0x407FB0, &CStreaming::FindMIPedSlotForInterior);
    Install("CStreaming", "FinishLoadingLargeFile",0x408CB0, &CStreaming::FinishLoadingLargeFile);
    Install("CStreaming", "FlushChannels",0x40E460, &CStreaming::FlushChannels);
    Install("CStreaming", "RequestModelStream",0x40CBA0, &CStreaming::RequestModelStream);
    Install("CStreaming", "RequestSpecialChar",0x40B450, &CStreaming::RequestSpecialChar);
    Install("CStreaming", "RequestSpecialModel",0x409D10, &CStreaming::RequestSpecialModel);
    Install("CStreaming", "ProcessLoadingChannel",0x40E170, &CStreaming::ProcessLoadingChannel);
    Install("CStreaming", "PurgeRequestList",0x40C1E0, &CStreaming::PurgeRequestList);
    Install("CStreaming", "ReInit",0x40E560, &CStreaming::ReInit);
    Install("CStreaming", "ReadIniFile",0x5BCCD0, &CStreaming::ReadIniFile);
    Install("CStreaming", "ReclassifyLoadedCars",0x40AFA0, &CStreaming::ReclassifyLoadedCars);
    Install("CStreaming", "RemoveAllUnusedModels",0x40CF80, &CStreaming::RemoveAllUnusedModels);
    Install("CStreaming", "RemoveBigBuildings",0x4093B0, &CStreaming::RemoveBigBuildings);
    Install("CStreaming", "RemoveBuildingsNotInArea",0x4094B0, &CStreaming::RemoveBuildingsNotInArea);
    Install("CStreaming", "RemoveCarModel",0x4080F0, &CStreaming::RemoveCarModel);
    Install("CStreaming", "RemoveCurrentZonesModels",0x40B080, &CStreaming::RemoveCurrentZonesModels);
    Install("CStreaming", "RemoveDodgyPedsFromRandomSlots",0x40BE60, &CStreaming::RemoveDodgyPedsFromRandomSlots);
    Install("CStreaming", "RemoveEntity",0x409710, &CStreaming::RemoveEntity);
    Install("CStreaming", "RemoveInappropriatePedModels",0x40B3A0, &CStreaming::RemoveInappropriatePedModels);
    Install("CStreaming", "RemoveLeastUsedModel",0x40CFD0, &CStreaming::RemoveLeastUsedModel);
    Install("CStreaming", "RemoveLoadedVehicle",0x40C020, &CStreaming::RemoveLoadedVehicle);
    Install("CStreaming", "RemoveLoadedZoneModel",0x40B340, &CStreaming::RemoveLoadedZoneModel);
    Install("CStreaming", "RemoveModel",0x4089A0, &CStreaming::RemoveModel);
    Install("CStreaming", "RemoveTxdModel",0x40C180, &CStreaming::RemoveTxdModel);
    Install("CStreaming", "MakeSpaceFor",0x40E120, &CStreaming::MakeSpaceFor);
    Install("CStreaming", "ProcessEntitiesInSectorList", 0x40C270, (void(*)(CPtrList&, float, float, float, float, float, float, float, int32)) & CStreaming::ProcessEntitiesInSectorList);
    Install("CStreaming", "RetryLoadFile",0x4076C0, &CStreaming::RetryLoadFile);
    Install("CStreaming", "LoadRequestedModels",0x40E3A0, &CStreaming::LoadRequestedModels);
    Install("CStreaming", "FlushRequestList",0x40E4E0, &CStreaming::FlushRequestList);
    Install("CStreaming", "AddToLoadedVehiclesList",0x408000, &CStreaming::AddToLoadedVehiclesList);
    Install("CStreaming", "GetDefaultCabDriverModel",0x407D50, &CStreaming::GetDefaultCabDriverModel);
    Install("CStreaming", "GetDefaultFiremanModel",0x407D40, &CStreaming::GetDefaultFiremanModel);
    Install("CStreaming", "GetDefaultMedicModel",0x407D20, &CStreaming::GetDefaultMedicModel);
    Install("CStreaming", "GetDefaultCopCarModel",0x407C50, &CStreaming::GetDefaultCopCarModel);
    Install("CStreaming", "GetDefaultCopModel",0x407C00, &CStreaming::GetDefaultCopModel);
    Install("CStreaming", "Init2",0x5B8AD0, &CStreaming::Init2);
    Install("CStreaming", "InitImageList",0x4083C0, &CStreaming::InitImageList);
    Install("CStreaming", "InstanceLoadedModels",0x4084F0, &CStreaming::InstanceLoadedModels);
    Install("CStreaming", "IsCarModelNeededInCurrentZone",0x407DD0, &CStreaming::IsCarModelNeededInCurrentZone);
    Install("CStreaming", "SetMissionDoesntRequireModel",0x409C90, &CStreaming::SetMissionDoesntRequireModel);
    Install("CStreaming", "SetModelIsDeletable",0x409C10, &CStreaming::SetModelIsDeletable);
    Install("CStreaming", "Shutdown",0x4084B0, &CStreaming::Shutdown);
    Install("CStreaming", "StreamAmbulanceAndMedic",0x40A2A0, &CStreaming::StreamAmbulanceAndMedic);
    Install("CStreaming", "StreamCopModels",0x40A150, &CStreaming::StreamCopModels);
    Install("CStreaming", "StreamFireEngineAndFireman",0x40A400, &CStreaming::StreamFireEngineAndFireman);
    Install("CStreaming", "StreamOneNewCar",0x40B4F0, &CStreaming::StreamOneNewCar);
    Install("CStreaming", "StreamPedsForInterior",0x40BBB0, &CStreaming::StreamPedsForInterior);
    Install("CStreaming", "StreamPedsIntoRandomSlots",0x40BDA0, &CStreaming::StreamPedsIntoRandomSlots);
    Install("CStreaming", "StreamVehiclesAndPeds",0x40B700, &CStreaming::StreamVehiclesAndPeds);
    Install("CStreaming", "StreamVehiclesAndPeds_Always",0x40B650, &CStreaming::StreamVehiclesAndPeds_Always);
    Install("CStreaming", "StreamZoneModels",0x40A560, &CStreaming::StreamZoneModels);
    Install("CStreaming", "StreamZoneModels_Gangs",0x40AA10, &CStreaming::StreamZoneModels_Gangs);
    Install("CStreaming", "Update",0x40E670, &CStreaming::Update);
    Install("CStreaming", "WeAreTryingToPhaseVehicleOut",0x407F80, &CStreaming::WeAreTryingToPhaseVehicleOut);
}

// 0x409650
CLink<CEntity*>* CStreaming::AddEntity(CEntity* pEntity) {
    switch (pEntity->GetType()) {
    case eEntityType::ENTITY_TYPE_PED:
    case eEntityType::ENTITY_TYPE_VEHICLE:
        return nullptr;
    }
    
    CLink<CEntity*>* link = ms_rwObjectInstances.Insert(pEntity);
    if (!link) {
        CLink<CEntity*>* previousLink = ms_rwObjectInstances.usedListTail.prev;
        for (; previousLink != &ms_rwObjectInstances.usedListHead; previousLink = previousLink->prev) {
            CEntity* entity = previousLink->data;
            if (!entity->m_bImBeingRendered && !entity->m_bStreamingDontDelete)
                break;
        }
        if (previousLink == &ms_rwObjectInstances.usedListHead)
            return ms_rwObjectInstances.Insert(pEntity);
        previousLink->data->DeleteRwObject();
        link = ms_rwObjectInstances.Insert(pEntity);
    }
    return link;
}

// 0x407610
void CStreaming::AddImageToList(char const* pFileName, bool bNotPlayerImg) {
    for (tStreamingFileDesc& file : ms_files) {
        if (!file.IsInUse()) {
            // Not in use, so make entry
            file = { pFileName, bNotPlayerImg };

            // Success
            return;
        }
    }
    // If it reaches this point it failed to find an empty file slot
    assert(0); // NOTSA
}

// 0x40C520
void CStreaming::AddLodsToRequestList(CVector const& point, uint32 streamingFlags) {
    CWorld::IncrementCurrentScanCode();

    float minX = point.x - CRenderer::ms_fFarClipPlane;
    float maxX = point.x + CRenderer::ms_fFarClipPlane;
    float minY = point.y - CRenderer::ms_fFarClipPlane;
    float maxY = point.y + CRenderer::ms_fFarClipPlane;

    int32 startSectorX = std::max(CWorld::GetLodSectorX(minX), 0);
    int32 startSectorY = std::max(CWorld::GetLodSectorY(minY), 0);
    int32 endSectorX = std::min(CWorld::GetLodSectorX(maxX), MAX_LOD_PTR_LISTS_X - 1);
    int32 endSectorY = std::min(CWorld::GetLodSectorY(maxY), MAX_LOD_PTR_LISTS_Y - 1);

    for (int32 sy = startSectorY; sy <= endSectorY; ++sy) {
        for (int32 sx = startSectorX; sx <= endSectorX; ++sx) {
            ProcessEntitiesInSectorList(CWorld::GetLodPtrList(sx, sy), point.x, point.y, minX, minY, maxX, maxY, CRenderer::ms_fFarClipPlane, streamingFlags);
        }
    }
}

// 0x40D3F0
void CStreaming::AddModelsToRequestList(CVector const& point, uint32 streamingFlags) {
    CWorld::IncrementCurrentScanCode();

    const float fRadius = CGame::IsInNormalWorld() ? 80.0f : 40.0f;

    // Defines a rectangle outside of which models won't be loaded.
    const auto min = point - CVector2D{ fRadius, fRadius },
               max = point + CVector2D{ fRadius, fRadius };

    const auto noCheckRadius = static_cast<int32>(CWorld::GetHalfMapSectorX(fRadius));

    // Smaller radius, models in it are loaded regardless if they're in the rectangle
    // defined by `min` `max` or in `fRadius`.
    const int32 radiusInnerSq = (noCheckRadius - 1) * (noCheckRadius - 1);

    // Bigger radius, models in it are loaded only if in the above mentioned
    // rectangle and radius.
    const int32 radiusOuterSq = (noCheckRadius + 2) * (noCheckRadius + 2);

    const int32 pointX = CWorld::GetSectorX(point.x);
    const int32 pointY = CWorld::GetSectorY(point.y);

    int32 startSectorX = std::max(CWorld::GetSectorX(min.x), 0);
    int32 startSectorY = std::max(CWorld::GetSectorY(min.y), 0);
    int32 endSectorX = std::min(CWorld::GetSectorX(max.x), MAX_SECTORS_X - 1);
    int32 endSectorY = std::min(CWorld::GetSectorY(max.y), MAX_SECTORS_Y - 1);

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
            CSector* pSector = GetSector(sectorX, sectorY);

            const int32 distanceY = sectorY - pointY;
            const int32 squaredDistanceY = distanceY * distanceY;
            const int32 distanceX = sectorX - pointX;
            const int32 pointSectorDistSq = distanceX * distanceX + squaredDistanceY;

            if (pointSectorDistSq <= radiusInnerSq) {
                ProcessEntitiesInSectorList(pSector->m_buildings, streamingFlags);
                ProcessEntitiesInSectorList(pRepeatSector->GetList(REPEATSECTOR_PEDS), streamingFlags);
                ProcessEntitiesInSectorList(pSector->m_dummies, streamingFlags);
            } else {
                if (pointSectorDistSq <= radiusOuterSq) {
                    ProcessEntitiesInSectorList(pSector->m_buildings, point.x, point.y, min.x, min.y, max.x, max.y, fRadius, streamingFlags);
                    ProcessEntitiesInSectorList(pRepeatSector->GetList(REPEATSECTOR_PEDS), point.x, point.y, min.x, min.y, max.x, max.y, fRadius, streamingFlags);
                    ProcessEntitiesInSectorList(pSector->m_dummies, point.x, point.y, min.x, min.y, max.x, max.y, fRadius, streamingFlags);
                }
            }
        }
    }
}

// 0x407AD0
bool CStreaming::AreAnimsUsedByRequestedModels(int32 animModelId) {
    for (auto info = ms_pStartRequestedList->GetNext(); info != ms_pEndRequestedList; info = info->GetNext()) {
        const int32 modelId = info - ms_aInfoForModel;
        if (modelId < RESOURCE_ID_TXD /*model is DFF*/ && CModelInfo::ms_modelInfoPtrs[modelId]->GetAnimFileIndex() == animModelId)
            return true;
    }

    for (int32 channelId = 0; channelId < 2; channelId++) {
        tStreamingChannel& channel = ms_channel[channelId];
        for (int32 model : channel.modelIds) {
            if (model != -1 && model < RESOURCE_ID_TXD /*model is DFF*/ &&
                CModelInfo::ms_modelInfoPtrs[model]->GetAnimFileIndex() == animModelId)
            {
                return true;
            }
        }   
    }

    return false;
}

// 0x409A90
bool CStreaming::AreTexturesUsedByRequestedModels(int32 txdModelId) {
    for (auto info = ms_pStartRequestedList->GetNext(); info != ms_pEndRequestedList; info = info->GetNext()) {
        int32 modelId = info - ms_aInfoForModel;
        if (modelId < RESOURCE_ID_TXD/*model is DFF*/) {
            if (CModelInfo::ms_modelInfoPtrs[modelId]->m_nTxdIndex == txdModelId)
                return true;
        } else if (modelId < RESOURCE_ID_COL/*model is TXD*/) {
            if (CTxdStore::GetParentTxdSlot(modelId - RESOURCE_ID_TXD) == txdModelId)
                return true;
        }
    }

    for (int32 channelId = 0; channelId < 2; channelId++) {
        tStreamingChannel& channel = ms_channel[channelId];
        for (int32 model : channel.modelIds) {
            if (model != -1) {
                if (model < RESOURCE_ID_TXD/*model is DFF*/) {
                    if (CModelInfo::ms_modelInfoPtrs[model]->m_nTxdIndex == txdModelId)
                        return true;
                }
                else if (model < RESOURCE_ID_COL/*model is TXD*/) {
                    if (CTxdStore::GetParentTxdSlot(model - RESOURCE_ID_TXD) == txdModelId)
                        return true;
                }
            }
        }
    }

    return false;
}

// 0x407A40
void CStreaming::ClearFlagForAll(uint32 streamingFlag) {
    for (int32 i = 0; i < RESOURCE_ID_TOTAL; i++) {
        ms_aInfoForModel[i].m_nFlags &= ~streamingFlag;
    }
}

// 0x40BAA0
void CStreaming::ClearSlots(int32 totalSlots) {
    for (int32 i = 0; i < totalSlots; ++i) {
        int32 modelId = ms_pedsLoaded[i];
        if (modelId >= 0) {
            SetModelIsDeletable(modelId);
            SetModelTxdIsDeletable(modelId);
            ms_pedsLoaded[i] = -1;
            ms_numPedsLoaded--;
        }
    }
}

// 0x408E20
int32 CStreaming::GetNextFileOnCd(uint32 streamLastPosn, bool bNotPriority) {
    uint32 nextRequestModelPos = UINT32_MAX;
    uint32 firstRequestModelCdPos = UINT32_MAX;
    int32 firstRequestModelId = -1;
    int32 nextRequestModelId = -1;
    CStreamingInfo* info = ms_pStartRequestedList->GetNext();
    for (; info != ms_pEndRequestedList; info = info->GetNext()) {
        const int32 modelId = info - ms_aInfoForModel;
        if (!bNotPriority || ms_numPriorityRequests == 0 || info->m_nFlags & STREAMING_PRIORITY_REQUEST) {
            // Additional conditions for some model types (DFF, TXD, IFP)
            if (modelId < RESOURCE_ID_TXD/*model is DFF*/) {
                CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];

                // Make sure TXD will be loaded for this model
                const int16 txdIndex = pModelInfo->m_nTxdIndex;
                if (!ms_aInfoForModel[txdIndex + RESOURCE_ID_TXD].IsLoadedOrBeingRead()) {
                    RequestModel(txdIndex + RESOURCE_ID_TXD, ms_aInfoForModel[modelId].m_nFlags); // Request TXD for this DFF
                    continue;
                }

                // Check if it has an anim (IFP), if so, make sure it gets loaded
                const int32 animFileIndex = pModelInfo->GetAnimFileIndex();
                if (animFileIndex != -1) {
                    const int32 animModelId = animFileIndex + RESOURCE_ID_IFP;
                    if (!ms_aInfoForModel[animModelId].IsLoadedOrBeingRead()) {
                        RequestModel(animModelId, STREAMING_KEEP_IN_MEMORY);
                        continue;
                    }
                }
            }
            else if (modelId < RESOURCE_ID_COL/*model is TXD*/) {
                // Make sure parent is/will be loaded
                TxdDef* pTexDictionary = CTxdStore::ms_pTxdPool->GetAt(modelId - RESOURCE_ID_TXD);
                const int16 parentIndex = pTexDictionary->m_wParentIndex;
                if (parentIndex != -1) {
                    const int32 parentModelIdx = parentIndex + RESOURCE_ID_TXD;
                    if (!ms_aInfoForModel[parentModelIdx].IsLoadedOrBeingRead()) {
                        RequestModel(parentModelIdx, STREAMING_KEEP_IN_MEMORY);
                        continue;
                    }
                }
            }
            else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR/*model is IFP*/)
            {
                if (CCutsceneMgr::ms_cutsceneProcessing || ms_aInfoForModel[MODEL_MALE01].m_nLoadState != LOADSTATE_LOADED) {
                    // Skip in this case
                    continue;
                }
            }

            const uint32 modelCdPos = ms_aInfoForModel[modelId].GetCdPosn();
            if (modelCdPos < firstRequestModelCdPos) {
                firstRequestModelCdPos = modelCdPos;
                firstRequestModelId = modelId;
            }
            if (modelCdPos < nextRequestModelPos && modelCdPos >= streamLastPosn) {
                nextRequestModelPos = modelCdPos;
                nextRequestModelId = modelId;
            }
        }
    }

    const int32 nextModelId = nextRequestModelId == -1 ? firstRequestModelId : nextRequestModelId;
    if (nextModelId != -1 || ms_numPriorityRequests == 0)
        return nextModelId;

    ms_numPriorityRequests = 0;
    return nextModelId;
}

// 0x407F00
bool CStreaming::HasSpecialCharLoaded(int32 slot) {
    return ms_aInfoForModel[slot + SPECIAL_MODELS_RESOURCE_ID].m_nLoadState == LOADSTATE_LOADED;
}

// 0x407820
bool CStreaming::HasVehicleUpgradeLoaded(int32 modelId) {
    if (ms_aInfoForModel[modelId].m_nLoadState != LOADSTATE_LOADED)
        return false;

    const int16 otherUpgradeModelId = CVehicleModelInfo::ms_linkedUpgrades.FindOtherUpgrade(modelId);
    return otherUpgradeModelId == -1 || ms_aInfoForModel[otherUpgradeModelId].m_nLoadState == LOADSTATE_LOADED;
}

// 0x40C6B0
bool CStreaming::ConvertBufferToObject(uint8* pFileBuffer, int32 modelId)
{
    CStreamingInfo* pStartLoadedListStreamingInfo = ms_startLoadedList;;
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];

    const int32 bufferSize = streamingInfo.GetCdSize() * STREAMING_SECTOR_SIZE;
    tRwStreamInitializeData rwStreamInitData = { pFileBuffer, bufferSize };

    // Make RW stream from memory
    // TODO: The _ prefix seems to indicate its "private" (maybe), perhaps it was some kind of macro originally?
    RwStream* pRwStream = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitData);

    if (modelId >= RESOURCE_ID_DFF && modelId < RESOURCE_ID_TXD /*model is DFF*/) {

        // Check if TXD and IFP are loaded
        const int32 animFileIndex = pBaseModelInfo->GetAnimFileIndex();
        const int16 nTXDIdx = pBaseModelInfo->m_nTxdIndex;
        const TxdDef* pTxdDef = CTxdStore::ms_pTxdPool->GetAt(nTXDIdx);
        if ((pTxdDef && !pTxdDef->m_pRwDictionary) || /*check TXD (if any)*/
            animFileIndex != -1 && !CAnimManager::ms_aAnimBlocks[animFileIndex].bLoaded /*check anim (if any)*/
        ) {
            // TXD or IFP not loaded, rerequest model. (I dont think this is supposed to happen at all)
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }

        CTxdStore::AddRef(nTXDIdx);
        if (animFileIndex != -1)
            CAnimManager::AddAnimBlockRef(animFileIndex);
        CTxdStore::SetCurrentTxd(pBaseModelInfo->m_nTxdIndex);

        bool bFileLoaded = false;
        if (pBaseModelInfo->GetRwModelType() == rpATOMIC) {
            RwChunkHeaderInfo chunkHeaderInfo;
            RwStreamReadChunkHeaderInfo(pRwStream, &chunkHeaderInfo);

            RtDict* pRtDictionary = nullptr;
            if (chunkHeaderInfo.type == rwID_UVANIMDICT) {
                pRtDictionary = RtDictSchemaStreamReadDict(&RpUVAnimDictSchema, pRwStream);
                RtDictSchemaSetCurrentDict(&RpUVAnimDictSchema, pRtDictionary);
            }
            RwStreamClose(pRwStream, &rwStreamInitData);

            // Load atomic file, we need a separate stream for it (presumeably to not mess up the cursor pos)
            // TODO: It seems like this stream is never closed...
            RwStream* pRwStream2 = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitData);
            bFileLoaded = CFileLoader::LoadAtomicFile(pRwStream2, modelId);
            if (pRtDictionary) {
                RtDictDestroy(pRtDictionary);
            }
        } else {
            bFileLoaded = CFileLoader::LoadClumpFile(pRwStream, modelId);
        }

        if (streamingInfo.m_nLoadState != LOADSTATE_FINISHING)
        {
            CTxdStore::RemoveRefWithoutDelete(pBaseModelInfo->m_nTxdIndex);
            if (animFileIndex != -1)
                CAnimManager::RemoveAnimBlockRefWithoutDelete(animFileIndex);

            if (bFileLoaded && pBaseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
            {
                if (!AddToLoadedVehiclesList(modelId))
                {
                    RemoveModel(modelId);
                    RequestModel(modelId, streamingInfo.m_nFlags);
                    RwStreamClose(pRwStream, &rwStreamInitData);
                    return false;
                }
            }
        }

        if (!bFileLoaded)
        {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }

    }
    else if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL/*model is TXD*/) {
        const int32 modelTxdIndex = modelId - RESOURCE_ID_TXD;
        const TxdDef* pTxdDef = CTxdStore::ms_pTxdPool->GetAt(modelTxdIndex);
        if (pTxdDef) {
            const int32 parentTXDIdx = pTxdDef->m_wParentIndex;
            if (parentTXDIdx != -1 && !CTxdStore::GetTxd(parentTXDIdx)) {
                // Parent not loaded, re-request..
                RemoveModel(modelId);
                RequestModel(modelId, streamingInfo.m_nFlags);
                RwStreamClose(pRwStream, &rwStreamInitData);
                return false;
            }
        }

        if (!(streamingInfo.m_nFlags & (STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED))
            && !AreTexturesUsedByRequestedModels(modelTxdIndex))
        {
            // Model not needed anymore, unload
            RemoveModel(modelId);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }

        bool bTxdLoaded = false;
        if (ms_bLoadingBigModel) {
            bTxdLoaded = CTxdStore::StartLoadTxd(modelTxdIndex, pRwStream);
            if (bTxdLoaded)
                streamingInfo.m_nLoadState = LOADSTATE_FINISHING;
        } else {
            bTxdLoaded = CTxdStore::LoadTxd(modelTxdIndex, pRwStream);
        }
        if (!bTxdLoaded) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }
    }
    else if (modelId >= RESOURCE_ID_COL && modelId < RESOURCE_ID_IPL/*model is COL*/) {
        if (!CColStore::LoadCol(modelId - RESOURCE_ID_COL, pFileBuffer, bufferSize)) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }
    }
    else if (modelId >= RESOURCE_ID_IPL && modelId < RESOURCE_ID_DAT/*model is IPL*/) {
        if (!CIplStore::LoadIpl(modelId - RESOURCE_ID_IPL, pFileBuffer, bufferSize)) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }
    }
    else if (modelId >= RESOURCE_ID_DAT && modelId < RESOURCE_ID_IFP/*model is DAT*/) {
        ThePaths.LoadPathFindData(pRwStream, modelId - RESOURCE_ID_DAT);
    }
    else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR/*model is IFP*/) {
        if (!(streamingInfo.m_nFlags & (STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED))
            && !AreAnimsUsedByRequestedModels(modelId - RESOURCE_ID_IFP))
        {
            // Not required anymore, unload
            RemoveModel(modelId);
            RwStreamClose(pRwStream, &rwStreamInitData);
            return false;
        }
        // Still required, load
        CAnimManager::LoadAnimFile(pRwStream, true, nullptr);
        CAnimManager::CreateAnimAssocGroups();
    }
    else if (modelId >= RESOURCE_ID_RRR && modelId < RESOURCE_ID_SCM/*model is RRR*/) {
        CVehicleRecording::Load(pRwStream, modelId - RESOURCE_ID_RRR, bufferSize);
    }
    else if (modelId >= RESOURCE_ID_SCM/*model is SCM*/) {
        CTheScripts::StreamedScripts.LoadStreamedScript(pRwStream, modelId - RESOURCE_ID_SCM);
    }
    RwStreamClose(pRwStream, &rwStreamInitData);

    if (modelId >= RESOURCE_ID_TXD) {
        if (!(modelId >= RESOURCE_ID_COL && (modelId < RESOURCE_ID_IFP || modelId >= RESOURCE_ID_RRR)
            && modelId < RESOURCE_ID_SCM || streamingInfo.m_nFlags & (STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED))
        ) {
            // This stmt is only reached if
            // Model type is SCM/IFP/TXD OR it's not a DFF and MISSION_REQUIRED or GAME_REQUIRED flags are set.
            streamingInfo.AddToList(pStartLoadedListStreamingInfo);
        }
    } else {
        // Model is a DFF
        switch (pBaseModelInfo->GetModelType()) {
        case eModelInfoType::MODEL_INFO_TYPE_VEHICLE:
        case eModelInfoType::MODEL_INFO_TYPE_PED:
            break;
        default: {
            // Model type is not vehicle/ped
            CBaseModelInfo* pAsAtomicModelInfo = pBaseModelInfo->AsAtomicModelInfoPtr();
            if (pAsAtomicModelInfo) {
                // TODO: What the fuck...
                // From what I understand its either -1 or -0, which, when casted to uint8, becomes 128 or 129
                // Doesnt make a lot of sense to me
                pAsAtomicModelInfo->m_nAlpha = -((streamingInfo.m_nFlags & (STREAMING_LOADING_SCENE | STREAMING_MISSION_REQUIRED)) != 0);
            }

            if (!(streamingInfo.m_nFlags & (STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED)))
                streamingInfo.AddToList(pStartLoadedListStreamingInfo);

            break;
        }
        }
    }

    if (streamingInfo.m_nLoadState != LOADSTATE_FINISHING) {
        streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        ms_memoryUsed += bufferSize;
    }
    return true;
}

// 0x4090A0
void CStreaming::DeleteAllRwObjects() {
    for (int32 sx = 0; sx < MAX_SECTORS_X; ++sx) {
        for (int32 sy = 0; sy < MAX_SECTORS_Y; ++sy) {
            CRepeatSector* pRepeatSector = GetRepeatSector(sx, sy);
            CSector* pSector = GetSector(sx, sy);
            DeleteRwObjectsInSectorList(pSector->m_buildings);
            DeleteRwObjectsInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            DeleteRwObjectsInSectorList(pSector->m_dummies);
        }
    }
}

// 0x409760
// Function name is a little misleading, as it deletes the first entity it can.
bool CStreaming::DeleteLeastUsedEntityRwObject(bool bNotOnScreen, uint32 streamingFlags) {
    const float fCameraFarPlane = TheCamera.m_pRwCamera->farPlane;
    CPlayerPed* pPlayer = FindPlayerPed(-1);

    for (auto prevLink = ms_rwObjectInstances.usedListTail.prev; prevLink != &ms_rwObjectInstances.usedListHead; prevLink = prevLink->prev) {
        CEntity* pEntity = prevLink->data;
        
        if (pEntity->m_bImBeingRendered || pEntity->m_bStreamingDontDelete)
            continue;

        const int32 modelId = pEntity->m_nModelIndex;
        const auto pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
        float drawDistanceRadius = TheCamera.m_fLODDistMultiplier * pBaseModelInfo->m_fDrawDistance;
        if (pEntity->m_bIsBIGBuilding)
            drawDistanceRadius *= CRenderer::ms_lowLodDistScale;

        const CVector entityPos = pEntity->m_pLod ? pEntity->m_pLod->GetPosition() : pEntity->GetPosition();
        const float fEntityToCamDist = DistanceBetweenPoints(TheCamera.GetPosition(), entityPos);
        CEntity* const pEntityLastLod = pEntity->FindLastLOD();

        const float fModelRadius = pBaseModelInfo->GetColModel()->GetBoundRadius();
        if (ms_bLoadingScene
            || bNotOnScreen && !pEntityLastLod->GetIsOnScreen()
            || pEntity->m_nAreaCode != CGame::currArea && pEntity->m_nAreaCode != AREA_CODE_13
            || drawDistanceRadius + 50.0f < fEntityToCamDist
            || fModelRadius + fCameraFarPlane < fEntityToCamDist)
        {
            CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
            if (streamingInfo.InList() && !(streamingFlags & streamingInfo.m_nFlags)) {
                if (!pPlayer || pPlayer->bInVehicle || pPlayer->m_pContactEntity != pEntity) {
                    pEntity->DeleteRwObject();
                    if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
                        RemoveModel(modelId);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// 0x409210
// Deletes all RW objects more than 3 sectors (on each axis) away from the given point's sector
void CStreaming::DeleteRwObjectsAfterDeath(CVector const& point) {
    const int32 pointSecX = CWorld::GetSectorX(point.x),
                pointSecY = CWorld::GetSectorY(point.y);
    for (int32 sx = 0; sx < MAX_SECTORS_X; ++sx) {
        if (abs(pointSecX - sx) > 3) {
            for (int32 sy = 0; sy < MAX_SECTORS_Y; ++sy) {
                if (abs(pointSecY - sy) > 3) {
                    CRepeatSector* pRepeatSector = GetRepeatSector(sx, sy);
                    CSector* pSector = GetSector(sx, sy);
                    DeleteRwObjectsInSectorList(pSector->m_buildings);
                    DeleteRwObjectsInSectorList(pRepeatSector->GetList(REPEATSECTOR_OBJECTS));
                    DeleteRwObjectsInSectorList(pSector->m_dummies);
                }
            }
        }
    }
}

// 0x40D7C0
// TODO: Decode this, no clue whats going on here..
void CStreaming::DeleteRwObjectsBehindCamera(int32 memoryToCleanInBytes) {
    if (static_cast<int32>(CStreaming::ms_memoryUsed) < memoryToCleanInBytes)
        return;

    const CVector& cameraPos = TheCamera.GetPosition();
    const int32 pointSecX = CWorld::GetSectorX(cameraPos.x),
                pointSecY = CWorld::GetSectorY(cameraPos.y);
    const CVector2D& camFwd = TheCamera.GetForward();
    if (fabs(camFwd.y) < fabs(camFwd.x)) {
        int32 sectorStartY = std::max(pointSecY - 10, 0);
        int32 sectorEndY = std::min(pointSecY + 10, MAX_SECTORS_Y - 1);
        int32 sectorStartX = 0;
        int32 sectorEndX = 0;
        int32 factorX = 0;

        if (camFwd.x <= 0.0f) {
            sectorStartX = std::min(pointSecX + 10, MAX_SECTORS_X - 1);
            sectorEndX = std::min(pointSecX + 2, MAX_SECTORS_X - 1);
            factorX = -1;
        } else {
            sectorStartX = std::max(pointSecX - 10, 0);
            sectorEndX = std::max(pointSecX - 2, 0);
            factorX = 1;
        }

        CWorld::IncrementCurrentScanCode();
        for (int32 sectorX = sectorStartX; sectorX != sectorEndX; sectorX += factorX) {
            for (int32 sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
                CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* pSector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(pSector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pSector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }

        if (camFwd.x <= 0.0f) {
            sectorEndX = std::min(pointSecX + 2, MAX_SECTORS_X - 1);
            sectorStartX = std::max(pointSecX - 10, 0);
            factorX = -1;
        } else {
            sectorEndX = std::max(pointSecX - 2, 0);
            sectorStartX = std::min(pointSecX + 10, MAX_SECTORS_X - 1);
            factorX = 1;
        }

        CWorld::IncrementCurrentScanCode();
        for (int32 sectorX = sectorStartX; sectorX != sectorEndX; sectorX -= factorX) {
            for (int32 sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
                CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* pSector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsNotInFrustumInSectorList(pSector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(pSector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }

        CWorld::IncrementCurrentScanCode();
        for (int32 sectorX = sectorStartX; sectorX != sectorEndX; sectorX -= factorX) {
            for (int32 sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
                CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* pSector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(pSector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pSector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
    }
    else {
        int32 sectorStartX = std::max(pointSecX - 10, 0);
        int32 sectorEndX = std::min(pointSecX + 10, MAX_SECTORS_X - 1);
        int32 sectorStartY = 0;
        int32 sectorEndY = 0;
        int32 factorY = 0;
        if (camFwd.y <= 0.0f) {
            sectorEndY = std::min(pointSecY + 2, MAX_SECTORS_Y - 1);
            sectorStartY = std::min(pointSecY + 10, MAX_SECTORS_Y - 1);
            factorY = -1;
        }
        else  {
            factorY = 1;
            sectorStartY = std::max(pointSecY - 10, 0);
            sectorEndY = std::max(pointSecY - 2, 0);
        }
        CWorld::IncrementCurrentScanCode();
        for (int32 sectorY = sectorStartY; sectorY != sectorEndY; sectorY += factorY) {
            for (int32 sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
                CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* pSector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(pSector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pSector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
        if (camFwd.y <= 0.0f) {
            sectorEndY = std::min(pointSecY + 2, MAX_SECTORS_Y - 1);
            sectorStartY = std::max(pointSecY - 10, 0);
            factorY = -1;
        }
        else {
            sectorEndY = std::max(pointSecY - 2, 0);
            sectorStartY = std::min(pointSecY + 10, MAX_SECTORS_Y - 1);
            factorY = 1;
        }
        CWorld::IncrementCurrentScanCode();
        for (int32 sectorY = sectorStartY; sectorY != sectorEndY; sectorY -= factorY) {
            for (int32 sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
                CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* pSector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsNotInFrustumInSectorList(pSector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(pSector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
        if (RemoveReferencedTxds(memoryToCleanInBytes))
            return;
        // BUG: possibly missing CWorld::IncrementCurrentScanCode() here?
        for (int32 sectorY = sectorStartY; sectorY != sectorEndY; sectorY -= factorY) {
            for (int32 sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
                CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* pSector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(pSector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pSector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
    }

    while ((static_cast<int32>(ms_memoryUsed) >= memoryToCleanInBytes)) {
        if (!RemoveLeastUsedModel(0))
            break;
    }
}

// 0x409940
bool CStreaming::DeleteRwObjectsBehindCameraInSectorList(CPtrList& list, int32 memoryToCleanInBytes) {
    for (CPtrNode* pNode = list.GetNode(); pNode; pNode = pNode->m_next) {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->m_item);
        if (pEntity->m_nScanCode == CWorld::ms_nCurrentScanCode)
            continue;
        pEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;

        const int32 modelId = pEntity->m_nModelIndex;
        if (!pEntity->m_bImBeingRendered && !pEntity->m_bStreamingDontDelete
            && pEntity->m_pRwObject
            && ms_aInfoForModel[modelId].InList()
            && FindPlayerPed(-1)->m_pContactEntity != pEntity)
        {
            pEntity->DeleteRwObject();
            if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
                RemoveModel(modelId);
                if (static_cast<int32>(ms_memoryUsed) < memoryToCleanInBytes)
                    return true;
            }
        }
    }
    return false;
}

// 0x407A70
void CStreaming::DeleteRwObjectsInSectorList(CPtrList& list, int32 sectorX, int32 sectorY) {
    for (CPtrNode* pNode = list.GetNode(); pNode; pNode = pNode->m_next) {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->m_item);
        if (sectorX < 0 || pEntity->LivesInThisNonOverlapSector(sectorX, sectorY)) {
            if (!pEntity->m_bImBeingRendered && !pEntity->m_bStreamingDontDelete)
                pEntity->DeleteRwObject();
        }
    }
}

// 0x4099E0
bool CStreaming::DeleteRwObjectsNotInFrustumInSectorList(CPtrList& list, int32 memoryToCleanInBytes) {
    for (CPtrNode* pNode = list.GetNode(); pNode; pNode = pNode->m_next) {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->m_item);
        if (pEntity->m_nScanCode == CWorld::ms_nCurrentScanCode)
            continue;
        pEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;

        const int32 modelId = pEntity->m_nModelIndex;
        if (!pEntity->m_bImBeingRendered && !pEntity->m_bStreamingDontDelete
            && pEntity->m_pRwObject
            && (!pEntity->IsVisible() || pEntity->m_bOffscreen)
            && ms_aInfoForModel[modelId].InList())
        {
            pEntity->DeleteRwObject();
            if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
                RemoveModel(modelId);
                if (static_cast<int32>(ms_memoryUsed) < memoryToCleanInBytes)
                    return true;
            }
        }
    }
    return false;
}

// 0x40D2F0
// The naming seems to be incorrect. In fact it only removes TXDs with `STREAMING_LOADING_SCENE` not set and no references.
bool CStreaming::RemoveReferencedTxds(int32 memoryToCleanInBytes)
{
    for (auto info = ms_pEndLoadedList->GetPrev(); info != CStreaming::ms_startLoadedList; info = info->GetPrev()) {
        const int32 modelId = info - CStreaming::ms_aInfoForModel;
        if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL/*model is TXD*/
            && !(info->m_nFlags & STREAMING_LOADING_SCENE)
        ) {
            if (!CTxdStore::GetNumRefs(modelId - RESOURCE_ID_TXD)) {
                CStreaming::RemoveModel(modelId);
                if (static_cast<int32>(CStreaming::ms_memoryUsed) < memoryToCleanInBytes)
                    return true;
            }
        }
    }
    return false;
}

// 0x407D10
void CStreaming::DisableCopBikes(bool bDisable) {
    m_bDisableCopBikes = bDisable;
}

// 0x4076A0
bool CStreaming::IsVeryBusy() {
    return CRenderer::m_loadingPriority || ms_numModelsRequested > 5;
}

// 0x5D29E0
void CStreaming::Load() {
    for (int32 i = 0; i < RESOURCE_ID_TOTAL; i++) {
        CStreamingInfo& streamingInfo = ms_aInfoForModel[i];

        uint8 flags;
        CGenericGameStorage::LoadDataFromWorkBuffer(&flags, 1u);
        if (streamingInfo.m_nLoadState == LOADSTATE_LOADED && flags != 0xFFu)
            streamingInfo.m_nFlags |= flags;
    }
}

// There are only 2 streaming channels within CStreaming::ms_channel. In this function,
// if your current channelIndex is zero then "1 - channelIndex" will give you the other
// streaming channel within CStreaming::ms_channel which is 1 (second streaming channel).
// 0x40EA10
void CStreaming::LoadAllRequestedModels(bool bOnlyPriorityRequests)
{
    if (m_bLoadingAllRequestedModels)
        return;
    m_bLoadingAllRequestedModels = true;

    FlushChannels();
    int32 numModelsToLoad = 2 * ms_numModelsRequested >= 10 ? 2 * ms_numModelsRequested : 10;

    int32 chIdx = 0;
    while (true)
    {
        const tStreamingChannel& ch1 = ms_channel[0];
        const tStreamingChannel& ch2 = ms_channel[1];

        if (ms_pEndRequestedList->GetPrev() == ms_pStartRequestedList /*empty request list*/
            && ch1.LoadStatus == LOADSTATE_NOT_LOADED
            && ch2.LoadStatus == LOADSTATE_NOT_LOADED
            || numModelsToLoad <= 0)
        {
            break;
        }

        if (ms_bLoadingBigModel)
            chIdx = 0;

        tStreamingChannel& channel = ms_channel[chIdx];
        if (channel.LoadStatus != LOADSTATE_NOT_LOADED) {
            CdStreamSync(chIdx);
            channel.iLoadingLevel = 100;
        }

        if (channel.LoadStatus == LOADSTATE_LOADED) {
            ProcessLoadingChannel(chIdx);
            if (channel.LoadStatus == LOADSTATE_REQUESTED)
                ProcessLoadingChannel(chIdx);
        }

        if (bOnlyPriorityRequests && ms_numPriorityRequests == 0)
            break;

        if (!ms_bLoadingBigModel) {
            tStreamingChannel& otherChannel = ms_channel[1 - chIdx];

            if (otherChannel.LoadStatus == LOADSTATE_NOT_LOADED)
                RequestModelStream(1 - chIdx);

            if (channel.LoadStatus == LOADSTATE_NOT_LOADED && !ms_bLoadingBigModel)
                RequestModelStream(chIdx);
        }

        if (ch1.LoadStatus == LOADSTATE_NOT_LOADED && ch2.LoadStatus == LOADSTATE_NOT_LOADED)
            break;

        chIdx = 1 - chIdx; // Switch to other channel
        --numModelsToLoad;
    }
    FlushChannels();
    m_bLoadingAllRequestedModels = false;
}

// 0x5B6170
void CStreaming::LoadCdDirectory(const char* filename, int32 archiveId)
{
    FILE* imgFile = CFileMgr::OpenFile(filename, "rb");
    if (!imgFile)
        return;

    int32 previousModelId = -1;
    char version[4];
    int32 entryCount;
    CFileMgr::Read(imgFile, &version, 4u);
    CFileMgr::Read(imgFile, &entryCount, 4u);
    for (int32 i = 0; i < entryCount; i++) {
        CDirectory::DirectoryInfo entryInfo{};
        CFileMgr::Read(imgFile, &entryInfo, sizeof(CDirectory::DirectoryInfo));

        ms_streamingBufferSize = std::max(ms_streamingBufferSize, (uint32)entryInfo.m_nStreamingSize);

        // Find extension from name
        const int32 nameSize = sizeof(CDirectory::DirectoryInfo::m_szName);
        entryInfo.m_szName[nameSize - 1] = 0;
        char* pExtension = strchr(entryInfo.m_szName, '.');
        if (!pExtension || pExtension - entryInfo.m_szName > 20) {
            entryInfo.m_szName[nameSize - 1] = 0;
            previousModelId = -1;
            continue;
        }
        *pExtension = 0;

        const auto ExtensionIs = [=](const char what[]) {
            return _memicmp(pExtension + 1, what, strlen(what)) == 0;
        };

        int32 modelId = -1;
        if (ExtensionIs("DFF")) {
            if (!CModelInfo::GetModelInfo(entryInfo.m_szName, &modelId)) {
                entryInfo.m_nOffset |= archiveId << 24;
                CStreaming::ms_pExtraObjectsDir->AddItem(entryInfo);
                previousModelId = -1;
                continue;
            }

        } else if (ExtensionIs("TXD")) {
            int32 txdSlot = CTxdStore::FindTxdSlot(entryInfo.m_szName);
            if (txdSlot == -1) {
                txdSlot = CTxdStore::AddTxdSlot(entryInfo.m_szName);
                CVehicleModelInfo::AssignRemapTxd(entryInfo.m_szName, txdSlot);
            }
            modelId = txdSlot + RESOURCE_ID_TXD;

        } else if (ExtensionIs("COL")) {
            int32 colSlot = CColStore::FindColSlot();
            if (colSlot == -1)
                colSlot = CColStore::AddColSlot(entryInfo.m_szName);
            modelId = colSlot + RESOURCE_ID_COL;

        } else if (ExtensionIs("IPL")) {
            int32 iplSlot = CIplStore::FindIplSlot(entryInfo.m_szName);
            if (iplSlot == -1)
                iplSlot = CIplStore::AddIplSlot(entryInfo.m_szName);
            modelId = iplSlot + RESOURCE_ID_IPL;

        } else if (ExtensionIs("DAT")) {
            // Extract nodes file sector from name
            sscanf(&entryInfo.m_szName[sizeof("nodes") - 1], "%d", &modelId);
            modelId += RESOURCE_ID_DAT;

        } else if (ExtensionIs("IFP")) {
            modelId = CAnimManager::RegisterAnimBlock(entryInfo.m_szName) + RESOURCE_ID_IFP;

        } else if (ExtensionIs("RRR")) {
            modelId = CVehicleRecording::RegisterRecordingFile(entryInfo.m_szName) + RESOURCE_ID_RRR;

        } else if (ExtensionIs("SCM")) {
            modelId = CTheScripts::StreamedScripts.RegisterScript(entryInfo.m_szName) + RESOURCE_ID_SCM;

        } else {
            *pExtension = '.'; // Unnecessary because extension is limited to this scope only.
            previousModelId = -1;
            continue;
        }

        uint32 cdPos, cdSize;
        CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
        if (!streamingInfo.GetCdPosnAndSize(cdPos, cdSize)) {
            streamingInfo.m_nImgId = archiveId;

            if (entryInfo.m_nSizeInArchive)
                entryInfo.m_nStreamingSize = entryInfo.m_nSizeInArchive;

            streamingInfo.SetCdPosnAndSize(entryInfo.m_nOffset, entryInfo.m_nStreamingSize);
            streamingInfo.m_nFlags = 0;

            if (previousModelId != -1)
                ms_aInfoForModel[previousModelId].m_nNextIndexOnCd = modelId;

            previousModelId = modelId;
        }
    }
    CFileMgr::CloseFile(imgFile);
}

// 0x5B82C0
void CStreaming::LoadCdDirectory()
{
    ////////////// unused///////////////
    ms_imageOffsets[0] = 0;
    ms_imageOffsets[1] = -1;
    ms_imageOffsets[2] = -1;
    ms_imageOffsets[3] = -1;
    ms_imageOffsets[4] = -1;
    ms_imageOffsets[5] = -1;
    ////////////////////////////////////
    for (int32 archiveId = 0; archiveId < TOTAL_IMG_ARCHIVES; archiveId++) {
        tStreamingFileDesc& streamingFile = ms_files[archiveId];
        if (!streamingFile.m_szName[0])
            break;
        if (streamingFile.m_bNotPlayerImg)
            LoadCdDirectory(streamingFile.m_szName, archiveId);
    }
    // more unused code, so let's stop here
}

// 0x40D3D0
void CStreaming::LoadInitialPeds() {
    RequestModel(MODEL_MALE01, STREAMING_GAME_REQUIRED); // Without this model the game basically crashes, it has to be loaded at all times.
    StreamCopModels(LEVEL_NAME_LOS_SANTOS);
}

void CStreaming::LoadInitialVehicles() {
    // empty function
}

// 0x40A120
void CStreaming::LoadInitialWeapons() {
    RequestModel(MODEL_COLT45, STREAMING_GAME_REQUIRED);
    RequestModel(MODEL_NITESTICK, STREAMING_GAME_REQUIRED);
    RequestModel(MODEL_MISSILE, STREAMING_GAME_REQUIRED);
}

// 0x40EB70
void CStreaming::LoadScene(CVector const& point) {
    ms_bLoadingScene = true;

    CVector playerPosition = FindPlayerCoors(0);

    // Can't use a simple `for` loop here, because model is unlinked (thus the iterator is invalidated) when removed.
    {
        CStreamingInfo* iter = ms_pEndRequestedList->GetPrev();
        while (iter != ms_pStartRequestedList) {
            const auto next = iter->GetPrev();
            if (!iter->DontRemoveInLoadScene())
                RemoveModel(iter - ms_aInfoForModel);
            iter = next;
        }
    }

    CRenderer::m_loadingPriority = false;
    DeleteAllRwObjects();
    RequestBigBuildings(point);
    CIplStore::LoadIpls(point, true);
    LoadAllRequestedModels(false);
    AddModelsToRequestList(point, STREAMING_LOADING_SCENE);
    CRadar::StreamRadarSections(point);
    ThePaths.LoadSceneForPathNodes(point);
    if (CGame::currArea == eAreaCodes::AREA_CODE_NORMAL_WORLD) {
        if (ms_bLoadVehiclesInLoadScene) {
            if (CTheZones::GetZoneInfo(point, nullptr) != CTheZones::GetZoneInfo(playerPosition, nullptr)) {
                for (int32 i = 0; i < 5; i++) {
                    LoadZoneVehicle(point);
                }
            }
        }
        StreamCopModels(CTheZones::GetLevelFromPosition(point));
    }
    LoadAllRequestedModels(false);
    InstanceLoadedModels(point);
    ClearFlagForAll(STREAMING_LOADING_SCENE);
    ms_bLoadingScene = false;
    if (CWorld::Players[0].m_pPed)
        CPopulation::ManageAllPopulation();
}

// 0x40ED80
void CStreaming::LoadSceneCollision(CVector const& point) {
    CColStore::LoadCollision(point, true);
    CIplStore::LoadIpls(point, true);
    LoadAllRequestedModels(false);
}

// 0x40B4B0
void CStreaming::LoadZoneVehicle(const CVector& point) {
    if (CPopCycle::m_pCurrZoneInfo) {
        CTheZones::GetZoneInfo(point, nullptr); // called but return value is ignored
        const auto modelId = CCarCtrl::ChooseCarModelToLoad(CPopCycle::PickARandomGroupOfOtherPeds());
        if (modelId >= 0)
            RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
    }

}

// 0x40BA70
void CStreaming::PossiblyStreamCarOutAfterCreation(int32 modelId) {
    if (CModelInfo::ms_modelInfoPtrs[modelId]->m_nFlags & STREAMING_UNKNOWN_1) {
        if (rand() % 2)
            SetModelIsDeletable(modelId);
    }
}

// 0x4096D0
void CStreaming::RenderEntity(CLink<CEntity*>* streamingLink) {
    if (streamingLink && streamingLink != ms_renderEntityLink) {
        streamingLink->Remove();
        ms_renderEntityLink->Insert(streamingLink);
        ms_renderEntityLink = streamingLink;
    }
}

// 0x409430
// Load big buildings around `point`
void CStreaming::RequestBigBuildings(CVector const& point) {
    for (int32 i = CPools::ms_pBuildingPool->GetSize() - 1; i >= 0; i--) {
        CBuilding* pBuilding = CPools::ms_pBuildingPool->GetAt(i);
        if (pBuilding && pBuilding->m_bIsBIGBuilding) {
            if (CRenderer::ShouldModelBeStreamed(pBuilding, point, TheCamera.m_pRwCamera->farPlane))
                RequestModel(pBuilding->m_nModelIndex, 0);
        }
    }
}

// 0x40A080
// Request model @ `posn` with size `size` in the img `imgId`.
void CStreaming::RequestFile(int32 modelId, int32 posn, int32 size, int32 imgId, int32 streamingFlags) {
    auto& info = ms_aInfoForModel[modelId];
    const uint32 blockOffset = (imgId << 24) | posn;
    if (info.GetCdSize() && info.GetCdPosn() == blockOffset && info.GetCdSize() == size) {
        RequestModel(modelId, streamingFlags);
    } else {
        RemoveModel(modelId);
        info.SetCdPosnAndSize(blockOffset & 0xFFFFFF, size);
        info.m_nImgId = imgId;
        RequestModel(modelId, streamingFlags);
    }
}

// 0x409050
void CStreaming::RequestFilesInChannel(int32 chIdx) {
    for (auto modelId : ms_channel[chIdx].modelIds) {
        if (modelId != -1) {
            RemoveModel(modelId);
            RequestModel(modelId, ms_aInfoForModel[modelId].m_nFlags);
        }
    }
}

// 0x4087E0
void CStreaming::RequestModel(int32 modelId, uint32 streamingFlags)
{
    CStreamingInfo& info = ms_aInfoForModel[modelId];
    
    switch (info.m_nLoadState) {
    case eStreamingLoadState::LOADSTATE_REQUESTED: {
        // Model already requested, just add priority request flag if necessary
        if ((streamingFlags & STREAMING_PRIORITY_REQUEST) && !(info.m_nFlags & STREAMING_PRIORITY_REQUEST)) // Is priority request
        {
            ++ms_numPriorityRequests;
            info.m_nFlags |= STREAMING_PRIORITY_REQUEST;
        }
        break;
    }
    case eStreamingLoadState::LOADSTATE_NOT_LOADED:
        break;

    default: {
        streamingFlags &= ~STREAMING_PRIORITY_REQUEST; // Remove flag otherwise
        break;
    }
    }
    info.m_nFlags |= streamingFlags;

    switch (info.m_nLoadState) {
    case eStreamingLoadState::LOADSTATE_LOADED: {
        if (info.InList()) {
            info.RemoveFromList();
            if (modelId < RESOURCE_ID_TXD/*model is DFF*/) {
                switch (CModelInfo::GetModelInfo(modelId)->GetModelType()) {
                case eModelInfoType::MODEL_INFO_TYPE_PED:
                case eModelInfoType::MODEL_INFO_TYPE_VEHICLE: {
                    return;
                }
                }
            }

            if (!(info.m_nFlags & (STREAMING_GAME_REQUIRED | STREAMING_MISSION_REQUIRED)))
                info.AddToList(ms_startLoadedList);
        }
        break;
    }
    case eStreamingLoadState::LOADSTATE_READING:
    case eStreamingLoadState::LOADSTATE_REQUESTED:
    case eStreamingLoadState::LOADSTATE_FINISHING:
        break;

    case eStreamingLoadState::LOADSTATE_NOT_LOADED: {
        if (modelId >= RESOURCE_ID_TXD) {
            if (modelId < RESOURCE_ID_COL) {
                // Model is TXD
                int32 txdEntryParentIndex = CTxdStore::GetParentTxdSlot(modelId - RESOURCE_ID_TXD);
                if (txdEntryParentIndex != -1)
                    RequestTxdModel(txdEntryParentIndex, streamingFlags);
            }
        } else {
            // Model is DFF

            CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
            RequestTxdModel(modelInfo->m_nTxdIndex, streamingFlags);

            const int32 animFileIndex = modelInfo->GetAnimFileIndex();
            if (animFileIndex != -1)
                RequestModel(animFileIndex + RESOURCE_ID_IFP, STREAMING_KEEP_IN_MEMORY);
        }

        info.AddToList(ms_pStartRequestedList);

        ++ms_numModelsRequested;
        if (streamingFlags & STREAMING_PRIORITY_REQUEST)
            ++ms_numPriorityRequests;

        // Fallthrough 
        __fallthrough;
    }
    default: {
        info.m_nFlags = streamingFlags;
        info.m_nLoadState = LOADSTATE_REQUESTED; // requested, loading
    }
    }
}

// TODO: Make more of these functions, really makes the code cleaner.
// 0x407100
void CStreaming::RequestTxdModel(int32 slot, int32 streamingFlags) {
    RequestModel(slot + RESOURCE_ID_TXD, streamingFlags);
}

// 0x408C70
void CStreaming::RequestVehicleUpgrade(int32 modelId, uint32 streamingFlags)
{
    RequestModel(modelId, streamingFlags);
    int16 otherUpgradeModelId = CVehicleModelInfo::ms_linkedUpgrades.FindOtherUpgrade(modelId);
    if (otherUpgradeModelId != -1)
        RequestModel(otherUpgradeModelId, streamingFlags);
}

// 0x407FB0
int32 CStreaming::FindMIPedSlotForInterior(int32 randFactor)
{
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[(i + randFactor) % TOTAL_LOADED_PEDS];
        if (modelId >= 0 && ms_aInfoForModel[modelId].m_nLoadState == LOADSTATE_LOADED)
            return modelId;
    }
    return MODEL_MALE01;
}

// 0x408CB0
void CStreaming::FinishLoadingLargeFile(uint8* pFileBuffer, int32 modelId)
{
    bool bFinishedLoadingLargeFile = false;
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
    if (streamingInfo.m_nLoadState == LOADSTATE_FINISHING) {
        const uint32 bufferSize = streamingInfo.GetCdSize() * STREAMING_SECTOR_SIZE;
        tRwStreamInitializeData rwStreamInitializationData = { pFileBuffer, bufferSize };
        RwStream* pRwStream = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitializationData);

        bool bLoaded = false;
        if (modelId >= RESOURCE_ID_DFF && modelId < RESOURCE_ID_TXD/*model is DFF*/) {
            CTxdStore::SetCurrentTxd(pBaseModelInfo->m_nTxdIndex);

            bLoaded = CFileLoader::FinishLoadClumpFile(pRwStream, modelId);
            if (bLoaded)
                bLoaded = AddToLoadedVehiclesList(modelId);
            pBaseModelInfo->RemoveRef();
            CTxdStore::RemoveRefWithoutDelete(pBaseModelInfo->m_nTxdIndex);

            const int32 animFileIndex = pBaseModelInfo->GetAnimFileIndex();
            if (animFileIndex != -1) {
                CAnimManager::RemoveAnimBlockRefWithoutDelete(animFileIndex);
            }
        } else if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL/*model is TXD*/) {
            CTxdStore::AddRef(modelId - RESOURCE_ID_TXD);
            bLoaded = CTxdStore::FinishLoadTxd(modelId - RESOURCE_ID_TXD, pRwStream);
            CTxdStore::RemoveRefWithoutDelete(modelId - RESOURCE_ID_TXD);
        }
        else
            assert(modelId < RESOURCE_ID_COL && "FinishLoadingLargeFile: model id is out of range");
        RwStreamClose(pRwStream, &pFileBuffer);

        streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        ms_memoryUsed += bufferSize;
        if (!bLoaded) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.m_nFlags);
        }
    } else {
        if (modelId < RESOURCE_ID_TXD/*model is DFF*/)
            pBaseModelInfo->RemoveRef();
    }
}

// 0x40E460
void CStreaming::FlushChannels()
{
    if (ms_channel[1].LoadStatus == LOADSTATE_REQUESTED)
        ProcessLoadingChannel(1);

    if (ms_channel[0].LoadStatus == LOADSTATE_LOADED)
    {
        CdStreamSync(0);
        ms_channel[0].iLoadingLevel = 100;
        ProcessLoadingChannel(0);
    }
    if (ms_channel[0].LoadStatus == LOADSTATE_REQUESTED)
        ProcessLoadingChannel(0);

    if (ms_channel[1].LoadStatus == LOADSTATE_LOADED)
    {
        CdStreamSync(1u);
        ms_channel[1].iLoadingLevel = 100;
        ProcessLoadingChannel(1);
    }
    if (ms_channel[1].LoadStatus == LOADSTATE_REQUESTED)
        ProcessLoadingChannel(1);;
}

// 0x40CBA0
// TODO: Document this function.. I'm really unsure what it does exactly
void CStreaming::RequestModelStream(int32 chIdx)
{
    int32 modelId = GetNextFileOnCd(CdStreamGetLastPosn(), true);
    if (modelId == -1)
        return;

    tStreamingChannel& ch = ms_channel[chIdx];
    uint32 posn = 0;
    uint32 sizeInSectors = 0;
    CStreamingInfo* streamingInfo = &ms_aInfoForModel[modelId];
    while (!streamingInfo->IsRequiredToBeKept()) {
        // Remove unused TXDs or IFPs from stream.
        if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL /*model is TXD*/) {
            if (AreTexturesUsedByRequestedModels(modelId - RESOURCE_ID_TXD))
                break;
        } else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR /*model is IFP*/) {
            if (AreAnimsUsedByRequestedModels(modelId - RESOURCE_ID_IFP))
                break;
        } else /*model is neither TXD or IFP*/ {
            break;
        }

        RemoveModel(modelId);

        streamingInfo->GetCdPosnAndSize(posn, sizeInSectors);
        modelId = GetNextFileOnCd(sizeInSectors + posn, true);
        if (modelId == -1)
            return;
        streamingInfo = &ms_aInfoForModel[modelId];
    }
    if (modelId == -1)
        return;

    streamingInfo->GetCdPosnAndSize(posn, sizeInSectors);
    if (sizeInSectors > ms_streamingBufferSize) {
        if (chIdx == 1 || ms_channel[1].LoadStatus != eStreamingLoadState::LOADSTATE_NOT_LOADED)
            return;
        ms_bLoadingBigModel = true;
    }

    uint32 sectorCount = 0;
    const bool isThisModelBig = sizeInSectors > 200;
    bool isPreviousModelBig = false; // All models with the size > 200 (in sectors) are considered big
    bool isPreviousModelPed = false;
    const int32 numberOfModelIds = sizeof(tStreamingChannel::modelIds) / sizeof(tStreamingChannel::modelIds[0]);
    int32 modelIndex = 0;
    for (; modelIndex < numberOfModelIds; modelIndex++) {
        streamingInfo = &ms_aInfoForModel[modelId];
        if (streamingInfo->m_nLoadState != LOADSTATE_REQUESTED)
            break;

        if (streamingInfo->GetCdSize())
            sizeInSectors = streamingInfo->GetCdSize();

        if (ms_numPriorityRequests && !(streamingInfo->m_nFlags & STREAMING_PRIORITY_REQUEST))
            break;

        if (modelId >= RESOURCE_ID_TXD/*model is NOT DFF*/) {
            if (modelId < RESOURCE_ID_IFP || modelId >= RESOURCE_ID_RRR/*model is NOT IFP*/) {
                if (isPreviousModelBig && isThisModelBig)
                    break;
            } else if (CCutsceneMgr::ms_cutsceneProcessing || ms_aInfoForModel[MODEL_MALE01].m_nLoadState != LOADSTATE_LOADED) {
                break;
            }
        } else /*Model is DFF*/ {
            CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];

            if (isPreviousModelPed && pBaseModelInfo->GetModelType() == MODEL_INFO_PED)
                break;

            if (isPreviousModelBig && pBaseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
                break;

            if (!ms_aInfoForModel[pBaseModelInfo->m_nTxdIndex + RESOURCE_ID_TXD].IsLoadedOrBeingRead())
                break; // TXD not yet loaded

            
            int32 animFileIndex = pBaseModelInfo->GetAnimFileIndex();
            if (animFileIndex != -1)
            {
                if (!ms_aInfoForModel[animFileIndex + RESOURCE_ID_IFP].IsLoadedOrBeingRead())
                    break; // IFP not loaded yet
            }
        }
        ch.modelStreamingBufferOffsets[modelIndex] = sectorCount;
        ch.modelIds[modelIndex] = modelId;

        sectorCount += sizeInSectors;
        if (sectorCount > ms_streamingBufferSize && modelIndex > 0) {
            sectorCount -= sizeInSectors;
            break;
        }

        CBaseModelInfo* pBaseModelInfo = CModelInfo::GetModelInfo(modelId);
        if (modelId >= RESOURCE_ID_TXD/*model is NOT DFF*/) {
            if (isThisModelBig)
                isPreviousModelBig = true;
        } else /*model is DFF*/ {
            switch (pBaseModelInfo->GetModelType()) {
            case ModelInfoType::MODEL_INFO_PED:
                isPreviousModelPed = true;
                break;
            case ModelInfoType::MODEL_INFO_VEHICLE:
                isPreviousModelBig = true;
                break;
            }
        }
        streamingInfo->m_nLoadState = LOADSTATE_READING;
        streamingInfo->RemoveFromList();
        ms_numModelsRequested--;
        if (streamingInfo->IsPriorityRequest()) {
            streamingInfo->m_nFlags &= ~STREAMING_PRIORITY_REQUEST;
            ms_numPriorityRequests--;
        }
        modelId = streamingInfo->m_nNextIndexOnCd;
    }
    for (int32 i = modelIndex; i < numberOfModelIds; i++) {
        ch.modelIds[i] = -1;
    }
    CdStreamRead(chIdx, ms_pStreamingBuffer[chIdx], posn, sectorCount);
    ch.LoadStatus = LOADSTATE_LOADED;
    ch.iLoadingLevel = 0;
    ch.sectorCount = sectorCount;
    ch.offsetAndHandle = posn;
    ch.totalTries = 0;
    if (m_bModelStreamNotLoaded)
        m_bModelStreamNotLoaded = false;
}

// 0x40B450
void CStreaming::RequestSpecialChar(int32 modelId, char const* name, int32 flags) {
    return RequestSpecialModel(modelId + SPECIAL_MODELS_RESOURCE_ID, name, flags);
}

// 0x409D10
// TODO: Document this function...
void CStreaming::RequestSpecialModel(int32 modelId, char const* name, int32 flags)
{
    CBaseModelInfo* modelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = CStreaming::ms_aInfoForModel[modelId];
    uint32 CdPosn, CdSize;
    if (CKeyGen::GetUppercaseKey(name) == modelInfo->m_nKey && streamingInfo.GetCdPosnAndSize(CdPosn, CdSize)) {
        RequestModel(modelId, flags);
        return;
    }

    if (modelInfo->m_nRefCount > 0) {
        for (int32 i = CPools::ms_pPedPool->GetSize() - 1; i >= 0; i--) {
            if (modelInfo->m_nRefCount <= 0)
                break;

            CPed* pPed = CPools::ms_pPedPool->GetAt(i);
            if (pPed && pPed->m_nModelIndex == modelId && !pPed->IsPlayer() && pPed->CanBeDeletedEvenInVehicle()) {
                CTheScripts::RemoveThisPed(pPed);
            }
        }
        for (int32 i = CPools::ms_pObjectPool->GetSize() - 1; i >= 0; i--) {
            if (modelInfo->m_nRefCount <= 0)
                break;

            CObject* pObject = CPools::ms_pObjectPool->GetAt(i);
            if (pObject && pObject->m_nModelIndex == modelId && pObject->CanBeDeleted()) {
                CWorld::Remove(pObject);
                CWorld::RemoveReferencesToDeletedObject(pObject);
                delete pObject;
            }
        }
    }
    const auto modelNameKey = modelInfo->m_nKey;
    modelInfo->SetModelName(name);
    CBaseModelInfo* pFoundModelInfo = nullptr;

    for (int32 i = 0; i < 1001; i++) {
        CBaseModelInfo* pTheModelInfo = CModelInfo::ms_modelInfoPtrs[i];
        if (pTheModelInfo && modelNameKey == pTheModelInfo->m_nKey) {
            pFoundModelInfo = pTheModelInfo;
        }
    }

    if (pFoundModelInfo && pFoundModelInfo->m_nTxdIndex != -1 && CTxdStore::ms_pTxdPool->GetAt(pFoundModelInfo->m_nTxdIndex)) {
        CTxdStore::AddRef(pFoundModelInfo->m_nTxdIndex);
        RemoveModel(modelId);
        CTxdStore::RemoveRefWithoutDelete(pFoundModelInfo->m_nTxdIndex);
    } else {
        RemoveModel(modelId);
    }
    uint32 outOffset, outStreamingSize;
    CStreaming::ms_pExtraObjectsDir->FindItem(name, outOffset, outStreamingSize);
    modelInfo->ClearTexDictionary();
    if (CTxdStore::FindTxdSlot(name) == -1)
        modelInfo->SetTexDictionary("generic");
    else
        modelInfo->SetTexDictionary(name);

    // The first 3 bytes of outOffset is used for m_nCdPosn and
    // the remaining 1 byte is used for m_nImgId
    // outOffset & 0xFFFFF = returns the first 3 bytes and ignores the last one
    // outOffset >> 24 = Ignores the first 3 bytes and returns the last byte
    streamingInfo.SetCdPosnAndSize(outOffset & 0xFFFFFF, outStreamingSize);
    streamingInfo.m_nImgId = outOffset >> 24;
    streamingInfo.m_nNextIndexOnCd = -1;
    RequestModel(modelId, flags);
}

// 0x40E170
bool CStreaming::ProcessLoadingChannel(int32 chIdx)
{
    tStreamingChannel& ch = ms_channel[chIdx];

    const eCdStreamStatus streamStatus = CdStreamGetStatus(chIdx);
    if (streamStatus != eCdStreamStatus::READING_SUCCESS) {
        switch (streamStatus) {
        case eCdStreamStatus::READING:
        case eCdStreamStatus::WAITING_TO_READ:
            return false;
        }

        // At this point the stream status is anything but READING_SUCCESS, READING, WAITING_TO_READ
        // Which leaves us with FAILURE, that is, if the enum has no more entries but only these 4.
        ch.m_nCdStreamStatus = streamStatus;
        ch.LoadStatus = LOADSTATE_READING;

        if (ms_channelError != -1)
            return false; // Channel has errors

        ms_channelError = chIdx;
        RetryLoadFile(chIdx);
        return true;
    }

    const bool isRequested = ch.LoadStatus == LOADSTATE_REQUESTED;
    ch.LoadStatus = LOADSTATE_NOT_LOADED;
    if (isRequested) {
        int32 bufferOffset = ch.modelStreamingBufferOffsets[0];
        uint8* pFileContents = reinterpret_cast<uint8*>(&ms_pStreamingBuffer[chIdx][STREAMING_SECTOR_SIZE * bufferOffset]);
        FinishLoadingLargeFile(pFileContents, ch.modelIds[0]);
        ch.modelIds[0] = -1;
    } else {
        const int32 numberOfModelIds = std::size(ch.modelIds);
        for (int32 chModelIter = 0; chModelIter < numberOfModelIds; chModelIter++) {
            const int32 modelId = ch.modelIds[chModelIter];
            if (modelId == -1)
                continue;

            CBaseModelInfo* baseModelInfo = CModelInfo::GetModelInfo(modelId);
            CStreamingInfo& info = ms_aInfoForModel[modelId];

            if (modelId >= RESOURCE_ID_TXD /*model is NOT DFF*/
                || baseModelInfo->GetModelType() != MODEL_INFO_VEHICLE /* It's a DFF, check if its a vehicle */
                || ms_vehiclesLoaded.CountMembers() < desiredNumVehiclesLoaded /* It's a vehicle, so lets check if we can load more */
                || RemoveLoadedVehicle() /* no, so try to remove one, and load this in its place */
                || info.m_nFlags & (STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED) /* failed, lets check if its absolutely mission critical */
            ) {
                if (modelId < RESOURCE_ID_IPL || modelId >= RESOURCE_ID_DAT/*model is NOT IPL*/)
                    MakeSpaceFor(info.GetCdSize() * STREAMING_SECTOR_SIZE);

                const int32 bufferOffsetInSectors = ch.modelStreamingBufferOffsets[chModelIter];
                uint8* pFileBuffer = reinterpret_cast <uint8*> (&ms_pStreamingBuffer[chIdx][STREAMING_SECTOR_SIZE * bufferOffsetInSectors]);

                ConvertBufferToObject(pFileBuffer, modelId);

                if (info.m_nLoadState == LOADSTATE_FINISHING) {
                    ch.LoadStatus = LOADSTATE_REQUESTED;
                    ch.modelStreamingBufferOffsets[chModelIter] = bufferOffsetInSectors;
                    ch.modelIds[chModelIter] = modelId;
                    if (chModelIter == 0)
                        continue;
                }
                ch.modelIds[chModelIter] = -1;
            } else {
                // I think at this point it's guaranteed to be a vehicle (thus its a DFF),
                // with `STREAMING_MISSION_REQUIRED` `STREAMING_GAME_REQUIRED` flags unset.

                const int32 modelTxdIdx = baseModelInfo->m_nTxdIndex;
                RemoveModel(modelId);

                if (info.m_nFlags & (STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED)) {
                    // Re-request it.
                    // I think this code is unreachable, because
                    // if any of the 2 flags (above) is set the `else` branch is never executed.
                    RequestModel(modelId, info.m_nFlags); 
                } else if (!CTxdStore::GetNumRefs(modelTxdIdx))
                    RemoveTxdModel(modelTxdIdx); // Unload TXD, as it has no refs
            }
        }
    }

    if (ms_bLoadingBigModel) {
        if (ch.LoadStatus != LOADSTATE_REQUESTED) {
            ms_bLoadingBigModel = false;
            for (int32 i = 0; i < 16; i++) {
                ms_channel[1].modelIds[i] = -1;
            }
        }
    }

    return true;
}

// 0x40C1E0
void CStreaming::PurgeRequestList() {
    auto streamingInfo = ms_pEndRequestedList->GetPrev();
    while (streamingInfo != ms_pStartRequestedList) {
        auto previousStreamingInfo = streamingInfo->GetPrev();
        if (!streamingInfo->DoKeepInMemory() && !streamingInfo->IsPriorityRequest())
            RemoveModel(streamingInfo - ms_aInfoForModel);
        streamingInfo = previousStreamingInfo;
    }
}

// 0x40E560
void CStreaming::ReInit() {
    CTheScripts::StreamedScripts.ReInitialise();
    FlushRequestList();
    DeleteAllRwObjects();
    RemoveAllUnusedModels();
    for (int32 modelId = 0; modelId < RESOURCE_ID_TOTAL; modelId++)
    {
        CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
        if (streamingInfo.m_nFlags & STREAMING_MISSION_REQUIRED)
            SetMissionDoesntRequireModel(modelId);
    }

    for (int32 scmId = 0; scmId < TOTAL_SCM_MODEL_IDS; scmId++) {
        RemoveModel(scmId + RESOURCE_ID_SCM);
    }
    ms_disableStreaming = false;
    ms_currentZoneType = -1;
    m_bBoatsNeeded = false;
    m_bCopBikeLoaded = false;
    m_bDisableCopBikes = false;
    ms_nTimePassedSinceLastCopBikeStreamedIn = 0;
    for (int32 i = 0; i < TOTAL_SPECIAL_MODELS; i++) {
        const int32 modelId = i + SPECIAL_MODELS_RESOURCE_ID;
        RemoveModel(modelId);
        CModelInfo::ms_modelInfoPtrs[modelId]->SetModelName(gta_empty_string);
    }
    for (int32 i = 0; i < TOTAL_CLOTHES_MODELS; i++) {
        const int32 modelId = i + CLOTHES_MODELS_RESOURCE_ID;
        RemoveModel(modelId);
        CModelInfo::ms_modelInfoPtrs[modelId]->SetModelName(gta_empty_string);
    }
    for (int32 i = 0; i < TOTAL_CUTSCENE_MODELS; i++) {
        const int32 modelId = i + CUTSCENE_MODELS_RESOURCE_ID;
        RemoveModel(modelId);
        CModelInfo::ms_modelInfoPtrs[modelId]->SetModelName(gta_empty_string);
    }
}

// 0x5BCCD0
void CStreaming::ReadIniFile() {
    bool bHasDevkitMemory = false;
    FILE* file = CFileMgr::OpenFile("stream.ini", "r");
    for (char* line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file))
    {
        if (*line != '#' && *line)
        {
            char* attribute = strtok(line, " ,\t");
            char* value = strtok(nullptr, " ,\t");
            if (_stricmp(attribute, "memory") != 0 || bHasDevkitMemory)
            {
                if (!_stricmp(attribute, "devkit_memory"))
                {
                    CStreaming::ms_memoryAvailable = atoi(value) * 1024; // kB => bytes conversion
                    bHasDevkitMemory = true;
                }
                else if (!_stricmp(attribute, "vehicles"))
                {
                    CStreaming::desiredNumVehiclesLoaded = atoi(value);
                }
                else if (!_stricmp(attribute, "dontbuildpaths"))
                {
                    //bDontBuildPaths = 1; // unused
                }
                else if (!_stricmp(attribute, "pe_lightchangerate"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE = static_cast<float>(atof(value));
                }
                else if (!_stricmp(attribute, "pe_lightingbasecap"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP = static_cast<float>(atof(value));
                }
                else if (!_stricmp(attribute, "pe_lightingbasemult"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT = static_cast<float>(atof(value));
                }
                else if (!_stricmp(attribute, "pe_leftx"))
                {
                    CPostEffects::m_colourLeftUOffset = atoi(value);
                }
                else if (!_stricmp(attribute, "pe_rightx"))
                {
                    CPostEffects::m_colourRightUOffset = atoi(value);
                }
                else if (!_stricmp(attribute, "pe_topy"))
                {
                    CPostEffects::m_colourTopVOffset = atoi(value);
                }
                else if (!_stricmp(attribute, "pe_bottomy"))
                {
                    CPostEffects::m_colourBottomVOffset = atoi(value);
                }
                else if (!_stricmp(attribute, "pe_bRadiosity"))
                {
                    CPostEffects::m_bRadiosity = atoi(value) != 0;
                }
                else if (!_stricmp(attribute, "def_brightness_pal"))
                {
                    FrontEndMenuManager.m_nBrightness = atoi(value);
                }
            }
            else
            {
                CStreaming::ms_memoryAvailable = atoi(value) << 10;
            }
        }
    }
    CFileMgr::CloseFile(file);
}

// 0x40AFA0
void CStreaming::ReclassifyLoadedCars() {
    CLoadedCarGroup appropriateCarGroup = CPopulation::m_AppropriateLoadedCars;
    CLoadedCarGroup inAppropriateCarGroup = CPopulation::m_InAppropriateLoadedCars;

    CPopulation::m_AppropriateLoadedCars.Clear();
    CPopulation::m_InAppropriateLoadedCars.Clear();

    for (auto& group : { appropriateCarGroup, inAppropriateCarGroup }) {
        for (int32 i = 0; i < group.CountMembers(); i++) {
            int32 modelId = group.GetMember(i);
            if (IsCarModelNeededInCurrentZone(modelId))
                CPopulation::m_AppropriateLoadedCars.AddMember(modelId);
            else
                CPopulation::m_InAppropriateLoadedCars.AddMember(modelId);
        }
    }
}

// 0x40CF80
void CStreaming::RemoveAllUnusedModels() {
    for (int32 i = 0; i < 50; i++) {
        RemoveLoadedVehicle();
    }
    for (int32 modelId = 1000; modelId < RESOURCE_ID_TXD; modelId++) {
        CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
        if (streamingInfo.m_nLoadState == LOADSTATE_LOADED && !CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
            RemoveModel(modelId);
            streamingInfo.m_nFlags = 0;
        }
    }
}

// 0x4093B0
void CStreaming::RemoveBigBuildings() {
    for (int32 i = CPools::ms_pBuildingPool->GetSize() - 1; i >= 0; i--) {
        CBuilding* pBuilding = CPools::ms_pBuildingPool->GetAt(i);
        if (pBuilding && pBuilding->m_bIsBIGBuilding && !pBuilding->m_bImBeingRendered) {
            pBuilding->DeleteRwObject();
            if (!CModelInfo::ms_modelInfoPtrs[pBuilding->m_nModelIndex]->m_nRefCount)
                RemoveModel(pBuilding->m_nModelIndex);
        }
    }
}

// 0x4094B0
void CStreaming::RemoveBuildingsNotInArea(eAreaCodes areaCode) {
    for (int32 i = CPools::ms_pBuildingPool->GetSize() - 1; i >= 0; i--) {
        CBuilding* pBuilding = CPools::ms_pBuildingPool->GetAt(i);
        if (pBuilding && pBuilding->m_pRwObject) {
            if (pBuilding->m_nAreaCode != areaCode && pBuilding->m_nAreaCode != AREA_CODE_13) {
                if (!pBuilding->m_bImBeingRendered && !pBuilding->m_bIsBIGBuilding)
                    pBuilding->DeleteRwObject();
            }
        }
    }
    for (int32 i = CPools::ms_pObjectPool->GetSize() - 1; i >= 0; i--) {
        CObject* pObject = CPools::ms_pObjectPool->GetAt(i);
        if (pObject && pObject->m_pRwObject) {
            if (pObject->m_nAreaCode != areaCode && pObject->m_nAreaCode != AREA_CODE_13) {
                if (!pObject->m_bImBeingRendered && pObject->m_nObjectType == eObjectType::OBJECT_GAME)
                    pObject->DeleteRwObject();
            }
        }
    }
    for (int32 i = CPools::ms_pDummyPool->GetSize() - 1; i >= 0; i--) {
        CDummy* pDummy = CPools::ms_pDummyPool->GetAt(i);
        if (pDummy && pDummy->m_pRwObject) {
            if (pDummy->m_nAreaCode != areaCode && pDummy->m_nAreaCode != AREA_CODE_13) {
                if (!pDummy->m_bImBeingRendered)
                    pDummy->DeleteRwObject();
            }
        }
    }
}

// 0x4080F0
void CStreaming::RemoveCarModel(int32 modelId) {
    CPopulation::m_AppropriateLoadedCars.RemoveMember(modelId);
    CPopulation::m_InAppropriateLoadedCars.RemoveMember(modelId);
    CPopulation::m_LoadedBoats.RemoveMember(modelId);
    for (CLoadedCarGroup& group : CPopulation::m_LoadedGangCars) {
        group.RemoveMember(modelId);
    }
    ms_vehiclesLoaded.RemoveMember(modelId);
    CPopulation::RemoveSpecificDriverModelsForCar(modelId);
}

// 0x40B080
void CStreaming::RemoveCurrentZonesModels() {
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        if (modelId >= 0) {
            SetModelIsDeletable(modelId);
            SetModelTxdIsDeletable(modelId);
            ms_pedsLoaded[i] = -1;
        }
    }
    ms_numPedsLoaded = 0;
    RequestModel(MODEL_MALE01, STREAMING_GAME_REQUIRED);
    for (int32 groupId = 0; groupId < TOTAL_GANGS; groupId++) {
        ePopcycleGroup popcycleGroup = static_cast<ePopcycleGroup>(groupId + POPCYCLE_GROUP_BALLAS);
        ePopcyclePedGroup pedGroupId = CPopulation::GetPedGroupId(popcycleGroup, 0);
        for (int32 i = 0; i < 5; i++) {
            int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, i);
            if (modelId != CPopulation::m_defaultCarGroupModelId) {
                SetModelIsDeletable(modelId);
                SetModelTxdIsDeletable(modelId);
            }
        }
    }
    ms_currentZoneType = -1;
    ms_loadedGangs = 0;
    ms_loadedGangCars = 0;
}

// 0x40BE60
void CStreaming::RemoveDodgyPedsFromRandomSlots() {
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        switch (modelId)
        {
        case MODEL_VWFYST1:
        case MODEL_VBFYST2:
        case MODEL_VHFYST3:
        case MODEL_SBFYSTR:
        case MODEL_SWFYSTR:
            SetModelIsDeletable(modelId);
            SetModelTxdIsDeletable(modelId);
            ms_pedsLoaded[i] = -1;
            ms_numPedsLoaded--;
            break;
        }
    }
}

// 0x409710
void CStreaming::RemoveEntity(CLink<CEntity*>* streamingLink)
{
    if (streamingLink) {
        if (streamingLink == ms_renderEntityLink)
            ms_renderEntityLink = ms_renderEntityLink->prev;
        ms_rwObjectInstances.Remove(streamingLink);
    }
}

// 0x40B3A0
void CStreaming::RemoveInappropriatePedModels() {
    if (CPopCycle::m_pCurrZoneInfo) {
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = ms_pedsLoaded[i];
            if (modelId >= 0 && !CPopCycle::IsPedAppropriateForCurrentZone(modelId)) {
                SetModelIsDeletable(modelId);
                SetModelTxdIsDeletable(modelId);
                ms_pedsLoaded[i] = -1;
                ms_numPedsLoaded--;
            }
        }
    }
    else {
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = ms_pedsLoaded[i];
            if (modelId >= 0) {
                SetModelIsDeletable(modelId);
                SetModelTxdIsDeletable(modelId);
                ms_pedsLoaded[i] = -1;
            }
        }
        ms_numPedsLoaded = 0;
    }
}

// 0x40CFD0
bool CStreaming::RemoveLeastUsedModel(uint32 streamingFlags) {
    auto streamingInfo = ms_pEndLoadedList->GetPrev();
    for (; streamingInfo != ms_startLoadedList; streamingInfo = streamingInfo->GetPrev()) {
        const int32 modelId = streamingInfo - ms_aInfoForModel;
        if (!(streamingFlags & streamingInfo->m_nFlags)) {
            if (modelId >= RESOURCE_ID_DFF && modelId < RESOURCE_ID_TXD) {
                if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
                    RemoveModel(modelId);
                    return true;
                }
            }
            else if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL) {
                const int32 txdId = modelId - RESOURCE_ID_TXD;
                if (!CTxdStore::GetNumRefs(txdId) && !AreTexturesUsedByRequestedModels(txdId)) {
                    RemoveModel(modelId);
                    return true;
                }
            }
            else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR) {
                const int32 animBlockId = modelId - RESOURCE_ID_IFP;
                if (!CAnimManager::GetNumRefsToAnimBlock(animBlockId) && !AreAnimsUsedByRequestedModels(animBlockId)) {
                    RemoveModel(modelId);
                    return true;
                }
            }
            else if (modelId >= RESOURCE_ID_SCM) {
                const int32 scmId = modelId - RESOURCE_ID_SCM;
                if (!CTheScripts::StreamedScripts.m_aScripts[scmId].m_nStatus) {
                    RemoveModel(modelId);
                    return true;
                }
            }
        }
    }
    if (TheCamera.GetPosition().z - TheCamera.CalculateGroundHeight(eGroundHeightType::ENTITY_BOUNDINGBOX_BOTTOM) > 50.0f
        && (ms_numPedsLoaded > 4 && RemoveLoadedZoneModel() || ms_vehiclesLoaded.CountMembers() > 4 && RemoveLoadedVehicle())
        || !ms_bLoadingScene
        && (DeleteLeastUsedEntityRwObject(false, streamingFlags)
            || ms_numPedsLoaded > 4 && RemoveLoadedZoneModel()
            || (ms_vehiclesLoaded.CountMembers() > 7 || CGame::currArea && ms_vehiclesLoaded.CountMembers() > 4)
            && RemoveLoadedVehicle())
        || DeleteLeastUsedEntityRwObject(true, streamingFlags)
        || (ms_vehiclesLoaded.CountMembers() > 7 || CGame::currArea && ms_vehiclesLoaded.CountMembers() > 4)
        && RemoveLoadedVehicle() || ms_numPedsLoaded > 4 && RemoveLoadedZoneModel())
    {
        return true;
    }
    return false;
}

bool CStreaming::CarIsCandidateForRemoval(int32 modelId) {
    CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
    if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount
        && !(streamingInfo.m_nFlags & (STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED))
        && streamingInfo.m_nLoadState == LOADSTATE_LOADED)
    {
        return true;
    }
    return false;
}

// 0x40C020
bool CStreaming::RemoveLoadedVehicle() {
    for (int32 i = 0; i < CPopulation::m_InAppropriateLoadedCars.CountMembers(); i++) {
        int32 modelId = CPopulation::m_InAppropriateLoadedCars.GetMember(i);
        if (CarIsCandidateForRemoval(modelId)) {
            RemoveModel(modelId);
            return true;
        }
    }
    int32 numBoatsNeeded = 0;
    if (CStreaming::m_bBoatsNeeded)
        numBoatsNeeded = 2;
    if (numBoatsNeeded < CPopulation::m_LoadedBoats.CountMembers()) {
        for (int32 i = 0; i < CPopulation::m_LoadedBoats.CountMembers(); i++) {
            int32 modelId = CPopulation::m_LoadedBoats.GetMember(i);
            if (CarIsCandidateForRemoval(modelId)) {
                RemoveModel(modelId);
                return true;
            }
        }
    }
    CLoadedCarGroup appropriateLoadedCars{};
    memcpy(&appropriateLoadedCars, &CPopulation::m_AppropriateLoadedCars, sizeof(CLoadedCarGroup));
    appropriateLoadedCars.SortBasedOnUsage();
    for (int32 i = 0; i < appropriateLoadedCars.CountMembers(); i++) {
        int32 modelId = appropriateLoadedCars.GetMember(i);
        if (CarIsCandidateForRemoval(modelId)) {
            RemoveModel(modelId);
            return true;
        }
    }
    return false;
}

bool CStreaming::ZoneModelIsCandidateForRemoval(int32 modelId) {
    CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
    if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount
        && !(streamingInfo.m_nFlags & (STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED))
        && streamingInfo.m_nLoadState == LOADSTATE_LOADED)
    {
        return true;
    }
    return false;
}

// 0x40B340
bool CStreaming::RemoveLoadedZoneModel() {
    if (CStreaming::ms_currentZoneType == -1 || CCheat::IsZoneStreamingAllowed())
        return false;
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        if (modelId >= 0 && ZoneModelIsCandidateForRemoval(modelId)) {
            RemoveModel(modelId);
            return true;
        }
    }
    return false;
}

// 0x4089A0
void CStreaming::RemoveModel(int32 modelId)
{
    CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];;
    if (streamingInfo.m_nLoadState == LOADSTATE_NOT_LOADED)
        return;

    if (streamingInfo.m_nLoadState == LOADSTATE_LOADED) {
        if (modelId >= RESOURCE_ID_DFF && modelId < RESOURCE_ID_TXD/*model is DFF*/) {
            CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
            pModelInfo->DeleteRwObject();
            if (pModelInfo->GetModelType() == MODEL_INFO_PED) {
                for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
                    if (ms_pedsLoaded[i] == modelId) {
                        ms_pedsLoaded[i] = -1;
                        ms_numPedsLoaded--;
                    }
                }
            } else if (pModelInfo->GetModelType() == MODEL_INFO_VEHICLE) {
                RemoveCarModel(modelId);
            }
        } else if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL/*model is TXD*/) {
            CTxdStore::RemoveTxd(modelId - RESOURCE_ID_TXD);
        } else if (modelId >= RESOURCE_ID_COL && modelId < RESOURCE_ID_IPL/*model is COL*/) {
            CColStore::RemoveCol(modelId - RESOURCE_ID_COL);
        } else if (modelId >= RESOURCE_ID_IPL && modelId < RESOURCE_ID_DAT/*model is IPL*/) {
            CIplStore::RemoveIpl(modelId - RESOURCE_ID_IPL);
        } else if (modelId >= RESOURCE_ID_DAT && modelId < RESOURCE_ID_IFP/*model is DAT*/) {
            ThePaths.UnLoadPathFindData(modelId - RESOURCE_ID_DAT);
        } else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR/*model is IFP*/) {
            CAnimManager::RemoveAnimBlock(modelId - RESOURCE_ID_IFP);
        } else if (modelId >= RESOURCE_ID_SCM/*model is SCM*/) {
            CTheScripts::StreamedScripts.RemoveStreamedScriptFromMemory(modelId - RESOURCE_ID_SCM);
        }
        ms_memoryUsed -= STREAMING_SECTOR_SIZE * streamingInfo.GetCdSize();
    }

    if (streamingInfo.m_nNextIndex == -1) {
        if (streamingInfo.m_nLoadState == LOADSTATE_READING) {
            for (int32 i = 0; i < 16; i++) {
                for (int32 channelId = 0; channelId < 2; channelId++) {
                    if (ms_channel[channelId].modelIds[i] == modelId)
                        ms_channel[channelId].modelIds[i] = -1;
                }
            }
        }
    } else {
        if (streamingInfo.m_nLoadState == LOADSTATE_REQUESTED) {
            ms_numModelsRequested--;
            if (streamingInfo.m_nFlags & STREAMING_PRIORITY_REQUEST) {
                streamingInfo.m_nFlags &= ~STREAMING_PRIORITY_REQUEST;
                ms_numPriorityRequests--;
            }
        }
        streamingInfo.RemoveFromList();
    }

    if (streamingInfo.m_nLoadState == LOADSTATE_FINISHING) {
        if (modelId < RESOURCE_ID_TXD/*model is DFF*/)
            RpClumpGtaCancelStream();
        else if (modelId < RESOURCE_ID_COL/*model is TXD*/)
            CTxdStore::RemoveTxd(modelId - RESOURCE_ID_TXD);
        else if (modelId < RESOURCE_ID_IPL/*model is COL*/)
            CColStore::RemoveCol(modelId - RESOURCE_ID_COL);
        else if (modelId < RESOURCE_ID_DAT/*model is IPL*/)
            CIplStore::RemoveIpl(modelId - RESOURCE_ID_IPL);
        else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR/*model is IFP*/)
            CAnimManager::RemoveAnimBlock(modelId - RESOURCE_ID_IFP);
        else if (modelId >= RESOURCE_ID_SCM/*model is SCM*/)
            CTheScripts::StreamedScripts.RemoveStreamedScriptFromMemory(modelId - RESOURCE_ID_SCM);
    }

    streamingInfo.m_nLoadState = LOADSTATE_NOT_LOADED;
}

void CStreaming::RemoveUnusedModelsInLoadedList() {
    // empty function
}

// 0x40C180
void CStreaming::RemoveTxdModel(int32 modelId)
{
    RemoveModel(modelId + RESOURCE_ID_TXD);
}

// 0x40E120
void CStreaming::MakeSpaceFor(int32 memoryToCleanInBytes)
{
    while (ms_memoryUsed >= ms_memoryAvailable - memoryToCleanInBytes) {
        if (!RemoveLeastUsedModel(STREAMING_LOADING_SCENE)) {
            DeleteRwObjectsBehindCamera(ms_memoryAvailable - memoryToCleanInBytes);
            return;
        }
    }
}

// 0x40C270
// Similar to the other overload but also checks if model is:
// - In the rectangle defined by `minX, minY`, `maxX, maxY`
// - In the radius of min(radius, <model draw distance> * <cam lod dist multiplier>)
void CStreaming::ProcessEntitiesInSectorList(CPtrList& list, float posX, float posY, float minX, float minY, float maxX, float maxY, float radius, int32 streamingflags) {
    CVector2D position(posX, posY);
    for (CPtrNode* pNode = list.GetNode(); pNode; pNode = pNode->m_next) {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->m_item);

        if (pEntity->m_nScanCode == CWorld::ms_nCurrentScanCode)
            continue;
        pEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;

        const uint16 modelId = pEntity->m_nModelIndex;
        if (CStreaming::ms_aInfoForModel[modelId].m_nLoadState == LOADSTATE_LOADED)
            continue;
        if (pEntity->m_bStreamingDontDelete)
            continue;
        if (pEntity->m_nAreaCode != CGame::currArea && pEntity->m_nAreaCode != AREA_CODE_13)
            continue;
        if (pEntity->m_bDontStream || !pEntity->m_bIsVisible)
            continue;

        // Check time for models visible only in specific time intervals
        CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
        CTimeInfo* pTimeInfo = pModelInfo->GetTimeInfo();
        if (pTimeInfo && !pTimeInfo->IsVisibleNow())
            continue;

        const CVector& entityPos = pEntity->GetPosition();
        if (!IsPointInRect2D(entityPos, { minX, minY }, { maxX, maxY }))
            continue;

        const float drawDistanceRadius = TheCamera.m_fLODDistMultiplier * pModelInfo->m_fDrawDistance;
        if (!IsPointInCircle2D(entityPos, position, std::min(drawDistanceRadius, radius)))
            continue;

        if (pModelInfo->m_pRwObject && !pEntity->m_pRwObject)
            pEntity->CreateRwObject();
        RequestModel(pEntity->m_nModelIndex, streamingflags);    
    }
}

// 0x40C450
// Load all required models in the given sector list
// unlike the above function (other overload) this one doesn't do radius checks
// just requests all models necessary (if they meet the conditions).
void CStreaming::ProcessEntitiesInSectorList(CPtrList& list, int32 streamingFlags) {
    for (CPtrNode* pNode = list.GetNode(); pNode; pNode = pNode->m_next) {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->m_item);
        if (pEntity->m_nScanCode == CWorld::ms_nCurrentScanCode)
            continue;
        pEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;

        const uint16 modelId = pEntity->m_nModelIndex;
        if (CStreaming::ms_aInfoForModel[modelId].m_nLoadState == LOADSTATE_LOADED)
            continue;
        if (pEntity->m_bStreamingDontDelete)
            continue;
        if (pEntity->m_nAreaCode != CGame::currArea && pEntity->m_nAreaCode != AREA_CODE_13)
            continue;
        if (pEntity->m_bDontStream || !pEntity->m_bIsVisible)
            continue;

        // Check time for models visible only in specific time intervals
        CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
        CTimeInfo* pTimeInfo = pModelInfo->GetTimeInfo();
        if (pTimeInfo && !CClock::GetIsTimeInRange(pTimeInfo->GetTimeOn(), pTimeInfo->GetTimeOff()))
            continue;

        if (pModelInfo->m_pRwObject && !pEntity->m_pRwObject)
            pEntity->CreateRwObject();
        RequestModel(pEntity->m_nModelIndex, streamingFlags);
    }
}

// 0x4076C0
void CStreaming::RetryLoadFile(int32 chIdx) {
    printf("CStreaming::RetryLoadFile called!\n"); // NOTSA

    if (ms_channelError == -1)
        return CLoadingScreen::Continue();

    CLoadingScreen::Pause(); // empty function
    if (ms_channelError == -1)
        return;

    tStreamingChannel& streamingChannel = CStreaming::ms_channel[chIdx];
    while (true) {
        bool bStreamRead = false;
        switch (streamingChannel.LoadStatus) {
        case eStreamingLoadState::LOADSTATE_LOADED: {
            if (ProcessLoadingChannel(chIdx)) {
                if (streamingChannel.LoadStatus == LOADSTATE_REQUESTED)
                    ProcessLoadingChannel(chIdx);

                ms_channelError = -1; // Clear error code
                return CLoadingScreen::Continue();
            }
            break;
        }
        case eStreamingLoadState::LOADSTATE_READING: {
            streamingChannel.totalTries++;

            // Keep in mind that `CdStreamGetStatus` changes the stream status.
            const eCdStreamStatus status = CdStreamGetStatus(chIdx);
            if ((status == eCdStreamStatus::READING || status == eCdStreamStatus::WAITING_TO_READ) &&
                (status != eCdStreamStatus::READING || CdStreamGetStatus(chIdx) != eCdStreamStatus::READING)
            ) {
                break; // Otherwise fallthrough, and do stream read
            }
            // TODO: Fallthru. Use [[fallthrough]]; from c++17
            __fallthrough;
        }
        case eStreamingLoadState::LOADSTATE_NOT_LOADED: {
            uint8* pBuffer = ms_pStreamingBuffer[chIdx];
            CdStreamRead(chIdx, pBuffer, streamingChannel.offsetAndHandle, streamingChannel.sectorCount);
            streamingChannel.LoadStatus = LOADSTATE_LOADED;
            streamingChannel.iLoadingLevel = -600;
            break;
        }
        }

        if (ms_channelError == -1)
            return CLoadingScreen::Continue();
    }
}

// 0x40E3A0
void CStreaming::LoadRequestedModels()
{
    static int32 currentChannel = 0;
    if (ms_bLoadingBigModel)
        currentChannel = 0;
    const tStreamingChannel& channel = ms_channel[currentChannel];
    if (channel.LoadStatus != LOADSTATE_NOT_LOADED)
        ProcessLoadingChannel(currentChannel);
    if (!ms_bLoadingBigModel) {
        const int32 otherChannelId = 1 - currentChannel;
        if (ms_channel[otherChannelId].LoadStatus == LOADSTATE_NOT_LOADED)
            RequestModelStream(otherChannelId);
        if (channel.LoadStatus == LOADSTATE_NOT_LOADED && !ms_bLoadingBigModel)
            RequestModelStream(currentChannel);
    }
    if (channel.LoadStatus != LOADSTATE_REQUESTED)
        currentChannel = 1 - currentChannel;
}

// 0x40E4E0
void CStreaming::FlushRequestList()
{
    auto streamingInfo = ms_pStartRequestedList->GetNext();
    while (streamingInfo != ms_pEndRequestedList) {
        auto nextStreamingInfo = streamingInfo->GetNext();
        RemoveModel(streamingInfo - ms_aInfoForModel);
        streamingInfo = nextStreamingInfo;
    }
    FlushChannels();
}

// 0x408000
bool CStreaming::AddToLoadedVehiclesList(int32 modelId)
{
    auto pVehicleModelInfo = reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelId]);
    pVehicleModelInfo->m_nTimesUsed = 0;
    CLoadedCarGroup* pLoadedCarGroup = nullptr;
    const int32 numBoats = CPopulation::m_nNumCarsInGroup[POPCYCLE_CARGROUP_BOATS];
    for (int32 i = 0; i < numBoats; i++) {
        if (CPopulation::m_CarGroups[POPCYCLE_CARGROUP_BOATS][i] == modelId) {
            pLoadedCarGroup = &CPopulation::m_LoadedBoats;
            break;
        }
    }
    if (!pLoadedCarGroup) {
        pLoadedCarGroup = &CPopulation::m_AppropriateLoadedCars;
        if (!IsCarModelNeededInCurrentZone(modelId))
            pLoadedCarGroup = &CPopulation::m_InAppropriateLoadedCars;
    }
    pLoadedCarGroup->AddMember(modelId);
    for (int32 gangId = 0; gangId < TOTAL_GANGS; gangId++) {
        const int32 groupId = gangId + POPCYCLE_CARGROUP_BALLAS;
        const uint16 numCarsInGroup = CPopulation::m_nNumCarsInGroup[groupId];
        for (int32 i = 0; i < numCarsInGroup; i++) {
            const int32 vehicleModelId = CPopulation::m_CarGroups[groupId][i];
            if (vehicleModelId == modelId) {
                CPopulation::m_LoadedGangCars[gangId].AddMember(modelId);
                break;
            }
        }
    }
    ms_vehiclesLoaded.AddMember(modelId);
    return true;
}

// 0x407D50
int32 CStreaming::GetDefaultCabDriverModel()
{
    static int32 randomIndex = 0;
    const int32 defaultCabDriverModels[7] = { MODEL_BMOCD, MODEL_WMYCD1, MODEL_SBMOCD,
        MODEL_SWMOCD, MODEL_VBMOCD , MODEL_VWMYCD, -1 };
    const int32 modelId = defaultCabDriverModels[randomIndex];
    if (!CStreaming::ms_aInfoForModel[modelId].m_nLoadState) {
        if (CTheZones::m_CurrLevel)
            randomIndex = CGeneral::GetRandomNumberInRange(0, 2 * CTheZones::m_CurrLevel);
        return defaultCabDriverModels[randomIndex];
    }
    return modelId;
}

// 0x407C50
int32 CStreaming::GetDefaultCopCarModel(int32 ignoreLvpd1Model) {
    int32 carModelId = ms_DefaultCopBikeModel;
    if (!m_bCopBikeLoaded || ignoreLvpd1Model ||
        ms_aInfoForModel[ms_DefaultCopBikerModel].m_nLoadState != LOADSTATE_LOADED ||
        ms_aInfoForModel[ms_DefaultCopBikeModel].m_nLoadState != LOADSTATE_LOADED)
    {
        carModelId = ms_aDefaultCopCarModel[CTheZones::m_CurrLevel];
        if (ms_aInfoForModel[ms_aDefaultCopModel[CTheZones::m_CurrLevel]].m_nLoadState != LOADSTATE_LOADED
            || ms_aInfoForModel[carModelId].m_nLoadState != LOADSTATE_LOADED)
        {
            int32 elementCount = 4;
            if (ignoreLvpd1Model)
                elementCount = 3;
            for (int32 i = 0; i < elementCount; i++) {
                uint8 copModelLoadState = ms_aInfoForModel[ms_aDefaultCopModel[i]].m_nLoadState;
                uint8 copCarModelLoadState = ms_aInfoForModel[ms_aDefaultCopCarModel[i]].m_nLoadState;
                if (copModelLoadState == LOADSTATE_LOADED && copCarModelLoadState == LOADSTATE_LOADED) {
                    return ms_aDefaultCopCarModel[i];
                }
            }
            return -1;
        }
    }
    return carModelId;
}

// 0x407C00
int32 CStreaming::GetDefaultCopModel()
{
    const int32 modelId = ms_aDefaultCopModel[CTheZones::m_CurrLevel];
    if (ms_aInfoForModel[modelId].m_nLoadState == LOADSTATE_LOADED)
        return modelId;
    for (int32 i = 0; i < 4; i++) {
        const int32 copModelId = ms_aDefaultCopModel[i];
        if (ms_aInfoForModel[copModelId].m_nLoadState == LOADSTATE_LOADED)
            return copModelId;
    }
    return -1;
}

// 0x407D40
int32 CStreaming::GetDefaultFiremanModel() {
    return ms_aDefaultFiremanModel[CTheZones::m_CurrLevel];
}

// 0x407D20
int32 CStreaming::GetDefaultMedicModel() {
    return ms_aDefaultMedicModel[CTheZones::m_CurrLevel];
}

// 0x5B9020
void CStreaming::Init()
{
    Init2();
}

// 0x5B8AD0
void CStreaming::Init2()
{
    for (int32 modelId = 0; modelId < RESOURCE_ID_TOTAL; modelId++) {
        ms_aInfoForModel[modelId].Init();
    }
    CStreamingInfo::ms_pArrayBase = &ms_aInfoForModel[0];
    ms_startLoadedList = &ms_aInfoForModel[RESOURCE_ID_INTERNAL_1];
    ms_pEndLoadedList = &ms_aInfoForModel[RESOURCE_ID_INTERNAL_2];
    ms_pStartRequestedList = &ms_aInfoForModel[RESOURCE_ID_INTERNAL_3];
    ms_pEndRequestedList = &ms_aInfoForModel[RESOURCE_ID_INTERNAL_4];
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_1].m_nNextIndex = RESOURCE_ID_INTERNAL_2;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_1].m_nPrevIndex = -1;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_2].m_nNextIndex = -1;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_2].m_nPrevIndex = RESOURCE_ID_INTERNAL_1;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_3].m_nNextIndex = RESOURCE_ID_INTERNAL_4;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_3].m_nPrevIndex = -1;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_4].m_nNextIndex = -1;
    ms_aInfoForModel[RESOURCE_ID_INTERNAL_4].m_nPrevIndex = RESOURCE_ID_INTERNAL_3;
    //ms_oldSectorX = 0; // Unused
    //ms_oldSectorY = 0; // Unused
    ms_aInfoForModel[374].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[375].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[376].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[377].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[378].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[379].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[380].m_nLoadState = LOADSTATE_LOADED;
    ms_aInfoForModel[381].m_nLoadState = LOADSTATE_LOADED;
    ms_streamingBufferSize = 0;
    ms_disableStreaming = false;
    ms_memoryUsed = 0;
    ms_channelError = -1;
    ms_bLoadingBigModel = false;
    ms_bEnableRequestListPurge = true;
    m_bStreamHarvesterModelsThisFrame = false;
    m_bHarvesterModelsRequested = false;
    for (int32 channelId = 0; channelId < 2; channelId++) {
        tStreamingChannel& streamingChannel = ms_channel[channelId];
        streamingChannel.LoadStatus = LOADSTATE_NOT_LOADED;
        for (int32 i = 0; i < 16; i++) {
            streamingChannel.modelIds[i] = -1;
        }
    }
    for (int32 i = 0; i < TOTAL_DFF_MODEL_IDS; i++) {
        const int32 modelId = i + RESOURCE_ID_DFF;
        auto pBaseModelnfo = CModelInfo::ms_modelInfoPtrs[modelId];
        CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
        if (pBaseModelnfo && pBaseModelnfo->m_pRwObject) {
            auto pAtomicModelInfo = pBaseModelnfo->AsAtomicModelInfoPtr();
            streamingInfo.m_nFlags = 0;
            streamingInfo.m_nFlags |= STREAMING_GAME_REQUIRED;
            streamingInfo.m_nLoadState = LOADSTATE_LOADED;
            if (pAtomicModelInfo)
                pAtomicModelInfo->m_nAlpha = 255;
        }
    }
    for (int32 i = 0; i < TOTAL_TXD_MODEL_IDS; i++) {
        const int32 modelId = i + RESOURCE_ID_TXD;
        CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
        TxdDef* pTxd = CTxdStore::ms_pTxdPool->GetAt(i);
        if (pTxd && pTxd->m_pRwDictionary) {
            streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        }
    }
    ms_vehiclesLoaded.Clear();
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        ms_pedsLoaded[i] = -1;
    }
    ms_numPedsLoaded = 0;
    for (int32 i = 0; i < 18; i++) {
        ms_NextPedToLoadFromGroup[i] = 0;
    }
    ms_pExtraObjectsDir = new CDirectory(550);
    ms_currentZoneType = -1;
    ms_loadedGangs = 0;
    ms_lastCullZone = -1;
    ms_numPriorityRequests = 0;
    CTheScripts::StreamedScripts.Initialise();
    // ms_streamingBufferSize is 0 at this point.
    // After calling LoadCdDirectory, ms_streamingBufferSize will contain the maximum number
    // of memory blocks/sectors used for a streaming model, like txd, dff, col, ipl, scm, etc.
    // The size of one streaming sector is STREAMING_BLOCK_SIZE by default.
    LoadCdDirectory();
    if (ms_streamingBufferSize & 1) // check if the value of ms_streamingBufferSize is odd
        ms_streamingBufferSize++; // make it even by adding 1

    // Since gta sa streamer runs on a secondary thread, if two models can fit
    // inside this one big buffer (one model goes in the 1st half of the buffer, the other
    // model goes in the second half), it will load the two models together.
    // Hence ms_pStreamingBuffer[0] is used by 1st channel and ms_pStreamingBuffer[1] is used by the 2nd channel.
    // If a model is big, and it cannot fit in half of the buffer, then the entire buffer is used,
    // and the model is loaded alone.

    // Here, ms_streamingBufferSize * STREAMING_BLOCK_SIZE = maximum size in bytes that a streaming model can possibly have.
    const uint32 maximumModelSizeInBytes = ms_streamingBufferSize * STREAMING_SECTOR_SIZE;
    ms_pStreamingBuffer[0] = CMemoryMgr::MallocAlign(maximumModelSizeInBytes, STREAMING_SECTOR_SIZE);
    ms_streamingBufferSize /= 2;
    ms_pStreamingBuffer[1] = &ms_pStreamingBuffer[0][STREAMING_SECTOR_SIZE * ms_streamingBufferSize];
    ms_memoryAvailable = 52428800;
    desiredNumVehiclesLoaded = 22;
    ms_rwObjectInstances.Init(12000);
    ms_bIsInitialised = true;
}

// 0x4083C0
void CStreaming::InitImageList() {
    for (int32 i = 0; i < TOTAL_IMG_ARCHIVES; i++) {
        ms_files[i].m_szName[0] = 0;
        ms_files[i].m_StreamHandle = 0;
    }
    AddImageToList("MODELS\\GTA3.IMG", true);
    AddImageToList("MODELS\\GTA_INT.IMG", true);
}

// 0x4084F0
void CStreaming::InstanceLoadedModels(CVector const& point) {
    float fRadius = 80.0f;
    if (CGame::currArea)
        fRadius = 40.0f;
    const float minX = point.x - fRadius;
    const float maxX = point.x + fRadius;
    const float minY = point.y - fRadius;
    const float maxY = point.y + fRadius;
    int32 startSectorX = std::max(CWorld::GetSectorX(minX), 0);
    int32 startSectorY = std::max(CWorld::GetSectorY(minY), 0);
    int32 endSectorX = std::min(CWorld::GetSectorX(maxX), MAX_SECTORS_X - 1);
    int32 endSectorY = std::min(CWorld::GetSectorY(maxY), MAX_SECTORS_Y - 1);
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
            CSector* pSector = GetSector(sectorX, sectorY);
            InstanceLoadedModelsInSectorList(pSector->m_buildings);
            InstanceLoadedModelsInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            InstanceLoadedModelsInSectorList(pSector->m_dummies);
        }
    }
}

void CStreaming::InstanceLoadedModelsInSectorList(CPtrList& list)
{
    for (CPtrNode* pNode = list.GetNode(); pNode; pNode = pNode->m_next) {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->m_item);
        if ((pEntity->m_nAreaCode == CGame::currArea || pEntity->m_nAreaCode == AREA_CODE_13) && !pEntity->m_pRwObject)
            pEntity->CreateRwObject();
    }
}

// 0x407DD0
bool CStreaming::IsCarModelNeededInCurrentZone(int32 modelId) {
    CZoneInfo* pCurrentZoneInfo = CPopCycle::m_pCurrZoneInfo;
    if (!CPopCycle::m_pCurrZoneInfo)
        return false;
    if (CCheat::m_aCheatsActive[CHEAT_BEACH_PARTY])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_BEACHFOLK, modelId);
    if (CCheat::m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_FARMERS, modelId);
    if (CCheat::m_aCheatsActive[CHEAT_CHEAP_TRAFFIC])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT1, modelId);
    if (CCheat::m_aCheatsActive[CHEAT_FAST_TRAFFIC])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT2, modelId);
    if (CCheat::m_aCheatsActive[CHEAT_NINJA_THEME])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT3, modelId);
    if (CCheat::m_aCheatsActive[CHEAT_FUNHOUSE_THEME])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT4, modelId);
    for (int32 groupId = 0; groupId < POPCYCLE_TOTAL_GROUP_PERCS; groupId++) {
        if (CPopCycle::GetCurrentPercTypeGroup(groupId, pCurrentZoneInfo->zonePopulationType) &&
            CPopulation::DoesCarGroupHaveModelId(groupId, modelId)) {
            return true;
        }
    }
    for (int32 groupId = 0; groupId < TOTAL_GANGS; groupId++) {
        if (pCurrentZoneInfo->GangDensity[groupId] && CPopulation::DoesCarGroupHaveModelId(groupId, modelId))
            return true;
    }
    return false;
}

// 0x407600
bool CStreaming::IsInitialised() {
    return ms_bIsInitialised;
}

// 0x407800
bool CStreaming::IsObjectInCdImage(int32 modelId) {
    return ms_aInfoForModel[modelId].GetCdSize() != 0;
}

// 0x5D29A0
void CStreaming::Save() {
    plugin::Call<0x5D29A0>();
}

// 0x407A30
void CStreaming::SetLoadVehiclesInLoadScene(bool bEnable) {
    ms_bLoadVehiclesInLoadScene = bEnable;
}

// 0x48B570
void CStreaming::SetMissionDoesntRequireAnim(int32 slot) {
    SetMissionDoesntRequireModel(slot + RESOURCE_ID_IFP);
}

// 0x409C90
void CStreaming::SetMissionDoesntRequireModel(int32 modelId) {
    for (int32 i = modelId; ; i = CModelInfo::ms_modelInfoPtrs[i]->m_nTxdIndex + RESOURCE_ID_TXD) {
        CStreamingInfo& streamingInfo = CStreaming::ms_aInfoForModel[i];
        streamingInfo.m_nFlags &= ~STREAMING_MISSION_REQUIRED;
        if (!(streamingInfo.m_nFlags & STREAMING_GAME_REQUIRED)) {
            if (streamingInfo.m_nLoadState == LOADSTATE_LOADED) {
                if (!streamingInfo.InList())
                    streamingInfo.AddToList(ms_startLoadedList);
            }
            else if (!(streamingInfo.m_nFlags & STREAMING_KEEP_IN_MEMORY)) {
                RemoveModel(i);
            }
        }
        if (i >= RESOURCE_ID_TXD)
            break;
    }
}

// 0x40B490
void CStreaming::SetMissionDoesntRequireSpecialChar(int32 slot) {
    SetMissionDoesntRequireModel(slot + SPECIAL_MODELS_RESOURCE_ID);
}

// 0x409C10
void CStreaming::SetModelIsDeletable(int32 modelId) {
    CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
    streamingInfo.m_nFlags &= ~STREAMING_GAME_REQUIRED;
    if (!(streamingInfo.m_nFlags & STREAMING_MISSION_REQUIRED)) {
        if (streamingInfo.m_nLoadState == LOADSTATE_LOADED) {
            if (!streamingInfo.InList())
                streamingInfo.AddToList(ms_startLoadedList);
        }
        else if (!(streamingInfo.m_nFlags & STREAMING_KEEP_IN_MEMORY)) {
            RemoveModel(modelId);
        }
    }
}

// 0x409C70
void CStreaming::SetModelTxdIsDeletable(int32 modelId) {
    SetModelIsDeletable(CModelInfo::ms_modelInfoPtrs[modelId]->m_nTxdIndex + RESOURCE_ID_TXD);
}

// 0x40B470
void CStreaming::SetSpecialCharIsDeletable(int32 slot) {
    SetModelIsDeletable(slot + SPECIAL_MODELS_RESOURCE_ID);
}

// 0x4084B0
void CStreaming::Shutdown() {
    CMemoryMgr::FreeAlign(ms_pStreamingBuffer[0]);
    ms_streamingBufferSize = 0;
    delete ms_pExtraObjectsDir;
}

// 0x4096C0
void CStreaming::StartRenderEntities() {
    ms_renderEntityLink = &ms_rwObjectInstances.usedListHead;
}

// 0x40A2A0
bool CStreaming::StreamAmbulanceAndMedic(bool bStreamForAccident) {
    for (int32 i = 1; i < 4; i++) {
        SetModelIsDeletable(ms_aDefaultMedicModel[i]);
        SetModelTxdIsDeletable(ms_aDefaultMedicModel[i]);
    }
    for (int32 i = 1; i < 4; i++) {
        SetModelIsDeletable(ms_aDefaultAmbulanceModel[i]);
        SetModelTxdIsDeletable(ms_aDefaultAmbulanceModel[i]);
    }
    if (!CTheZones::m_CurrLevel || !bStreamForAccident)
        return false;
    int32 medicModel = ms_aDefaultMedicModel[CTheZones::m_CurrLevel];
    int32 ambulanceModel = ms_aDefaultAmbulanceModel[CTheZones::m_CurrLevel];
    RequestModel(medicModel, STREAMING_KEEP_IN_MEMORY);
    RequestModel(ambulanceModel, STREAMING_KEEP_IN_MEMORY);
    const CStreamingInfo& medicInfo = ms_aInfoForModel[medicModel];
    const CStreamingInfo& ambulanceInfo = ms_aInfoForModel[ambulanceModel];
    if (medicInfo.m_nLoadState != LOADSTATE_LOADED || ambulanceInfo.m_nLoadState != LOADSTATE_LOADED)
        return false;
    return true;
}

// 0x40A150
void CStreaming::StreamCopModels(int32 level) {
    if (CGame::currArea)
        return;
    if (FindPlayerWanted(-1) && FindPlayerWanted(-1)->m_nWantedLevel < 3 && level && !m_bDisableCopBikes) {
        const uint32 timeInMs = CTimer::GetTimeInMS();
        if (ms_nTimePassedSinceLastCopBikeStreamedIn < timeInMs) {
            m_bCopBikeLoaded = !m_bCopBikeLoaded;
            ms_nTimePassedSinceLastCopBikeStreamedIn = timeInMs + CGeneral::GetRandomNumberInRange(30000, 50000);
        }
        if (m_bCopBikeLoaded)
            level = 4;
    }
    else {
        m_bCopBikeLoaded = false;
    }
    const CStreamingInfo& copModelInfo = ms_aInfoForModel[ms_aDefaultCopModel[level]];
    const CStreamingInfo& copCarModelInfo = ms_aInfoForModel[ms_aDefaultCopCarModel[level]];
    if (copModelInfo.m_nLoadState == LOADSTATE_LOADED && copCarModelInfo.m_nLoadState == LOADSTATE_LOADED) {
        for (int32 i = 0; i < 4; i++) {
            if (i != level) {
                if (level != 4) {
                    SetModelIsDeletable(ms_aDefaultCopModel[i]);
                    SetModelTxdIsDeletable(ms_aDefaultCopModel[i]);
                }
                SetModelIsDeletable(ms_aDefaultCopCarModel[i]);
                SetModelTxdIsDeletable(ms_aDefaultCopCarModel[i]);
            }
        }
    }
    RequestModel(ms_aDefaultCopModel[level], STREAMING_GAME_REQUIRED);
    RequestModel(ms_aDefaultCopCarModel[level], STREAMING_GAME_REQUIRED);
}

// 0x40A400
bool CStreaming::StreamFireEngineAndFireman(bool bStreamForFire) {
    for (int32 i = 1; i < 4; i++) {
        SetModelIsDeletable(ms_aDefaultFiremanModel[i]);
        SetModelTxdIsDeletable(ms_aDefaultFiremanModel[i]);
    }
    for (int32 i = 1; i < 4; i++) {
        SetModelIsDeletable(ms_aDefaultFireEngineModel[i]);
        SetModelTxdIsDeletable(ms_aDefaultFireEngineModel[i]);
    }
    if (!CTheZones::m_CurrLevel || !bStreamForFire)
        return false;
    int32 firemanModel = ms_aDefaultFiremanModel[CTheZones::m_CurrLevel];
    int32 fireTruckModel = ms_aDefaultFireEngineModel[CTheZones::m_CurrLevel];
    RequestModel(firemanModel, STREAMING_KEEP_IN_MEMORY);
    RequestModel(fireTruckModel, STREAMING_KEEP_IN_MEMORY);
    const CStreamingInfo& firemanInfo = ms_aInfoForModel[firemanModel];
    const CStreamingInfo& fireTruckInfo = ms_aInfoForModel[fireTruckModel];
    if (firemanInfo.m_nLoadState != LOADSTATE_LOADED || fireTruckInfo.m_nLoadState != LOADSTATE_LOADED)
        return false;
    return true;
}

// 0x40B4F0
void CStreaming::StreamOneNewCar() {
    if (!CPopCycle::m_pCurrZoneInfo)
        return;
    bool bCheatActive = false;
    int32 carGroupId = 0;
    if (CCheat::m_aCheatsActive[CHEAT_BEACH_PARTY]) {
        carGroupId = POPCYCLE_CARGROUP_BEACHFOLK;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC]) {
        carGroupId = POPCYCLE_CARGROUP_FARMERS;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_CHEAP_TRAFFIC]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT1;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_FAST_TRAFFIC]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT2;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_NINJA_THEME]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT3;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_FUNHOUSE_THEME]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT4;
        bCheatActive = true;
    }
    if (bCheatActive) {
        int32 carModelId = CCarCtrl::ChooseCarModelToLoad(carGroupId);
        if (carModelId < 0)
            return;
        RequestModel(carModelId, STREAMING_KEEP_IN_MEMORY);
        CPopulation::LoadSpecificDriverModelsForCar(carModelId);
        return;
    }
    if (m_bBoatsNeeded && (CPopulation::m_LoadedBoats.CountMembers() < 2 ||
        CPopulation::m_LoadedBoats.CountMembers() <= 2 && (rand() % 8) == 3)) {
        int32 carModelId = CCarCtrl::ChooseCarModelToLoad(POPCYCLE_CARGROUP_BOATS);
        if (carModelId >= 0) {
            RequestModel(carModelId, STREAMING_KEEP_IN_MEMORY);
            CPopulation::LoadSpecificDriverModelsForCar(carModelId);
            return;
        }
    }
    int32 carModelId = -1;
    if (ms_aInfoForModel[MODEL_TAXI].m_nLoadState != LOADSTATE_LOADED
        && ms_aInfoForModel[MODEL_CABBIE].m_nLoadState != LOADSTATE_LOADED) {
        static int32 lastCarModelStreamedIn = MODEL_TAXI;
        if (lastCarModelStreamedIn == MODEL_TAXI) {
            if (!IsCarModelNeededInCurrentZone(MODEL_CABBIE)) {
                if (IsCarModelNeededInCurrentZone(MODEL_TAXI)) {
                    carModelId = MODEL_TAXI;
                    lastCarModelStreamedIn = carModelId;
                }
            }
        }
        else {
            if (IsCarModelNeededInCurrentZone(MODEL_TAXI)) {
                carModelId = MODEL_TAXI;
                lastCarModelStreamedIn = carModelId;
            }
            else if (IsCarModelNeededInCurrentZone(MODEL_CABBIE)) {
                carModelId = MODEL_CABBIE;
                lastCarModelStreamedIn = carModelId;
            }
        }
    }
    if (carModelId < 0) {
        int32 carGroupId = CPopCycle::PickARandomGroupOfOtherPeds();
        carModelId = CCarCtrl::ChooseCarModelToLoad(carGroupId);
        if (carModelId < 0)
            return;
    }
    RequestModel(carModelId, STREAMING_KEEP_IN_MEMORY);
    CPopulation::LoadSpecificDriverModelsForCar(carModelId);
}

// 0x40BBB0
void CStreaming::StreamPedsForInterior(int32 interiorType) {
    if (interiorType == 0) {
        int32 numHusbands = CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_HUSBANDS, 0);
        int32 randomHusband = rand() % numHusbands;
        int32 random = CGeneral::GetRandomNumberInRange(3, 9);
        int32 randomWife = std::max(0, randomHusband - random);
        int32 numWives = CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_WIVES, 0);
        if (numWives - 1 < randomWife)
            randomWife = numWives - 1;
        ePopcyclePedGroup husbandGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_HUSBANDS, CPopulation::CurrentWorldZone);
        int32 husbandModelId = CPopulation::GetPedGroupModelId(husbandGroupId, randomHusband);
        ePopcyclePedGroup wifeGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_WIVES, CPopulation::CurrentWorldZone);
        int32 wifeModelId = CPopulation::GetPedGroupModelId(wifeGroupId, randomWife);
        ClearSlots(2);
        RequestModel(husbandModelId, STREAMING_KEEP_IN_MEMORY);
        ms_pedsLoaded[0] = husbandModelId;
        ms_numPedsLoaded++;
        RequestModel(wifeModelId, STREAMING_KEEP_IN_MEMORY);
        ms_pedsLoaded[1] = wifeModelId;
        ms_numPedsLoaded++;
    }
    else if (interiorType == 1) {
        int32 numPeds = CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_SHOPKEEPERS, 0);
        ePopcyclePedGroup groupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_SHOPKEEPERS, CPopulation::CurrentWorldZone);
        int32 modelId = CPopulation::GetPedGroupModelId(groupId, rand() % numPeds);
        ClearSlots(1);
        RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
        ms_pedsLoaded[0] = modelId;
        ms_numPedsLoaded++;
    }
    else if (interiorType == 2) {
        ClearSlots(TOTAL_LOADED_PEDS);
        int32 numPeds = CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_OFFICE_WORKERS, 0);
        int32 random = CGeneral::GetRandomNumberInRange(0, numPeds);
        ePopcyclePedGroup groupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_OFFICE_WORKERS, CPopulation::CurrentWorldZone);
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = CPopulation::GetPedGroupModelId(groupId, (i + random) % numPeds);
            RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
            ms_pedsLoaded[i] = modelId;
            ms_numPedsLoaded++;
        }
    }
}

// 0x40BDA0
void CStreaming::StreamPedsIntoRandomSlots(int32* modelArray) {
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        int32 pedModelId = modelArray[i];
        if (pedModelId >= 0) {
            if (modelId >= 0) {
                SetModelIsDeletable(modelId);
                SetModelTxdIsDeletable(modelId);
                ms_pedsLoaded[i] = -1;
                ms_numPedsLoaded--;
            }
            RequestModel(pedModelId, STREAMING_KEEP_IN_MEMORY);
            ms_pedsLoaded[i] = pedModelId;
            ms_numPedsLoaded++;
        }
        else if (pedModelId == -2) {
            if (modelId >= 0) {
                SetModelIsDeletable(modelId);
                SetModelTxdIsDeletable(modelId);
                ms_pedsLoaded[i] = -1;
                ms_numPedsLoaded--;
            }
        }
    }
}

// 0x40B700
void CStreaming::StreamVehiclesAndPeds() {
    StreamCopModels(CTheZones::m_CurrLevel);
    CWanted* pWanted = FindPlayerWanted(-1);
    if (pWanted->AreSwatRequired()) {
        RequestModel(MODEL_ENFORCER, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_SWAT, STREAMING_GAME_REQUIRED);
    }
    else {
        SetModelIsDeletable(MODEL_ENFORCER);
        if (ms_aInfoForModel[MODEL_ENFORCER].m_nLoadState != LOADSTATE_LOADED)
            SetModelIsDeletable(MODEL_SWAT);
    }
    pWanted = FindPlayerWanted(-1);
    if (pWanted->AreFbiRequired()) {
        RequestModel(MODEL_FBIRANCH, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_FBI, STREAMING_GAME_REQUIRED);
    }
    else {
        SetModelIsDeletable(MODEL_FBIRANCH);
        if (ms_aInfoForModel[MODEL_FBIRANCH].m_nLoadState != LOADSTATE_LOADED)
            SetModelIsDeletable(MODEL_FBI);
    }
    pWanted = FindPlayerWanted(-1);
    if (pWanted->AreArmyRequired()) {
        RequestModel(MODEL_RHINO, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_BARRACKS, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_ARMY, STREAMING_GAME_REQUIRED);
    }
    else {
        SetModelIsDeletable(MODEL_BARRACKS);
        SetModelIsDeletable(MODEL_RHINO);
        if (ms_aInfoForModel[MODEL_BARRACKS].m_nLoadState != LOADSTATE_LOADED
            && ms_aInfoForModel[MODEL_RHINO].m_nLoadState != LOADSTATE_LOADED)
        {
            SetModelIsDeletable(MODEL_ARMY);
        }
    }
    pWanted = FindPlayerWanted(-1);
    if (pWanted->NumOfHelisRequired() <= 0) {
        SetModelIsDeletable(MODEL_VCNMAV);
        SetModelIsDeletable(MODEL_POLMAV);
    }
    else {
        RequestModel(MODEL_POLMAV, STREAMING_GAME_REQUIRED);
        pWanted = FindPlayerWanted(-1);
        if (pWanted->NumOfHelisRequired() > 1 && CWanted::bUseNewsHeliInAdditionToPolice)
            RequestModel(MODEL_VCNMAV, STREAMING_GAME_REQUIRED);
        else
            SetModelIsDeletable(MODEL_VCNMAV);
    }
    int32 pedGroupId = -1;
    if (CPopCycle::m_NumDealers_Peds > 0.03f) {
        if (CWeather::WeatherRegion == WEATHER_REGION_SF) {
            pedGroupId = POPCYCLE_PEDGROUP_BUSINESS_LA;
        }
        else if (CPopCycle::m_pCurrZoneInfo)
        {
            uint8 currenZoneFlags = CPopCycle::m_pCurrZoneInfo->Flags2;
            if (currenZoneFlags & 1)
                pedGroupId = 0;
            else
                pedGroupId = POPCYCLE_PEDGROUP_WORKERS_VG - ((currenZoneFlags & 2) != 0);
        }
    }
    ePopcyclePedGroup dealerGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_DEALERS, 0);
    for (int32 i = 0; i < CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_DEALERS, 0); i++) {
        if (i == pedGroupId) {
            RequestModel(CPopulation::GetPedGroupModelId(dealerGroupId, i), STREAMING_GAME_REQUIRED);
        }
        else {
            int32 modelId = CPopulation::GetPedGroupModelId(dealerGroupId, i);
            SetModelIsDeletable(modelId);
        }
        dealerGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_DEALERS, 0);
    }
    static int32 framesBeforeStreamingNextNewCar = 0;
    if (framesBeforeStreamingNextNewCar >= 0) {
        --framesBeforeStreamingNextNewCar;
    }
    else if (ms_vehiclesLoaded.CountMembers() <= desiredNumVehiclesLoaded && CPopCycle::m_pCurrZoneInfo) {
        StreamOneNewCar();
        framesBeforeStreamingNextNewCar = 350;
    }
    if (m_bStreamHarvesterModelsThisFrame) {
        RequestModel(ModelIndices::MI_HARVESTERBODYPART1, STREAMING_GAME_REQUIRED);
        RequestModel(ModelIndices::MI_HARVESTERBODYPART2, STREAMING_GAME_REQUIRED);
        RequestModel(ModelIndices::MI_HARVESTERBODYPART3, STREAMING_GAME_REQUIRED);
        RequestModel(ModelIndices::MI_HARVESTERBODYPART4, STREAMING_GAME_REQUIRED);
        m_bHarvesterModelsRequested = true;
        m_bStreamHarvesterModelsThisFrame = false;
    }
    else {
        if (m_bHarvesterModelsRequested) {
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART1);
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART2);
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART3);
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART4);
            m_bHarvesterModelsRequested = false;
        }
        m_bStreamHarvesterModelsThisFrame = false;
    }
}

// 0x40B650
void CStreaming::StreamVehiclesAndPeds_Always(CVector const& unused) {
    bool bStream = false;
    CVehicle* pVehicle = FindPlayerVehicle(-1, false);
    if (!pVehicle) {
        bStream = true;
    }
    else if (pVehicle->m_vehicleSubType != VEHICLE_PLANE) {
        if (pVehicle->m_vehicleSubType != VEHICLE_HELI || pVehicle->m_vecMoveSpeed.Magnitude2D() <= 0.1f) {
            bStream = true;
        }
    }
    if (bStream) {
        if (!(CTimer::GetFrameCounter() & 0x3F) && CPopulation::m_AppropriateLoadedCars.CountMembers() < 3)
            StreamOneNewCar();
        StreamZoneModels_Gangs(CVector());
        if (CPopCycle::m_pCurrZoneInfo) {
            static int32 lastZonePopulationType = 0;
            if (CPopCycle::m_pCurrZoneInfo->zonePopulationType != lastZonePopulationType) {
                ReclassifyLoadedCars();
                lastZonePopulationType = CPopCycle::m_pCurrZoneInfo->zonePopulationType;
            }
        }
    }
}

// 0x40A560
void CStreaming::StreamZoneModels(CVector const& unused) {
    if (!CPopCycle::m_pCurrZoneInfo || CCheat::IsZoneStreamingAllowed())
        return;

    static int32 timeBeforeNextLoad = 0;
    if (CPopCycle::m_pCurrZoneInfo->zonePopulationType == ms_currentZoneType) {
        if (timeBeforeNextLoad >= 0) {
            timeBeforeNextLoad--;
        }
        else {
            int32 pedId = 0;
            int32 modelId = 0;
            for (; pedId < TOTAL_LOADED_PEDS; pedId++) {
                modelId = ms_pedsLoaded[pedId];
                if (modelId == -1)
                    break;
                if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount)
                    break;
            }
            if (pedId != TOTAL_LOADED_PEDS) {
                int32 pedModelId = CPopCycle::PickPedMIToStreamInForCurrentZone();
                if (pedModelId != modelId && pedModelId >= 0) {
                    RequestModel(pedModelId, STREAMING_KEEP_IN_MEMORY | STREAMING_GAME_REQUIRED);
                    ms_aInfoForModel[pedModelId].m_nFlags &= ~STREAMING_GAME_REQUIRED;
                    if (ms_numPedsLoaded == TOTAL_LOADED_PEDS) {
                        SetModelIsDeletable(modelId);
                        SetModelTxdIsDeletable(modelId);
                        ms_pedsLoaded[pedId] = -1;
                    }
                    else {
                        ++ms_numPedsLoaded;
                    }
                    int32 freeSlot = 0;
                    for (; ms_pedsLoaded[freeSlot] >= 0; freeSlot++) {
                    }
                    ms_pedsLoaded[freeSlot] = pedModelId;
                    timeBeforeNextLoad = 300;
                }
            }
        }
    }
    else {
        int32 numPedsToLoad = ms_numPedsLoaded;
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = ms_pedsLoaded[i];
            if (modelId >= 0) {
                SetModelIsDeletable(modelId);
                SetModelTxdIsDeletable(modelId);
                ms_pedsLoaded[i] = -1;
            }
        }
        ms_numPedsLoaded = 0;
        ms_currentZoneType = CPopCycle::m_pCurrZoneInfo->zonePopulationType;
        if (numPedsToLoad < 4)
            numPedsToLoad = 4;
        if (numPedsToLoad > 0) {
            for (int32 i = 0; i < numPedsToLoad; i++) {
                int32 pedModelId = CPopCycle::PickPedMIToStreamInForCurrentZone();
                if (pedModelId < 0) {
                    ms_pedsLoaded[i] = -1;
                }
                else {
                    RequestModel(pedModelId, STREAMING_KEEP_IN_MEMORY | STREAMING_GAME_REQUIRED);
                    ms_aInfoForModel[pedModelId].m_nFlags &= ~STREAMING_GAME_REQUIRED;
                    ms_pedsLoaded[i] = pedModelId;
                    ms_numPedsLoaded++;
                }
            }
        }
        timeBeforeNextLoad = 300;
    }
    static int32 timeBeforeNextGangLoad = 0;
    if (timeBeforeNextGangLoad >= 0) {
        timeBeforeNextGangLoad--;
    }
    else if (timeBeforeNextGangLoad < 0) {
        timeBeforeNextGangLoad = 550;
        const int32 currentGangMemberToLoadSlot = CurrentGangMemberToLoad;
        const int32 nextGangMemberToLoadSlot = CurrentGangMemberToLoad + 1;
        const int32 nextGangMemberToLoadAnySlot = (CurrentGangMemberToLoad + 1) % 21;
        CurrentGangMemberToLoad = nextGangMemberToLoadAnySlot;
        for (int32 groupId = 0; groupId < TOTAL_GANGS; groupId++) {
            const ePopcycleGroup popcycleGroup = static_cast<ePopcycleGroup>(groupId + POPCYCLE_GROUP_BALLAS);
            const ePopcyclePedGroup pedGroupId = CPopulation::GetPedGroupId(popcycleGroup, 0);
            const uint16 gang = 1 << groupId;
            if (gang & ms_loadedGangs) {
                const int32 numPedsInGroup = CPopulation::GetNumPedsInGroup(pedGroupId);
                const int32 currentGangMemberSlot = currentGangMemberToLoadSlot % numPedsInGroup;
                const int32 nextGangMemberSlot = nextGangMemberToLoadSlot % numPedsInGroup;
                const int32 nextGangMemberSlot1 = nextGangMemberToLoadAnySlot % numPedsInGroup;
                const int32 nextGangMemberSlot2 = (nextGangMemberToLoadAnySlot + 1) % numPedsInGroup;
                for (int32 slot = 0; slot < numPedsInGroup; slot++) {
                    bool bRequestModel = false;
                    if (slot == currentGangMemberSlot || slot == nextGangMemberSlot) {
                        if (slot == nextGangMemberSlot1) {
                            if (slot != currentGangMemberSlot && slot != nextGangMemberSlot) {
                                const int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, slot);
                                RequestModel(modelId, STREAMING_GAME_REQUIRED);
                            }
                        }
                        else if (slot == nextGangMemberSlot2) {
                            bRequestModel = true;
                        }
                        else {
                            const int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, slot);
                            SetModelIsDeletable(modelId);
                            SetModelTxdIsDeletable(modelId);
                        }
                    }
                    else {
                        bRequestModel = true;
                    }
                    if (bRequestModel) {
                        if (slot == nextGangMemberSlot1 || slot == nextGangMemberSlot2) {
                            if (slot != currentGangMemberSlot && slot != nextGangMemberSlot) {
                                const int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, slot);
                                RequestModel(modelId, STREAMING_GAME_REQUIRED);
                            }
                        }
                    }
                }
            }
        }
    }
}

// 0x40AA10
void CStreaming::StreamZoneModels_Gangs(CVector const& unused) {
    if (!CPopCycle::m_pCurrZoneInfo)
        return;

    int32 gangsNeeded = 0;
    for (int32 i = 0; i < TOTAL_GANGS; i++) {
        if (CPopCycle::m_pCurrZoneInfo->GangDensity[i])
            gangsNeeded |= (1 << i);
    }
    if (CCheat::m_aCheatsActive[CHEAT_GANGS_CONTROLS_THE_STREETS])
        gangsNeeded |= 0xFF;
    CGangWars::TellStreamingWhichGangsAreNeeded(&gangsNeeded);
    if (gangsNeeded == ms_loadedGangs && gangsNeeded == ms_loadedGangCars)
        return;

    for (int32 groupId = 0; groupId < TOTAL_GANGS; groupId++) {
        const ePopcycleGroup popcycleGroup = static_cast<ePopcycleGroup>(groupId + POPCYCLE_GROUP_BALLAS);
        const ePopcyclePedGroup pedGroupId = CPopulation::GetPedGroupId(popcycleGroup, 0);
        const uint16 gang = 1 << groupId;
        if (!(gangsNeeded & gang) || ms_loadedGangs & gang) {
            if (!(gangsNeeded & gang) && ms_loadedGangs & gang) {
                for (int32 i = 0; i < CPopulation::GetNumPedsInGroup(pedGroupId); ++i) {
                    int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, i);
                    SetModelIsDeletable(modelId);
                    SetModelTxdIsDeletable(modelId);
                }
                ms_loadedGangs &= ~gang;
            }
        }
        else {
            int32 slot1 = CurrentGangMemberToLoad % CPopulation::GetNumPedsInGroup(pedGroupId);
            int32 modelId1 = CPopulation::GetPedGroupModelId(pedGroupId, slot1);
            int32 slot2 = (CurrentGangMemberToLoad + 1) % CPopulation::GetNumPedsInGroup(pedGroupId);
            int32 modelId2 = CPopulation::GetPedGroupModelId(pedGroupId, slot2);
            RequestModel(modelId1, STREAMING_KEEP_IN_MEMORY);
            RequestModel(modelId2, STREAMING_KEEP_IN_MEMORY);
            ms_loadedGangs |= gang;
        }
        CLoadedCarGroup& loadedGangCarGroup = CPopulation::m_LoadedGangCars[groupId];
        if (loadedGangCarGroup.CountMembers() < 1) {
            if (!(gangsNeeded & gang) || ms_loadedGangCars & gang) {
                if (!(gangsNeeded & gang) && (ms_loadedGangCars & gang)) {
                    CLoadedCarGroup loadedCarGroup{};
                    memcpy(&loadedCarGroup, &loadedGangCarGroup, sizeof(loadedCarGroup));
                    for (int32 memberId = 0; memberId < loadedCarGroup.CountMembers(); memberId++) {
                        int32 gangCarModelId = loadedCarGroup.GetMember(memberId);
                        bool bGangHasModelId = false;
                        for (int32 i = 0; i < CPopulation::m_AppropriateLoadedCars.CountMembers(); ++i) {
                            if (gangCarModelId == CPopulation::m_AppropriateLoadedCars.GetMember(i))
                                bGangHasModelId = true;
                        }
                        for (int32 index = 0; index < TOTAL_GANGS; index++) {
                            const int32 carGroupId = index + POPCYCLE_CARGROUP_BALLAS;
                            const uint16 theGang = (1 << index);
                            if (index != groupId && (theGang & ms_loadedGangs)) {
                                for (int32 i = 0; i < 23; i++) {
                                    int32 modelId = CPopulation::m_CarGroups[carGroupId][i];
                                    if (modelId != CPopulation::m_defaultCarGroupModelId && modelId == gangCarModelId)
                                        bGangHasModelId = true;
                                }
                            }
                        }
                        if (!bGangHasModelId) {
                            SetModelIsDeletable(gangCarModelId);
                            SetModelTxdIsDeletable(gangCarModelId);
                        }
                    }
                }
            }
            else {
                const int32 carGroupId = groupId + POPCYCLE_CARGROUP_BALLAS;
                const uint16 numCars = CPopulation::m_nNumCarsInGroup[carGroupId];
                const int32 modelId = CPopulation::m_CarGroups[carGroupId][rand() % numCars];
                if (ms_aInfoForModel[modelId].m_nLoadState != LOADSTATE_LOADED)
                    RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
            }
        }
    }
    ms_loadedGangCars = gangsNeeded;
}

// 0x40E670
void CStreaming::Update() {
    g_LoadMonitor.m_numModelsRequest = ms_numModelsRequested;
    if (CTimer::GetIsPaused())
        return;

    float fDistanceZ = TheCamera.GetPosition().z - TheCamera.CalculateGroundHeight(eGroundHeightType::ENTITY_BOUNDINGBOX_BOTTOM);
    if (!ms_disableStreaming && !CRenderer::m_loadingPriority) {
        if (fDistanceZ >= 50.0) {
            if (!CGame::currArea)
                AddLodsToRequestList(TheCamera.GetPosition(), 0);
        }
        else if (CRenderer::ms_bRenderOutsideTunnels) {
            AddModelsToRequestList(TheCamera.GetPosition(), 0);
        }
    }
    if ((CTimer::GetFrameCounter() & 0x7F) == 106) {
        m_bBoatsNeeded = false;
        if (TheCamera.GetPosition().z < 500.0f)
            m_bBoatsNeeded = ThePaths.IsWaterNodeNearby(TheCamera.GetPosition(), 80.0f);
    }
    if (!ms_disableStreaming && !CCutsceneMgr::ms_cutsceneProcessing && !CGame::currArea
        && CReplay::Mode != REPLAY_MODE_1 && fDistanceZ < 50.0f)
    {
        StreamVehiclesAndPeds_Always(FindPlayerCoors(-1));
        if (!IsVeryBusy()) {
            StreamVehiclesAndPeds();
            StreamZoneModels(FindPlayerCoors(-1));
        }
    }
    LoadRequestedModels();
    CVector playerPos = FindPlayerCoors(-1);
    CVehicle* pRemoveVehicle = CWorld::Players[0].m_pRemoteVehicle;
    if (pRemoveVehicle) {
        CColStore::AddCollisionNeededAtPosn(playerPos);
        CColStore::LoadCollision(pRemoveVehicle->GetPosition(), false);
        CColStore::EnsureCollisionIsInMemory(pRemoveVehicle->GetPosition());
        CIplStore::AddIplsNeededAtPosn(playerPos);
        CIplStore::LoadIpls(pRemoveVehicle->GetPosition(), false);
        CIplStore::EnsureIplsAreInMemory(pRemoveVehicle->GetPosition());
    }
    else {
        CColStore::LoadCollision(playerPos, false);
        CColStore::EnsureCollisionIsInMemory(playerPos);
        CIplStore::LoadIpls(playerPos, false);
        CIplStore::EnsureIplsAreInMemory(playerPos);
    }
    if (ms_bEnableRequestListPurge)
        PurgeRequestList();
}

// unused
// 0x40E960
void CStreaming::UpdateForAnimViewer() {
    CVector position;
    AddModelsToRequestList(position, 0);
    LoadRequestedModels();
    sprintf(gString, "Requested %d, memory size %dK\n", ms_numModelsRequested, 2 * ms_memoryUsed);
}

// 0x407F80
bool CStreaming::WeAreTryingToPhaseVehicleOut(int32 modelId) {
    CStreamingInfo& streamingInfo = CStreaming::ms_aInfoForModel[modelId];
    if (streamingInfo.m_nLoadState == LOADSTATE_LOADED)
        return streamingInfo.m_nNextIndex >= 0 || streamingInfo.m_nPrevIndex >= 0;
    return false;
}
