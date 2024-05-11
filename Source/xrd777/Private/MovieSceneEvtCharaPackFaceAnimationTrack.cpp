#include "MovieSceneEvtCharaPackFaceAnimationTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaPackFaceAnimationSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaPackFaceAnimationTrack"

UMovieSceneEvtCharaPackFaceAnimationTrack::UMovieSceneEvtCharaPackFaceAnimationTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
	EventPosition = EAtlCharaFaceAnimFireEventsAtPosition::AfterSpawn;
}

bool UMovieSceneEvtCharaPackFaceAnimationTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaPackFaceAnimationTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaPackFaceAnimationTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaPackFaceAnimationTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaPackFaceAnimationTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaPackFaceAnimationSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaPackFaceAnimationTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaPackFaceAnimationSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaPackFaceAnimationTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaPackFaceAnimationTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaPackFaceAnimationTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Pack Face Anim");
}
#endif

#undef LOCTEXT_NAMESPACE

