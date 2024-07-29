#include "AppActor.h"

EAppPauseObjectFlag AAppActor::GetAppPauseFlags() const {
    return EAppPauseObjectFlag::Unknown;
}

void AAppActor::EndPlay(const TEnumAsByte<EEndPlayReason::Type> EndPlayReason) {
    Super::EndPlay(EndPlayReason);
}

void AAppActor::BeginPlay() {
    Super::BeginPlay();
}

AAppActor::AAppActor() {
    this->AppPauseFlags = EAppPauseObjectFlag::Unknown;
}

