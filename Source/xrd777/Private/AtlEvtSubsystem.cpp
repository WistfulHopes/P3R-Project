#include "AtlEvtSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtSubsystem, Log, All);

void UAtlEvtSubsystem::TransitionLightScenarioSublevel(int32 NextLightScenarioIndex) {
}

void UAtlEvtSubsystem::SetShowCinemaScope(bool bShow) {
    // 0x1410a5980 (PERSONA3 RELOAD 1.0.0.0 Win64)
    bShowCinemascope = bShow;
}

void UAtlEvtSubsystem::SetOT(FColor Color) {
}

void UAtlEvtSubsystem::SetLocalData(int32 Index, int32 Data) {
    // 0x1410a5910 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (EvtLocalData.LocalDatas.IsValidIndex(Index)) {
        EvtLocalData.LocalDatas[Index] = Data;
    }
}

void UAtlEvtSubsystem::SetEventPlayMode(EAtlEvtPlayMode InPlayMode) {
    // 0x1415569b0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    EventPlayMode = InPlayMode;
}

void UAtlEvtSubsystem::ResetLocalData() {
    // 0x14ac122a0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    EvtLocalData.LocalDatas.Empty();
    EvtLocalData.LocalDatas.SetNum(0);
    if (EvtLocalData.LocalDatas.Max() < 0x30) {
        EvtLocalData.LocalDatas.Reserve(0x30);
    }
    if (EvtLocalData.LocalDatas.Num() < 0x30) {
        EvtLocalData.LocalDatas.SetNum(0x30);
    }
}

void UAtlEvtSubsystem::OnActorSpawnedEventSublevel(AActor* SpawnedActor) {
    // 0x14abc5370 (PERSONA3 RELOAD 1.0.0.0 Win64)
    UAppCharBaseComp* AppCharBase = SpawnedActor->FindComponentByClass<UAppCharBaseComp>();
    if (AppCharBase) {
        uint32 CharHash = GetAppEvtCharactersHash(AppCharBase->GetCategoryID(), AppCharBase->GetIndexID());
        FAtlEvtPlayingCharacterInfo CharInfoEmpty;
        AppEvtCharactersMap.Add(CharHash, CharInfoEmpty);
    }
}

TArray<FString> UAtlEvtSubsystem::MakeFieldSublevelPathListField(const UObject* WorldContextObject, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
    return TArray<FString>();
}

TArray<FString> UAtlEvtSubsystem::MakeFieldSublevelPathListEvent(const UObject* WorldContextObject, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
    return TArray<FString>();
}

TArray<FString> UAtlEvtSubsystem::MakeFieldSublevelPathListCmmu(const UObject* WorldContextObject, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
    return TArray<FString>();
}

TArray<FString> UAtlEvtSubsystem::MakeFieldSublevelPathList(const UObject* WorldContextObject, EAtlEvtEventCategoryType CategoryType, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
    return TArray<FString>();
}

bool UAtlEvtSubsystem::IsShowCinemaScope() const {
    // 0x14109aeb0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    return bShowCinemascope;
}

bool UAtlEvtSubsystem::IsPlayingEventOrEditHelperMode() const {
    // 0x14109ab10 (PERSONA3 RELOAD 1.0.0.0 Win64)
    return bIsPlaying;
}

bool UAtlEvtSubsystem::IsPlayingEvent() const {
    // 0x141555dc0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    return bIsPlaying;
}

bool UAtlEvtSubsystem::IsHighSpeed() const {
    return false;
}

bool UAtlEvtSubsystem::IsFinishedPreloadLightScenarioSublevels() const {
    return false;
}

bool UAtlEvtSubsystem::IsEventPlayModeEditHelper() const {
    return false;
}

bool UAtlEvtSubsystem::IsDoingTransitionLightScenarioSublevel() const {
    return false;
}

bool UAtlEvtSubsystem::IsConditionalBranchFromLocalData(EEvtConditionalBranchCompType CompType, int32 LHS, int32 Index) {
    return false;
}

void UAtlEvtSubsystem::InitScriptFinishFunction(int32 ExitType) {
}

