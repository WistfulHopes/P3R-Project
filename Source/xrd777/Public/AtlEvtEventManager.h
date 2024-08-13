#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "InputCoreTypes.h"
#include "AppActor.h"
#include "AtlEvtEventManagerMovieSceneOperator.h"
#include "EEventManagerEventRank.h"
#include "EEventManagerMessageState.h"
#include "EEventManagerSeqControllerState.h"
#include "Templates/SubclassOf.h"

#include "BmdAssetPlugin/Public/BmdAsset.h"
#include "AtlEvtLevelSequenceActor.h"
#include "EAtlEvtEventCategoryType.h"
#include "EvtDialoguePayload.h"
//#include "AtlEvtSubsystem.h"

#include "AtlEvtEventManager.generated.h"

class AActor;
class AAtlEvtEventManager_PauseActor;
class AScrActor;
class AUIBackLog;
class AUIVoiceAnswer;
class UAtlEvtMoviePlayManager;
class UBfAsset;
class UBmdAsset;
class UEventSkipWidgetDelegate;
class UMovieSceneSequencePlayer;

UCLASS(Blueprintable)
class XRD777_API AAtlEvtEventManager : public AAppActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* FieldCameraActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* MovieSceneCameraActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEventManagerEventRank EventRank;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEventSkipWidgetDelegate* EventSkipWidget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEventSkipWidgetDelegate> EventSkipWidgetClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAtlEvtEventManagerMovieSceneOperator MovieSceneOperator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBmdAsset* mpBmdAsset;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint32> MsgUniqIDList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BmdAssetMsgID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ExecutingMessageNo;

public:
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEventManagerMessageState MessageState;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AScrActor* ScrActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AUIBackLog* UIBackLogActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AUIVoiceAnswer* UINetAnswerActor;
    
//protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UMovieSceneSequencePlayer* EventSequencePlayer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 RequestedSeqClosedEventMessageID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEventManagerSeqControllerState SeqControllerState;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AAtlEvtEventManager_PauseActor* PauseControllerActor;
    
//private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAtlEvtMoviePlayManager* MoviePlayManager;

    // Cache result for AAtlEvtEventManager::GetAtlEvtLevelSequenceActor when it's called during PIE
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    AAtlEvtLevelSequenceActor* ActiveLevelSequenceActor;

    // Evt Dialog State
    FEvtDialoguePayload CurrentEvtDialoguePayload;
    BmdData CurrentBmdData;
    TSharedRef<BmdDialogBase>* CurrentBmdDialog;
    int32 CurrentBmdPage;
    
public:
    AAtlEvtEventManager();
    UFUNCTION(BlueprintCallable)
    void SetLocalData(int32 Index, int32 Data);
    
    UFUNCTION(BlueprintCallable)
    void ResumeEventSequencer();
    
    UFUNCTION(BlueprintCallable)
    void OnFinishedAtlScr(int32 ExitType);
    
    UFUNCTION(BlueprintCallable)
    bool IsPlaying();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsEventRankA() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetLocalData(int32 Index) const;
    
    UFUNCTION(BlueprintCallable)
    void ForcedStopScript();
    
    UFUNCTION(BlueprintCallable)
    void ForcedRemoveMessage();
    
    UFUNCTION(BlueprintCallable)
    void ForceClick(FKey Key, TEnumAsByte<EInputEvent> EventType);
    
protected:
    UFUNCTION(BlueprintCallable)
    int32 ExecuteSelectScript();
    
public:
    UFUNCTION(BlueprintCallable)
    void ExecuteScript(UBfAsset* InAsset, int32 InProcNo, bool bUseBmdAssetInBfAsset, UBmdAsset* InBmdAsset);
    
protected:
    UFUNCTION(BlueprintCallable)
    int32 ExecuteMsgScript();
    
