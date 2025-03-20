// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"

// from p5r_clt

enum EModelledNPCFlags : uint32 {
	Moving = 0x4,
	RandomStartNode = 0x800
};

struct FModelledNPCHeader {
public:
	uint32 blockCount;
	uint32 Flags;
	float ClipEnd;
	float ClipStart;
public:
    FModelledNPCHeader(FArchive& Ar, uint32 Version);
};

struct FPathNodeContainer {
public:
	uint32 Field00;
	uint32 Field04;
	uint32 Field08;
	//uint16 nodeCount;
	uint16 Field0E;
	TArray<FVector> positions;
public:
    friend FArchive& operator<<(FArchive& Ar, FPathNodeContainer& Out);
};

struct FModelledNPCVariations {
public:
	uint16 crowdResrcEntry; // entry in resource/resrcCrowdUnit.bin
	uint16 percentChance;
public:
    friend FArchive& operator<<(FArchive& Ar, FModelledNPCVariations& Out);
};

struct FModelledNPCData {
public:
    EModelledNPCFlags flags;
    uint16 type;
    uint16 startNode; /* useful with RandomStartNode flag (0x800) to choose a random start node between 0 - startNode */
    uint16 endNode;
    uint8 Field0A;
    uint8 Field0B;
    uint8 Field0C;
    uint8 Field0D;
    uint8 Field0E;
    uint8 Field0F;
    uint16 Field10;
    uint8 Field12;
    uint8 Field13;
    uint16 Field14;
    uint16 Field16;
    uint32 Field18;
    FModelledNPCVariations variations[5];
    FVector Rotation;
    uint32 SpawnFlags1;
    uint32 SpawnFlags2; /* root node scale flag: 0x2 */
    uint32 spawnLimit;
    float spawnTime;
    FPathNodeContainer nodes;
public:
    friend FArchive& operator<<(FArchive& Ar, FModelledNPCData& Out);
};

struct FCutoutNPCHeader {
public:
    float clipEnd;
    float clipStart;
    uint32 count;
    uint32 cutoutFlags;
    uint32 Field10;
    uint32 Field14;
    uint32 Field18;
    uint32 Field1C;
public:
    friend FArchive& operator<<(FArchive& Ar, FCutoutNPCHeader& Out);
};


class XRD777_API Xrd777EditImportClt {
public:
	Xrd777EditImportClt();
	~Xrd777EditImportClt();
    uint32 CltVersion;
    TArray<FModelledNPCData> CrowdModels;
    TArray<FVector> CrowdCutouts;
    void ImportClt(FString& Filename);
};

#endif