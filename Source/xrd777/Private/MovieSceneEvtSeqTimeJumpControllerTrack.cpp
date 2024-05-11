#include "MovieSceneEvtSeqTimeJumpControllerTrack.h"
#include <xrd777/Public/MovieSceneEvtSeqTimeJumpControllerSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtSeqControllerTrack"

UMovieSceneEvtSeqTimeJumpControllerTrack::UMovieSceneEvtSeqTimeJumpControllerTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtSeqTimeJumpControllerTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtSeqTimeJumpControllerTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtSeqTimeJumpControllerTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtSeqTimeJumpControllerTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtSeqTimeJumpControllerTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtSeqTimeJumpControllerSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtSeqTimeJumpControllerTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtSeqTimeJumpControllerSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtSeqTimeJumpControllerTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtSeqTimeJumpControllerTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtSeqTimeJumpControllerTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Time Jump Controller");
}
#endif

#undef LOCTEXT_NAMESPACE