#pragma once
#include "CoreMinimal.h"
#include "MovieSceneObjectBindingID.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "MovieSceneEvtConditionalBranchTrack.h"
#include "Evaluation/MovieSceneEvaluationTrack.h"
#include "MovieSceneEvtSeqControllerTrack.generated.h"

class UMovieSceneSection;

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEvtSeqControllerTrack : public UMovieSceneEvtConditionalBranchTrack, public IMovieSceneTrackTemplateProducer {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    uint8 bFireEventsWhenForwards : 1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    uint8 bFireEventsWhenBackwards : 1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    TArray<FMovieSceneObjectBindingID> EventReceivers;

private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta = (AllowPrivateAccess = true))
    TArray<UMovieSceneSection*> Sections;

public:
    UMovieSceneEvtSeqControllerTrack(const FObjectInitializer& Init);

    // UMovieSceneTrack interface
    virtual bool IsEmpty() const override;
    virtual void AddSection(UMovieSceneSection& Section) override;
    virtual void RemoveSection(UMovieSceneSection& Section) override;
    virtual void RemoveSectionAt(int32 SectionIndex) override;
    virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;
    virtual UMovieSceneSection* CreateNewSection() override;
    virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;
    virtual bool HasSection(const UMovieSceneSection& Section) const override;
    virtual bool SupportsMultipleRows() const override { return true; }
    virtual void PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const override;

    // IMovieSceneTrackTemplateProducer interface
    virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;

#if WITH_EDITORONLY_DATA
    virtual FText GetDefaultDisplayName() const override;
#endif
};