FAtlEvtVisibleEventInfo UAtlEvtSubsystem::GetPlayingVisibleEventInfo(const UObject* WorldContextObject) const {
    return FAtlEvtVisibleEventInfo{};
}

int32 UAtlEvtSubsystem::GetLocalData(int32 Index) const {
    // 0x14ab9f250 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (EvtLocalData.LocalDatas.IsValidIndex(Index)) {
        return EvtLocalData.LocalDatas[Index];
    }
    return 0;
}

TArray<FAtlEvtPlayLoadSublevelInfo> UAtlEvtSubsystem::GetLoadedEventSublevelInfos() const {
    // 0x1415558e0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    return LoadedEventSublevelInfos;
}

AActor* UAtlEvtSubsystem::GetFirstAppEventCharacterByLipUniqueID(int32 LipUniqueID) const {
    return NULL;
}

AActor* UAtlEvtSubsystem::GetFirstAppEventCharacter(EAppCharCategoryType CharcterCategoryType, int32 CharaIndexID) const {
    return NULL;
}

uint32 UAtlEvtSubsystem::GetEvtPreDataHash(EAtlEvtEventCategoryType CategoryType, int32 EventMajorID, int32 EventMinorID) const {
    // https://github.com/rirurin/p3rpc.nativetypes/blob/6ef7013234b9599b78ec52ef55225f788602cc17/p3rpc.nativetypes.Interfaces/Xrd777.cs#L4456
    uint32 uVar3 = EventMajorID - EventMinorID ^ (uint32)EventMinorID >> 0xd;
    uint32 uVar1 = (uint32)(-0x61c88647 - uVar3) - (uint32)EventMinorID ^ uVar3 << 8;
    uint32 uVar4 = (EventMinorID - uVar1) - uVar3 ^ uVar1 >> 0xd;
    uVar3 = (uVar3 - uVar1) - uVar4 ^ uVar4 >> 0xc;
    uVar1 = (uVar1 - uVar3) - uVar4 ^ uVar3 << 0x10;
    uVar4 = (uVar4 - uVar1) - uVar3 ^ uVar1 >> 5;
    uVar3 = (uVar3 - uVar1) - uVar4 ^ uVar4 >> 3;
    uVar1 = (uVar1 - uVar3) - uVar4 ^ uVar3 << 10;
    uVar1 = (uVar4 - uVar1) - uVar3 ^ uVar1 >> 0xf;
    uint32 iVar2 = uVar1 - (uint32)CategoryType;
    uVar3 = 0x9e3779b9 - uVar1 ^ iVar2 * 0x100;
    uVar4 = ((uint32)CategoryType - uVar3) - iVar2 ^ uVar3 >> 0xd;
    uVar1 = (iVar2 - uVar3) - uVar4 ^ uVar4 >> 0xc;
    uVar3 = (uVar3 - uVar1) - uVar4 ^ uVar1 << 0x10;
    uVar4 = (uVar4 - uVar3) - uVar1 ^ uVar3 >> 5;
    uVar1 = (uVar1 - uVar3) - uVar4 ^ uVar4 >> 3;
    uVar3 = (uVar3 - uVar1) - uVar4 ^ uVar1 << 10;
    return (uVar4 - uVar3) - uVar1 ^ uVar3 >> 0xf;
}

FAtlEvtPreData UAtlEvtSubsystem::GetEvtPreData(EAtlEvtEventCategoryType CategoryType, int32 EventMajorID, int32 EventMinorID) const {
    // 0x14ab96f60 (PERSONA3 RELOAD 1.0.0.0 Win64)
    FAtlEvtPreData EvtPreData = FAtlEvtPreData();
    const FAtlEvtPreData* FoundEvtPreData = EvtPreDataMap.Find(GetEvtPreDataHash(CategoryType, EventMajorID, EventMinorID));
    if (FoundEvtPreData) {
        EvtPreData = *FoundEvtPreData;
    }
    return EvtPreData;
}

EAtlEvtPlayMode UAtlEvtSubsystem::GetEventPlayMode() const {
    // 0x1415554d0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    return EventPlayMode;
}

