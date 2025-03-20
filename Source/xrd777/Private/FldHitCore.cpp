#include "FldHitCore.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

void AFldHitCore::RequestKeyPushBluePrint() {
}

void AFldHitCore::OnActorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void AFldHitCore::OnActorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void AFldHitCore::CleanupRequest() {
}

AFldHitCore::AFldHitCore() {
    this->mPriority_ = 0;
    this->RootComp_ = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    this->SetRootComponent(this->RootComp_);
    this->HitComp_ = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit"));
    this->HitComp_->AttachTo(this->RootComp_);
#if WITH_EDITORONLY_DATA
    UArrowComponent* DebugArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Dir"));
    DebugArrow->ArrowColor = FColor(0xDD, 0x00, 0xE0);
    DebugArrow->ArrowSize = 2.0f;
    DebugArrow->SetRelativeRotation(FRotator(0, -90.0f, 0));
	this->DirDebugComp_ = DebugArrow;
    this->DirDebugComp_->AttachTo(this->RootComp_);
#endif
    this->mOverlapBluePrint_ = NULL;
    this->mOverlapKeyLock_ = false;
    this->mKeyPushBluePrint_ = NULL;
    this->mActionKeyLock_ = true;
    this->mHeroDirectType_ = FFldHitCoreHeroDirectType::None;
    this->mCheckIcon_ = EFldHitCoreCheckIconType::Check;
}

