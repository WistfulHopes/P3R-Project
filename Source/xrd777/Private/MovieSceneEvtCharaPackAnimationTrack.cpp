#include "MovieSceneEvtCharaPackAnimationTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaPackAnimationSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaPackAnimationTrack"

UMovieSceneEvtCharaPackAnimationTrack::UMovieSceneEvtCharaPackAnimationTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtCharaPackAnimationTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaPackAnimationTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaPackAnimationTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaPackAnimationTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaPackAnimationTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaPackAnimationSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaPackAnimationTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaPackAnimationSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaPackAnimationTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaPackAnimationTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaPackAnimationTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Pack Anim");
}
#endif

#undef LOCTEXT_NAMESPACE