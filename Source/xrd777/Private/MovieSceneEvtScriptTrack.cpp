#include "MovieSceneEvtScriptTrack.h"
#include <xrd777/Public/MovieSceneEvtScriptSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtScriptTrack"

UMovieSceneEvtScriptTrack::UMovieSceneEvtScriptTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtScriptTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtScriptTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtScriptTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtScriptTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtScriptTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtScriptSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtScriptTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtScriptSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtScriptTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtScriptTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtScriptTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Script");
}
#endif

#undef LOCTEXT_NAMESPACE