uint32 UAtlEvtSubsystem::GetAppEvtCharactersHash(EAppCharCategoryType CharcterCategoryType, int32 CharaIndexID) const {
    // 0x14ab95490 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if ((CharcterCategoryType == EAppCharCategoryType::NpcCharacter) && (10000 < (int32)CharaIndexID)) {
        CharaIndexID = CharaIndexID / 10000;
    }
    uint32 uVar2 = (uint32)CharcterCategoryType - (uint32)CharaIndexID ^ (uint32)CharaIndexID >> 0xd;
    uint32 uVar1 = (-0x61c88647 - uVar2) - (uint32)CharaIndexID ^ uVar2 << 8;
    uint32 uVar3 = ((uint32)CharaIndexID - uVar1) - uVar2 ^ uVar1 >> 0xd;
    uVar2 = (uVar2 - uVar1) - uVar3 ^ uVar3 >> 0xc;
    uVar1 = (uVar1 - uVar2) - uVar3 ^ uVar2 << 0x10;
    uVar3 = (uVar3 - uVar1) - uVar2 ^ uVar1 >> 5;
    uVar2 = (uVar2 - uVar1) - uVar3 ^ uVar3 >> 3;
    uVar1 = (uVar1 - uVar2) - uVar3 ^ uVar2 << 10;
    return (uVar3 - uVar1) - uVar2 ^ uVar1 >> 0xf;
}

FAtlEvtPlayingCharacterInfo UAtlEvtSubsystem::GetAppEventCharacter(EAppCharCategoryType CharcterCategoryType, int32 CharaIndexID) const {
    return FAtlEvtPlayingCharacterInfo{};
}

void UAtlEvtSubsystem::EvtPlay(const UObject* WorldContextObject, const FString& EvtName, const FString& InEventRank, const FAtlEvtPlayParameter& Param) {
}

void UAtlEvtSubsystem::DateOffDelegate(int32 idx) {
}

void UAtlEvtSubsystem::CallEventField(UObject* WorldContextObject, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
}

void UAtlEvtSubsystem::CallEventCmmu(UObject* WorldContextObject, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
}

AAtlEvtPlayObject* UAtlEvtSubsystem::CallEvent_SpawnLoadSublevelActor(UWorld* World, FName& StreamTargetLevelName, const FAtlEvtPlayParameter& Param, FAtlEvtPreData& PreData, EAtlEvtSublevelType SublevelType, FLatentActionInfo& LatentInfo, UObject* WorldContextObject) {
    return NULL;
}

bool UAtlEvtSubsystem::CallEvent_IsCompleteFieldLoadingSublevel() const {
    return false;
}

void UAtlEvtSubsystem::CallEvent_InternalFinishedEvent(int32 Value) {
    // 0x141092a00 (PERSONA3 RELOAD 1.0.0.0 Win64)
    AppEvtCharactersMap.Empty();
    AppEvtLipUniqueIDCharactersMap.Empty();
    if (OnePicture) {
        OnePicture->Destroy();
        OnePicture = nullptr;
    }
    pLSAssetLoader = nullptr;
    LevelSequenceObject = nullptr;
}

void UAtlEvtSubsystem::CallEvent_DecrementFieldLoadingCount() {
}

void UAtlEvtSubsystem::CallEvent(UObject* WorldContextObject, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
}

bool UAtlEvtSubsystem::IsEventRankA() {
    return EventRank == TEXT("A");
}

