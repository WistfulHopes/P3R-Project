// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "BfAssetStyle.h"

TSharedPtr< FSlateStyleSet > FBfAssetStyle::StyleInstance = NULL;

void FBfAssetStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBfAssetStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FBfAssetStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BfAssetPluginStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon64x64(64.0f, 64.0f);

TSharedRef< FSlateStyleSet > FBfAssetStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("BfAssetPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BfAssetPlugin")->GetBaseDir() / TEXT("Resources"));
	Style->Set("ClassIcon.BfAsset", new IMAGE_BRUSH(TEXT("ButtonIcon_40x"), Icon16x16));
	Style->Set("ClassThumbnail.BfAsset", new IMAGE_BRUSH(TEXT("Icon128"), Icon64x64));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FBfAssetStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBfAssetStyle::Get()
{
	return *StyleInstance;
}

#endif