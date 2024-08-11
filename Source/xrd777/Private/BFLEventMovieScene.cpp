#include "BFLEventMovieScene.h"

DEFINE_LOG_CATEGORY_STATIC(BlueprintLibEventMovieScene, Log, All);

void UBFLEventMovieScene::StopSlotAnimation(UAnimInstance* AnimInstance, float BlendOutTime, FName SlotNodeName) {
    // 0x14acfe5a0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (!AnimInstance) {
        return;
    }
    if (SlotNodeName == NAME_None) {
        AnimInstance->Montage_Stop(BlendOutTime, nullptr);
        return;
    }
    for (FAnimMontageInstance*& MontageInst : AnimInstance->MontageInstances) {
        if (MontageInst->Montage) {
            if (MontageInst->GetDesiredWeight() == 0.0f || !MontageInst->IsPlaying()) {
                for (FSlotAnimationTrack& SlotTrack : MontageInst->Montage->SlotAnimTracks) {
                    if (SlotTrack.SlotName == SlotNodeName) {
                        // Stop multi montages nested in notifies
                        for (FAnimNotifyEvent& Notify : MontageInst->Montage->Notifies) {
                            if (Notify.Notify->IsA<UAnimNotify_PlayEvtMultiMontage>()) {
                                Cast<UAnimNotify_PlayEvtMultiMontage>(Notify.Notify)->bStop = 1;
                                FAlphaBlend StopBlend = FAlphaBlend(BlendOutTime);
                                MontageInst->Stop(StopBlend, true);
                            }
                        }
                        // Stop root montage anim
                        FAlphaBlend StopBlend = FAlphaBlend(BlendOutTime);
                        MontageInst->Stop(StopBlend, true);
                    }
                }
            }
        }
    }
}

USkeletalMeshComponent* UBFLEventMovieScene::SkeletalMeshComponentFromObject(UObject* InObject) {
    // 0x1410c6f40 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (InObject->IsA<USkeletalMeshComponent>()) {
        return Cast<USkeletalMeshComponent>(InObject);
    }
    else if (InObject->IsA<ACharacter>()) {
        return Cast<ACharacter>(InObject)->GetMesh();
    }
    else if (InObject->IsA<AActor>()) {
        return Cast<USkeletalMeshComponent>(Cast<AActor>(InObject)->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
    }
    return nullptr;
}

void UBFLEventMovieScene::SetNearClipPlane(const UObject* WorldContextObject, float NearClipCm) {
    // 0x1410c6d50 (PERSONA3 RELOAD 1.0.0.0 Win64)
    GNearClippingPlane = NearClipCm;
}

void UBFLEventMovieScene::SetEnableStreamingTexture(const UObject* WorldContextObject, bool bEnable) {
}