void UAtlEvtSubsystem::CallCategoryEvent(UObject* WorldContextObject, EAtlEvtEventCategoryType CategoryType, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
    // Loosely based on original implementation of UAtlEvtSubsystem::CallCategoryEvent
    // 0x141092a00 (PERSONA3 RELOAD 1.0.0.0 Win64)
    UWorld* CurrentWorld = GEngine->GetWorldFromContextObject(WorldContextObject);
    if (CurrentWorld) {
        FAtlEvtPreData PreData = GetEvtPreData(CategoryType, EventMajorID, EventMinorID);
        if (PreData.EventMajorID < 0) {
            UE_LOG(AtlEvtSubsystem, Error, TEXT("Call None Event. [event_major:%d minor:%d]"), EventMajorID, EventMinorID);
            CallEvent_InternalFinishedEvent(0);
            return;
        }

        AppEvtCharactersMap.Empty();
        AppEvtLipUniqueIDCharactersMap.Empty();
        // Get event manager and level sequence actors
        // See AAtlEvtPlayObject::OnLoadedMovieTrack
        AActor** AtlEvtManagerMaybe = CurrentWorld->PersistentLevel->Actors.FindByPredicate([](AActor*& CurrentActor) { return CurrentActor->IsA<AAtlEvtEventManager>(); });
        if (!AtlEvtManagerMaybe) {
            UE_LOG(AtlEvtSubsystem, Error, TEXT("Couldn't find event manager in Level!"));
            return;
        }
        AAtlEvtEventManager* EvtManager = Cast<AAtlEvtEventManager>(*AtlEvtManagerMaybe);
        AActor** LevelSeqMaybe = CurrentWorld->PersistentLevel->Actors.FindByPredicate([](AActor*& CurrentActor) { return CurrentActor->IsA<ALevelSequenceActor>();  });
        if (!LevelSeqMaybe) {
            UE_LOG(AtlEvtSubsystem, Error, TEXT("Couldn't find level sequence actor in level!"));
            return;
        }
        AAtlEvtLevelSequenceActor* EvtLevelSeq = Cast<AAtlEvtLevelSequenceActor>(*LevelSeqMaybe);
        ULevelSequence* LevelSeq = EvtLevelSeq->LoadSequence();
        //LevelSeq->FindPossessableObjectId()

        // Load streamed levels
        FVector StreamLevelPos = FVector(0, 0, 0);
        FRotator StreamLevelRot = FRotator(0, 0, 0);
        bool bStreamLevelSucceeded = false;
        for (FAtlEvtPreSublevelData& Sublevel : PreData.EventSublevels) {
            for (FString& BGLevelPath : Sublevel.EventBGLevels) {
                // P3RE calls UAtlEvtSubsystem::CallEvent_SpawnLoadSublevelActor when loading in a sublevel actor. This loads the level in using
                // UGameplayStatics::LoadStreamLevel and passes in a FLatentActionInfo to call AAtlEvtPlayObject::OnLoadFieldLevelStreaming.
                // It returns an AAtlEvtPlayObject*
                ULevelStreamingDynamic* CurrentBGLevel = ULevelStreamingDynamic::LoadLevelInstance(WorldContextObject, BGLevelPath, StreamLevelPos, StreamLevelRot, bStreamLevelSucceeded);
                if (!bStreamLevelSucceeded) {
                    UE_LOG(AtlEvtSubsystem, Warning, TEXT("[UEvtSubsystem::CallEvent] Not found Sublevel[%s] in Persistent Level!!!!"), *BGLevelPath);
                }
            }
            ULevelStreamingDynamic* CurrentSeasonLevel = ULevelStreamingDynamic::LoadLevelInstance(WorldContextObject, Sublevel.BGFieldSeasonSubLevel, StreamLevelPos, StreamLevelRot, bStreamLevelSucceeded);
            if (!bStreamLevelSucceeded) {
                UE_LOG(AtlEvtSubsystem, Warning, TEXT("[UEvtSubsystem::CallEvent] Not found Season Sublevel[%s] in Persistent Level!!!!"), *Sublevel.BGFieldSeasonSubLevel);
            }
            ULevelStreamingDynamic* CurrentSoundLevel = ULevelStreamingDynamic::LoadLevelInstance(WorldContextObject, Sublevel.BGFieldSoundSubLevel, StreamLevelPos, StreamLevelRot, bStreamLevelSucceeded);
            if (!bStreamLevelSucceeded) {
                UE_LOG(AtlEvtSubsystem, Warning, TEXT("[UEvtSubsystem::CallEvent] Not found Sound Sublevel[%s] in Persistent Level!!!!"), *Sublevel.BGFieldSoundSubLevel);
            }
            // TODO: Crowd sublevel
        }
        for (FName& LightScenario : PreData.LightScenarioSublevels) {
            FString LightScenarioStr = LightScenario.ToString();
            ULevelStreamingDynamic* CurrentLightScenarioSublevel = ULevelStreamingDynamic::LoadLevelInstance(WorldContextObject, LightScenarioStr, StreamLevelPos, StreamLevelRot, bStreamLevelSucceeded);
            if (!bStreamLevelSucceeded) {
                UE_LOG(AtlEvtSubsystem, Warning, TEXT("[UEvtSubsystem::CallEvent] Not found LightScenario Sublevel[%s] in Persistent Level!!!!"), *LightScenarioStr);
            }
        }

        
        // Get actor data
        for (AActor*& LevelActor : CurrentWorld->PersistentLevel->Actors) {
            if (LevelActor->IsA<ALevelSequenceActor>()) {
                ALevelSequenceActor* LevelSequenceActor = Cast<ALevelSequenceActor>(LevelActor);
                LevelSequenceActor->SequencePlayer->Play();
                /*
                if (LevelSequenceActor->LevelSequence.IsValid()) {
                    ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->LevelSequence.ResolveObject());
                    if (!LevelSequence) {
                        LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->LevelSequence.TryLoad());
                    }
                    //LevelSequence->GetMovieScene()->
                    //LevelSequenceActor->Play
                }
                else {
                    UE_LOG(AtlEvtSubsystem, Error, TEXT("Level Sequence is missing!"));
                }*/
            }
            else {
                UAppCharBaseComp* CharBaseComp = LevelActor->FindComponentByClass<UAppCharBaseComp>();
                if (CharBaseComp) {
                    uint32 CharHash = GetAppEvtCharactersHash(CharBaseComp->GetCategoryID(), CharBaseComp->GetIndexID());
                    FAtlEvtPlayingCharacterInfo* PlayerCharInfoMaybe = AppEvtCharactersMap.Find(CharHash);
                    if (!PlayerCharInfoMaybe) {
                        FAtlEvtPlayingCharacterInfo NewEntry = FAtlEvtPlayingCharacterInfo();
                        NewEntry.AppEventCharacters.Add(LevelActor);
                        AppEvtCharactersMap.Add(CharHash, NewEntry);
                    }
                    else {
                        PlayerCharInfoMaybe->AppEventCharacters.Add(LevelActor);
                    }
                }
            }
        }
    }
}

