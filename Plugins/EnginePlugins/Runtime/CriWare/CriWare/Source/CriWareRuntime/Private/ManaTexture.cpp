#include "ManaTexture.h"

void UManaTexture::SetMovieSource(UManaSource* InSource) {
}

class FTextureResource* UManaTexture::CreateResource()
{
	return nullptr;
}

UManaTexture::UManaTexture() {
    this->MovieSource = NULL;
    this->bRenderToTexture = false;
    this->TargetGamma = 0.00f;
    this->bHDR = false;
    this->AddressX = TA_Wrap;
    this->AddressY = TA_Wrap;
    this->bOverrideDimensions = false;
    this->OverrideFormat = PF_Unknown;
    this->ManaPlayer = NULL;
}