void UBFLEventMovieScene::ResetNearClipPlane(const UObject* WorldContextObject) {
    // 0x14acf8060 (PERSONA3 RELOAD 1.0.0.0 Win64)
    GNearClippingPlane = GEngine->NearClipPlane;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotOffsetAnimationAsDynamicMontageLoop(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* Asset, FName SlotNodeName, float StartOffsetTime, float EndOffsetTime, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    return NULL;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotMultiAnimationOffsetAsDynamicMontageTwo(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* BaseAnimAsset, UAnimSequenceBase* LoopAsset, FName SlotNodeName, float StartOffsetTime, float EndOffsetTime, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    // 0x1410c3740 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (CheckMeshAndAnimSkeletonsAreEqual(Mesh, BaseAnimAsset)) {
        UAnimMontage* NewMontage = CreateSlotOffsetAnimationAsDynamicMontage(Mesh, BaseAnimAsset, SlotNodeName, StartOffsetTime, EndOffsetTime, BlendInTime, BlendOutTime, InPlayRate, LoopCount, BlendOutTriggerTime, InTimeToStartMontageAt);
        if (NewMontage) {
            // Slot names
            FName MontageDefaultSlot = FName("Default");
            FName MontageLoopSlot = FName("Loop");

            // edit the anim track name + length
            FSlotAnimationTrack& FirstSlot = NewMontage->SlotAnimTracks[0];
            FirstSlot.SlotName = SlotNodeName;
            float LooperRateScale = (LoopAsset->RateScale > 0.000001f) ? LoopAsset->RateScale : 1.0f;
            float FullSequenceLength = NewMontage->SequenceLength;
            NewMontage->SequenceLength = ((float)LoopCount * LoopAsset->SequenceLength) / LooperRateScale;
            
            // new anim segment
            FAnimSegment& NewSegment = FirstSlot.AnimTrack.AnimSegments.AddDefaulted_GetRef();
            NewSegment.AnimReference = LoopAsset;
            NewSegment.StartPos = FullSequenceLength;
            NewSegment.AnimEndTime = LoopAsset->SequenceLength;
            NewSegment.LoopingCount = LoopCount;

            // new linkable element
            FCompositeSection& NewSection = NewMontage->CompositeSections.AddDefaulted_GetRef();
            NewSection.SectionName = MontageLoopSlot;
            NewSection.LinkMontage(NewMontage, FullSequenceLength);

            AnimInstance->Montage_Play(NewMontage, InPlayRate, EMontagePlayReturnType::MontageLength, InTimeToStartMontageAt, true);
            AnimInstance->Montage_SetNextSection(MontageDefaultSlot, MontageLoopSlot, NewMontage);
            AnimInstance->Montage_SetNextSection(MontageLoopSlot, MontageLoopSlot, NewMontage);
        }
        return NewMontage;
    }
    return nullptr;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotMultiAnimationOffsetAsDynamicMontage(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* BaseAnimAsset, TArray<FAtlSlotMultiAnimationParam>& AnimAssets, FName SlotNodeName, EEvtCharaAnimationType EvtCharaAnimationType, float StartOffsetTime, float EndOffsetTime, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    return NULL;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotMultiAnimationAsDynamicMontage(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* BaseAnimAsset, TArray<FAtlSlotMultiAnimationParam>& AnimAssets, FName SlotNodeName, EEvtCharaAnimationType EvtCharaAnimationType, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    // 0x1410c2ed0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (CheckMeshAndAnimSkeletonsAreEqual(Mesh, BaseAnimAsset)) {
        UAnimMontage* NewMontage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(BaseAnimAsset, SlotNodeName, BlendInTime, BlendOutTime, InPlayRate, LoopCount, BlendOutTriggerTime, InTimeToStartMontageAt);
        if (NewMontage) {
            // Slot names
            FName MontageDefaultSlot = FName("Default");
            FName MontageLoopSlot = FName("Loop");

            // Edit anim track
            FSlotAnimationTrack& FirstTrack = NewMontage->SlotAnimTracks[0];
            FirstTrack.SlotName = SlotNodeName;
            NewMontage->SequenceLength += 0.001f;
            // Add new anim segment
            FAnimSegment& NewSegment = FirstTrack.AnimTrack.AnimSegments.AddDefaulted_GetRef();
            NewSegment.AnimReference = BaseAnimAsset;
            NewSegment.StartPos = BaseAnimAsset->SequenceLength;
            NewSegment.AnimStartTime = BaseAnimAsset->SequenceLength - 0.001f;
            NewSegment.AnimEndTime = BaseAnimAsset->SequenceLength;
            NewSegment.AnimPlayRate = 1.0f;
            NewSegment.LoopingCount = LoopCount;

            // Link segment
            FCompositeSection& NewElement = NewMontage->CompositeSections.AddDefaulted_GetRef();
            NewElement.LinkMontage(NewMontage, BaseAnimAsset->SequenceLength);
            NewElement.SectionName = MontageLoopSlot;

            // Setup multi anims
            if (AnimAssets.Num() > 0) {
                AddPlayEvtMultiMontageAnimNotify(0, NewMontage, AnimAssets, SlotNodeName, EvtCharaAnimationType, BlendOutTime, AnimAssets[0].BlendIn);
            }
            // Setup montage first anim + loop anim
            AnimInstance->Montage_Play(NewMontage, InPlayRate, EMontagePlayReturnType::MontageLength, InTimeToStartMontageAt, true);
            AnimInstance->Montage_SetNextSection(MontageDefaultSlot, MontageLoopSlot, NewMontage);
            AnimInstance->Montage_SetNextSection(MontageLoopSlot, MontageLoopSlot, NewMontage);
        }
    }
    return NULL;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotAnimationAsDynamicMontageTwo(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* Asset, UAnimSequenceBase* Asset2, FName SlotNodeName, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    return NULL;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotAnimationAsDynamicMontageLoopSecOnLastFrame(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* Asset, FName SlotNodeName, float StartOffsetTime, float EndOffsetTime, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    // 0x1410c2730 (PERSONA3 RELOAD 1.0.0.0 Win64)
    UAnimMontage* NewMontage = nullptr;
    if (CheckMeshAndAnimSkeletonsAreEqual(Mesh, Asset)) {
        NewMontage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(Asset, SlotNodeName, BlendInTime, BlendOutTime, InPlayRate, LoopCount, BlendOutTriggerTime, InTimeToStartMontageAt);
    }
    if (NewMontage) {
        if (EndOffsetTime < 0.0) {
            EndOffsetTime = 0.0;
        }
        if (StartOffsetTime < 0.0) {
            StartOffsetTime = 0.0;
        }

        // Slot names
        FName MontageDefaultSlot = FName("Default");
        FName MontageLoopSlot = FName("Loop");

        // Edit first animation segment in track 0
        FSlotAnimationTrack& TargetAnimTrack = NewMontage->SlotAnimTracks[0];
        FAnimSegment& FirstAnimSegment = TargetAnimTrack.AnimTrack.AnimSegments[0];
        FirstAnimSegment.AnimStartTime = StartOffsetTime;
        FirstAnimSegment.AnimEndTime = Asset->SequenceLength - EndOffsetTime;
        NewMontage->SequenceLength = NewMontage->SequenceLength - (StartOffsetTime + EndOffsetTime) + 0.001;
        TargetAnimTrack.SlotName = SlotNodeName;

        // Add new loop segment
        FAnimSegment& LoopSegment = TargetAnimTrack.AnimTrack.AnimSegments.AddDefaulted_GetRef();
        LoopSegment.AnimReference = Asset;
        LoopSegment.StartPos = NewMontage->SequenceLength;
        LoopSegment.AnimStartTime = FirstAnimSegment.AnimEndTime - 0.001;
        LoopSegment.AnimEndTime = NewMontage->SequenceLength;
        LoopSegment.LoopingCount = LoopCount;

        // Link to montage
        FCompositeSection& NewElement = NewMontage->CompositeSections.AddDefaulted_GetRef();
        NewElement.LinkMontage(NewMontage, Asset->SequenceLength);
        NewElement.SectionName = MontageLoopSlot;
        
        // Setup montage first anim + loop anim
        AnimInstance->Montage_Play(NewMontage, InPlayRate, EMontagePlayReturnType::MontageLength, InTimeToStartMontageAt, true);
        AnimInstance->Montage_SetNextSection(MontageDefaultSlot, MontageLoopSlot, NewMontage);
        AnimInstance->Montage_SetNextSection(MontageLoopSlot, MontageLoopSlot, NewMontage);
    }
    return NULL;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotAnimationAsDynamicMontageLoopOnLastFrame(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* Asset, FName SlotNodeName, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    return NULL;
}

UAnimMontage* UBFLEventMovieScene::PlaySlotAnimationAsDynamicMontageLoop(UAnimInstance* AnimInstance, USkeletalMesh* Mesh, UAnimSequenceBase* Asset, FName SlotNodeName, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    return NULL;
}

FName UBFLEventMovieScene::MakeSeasonSublevel(int32 FieldMajorID, int32 FieldMinorID, ECldSeason Season, bool bStreamingPath) {
    // 0x1410c1a10 (PERSONA3 RELOAD 1.0.0.0 Win64)
    FName LevelName = NAME_None;
    switch (Season) {
        case ECldSeason::Spring:
            LevelName = FName(FString::Printf(TEXT("/Game/Xrd777/Maps/Field/F%03d/BG/LV_F%03d_%03d_BG_Spring"), FieldMajorID, FieldMajorID, FieldMinorID));
            break;
        case ECldSeason::Summer:
            LevelName = FName(FString::Printf(TEXT("/Game/Xrd777/Maps/Field/F%03d/BG/LV_F%03d_%03d_BG_Summer"), FieldMajorID, FieldMajorID, FieldMinorID));
            break;
        case ECldSeason::Autumn:
            LevelName = FName(FString::Printf(TEXT("/Game/Xrd777/Maps/Field/F%03d/BG/LV_F%03d_%03d_BG_Autumn"), FieldMajorID, FieldMajorID, FieldMinorID));
            break;
        case ECldSeason::Winter:
            LevelName = FName(FString::Printf(TEXT("/Game/Xrd777/Maps/Field/F%03d/BG/LV_F%03d_%03d_BG_Winter"), FieldMajorID, FieldMajorID, FieldMinorID));
            break;
    }
    if (bStreamingPath) {
        LevelName = FName(LevelName.ToString() + "." + FPaths::GetBaseFilename(LevelName.ToString()));
    }
    return LevelName;
}

void UBFLEventMovieScene::LoadSublevel(const FString& SublevelName) {
}

bool UBFLEventMovieScene::IsCondition(EEvtConditionalBranchCompType CompareType, int32 LHS, int32 RHS) {
    // 0x1410c1720 (PERSONA3 RELOAD 1.0.0.0 Win64)
    switch (CompareType) {
    case EEvtConditionalBranchCompType::Equal:
        if (LHS == RHS) {
            return true;
        }
        break;
    case EEvtConditionalBranchCompType::Not:
        if (LHS != RHS) {
            return true;
        }
        break;
    case EEvtConditionalBranchCompType::LessThan:
        if (LHS < RHS) {
            return true;
        }
        break;
    case EEvtConditionalBranchCompType::GreaterThan:
        if (RHS < LHS) {
            return true;
        }
        break;
    case EEvtConditionalBranchCompType::Less:
        if (LHS <= RHS) {
            return true;
        }
        break;
    case EEvtConditionalBranchCompType::Greater:
        if (RHS <= LHS) {
            return true;
        }
    }
    return false;
}

FMovieSceneObjectBindingID UBFLEventMovieScene::GetBindingID(ALevelSequenceActor* SequenceActor, const FString& ObjectDisplayName) {
    // 0x1410c0f70 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (SequenceActor) {
        ULevelSequence* LevelSequence = SequenceActor->GetSequence();
        if (LevelSequence && !ObjectDisplayName.IsEmpty()) {
            UMovieScene* MovieScene = LevelSequence->GetMovieScene();
            if (MovieScene) {
                if (MovieScene->HasAnyFlags(EObjectFlags::RF_NeedLoad)) {
                    MovieScene->GetLinker()->Preload(MovieScene);
                }
                for (int i = 0; i < MovieScene->GetSpawnableCount(); i++) {
                    FMovieSceneSpawnable& CurrSpawnable = MovieScene->GetSpawnable(i);
                    if (CurrSpawnable.GetName() == ObjectDisplayName) {
                        return FMovieSceneObjectBindingID(CurrSpawnable.GetGuid());
                    }
                }
                for (int i = 0; i < MovieScene->GetPossessableCount(); i++) {
                    FMovieScenePossessable& CurrPossess = MovieScene->GetPossessable(i);
                    if (CurrPossess.GetName() == ObjectDisplayName) {
                        return FMovieSceneObjectBindingID(CurrPossess.GetGuid());
                    }
                }
            }
        }
    }
    return FMovieSceneObjectBindingID{};
}

FName UBFLEventMovieScene::GetAnimationSlotName(EEvtCharaAnimationSlotType SlotType) {
    // 0x1410c0eb0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    switch (SlotType) {
        case EEvtCharaAnimationSlotType::EventSlot:
            return FName("DefaultSlot");
        case EEvtCharaAnimationSlotType::NodSlot:
            return FName("NodSlot");
        case EEvtCharaAnimationSlotType::FacialSlot:
            return FName("FacialSlot");
        case EEvtCharaAnimationSlotType::ArmL:
            return FName("Arm L");
        case EEvtCharaAnimationSlotType::ArmR:
            return FName("Arm R");
        default:
            return FName("DefaultSlot");
    }
}

ALevelSequenceActor* UBFLEventMovieScene::FindLevelSequenceActor(ULevelStreaming* TargetLevelStreaming) {
    // 0x14acee290 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (ULevel* LoadedLevel = TargetLevelStreaming->GetLoadedLevel()) {
        for (AActor*& LevelActor : LoadedLevel->Actors) {
            if (LevelActor->GetClass() == ALevelSequenceActor::StaticClass()) {
                return Cast<ALevelSequenceActor>(LevelActor);
            }
        }
    }
    return nullptr;
}

AAtlEvtEventManager* UBFLEventMovieScene::FindAtlEvtEventManager(ULevelStreaming* TargetLevelStreaming) {
    // 0x14acec2e0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (ULevel* LoadedLevel = TargetLevelStreaming->GetLoadedLevel()) {
        for (AActor*& LevelActor : LoadedLevel->Actors) {
            if (LevelActor->GetClass() == AAtlEvtEventManager::StaticClass()) {
                return Cast<AAtlEvtEventManager>(LevelActor);
            }
        }
    }
    return nullptr;
}

UAnimMontage* UBFLEventMovieScene::CreateSlotOffsetAnimationAsDynamicMontage(USkeletalMesh* Mesh, UAnimSequenceBase* Asset, FName SlotNodeName, float StartOffsetTime, float EndOffsetTime, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    // 0x1410b38a0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (CheckMeshAndAnimSkeletonsAreEqual(Mesh, Asset)) {
        return UAnimMontage::CreateSlotAnimationAsDynamicMontage(Asset, SlotNodeName, BlendInTime, BlendOutTime, InPlayRate, LoopCount, BlendOutTriggerTime, InTimeToStartMontageAt);
    }
    return nullptr;
}

