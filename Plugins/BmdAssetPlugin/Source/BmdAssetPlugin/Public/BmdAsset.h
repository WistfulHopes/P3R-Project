#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "BmdAsset.generated.h"

// Structures from
// https://github.com/tge-was-taken/Atlus-Script-Tools/blob/master/Source/AtlusScriptLibrary/MessageScriptLanguage/BinaryModel/Enums.cs
// https://github.com/tge-was-taken/Atlus-Script-Tools/blob/master/Source/AtlusScriptLibrary/MessageScriptLanguage/BinaryModel/Structs.cs

enum BmdBinaryDialogKind
{
    Message,
    Selection
};

enum BmdBinaryFormatVersion : int32
{
    Unknown = 1 << 0,
    Version1 = 1 << 1,
    Version1DDS = 1 << 2,
    BigEndian = 1 << 15,
    Version1BigEndian = Version1 | BigEndian
};

enum BmdBinarySelectionDialogPattern : int16
{
    Top = 0,
    Bottom = 1,
};

// Header

struct BmdBinaryHeader {
public:
    int8 FileType;
    int8 Format;
    int16 UserId;
    int32 FileSize;
    int32 Magic;
    int32 ExtSize;
    int32 ptrRelocationTable;
    int32 szRelocationTable;
    int32 DialogCount;
    int8 bIsRelocated;
    int8 Reserved;
    int16 Version;
public:
    static int32 GetFileType() { return 7; }
    static int32 GetLittleEndianMagic() { return 0x3147534d; }
    static int32 GetBigEndianMagic() { return 0x4d534731; }

    friend BMDASSETPLUGIN_API FArchive& operator<<(FArchive& Ar, BmdBinaryHeader& Header);
};

// Dialogs

struct BmdBinaryDialogHeader {
public:
    BmdBinaryDialogKind DialogKind;
    int32 ptrData;
public:
    friend BMDASSETPLUGIN_API FArchive& operator<<(FArchive& Ar, BmdBinaryDialogHeader& Header);
};

class BmdTokenBase {
public:
    virtual ~BmdTokenBase() {}
    //virtual void ReadFromStream() = 0;

    virtual FString PrintValue() = 0;
    virtual bool IsText() = 0;
};

class BmdFunctionToken : public BmdTokenBase {
public:
    int32 TableIndex;
    int32 FunctionIndex;
    TArray<int16> Parameters;

    BmdFunctionToken(int32 TableIndex, int32 FunctionIndex, int32 ParameterCount)
        : TableIndex(TableIndex), FunctionIndex(FunctionIndex)
    {
        Parameters.Reserve(ParameterCount);
        Parameters.SetNumUninitialized(ParameterCount);
    }
    FString PrintValue() override {
        FString FnFmt = FString::Printf(TEXT("[f %d %d "), TableIndex, FunctionIndex);
        for (int16 Param : Parameters) {
            int16 ParamAdj = ((Param & 0xff) - 1) << 8 | ((Param & 0xff00) - 1) >> 8;
            FnFmt += FString::Printf(TEXT("%d "), ParamAdj);
        }
        FnFmt = FnFmt.LeftChop(1);
        FnFmt += TEXT("]");
        return FnFmt;
    }
    bool IsText() override {
        return false;
    }

    static FLinearColor GetMessageColor(int32 ColorId) {
        // 0x14ba86780 (PERSONA3 RELOAD 1.0.0.0 Win64)
        switch (ColorId) {
        case 0:
            return FLinearColor(FColor(0xffffffff));
        case 1:
            return FLinearColor(FColor(0x7afdffff));
        case 2:
            return FLinearColor(FColor(0x3838ffff));
        case 3:
            return FLinearColor(FColor(0xfffe86ff));
        case 4:
            return FLinearColor(FColor(0x6ef00ff));
        case 5:
            return FLinearColor(FColor(0x50321eff));
        case 6:
            return FLinearColor(FColor(0xdc6e00ff));
        case 7:
            return FLinearColor(FColor(0xffffffff));
        case 8:
            return FLinearColor(FColor(0x50321eff));
        case 9:
            return FLinearColor(FColor(0xff1800ff));
        case 10:
            return FLinearColor(FColor(0xba0000ff));
        case 11:
            return FLinearColor(FColor(0x1200ffff));
        case 12:
            return FLinearColor(FColor(0x1f00baff));
        case 13:
            return FLinearColor(FColor(0x0ac000ff));
        case 14:
            return FLinearColor(FColor(0x078600ff));
        case 15:
            return FLinearColor(FColor(0x9D00EFFF));
        case 16:
            return FLinearColor(FColor(0x78008eff));
        case 17:
            return FLinearColor(FColor(0xbf9d02ff));
        case 18:
            return FLinearColor(FColor(0xff0391ff));
        case 19:
            return FLinearColor(FColor(0xff00fcff));
        case 20:
            return FLinearColor(FColor(0xbd0054ff));
        case 21:
            return FLinearColor(FColor(0x00aeffff));
        case 22:
            return FLinearColor(FColor(0x90401aff));
        case 23:
            return FLinearColor(FColor(0x161616FF));
        case 24:
            return FLinearColor(FColor(0x404040ff));
        case 25:
            return FLinearColor(FColor(0x656565ff));
        case 26:
            return FLinearColor(FColor(0xe6b625ff));
        case 27:
            return FLinearColor(FColor(0xffffffff));
        case 28:
            return FLinearColor(FColor(0xf0f3fcff));
        case 29:
            return FLinearColor(FColor(0xe4d4c7ff));
        case 30:
            return FLinearColor(FColor(0x505050ff));
        case 31:
            return FLinearColor(FColor(0xffffffff));
        case 32:
            return FLinearColor(FColor(0xffffffff));
        case 33:
            return FLinearColor(FColor(0x06ef00ff));
        case 34:
            return FLinearColor(FColor(0x7afdffff));
        case 35:
            return FLinearColor(FColor(0x45feffff));
        case 36:
            return FLinearColor(FColor(0x45feffff));
        case 37:
            return FLinearColor(FColor(0xff690aff));
        case 38:
            return FLinearColor(FColor(0xff690aff));
        case 39:
            return FLinearColor(FColor(0xff690aff));
        case 40:
            return FLinearColor(FColor(0xff690aff));
        case 41:
            return FLinearColor(FColor(0xff690aff));
        case 42:
            return FLinearColor(FColor(0xff690aff));
        case 43:
            return FLinearColor(FColor(0x45feffff));
        case 44:
            return FLinearColor(FColor(0xffea35ff));
        case 45:
            return FLinearColor(FColor(0xffea35ff));
        default:
            return FLinearColor(FColor(0xffffffff));
        }
    }
};

