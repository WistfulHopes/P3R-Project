#include "MovieSceneEvtDialogueTrack.h"
#include <xrd777/Public/MovieSceneEvtDialogueSection.h>
#include <xrd777/Public/MovieSceneEvtDialogueSectionTemplate.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtDialogueTrack"

UMovieSceneEvtDialogueTrack::UMovieSceneEvtDialogueTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtDialogueTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtDialogueTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtDialogueTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtDialogueTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtDialogueTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtDialogueSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtDialogueTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtDialogueSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtDialogueTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtDialogueTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtDialogueTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtDialogueSectionTemplate(*CastChecked<UMovieSceneEvtDialogueSection>(&InSection));
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtDialogueTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Dialog");
}
#endif

#undef LOCTEXT_NAMESPACE

