#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Channels/MovieSceneChannel.h"
#include "EvtSeqControllerPayload.h"
#include <MovieScene/Public/MovieSceneClipboard.h>
#include <MovieScene/Public/Channels/MovieSceneChannelData.h>
#include <MovieScene/Public/Channels/MovieSceneChannelTraits.h>
#include "MovieSceneEvtSeqControllerSectionData.generated.h"

USTRUCT(BlueprintType)
struct XRD777_API FMovieSceneEvtSeqControllerSectionData : public FMovieSceneChannel {
    GENERATED_BODY()
public:
//private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true, KeyTimes))
    TArray<FFrameNumber> Times;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true, KeyValues))
    TArray<FEvtSeqControllerPayload> KeyValues;
private:
	/** This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it doesn't get saved into assets. */
	UPROPERTY(Transient)
	FMovieSceneKeyHandleMap KeyHandles;

public:
	/**
	 * Access a mutable interface for this channel's data
	 *
	 * @return An object that is able to manipulate this channel's data
	 */
	FORCEINLINE TMovieSceneChannelData<FEvtSeqControllerPayload> GetData()
	{
		return TMovieSceneChannelData<FEvtSeqControllerPayload>(&Times, &KeyValues, &KeyHandles);
	}

	/**
	 * Access a constant interface for this channel's data
	 *
	 * @return An object that is able to interrogate this channel's data
	 */
	FORCEINLINE TMovieSceneChannelData<const FEvtSeqControllerPayload> GetData() const
	{
		return TMovieSceneChannelData<const FEvtSeqControllerPayload>(&Times, &KeyValues);
	}

	/**
	 * Check whether this channel has any data
	 */
	FORCEINLINE bool HasAnyData() const
	{
		return Times.Num() != 0;
	}

	bool Evaluate(FFrameTime InTime, FEvtSeqControllerPayload& OutValue) const { return true; }

public:
	// FMovieSceneChannel Interface
	virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;
	virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;
	virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;
	virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;
	virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;
	virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;
	virtual void ChangeFrameResolution(FFrameRate SourceRate, FFrameRate DestinationRate) override;
	virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;
	virtual int32 GetNumKeys() const override;
	virtual void Reset() override;
	virtual void Offset(FFrameNumber DeltaPosition) override;
	virtual void Optimize(const FKeyDataOptimizationParams& InParameters) override {}
	virtual void ClearDefault() override {}

public:
	const TArray<FFrameNumber>& GetTimes() const { return Times; }
	const TArray<FEvtSeqControllerPayload>& GetValues() const { return KeyValues; }
public:
    FMovieSceneEvtSeqControllerSectionData();
};

template<>
struct TMovieSceneChannelTraits<FMovieSceneEvtSeqControllerSectionData> : TMovieSceneChannelTraitsBase<FMovieSceneEvtSeqControllerSectionData>
{
#if WITH_EDITOR
    /** Byte channels can have external values (ie, they can get their values from external objects for UI purposes) */
    typedef TMovieSceneExternalValue<FEvtSeqControllerPayload> ExtendedEditorDataType;
#endif
};

#if WITH_EDITOR
namespace MovieSceneClipboard
{
    template<> inline FName GetKeyTypeName<FEvtSeqControllerPayload>()
    {
        return "FEvtSeqControllerPayload";
    }
}
#endif