UAtlEvtSubsystem::UAtlEvtSubsystem() {
    this->LightScenarioTransitionController = NULL;
    this->pLSAssetLoader = NULL;
    this->LevelSequenceObject = NULL;
    this->EvtPreDataAsset = NULL;
    this->AssetOverrideLoader = NULL;
    this->AssetOverrideSubClass = NULL;
    this->BagActor = NULL;
    this->OnePicture = NULL;

#if WITH_EDITORONLY_DATA

    this->EventPlayMode = EAtlEvtPlayMode::PlayingGameMode;

    // UAtlEvtSubsystem::FillEvtPreDataMap
    // 0x14aba71a0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    FString EvtPreDataPath = TEXT("/Game/Xrd777/Events/Data/DataAsset/EvtPreDataAsset.EvtPreDataAsset");
    //EvtPreDataAsset = Cast<UAtlEvtPreDataAsset>(StaticFindObject(UAtlEvtPreDataAsset::StaticClass(), nullptr, *EvtPreDataPath));
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FAssetData EvtPreDataAsset = AssetRegistryModule.Get().GetAssetByObjectPath(*EvtPreDataPath);
    if (EvtPreDataAsset.IsValid()) {
        for (FAtlEvtPreData& EventEntry : Cast<UAtlEvtPreDataAsset>(EvtPreDataAsset.GetAsset())->Data) {
            uint32 EvtHash = GetEvtPreDataHash((EAtlEvtEventCategoryType)EventEntry.EventCategoryTypeID, EventEntry.EventMajorID, EventEntry.EventMinorID);
            EvtPreDataMap.Add(EvtHash, EventEntry);
        }
    }
#endif
}