class BmdMessageToken : public BmdTokenBase {
public:
    FString MessageText;

    BmdMessageToken(TArray<uint8>& Bytes) {
        MessageText = FString(UTF8_TO_TCHAR(Bytes.GetData()));
    }

    FString PrintValue() override {
        return MessageText;
    }

    bool IsText() override {
        return true;
    }
};

class BmdDialogBase {
public:
    BmdBinaryDialogKind DialogKind;
    FString Name;
    TArray<TArray<TSharedPtr<BmdTokenBase>>> Pages;

    BmdDialogBase(BmdBinaryDialogKind InDialogKind, FString InName, int32 PageCount)
        : DialogKind(InDialogKind), Name(InName)
    {
        Pages.Reserve(PageCount);
        Pages.SetNum(PageCount);
    }

    virtual ~BmdDialogBase() {};

    virtual void ReadDialogTokens(FArchive& Ar, TArray<int32>& Offsets, int64 DialogBase, int32 TokenSize);
    BmdFunctionToken* ReadFunctionToken(FArchive& Ar, uint8 FirstByte);
    virtual BmdMessageToken* ReadMessageToken(FArchive& Ar, uint8 FirstByte);
    static bool CheckMessageTokenStream(uint8 LastByte);
};

class BmdDialogMessage : public BmdDialogBase {
public:
    FString* Speaker;

    BmdDialogMessage(FString InName, int32 PageCount, FString* InSpeaker)
        : BmdDialogBase(BmdBinaryDialogKind::Message, InName, PageCount), Speaker(InSpeaker) {}

    static FString GetMessageName(int32 MajorID, int32 MinorID, int32 SubID) {
        return FString::Printf(TEXT("MSG_%03d_%d_%d"), MajorID, MinorID, SubID);
    }

    static FString GetMessageNameMind(int32 MajorID, int32 MinorID, int32 SubID) {
        return FString::Printf(TEXT("MND_%03d_%d_%d"), MajorID, MinorID, SubID);
    }
};

class BmdDialogSelection : public BmdDialogBase {
public:
    BmdDialogSelection(FString InName, int32 SelectCount)
        : BmdDialogBase(BmdBinaryDialogKind::Selection, InName, SelectCount) {}

    static FString GetMessageName(int32 MajorID, int32 MinorID, int32 SubID) {
        return FString::Printf(TEXT("SEL_%03d_%d_%d"), MajorID, MinorID, SubID);
    }

    //BmdMessageToken* ReadMessageToken(FArchive& Ar, uint8 FirstByte) override;
};

struct BmdBinaryMessage {
public:
    int16 SpeakerId;
    TArray<int32> PageOffsets;
    int32 TokenSize;
public:
    friend FArchive& operator<<(FArchive& Ar, BmdBinaryMessage& Header);
};

struct BmdBinarySelectionDialog {
public:
    int16 Ext;
    TArray<int32> OptionOffsets;
    BmdBinarySelectionDialogPattern Pattern;
    int16 Reserved;
    int32 TokenSize;
public:
    friend FArchive& operator<<(FArchive& Ar, BmdBinarySelectionDialog& Header);
};

// Speakers

struct BmdBinarySpeakerHeader {
public:
    int32 ptrSpeakers;
    int32 SpeakerCount;
    int32 pExtData;
    int32 Reserved;

    friend BMDASSETPLUGIN_API FArchive& operator<<(FArchive& Ar, BmdBinarySpeakerHeader& Header);
};

// Deserialized Container

class BmdData {
public:
    BmdBinaryHeader BinaryHeader;
    TMap<FString, TSharedRef<BmdDialogBase>> Dialogs;
    //TArray<TSharedRef<BmdDialogBase>> Dialogs;
    TArray<FString> Speakers;

    friend BMDASSETPLUGIN_API FArchive& operator<<(FArchive& Ar, BmdData& Data);

    FString* GetSpeakerName(int16 SpeakerIndex) {
        if (SpeakerIndex == -1) {
            return nullptr;
        }
        check(Speakers.IsValidIndex(SpeakerIndex));
        return &Speakers[SpeakerIndex];
    }
};

UCLASS(Blueprintable)
class BMDASSETPLUGIN_API UBmdAsset : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int8> mBuf;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
    FString SyncToBmdFile;
#endif
    
    UBmdAsset();
};