public:
    UFUNCTION(BlueprintCallable)
    void ExecuteMessageWithSelect(UBmdAsset* InAsset, int32 InMessageNo, int32 InSelectNo, int32 InSelectResponceToLocalDataID, int32 InSeqEventMessageID);
    
    UFUNCTION(BlueprintCallable)
    void ExecuteMessage(UBmdAsset* InAsset, int32 InMessageNo, int32 InEventMessageID);
    
    UFUNCTION(BlueprintCallable)
    void ExecuteBmdMessageWithSelect(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, int32 InSelectMessageMajorID, int32 InSelectMessageMinorID, int32 InSelectMessageSubID, int32 InSelectResponceToLocalDataID, bool bInEnableMessageRef, int32 InEventMessageID);
    
    UFUNCTION(BlueprintCallable)
    void ExecuteBmdMessageSubtitleWithSelect(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, int32 InDrawFrame, int32 InSelectMessageMajorID, int32 InSelectMessageMinorID, int32 InSelectMessageSubID, int32 InSelectResponceToLocalDataID, bool bInEnableMessageRef, int32 InSeqEventMessageID);
    
    UFUNCTION(BlueprintCallable)
    void ExecuteBmdMessageSubtitleSelect(UBmdAsset* InAsset, int32 InSelectMessageMajorID, int32 InSelectMessageMinorID, int32 InSelectMessageSubID, int32 InSelectResponceToLocalDataID);
    
    UFUNCTION(BlueprintCallable)
    void ExecuteBmdMessageSubtitle(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, int32 InDrawFrame, bool bInEnableMessageRef, int32 InSeqEventMessageID);
    
    UFUNCTION(BlueprintCallable)
    void ExecuteBmdMessage(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, bool bInEnableMessageRef, int32 InSeqEventMessageID);

    UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "ExecuteBmdMessage"), Category="Atl Event")
    void ReceiveExecuteBmdMessage(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, bool bInEnableMessageRef, int32 InSeqEventMessageID);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DrawMessage"), Category = "Atl Event")
    void ReceiveDrawMessage(const FString& MessageText, const FString& SpeakerText);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DrawBustup"), Category = "Atl Event")
    void ReceiveDrawBustup(int32 CharacterId, int32 a2, int32 a3, int32 a4, int32 a5, int32 a6);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "PlayVoiceLine"), Category = "Atl Event")
    void ReceivePlayVoiceLine(int32 a1, int32 a2, int32 a3, int32 a4, int32 a5, int32 a6);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetTextColor"), Category = "Atl Event")
    void ReceiveSetTextColor(FLinearColor Color);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DrawFirstName"), Category = "Atl Event")
    void ReceiveDrawFirstName();

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DrawLastName"), Category = "Atl Event")
    void ReceiveDrawLastName();

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DrawCutin"), Category = "Atl Event")
    void ReceiveDrawCutin(int32 Major, int32 Minor, int32 a3);

    UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
    AAtlEvtLevelSequenceActor* GetAtlEvtLevelSequenceActor(const UObject* WorldContextObject);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    FString CreateEventDebugText(const UObject* WorldContextObject, const FString& EventType, int32 EventMajor, int32 EventMinor, FName EventRankVisible);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateMsgDebug"), Category = "Atl Event")
    void ReceiveUpdateMsgDebug(const FString& DebugText, bool bVisibility);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Atl Event")
    void BmdTryNextPage(const UObject* WorldContextObject);

    void ExecuteBmdDialog(const UObject* WorldContextObject, FEvtDialoguePayload& Payload);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ClearBustup"), Category = "Atl Event")
    void ReceiveClearBustup();

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ClearMessageBox"), Category = "Atl Event")
    void ReceiveClearMessageBox();

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "CreateSelectOptions"), Category = "Atl Event")
    void ReceiveCreateSelectOptions(const TArray<FString>& SelOptions);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Atl Event")
    void BmdExecuteSelection(const UObject* WorldContextObject, int32 SelectId);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetLocalDataBP"), Category = "Atl Event")
    void ReceiveSetLocalDataBP(int32 Index, int32 Data);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "GetLocalDataBP"), Category = "Atl Event")
    int32 ReceiveGetLocalDataBP(int32 Index);
    
    UFUNCTION(BlueprintCallable)
    void CloseMessage();
    
    UFUNCTION(BlueprintCallable)
    void BackLogFinishDelegte();
    
    UFUNCTION(BlueprintCallable)
    void AtlEvt_ResumeEventSequencer();
    
};

