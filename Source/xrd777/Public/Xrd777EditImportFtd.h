// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"

struct FFtdTable {
public:
    uint32 Field00;
    uint32 Magic;
    uint32 FileSize;
    uint16 DataType;
    uint16 DataCount;
    TArray<FString> Data;
public:
    static constexpr uint32 GetBigEndianMagic() { return 0x30445446; }
    static constexpr uint32 GetLittleEndianMagic() { return 0x46544430; }
    friend FArchive& operator<<(FArchive& Ar, FFtdTable& OutTable);
};

/**
 * 
 */
class XRD777_API Xrd777EditImportFtd
{
public:
    FFtdTable Table;
public:
    Xrd777EditImportFtd();
    void ImportFtd(FString& Path);
};

#endif