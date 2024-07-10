/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <Audio/entities/AEAudioEntity.h>
#include <Audio/AESound.h>
#include <Audio/eGlobalSpeechContext.h>
#include <Audio/eSoundBank.h>
#include <Audio/PedSpeechVoices.h>

enum eAudioPedType : int16 {
    PED_TYPE_UNK    = -1, // notsa
    PED_TYPE_GEN    = 0,
    PED_TYPE_EMG    = 1,
    PED_TYPE_PLAYER = 2,
    PED_TYPE_GANG   = 3,
    PED_TYPE_GFD    = 4,
    PED_TYPE_SPC    = 5, // SPC => Special (?)

    //
    // Add above
    //
    PED_TYPE_NUM // = 6
};

enum eCJMood : int32 {
    MOOD_UNK = -1, // notsa

    MOOD_AG = 0,
    MOOD_AR = 1,

    MOOD_CD = 2,
    MOOD_CF = 3, //!< CJ Is fat (?)
    MOOD_CG = 4, //!< CJ Gang banging (?)
    MOOD_CR = 5,

    MOOD_PG = 6,
    MOOD_PR = 7,

    MOOD_WG = 8,
    MOOD_WR = 9,

    //
    // Add above
    //
    MOOD_END // = 10
};


class CAEPedSpeechAudioEntity;

struct CAEPedSpeechSlot {
    enum class eStatus : int16 {
        FREE      = 0,
        LOADING   = 1,
        WAITING   = 2,
        REQUESTED = 3,
        RESERVED  = 4,
        PLAYING   = 5,
    };

    eStatus                  Status{};
    CAEPedSpeechAudioEntity* AudioEntity{};
    CAESound*                Sound{};
    int16                    SoundID{ -1 };
    eSoundBankS16            SoundBankID{ SND_BANK_UNK };
    uint32                   StartPlaybackTime{};
    eGlobalSpeechContextS16  GCtx{ GCTX_UNK };
    eAudioPedType            PedAudioType{ PED_TYPE_UNK };
    bool                     ForceAudible{};
    bool                     IsReservedForPedConversation{};
    bool                     IsReservedForPlayerConversation{};
};
VALIDATE_SIZE(CAEPedSpeechSlot, 0x1C);

struct tPhraseMemory {
    int16         SoundID{ -1 };
    eSoundBankS16 BankID{ SND_BANK_UNK };
};
VALIDATE_SIZE(tPhraseMemory, 0x04);

class NOTSA_EXPORT_VTABLE CAEPedSpeechAudioEntity : public CAEAudioEntity {
public:
    std::array<CAESound*, 5>                                m_Sounds{};
    bool                                                    m_IsInitialized{};
    eAudioPedType                                           m_PedAudioType{};
    ePedSpeechVoice                                         m_VoiceID{};  //!< Exact enum to use depends on `m_PedAudioType` (See `PedSpeechVoices.h`)
    int16                                                   m_IsFemale{};
    bool                                                    m_IsPlayingSpeech{};
    bool                                                    m_IsSpeechDisabled{};
    bool                                                    m_IsSpeechForScriptsDisabled{};
    bool                                                    m_IsFrontend{};
    bool                                                    m_IsForcedAudible{};
    CAESound*                                               m_Sound{};
    int16                                                   m_SoundID{ -1 };
    eSoundBankS16                                           m_BankID{ SND_BANK_UNK };
    int16                                                   m_PedSpeechSlotID{ -1 };
    float                                                   m_EventVolume{ -100.f };
    eGlobalSpeechContextS16                                 m_LastGCtx{ GCTX_UNK };
    std::array<uint32, GCTX_PAIN_END - GCTX_PAIN_START - 1> m_NextTimeCanSayPain{};

public:
    static inline auto& s_nCJMoodOverrideTime = StaticRef<uint32>(0xB613E0);   //!< Until when the override is active in [TimeMS]
    static inline auto& s_nCJWellDressed      = StaticRef<int16>(0xB613D0);   //!< Override as CJ being well dressed (-1 => ignore, 0/1 => false/true)
    static inline auto& s_nCJFat              = StaticRef<int16>(0xB613D4);   //!< Override as CJ being fat (-1 => ignore, 0/1 => false/true)
    static inline auto& s_nCJGangBanging      = StaticRef<int16>(0xB613D8);   //!< Override as CJ being with his group (gang) (-1 => ignore, 0/1 => false/true)
    static inline auto& s_nCJBasicMood        = StaticRef<eCJMood>(0xB613DC); //!< Override the basic mood that is used to calculate the current mood (-1 => ignore, 0/1 => false/true)

    static inline auto& s_bForceAudible                  = StaticRef<bool>(0xB613E4);
    static inline auto& s_bAPlayerSpeaking               = StaticRef<bool>(0xB613E5);
    static inline auto& s_bAllSpeechDisabled             = StaticRef<bool>(0xB613E6);
    static inline auto& s_ConversationLength             = StaticRef<int16>(0xB613E8);
    static inline auto& s_Conversation                   = StaticRef<std::array<int16, 8>>(0xB613EC);
    static inline auto& s_bPlayerConversationHappening   = StaticRef<bool>(0xB613FC);
    static inline auto& s_bPedConversationHappening      = StaticRef<bool>(0xB613FD);
    static inline auto& s_pPlayerConversationPed         = StaticRef<CPed*>(0xB61400);
    static inline auto& s_pConversationPedSlot2          = StaticRef<int16>(0xB61404);
    static inline auto& s_pConversationPedSlot1          = StaticRef<int16>(0xB61408);
    static inline auto& s_pConversationPed2              = StaticRef<CPed*>(0xB6140C);
    static inline auto& s_pConversationPed1              = StaticRef<CPed*>(0xB61410);
    static inline auto& s_NextSpeechSlot                 = StaticRef<int16>(0xB61414);

