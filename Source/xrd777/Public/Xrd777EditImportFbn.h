// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"

// from p5_fbn by @lynlyn_cpk

enum EFbnListType : int32
{
    FBN_Trigger = 1,
    FBN_Entrance = 4,
    FBN_Hit = 5,
    FBN_WanderShadow = 8,
    FBN_Chest = 9,
    FBN_Cover = 10,
    FBN_PatrolShadow = 11,
    FBN_MementosHit = 12, //5 Dupe
    FBN_MementosEntrance = 13, // 4 Dupe
    FBN_Npc = 14,
    FBN_SearchObject = 18,
    FBN_SearchObjectHit = 19,
    FBN_WarningObject = 21, // Lol, lmao
    FBN_VoiceHit = 22,
    FBN_MementosEntrance_2 = 24, //13 Dupe
    FBN_GrappleObject = 25,
    FBN_GrappleTrigger = 26,
    FBN_Header = 1178750512
};

enum ETriggerShape : int8 {
    Sphere = 1,
    Cube = 2,
};

enum ETriggerDirection : int8 {
    AnyDirection = 0,
    TowardsCenter = 1,
    Right = 2,
    Front = 3,
    Left = 4,
    Back = 5,
};

enum EHitType : int8 {
    Autohit = 0, 
    Hit = 2
};

enum EPromptTypeList : int16 {
    EXAMINE_fldCheckName0 = 0,
    GO_Blank = 1,
    EXAMINE_fldCheckName1 = 2,
    EXAMINE_fldCheckName2 = 3,
    EXAMINE_fldCheckName3 = 4,
    EXAMINE_fldCheckName4 = 5,
    STEAL_fldCheckName = 6,
    ACTION_fldActionName0 = 7,
    ACTION_fldActionName1 = 8,
    ACTION_fldActionName2 = 9,
    TALK_fldNPCName = 10,
    GO_fldPlaceName = 11,
    SHOP_fldCheckName = 12,
    EXAMINE_fldKFECheckName = 13,
};

enum ECoverBehaviorFlags : int32 {
    LStickAllowed = 1 << 24,
    InvisibleFromOtherSpots = 1 << 25,
    VisiblePartyMembers = 1 << 26,
    EnablePoint2 = 1 << 28,
    EnablePoint1 = 1 << 29
};

struct FFbnTriggerVolume {
public:
    FFbnTriggerVolume(FArchive& Ar, int32 Version);
public:
    int32 TriggerEnabled;
    int8 HTBIndex;
    ETriggerShape Shape;
    int8 Unk08;
    ETriggerDirection HitRegisterDirection;
    FVector SphereCenter;
    float Unk01;
    float Unk02;
    float Unk03;
    float SphereRadiusX;
    float SphereRadiusY;
    float Unk05;
    FVector CubeBottomRight;
    FVector CubeTopRight;
    FVector CubeBottomLeft;
    FVector CubeTopLeft;
    float Unk06;
    float Unk07;
};

struct FFbnEntrance {
public:
    FFbnEntrance(FArchive& Ar, int32 Version);
public:
    int32 Unk00;
    int32 Unk01;
    FVector Position;
    FVector Rotation;
    int16 EntranceID;
    int16 Unk02;
};

struct FFbnHitDefinition {
public:
    FFbnHitDefinition(FArchive& Ar, int32 Version);
public:
    EHitType HitType;
    uint16 NameID;
    uint16 ProcedureIndex;
    EPromptTypeList PromptType;
};

struct FFbnWanderShadow {
public:
    FFbnWanderShadow(FArchive& Ar, int32 Version);
public:
    int32 Unk00;
    int16 Unk01;
    int16 Unk02;
    FVector Position;
    FVector Rotation;
    float WanderRadius;
    uint32 Unk04;
};

struct FFbnTreasureChest {
public:
    FFbnTreasureChest(FArchive& Ar, int32 Version);
public:
    int32 Unk00;
    FVector Position;
    FQuat Rotation;
    int16 Model_MajorID;
    int16 Model_MinorID;
    uint16 Chest_ResourceHandle;
    int16 Unk01;
};

