
// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class XRD777_API FXrd777RiriModule 
	: public IModuleInterface {
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool IsGameModule() const override {
		return true;
	}

private:
#if WITH_EDITORONLY_DATA
	FDelegateHandle EvtAdxSoundFadeTrackEditorHandle;
	FDelegateHandle EvtAdxSoundManageTrackEditorHandle;
	FDelegateHandle EvtAdxSoundTrackEditorHandle;
	FDelegateHandle EvtCharaAnimTrackEditorHandle;
	FDelegateHandle EvtCharaHandwritingTrackEditorHandle;
	FDelegateHandle EvtCharaOperationControllerTrackEditorHandle;
	FDelegateHandle EvtCharaPackAnimTrackEditorHandle;
	FDelegateHandle EvtCharaPackFaceAnimTrackEditorHandle;
	FDelegateHandle EvtCharaPropAttachTrackEditorHandle;
	FDelegateHandle EvtDialogueOptionsTrackEditorHandle;
	FDelegateHandle EvtDialogueTrackEditorHandle;
	FDelegateHandle EvtFadeScreenTrackEditorHandle;
	FDelegateHandle EvtFieldAnimTrackEditorHandle;
	FDelegateHandle EvtNessageSubtitleTrackEditorHandle;
	FDelegateHandle EvtMovieTrackEditorHandle;
	FDelegateHandle EvtScriptTrackEditorHandle;
	FDelegateHandle EvtSeqControlTrackEditorHandle;
	FDelegateHandle EvtSeqTimeJumpControlTrackEditorHandle;
#endif
};