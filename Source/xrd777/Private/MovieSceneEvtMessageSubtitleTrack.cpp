#include "MovieSceneEvtMessageSubtitleTrack.h"
#include <xrd777/Public/MovieSceneEvtMessageSubtitleSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtSeqControllerTrack"

UMovieSceneEvtMessageSubtitleTrack::UMovieSceneEvtMessageSubtitleTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtMessageSubtitleTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtMessageSubtitleTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtMessageSubtitleTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtMessageSubtitleTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtMessageSubtitleTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtMessageSubtitleSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtMessageSubtitleTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtMessageSubtitleSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtMessageSubtitleTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtMessageSubtitleTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtMessageSubtitleTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Msg Subtitle");
}
#endif

#undef LOCTEXT_NAMESPACE