struct FFbnCoverPoints {
public:
    FFbnCoverPoints(FArchive& Ar, int32 Version);
public:
    ECoverBehaviorFlags Behavior;
    int32 Unk00;
    FVector Point1_JokerPosition;
    FVector Point2_JokerPosition;
    FVector Point1_PartyRotation;
    FVector Point2_PartyRotation;
    FVector Point1_IconPosition;
    FVector Point2_IconPosition;
    FVector Point1_CameraRotation;
    FVector Point2_CameraRotation;
    int32 Unk01;
    int32 Field94;
    int32 Field98;
    int16 CameraHeightMode;
    int16 ConnectedPoint_ID;
    int16 BitflagSection;
    int16 BitflagFlag;
    FVector Point1_JokerRotation;
    FVector Point2_JokerRotation;
};

struct FFbnPatrolShadow {
public:
    FFbnPatrolShadow(FArchive& Ar, int32 Version);
public:
    int32 Unk00;
    float ShadowSpeed;
    int32 Unk01;
    int32 DoesShadowExist;
    int32 Unk02;
    int32 Unk03;
    int16 PathNodeCount;
    int16 Unk04;
    TArray<FVector> ShadowPathNode;
    TArray<uint32> Test;
};

struct FFbnNpc {
public:
    FFbnNpc(FArchive& Ar, int32 Version);
public:
    int32 Unk00;
    float Unk01;
    FVector NPCRotation;
    float Unk02;
    float Unk03;
    int16 FNT_ID;
    int16 Unk04;
    int32 Unk05;
    int32 Unk06;
    int32 Unk07;
    int16 PathNodeCount;
    int16 Unk08;
    TArray<FVector> PathNodes;
};

struct FFbnSearchObject {
public:
    FFbnSearchObject(FArchive& Ar, int32 Version);
public:
    int32 Unk00;
    int16 Unk01;
    int16 Unk02;
    FVector Position;
    FQuat Rotation;
    int16 Model_MajorID;
    int16 Model_MinorID;
    uint16 SearchObject_ResourceHandle;
    int16 Unk03;
};

struct FFbnWarningObject {
public:
    FFbnWarningObject(FArchive& Ar, int32 Version);
public: 
    int32 Unk00;
    FVector Position;
    FQuat Rotation;
    uint8 Field30;
    uint8 Field31;
    int16 Field32;
    int16 Model_MajorID;
    int16 Model_MinorID;
    uint16 Gimmick_ResourceHandle;
    int16 Unk03;
    int32 Unk04;
    float ActiveTimer;
    float InactiveTime;
    // else ActiveTimer = 3.0, InactiveTime = 3.0
};

struct FFbnGrappleObject {
public:
    FFbnGrappleObject(FArchive& Ar, int32 Version);
public:
    uint32 Unk00;
    bool bJumpAfterGrapple;
    bool bJumpAfterGrapple2;
    int16 Wire_SequenceID;
    FVector Position;
    FQuat Rotation;
    int16 Model_MajorID;
    int16 Model_MinorID;
    uint16 Grapple_ResourceHandle;
    uint16 Unk01;
    uint16 JumpLength;
    uint16 JumpHeight;
};

struct FFbnGrappleTrigger {
public:
    FFbnGrappleTrigger(FArchive& Ar, int32 Version);
public:
    uint32 TriggerEnabled;
    uint8 HTBIndex;
    ETriggerShape Shape;
    uint8 Unk01;
    ETriggerDirection HitRegisterDirection;
    uint16 Grapple_ResourceHandle;
    int16 Unk03;
    FVector Center;
    float Unk04;
    float Unk05;
    float Unk06;
    float Scale;
    float Unk07;
    float Unk08;
    FVector BottomRight;
    FVector TopRight;
    FVector BottomLeft;
    FVector TopLeft;
    uint16 Unk09;
    uint16 Unk10;
};

struct FFbnBlock {
public:
    EFbnListType Type;
    int32 Version;
    int32 Size;
    int32 ListOffset;
    TArray<int8*> BlockEntries;
public:
    friend FArchive& operator<<(FArchive& Ar, FFbnBlock& Block);
    void ReadList(FArchive& Ar, TArray<int8*>& ListOut);
};

/**
 *
 */
class XRD777_API Xrd777EditImportFbn
{
public:
    Xrd777EditImportFbn();
    ~Xrd777EditImportFbn();
    TArray<FFbnBlock> FbnBlocks;
    void ImportFbn(FString& Filename);
};

#endif