UAnimMontage* UBFLEventMovieScene::CreateSlotAnimationAsDynamicMontage(USkeletalMesh* Mesh, UAnimSequenceBase* Asset, FName SlotNodeName, float BlendInTime, float BlendOutTime, float InPlayRate, int32 LoopCount, float BlendOutTriggerTime, float InTimeToStartMontageAt) {
    // 0x1410b3820 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (CheckMeshAndAnimSkeletonsAreEqual(Mesh, Asset)) {
        //Asset->SequenceLength -= (BlendInTime + BlendOutTime);
        return UAnimMontage::CreateSlotAnimationAsDynamicMontage(Asset, SlotNodeName, BlendInTime, BlendOutTime, InPlayRate, LoopCount, BlendOutTriggerTime, InTimeToStartMontageAt);
    }
    return nullptr;
}

bool UBFLEventMovieScene::CheckMeshAndAnimSkeletonsAreEqual(USkeletalMesh* Mesh, UAnimSequenceBase* Asset) {
    return Mesh && Mesh->GetSkeleton() && Asset && Asset->GetSkeleton() && Mesh->GetSkeleton() == Asset->GetSkeleton();
}

int32 UBFLEventMovieScene::AllActorBinding(AActor* BindingActor, const FString& TargetName) {
    // 0x1410b2820 (PERSONA3 RELOAD 1.0.0.0 Win64)
    return 0;
}

