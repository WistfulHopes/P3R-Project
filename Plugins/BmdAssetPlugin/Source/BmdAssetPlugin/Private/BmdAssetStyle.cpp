// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "BmdAssetStyle.h"

TSharedPtr< FSlateStyleSet > FBmdAssetStyle::StyleInstance = NULL;

void FBmdAssetStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBmdAssetStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FBmdAssetStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BmdAssetPluginStyle"));
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

TSharedRef< FSlateStyleSet > FBmdAssetStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("BmdAssetPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BmdAssetPlugin")->GetBaseDir() / TEXT("Resources"));
	Style->Set("ClassIcon.BmdAsset", new IMAGE_BRUSH(TEXT("ButtonIcon_40x"), Icon16x16));
	Style->Set("ClassThumbnail.BmdAsset", new IMAGE_BRUSH(TEXT("Icon128"), Icon64x64));

	const FTextBlockStyle NormalText = FTextBlockStyle()
		.SetFont(DEFAULT_FONT("Regular", 9))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor(FLinearColor(0.02f, 0.3f, 0.0f))
		.SetHighlightShape(BOX_BRUSH("Common/TextBlockHighlightShape", FMargin(3.f / 8.f)));

	Style->Set("BmdText.Style", NormalText);
	Style->Set("BmdText.DialogName", FTextBlockStyle(NormalText).SetFont(DEFAULT_FONT("Bold", 16)));
	Style->Set("BmdText.Bold", FTextBlockStyle(NormalText).SetFont(DEFAULT_FONT("Bold", 9)));
	Style->Set("BmdText.SpeakerName", FTextBlockStyle(NormalText).SetFont(DEFAULT_FONT("Italic", 9)));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FBmdAssetStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBmdAssetStyle::Get()
{
	return *StyleInstance;
}

#endif