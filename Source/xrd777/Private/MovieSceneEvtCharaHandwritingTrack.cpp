#include "MovieSceneEvtCharaHandwritingTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaHandwritingSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaHandwritingTrack"

UMovieSceneEvtCharaHandwritingTrack::UMovieSceneEvtCharaHandwritingTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtCharaHandwritingTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaHandwritingTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaHandwritingTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaHandwritingTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaHandwritingTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaHandwritingSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaHandwritingTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaHandwritingSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaHandwritingTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaHandwritingTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaHandwritingTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Handwriting");
}
#endif

#undef LOCTEXT_NAMESPACE