    static inline auto& s_PhraseMemory                   = StaticRef<std::array<tPhraseMemory, 150>>(0xB61418);
    static inline auto& s_PedSpeechSlots                 = StaticRef<std::array<CAEPedSpeechSlot, PED_TYPE_NUM>>(0xB61C38);
    static inline auto& gGlobalSpeechContextNextPlayTime = StaticRef<std::array<uint32, GCTX_NUM>>(0xB61670); // PAIN (GCTX_PAIN_START -> GCTX_PAIN_END) is ignored, and `m_NextTimeCanSayPain` is used instead
    static inline auto& gSpeechContextLookup             = StaticRef<notsa::mdarray<int16, GCTX_NUM, 8>>(0x8C6A68);

public:
    static void InjectHooks();

    CAEPedSpeechAudioEntity() = default;
    ~CAEPedSpeechAudioEntity() = default;

    static bool __stdcall IsGlobalContextImportantForInterupting(int16 globalCtx); // typo: Interrupting
    static bool IsGlobalContextUberImportant(int16 globalCtx);
    static int16 __stdcall GetNextMoodToUse(eCJMood lastMood);
    static int32 __stdcall GetVoiceForMood(int16 mood);
    static int16 CanWePlayScriptedSpeech();
    static float GetSpeechContextVolumeOffset(eGlobalSpeechContextS16 gctx);
    static bool RequestPedConversation(CPed* pedA, CPed* pedB);
    static void ReleasePedConversation();
    static int16 GetCurrentCJMood();
    static void StaticInitialise();
    static int16 GetSpecificSpeechContext(eGlobalSpeechContext gCtx, eAudioPedType pedAudioType);
    static void Service();
    static void Reset();
    static int8 ReservePedConversationSpeechSlots();
    static int8 ReservePlayerConversationSpeechSlot();
    static bool RequestPlayerConversation(CPed* ped);
    static void ReleasePlayerConversation();
    static void SetUpConversation();
    static int16 GetAudioPedType(Const char* name);
    static int32 GetVoice(char* name, int16 type);
    static void DisableAllPedSpeech();
    bool        IsGlobalContextPain(int16 globalCtx);
    static void SetCJMood(int16, uint32, int16, int16, int16);
    static void EnableAllPedSpeech();
    static bool IsCJDressedInForGangSpeech();
    int8        GetSexForSpecialPed(uint32 a1);

    bool IsGlobalContextImportantForWidescreen(int16 globalCtx);
    int32 GetRepeatTime(int16 a1);
    void LoadAndPlaySpeech(uint32 offset);
    int32 GetNumSlotsPlayingContext(int16 context);
    uint32 GetNextPlayTime(int16 globalCtx);
    void SetNextPlayTime(int16 globalCtx);
    void DisablePedSpeech(int16 a1);
    void DisablePedSpeechForScriptSpeech(int16 a1);
    int8 CanPedSayGlobalContext(int16 a2);
    int8 GetVoiceAndTypeFromModel(eModelID modelId);
    int16 GetSoundAndBankIDs(int16 phraseId, int16* a3);
    bool CanWePlayGlobalSpeechContext(int16 a2);
    int16 AddSayEvent(eAudioEvents audioEvent, int16 phraseId, uint32 a4, float a5, uint8 a6, uint8 a7, uint8 a8);
    void Initialise(CEntity* ped);
    bool CanPedHoldConversation();
    bool IsGlobalContextImportantForStreaming(int16 a1);
    void EnablePedSpeech();
    void EnablePedSpeechForScriptSpeech();
    void StopCurrentSpeech();
    int8 GetSoundAndBankIDsForScriptedSpeech(int32 a2);
    int8 GetSexFromModel(int32);
    bool GetPedTalking();
    int8 GetVoiceAndTypeForSpecialPed(uint32 modelNameHash);

    bool IsAllSpeechDisabled() const noexcept { return m_IsSpeechDisabled || m_IsSpeechForScriptsDisabled; }

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    virtual void AddScriptSayEvent(int32, int32, uint8, uint8, uint8);
    virtual void Terminate();
    virtual void PlayLoadedSound();
    virtual int16 GetAllocatedVoice();
    virtual bool WillPedChatAboutTopic(int16 topic);
    virtual int16 GetPedType();
    virtual bool IsPedFemaleForAudio();

private:
    CAEPedSpeechAudioEntity* Constructor();


    // NOTSA
    CAEPedSpeechSlot& GetSpeech() const {
        return s_PedSpeechSlots[m_PedSpeechSlotID];
    }
};

VALIDATE_SIZE(CAEPedSpeechAudioEntity, 0x100);
