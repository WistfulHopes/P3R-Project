#include "AtlEvtEventManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogAtlEvtEventManager, Log, All);

void AAtlEvtEventManager::SetLocalData(int32 Index, int32 Data) {
}

void AAtlEvtEventManager::ResumeEventSequencer() {
}

void AAtlEvtEventManager::OnFinishedAtlScr(int32 ExitType) {
}

bool AAtlEvtEventManager::IsPlaying() {
    return false;
}

bool AAtlEvtEventManager::IsEventRankA() const {
    return false;
}

int32 AAtlEvtEventManager::GetLocalData(int32 Index) const {
    return 0;
}

void AAtlEvtEventManager::ForcedStopScript() {
}

void AAtlEvtEventManager::ForcedRemoveMessage() {
}

void AAtlEvtEventManager::ForceClick(FKey Key, TEnumAsByte<EInputEvent> EventType) {
}

int32 AAtlEvtEventManager::ExecuteSelectScript() {
    return 0;
}

void AAtlEvtEventManager::ExecuteScript(UBfAsset* InAsset, int32 InProcNo, bool bUseBmdAssetInBfAsset, UBmdAsset* InBmdAsset) {
}

int32 AAtlEvtEventManager::ExecuteMsgScript() {
    return 0;
}

void AAtlEvtEventManager::ExecuteMessageWithSelect(UBmdAsset* InAsset, int32 InMessageNo, int32 InSelectNo, int32 InSelectResponceToLocalDataID, int32 InSeqEventMessageID) {
}

void AAtlEvtEventManager::ExecuteMessage(UBmdAsset* InAsset, int32 InMessageNo, int32 InEventMessageID) {
}

void AAtlEvtEventManager::ExecuteBmdMessageWithSelect(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, int32 InSelectMessageMajorID, int32 InSelectMessageMinorID, int32 InSelectMessageSubID, int32 InSelectResponceToLocalDataID, bool bInEnableMessageRef, int32 InEventMessageID) {
    if (MessageState == EEventManagerMessageState::RunningMessage) {
        ExecuteBmdMessage(InAsset, InMessageMajorID, InMessageMinorID, InMessageSubID, InMessagePageID, bInEnableMessageRef, InEventMessageID);
    }
    else {
        FString SelDialogName = BmdDialogSelection::GetMessageName(InSelectMessageMajorID, InSelectMessageMinorID, InSelectMessageSubID);
        TSharedRef<BmdDialogBase>* SelMsgRef = CurrentBmdData.Dialogs.Find(SelDialogName);
        if (SelMsgRef) {
            BmdDialogBase& SelMsg = SelMsgRef->Get();
            ReceiveUpdateMsgDebug(FString::Printf(TEXT("<<< \t SEL INFO \t NAME: %s \t >>>"), *SelMsg.Name), true);
            TArray<FString> SelOptions;
            for (auto& SelPage : SelMsg.Pages) {
                for (TSharedPtr<BmdTokenBase>& Token : SelPage) {
                    if (Token.IsValid()) {
                        BmdTokenBase* TokenInner = Token.Get();
                        if (TokenInner->IsText()) {
                            SelOptions.Add(((BmdMessageToken*)TokenInner)->MessageText);
                        }
                    }
                }
            }
            ReceiveCreateSelectOptions(SelOptions);
        }
        else {
            UE_LOG(LogAtlEvtEventManager, Error, TEXT("Selection Entry %s is missing from BMD!!"), *SelDialogName);
        }
    }
}

void AAtlEvtEventManager::ExecuteBmdMessageSubtitleWithSelect(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, int32 InDrawFrame, int32 InSelectMessageMajorID, int32 InSelectMessageMinorID, int32 InSelectMessageSubID, int32 InSelectResponceToLocalDataID, bool bInEnableMessageRef, int32 InSeqEventMessageID) {
}

void AAtlEvtEventManager::ExecuteBmdMessageSubtitleSelect(UBmdAsset* InAsset, int32 InSelectMessageMajorID, int32 InSelectMessageMinorID, int32 InSelectMessageSubID, int32 InSelectResponceToLocalDataID) {
}

