#include "AtlEvtSubsystem.h"

void UAtlEvtSubsystem::TransitionLightScenarioSublevel(int32 NextLightScenarioIndex) {
}

void UAtlEvtSubsystem::SetShowCinemaScope(bool bShow) {
}

void UAtlEvtSubsystem::SetOT(FColor Color) {
}

void UAtlEvtSubsystem::SetLocalData(int32 Index, int32 Data) {
}

void UAtlEvtSubsystem::SetEventPlayMode(EAtlEvtPlayMode InPlayMode) {
}

void UAtlEvtSubsystem::ResetLocalData() {
}

void UAtlEvtSubsystem::OnActorSpawnedEventSublevel(AActor* SpawnedActor) {
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
    return false;
}

bool UAtlEvtSubsystem::IsPlayingEventOrEditHelperMode() const {
    return false;
}

bool UAtlEvtSubsystem::IsPlayingEvent() const {
    return false;
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
    return 0;
}

TArray<FAtlEvtPlayLoadSublevelInfo> UAtlEvtSubsystem::GetLoadedEventSublevelInfos() const {
    return TArray<FAtlEvtPlayLoadSublevelInfo>();
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
    FAtlEvtPreData EvtPreData = FAtlEvtPreData();
    const FAtlEvtPreData* FoundEvtPreData = EvtPreDataMap.Find(GetEvtPreDataHash(CategoryType, EventMajorID, EventMinorID));
    if (FoundEvtPreData) {
        EvtPreData = *FoundEvtPreData;
    }
//#if WITH_EDITORONLY_DATA
//#endif
    return EvtPreData;
}

EAtlEvtPlayMode UAtlEvtSubsystem::GetEventPlayMode() const {
    return EAtlEvtPlayMode::PlayingGameMode;
}

uint32 UAtlEvtSubsystem::GetAppEvtCharactersHash(EAppCharCategoryType CharcterCategoryType, int32 CharaIndexID) const {
    return 0;
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
    // 0x14ab65e30 (PERSONA3 RELOAD 1.0.0.0 Win64)
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

void UAtlEvtSubsystem::CallCategoryEvent(UObject* WorldContextObject, EAtlEvtEventCategoryType CategoryType, int32 EventMajorID, int32 EventMinorID, const FAtlEvtPlayParameter& Param) {
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

