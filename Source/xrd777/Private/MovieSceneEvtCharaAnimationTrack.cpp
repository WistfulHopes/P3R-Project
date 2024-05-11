#include "MovieSceneEvtCharaAnimationTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaAnimationSection.h>
#include <xrd777/Public/MovieSceneEvtCharaAnimationSectionTemplate.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaAnimationTrack"

UMovieSceneEvtCharaAnimationTrack::UMovieSceneEvtCharaAnimationTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
	EventPosition = EAtlCharaAnimFireEventsAtPosition::AfterSpawn;
}

bool UMovieSceneEvtCharaAnimationTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaAnimationTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaAnimationTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaAnimationTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaAnimationTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaAnimationSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaAnimationTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaAnimationSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaAnimationTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaAnimationTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtCharaAnimationTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtCharaAnimationSectionTemplate(*CastChecked<UMovieSceneEvtCharaAnimationSection>(&InSection));
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaAnimationTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Anim");
}
#endif

#undef LOCTEXT_NAMESPACE