void AAtlEvtEventManager::ExecuteBmdMessageSubtitle(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, int32 InDrawFrame, bool bInEnableMessageRef, int32 InSeqEventMessageID) {
}

void AAtlEvtEventManager::ExecuteBmdMessage(UBmdAsset* InAsset, int32 InMessageMajorID, int32 InMessageMinorID, int32 InMessageSubID, int32 InMessagePageID, bool bInEnableMessageRef, int32 InSeqEventMessageID) {

    // Original function: 0x14ab888e0 (PERSONA3 RELOAD Steam v1.0.0.0)

    //ReceiveExecuteBmdMessage(InAsset, InMessageMajorID, InMessageMinorID, InMessageSubID, InMessagePageID, bInEnableMessageRef, InSeqEventMessageID);
    if (CurrentBmdDialog) {
        BmdDialogBase& TargetDialog = CurrentBmdDialog->Get();
        // Draw debug information
        ReceiveUpdateMsgDebug(FString::Printf(TEXT("<<< \t MSG INFO \t NAME: %s \t PAGE: %d \t >>>"), *TargetDialog.Name, InMessagePageID), true);

        FString SpeakerName = TEXT("");
        if (TargetDialog.DialogKind == BmdBinaryDialogKind::Message) {
            if (FString* SpeakerMaybe = ((BmdDialogMessage*)(&TargetDialog))->Speaker) {
                SpeakerName = *SpeakerMaybe;
            }
        }
        for (TSharedPtr<BmdTokenBase>& Token : TargetDialog.Pages[InMessagePageID]) {
            if (Token.IsValid()) {
                BmdTokenBase* TokenInner = Token.Get();
                if (TokenInner->IsText()) {
                    ReceiveDrawMessage(((BmdMessageToken*)TokenInner)->MessageText, SpeakerName);
                }
                else { // Function tokens
                    BmdFunctionToken* FnToken = (BmdFunctionToken*)TokenInner;
                    switch (FnToken->TableIndex) {
                    case 0:
                        switch (FnToken->FunctionIndex) {
                        case 1:
                            ReceiveSetTextColor(BmdFunctionToken::GetMessageColor((int32)FnToken->Parameters[0]));
                            break;
                        }
                        break;
                    case 3:
                        switch (FnToken->FunctionIndex) {
                        case 1:
                            ReceivePlayVoiceLine(FnToken->Parameters[0], FnToken->Parameters[1], FnToken->Parameters[2],
                                FnToken->Parameters[3], FnToken->Parameters[4], FnToken->Parameters[5]);
                            break;
                        }
                        break;
                    case 4:
                        switch (FnToken->FunctionIndex) {
                        case 1:
                            ReceiveDrawLastName();
                            break;
                        case 2:
                            ReceiveDrawFirstName();
                            break;
                        case 5:
                            ReceiveDrawBustup(FnToken->Parameters[0], FnToken->Parameters[1], FnToken->Parameters[2],
                                FnToken->Parameters[3], FnToken->Parameters[4], FnToken->Parameters[5]);
                            break;
                        case 17:
                            ReceiveDrawCutin(FnToken->Parameters[0], FnToken->Parameters[1], FnToken->Parameters[2]);
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}

AAtlEvtLevelSequenceActor* AAtlEvtEventManager::GetAtlEvtLevelSequenceActor(const UObject* WorldContextObject) {
    if (ActiveLevelSequenceActor) {
        return ActiveLevelSequenceActor;
    }
    UWorld* CurrentWorld = WorldContextObject->GetWorld();
    if (!CurrentWorld) {
        return nullptr;
    }
    for (AActor*& Actor : CurrentWorld->GetCurrentLevel()->Actors) {
        if (Actor->IsA<AAtlEvtLevelSequenceActor>()) {
            ActiveLevelSequenceActor = (AAtlEvtLevelSequenceActor*)Actor;
            return ActiveLevelSequenceActor;
        }
    }
    return nullptr;
}

FString AAtlEvtEventManager::CreateEventDebugText(const UObject* WorldContextObject, const FString& EventType, int32 EventMajor, int32 EventMinor, FName EventRankVisible) {
    AAtlEvtLevelSequenceActor* LevelSequenceActor = GetAtlEvtLevelSequenceActor(WorldContextObject);
    int32 CurrTime = 0;
    int32 EndTime = 0;
    if (LevelSequenceActor && LevelSequenceActor->GetSequencePlayer()) {
        CurrTime = LevelSequenceActor->GetSequencePlayer()->GetCurrentTime().Time.FrameNumber.Value;
        EndTime = LevelSequenceActor->GetSequencePlayer()->GetEndTime().Time.FrameNumber.Value;
    }
    return FString::Printf(TEXT("<<< \t EVENT INFO \t ID:%03d_%03d \t TYPE: %s \t RANK: %s \t COUNT: %d/%d \t >>>"), EventMajor, EventMinor, *EventType, *EventRankVisible.ToString(), CurrTime, EndTime);
}

void AAtlEvtEventManager::ExecuteBmdDialog(const UObject* WorldContextObject, FEvtDialoguePayload& Payload) {
    CurrentEvtDialoguePayload = Payload;
    // Load BMD data if required
    if (!mpBmdAsset || Payload.BmdAsset != mpBmdAsset) {
        mpBmdAsset = Payload.BmdAsset;
        TArrayView<const uint8> BufData = TArrayView<const uint8>((const uint8*)mpBmdAsset->mBuf.GetData(), mpBmdAsset->mBuf.Num());
        FMemoryReaderView BufReader = FMemoryReaderView(BufData);
        BufReader << CurrentBmdData;
    }
    AAtlEvtLevelSequenceActor* LevelSequenceActor = GetAtlEvtLevelSequenceActor(WorldContextObject);
    if (!LevelSequenceActor) {
        UE_LOG(LogAtlEvtEventManager, Error, TEXT("Level Sequence Actor is missing!!!"));
        return;
    }
    if (!LevelSequenceActor->SequencePlayer) {
        UE_LOG(LogAtlEvtEventManager, Error, TEXT("Sequence Player is null! Cannot control sequencer!"));
        return;
    }
    CurrentBmdPage = CurrentEvtDialoguePayload.MessagePageID;
    if (CurrentEvtDialoguePayload.bPauseSequencer) {
        LevelSequenceActor->SequencePlayer->Pause();
    }

    FString TargetMessageName = BmdDialogMessage::GetMessageName(Payload.MessageMajorID, Payload.MessageMinorID, Payload.MessageSubID);
    if (!CurrentBmdDialog || CurrentBmdDialog->Get().Name != TargetMessageName) {
        CurrentBmdDialog = CurrentBmdData.Dialogs.Find(TargetMessageName);
        // Backup - this may be a mind message box, so check for that too
        if (!CurrentBmdDialog) {
            CurrentBmdDialog = CurrentBmdData.Dialogs.Find(BmdDialogMessage::GetMessageNameMind(Payload.MessageMajorID, Payload.MessageMinorID, Payload.MessageSubID));
        }
    }
    // Tried to look for the target MSG/SEL entry, but it's missing
    if (!CurrentBmdDialog) {
        UE_LOG(LogAtlEvtEventManager, Error, TEXT("Dialog Entry %s is missing from BMD!!"), *TargetMessageName);
        return;
    }

    MessageState = EEventManagerMessageState::RunningMessage;
    ExecuteBmdMessage(Payload.BmdAsset, Payload.MessageMajorID, Payload.MessageMinorID, Payload.MessageSubID,
        CurrentBmdPage, Payload.bMessageRefAffected, Payload.SeqEventMessageID);

    /*

    if (Payload.bWithSelect) {
        MessageState = EEventManagerMessageState::RunningMessage;
        ExecuteBmdMessageWithSelect(Payload.BmdAsset, Payload.MessageMajorID, Payload.MessageMinorID, Payload.MessageSubID, CurrentBmdPage, Payload.SelectMessageMajorID,
            Payload.SelectMessageMinorID, Payload.SelectMessageSubID, Payload.SelectResponceToLocalDataID, Payload.bMessageRefAffected, Payload.SeqEventMessageID);
    }
    else {
        MessageState = EEventManagerMessageState::RunningMessage;
        ExecuteBmdMessage(Payload.BmdAsset, Payload.MessageMajorID, Payload.MessageMinorID, Payload.MessageSubID, 
            CurrentBmdPage, Payload.bMessageRefAffected, Payload.SeqEventMessageID);
    }
    */
}

void AAtlEvtEventManager::BmdTryNextPage(const UObject* WorldContextObject) {
    AAtlEvtLevelSequenceActor* LevelSequenceActor = GetAtlEvtLevelSequenceActor(WorldContextObject);
    if (CurrentBmdDialog->Get().Pages.Num() <= CurrentBmdPage + 1) {
        if (CurrentEvtDialoguePayload.bWithSelect) {
            MessageState = EEventManagerMessageState::RunningSelect;
            ExecuteBmdMessageWithSelect(CurrentEvtDialoguePayload.BmdAsset, CurrentEvtDialoguePayload.MessageMajorID, CurrentEvtDialoguePayload.MessageMinorID, CurrentEvtDialoguePayload.MessageSubID, CurrentBmdPage, CurrentEvtDialoguePayload.SelectMessageMajorID,
                CurrentEvtDialoguePayload.SelectMessageMinorID, CurrentEvtDialoguePayload.SelectMessageSubID, CurrentEvtDialoguePayload.SelectResponceToLocalDataID, CurrentEvtDialoguePayload.bMessageRefAffected, CurrentEvtDialoguePayload.SeqEventMessageID);
            return;
        }
        else {
            ReceiveDrawMessage(TEXT(""), TEXT(""));
            ReceiveClearMessageBox();
            ReceiveUpdateMsgDebug(TEXT(""), false);
            ReceiveClearBustup();
            if (LevelSequenceActor->SequencePlayer->IsPaused()) {
                LevelSequenceActor->SequencePlayer->Play();
            }
            MessageState = EEventManagerMessageState::EndMessage;
            return;
        }
    }
    CurrentBmdPage++;
    MessageState = EEventManagerMessageState::RunningMessage;
    ExecuteBmdMessage(CurrentEvtDialoguePayload.BmdAsset, CurrentEvtDialoguePayload.MessageMajorID, CurrentEvtDialoguePayload.MessageMinorID, CurrentEvtDialoguePayload.MessageSubID,
        CurrentBmdPage, CurrentEvtDialoguePayload.bMessageRefAffected, CurrentEvtDialoguePayload.SeqEventMessageID);
}

void AAtlEvtEventManager::BmdExecuteSelection(const UObject* WorldContextObject, int32 SelectId) {
    AAtlEvtLevelSequenceActor* LevelSequenceActor = GetAtlEvtLevelSequenceActor(WorldContextObject);
    ReceiveDrawMessage(TEXT(""), TEXT(""));
    ReceiveClearMessageBox();
    ReceiveUpdateMsgDebug(TEXT(""), false);
    ReceiveClearBustup();
    if (LevelSequenceActor->SequencePlayer->IsPaused()) {
        LevelSequenceActor->SequencePlayer->Play();
    }
    MessageState = EEventManagerMessageState::EndMessage;
    return;
}

void AAtlEvtEventManager::CloseMessage() {
}

void AAtlEvtEventManager::BackLogFinishDelegte() {
}

void AAtlEvtEventManager::AtlEvt_ResumeEventSequencer() {
}

AAtlEvtEventManager::AAtlEvtEventManager() {
    this->FieldCameraActor = NULL;
    this->MovieSceneCameraActor = NULL;
    this->EventRank = EEventManagerEventRank::EventRankA;
    this->EventSkipWidget = NULL;
    this->mpBmdAsset = NULL;
    this->BmdAssetMsgID = 0;
    this->ExecutingMessageNo = 0;
    this->MessageState = EEventManagerMessageState::Invalid;
    this->ScrActor = NULL;
    this->UIBackLogActor = NULL;
    this->UINetAnswerActor = NULL;
    this->EventSequencePlayer = NULL;
    this->RequestedSeqClosedEventMessageID = 0;
    this->SeqControllerState = EEventManagerSeqControllerState::Idle;
    this->PauseControllerActor = NULL;
    this->MoviePlayManager = NULL;

    this->ActiveLevelSequenceActor = nullptr;
    this->CurrentBmdDialog = nullptr;
    //this->CurrentEvtDialoguePayload = nullptr;
    this->CurrentBmdPage = 0;
}

