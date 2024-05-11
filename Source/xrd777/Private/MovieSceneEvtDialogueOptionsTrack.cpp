#include "MovieSceneEvtDialogueOptionsTrack.h"
#include <xrd777/Public/MovieSceneEvtDialogueOptionsSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtDialogueOptionsTrack"

UMovieSceneEvtDialogueOptionsTrack::UMovieSceneEvtDialogueOptionsTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
	EventPosition = EFireEventsAtPositionggg::AfterSpawn; // i had a stroke
}

bool UMovieSceneEvtDialogueOptionsTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtDialogueOptionsTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtDialogueOptionsTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtDialogueOptionsTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtDialogueOptionsTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtDialogueOptionsSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtDialogueOptionsTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtDialogueOptionsSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtDialogueOptionsTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtDialogueOptionsTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtDialogueOptionsTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Dialog Option");
}
#endif

#undef LOCTEXT_NAMESPACE

