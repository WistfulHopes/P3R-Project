#pragma once
#include "CharacterBaseCore.h"
#include "Engine/Classes/Components/CapsuleComponent.h"

void ACharacterBaseCore::ReCalculateBounds() {
    // 0x1482bf8d0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (GetMesh() && GetMesh()->SkeletalMesh) {
        USkeletalMesh* SkelMesh = GetMesh()->SkeletalMesh;
        FBoxSphereBounds ImportedBounds = SkelMesh->GetImportedBounds();
        FVector CapsuleSize = GetCapsuleComponent()->GetComponentToWorld().GetScale3D();
        CapsuleSize.Z = GetMesh()->GetRelativeLocation().Z;
        float BoxSize = ((ImportedBounds.BoxExtent.Z + ImportedBounds.Origin.Z) -
            (ImportedBounds.Origin.Z - ImportedBounds.BoxExtent.Z)) * 0.5;
        if (BoxSize > static_cast<float>(0x34000000)) {
            FVector ExtendBounds = FVector();
            ExtendBounds.Z = GetCapsuleComponent()->GetComponentToWorld().GetScale3D().Z *
                GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() / BoxSize;
            GetMesh()->BoundsScale = ExtendBounds.Z;
            ExtendBounds.Z = (GetMesh()->GetRelativeLocation().Z + ImportedBounds.Origin.Z) / ExtendBounds.Z;
            SkelMesh->SetPositiveBoundsExtension(ExtendBounds);
            SkelMesh->SetNegativeBoundsExtension(ExtendBounds);
            LoadEndEvent();
        }
    }
}


FName ACharacterBaseCore::GetMontageSectionName(UAnimMontage* Montage, int32 Index) {
    // 0x142e65ed0 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (Montage->CompositeSections.IsValidIndex(Index)) {
        return Montage->CompositeSections[Index].SectionName;
    }
    return NAME_None;
}

float ACharacterBaseCore::GetLastRenderTimeOnScreen() {
    return GetMesh()->GetLastRenderTimeOnScreen();
}

float ACharacterBaseCore::GetCompLastRenderTimeOnScreen(UPrimitiveComponent* MeshComp) {
    return MeshComp->GetLastRenderTimeOnScreen();
}

ACharacterBaseCore::ACharacterBaseCore() {
    this->_SkeletalMeshLoader = NULL;
    this->_AnimBpLoader = NULL;
    this->_RecalcBounds = true;
    this->_AutoLoading = true;
    this->_MeshPackAsset = NULL;
    this->_PreviewMeshNo = 0;
    this->_PreviewCostumeNo = 0;
    this->_PreviewHairNo = 0;
    this->_PreviewFaceNo = 0;
    this->_AnimPackAsset = NULL;
    this->_PreviewMeshAnimNo = 0;
    this->_PreviewCostumeAnimNo = 0;
    this->_PreviewHairAnimNo = 0;
}

