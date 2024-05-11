// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "xrd777Module.h"
#include "Modules/ModuleManager.h"
#if WITH_EDITORONLY_DATA
#include "Logging/LogMacros.h"
#include <ISequencerModule.h>
#include <EvtAdxSoundFadeTrackEditor.h>
#include <EvtAdxSoundManageTrackEditor.h>
#include <EvtAdxSoundTrackEditor.h>
#include <EvtCharaAnimTrackEditor.h>
#include <EvtCharaHandwritingTrackEditor.h>
#include <EvtCharaOpControlTrackEditor.h>
#include <EvtCharaPackAnimTrackEditor.h>
#include <EvtCharaPackFaceAnimTrackEditor.h>
#include <EvtCharaPropAttachTrackEditor.h>
#include <EvtDialogueOptionsTrackEditor.h>
#include <EvtDialogueTrackEditor.h>
#include <EvtFadeScreenTrackEditor.h>
#include <EvtFieldAnimTrackEditor.h>
#include <EvtMessageSubtitleTrackEditor.h>
#include <EvtMovieTrackEditor.h>
#include <EvtScriptTrackEditor.h>
#include <EvtSeqControlTrackEditor.h>
#include <EvtSeqTimeJumpControlTrackEditor.h>

DEFINE_LOG_CATEGORY_STATIC(LogRiriModule, Log, All);
#endif

void FXrd777RiriModule::StartupModule() {
#if WITH_EDITORONLY_DATA
	UE_LOG(LogRiriModule, Display, TEXT("haiiii!!"));

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");

	EvtAdxSoundFadeTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtAdxSoundFadeTrackEditor::CreateTrackEditor));
	EvtAdxSoundManageTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtAdxSoundManageTrackEditor::CreateTrackEditor));
	EvtAdxSoundTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtAdxSoundTrackEditor::CreateTrackEditor));
	EvtCharaAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaAnimTrackEditor::CreateTrackEditor));
	EvtCharaHandwritingTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaHandwritingTrackEditor::CreateTrackEditor));
	EvtCharaOperationControllerTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaOpControlTrackEditor::CreateTrackEditor));
	EvtCharaPackAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaPackAnimTrackEditor::CreateTrackEditor));
	EvtCharaPackFaceAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaPackFaceAnimTrackEditor::CreateTrackEditor));
	EvtCharaPropAttachTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaPropAttachTrackEditor::CreateTrackEditor));
	EvtDialogueOptionsTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtDialogueOptionsTrackEditor::CreateTrackEditor));
	EvtDialogueTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtDialogueTrackEditor::CreateTrackEditor));
	EvtFadeScreenTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtFadeScreenTrackEditor::CreateTrackEditor));
	EvtFieldAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtFieldAnimTrackEditor::CreateTrackEditor));
	EvtNessageSubtitleTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtMessageSubtitleTrackEditor::CreateTrackEditor));
	EvtMovieTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtMovieTrackEditor::CreateTrackEditor));
	EvtScriptTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtScriptTrackEditor::CreateTrackEditor));
	EvtSeqControlTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtSeqControlTrackEditor::CreateTrackEditor));
	EvtSeqTimeJumpControlTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtSeqTimeJumpControlTrackEditor::CreateTrackEditor));
#endif
}

void FXrd777RiriModule::ShutdownModule() {
#if WITH_EDITORONLY_DATA
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(EvtAdxSoundFadeTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtAdxSoundManageTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtAdxSoundTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaHandwritingTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaOperationControllerTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaPackAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaPackFaceAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaPropAttachTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtDialogueOptionsTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtDialogueTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtFadeScreenTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtFieldAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtNessageSubtitleTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtMovieTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtScriptTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtSeqControlTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtSeqTimeJumpControlTrackEditorHandle);
#endif
}

IMPLEMENT_PRIMARY_GAME_MODULE(FXrd777RiriModule, xrd777, "xrd777" );