void UBFLEventMovieScene::AddViewSlaveLocation(const FVector& Location, float BoostFactor, bool bOverrideLocation, float Duration) {
    // 0x1410b27c0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    IStreamingManager::Get().AddViewSlaveLocation(Location, BoostFactor, bOverrideLocation, Duration);
}

UAnimMontage* UBFLEventMovieScene::AddPlayEvtMultiMontageAnimNotify(int32 Index, UAnimMontage* NewMontage, const TArray<FAtlSlotMultiAnimationParam>& AnimAssets, FName SlotNodeName, EEvtCharaAnimationType EvtCharaAnimationType, float CurrentMontageBlendOut, float NextMontageBlendIn) {
    // 0x1410b23c0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (!NewMontage) {
        return nullptr;
    }
    FName EvtMontageName = FName(FString::Printf(TEXT("EvtAN_Montage_%d"), Index));
    UE_LOG(BlueprintLibEventMovieScene, Display, TEXT("%s"), *EvtMontageName.ToString());
    /*
    // Make new notify event
    // UAnimationBlueprintLibrary::AddAnimationNotifyStateEvent
    FAnimNotifyEvent& NewNotify = NewMontage->Notifies.AddDefaulted_GetRef();
    NewNotify.NotifyName = EvtMontageName;
    NewNotify.LinkMontage(NewMontage, NewMontage->SequenceLength, 0);
    NewNotify.TriggerTimeOffset = GetTriggerTimeOffsetForType(EAnimEventTriggerOffsets::OffsetBefore);
    NewNotify.TrackIndex = 0;
    // Create evt multi montage notifier
    UAnimNotify_PlayEvtMultiMontage* AnimNotify = NewObject<UAnimNotify_PlayEvtMultiMontage>(NewMontage);
    AnimNotify->MontageArray = AnimAssets;
    AnimNotify->SlotNodeName = SlotNodeName;
    AnimNotify->AnimationType = EvtCharaAnimationType;
    AnimNotify->bStop = false;
    NewNotify.Notify = AnimNotify;
    */
    return NewMontage;
}

UBFLEventMovieScene::UBFLEventMovieScene() {
}

