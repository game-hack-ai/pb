#pragma once
#include <ctime>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <string>

#define MAX_NETWORKED_HARDCODED_NAME 410
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned short UINT16;
#define FALSE false
#define TRUE true
typedef DWORD ULONG_PTR;
typedef ULONG_PTR DWORD_PTR;
typedef BYTE* LPBYTE;

#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
typedef DWORD* LPDWORD;
#define _byteswap_ushort(x)  ((unsigned short int) ((((x) >> 8) & 0xffu) | (((x) & 0xffu) << 8)))
#define HIDWORD(_qw)    ((DWORD)(((_qw) >> 32) & 0xffffffff))
typedef long long LONGLONG;
#define LOWORD(_dw)     ((WORD)(((DWORD_PTR)(_dw)) & 0xffff))
#define HIWORD(_dw)     ((WORD)((((DWORD_PTR)(_dw)) >> 16) & 0xffff))
#define LODWORD(_qw)    ((DWORD)(_qw))
#define HIBYTE(x) ((unsigned char) ((x) >> 8 & 0xff))
typedef uint32_t UINT32;
typedef int32_t INT32;

typedef uint8_t UINT8;
typedef bool BOOL;




enum
{
	ITEMINDEX_AKM = 0,
	ITEMINDEX_SCAR,
	ITEMINDEX_M416,
	ITEMINDEX_AUG,
	ITEMINDEX_M16A4,
	ITEMINDEX_QBZ,
	ITEMINDEX_M762,
	ITEMINDEX_GROZA,
	ITEMINDEX_MK47,
	ITEMINDEX_VSS,
	ITEMINDEX_MINI14,
	ITEMINDEX_QBU,
	ITEMINDEX_MK14,
	ITEMINDEX_PISTOL,
	ITEMINDEX_KAR98K,
	ITEMINDEX_SKS,
	ITEMINDEX_SLR,
	ITEMINDEX_AWM,
	ITEMINDEX_M24,
	ITEMINDEX_TOMMYGUN,
	ITEMINDEX_UMP,
	ITEMINDEX_VECTOR,
	ITEMINDEX_UZI,
	ITEMINDEX_S686,
	ITEMINDEX_S189,
	ITEMINDEX_S12K,
	ITEMINDEX_FLARE,
	ITEMINDEX_DP28,
	ITEMINDEX_M249,
	ITEMINDEX_PAN,
	ITEMINDEX_SMOKE,
	ITEMINDEX_STUN,
	ITEMINDEX_MOLOTOV,
	ITEMINDEX_FRAG,
	ITEMINDEX_CROSSBOW,
	ITEMINDEX_AMMO9,
	ITEMINDEX_AMMO12GAUGE,
	ITEMINDEX_AMMO45ACP,
	ITEMINDEX_AMMO556,
	ITEMINDEX_AMMO762,
	ITEMINDEX_BOLT,
	ITEMINDEX_SNISUP,
	ITEMINDEX_ARSUP,
	ITEMINDEX_SMGSUP,
	ITEMINDEX_PISSUP,
	ITEMINDEX_SNIFLASH,
	ITEMINDEX_ARFLASH,
	ITEMINDEX_SMGFLASH,
	ITEMINDEX_SNICOM,
	ITEMINDEX_ARCOM,
	ITEMINDEX_SMGCOM,
	ITEMINDEX_X8,
	ITEMINDEX_X6,
	ITEMINDEX_X4,
	ITEMINDEX_X3,
	ITEMINDEX_X2,
	ITEMINDEX_REDSIGHT,
	ITEMINDEX_HOLOSIGHT,
	ITEMINDEX_HELMETLV3,
	ITEMINDEX_HELMETLV2,
	ITEMINDEX_HELMETLV1,
	ITEMINDEX_BAGLV3,
	ITEMINDEX_BAGLV2,
	ITEMINDEX_BAGLV1,
	ITEMINDEX_ARMMORLV3,
	ITEMINDEX_ARMMORLV2,
	ITEMINDEX_ARMMORLV1,
	ITEMINDEX_MEDKIT,
	ITEMINDEX_FIRSTKIT,
	ITEMINDEX_BANDAGE,
	ITEMINDEX_INJECTION,
	ITEMINDEX_PILLS,
	ITEMINDEX_DRINK,
	ITEMINDEX_VEHICLE,
	ITEMINDEX_PLAYER,
	ITEMINDEX_CRATEBOX,
	ITEMINDEX_END,
};
typedef struct _Object
{
	UINT32 nGUID;
	char szPathName[1024];
	_Object()
	{
		memset(szPathName, 0, 1024);
		nGUID = 0;
	}
}OBJECT, * POBJECT;


typedef struct _Vector
{
	float X;
	float Y;
	float Z;
}FVECTOR, * PFVECTOR;
typedef struct _Rotator
{
	float Pitch;
	float Yaw;
	float Roll;
}FROTATOR, * PFROTATOR;

typedef struct _Name
{
	UINT32 nInNumber;
	char szString[1024];
	_Name()
	{
		memset(szString, 0, 1024);
	}
}FName, * PFName;

class CBitReader
{
public:
	CBitReader() {};
	CBitReader(CBitReader& Other) { memcpy(Buffer, Other.Buffer, (Other.nNum + 7) >> 3); nNum = Other.nNum; nPos = Other.nPos; };
	BYTE Buffer[1024 * 5];
	UINT32 nNum;
	UINT32 nPos;
	void printString() {
		for (int i = nPos; i < nNum; i++)
		{
			printf("%c", Buffer[i]);
		}
		printf("\n");
	}
	void printHex() {
		UINT32 oldPos = nPos;



		std::ofstream outfile;
		outfile.open("hexout.txt", std::ios_base::app);

		for (int i = oldPos; i < nNum; i++)
		{
			/*char p = (Buffer[(oldPos >> 3)] >> (oldPos % 8)) | (Buffer[(oldPos >> 3) + 1] << (8 - oldPos % 8));
			oldPos += 8;*/
			char p = Buffer[i];
			std::cout << std::hex << (int)p;

			outfile << std::hex << (int)p;
		}

		outfile << std::endl;
		outfile.close();
		printf("\n");
	}
	UINT32 GetPos()
	{
		return nPos;
	}
	BYTE Shift(BYTE Cnt)
	{
		return 1 << Cnt;
	}
	uint64_t GetTickCountMs()
	{
		struct timespec ts;

		//clock_gettime(CLOCK_MONOTONIC, &ts);

		return (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
	}
	bool ReadByteData(BYTE* data, int nBytes)
	{
		for (int i = 0; i < nBytes; i++)
		{
			data[i] = (Buffer[(nPos >> 3)] >> (nPos % 8)) | (Buffer[(nPos >> 3) + 1] << (8 - nPos % 8));
			nPos += 8;
			if (IsError())
			{
				return false;
			}
		}
		return true;
	}
	bool IsError()
	{
		return(nPos > nNum);
	}
	bool IsOver()
	{
		return(nPos > nNum);
	}
	int ReadString(char* data, int* pStrLen = NULL)
	{
		BYTE szTemp[1024] = { 0 };
		int nSaveNum;
		UINT32 nTemp;
		int nReadBytes = 0;
		Serialize(&nTemp, 4);
		nSaveNum = (int)nTemp;
		bool LoadUCS2Char = nSaveNum < 0;
		bool bRes = false;
		if (LoadUCS2Char)
			nSaveNum = -nSaveNum;
		if (LoadUCS2Char)
		{
			if (nSaveNum > 512)
			{
				return 0;
			}
		}
		else
		{
			if (nSaveNum > 1024)
			{
				return 0;
			}
		}

		if (nSaveNum == 0)
			return 0;
		if (LoadUCS2Char)
		{
			bRes = ReadByteData(szTemp, nSaveNum * 2);
			if (!bRes)
				return 0;
			if ((szTemp[nSaveNum * 2 - 1] != 0) || (szTemp[nSaveNum * 2 - 2] != 0))
				return 0;
			if (pStrLen != NULL)
				* pStrLen = -nSaveNum;
			memcpy(data, szTemp, nSaveNum * 2);
			return 2;
		}
		else
		{
			bRes = ReadByteData(szTemp, nSaveNum);
			if (!bRes)
				return 0;

			if (szTemp[nSaveNum - 1] != 0)
				return 0;
			memcpy(data, szTemp, nSaveNum);
			if (pStrLen != NULL)
				* pStrLen = nSaveNum;
			return 1;
		}
	}
	BYTE ReadBit()
	{
		UINT8 Bit = 0;
		if (!IsError())
		{
			UINT32 LocalPos = nPos;
			const UINT32 LocalNum = nNum;
			{
				Bit = !!(Buffer[LocalPos >> 3] & Shift(LocalPos & 7));
				nPos++;
			}
		}

		return Bit;
	}
	UINT32 GetNumBytes() const
	{
		return (nNum + 7) >> 3;
	}
	UINT32 GetNumBits() const
	{
		return nNum;
	}
	UINT32 GetPosBits() const
	{
		return nPos;
	}
	BOOL AtEnd()
	{
		return nPos >= nNum;
	}
	void appBitsCpy(UINT8* Dest, INT32 DestBit, UINT8* Src, INT32 SrcBit, INT32 BitCount)
	{
		if (BitCount == 0) return;

		if (BitCount <= 8)
		{
			UINT32 DestIndex = DestBit / 8;
			UINT32 SrcIndex = SrcBit / 8;
			UINT32 LastDest = (DestBit + BitCount - 1) / 8;
			UINT32 LastSrc = (SrcBit + BitCount - 1) / 8;
			UINT32 ShiftSrc = SrcBit & 7;
			UINT32 ShiftDest = DestBit & 7;
			UINT32 FirstMask = 0xFF << ShiftDest;
			UINT32 LastMask = 0xFE << ((DestBit + BitCount - 1) & 7);
			UINT32 Accu;

			if (SrcIndex == LastSrc)
				Accu = (Src[SrcIndex] >> ShiftSrc);
			else
				Accu = ((Src[SrcIndex] >> ShiftSrc) | (Src[LastSrc] << (8 - ShiftSrc)));

			if (DestIndex == LastDest)
			{
				UINT32 MultiMask = FirstMask & ~LastMask;
				Dest[DestIndex] = ((Dest[DestIndex] & ~MultiMask) | ((Accu << ShiftDest) & MultiMask));
			}
			else
			{
				Dest[DestIndex] = (UINT8)((Dest[DestIndex] & ~FirstMask) | ((Accu << ShiftDest) & FirstMask));
				Dest[LastDest] = (UINT8)((Dest[LastDest] & LastMask) | ((Accu >> (8 - ShiftDest)) & ~LastMask));
			}

			return;
		}

		UINT32 DestIndex = DestBit / 8;
		UINT32 FirstSrcMask = 0xFF << (DestBit & 7);
		UINT32 LastDest = (DestBit + BitCount) / 8;
		UINT32 LastSrcMask = 0xFF << ((DestBit + BitCount) & 7);
		UINT32 SrcIndex = SrcBit / 8;
		UINT32 LastSrc = (SrcBit + BitCount) / 8;
		int   ShiftCount = (DestBit & 7) - (SrcBit & 7);
		int   DestLoop = LastDest - DestIndex;
		INT32   SrcLoop = LastSrc - SrcIndex;
		UINT32 FullLoop;
		UINT32 BitAccu;

		if (ShiftCount >= 0)
		{
			FullLoop = std::max(DestLoop, SrcLoop);
			BitAccu = Src[SrcIndex] << ShiftCount;
			ShiftCount += 8;
		}
		else
		{
			ShiftCount += 8;
			FullLoop = std::max(DestLoop, SrcLoop - 1);
			BitAccu = Src[SrcIndex] << ShiftCount;
			SrcIndex++;
			ShiftCount += 8;
			BitAccu = (((UINT32)Src[SrcIndex] << ShiftCount) + (BitAccu)) >> 8;
		}

		Dest[DestIndex] = (UINT8)((BitAccu & FirstSrcMask) | (Dest[DestIndex] & ~FirstSrcMask));
		SrcIndex++;
		DestIndex++;

		for (; FullLoop > 1; FullLoop--)
		{
			BitAccu = (((UINT32)Src[SrcIndex] << ShiftCount) + (BitAccu)) >> 8;
			SrcIndex++;
			Dest[DestIndex] = (UINT8)BitAccu;
			DestIndex++;
		}

		if (LastSrcMask != 0xFF)
		{
			if ((UINT32)(SrcBit + BitCount - 1) / 8 == SrcIndex)
			{
				BitAccu = (((UINT32)Src[SrcIndex] << ShiftCount) + (BitAccu)) >> 8;
			}
			else
			{
				BitAccu = BitAccu >> 8;
			}

			Dest[DestIndex] = (UINT8)((Dest[DestIndex] & LastSrcMask) | (BitAccu & ~LastSrcMask));
		}
	}
	void SerializeBits(void* Dest, UINT32 LengthBits)
	{
		if (LengthBits > 1000000)
		{
			return;
		}
		if (nPos + LengthBits > nNum)
		{
			memset(Dest, 0, (LengthBits + 7) >> 3);
			nPos = nNum + 1;
			return;
		}
		if (LengthBits == 1)
		{
			((BYTE*)Dest)[0] = 0;
			if (Buffer[nPos >> 3] & Shift(nPos & 7))
				((BYTE*)Dest)[0] |= 0x01;
			nPos++;
		}
		else if (LengthBits != 0)
		{
			((BYTE*)Dest)[((LengthBits + 7) >> 3) - 1] = 0;
			appBitsCpy((BYTE*)Dest, 0, (BYTE*)Buffer, nPos, LengthBits);
			nPos += LengthBits;
		}
	}
	void SerializeInt(UINT32& OutValue, UINT32 ValueMax)
	{
		{
			int Value = 0;
			int LocalPos = nPos;
			const int LocalNum = nNum;

			for (int Mask = 1; (Value + Mask) < ValueMax && Mask; Mask *= 2, LocalPos++)
			{
				if (LocalPos >= LocalNum)
				{
					break;
				}

				if (Buffer[LocalPos >> 3] & Shift(LocalPos & 7))
				{
					Value |= Mask;
				}
			}

			nPos = LocalPos;
			OutValue = Value;
		}
	}
	UINT32 ReadInt(UINT32 Max)
	{
		UINT32 Value = 0;

		SerializeInt(Value, Max);

		return Value;
	}
	float ReadFloat()
	{
		UINT32 nVal = 0;
		float fRet;
		ReadByteData((BYTE*)& nVal, 4);
		fRet = *(float*)& nVal;
		return fRet;
	}
	void Serialize(void* Dest, UINT32 LengthBytes)
	{
		SerializeBits(Dest, LengthBytes * 8);
	}
	void SetData(CBitReader& Src, UINT32 CountBits)
	{
		nNum = CountBits;
		nPos = 0;
		Src.SerializeBits(Buffer, CountBits);
	}
	void SerializeIntPacked(UINT32& Value)
	{
		{
			Value = 0;
			UINT8 cnt = 0;
			UINT8 more = 1;
			while (more)
			{
				UINT8 NextByte;
				Serialize(&NextByte, 1);

				more = NextByte & 1;
				NextByte = NextByte >> 1;
				Value += NextByte << (7 * cnt++);
			}
		}
	}
};
class FInBunch : public CBitReader
{
public:
	FInBunch(CBitReader reader) :CBitReader(reader) { bHasPackageMapExports = 0; bHasMustBeMappedGUIDs = 0; };
	FInBunch() {};
	int 				PacketId;
	int 				ChIndex;
	int 				ChType;
	int 				ChSequence;
	bool				bOpen;
	bool				bClose;
	bool				bDormant;
	bool				bIsReplicationPaused;
	bool				bReliable;
	bool				bPartial;
	bool				bPartialInitial;
	bool				bPartialFinal;
	bool				bHasPackageMapExports;
	bool				bHasMustBeMappedGUIDs;
	bool				bIgnoreRPCs;

};


typedef struct _ActorInfoV {
	char szName[100];
	int nNameLen;
	UINT32 nNetGUID;
	_ActorInfoV()
	{
		nNameLen = 0;
		nNetGUID = 0x77777777;
	}
}ACTORINFOV, * PACTORINFOV;
typedef struct _ACTOR {
	bool bDead;
	bool bVisible;
	bool bVehicle;
	bool bDraw;
	int nType;
	UINT32 nTeamID;
	UINT32 nVehicleSeatIdx;
	UINT32 nInstigator;
	UINT32 nAttachParent;
	UINT32 nVehicleParent;
	DWORD nVehicleSeat;
	int nTeamNo;
	float fXPos;
	float fYPos;
	float fZPos;
	float fYaw;
	float fVelX;
	float fVelY;
	float fVelZ;
	float fSeverTime;
	char m_szPlayerName[100];
	DWORD dwReceiveDataTime;
	UINT32 nTeamIndex;
	int nVirtualID;
	int nTimes;
	int nChangeCnt;
	int nErrorCnt;
	UINT32 nActorChannelIndex;
	int nStateID;
	BYTE nMoveMode;
	_ACTOR() : fSeverTime(0)
	{
		nVehicleSeatIdx = 0x77777777;
		nAttachParent = 0x77777777;
		nVehicleParent = 0x77777777;
		nInstigator = 0x77777777;
		nTeamID = 0x77777777;
		bDraw = false;
		nActorChannelIndex = 0;
		nStateID = -1;
		bDead = false;
		nMoveMode = 0xFF;
		bVisible = true;
		bVehicle = false;
		nVehicleSeat = 0x77777777;
		dwReceiveDataTime = 0x00;
		fVelX = 0.0;
		fVelY = 0.0;
		fVelZ = 0.0;
		fXPos = 0.0;
		fYPos = 0.0;
		fZPos = 0.0;
		nTeamNo = 0;
	}
	void Reset()
	{
		nVehicleSeatIdx = 0x77777777;
		nAttachParent = 0x77777777;
		nVehicleParent = 0x77777777;
		nInstigator = 0x77777777;
		nTeamID = 0x77777777;
		bDraw = false;
		nActorChannelIndex = 0;
		nStateID = -1;
		bDead = false;
		nMoveMode = 0xFF;
		bVisible = true;
		bVehicle = false;
		nVehicleSeat = 0x77777777;
		dwReceiveDataTime = 0x00;
		fVelX = 0.0;
		fVelY = 0.0;
		fVelZ = 0.0;
		fXPos = 0.0;
		fYPos = 0.0;
		fZPos = 0.0;
		nTeamNo = 0;
	}

}ACTOR, * PACTOR;
typedef struct _VEHICLE_INFO {
	UINT32 nTypeGUID;
	UINT32 nNum[4];
	UINT32 nInstigator;
	int nSeatCnt;
	float fXPos;
	float fYPos;
	float fZPos;
	float fVelX;
	float fVelY;
	float fVelZ;
	float fYaw;
	bool bVisible;
	DWORD dwReceiveDataTime;
	_VEHICLE_INFO()
	{
		nTypeGUID = 0x77777777;
		nInstigator = 0x77777777;
		memset(nNum, 0x77777777, 4 * sizeof(UINT32));
		bVisible = false;
		nSeatCnt = 0;
		fVelX = 0.0;
		fVelY = 0.0;
		fVelZ = 0.0;
		dwReceiveDataTime = 0x00;
	}
}VEHICLE_INFO, * pVEHICLE_INFO;
typedef struct _AirDrop
{
	float fXPos;
	float fYPos;
	float fZPos;
	float fDirX;
	float fDirY;
	float fCurX;
	float fCurY;
	float fSpeed;
	bool bAirDropVisible;
	DWORD dwGetTickCnt;
	_AirDrop()
	{
		bAirDropVisible = false;
	}
}AIR_DROP_PLANE, * PAIR_DROP_PLANE;
typedef struct _Item {
	UINT32 nGUID;
	UINT32 nTypeGUID;
	float fXPos;
	float fYPos;
	float fZPos;
	float fYaw;
	int nItemIndex;
	bool bVisible;
	uint64_t dwReceiveDataTime;
	_Item()
	{
		dwReceiveDataTime = 0;
		nItemIndex = -1;
		nGUID = 0x77777777;
		nTypeGUID = 0x77777777;
		bVisible = true;
	}
}ITEM, * PITEM;
typedef struct _Channel
{
	UINT32 nChannelIndex;
	UINT32 nNetGUID;
	UINT32 nTypeNetGUID;
	bool bChannelOpen;
	bool bChannelClose;
	bool bDormant;
	PACTOR pActor;
	PITEM pItem;
	pVEHICLE_INFO pVehicle;
	PAIR_DROP_PLANE pAirDropPlane;

	_Channel()
	{
		nChannelIndex = 0;
		nNetGUID = 0x77777777;
		nTypeNetGUID = 0x77777777;
		bChannelOpen = false;
		bChannelClose = false;
		bDormant = false;
		pActor = nullptr;
		pItem = nullptr;
		pVehicle = nullptr;
		pAirDropPlane = nullptr;
	}
	void Reset()
	{
		nChannelIndex = 0;
		nNetGUID = 0x77777777;
		nTypeNetGUID = 0x77777777;
		bChannelOpen = false;
		bChannelClose = false;
		bDormant = false;
		pActor = NULL;
		pItem = NULL;
		pVehicle = NULL;
		pAirDropPlane = NULL;
	}
}CHANNEL, * PCHANNEL;
typedef struct _DeadActor {
	float fXPos;
	float fYPos;
	float fZPos;
	int nTimes;
	int nType;
	int nTeamNo;
	_DeadActor()
	{
		nTimes = 0;
		nType = 0;
		nTeamNo = 0;
	}
}DEAD_ACTOR, * PDEAD_ACTOR;
typedef struct _ShootInfo
{
	float fImpactXPos;
	float fImpactYPos;
	float fImpactZPos;
	float fMuzzleXPos;
	float fMuzzleYPos;
	float fMuzzleZPos;
	float fShootDirX;
	float fShootDirY;
	int nTimes;
}SHOOTINFO, * PSHOOTINFO;

typedef struct _ItemTypeID
{
	UINT32 nTypeGUID;
	int nIDIndex;
}ITEM_TYPE_ID, * PITEM_TYPE_ID;
typedef struct _CircleInfo
{
	float fBlueX;
	float fBlueY;
	float fBlueR;
	float fWhiteX;
	float fWhiteY;
	float fWhiteR;
	float fTime;
	bool bRestictionStart;
	DWORD dwTickStartCnt;
	size_t	hash;
	_CircleInfo()
	{
		hash = 0;
		fBlueX = 0;
		fBlueY = 0;
		fBlueR = 0;
		fWhiteX = 0;
		fWhiteY = 0;
		fWhiteR = 0;
		fTime = 0;
		bRestictionStart = false;
		dwTickStartCnt = 0;
	}
}CIRCLE_INFO, * pCIRCLE_INFO;
typedef struct _AirAttackArea
{
	float fRedX;
	float fRedY;
	float fRedR;
	DWORD dwGetTickCnt;
	bool bVisible;
	_AirAttackArea()
	{
		bVisible = false;
	}
}AIR_ATTACK_AREA, * PAIR_ATTACK_AREA;
struct user_shared_container {
	uint64_t	gamestatustime;
	uint64_t	lastUpdateTime;
	time_t	lastResponseTime;
	UINT32 m_nPlayerGUID;
	UINT32 m_nAirDropGUID;
	bool m_bPacketTruncate;
	bool m_bReadMyPlayerName;
	bool m_bReadWeatherNameSuccess;
	bool m_bReadWeatherName;
	BOOL m_bDrawThreadF;
	CHANNEL m_channel[8000];
	int m_nChannelCnt;
	ACTORINFOV m_actorInfo[100];
	int m_nActorInfoCnt;
	char m_szMyActorName[300];
	int m_nMyActorNameLen;
	ACTOR m_actors[300];
	int m_nActorCnt;
	DEAD_ACTOR m_DeadActor[100];
	int m_nDeadActorCnt;
	size_t airplanehash;
	size_t deadactorhash;
	size_t circlehash;
	size_t iteminfohash;

	ACTOR m_TestActors[10];
	int m_nTestActorCnt;
	ACTOR m_FilterActors[10];
	int m_nFilterActorCnt;
	ACTOR m_myActor;
	int m_nChangeCnt;
	ACTOR m_myActorTemp;
	bool m_bTeamInfoResetF;
	ACTOR m_TeamActor[12];
	int m_nTeammateCnt;
	int m_nTeammateCntTemp;
	int m_nTeamRealID[12];
	int m_nTeamRealIDTemp[12];
	int m_nTeamNo[12];
	int m_nTeamNetGUID[12];
	int m_nTeamNetGUIDTemp[12];
	ACTOR m_DrawActors[1000];
	SHOOTINFO m_arShootInfo[1000];
	int m_nShootInfoCnt;
	int m_nDrawActorCnt;
	ACTOR m_DrawActorsTemp[100];
	int m_nDrawActorTempCnt;
	size_t vehicleHash;
	size_t actorinfohash;
	VEHICLE_INFO m_DrawVehicles[1000];
	int m_nDrawVehicleCnt;
	VEHICLE_INFO m_DrawVehiclesTemp[100];
	int m_nDrawVehiclesTempCnt;
	ITEM m_DrawItem[1000];
	int m_nDrawItemCnt;
	AIR_DROP_PLANE m_DrawAirDropPlane[20];
	int m_nDrawAirDropPlaneCnt;
	AIR_DROP_PLANE m_DrawAirDropPlaneTemp[20];
	int m_nDrawAirDropPlaneTempCnt;
	ITEM m_DrawItemTemp[1000];
	int m_nDrawItemTempCnt;
	SHOOTINFO m_DrawShootLineTemp[1000];
	int m_nDrawShootLineTempCnt;

	UINT32 m_arVehicleTypeGUID[1000];
	int m_nVehicleTypeGUIDCnt;
	ITEM_TYPE_ID m_arItemTypeGUID[1000];
	int m_nItemTypeGUIDCnt;

	bool m_bUpdateActorInfo;
	int m_nStartPosX;
	int m_nStartPosY;
	int m_nWidth;
	int m_nHeight;
	int m_nVirtualWidth;
	int m_nVirtualHeight;
	int m_nScale;
	int m_nMylineLen;
	bool m_bMyCircleDraw;
	float m_fMyXPos;
	float m_fMyYPos;
	float m_fMyZPos;
	float m_fMyDirYaw;
	UINT32 m_nMyChannelIndex;
	int m_nMapIndex;
	char g_sz3366PacketDecodeKeyMakeKey[16];
	char g_sz3366PacketDecodeKey[488];
	char g_szGameServerIpAddr[256];
	char g_szGamePacketKey01[256];
	char g_szGamePacketKey02[13];
	char g_szPacketDecodeKey_3F213A0[32];
	char g_szPacketDecodeKey_3F21350[12];
	bool g_bPacketDecode_3F21303;
	CIRCLE_INFO m_CircleInfo;
	AIR_ATTACK_AREA m_AirAttackArea;
	int64_t g_ullDecodeKey;

	bool g_bLoc;
	float g_fMaxNorm;
	bool g_bExternStringDetect;
	//pthread_t drawThread;
};
struct user_container {
	uint64_t GetTickCountMs()
	{
		struct timespec ts;

		//clock_gettime(CLOCK_MONOTONIC, &ts);

		return (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
	}


	int socket;
	int distrbute_sockfd;
	//pthread_t recvThread;


	user_shared_container* user;
	bool _running;
	//pthread_mutex_t lock;


	bool KillActor(char* Name, int nNameLen, int nRelation)
	{
		if (user == nullptr)
			return false;
		int i = 0, j = 0;
		UINT32 nNetGUID = 0;
		int nTeamNo = 0;
		if (user->m_nDeadActorCnt > 99)
		{
			return false;
		}
		if (NameCmp(user->m_szMyActorName, user->m_nMyActorNameLen, Name, nNameLen))
		{
			user->m_myActor.dwReceiveDataTime = GetTickCountMs();
			user->m_myActor.bDead = true;
			user->m_DeadActor[user->m_nDeadActorCnt].fXPos = user->m_myActor.fXPos;
			user->m_DeadActor[user->m_nDeadActorCnt].fYPos = user->m_myActor.fYPos;
			user->m_DeadActor[user->m_nDeadActorCnt].fZPos = user->m_myActor.fZPos;
			user->m_DeadActor[user->m_nDeadActorCnt].nType = 0;
			user->m_DeadActor[user->m_nDeadActorCnt].nTimes = 60;
			user->m_nDeadActorCnt++;
		}
		else
		{
			for (j = 0; j < user->m_nActorInfoCnt; j++)
			{
				if (NameCmp(user->m_actorInfo[j].szName, user->m_actorInfo[j].nNameLen, Name, nNameLen))
				{
					nNetGUID = user->m_actorInfo[j].nNetGUID;
					break;
				}
			}
			if (j < user->m_nActorInfoCnt)
			{
				for (i = 0; i < user->m_nTeammateCnt; i++)
				{
					if (nNetGUID == user->m_nTeamNetGUID[i])
					{
						nTeamNo = user->m_nTeamNo[i];
						user->m_TeamActor[i].bDead = true;
						user->m_DeadActor[user->m_nDeadActorCnt].fXPos = user->m_TeamActor[i].fXPos;
						user->m_DeadActor[user->m_nDeadActorCnt].fYPos = user->m_TeamActor[i].fYPos;
						user->m_DeadActor[user->m_nDeadActorCnt].fZPos = user->m_TeamActor[i].fZPos;
						user->m_DeadActor[user->m_nDeadActorCnt].nType = 1;
						user->m_DeadActor[user->m_nDeadActorCnt].nTeamNo = user->m_nTeamNo[i];
						user->m_DeadActor[user->m_nDeadActorCnt].nTimes = 60;
						user->m_nDeadActorCnt++;
						break;
					}
				}
				if (i == user->m_nTeammateCnt)
				{
					for (i = 0; i < user->m_nChannelCnt; i++)
					{
						if (user->m_channel[i].pActor)
						{
							if (user->m_channel[i].nNetGUID == nNetGUID)
							{

								user->m_DeadActor[user->m_nDeadActorCnt].fXPos = user->m_channel[i].pActor->fXPos;
								user->m_DeadActor[user->m_nDeadActorCnt].fYPos = user->m_channel[i].pActor->fYPos;
								user->m_DeadActor[user->m_nDeadActorCnt].fZPos = user->m_channel[i].pActor->fZPos;
								user->m_DeadActor[user->m_nDeadActorCnt].nType = 2;
								user->m_DeadActor[user->m_nDeadActorCnt].nTeamNo = nTeamNo;
								user->m_DeadActor[user->m_nDeadActorCnt].nTimes = 60;
								user->m_nDeadActorCnt++;
							}
						}
					}
				}
			}
		}

		return true;
	}
	void TeamActorManager(ACTOR actor, int nActorID)
	{
		if (user == nullptr)
			return;
		int j = 0;
		int i = 0, k = 0;
		int nIDCnt = 0;
		int nTeamIDOrder[4];
		int nTemp;
		if (!user->m_bTeamInfoResetF)
		{
			if (abs(actor.fZPos - 150000) < 0.1)
				ResetTeammateInfo();
		}
		for (j = 0; j < user->m_nTeammateCnt; j++)
		{
			if (user->m_nTeamRealID[j] == nActorID)
			{
				actor.nTeamIndex = j;
				actor.nVirtualID = 0;
				if (user->m_nTeamNo[j] != 0)
				{
					actor.nTeamNo = user->m_nTeamNo[j];
				}
				break;
			}
		}
		user->m_TeamActor[j].fXPos = actor.fXPos;
		user->m_TeamActor[j].fYPos = actor.fYPos;
		user->m_TeamActor[j].fZPos = actor.fZPos;
		user->m_TeamActor[j].fYaw = actor.fYaw;
		user->m_TeamActor[j].fVelX = actor.fVelX;
		user->m_TeamActor[j].fVelY = actor.fVelY;
		user->m_TeamActor[j].fVelZ = actor.fVelZ;
		if (j < 3)
		{
			if (user->m_nTeammateCnt == j)
			{
				user->m_nTeamRealID[j] = nActorID;
				if (user->m_bTeamInfoResetF)
				{
					for (i = 0; i < user->m_nTeammateCntTemp; i++)
					{
						if (user->m_nTeamRealID[j] == user->m_nTeamRealIDTemp[i])
						{
							user->m_nTeamNetGUID[j] = user->m_nTeamNetGUIDTemp[i];
							break;
						}
					}
				}
				user->m_nTeammateCnt++;
				user->m_nTeammateCnt = user->m_nTeammateCnt % 100;

				for (i = 0; i < user->m_nTeammateCnt; i++)
				{
					nTeamIDOrder[i] = user->m_nTeamRealID[i];

				}
				nIDCnt = user->m_nTeammateCnt;
				if (user->m_myActor.nStateID != -1)
				{
					nTeamIDOrder[nIDCnt] = user->m_myActor.nStateID;
					nIDCnt++;
				}
				for (i = 0; i < nIDCnt - 1; i++)
				{
					for (k = i; k < nIDCnt; k++)
					{
						if (nTeamIDOrder[k] < nTeamIDOrder[i])
						{
							nTemp = nTeamIDOrder[k];
							nTeamIDOrder[k] = nTeamIDOrder[i];
							nTeamIDOrder[i] = nTemp;
						}
					}
				}
				for (i = 0; i < user->m_nTeammateCnt; i++)
				{
					for (k = 0; k < nIDCnt; k++)
					{
						if (user->m_nTeamRealID[i] == nTeamIDOrder[k])
						{
							user->m_nTeamNo[i] = k + 1;
							break;
						}
					}
				}
			}
		}
	}
	bool RemoveChannel(UINT32 nChannelNo)
	{
		if (user == nullptr)
			return false;
		int i = 0;
		if (user->m_nChannelCnt < 1)
		{
			return false;
		}
		{
			if (user->m_channel[nChannelNo].pActor)
			{
				if (user->m_channel[nChannelNo].pActor->nType == 1)
				{
					for (i = 0; i < user->m_nTeammateCnt; i++)
					{
						if ((user->m_channel[nChannelNo].pActor->nTeamNo != 0) && (user->m_channel[nChannelNo].pActor->nTeamNo == user->m_nTeamNo[i]))
						{
							user->m_TeamActor[i].bVisible = true;
							break;
						}
					}
				}
				if ((user->m_channel[nChannelNo].pActor->nVehicleSeatIdx >= 0) && (user->m_channel[nChannelNo].pActor->nVehicleSeatIdx < 4))
				{
					VehicleSeatOperation(nChannelNo, user->m_channel[nChannelNo].pActor->nAttachParent, 0xFFFFFFFF, user->m_channel[nChannelNo].pActor->nType);
				}
				delete user->m_channel[nChannelNo].pActor;
				user->m_channel[nChannelNo].pActor = NULL;
			}
			if (user->m_channel[nChannelNo].pVehicle)
			{
				delete user->m_channel[i].pVehicle;
				user->m_channel[nChannelNo].pVehicle = NULL;
			}
			if (user->m_channel[nChannelNo].pItem)
			{
				delete user->m_channel[i].pItem;
				user->m_channel[nChannelNo].pItem = NULL;
			}
			if (user->m_channel[nChannelNo].pAirDropPlane)
			{
				delete user->m_channel[nChannelNo].pAirDropPlane;
				user->m_channel[nChannelNo].pAirDropPlane = NULL;
			}
			for (i = nChannelNo; i < user->m_nChannelCnt - 1; i++)
			{
				user->m_channel[i] = user->m_channel[i + 1];
			}
			user->m_nChannelCnt--;
			user->m_channel[user->m_nChannelCnt].pItem = NULL;
			user->m_channel[user->m_nChannelCnt].pActor = NULL;
			user->m_channel[user->m_nChannelCnt].pVehicle = NULL;
			user->m_channel[user->m_nChannelCnt].pAirDropPlane = NULL;
			user->m_channel[user->m_nChannelCnt].bChannelOpen = false;
			user->m_channel[user->m_nChannelCnt].bChannelClose = false;
			user->m_channel[user->m_nChannelCnt].nChannelIndex = 0;
		}
		return true;
	}
	int MainChannelManager(UINT32 nChannelIndex)
	{
		int i = 0;
		for (i = 0; i < user->m_nChannelCnt; i++)
		{
			if (user->m_channel[i].nChannelIndex == nChannelIndex)
			{
				break;
			}
		}
		if (i == user->m_nChannelCnt)
		{
			user->m_channel[i].nChannelIndex = nChannelIndex;
			if (user->m_channel[i].nChannelIndex == 3)
			{
				user->m_channel[i].bChannelOpen = true;
				InsertActorToChannel(i);
			}
			user->m_nChannelCnt++;
		}
		return i;
	}
	void AddShootInfo(float fImpactXPos, float fImpactYPos, float fImpactZPos, float fMuzzleXPos, float fMuzzleYPos, float fMuzzleZPos)
	{
		if (user == nullptr)
			return;
		if (user->m_nShootInfoCnt >= 1000)
		{
			return;
		}
		int i = 0;
		if (user->m_nShootInfoCnt > 0)
		{
			for (i = user->m_nShootInfoCnt - 1; i >= 0; i--)
			{
				user->m_arShootInfo[i + 1].fImpactXPos = user->m_arShootInfo[i].fImpactXPos;
				user->m_arShootInfo[i + 1].fImpactYPos = user->m_arShootInfo[i].fImpactYPos;
				user->m_arShootInfo[i + 1].fMuzzleXPos = user->m_arShootInfo[i].fMuzzleXPos;
				user->m_arShootInfo[i + 1].fMuzzleYPos = user->m_arShootInfo[i].fMuzzleYPos;
				user->m_arShootInfo[i + 1].nTimes = user->m_arShootInfo[i].nTimes;
			}
		}
		user->m_arShootInfo[0].fImpactXPos = fImpactXPos;
		user->m_arShootInfo[0].fImpactYPos = fImpactYPos;
		user->m_arShootInfo[0].fMuzzleXPos = fMuzzleXPos;
		user->m_arShootInfo[0].fMuzzleYPos = fMuzzleYPos;
		user->m_arShootInfo[0].nTimes = 30;
		user->m_nShootInfoCnt++;
	}
	void ShootManager(float fImpactXPos, float fImpactYPos, float fImpactZPos, float fMuzzleXPos, float fMuzzleYPos, float fMuzzleZPos)
	{
		float fDis = 0, fDisError = 500;
		{
			AddShootInfo(fImpactXPos, fImpactYPos, fImpactZPos, fMuzzleXPos, fMuzzleYPos, fMuzzleZPos);
		}
	}
	bool NameCmp(char* szName1, int nName1Len, char* szName2, int nName2Len)
	{
		int nCmpRes = 0;
		char* tszTemp, * tszTemp2;
		int i;
		if (nName1Len != nName2Len)
			return false;
		if (nName1Len > 0)
		{
			nCmpRes = strcmp(szName1, szName2);
			if (nCmpRes == 0)
				return true;
			else
				return false;
		}
		else
		{
			tszTemp = szName1;
			tszTemp2 = szName2;
			nCmpRes = strcmp(tszTemp, tszTemp2);
			if (nCmpRes == 0)
			{
				return true;
			}
			else
				return false;
		}
	}
	void NameManage(char* szPlayerName, int nNameLen, UINT32 nNetGUID, UINT32 nChIndex)
	{
		if (user == nullptr)
			return;
		char szTemp[256] = { 0 };
		int nActorMatchNo;
		int i = 0;
		int nTeamIndex = -1;
		ACTOR actor;
		for (i = 0; i < user->m_nActorInfoCnt; i++)
		{
			if (NameCmp(user->m_actorInfo[i].szName, user->m_actorInfo[i].nNameLen, szPlayerName, nNameLen))
			{
				break;
			}
		}
		if (i == user->m_nActorInfoCnt)
		{
			NameCpy(user->m_actorInfo[i].szName, szPlayerName, nNameLen);
			user->m_actorInfo[i].nNameLen = nNameLen;
			user->m_actorInfo[i].nNetGUID = nNetGUID == 0 ? 0 : nNetGUID;
			user->m_nActorInfoCnt++;
		}
		else if ((user->m_actorInfo[i].nNetGUID == 0x77777777) && (nNetGUID != 0x77777777))
		{
			user->m_actorInfo[i].nNetGUID = nNetGUID;
		}
	}
	void VehicleSeatOperation(int nChannelNo, UINT32 nAttachParent, UINT32 nSeatNo, BYTE byteActorType)
	{
		if (user == nullptr)
			return;
		int i = 0;
		if (nSeatNo == 0xFFFFFFFF)
		{
			if (byteActorType == 0)
			{
				user->m_myActor.dwReceiveDataTime = GetTickCountMs();
				user->m_myActor.bVisible = true;
				user->m_myActor.bVehicle = false;
			}
			user->m_channel[nChannelNo].pActor->bVisible = true;
			for (i = 0; i < user->m_nChannelCnt; i++)
			{
				if (!user->m_channel[i].pVehicle)
					continue;
				if ((user->m_channel[i].nNetGUID == user->m_channel[nChannelNo].pActor->nVehicleParent) && (user->m_channel[nChannelNo].pActor->nVehicleSeatIdx >= 0) && (user->m_channel[nChannelNo].pActor->nVehicleSeatIdx < 4))
				{
					user->m_channel[i].pVehicle->nNum[user->m_channel[nChannelNo].pActor->nVehicleSeatIdx] = 0x77777777;
					user->m_channel[i].pVehicle->nSeatCnt--;
					break;
				}
			}
		}
		else
		{
			if ((user->m_channel[nChannelNo].pActor->nVehicleSeatIdx >= 0) && (user->m_channel[nChannelNo].pActor->nVehicleSeatIdx < 4))
			{
				for (i = 0; i < user->m_nChannelCnt; i++)
				{
					if (!user->m_channel[i].pVehicle)
						continue;
					if ((user->m_channel[i].nNetGUID == user->m_channel[nChannelNo].pActor->nVehicleParent) && (user->m_channel[nChannelNo].pActor->nVehicleSeatIdx >= 0) && (user->m_channel[nChannelNo].pActor->nVehicleSeatIdx < 4))
					{
						user->m_channel[i].pVehicle->nNum[user->m_channel[nChannelNo].pActor->nVehicleSeatIdx] = 0x77777777;
						user->m_channel[i].pVehicle->nNum[nSeatNo] = byteActorType;
						break;
					}
				}
			}
			else
			{
				if (byteActorType == 0)
				{
					user->m_myActor.bVisible = false;
					user->m_myActor.bVehicle = true;
				}
				user->m_channel[nChannelNo].pActor->bVisible = false;
				for (i = 0; i < user->m_nChannelCnt; i++)
				{
					if (!user->m_channel[i].pVehicle)
						continue;
					if ((user->m_channel[i].nNetGUID == nAttachParent))
					{
						user->m_channel[i].pVehicle->nNum[nSeatNo] = byteActorType;
						user->m_channel[i].pVehicle->nSeatCnt++;
						break;
					}
				}
			}

		}
		user->m_channel[nChannelNo].pActor->nVehicleSeatIdx = nSeatNo;
		user->m_channel[nChannelNo].pActor->nVehicleParent = nAttachParent;
	}
	BOOL ChangeTeammateActor(ACTOR actor)
	{
		if (user == nullptr)
			return FALSE;
		int i = 0;
		for (i = 0; i < user->m_nTeammateCnt; i++)
		{
			if (user->m_nTeamRealID[i] == actor.nStateID)
			{
			}
		}
		return TRUE;
	}
	int CheckItemTypeGUID(UINT32 nTypeGUID)
	{
		if (user == nullptr)
			return -1;
		int i = 0;
		for (i = 0; i < user->m_nItemTypeGUIDCnt; i++)
		{
			if (user->m_arItemTypeGUID[i].nTypeGUID == nTypeGUID)
			{
				return user->m_arItemTypeGUID[i].nIDIndex;
			}
		}
		return -1;
	}
	bool InsertVehicleToChannel(int nChannelNo, UINT32 nGUID, UINT32 nTypeGUID)
	{
		if (user == nullptr)
			return false;
		if (user->m_channel[nChannelNo].pVehicle == NULL)
		{
			user->m_channel[nChannelNo].pVehicle = new VEHICLE_INFO();
			user->m_channel[nChannelNo].pVehicle->nTypeGUID = nTypeGUID;
		}
	}
	void InsertItemToChannel(int nChannelNo, UINT32 nTypeGUID, int nItemIndex)
	{
		if (user == nullptr)
			return;
		if (user->m_channel[nChannelNo].pItem == NULL)
		{
			user->m_channel[nChannelNo].pItem = new ITEM();
			user->m_channel[nChannelNo].pItem->nTypeGUID = nTypeGUID;
			user->m_channel[nChannelNo].pItem->nItemIndex = nItemIndex;
		}
	}
	bool CheckVehicleTypeGUID(UINT32 nTypeGUID)
	{
		if (user == nullptr)
			return false;
		int  i;
		for (i = 0; i < user->m_nVehicleTypeGUIDCnt; i++)
		{
			if (user->m_arVehicleTypeGUID[i] == nTypeGUID)
				return true;
		}
		return false;
	}
	void InsertActorToChannel(int nChannelNo)
	{
		if (user == nullptr)
			return;
		if (user->m_channel[nChannelNo].pActor == NULL)
		{
			user->m_channel[nChannelNo].pActor = new ACTOR();
			user->m_channel[nChannelNo].pActor->nType = 2;
		}
	}

	void InsertAirDropPlaneToChannel(int nChannelNo)
	{
		if (user == nullptr)
			return;
		if (user->m_channel[nChannelNo].pAirDropPlane == NULL)
		{
			user->m_channel[nChannelNo].pAirDropPlane = new AIR_DROP_PLANE();
		}
	}

	void ItemTypeRegist(OBJECT obj)
	{
		if (user == nullptr)
			return;
		int nItemIndex = -1;
		int i = 0;
		if (strstr(obj.szPathName, "Default__") != NULL)
		{
			if (strstr(obj.szPathName, "BP_AirDropBox_") != NULL)
			{
				nItemIndex = ITEMINDEX_CRATEBOX;
			}
			else if (strstr(obj.szPathName, "Rifle_AKM") != NULL)
			{
				nItemIndex = ITEMINDEX_AKM;
			}
			else if (strstr(obj.szPathName, "MK14") != NULL)
			{
				nItemIndex = ITEMINDEX_MK14;
			}
			else if (strstr(obj.szPathName, "MK47") != NULL)
			{
				nItemIndex = ITEMINDEX_MK47;
			}
			else if (strstr(obj.szPathName, "M249") != NULL)
			{
				nItemIndex = ITEMINDEX_M249;
			}
			else if (strstr(obj.szPathName, "Rifle_SCAR") != NULL)
			{
				nItemIndex = ITEMINDEX_SCAR;
			}
			else if (strstr(obj.szPathName, "Rifle_M416") != NULL)
			{
				nItemIndex = ITEMINDEX_M416;
			}
			else if (strstr(obj.szPathName, "Rifle_QBZ") != NULL)
			{
				nItemIndex = ITEMINDEX_QBZ;
			}
			else if (strstr(obj.szPathName, "Rifle_M762") != NULL)
			{
				nItemIndex = ITEMINDEX_M762;
			}
			else if (strstr(obj.szPathName, "Rifle_AUG") != NULL)
			{
				nItemIndex = ITEMINDEX_AUG;
			}
			else if (strstr(obj.szPathName, "Rifle_M16A4") != NULL)
			{
				nItemIndex = ITEMINDEX_M16A4;
			}
			else if (strstr(obj.szPathName, "Sniper_VSS") != NULL)
			{
				nItemIndex = ITEMINDEX_VSS;
			}
			else if (strstr(obj.szPathName, "Sniper_QBU") != NULL)
			{
				nItemIndex = ITEMINDEX_QBU;
			}
			else if (strstr(obj.szPathName, "Sniper_Mini14") != NULL)
			{
				nItemIndex = ITEMINDEX_MINI14;
			}
			else if (strstr(obj.szPathName, "Sniper_Kar98k") != NULL)
			{
				nItemIndex = ITEMINDEX_KAR98K;
			}
			else if (strstr(obj.szPathName, "Sniper_SKS") != NULL)
			{
				nItemIndex = ITEMINDEX_SKS;
			}
			else if (strstr(obj.szPathName, "Sniper_SLR") != NULL)
			{
				nItemIndex = ITEMINDEX_SLR;
			}
			else if (strstr(obj.szPathName, "Sniper_AWM") != NULL)
			{
				nItemIndex = ITEMINDEX_AWM;
			}
			else if (strstr(obj.szPathName, "Sniper_M24") != NULL)
			{
				nItemIndex = ITEMINDEX_M24;
			}
			else if (strstr(obj.szPathName, "MachineGun_TommyGun") != NULL)
			{
				nItemIndex = ITEMINDEX_TOMMYGUN;
			}
			else if (strstr(obj.szPathName, "MachineGun_UMP9") != NULL)
			{
				nItemIndex = ITEMINDEX_UMP;
			}
			else if (strstr(obj.szPathName, "MachineGun_Vector") != NULL)
			{
				nItemIndex = ITEMINDEX_VECTOR;
			}
			else if (strstr(obj.szPathName, "MachineGun_Uzi") != NULL)
			{
				nItemIndex = ITEMINDEX_UZI;
			}
			else if (strstr(obj.szPathName, "ShotGun_S686") != NULL)
			{
				nItemIndex = ITEMINDEX_S686;
			}
			else if (strstr(obj.szPathName, "ShotGun_S1897") != NULL)
			{
				nItemIndex = ITEMINDEX_S189;
			}
			else if (strstr(obj.szPathName, "ShotGun_S12K") != NULL)
			{
				nItemIndex = ITEMINDEX_S12K;
			}
			else if (strstr(obj.szPathName, "Pistol_Flaregun") != NULL)
			{
				nItemIndex = ITEMINDEX_FLARE;
			}
			else if (strstr(obj.szPathName, "Other_DP28") != NULL)
			{
				nItemIndex = ITEMINDEX_DP28;
			}
			else if (strstr(obj.szPathName, "Other_CrossBow") != NULL)
			{
				nItemIndex = ITEMINDEX_CROSSBOW;
			}
			else if (strstr(obj.szPathName, "Ammo_9mm") != NULL)
			{
				nItemIndex = ITEMINDEX_AMMO9;
			}
			else if (strstr(obj.szPathName, "Ammo_556mm") != NULL)
			{
				nItemIndex = ITEMINDEX_AMMO556;
			}
			else if (strstr(obj.szPathName, "Ammo_762mm") != NULL)
			{
				nItemIndex = ITEMINDEX_AMMO762;
			}
			else if (strstr(obj.szPathName, "Ammo_45ACP_") != NULL)
			{
				nItemIndex = ITEMINDEX_AMMO45ACP;
			}
			else if (strstr(obj.szPathName, "Ammo_12Guage_") != NULL)
			{
				nItemIndex = ITEMINDEX_AMMO12GAUGE;
			}
			else if (strstr(obj.szPathName, "Ammo_Bolt") != NULL)
			{
				nItemIndex = ITEMINDEX_BOLT;
			}
			else if (strstr(obj.szPathName, "Sniper_Suppressor") != NULL)
			{
				nItemIndex = ITEMINDEX_SNISUP;
			}
			else if (strstr(obj.szPathName, "Large_Suppressor") != NULL)
			{
				nItemIndex = ITEMINDEX_ARSUP;
			}
			else if (strstr(obj.szPathName, "Mid_Suppressor") != NULL)
			{
				nItemIndex = ITEMINDEX_SMGSUP;
			}
			else if (strstr(obj.szPathName, "Small_Suppressor") != NULL)
			{
				nItemIndex = ITEMINDEX_PISSUP;
			}
			else if (strstr(obj.szPathName, "Sniper_FlashHider") != NULL)
			{
				nItemIndex = ITEMINDEX_SNIFLASH;
			}
			else if (strstr(obj.szPathName, "Large_FlashHider") != NULL)
			{
				nItemIndex = ITEMINDEX_ARFLASH;
			}
			else if (strstr(obj.szPathName, "Mid_FlashHider") != NULL)
			{
				nItemIndex = ITEMINDEX_SMGFLASH;
			}
			else if (strstr(obj.szPathName, "Sniper_Compensator") != NULL)
			{
				nItemIndex = ITEMINDEX_SNICOM;
			}
			else if (strstr(obj.szPathName, "Large_Compensator") != NULL)
			{
				nItemIndex = ITEMINDEX_ARCOM;
			}
			else if (strstr(obj.szPathName, "Mid_Compensator") != NULL)
			{
				nItemIndex = ITEMINDEX_SMGCOM;
			}
			else if (strstr(obj.szPathName, "MZJ_8X") != NULL)
			{
				nItemIndex = ITEMINDEX_X8;
			}
			else if (strstr(obj.szPathName, "MZJ_6X") != NULL)
			{
				nItemIndex = ITEMINDEX_X6;
			}
			else if (strstr(obj.szPathName, "MZJ_4X") != NULL)
			{
				nItemIndex = ITEMINDEX_X4;
			}
			else if (strstr(obj.szPathName, "MZJ_3X") != NULL)
			{
				nItemIndex = ITEMINDEX_X3;
			}
			else if (strstr(obj.szPathName, "MZJ_2X") != NULL)
			{
				nItemIndex = ITEMINDEX_X2;
			}
			else if (strstr(obj.szPathName, "MZJ_QX") != NULL)
			{
				nItemIndex = ITEMINDEX_HOLOSIGHT;
			}
			else if (strstr(obj.szPathName, "MZJ_HD") != NULL)
			{
				nItemIndex = ITEMINDEX_REDSIGHT;
			}
			else if (strstr(obj.szPathName, "Helmet_Lv3") != NULL)
			{
				nItemIndex = ITEMINDEX_HELMETLV3;
			}
			else if (strstr(obj.szPathName, "Helmet_Lv2") != NULL)
			{
				nItemIndex = ITEMINDEX_HELMETLV2;
			}
			else if (strstr(obj.szPathName, "Helmet_Lv1") != NULL)
			{
				nItemIndex = ITEMINDEX_HELMETLV1;
			}
			else if (strstr(obj.szPathName, "Bag_Lv3") != NULL)
			{
				nItemIndex = ITEMINDEX_BAGLV3;
			}
			else if (strstr(obj.szPathName, "Bag_Lv2") != NULL)
			{
				nItemIndex = ITEMINDEX_BAGLV2;
			}
			else if (strstr(obj.szPathName, "Bag_Lv1") != NULL)
			{
				nItemIndex = ITEMINDEX_BAGLV1;
			}
			else if (strstr(obj.szPathName, "Armor_Lv3") != NULL)
			{
				nItemIndex = ITEMINDEX_ARMMORLV3;
			}
			else if (strstr(obj.szPathName, "Armor_Lv2") != NULL)
			{
				nItemIndex = ITEMINDEX_ARMMORLV2;
			}
			else if (strstr(obj.szPathName, "Armor_Lv1") != NULL)
			{
				nItemIndex = ITEMINDEX_ARMMORLV1;
			}
			else if (strstr(obj.szPathName, "Firstaid_") != NULL)
			{
				nItemIndex = ITEMINDEX_FIRSTKIT;
			}
			else if (strstr(obj.szPathName, "FirstAidbox_") != NULL)
			{
				nItemIndex = ITEMINDEX_MEDKIT;
			}

			else if (strstr(obj.szPathName, "Bandage_") != NULL)
			{
				nItemIndex = ITEMINDEX_BANDAGE;
			}
			else if (strstr(obj.szPathName, "Injection_") != NULL)
			{
				nItemIndex = ITEMINDEX_INJECTION;
			}
			else if (strstr(obj.szPathName, "Pills_") != NULL)
			{
				nItemIndex = ITEMINDEX_PILLS;
			}
			else if (strstr(obj.szPathName, "Drink_") != NULL)
			{
				nItemIndex = ITEMINDEX_DRINK;
			}
			else if (strstr(obj.szPathName, "Grenade_Smoke_") != NULL)
			{
				nItemIndex = ITEMINDEX_SMOKE;
			}
			else if (strstr(obj.szPathName, "Grenade_Stun_") != NULL)
			{
				nItemIndex = ITEMINDEX_STUN;
			}
			else if (strstr(obj.szPathName, "Grenade_Shoulei_") != NULL)
			{
				nItemIndex = ITEMINDEX_FRAG;
			}
			else if (strstr(obj.szPathName, "Grenade_Burn_") != NULL)
			{
				nItemIndex = ITEMINDEX_MOLOTOV;
			}

			if (nItemIndex != -1)
			{
				for (i = 0; i < user->m_nItemTypeGUIDCnt; i++)
				{
					if (user->m_arItemTypeGUID[i].nTypeGUID == obj.nGUID)
					{
						break;
					}
				}
				if ((i == user->m_nItemTypeGUIDCnt) && (user->m_nItemTypeGUIDCnt < 1000))
				{
					user->m_arItemTypeGUID[i].nTypeGUID = obj.nGUID;
					user->m_arItemTypeGUID[i].nIDIndex = nItemIndex;
					user->m_nItemTypeGUIDCnt++;
				}
			}
		}
	}


	void ResetTeammateInfo()
	{
		if (user == nullptr)
			return;
		int i = 0;
		user->m_bTeamInfoResetF = true;
		for (i = 0; i < user->m_nTeammateCnt; i++)
		{
			user->m_nTeamNetGUIDTemp[i] = user->m_nTeamNetGUID[i];
			user->m_nTeamNetGUID[i] = 0x77777777;
			user->m_nTeamRealIDTemp[i] = user->m_nTeamRealID[i];
			user->m_nTeamRealID[i] = -1;
			user->m_nTeammateCntTemp = user->m_nTeammateCnt;
			user->m_nTeamNo[i] = 0;
			user->m_TeamActor[i].Reset();
		}
		user->m_nTeammateCnt = 0;
	}
	void NameCpy(char* szDstName, char* szSrcName, int nNameLen)
	{
		if (nNameLen > 0)
		{
			memcpy(szDstName, szSrcName, nNameLen);
		}
		else if (nNameLen < 0)
		{
			memcpy(szDstName, szSrcName, (-nNameLen) * 2);
		}
	}
	void ShiftBuffer(BYTE* OutStr, BYTE* InStr, int nBuflen, int nShiftCnt)
	{
		int i = 0;
		int nRevShift = (8 - nShiftCnt) & 0x7;
		BYTE hi, lo;
		if (nShiftCnt == 0)
		{
			memcpy(OutStr, InStr, nBuflen);
			return;
		}
		for (i = 0; i < nBuflen - 1; i++)
		{
			lo = (InStr[i] >> nShiftCnt);
			hi = (InStr[i + 1] << nRevShift);
			OutStr[i] = hi | lo;
		}
		OutStr[i] = (InStr[i] >> nShiftCnt);
	}

};
#define MAX_CHSEQUENCE 4096			
#define MAX_PACKETID 0x4000
#define MAX_CHANNELS 10240
enum EChannelType
{
	CHTYPE_None = 0,
	CHTYPE_Control = 1,
	CHTYPE_Actor = 2,

	CHTYPE_File = 3,

	CHTYPE_Voice = 4,
	CHTYPE_MAX = 8,
};


class CReceiveDataParsing
{
public:
	CReceiveDataParsing() { m_nPreHandle = 0; m_nItemTypeCnt = 0; };
	CBitReader Reader;
	UINT32 InPacketId;
	UINT32 m_nPreHandle;
	ACTOR m_actor;
	UINT32 m_nChannelIndex;
	int m_nChannelNo;
	ITEM_TYPE_ID m_itemTypeId[500];
	int m_nItemTypeCnt;
	char m_szPlayerName[100];
	int m_nPlayerNameLen;
	bool m_bReadIsEngineStarted;
	UINT8 m_type2Byte;
	UINT8 m_type3Bit;
	float m_type4Float;
	UINT32 m_type5Dword;
	BYTE m_type6Byte;
	FName m_type7Name;
	UINT32 m_type8Obj;
	UINT32 m_type9Dword;
	float m_type10FloatX;
	float m_type10FloatY;
	float m_type10FloatZ;
	FROTATOR m_type11FR;
	FVECTOR m_type13FV;
	FVECTOR m_type15FvLoc;
	FVECTOR m_type15FvVelocity;
	FROTATOR m_type15FrRot;
	char m_type19Str[1024];
	int m_type19StrRes;
	int m_type19StrLen;
	DWORD m_type21Dword;
	float m_type22FloatX;
	float m_type22FloatY;
	bool m_bReceiveYaw;
	bool m_bPacketTruncate;
	bool m_bShootDir2D;
	bool m_bActorGUID;
	bool m_bComponent;
	bool m_bImpactActorPos;
	bool m_bShootMomentMuzzlePos;
	float m_fShootDirX;
	float m_fShootDirY;
	DWORD m_nActorGUID;
	DWORD m_nComponent;
	bool m_bFlyingSpeed;
	float m_fFlyingSpeed;
	bool m_bFlyingDirection;
	float m_fFlyingDirX;
	float m_fFlyingDirY;
	FVECTOR m_fvImpactPos;
	FVECTOR m_fvMuzzlePos;
	bool m_bReadMyPlayerName;
	bool m_bReadWeatherName;
	char m_szMyPlayerName[300];
	int m_nMyPlayerNameLen;
	char m_szWeatherName[300];
	int m_nWeatherNameLen;
	void Find_MapIndex(FInBunch& Bunch, user_container* radar = NULL)
	{
		int i;
		bool bReadBlockRet = false, bOutHasRepLayout = false;
		int nReadBlockRet = 0;
		CBitReader OutPayload;
		UINT32 NumPayloadBits = 0;
		char szBuf[1024];
		int nBufLen;
		UINT32 nWaitingHandle = 0, nPreHandle = 0;
		bool bRes;
		ACTOR actor;
		int nPropertyCnt = 0;
		int nStrRet = 0;
		m_bReadMyPlayerName = false;
		m_bReadWeatherName = false;
		if (Bunch.nNum < 8 * 32)
		{
			return;
		}
		for (i = 8; i < Bunch.nNum - 8 * 32; i++)
		{
			Bunch.nPos = i;

			{
				m_bReadWeatherName = false;
				m_bReadMyPlayerName = false;
				ProcessCmdInitHandle();
				bRes = ReadNextHandle(Bunch, nWaitingHandle);
				while (nWaitingHandle && bRes && (!Bunch.AtEnd()))
				{
					bRes = FRepLayoutCmdIterator_ProcessCmd_FindInitInfo(Bunch, nWaitingHandle, nPreHandle, radar, &actor);
					nPropertyCnt++;
					nPreHandle = nWaitingHandle;
					if (bRes)
						bRes = ReadNextHandle(Bunch, nWaitingHandle);
					if (nWaitingHandle > 0x30)
						break;
				}

				if (m_bReadMyPlayerName && m_bReadWeatherName)
				{
					radar->NameCpy(radar->user->m_szMyActorName, m_szMyPlayerName, m_nMyPlayerNameLen);
					radar->user->m_nMyActorNameLen = m_nMyPlayerNameLen;



					if (m_nWeatherNameLen > 0)
					{
						if (strstr(m_szWeatherName, "PUBG_Forest"))
						{
							radar->user->m_bReadWeatherNameSuccess = true;
							radar->user->m_nMapIndex = 1;
						}
						else if (strstr(m_szWeatherName, "PUBG_Desert"))
						{
							radar->user->m_bReadWeatherNameSuccess = true;
							radar->user->m_nMapIndex = 2;
						}
						else if (strstr(m_szWeatherName, "PUBG_Savage"))
						{
							radar->user->m_bReadWeatherNameSuccess = true;
							radar->user->m_nMapIndex = 3;
						}
					}
					break;
				}
				if (Bunch.IsError())
					continue;
			}
		}
	}
	void UChannel_ReceivedRawBunch(FInBunch& Bunch, user_container* radar = NULL)
	{
		UINT32 pPos[50];
		UINT32 nPosCnt;
		OBJECT Obj[50];
		UINT32 nObjCnt = 0;
		int i, j;
		int nBufLen = 0;
		UINT32 nPosTemp = 0;




		if (radar)
		{
			if ((radar->user->m_bReadWeatherNameSuccess == false))
			{
				nPosTemp = Bunch.nPos;
				Find_MapIndex(Bunch, radar);
				Bunch.nPos = nPosTemp;
			}
		}


		if (Bunch.bHasPackageMapExports)
		{

			if (!UPackageMapClient_ReceiveNetGUIDBunch(Bunch, Obj, &nObjCnt))
				return;
			for (i = 0; i < nObjCnt; i++)
			{
				printf("Obj: %d = %s\n", i, Obj[i].szPathName);


				if (radar)
				{
					if (radar->user->m_nMapIndex == 0)
					{
						if (strstr(Obj[i].szPathName, "PUBG_Forest") != NULL)
						{
							radar->user->m_nMapIndex = 1;
							radar->user->m_nVirtualWidth = 800000;
							radar->user->m_nVirtualHeight = 800000;
						}
						else if (strstr(Obj[i].szPathName, "PUBG_Desert") != NULL)
						{
							radar->user->m_nMapIndex = 2;
							radar->user->m_nVirtualWidth = 800000;
							radar->user->m_nVirtualHeight = 800000;
						}
						else if (strstr(Obj[i].szPathName, "PUBG_Savage") != NULL)
						{
							radar->user->m_nMapIndex = 3;
							{
								radar->user->m_nVirtualWidth = 800000;
								radar->user->m_nVirtualHeight = 800000;
							}
						}
					}

					if ((strstr(Obj[i].szPathName, "Default__") != NULL) && ((strstr(Obj[i].szPathName, "VH_") != NULL) || (strstr(Obj[i].szPathName, "AquaRail") != NULL) || (strstr(Obj[i].szPathName, "PickUp_0") != NULL) || (strstr(Obj[i].szPathName, "PickUp_1") != NULL) || (strstr(Obj[i].szPathName, "Mirado") != NULL) || (strstr(Obj[i].szPathName, "Rony_") != NULL)))
					{
						for (j = 0; j < radar->user->m_nVehicleTypeGUIDCnt; j++)
						{
							if (radar->user->m_arVehicleTypeGUID[j] == Obj[i].nGUID)
							{
								break;
							}
						}
						if ((j == radar->user->m_nVehicleTypeGUIDCnt) && (j < 1000))
						{
							radar->user->m_arVehicleTypeGUID[j] = Obj[i].nGUID;
							radar->user->m_nVehicleTypeGUIDCnt++;
						}
					}
				}

				if (strstr(Obj[i].szPathName, "BP_PlayerPawn") != NULL)
				{
					radar->user->m_nPlayerGUID = Obj[i].nGUID;
				}
				else if (strstr(Obj[i].szPathName, "BP_AirDropPlane") != NULL)
				{
					radar->user->m_nAirDropGUID = Obj[i].nGUID;
				}
				else if (strstr(Obj[i].szPathName, "BP_PlaneCharacter") != NULL)
				{
					radar->ResetTeammateInfo();
				}
				else
				{
					radar->ItemTypeRegist(Obj[i]);
				}
			}
		}
		else
		{
			ProcessBunch(Bunch, pPos, &nPosCnt, radar);
		}
	}
	unsigned int InternalLoadObject(CBitReader& Ar, int InternalLoadObjectRecursionCount)
	{
		if (InternalLoadObjectRecursionCount > 16)
		{
			return 0;
		}
		unsigned int NetGUID;
		Ar.ReadByteData((BYTE*)& NetGUID, 4);
		if (Ar.IsError())
			return 0;
		if (!(NetGUID > 0))
		{
			return NetGUID;
		}
		UINT8 ExportFlags_value;

		if ((NetGUID == 1))
		{
			Ar.ReadByteData((BYTE*)& ExportFlags_value, 1);
			if (Ar.IsError())
				return 0;
		}
		if (ExportFlags_value & 0x01)
		{
			unsigned int OuterGUID = InternalLoadObject(Ar, InternalLoadObjectRecursionCount + 1);

			char PathName[1024];
			int nPathNameLen = 0;
			unsigned int NetworkChecksum = 0;

			nPathNameLen = Ar.ReadString(PathName);
			if (Ar.IsError())
				return 0;
			if (ExportFlags_value & 0x04)
			{
				Ar.ReadByteData((BYTE*)& NetworkChecksum, 4);
				if (Ar.IsError())
					return 0;
			}
		}
		return NetGUID;
	}
	UINT32 UPackageMapClient_InternalLoadObject(CBitReader& Ar, int InternalLoadObjectRecursionCount, OBJECT& outObj)
	{
		BOOL GuidCache_IsExportingNetGUIDBunch = TRUE;
		OBJECT otherObj;
		if (InternalLoadObjectRecursionCount > 16)
		{
			return 0xFFFFFFFF;
		}
		UINT32 NetGUID;
		Ar.SerializeIntPacked(NetGUID);
		if (Ar.IsOver())
			return 0xFFFFFFFF;
		if (NetGUID == 0)
		{
			return NetGUID;
		}
		UINT8 ExportFlags_value;

		if ((NetGUID == 1) || (GuidCache_IsExportingNetGUIDBunch))
		{
			Ar.ReadByteData((BYTE*)& ExportFlags_value, 1);
			if (Ar.IsOver())
				return 0xFFFFFFFF;
		}
		if (ExportFlags_value & 0x01)
		{
			UINT32 OuterGUID = UPackageMapClient_InternalLoadObject(Ar, InternalLoadObjectRecursionCount + 1, otherObj);
			if (OuterGUID == 0xFFFFFFFF)
			{
				return 0xFFFFFFFF;
			}

			char PathName[1024] = { 0 };
			int nStrType = 0;
			unsigned int NetworkChecksum = 0;

			nStrType = Ar.ReadString(PathName);
			if (nStrType == 1)
			{
				memcpy(outObj.szPathName, PathName, strlen(PathName));
			}
			else
				return 0xFFFFFFFF;
			if (Ar.IsOver())
				return 0xFFFFFFFF;
			if (ExportFlags_value & 0x04)
			{
				Ar.ReadByteData((BYTE*)& NetworkChecksum, 4);
				if (Ar.IsOver())
					return 0xFFFFFFFF;
			}
		}
		outObj.nGUID = NetGUID;
		return NetGUID;
	}
	BOOL UPackageMapClient_ReceiveNetGUIDBunch(CBitReader& Ar, OBJECT* pObj = NULL, UINT32* nObjCnt = NULL, user_container* pRadar = NULL)
	{
		Ar.ReadBit();
		const bool bHasRepLayoutExport = Ar.ReadBit() == 1 ? true : false;
		static UINT32 nMaxVal = 0;
		if (nObjCnt != NULL)
			* nObjCnt = 0;
		if (bHasRepLayoutExport)
			return FALSE;
		UINT32 nNumGUIDsInBunch = 0;
		UINT32 nObjGUID;
		Ar.Serialize(&nNumGUIDsInBunch, 4);
		if (nNumGUIDsInBunch > 2048)
		{
			return FALSE;
		}
		UINT32 nNumGUIDsRead = 0;
		OBJECT Obj;
		if (nMaxVal < nNumGUIDsInBunch)
		{
			nMaxVal = nNumGUIDsInBunch;
		}
		if (nObjCnt != NULL)
			* nObjCnt = nNumGUIDsInBunch;
		if (nNumGUIDsInBunch >= 50)
		{
			return FALSE;
		}
		while (nNumGUIDsRead < nNumGUIDsInBunch)
		{
			nObjGUID = UPackageMapClient_InternalLoadObject(Ar, 0, Obj);

			if (Ar.IsOver() || (nObjGUID == 0xFFFFFFFF))
			{
				return FALSE;
			}
			if (pObj != NULL)
			{
				memcpy(pObj[nNumGUIDsRead].szPathName, Obj.szPathName, strlen(Obj.szPathName));
				pObj[nNumGUIDsRead].nGUID = Obj.nGUID;
			}
			nNumGUIDsRead++;
		}
		return TRUE;
	}
	template<unsigned int ScaleFactor, int MaxBitsPerComponent>
	bool ReadPackedVector(FVECTOR& Value, CBitReader& Ar)
	{
		unsigned int Bits = 0;

		Ar.SerializeInt(Bits, MaxBitsPerComponent);

		int Bias = 1 << (Bits + 1);
		unsigned int Max = 1 << (Bits + 2);
		unsigned int DX = 0;
		unsigned int DY = 0;
		unsigned int DZ = 0;

		Ar.SerializeInt(DX, Max);
		Ar.SerializeInt(DY, Max);
		Ar.SerializeInt(DZ, Max);

		float fact = (float)ScaleFactor;

		Value.X = (float)(static_cast<int>(DX) - Bias) / fact;
		Value.Y = (float)(static_cast<int>(DY) - Bias) / fact;
		Value.Z = (float)(static_cast<int>(DZ) - Bias) / fact;

		return true;
	}
	void SerializeCompressedShort(FROTATOR& rotator, CBitReader& Ar)
	{
		UINT16 ShortPitch = 0;
		UINT16 ShortYaw = 0;
		UINT16 ShortRoll = 0;

		UINT8 B = (ShortPitch != 0);
		Ar.SerializeBits(&B, 1);
		if (B)
		{
			Ar.ReadByteData((BYTE*)(&ShortPitch), sizeof(UINT16));
		}
		else
		{
			ShortPitch = 0;
		}

		B = (ShortYaw != 0);
		Ar.SerializeBits(&B, 1);
		if (B)
		{
			Ar.ReadByteData((BYTE*)(&ShortYaw), sizeof(UINT16));
		}
		else
		{
			ShortYaw = 0;
		}

		B = (ShortRoll != 0);
		Ar.SerializeBits(&B, 1);
		if (B)
		{
			Ar.ReadByteData((BYTE*)(&ShortRoll), sizeof(UINT16));
		}
		else
		{
			ShortRoll = 0;
		}
		rotator.Pitch = DecompressAxisFromShort(ShortPitch);
		rotator.Yaw = DecompressAxisFromShort(ShortYaw);
		rotator.Roll = DecompressAxisFromShort(ShortRoll);
	}
	void SerializeCompressed(FROTATOR& rotator, CBitReader& Ar)
	{
		BYTE ShortPitch = 0;
		BYTE ShortYaw = 0;
		BYTE ShortRoll = 0;

		UINT8 B = (ShortPitch != 0);
		Ar.SerializeBits(&B, 1);
		if (B)
		{
			Ar.ReadByteData((BYTE*)(&ShortPitch), sizeof(BYTE));
		}
		else
		{
			ShortPitch = 0;
		}

		B = (ShortYaw != 0);
		Ar.SerializeBits(&B, 1);
		if (B)
		{
			Ar.ReadByteData((BYTE*)(&ShortYaw), sizeof(BYTE));
		}
		else
		{
			ShortYaw = 0;
		}

		B = (ShortRoll != 0);
		Ar.SerializeBits(&B, 1);
		if (B)
		{
			Ar.ReadByteData((BYTE*)(&ShortRoll), sizeof(BYTE));
		}
		else
		{
			ShortRoll = 0;
		}
		rotator.Pitch = DecompressAxisFromByte(ShortPitch);
		rotator.Yaw = DecompressAxisFromByte(ShortYaw);
		rotator.Roll = DecompressAxisFromByte(ShortRoll);
	}
	float DecompressAxisFromShort(UINT16 Angle)
	{
		return (Angle * 360.f / 65536.f);
	}
	float DecompressAxisFromByte(BYTE Angle)
	{
		return (Angle * 360.f / 256.f);
	}
	void SerializeName(FName& name, CBitReader& Ar)
	{
		UINT8 bHardcoded = 0;
		Ar.SerializeBits(&bHardcoded, 1);
		if (bHardcoded)
		{
			UINT32 NameIndex;
			Ar.SerializeInt(NameIndex, MAX_NETWORKED_HARDCODED_NAME + 1);
		}
		else
		{

			char szString[1024] = { 0 };
			UINT32 InNumber;
			Ar.ReadString(szString);
			Ar.ReadByteData((BYTE*)& InNumber, 4);
			memcpy(name.szString, szString, strlen(szString));
			name.nInNumber = InNumber;
		}
	}
	template<int MaxValue, int NumBits>
	bool SerializeFixedVector(FVECTOR& Vector, CBitReader& Ar)
	{
		ReadFixedCompressedFloat<MaxValue, NumBits>(Vector.X, Ar);
		ReadFixedCompressedFloat<MaxValue, NumBits>(Vector.Y, Ar);
		ReadFixedCompressedFloat<MaxValue, NumBits>(Vector.Z, Ar);
		return true;
	}

	template<int MaxValue, int NumBits>
	bool ReadFixedCompressedFloat(float& Value, CBitReader& Ar)
	{

		enum { MaxBitValue = (1 << (NumBits - 1)) - 1 };
		enum { Bias = (1 << (NumBits - 1)) };
		enum { SerIntMax = (1 << (NumBits - 0)) };
		enum { MaxDelta = (1 << (NumBits - 0)) - 1 };

		UINT32 Delta;
		Ar.SerializeInt(Delta, SerIntMax);
		float UnscaledValue = static_cast<float>(static_cast<INT32>(Delta) - Bias);

		if (MaxValue > MaxBitValue)
		{
			const float InvScale = MaxValue / (float)MaxBitValue;
			Value = UnscaledValue * InvScale;
		}
		else
		{
			enum { scale = MaxBitValue / MaxValue };
			const float InvScale = 1.f / (float)scale;

			Value = UnscaledValue * InvScale;
		}

		return true;
	}
	bool FRepMovementNetSerialize(FVECTOR& FvLoc, FROTATOR& FrRot, FVECTOR& FvVelocity, CBitReader& Ar)
	{
		FVECTOR FvPhy;
		BOOL bSimulatedPhysicSleep = Ar.ReadBit();
		BOOL bRepPhysics = Ar.ReadBit();
		ReadPackedVector<100, 30>(FvLoc, Ar);
		SerializeCompressed(FrRot, Ar);
		ReadPackedVector<1, 24>(FvVelocity, Ar);
		if (bRepPhysics)
			ReadPackedVector<1, 24>(FvPhy, Ar);
		return TRUE;
	}
	int UActorChannel_ReadContentBlockPayload(FInBunch& Bunch, CBitReader& OutPayload, bool& bOutHasRepLayout)
	{
		bool bObjectDeleted = false;
		UINT32 NetGUID = NULL;
		UINT32 ClassNetGUID = NULL;
		bOutHasRepLayout = Bunch.ReadBit() != 0 ? true : false;
		const bool bIsActor = Bunch.ReadBit() != 0 ? true : false;
		if (bIsActor)
		{
		}
		else
		{
			Bunch.SerializeIntPacked(NetGUID);
			if ((Bunch.nPos > Bunch.nNum) && (NetGUID))
			{
				return -1;
			}
			if (Bunch.IsError())
				return 0;
			const bool bStablyNamed = Bunch.ReadBit() != 0 ? true : false;
			if (!bStablyNamed)
			{
				Bunch.SerializeIntPacked(ClassNetGUID);
				if (Bunch.nPos > Bunch.nNum)
					return 0;
				if (ClassNetGUID <= 0)
				{
					bObjectDeleted = true;
				}
			}
		}
		if (bObjectDeleted)
		{
			OutPayload.SetData(Bunch, 0);

			return 0;
		}
		UINT32 NumPayloadBits = 0;
		Bunch.SerializeIntPacked(NumPayloadBits);
		if ((Bunch.IsError()) || (NumPayloadBits > 0x3000) || ((NumPayloadBits > 0) && (NumPayloadBits < 12)))
		{
			return -1;
		}
		if ((NumPayloadBits + Bunch.nPos > Bunch.nNum))
		{
			m_bPacketTruncate = true;
			NumPayloadBits = Bunch.nNum - Bunch.nPos;
		}
		OutPayload.SetData(Bunch, NumPayloadBits);
		return 1;
	}
	void SerializeNewActor(CBitReader& Reader, UINT32& NetGUID, UINT32& ArchetypeNetGUID, FVECTOR& fvLoc, FROTATOR& frRot, FVECTOR& fvVel, char* szOutPathName, int* nOutPathNameLen, int* nOutTeamNo)
	{
		BYTE bSerializeLocation = 0, bSerializeRotation = 0, bSerializeScale = 0, bSerializeVelocity = 0;
		Reader.SerializeIntPacked(NetGUID);
		FVECTOR fvFV;
		UINT32 nPosTemp = 0;
		char szPathName[1024] = { 0 };
		int nRes = 0;
		int nPathNameLen = 0;
		UINT32 nTeamNo;
		if (NetGUID > 0 && !(NetGUID & 1))
		{
			Reader.SerializeIntPacked(ArchetypeNetGUID);
			Reader.SerializeBits(&bSerializeLocation, 1);
			if (bSerializeLocation)
			{
				ReadPackedVector<10, 24>(fvLoc, Reader);
			}

			Reader.SerializeBits(&bSerializeRotation, 1);
			if (bSerializeRotation)
			{
				SerializeCompressedShort(frRot, Reader);
			}

			Reader.SerializeBits(&bSerializeScale, 1);
			if (bSerializeScale)
			{
				ReadPackedVector<10, 24>(fvFV, Reader);
			}

			Reader.SerializeBits(&bSerializeVelocity, 1);
			if (bSerializeVelocity)
			{
				ReadPackedVector<10, 24>(fvVel, Reader);
			}
			nPosTemp = Reader.nPos;
			nRes = Reader.ReadString(szPathName, &nPathNameLen);
			Reader.Serialize(&nTeamNo, 4);

			if ((nRes == 0) || (nTeamNo > 0x100))
			{
				Reader.nPos = nPosTemp;
			}
			else
			{
				if (nPathNameLen > 0)
				{
					memcpy(szOutPathName, szPathName, nPathNameLen);
				}
				else if (nPathNameLen < 0)
				{
					memcpy(szOutPathName, szPathName, (-nPathNameLen) * 2);
				}
				*nOutPathNameLen = nPathNameLen;
				*nOutTeamNo = nTeamNo;
			}
		}
		else
		{
		}
	}
	bool ReceivedBunch(FInBunch& Bunch)
	{
		bool client = true;
		UINT32 nGUID;
		UINT16 i = 0;
		if (client && Bunch.bHasMustBeMappedGUIDs)
		{
			UINT16 nNumMustBeMappedGUIDs = 0;
			Bunch.Serialize(&nNumMustBeMappedGUIDs, 2);
			if (nNumMustBeMappedGUIDs > 6)
			{
				return false;
			}
			for (i = 0; i < nNumMustBeMappedGUIDs; i++)
			{
				Bunch.SerializeIntPacked(nGUID);
			}
		}
		return true;
	}
	bool checkReadBlockPayloadSuccess(int nBunch_Pos, int nBunch_Num, int nReadBlockRet)
	{
		bool bRet = true;
		if ((nReadBlockRet == -1) || ((nReadBlockRet == 0) && (nBunch_Num - 7 > nBunch_Pos)))
		{
			bRet = false;
		}
		return bRet;
	}
	bool FObjectReplicator_ReceivedBunch(CBitReader& Ar, bool bHasRepLayout, user_container* Radar = NULL)
	{
		bool bRet = false;
		if (bHasRepLayout)
		{
			Radar->user->g_bLoc = false;
			Radar->user->g_bExternStringDetect = false;
			bRet = ReceiveProperties(Ar, Radar);
		}
		else
		{
			bRet = ReceivedForRPC(Ar, Radar);
		}
		return bRet;
	}
	uint64_t GetTickCountMs()
	{
		struct timespec ts;

		//clock_gettime(CLOCK_MONOTONIC, &ts);

		return (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
	}
	bool ProcessBunch(FInBunch& Bunch, UINT32* pPos, UINT32* nPosCnt, user_container* Radar = NULL)
	{
		UINT32 NetGUID, ArcheTypeNetGUID;
		FVECTOR fvLoc;
		FROTATOR frRot;
		FVECTOR fvVel;
		CBitReader OutPayload;
		UINT32 nPosTemp;
		char szSerializePathName[1024];
		int nSerializePathNameLen = 0;
		int nSerializeTeamNo = 0;

		int nReadBlockRet = 0;
		bool bOutHasRepLayout = false;
		int nItemIndex = -1;
		bool bCheck = false, bCheck1 = true, bCheck2 = true, bCheck3 = true, bCheck4 = true;
		UINT32 nPosCntTemp = 0;
		int i = 0;
		if (Bunch.bHasMustBeMappedGUIDs)
		{
			bCheck1 = ReceivedBunch(Bunch);
			if (bCheck1 == false)
			{
				Bunch.nPos;
			}
		}
		nPosTemp = Bunch.nPos;
		{
			Bunch.nPos = nPosTemp;
			nPosCntTemp = 0;
			{
				Bunch.nPos = nPosTemp;
				m_bPacketTruncate = false;
				while (!Bunch.AtEnd())
				{
					nReadBlockRet = UActorChannel_ReadContentBlockPayload(Bunch, OutPayload, bOutHasRepLayout);
					if (nReadBlockRet == 1)
						FObjectReplicator_ReceivedBunch(OutPayload, bOutHasRepLayout, Radar);
				}
			}
		}

		{
			{
				Bunch.nPos = nPosTemp;
				NetGUID = 0; ArcheTypeNetGUID = 0;
				SerializeNewActor(Bunch, NetGUID, ArcheTypeNetGUID, fvLoc, frRot, fvVel, szSerializePathName, &nSerializePathNameLen, &nSerializeTeamNo);
				if (Radar)
				{
					if ((Radar->user->m_nAirDropGUID != 0) && (ArcheTypeNetGUID == Radar->user->m_nAirDropGUID))
					{
						if ((fvLoc.X < 1000000) && (fvLoc.X > -3000) && (fvLoc.Y < 1000000) && (fvLoc.Y > -3000) && (fvLoc.Z < 150001) && (fvLoc.Z > -10000))
						{
							Radar->InsertAirDropPlaneToChannel(m_nChannelNo);
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->fXPos = fvLoc.X;
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->fYPos = fvLoc.Y;
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->fZPos = fvLoc.Z;
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->fSpeed = sqrt(fvVel.X * fvVel.X + fvVel.Y * fvVel.Y);
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->fDirX = cos(frRot.Yaw * 3.141592 / 180);
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->fDirY = sin(frRot.Yaw * 3.141592 / 180);
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->bAirDropVisible = true;
							Radar->user->m_channel[m_nChannelNo].pAirDropPlane->dwGetTickCnt = GetTickCountMs();
						}
					}
				}

				if ((fvLoc.X < 800000) && (fvLoc.X > 2000) && (fvLoc.Y < 800000) && (fvLoc.Y > 2000) && (fvLoc.Z < 150001) && (fvLoc.Z > -10000))
				{

					if (Radar)
					{
						if ((ArcheTypeNetGUID == Radar->user->m_nPlayerGUID))
						{
							Radar->InsertActorToChannel(m_nChannelNo);
							for (int j = 0; j < Radar->user->m_nTeammateCnt; j++)
							{
								if ((Radar->user->m_channel[m_nChannelNo].nNetGUID == Radar->user->m_nTeamNetGUID[j]) && (Radar->user->m_nTeamNetGUID[j] != 0x77777777))
								{
									Radar->user->m_channel[m_nChannelNo].pActor->nTeamNo = Radar->user->m_nTeamNo[j];
									Radar->user->m_channel[m_nChannelNo].pActor->nType = 1;
									Radar->user->m_TeamActor[j].bVisible = false;
									break;
								}
							}
							Radar->user->m_channel[m_nChannelNo].nNetGUID = NetGUID;
							Radar->user->m_channel[m_nChannelNo].pActor->nInstigator = NetGUID;
						}
						else if (Radar->CheckVehicleTypeGUID(ArcheTypeNetGUID))
						{
							Radar->user->m_channel[m_nChannelNo].nNetGUID = NetGUID;
							Radar->user->m_channel[m_nChannelNo].nTypeNetGUID = ArcheTypeNetGUID;
							Radar->InsertVehicleToChannel(m_nChannelNo, NetGUID, ArcheTypeNetGUID);
						}
						else if ((nItemIndex = Radar->CheckItemTypeGUID(ArcheTypeNetGUID)) >= 0)
						{
							Radar->user->m_channel[m_nChannelNo].nNetGUID = NetGUID;
							Radar->user->m_channel[m_nChannelNo].nTypeNetGUID = ArcheTypeNetGUID;
							Radar->InsertItemToChannel(m_nChannelNo, ArcheTypeNetGUID, nItemIndex);
							Radar->user->m_channel[m_nChannelNo].pItem->fXPos = fvLoc.X;
							Radar->user->m_channel[m_nChannelNo].pItem->fYPos = fvLoc.Y;
							Radar->user->m_channel[m_nChannelNo].pItem->fZPos = fvLoc.Z;
							Radar->user->m_channel[m_nChannelNo].pItem->dwReceiveDataTime = GetTickCountMs();

						}
					}
				}
				m_bPacketTruncate = false;
				while (!Bunch.AtEnd())
				{
					nReadBlockRet = UActorChannel_ReadContentBlockPayload(Bunch, OutPayload, bOutHasRepLayout);
					if (nReadBlockRet == 1)
						FObjectReplicator_ReceivedBunch(OutPayload, bOutHasRepLayout, Radar);
				}
			}
		}
		bCheck = bCheck1 | bCheck2 | bCheck3 | bCheck4;
		return bCheck;
	}
	bool ReceivedForRPC(CBitReader& Reader, user_container* pRadar = NULL)
	{
		UINT8 Header = 0;
		UINT32 nPosTemp = Reader.nPos;
		UINT32 nBufSize = 0;
		UINT32 nStartPos = 0;
		bool bRes = false;
		Reader.ReadByteData(&Header, 1);

		ACTOR actor;
		if (Header == 0xF4)
		{
			UINT8 bID_f = 0, bLoc_f = 0, bView_f = 0, bHealth = 0, bRoll = 0, bVoice = 0;
			UINT32 nTeamID;
			FVECTOR fvLoc;
			UINT32 nView;
			float fHealth;
			UINT32 nVoiceID;
			UINT8 Roll;
			Reader.SerializeIntPacked(nBufSize);
			nStartPos = Reader.nPos;
			Reader.SerializeBits(&bID_f, 1);
			if (bID_f)
			{
				Reader.SerializeIntPacked(nTeamID);
			}
			Reader.SerializeBits(&bLoc_f, 1);
			if (bLoc_f)
			{
				ReadPackedVector<100, 30>(fvLoc, Reader);
			}
			Reader.SerializeBits(&bView_f, 1);
			if (bView_f)
			{
				Reader.ReadByteData((BYTE*)& nView, 4);
			}
			Reader.SerializeBits(&bRoll, 1);
			if (bRoll)
			{
				Reader.ReadByteData(&Roll, 1);
			}
			Reader.SerializeBits(&bHealth, 1);
			if (bHealth)
			{
				fHealth = Reader.ReadFloat();
			}
			Reader.SerializeBits(&bVoice, 1);
			if (bVoice)
			{
				Reader.ReadByteData((BYTE*)& nVoiceID, 4);
			}
			if ((Reader.nPos - nStartPos) == nBufSize)
				bRes = true;
			if (bRes)
			{
				actor.fXPos = fvLoc.X;
				actor.fYPos = fvLoc.Y;
				actor.fZPos = fvLoc.Z;
				actor.fYaw = (float)((nView >> 16) * 360) / 65535.0;
				if (pRadar && (nTeamID != 0) && (fvLoc.X > 10000) && (fvLoc.X < 800000) && (fvLoc.Y > 10000) && (fvLoc.Y < 800000) && (fvLoc.Z > -1000) && (fvLoc.Z < 150001))
				{
					pRadar->TeamActorManager(actor, nTeamID);
				}

			}
		}
		if (!bRes)
		{
			UINT8 bNoTime = 0;
			Reader.nPos = nPosTemp;
			bNoTime = Reader.ReadBit();
			Reader.SerializeBits(&Header, 5);
			float fWhiteXP, fWhiteYP, fWhiteR, fBlueXP, fBlueYP, fBlueR;
			float fTime, fScreenSizeFact;
			UINT32 nInvertedIndex, nIndex;
			bool bTime, bWhiteCircle, bBlueCircle, bScreenSizeFactor, bInveredIndex, bIndex;
			if ((Header & 0x3F) == 0x14)
			{
				Reader.SerializeIntPacked(nBufSize);
				nStartPos = Reader.nPos;
				if (bNoTime)
				{
					bBlueCircle = Reader.ReadBit();
					if (bBlueCircle)
					{
						fBlueXP = Reader.ReadFloat();
						fBlueYP = Reader.ReadFloat();
						fBlueR = Reader.ReadFloat();
					}
					bWhiteCircle = Reader.ReadBit();
					if (bWhiteCircle)
					{
						fWhiteXP = Reader.ReadFloat();
						fWhiteYP = Reader.ReadFloat();
						fWhiteR = Reader.ReadFloat();
					}
					bIndex = Reader.ReadBit();
					if (bIndex)
					{
						Reader.ReadByteData((BYTE*)& nIndex, 4);
					}
					Reader.ReadBit();
					bScreenSizeFactor = Reader.ReadBit();
					if (bScreenSizeFactor)
					{
						fScreenSizeFact = Reader.ReadFloat();
					}
					Reader.ReadBit();
					if ((Reader.nPos - nStartPos) == nBufSize)
						bRes = true;
				}
				else
				{
					if (nBufSize == 261)
					{
						Reader.ReadBit();
					}
					else
					{
						Reader.ReadBit();
						Reader.ReadBit();
						Reader.ReadBit();
					}
					bTime = Reader.ReadBit();
					if (bTime)
					{
						fTime = Reader.ReadFloat();
					}
					bBlueCircle = Reader.ReadBit();
					if (bBlueCircle)
					{
						fBlueXP = Reader.ReadFloat();
						fBlueYP = Reader.ReadFloat();
						fBlueR = Reader.ReadFloat();
					}
					bWhiteCircle = Reader.ReadBit();
					if (bWhiteCircle)
					{
						fWhiteXP = Reader.ReadFloat();
						fWhiteYP = Reader.ReadFloat();
						fWhiteR = Reader.ReadFloat();
					}
					bInveredIndex = Reader.ReadBit();
					if (bInveredIndex)
					{
						Reader.ReadByteData((BYTE*)& nInvertedIndex, 4);
					}
					if ((Reader.nPos - nStartPos) == nBufSize)
						bRes = true;
				}
			}
			if (bRes)
			{
				if ((fBlueXP > 1000) && (fBlueYP > 1000) && (fBlueR > 1000) && (fWhiteXP > 1000) && (fWhiteYP > 1000) && (fWhiteR > 1000))
				{
					if (pRadar)
					{
						if ((bNoTime == false) && (fTime > pRadar->user->m_CircleInfo.fTime) && (abs(fBlueR - pRadar->user->m_CircleInfo.fBlueR) < 0.01))
						{
							pRadar->user->m_CircleInfo.dwTickStartCnt = GetTickCountMs();
							pRadar->user->m_CircleInfo.bRestictionStart = true;
						}
						else if ((abs(fBlueR - pRadar->user->m_CircleInfo.fBlueR) > 0.01))
						{
							pRadar->user->m_CircleInfo.bRestictionStart = false;
							pRadar->user->m_CircleInfo.dwTickStartCnt = 0;
						}
						pRadar->user->m_CircleInfo.fBlueX = fBlueXP;
						pRadar->user->m_CircleInfo.fBlueY = fBlueYP;
						pRadar->user->m_CircleInfo.fBlueR = fBlueR;
						pRadar->user->m_CircleInfo.fWhiteX = fWhiteXP;
						pRadar->user->m_CircleInfo.fWhiteY = fWhiteYP;
						pRadar->user->m_CircleInfo.fWhiteR = fWhiteR;
						if (bNoTime == false)
						{
							pRadar->user->m_CircleInfo.fTime = fTime;
						}
					}

				}

			}
		}
		if (!bRes)
		{
			Reader.nPos = nPosTemp;
			Reader.SerializeBits(&Header, 6);
			float fRedXP, fRedYP, fRedR;
			DWORD dwIndex;
			bool bReadArea = false, bReadIndex = false;
			if (((Header & 0x3F) == 0x27))
			{
				Reader.SerializeIntPacked(nBufSize);
				nStartPos = Reader.nPos;
				bReadArea = Reader.ReadBit();
				if (bReadArea)
				{
					fRedXP = Reader.ReadFloat();
					fRedYP = Reader.ReadFloat();
					fRedR = Reader.ReadFloat();
				}
				bReadIndex = Reader.ReadBit();
				if (bReadIndex)
				{
					Reader.ReadByteData((BYTE*)& dwIndex, 4);
				}
				if (((Reader.nPos - nStartPos) == nBufSize) && bReadArea)
				{
					bRes = true;
					if (pRadar)
					{
						pRadar->user->m_AirAttackArea.fRedX = fRedXP;
						pRadar->user->m_AirAttackArea.fRedY = fRedYP;
						pRadar->user->m_AirAttackArea.fRedR = fRedR;
						pRadar->user->m_AirAttackArea.bVisible = true;
						pRadar->user->m_AirAttackArea.dwGetTickCnt = GetTickCountMs();
					}
				}
			}
		}
		if (!bRes)
		{
			UINT8 bNoTime = 0;
			Reader.nPos = nPosTemp;
			Reader.SerializeBits(&Header, 7);
			float fDis = 0, fHeight = 0, fLength = 0, fStartPosX = 0, fStartPosY = 0, fStartPosZ = 0, fCrossBlockMaxFall = 0, fCrossBlockMaxDis = 0, fHitPointX = 0, fHitPointY = 0, fHitPointZ = 0;
			UINT32 nCheckActor = 0, nMoveDir = 0;
			char szVaultKey[1024] = { 0 };
			bool bDis, bHeight, bLength, bVaultKey, bStartPos, bCheckActor, bCrossblockMaxFall, bCrossblockMaxDis, bHitPoint, bMoveDir;
			if ((Header & 0x7F) == 0x57)
			{
				Reader.SerializeIntPacked(nBufSize);
				nStartPos = Reader.nPos;
				bDis = Reader.ReadBit();
				if (bDis)
				{
					fDis = Reader.ReadFloat();
				}
				bHeight = Reader.ReadBit();
				if (bHeight)
				{
					fHeight = Reader.ReadFloat();
				}
				bLength = Reader.ReadBit();
				if (bLength)
				{
					fLength = Reader.ReadFloat();
				}
				bVaultKey = Reader.ReadBit();
				if (bVaultKey)
				{
					Reader.ReadString(szVaultKey);
				}
				bStartPos = Reader.ReadBit();
				if (bStartPos)
				{
					fStartPosX = Reader.ReadFloat();
					fStartPosY = Reader.ReadFloat();
					fStartPosZ = Reader.ReadFloat();
				}
				bCheckActor = Reader.ReadBit();
				if (bCheckActor)
				{
					Reader.SerializeIntPacked(nCheckActor);
				}
				bCrossblockMaxFall = Reader.ReadBit();
				if (bCrossblockMaxFall)
				{
					fCrossBlockMaxFall = Reader.ReadFloat();
				}
				bCrossblockMaxDis = Reader.ReadBit();
				if (bCrossblockMaxDis)
				{
					fCrossBlockMaxDis = Reader.ReadFloat();
				}
				bHitPoint = Reader.ReadBit();
				if (bHitPoint)
				{
					fHitPointX = Reader.ReadFloat();
					fHitPointY = Reader.ReadFloat();
					fHitPointZ = Reader.ReadFloat();
				}
				bMoveDir = Reader.ReadBit();
				if (bMoveDir)
				{
					Reader.SerializeBits(&nMoveDir, 19);
				}
				if ((Reader.nPos - nStartPos) == nBufSize)
					bRes = true;
			}
			if (bRes)
			{
				if ((fHitPointX > 2000) && (fHitPointX < 800000) && (fHitPointY > 2000) && (fHitPointY < 800000))
				{
				}
			}
		}
		if (!bRes)
		{
			UINT8 bNoTime = 0;
			Reader.nPos = nPosTemp;
			Reader.ReadByteData(&Header, 1);
			float fDis = 0, fHeight = 0, fLength = 0, fStartPosX = 0, fStartPosY = 0, fStartPosZ = 0, fCrossBlockMaxFall = 0, fCrossBlockMaxDis = 0, fHitPointX = 0, fHitPointY = 0, fHitPointZ = 0;
			UINT32 nCheckActor = 0, nMoveDir = 0;
			char szVaultKey[1024] = { 0 };
			bool bReadNext;
			int nStrRes = 0;
			char szCauserName[1024];
			int nCauseNameLen = 0;
			char szVictimName[1024];
			int nVictimNameLen = 0;
			char szKillerName[1024];
			int nKillerNameLen = 0;
			int nStrLen;
			UINT32 nData;
			int i = 0;
			bool bVictimName = false, bKillerName = false;
			UINT32 nDamageType = 0, nRelationship = 0, nKillerNum = 0, nResultHealthState = 0;
			if (Header == 0x7c)
			{
				Reader.SerializeIntPacked(nBufSize);
				nStartPos = Reader.nPos;
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					nStrRes = Reader.ReadString(szCauserName, &nCauseNameLen);
					{
						if (nStrRes == 1)
						{
						}
						else if (nStrRes == 2)
						{
						}
						else
						{
							goto LABEL1;
						}
					}
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					nStrRes = Reader.ReadString(szVictimName, &nVictimNameLen);
					{
						if (nStrRes == 1)
						{
							bVictimName = true;
						}
						else if (nStrRes == 2)
						{
							bVictimName = true;
						}
						else
						{
							goto LABEL1;
						}
					}
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nDamageType, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{

				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nResultHealthState, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nRelationship, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					nStrRes = Reader.ReadString(szKillerName, &nKillerNameLen);
					{
						if (nStrRes == 1)
						{
						}
						else if (nStrRes == 2)
						{
						}
						else
							goto LABEL1;
					}
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nKillerNum, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				bReadNext = Reader.ReadBit();
				if (bReadNext)
				{
					Reader.ReadByteData((LPBYTE)& nData, 4);
					if (Reader.IsError())
						goto LABEL1;
				}
				if ((Reader.nPos - nStartPos) == nBufSize)
					bRes = true;
			}
			if ((bRes) && (pRadar))
			{
				if (nVictimNameLen != 0)
				{
					if (2 == nResultHealthState)
					{
						pRadar->KillActor(szVictimName, nVictimNameLen, nRelationship);
					}
				}
			}
		}
	LABEL1:
		return bRes;
	}
	void ProcessCmdInitHandle()
	{
		m_nPreHandle = 0;
	}
	bool ReadNextHandle(CBitReader& Ar, UINT32& nWaitingHandle)
	{
		bool bRet = true;
		Ar.SerializeIntPacked(nWaitingHandle);
		if (Ar.nPos > Ar.nNum)
		{
			bRet = false;
		}
		else if ((nWaitingHandle != 0) && ((m_nPreHandle >= nWaitingHandle) || (nWaitingHandle > 0x6a)))
		{
			bRet = false;
		}
		m_nPreHandle = nWaitingHandle;
		return bRet;
	}
	bool FRepLayoutCmdIterator_ProcessArrayCmd(CBitReader& Ar, UINT32 nWaitingHandle)
	{
		UINT16 nCnt, i;
		UINT32 nHandle;
		UINT32 arrayVal[64];
		UINT32 nTemp;
		bool bRet = false;
		if (nWaitingHandle == 0x5F)
		{
			Ar.ReadByteData((BYTE*)& nCnt, 2);
			for (i = 0; i < nCnt; i++)
			{
				Ar.SerializeIntPacked(nHandle);
				Ar.SerializeIntPacked(nTemp);
				if (i < 64)
					arrayVal[i] = nTemp;
			}
			Ar.SerializeIntPacked(nHandle);
			if (nHandle == 0)
				bRet = true;
		}
		return bRet;
	}
	void PropertyReadFunc(CBitReader& Ar, BYTE nInType, UINT32 nWaitingHandle, UINT32 nPreHandle)
	{
		int i = 0;
		UINT8 bit2Val = 0, type06Val = 0, bit4Type6 = 0, bit5Type6 = 0, bit1Type6 = 0, bit6Type6 = 0;
		m_type8Obj = 0x77777777;
		m_type5Dword = 0x77777777;
		m_type9Dword = 0;
		m_type15FvLoc.X = 0;
		m_type15FvLoc.Y = 0;
		m_type15FvLoc.Z = 0;
		m_type15FvVelocity.X = 0;
		m_type15FvVelocity.Y = 0;
		m_type15FvVelocity.Z = 0;
		m_type15FrRot.Pitch = 0;
		m_type15FrRot.Yaw = 0;
		m_type15FrRot.Roll = 0;
		m_type13FV.X = 0;
		m_type13FV.Y = 0;
		m_type13FV.Z = 0;
		m_type11FR.Pitch = 0;
		m_type11FR.Yaw = 0;
		m_type11FR.Roll = 0;
		memset(m_type7Name.szString, 0, 1024);
		m_type4Float = 0;
		m_type10FloatX = 0;
		m_type10FloatY = 0;
		m_type10FloatZ = 0;
		memset(m_type19Str, 0, 1024);
		m_type19StrRes = 0;
		m_type19StrLen = 0;
		BYTE nType = 0;
		BYTE nReadBits = 0;
		DWORD dwTemp;

		//Ar.printHex();

		if (nInType > 60)
		{
			nType = 6;
			nReadBits = nInType - 60;
		}
		else
		{
			nType = nInType;
		}
		switch (nType)
		{
		case 0:
			FRepLayoutCmdIterator_ProcessArrayCmd(Ar, 0x5F);
			break;
		case 1:
			break;
		case 2:
			Ar.ReadByteData(&m_type2Byte, 1);
			break;
		case 3:
			m_type3Bit = Ar.ReadBit();
			break;
		case 4:
			m_type4Float = Ar.ReadFloat();
			break;
		case 5:
			Ar.ReadByteData((BYTE*)& m_type5Dword, 4);
			break;
		case 6:
			Ar.SerializeBits(&m_type6Byte, nReadBits);
			break;
		case 7:
			SerializeName(m_type7Name, Ar);
			break;
		case 8:
			Ar.SerializeIntPacked(m_type8Obj);
			break;
		case 9:
			Ar.ReadByteData((BYTE*)& m_type9Dword, 4);
			break;
		case 10:
			m_type10FloatX = Ar.ReadFloat();
			m_type10FloatY = Ar.ReadFloat();
			m_type10FloatZ = Ar.ReadFloat();
			break;
		case 11:
			SerializeCompressedShort(m_type11FR, Ar);
			break;
		case 12:
			break;
		case 13:
			ReadPackedVector<100, 30>(m_type13FV, Ar);
			break;
		case 14:
			break;
		case 15:
			FRepMovementNetSerialize(m_type15FvLoc, m_type15FrRot, m_type15FvVelocity, Ar);
			break;
		case 16:
			Ar.ReadByteData((BYTE*)& dwTemp, 4);
			Ar.ReadByteData((BYTE*)& dwTemp, 2);
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:


			m_type19StrRes = Ar.ReadString(m_type19Str, &m_type19StrLen);

			break;
		case 20:
			break;
		case 21:
			Ar.ReadByteData((BYTE*)& m_type21Dword, 2);
			break;
		case 22:
			m_type22FloatX = Ar.ReadFloat();
			m_type22FloatY = Ar.ReadFloat();
			break;
		default:
			break;
		}
	}
	bool DealHitDataArray(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{
		DWORD dwVal = 0;
		bool bRes = false;
		Ar.ReadByteData((BYTE*)& dwVal, 2);
		UINT32 nWaitingHandleTemp;
		ProcessCmdInitHandle();
		bRes = ReadNextHandle(Ar, nWaitingHandleTemp);
		m_nPlayerNameLen = 0;
		m_bReadIsEngineStarted = false;
		nPreHandle = 0;
		int nProcessCmdCnt = 0;
		while (nWaitingHandleTemp && bRes && (!Ar.AtEnd()))
		{
			bRes = FRepLayoutCmdIterator_ProcessCmd_HitDataArray(Ar, (nWaitingHandleTemp - 1) % 0x11 + 1, nPreHandle);
			nProcessCmdCnt++;
			nPreHandle = nWaitingHandleTemp;
			if (bRes)
				bRes = ReadNextHandle(Ar, nWaitingHandleTemp);
		}
		if (Ar.nPos < (Ar.nNum - 8))
		{
			bRes = false;
		}
		if (!bRes)
		{
			if ((m_bPacketTruncate) && (m_bShootDir2D))
			{
				bRes = true;
			}
		}
		return bRes;
	}
	bool FRepLayoutCmdIterator_ProcessCmd_AirPlaneLine(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{
		bool bRet = true;
		int i = 0;
		BYTE nType = 0xFF;
		switch (nWaitingHandle)
		{
		case 0x1: nType = 3; break;
		case 0x2: nType = 3; break;
		case 0x3: nType = 3; break;
		case 0x4: nType = 62; break;
		case 0x5: nType = 8; break;
		case 0x6: nType = 15; break;
		case 0x7: nType = 8; break;
		case 0x8: nType = 13; break;
		case 0x9: nType = 13; break;
		case 0xa: nType = 11; break;
		case 0xb: nType = 7; break;
		case 0xc: nType = 8; break;
		case 0xd: nType = 6; break;
		case 0xe: nType = 3; break;
		case 0xf: nType = 8; break;
		case 0x10: nType = 4; break;
		case 0x11: nType = 10; break;
		case 0x12: nType = 4; break;
		}
		if (nType != 0xFF)
		{
			PropertyReadFunc(Ar, nType, nWaitingHandle, nPreHandle);
			if (nWaitingHandle == 0x10)
			{
				m_bFlyingSpeed = true;
				m_fFlyingSpeed = m_type4Float;
				if ((m_fFlyingSpeed < 7990) || (m_fFlyingSpeed > 8010))
					bRet = false;
			}
			if (nWaitingHandle == 0x11)
			{
				m_bFlyingDirection = true;
				m_fFlyingDirX = m_type10FloatX;
				m_fFlyingDirY = m_type10FloatY;
			}
		}
		return bRet;
	}
	bool FRepLayoutCmdIterator_ProcessCmd_HitDataArray(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{

		bool bRet = true;
		int i = 0;
		BYTE nType = 0xFF;
		switch (nWaitingHandle)
		{
		default:
			break;
		case 1:
			nType = 10;
			break;

		case 2:
			nType = 16;
			break;
		case 3:
			nType = 10;
			break;

		case 4:
			nType = 10;
			break;
		case 5:
			nType = 22;
			break;
		case 6:
			nType = 68;
			break;
		case 7:
			nType = 9;
			break;
		case 8:
			nType = 21;
			break;
		case 9:
			nType = 8;
			break;
		case 0xa:
			nType = 8;
			break;

		case 0xb:
			nType = 5;
			break;
		case 0xc:
			nType = 5;
			break;
		case 0xd:
			nType = 68;
			break;
		case 0xe:
			nType = 9;
			break;
		case 0xf:
			nType = 4;
			break;
		case 0x10:
			nType = 4;
			break;
		case 0x11:
			nType = 3;
			break;
		}
		if (nType != 0xFF)
		{
			PropertyReadFunc(Ar, nType, nWaitingHandle, nPreHandle);
			if ((((nWaitingHandle - 1) % 0x11) + 1) == 0x05)
			{
				m_bShootDir2D = true;
				m_fShootDirX = m_type22FloatX;
				m_fShootDirY = m_type22FloatY;
			}
			else if ((((nWaitingHandle - 1) % 0x11) + 1) == 0x01)
			{
				m_bImpactActorPos = true;
				m_fvImpactPos.X = m_type10FloatX;
				m_fvImpactPos.Y = m_type10FloatY;
				m_fvImpactPos.Z = m_type10FloatZ;
			}
			else if ((((nWaitingHandle - 1) % 0x11) + 1) == 0x04)
			{
				m_bShootMomentMuzzlePos = true;
				m_fvMuzzlePos.X = m_type10FloatX;
				m_fvMuzzlePos.Y = m_type10FloatY;
				m_fvMuzzlePos.Z = m_type10FloatZ;
			}
			else if ((((nWaitingHandle - 1) % 0x11) + 1) == 0x09)
			{
				m_bActorGUID = true;
				m_nActorGUID = m_type8Obj;
			}
			else if ((((nWaitingHandle - 1) % 0x11) + 1) == 0xa)
			{
				m_bComponent = true;
				m_nComponent = m_type8Obj;
			}
		}
		return bRet;
	}
	bool FRepLayoutCmdIterator_ProcessCmd_HitDataAnalyze(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{
		bool bRet = true;
		int i = 0;
		BYTE nType = 0xFF;
		switch (nWaitingHandle)
		{
		case 0x1: nType = 3; break;
		case 0x2: nType = 3; break;
		case 0x3: nType = 3; break;
		case 0x4: nType = 62; break;
		case 0x5: nType = 8; break;
		case 0x6: nType = 15; break;
		case 0x7: nType = 8; break;
		case 0x8: nType = 13; break;
		case 0x9: nType = 13; break;
		case 0xa: nType = 11; break;
		case 0xb: nType = 7; break;
		case 0xc: nType = 8; break;
		case 0xd: nType = 68; break;
		case 0xe: nType = 3; break;
		case 0xf: nType = 8; break;
		case 0x10: nType = 64; break;
		case 0x11: nType = 8; break;
		case 0x12: nType = 19; break;
		case 0x13: nType = 7; break;
		case 0x14: nType = 5; break;
		case 0x15: nType = 9; break;
		case 0x16: nType = 9; break;
		case 0x17: nType = 68; break;
		case 0x18: nType = 68; break;
		case 0x19: nType = 5; break;
		case 0x1a: nType = 5; break;
		case 0x1b: nType = 5; break;
		case 0x1c: nType = 3; break;
		case 0x1d: nType = 3; break;
		case 0x1e: nType = 20; break;
		case 0x1f: nType = 5; break;
		case 0x20: nType = 3; break;
		case 0x21: nType = 5; break;
		case 0x22: nType = 8; break;
		case 0x23: nType = 7; break;
		case 0x24: nType = 3; break;
		case 0x25: nType = 3; break;
		case 0x26: nType = 5; break;
		case 0x27: nType = 5; break;
		case 0x28: nType = 3; break;
		case 0x29: nType = 3; break;
		case 0x2a: nType = 20; break;
		case 0x2b: nType = 3; break;
		case 0x2c: nType = 5; break;
		case 0x2d: nType = 8; break;
		case 0x2e: nType = 19; break;
		case 0x2f: nType = 3; break;
		case 0x30: nType = 8; break;
		case 0x31: nType = 8; break;
		case 0x32: nType = 0; break;
		case 0x33: nType = 5; break;
		case 0x34: nType = 5; break;
		case 0x35: nType = 62; break;
		case 0x36: nType = 5; break;
		case 0x37: nType = 5; break;
		case 0x38: nType = 3; break;
		case 0x39: nType = 3; break;
		case 0x3a: nType = 3; break;
		case 0x3b: nType = 0; break;
		case 0x3c: nType = 0; break;
		default:
			break;
		}
		if (nType != 0xFF)
		{
			if (nType != 0)
			{
				PropertyReadFunc(Ar, nType, nWaitingHandle, nPreHandle);
			}
			else
			{
				bRet = DealHitDataArray(Ar, nWaitingHandle, nPreHandle, pRadar, pActor);
			}
		}
		return bRet;
	}
	bool FRepLayoutCmdIterator_ProcessCmd_FindInitInfo(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{
		bool bRet = true;
		int i = 0;
		BYTE nType = 0xFF;
		switch (nWaitingHandle)
		{
		case 0x1: nType = 3; break;
		case 0x2: nType = 3; break;
		case 0x3: nType = 3; break;
		case 0x4: nType = 62; break;

		case 0x5: nType = 8; break;
		case 0x6: nType = 15; break;
		case 0x7: nType = 8; break;
		case 0x8: nType = 13; break;
		case 0x9: nType = 13; break;
		case 0xa: nType = 11; break;
		case 0xb: nType = 7; break;
		case 0xc: nType = 8; break;
		case 0xd: nType = 68; break;
		case 0xe: nType = 3; break;
		case 0xf: nType = 8; break;
		case 0x10: nType = 8; break;
		case 0x11: nType = 8; break;
		case 0x12: nType = 11; break;
		case 0x13: nType = 10; break;
		case 0x14: nType = 19; break;
		case 0x15: nType = 9; break;
		case 0x16: nType = 5; break;
		case 0x17: nType = 10; break;
		case 0x18: nType = 5; break;
		case 0x19: nType = 19; break;
		case 0x1a: nType = 5; break;
		case 0x1b: nType = 4; break;
		case 0x1c: nType = 5; break;
		case 0x1d: nType = 5; break;
		case 0x1e: nType = 3; break;
		case 0x1f: nType = 19; break;
		case 0x20: nType = 61; break;
		}
		if (nType != 0xFF)
		{
			PropertyReadFunc(Ar, nType, nWaitingHandle, nPreHandle);
			if (pActor)
			{
				switch (nWaitingHandle)
				{
				case 0x14:
					if (m_type19StrLen != 0)
					{
						m_bReadMyPlayerName = true;
						if (m_type19StrLen > 0)
						{
							memcpy(m_szMyPlayerName, m_type19Str, m_type19StrLen);
						}
						else
						{
							memcpy(m_szMyPlayerName, m_type19Str, (-m_type19StrLen) * 2);
						}
						m_nMyPlayerNameLen = m_type19StrLen;
					}

					break;
				case 0x19:
					if (m_type19StrLen != 0)
					{
						m_bReadWeatherName = true;
						if (m_type19StrLen > 0)
						{
							memcpy(m_szWeatherName, m_type19Str, m_type19StrLen);
						}
						else
						{
							memcpy(m_szWeatherName, m_type19Str, (-m_type19StrLen) * 2);
						}
						m_nWeatherNameLen = m_type19StrLen;
					}
					break;
				}
			}
		}
		return bRet;
	}
	bool FRepLayoutCmdIterator_ProcessCmd_Main(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{
		bool bRet = true;
		int i = 0;
		BYTE nType = 0xFF;
		switch (nWaitingHandle)
		{
		case 0x1:
			nType = 3;
			break;
		case 0x2:
			nType = 3;
			break;
		case 0x3:
			nType = 3;
			break;
		case 0x4:
			nType = 62;
			break;
		case 0x5:
			nType = 8;
			break;
		case 0x6:
			nType = 15;
			break;
		case 0x7:
			nType = 8;
			break;
		case 0x8:
			nType = 13;
			break;
		case 0x9:
			nType = 13;
			break;
		case 0xa:
			nType = 11;
			break;
		case 0xb:
			nType = 7;
			break;
		case 0xc:
			nType = 8;
			break;
		case 0xd:
			nType = 66;
			break;
		case 0xe:
			nType = 3;
			break;
		case 0xf:
			nType = 8;
			break;
		case 0x10:
			nType = 8;
			break;
		case 0x11:
			nType = 68;
			break;
		case 0x12:
			nType = 8;
			break;
		case 0x13:
			nType = 8;
			break;
		case 0x14:
			nType = 7;
			break;
		case 0x15:
			nType = 13;
			break;
		case 0x16:
			nType = 11;
			break;
		case 0x17:
			nType = 3;
			break;
		case 0x18:
			nType = 3;
			break;
		case 0x19:
			nType = 3;
			break;
		case 0x1a:
			nType = 4;
			break;
		case 0x1b:
			nType = 4;
			break;
		case 0x1c:
			nType = 68;
			break;
		case 0x1d:
			nType = 3;
			break;
		case 0x1e:
			nType = 4;
			break;
		case 0x1f:
			nType = 5;
			break;
		case 0x20:
			nType = 3;
			break;
		case 0x21:
			nType = 8;
			break;
		case 0x22:
			nType = 4;
			break;
		case 0x23:
			nType = 13;
			break;
		case 0x24:
			nType = 11;
			break;
		case 0x25:
			nType = 8;
			break;
		case 0x26:
			nType = 7;
			break;
		case 0x27:
			nType = 3;
			break;
		case 0x28:
			nType = 3;
			break;
		case 0x29:
			nType = 2;
			break;
		case 0x2a:
			nType = 17;
			break;
		case 0x2b:
			nType = 17;
			break;
		case 0x2c:
			nType = 19;
			break;
		case 0x2d:
			nType = 9;
			break;
		case 0x2e:
			nType = 5;
			break;
		case 0x2f:
			nType = 3;
			break;
		case 0x30:
			nType = 61;
			break;
		case 0x31:
			nType = 3;
			break;
		case 0x32:
			nType = 3;
			break;
		case 0x33:
			nType = 4;
			break;
		case 0x34:
			nType = 4;
			break;
		case 0x35:
			nType = 3;
			break;
		case 0x36:
			nType = 11;
			break;
		case 0x37:
			nType = 64;
			break;
		case 0x38:
			nType = 0;
			break;
		case 0x39:
			nType = 3;
			break;
		case 0x3a:
			nType = 3;
			break;
		case 0x3b:
			nType = 4;
			break;
		case 0x3c:
			nType = 3;
			break;
		case 0x3d:
			nType = 5;
			break;
		case 0x3e:
			nType = 10;
			break;
		case 0x3f:
			nType = 68;
			break;
		case 0x40:
			nType = 68;
			break;
		case 0x41:
			nType = 68;
			break;
		case 0x42:
			nType = 3;
			break;
		case 0x43:
			nType = 11;
			break;

		case 0x44:
			nType = 5;
			break;
		case 0x45:
			nType = 5;
			break;
		case 0x46:
			nType = 65;
			break;
		case 0x47:
			nType = 19;
			break;
		case 0x48:
			nType = 19;
			break;
		case 0x49:
			nType = 19;
			break;
		case 0x4a:
			nType = 3;
			break;
		case 0x4b:
			nType = 5;
			break;
		case 0x4c:
			nType = 10;

			break;
		case 0x4d:
			nType = 61;
			break;
		case 0x4e:
			nType = 3;
			break;
		case 0x4f:
			nType = 4;
			break;
		case 0x50:
			nType = 4;
			break;
		case 0x51:
			nType = 62;
			break;
		case 0x52:
			nType = 3;
			break;
		case 0x53:
			nType = 4;
			break;
		case 0x54:
			nType = 4;
			break;
		case 0x55:
			nType = 4;
			break;
		case 0x56:
			nType = 4;
			break;
		case 0x57:
			nType = 5;
			break;
		case 0x58:
			nType = 5;
			break;
		case 0x59:
			nType = 4;
			break;
		case 0x5a:
			nType = 4;
			break;
		case 0x5b:
			nType = 2;
			break;
		case 0x5c:
			nType = 11;
			break;
		case 0x5d:
			nType = 10;
			break;
		case 0x5e:
			nType = 11;
			break;
		case 0x5f:
			nType = 10;
			break;
		case 0x60:
			nType = 3;
			break;
		case 0x61:
			nType = 3;
			break;
		case 0x62:
			nType = 0;
			break;
		case 0x63:
			nType = 8;
			break;
		case 0x64:
			nType = 62;
			break;
		case 0x65:
			nType = 0;
			break;
		case 0x66:
			nType = 3;
			break;
		case 0x67:
			nType = 4;
			break;
		case 0x68:
			nType = 62;
			break;
		case 0x69:
			nType = 3;
			break;
		case 0x6a:
			nType = 8;
			break;

		default:
			break;
		}
		if (nType != 0xFF)
		{
			PropertyReadFunc(Ar, nType, nWaitingHandle, nPreHandle);
			if (pActor)
			{
				switch (nWaitingHandle)
				{
				case 0x06:
					if ((m_type15FvLoc.X > 7000) && (m_type15FvLoc.X < 800000) && (m_type15FvLoc.Y > 7000) && (m_type15FvLoc.Y < 800000) && (m_type15FvLoc.Z > -3000) && (m_type15FvLoc.Z < 150001))
					{
						pRadar->user->g_bLoc = true;
						pActor->dwReceiveDataTime = GetTickCountMs();
						pActor->fXPos = m_type15FvLoc.X;
						pActor->fYPos = m_type15FvLoc.Y;
						pActor->fZPos = m_type15FvLoc.Z;
						pActor->fYaw = m_type15FrRot.Yaw;
						pActor->fVelX = m_type15FvVelocity.X;
						pActor->fVelY = m_type15FvVelocity.Y;
						pActor->fVelZ = m_type15FvVelocity.Z;

						pActor->nType = 2;
					}
					else
						bRet = false;
					break;
				case 0x10:
					pActor->nStateID = m_type8Obj;
					break;
				case 0x1C:
					if (nPreHandle != 0)
					{
						pActor->nMoveMode = m_type6Byte;
					}
					break;
				case 0x40:
					m_bReceiveYaw = true;
					pActor->fYaw = (float)(m_type6Byte) * 360 / 256.0;
					break;
				case 0x57:
					if ((pActor) && ((m_type5Dword == 0xFFFFFFFF) || (m_type5Dword == 0x00) || (m_type5Dword == 0x01) || (m_type5Dword == 0x02) || (m_type5Dword == 0x03)))
					{
						pActor->nVehicleSeatIdx = m_type5Dword;
					}
					break;
				case 0x07:
					if ((pActor) && (m_type8Obj != 0x77777777))
					{
						pActor->nAttachParent = m_type8Obj;
					}
					break;
				case 0x2E:
					if (pActor)
					{
						pActor->nTeamID = m_type5Dword;
					}
					break;
				case 0x2C:
					if (m_type19StrLen > 0)
					{
						memcpy(m_szPlayerName, m_type19Str, m_type19StrLen);
						m_nPlayerNameLen = m_type19StrLen;
						//strncpy(pActor->m_szPlayerName, m_type19Str, m_type19StrLen);
						pActor->m_szPlayerName[m_type19StrLen] = '\0';
						printf("Received name type0 : %s\n", pActor->m_szPlayerName);
					}
					else if (m_type19StrLen < 0)
					{
						m_nPlayerNameLen = (-m_type19StrLen) * 2;
						memcpy(m_szPlayerName, m_type19Str, (-m_type19StrLen) * 2);
						//strncpy(pActor->m_szPlayerName, m_type19Str, m_nPlayerNameLen);
						pActor->m_szPlayerName[m_type19StrLen] = '\0';
						printf("Received name type1 : %s\n", pActor->m_szPlayerName);
					}




					break;
				default:
					break;
				}
				if (nWaitingHandle == 0x6)
				{

				}
				else if (nWaitingHandle == 0x40)
				{

				}
			}
		}
		return bRet;
	}

	bool FRepLayoutCmdIterator_ProcessCmd2(CBitReader& Ar, UINT32 nWaitingHandle, UINT32 nPreHandle = 0, user_container * pRadar = NULL, ACTOR * pActor = NULL)
	{
		bool bRet = true;
		UINT8 bBit, bit2Val = 0, type06Val = 0, bit4Type6 = 0, bit5Type6 = 0, bit1Type6 = 0, bit6Type6 = 0, byteType2;
		UINT32 nObjProperty = 0, nType5 = 0, nType9;
		FVECTOR fvLoc = { 0, 0, 0 }, fvVelocity = { 0, 0, 0 };
		FROTATOR frRot = { 0 };
		FVECTOR type13FV;
		FROTATOR type11FR;
		FName type07Name;
		memset(type07Name.szString, 0, 1024);
		float fType4 = 0;
		float fType10X = 0, fType10Y = 0, fType10Z = 0;
		char szType19[1024] = { 0 };
		float fVelNorm = 0;
		int nStrRes = 0, i = 0, nStrLen = 0;
		switch (nWaitingHandle)
		{
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x0e:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x1e:
		case 0x22:
			bBit = Ar.ReadBit();
			break;
		case 0x10:
			Ar.SerializeIntPacked(nObjProperty);
			if (pActor)
			{
				pActor->nStateID = nObjProperty;
			}
			break;
		case 0x07:
			Ar.SerializeIntPacked(nObjProperty);
			break;
		case 0x05:
		case 0x0C:
		case 0x0F:
		case 0x12:
			Ar.SerializeIntPacked(nObjProperty);
			break;
		case 0x06:

			FRepMovementNetSerialize(fvLoc, frRot, fvVelocity, Ar);
			if ((fvLoc.X > 20000) && (fvLoc.X < 800000) && (fvLoc.Y > 20000) && (fvLoc.Y < 800000) && (fvLoc.Z > -1000) && (fvLoc.Z < 150001))
			{

				fVelNorm = sqrt(fvVelocity.X * fvVelocity.X + fvVelocity.Y * fvVelocity.Y);
				if (fVelNorm > pRadar->user->g_fMaxNorm)
				{
					pRadar->user->g_fMaxNorm = fVelNorm;
				}
			}
			if ((fvLoc.X > 20000) && (fvLoc.Y > 10000) && (fvLoc.Z < 150001))
			{
				pRadar->user->g_bLoc = true;
				if (pActor)
				{
					pActor->dwReceiveDataTime = GetTickCountMs();
					pActor->fXPos = fvLoc.X;
					pActor->fYPos = fvLoc.Y;
					pActor->fZPos = fvLoc.Z;
					pActor->fYaw = frRot.Yaw;
					pActor->fVelX = fvVelocity.X;
					pActor->fVelY = fvVelocity.Y;
					pActor->fVelZ = fvVelocity.Z;

					pActor->nType = 2;
				}
			}
			else
			{
				bRet = false;
			}
			break;
		case 0x08:
		case 0x09:

			ReadPackedVector<100, 30>(type13FV, Ar);
			break;
		case 0xA:
			SerializeCompressedShort(type11FR, Ar);
			break;
		case 0xB:
			SerializeName(type07Name, Ar);
			{
				if (strstr(type07Name.szString, "EnterDriverSocket") != NULL)
				{
					pRadar->user->g_bExternStringDetect = true;
				}
			}
			break;
		case 0x1B:
			if (nPreHandle == 0x1A)
			{
				Ar.ReadByteData(&type06Val, 1);
			}
			else
			{
				fType4 = Ar.ReadFloat();
				{
					if (pActor)
						pActor->fSeverTime = fType4;
				}
			}
			break;
		case 0x1A:
			fType4 = Ar.ReadFloat();
			{
				if (pActor)
					pActor->fSeverTime = fType4;
			}
			break;
		case 0x19:
			Ar.ReadByteData((BYTE*)& nType5, 4);
			if ((pActor) && ((nType5 == 0xFFFFFFFF) || (nType5 == 0x00) || (nType5 == 0x01) || (nType5 == 0x02) || (nType5 == 0x03)))
			{
				pActor->nVehicleSeat = nType5;
			}
			break;
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
			Ar.ReadByteData(&byteType2, 1);
			break;
		case 0x0D:
			Ar.SerializeBits(&bit6Type6, 6);
			bit6Type6 = bit6Type6 & 0x3F;
			break;
		case 0x04:
			Ar.SerializeBits(&bit2Val, 2);
			bit2Val = bit2Val & 0x3;
			break;
		case 0x11:
		case 0x1c:
		case 0x1d:
		case 0x1f:
		case 0x20:
		case 0x21:
			Ar.ReadByteData(&type06Val, 1);
			if (nPreHandle != 0)
			{
				pActor->nMoveMode = type06Val;
				if (type06Val == 0)
				{
					type06Val = type06Val;
				}
			}
			break;
		case 0x13:
			break;
		default:
			break;
		}
		return bRet;
	}
	bool ReceiveProperties(CBitReader& Ar, user_container* Radar = NULL)
	{
		bool bDoChecksum = Ar.ReadBit() ? true : false;
		bool bRes = true;
		UINT32 nWaitingHandle = 0;
		UINT32 nPreHandle = 0;
		UINT32 nPosTemp = 0;
		int nPropertyCnt = 0;
		int i = 0;
		ACTOR actor;
		actor.m_szPlayerName[0] = '\0';



		nPosTemp = Ar.nPos;

		ProcessCmdInitHandle();
		bRes = ReadNextHandle(Ar, nWaitingHandle);
		m_nPlayerNameLen = 0;
		m_bReadIsEngineStarted = false;
		m_bReceiveYaw = 0;
		m_bShootDir2D = 0;
		m_bImpactActorPos = 0;
		m_bShootMomentMuzzlePos = 0;
		m_bActorGUID = 0;
		m_bComponent = 0;
		while (nWaitingHandle && bRes && (!Ar.AtEnd()))
		{
			bRes = FRepLayoutCmdIterator_ProcessCmd_Main(Ar, nWaitingHandle, nPreHandle, Radar, &actor);
			nPropertyCnt++;
			nPreHandle = nWaitingHandle;
			if (bRes)
				bRes = ReadNextHandle(Ar, nWaitingHandle);
		}
		if (Ar.nPos < Ar.nNum)
		{
			if ((nWaitingHandle == 0) && (nPreHandle == 0x58) && (Ar.nPos > 0x30))
			{
				bRes = true;
			}
			else
				bRes = false;
		}
		if (bRes == false)
		{
			actor.nStateID = -1;
			actor.nVehicleSeatIdx = 0x77777777;
			Ar.nPos = nPosTemp;
			nPropertyCnt = 0;
			ProcessCmdInitHandle();
			nPreHandle = 0;
			bRes = ReadNextHandle(Ar, nWaitingHandle);
			m_nPlayerNameLen = 0;
			m_bReadIsEngineStarted = false;
			while (nWaitingHandle && bRes && (!Ar.AtEnd()))
			{

				bRes = FRepLayoutCmdIterator_ProcessCmd2(Ar, nWaitingHandle, nPreHandle, Radar, &actor);
				nPropertyCnt++;
				nPreHandle = nWaitingHandle;
				if (bRes)
					bRes = ReadNextHandle(Ar, nWaitingHandle);
			}
			if (Ar.nPos < Ar.nNum)
			{
				if ((nWaitingHandle == 0) && (nPreHandle == 0x57) && (Ar.nPos > 0x30))
				{
					bRes = true;
				}
				else
					bRes = false;
			}
		}
		if (!bRes)
		{
			Ar.nPos = nPosTemp;
			ProcessCmdInitHandle();
			nPreHandle = 0;
			bRes = ReadNextHandle(Ar, nWaitingHandle);
			while (nWaitingHandle && bRes && (!Ar.AtEnd()))
			{
				bRes = FRepLayoutCmdIterator_ProcessCmd_HitDataAnalyze(Ar, nWaitingHandle, nPreHandle, Radar, &actor);
				nPreHandle = nWaitingHandle;
				if ((m_bPacketTruncate) && (nWaitingHandle == 0x3C) && (bRes))
				{
					Ar.nPos = Ar.nNum;
				}
				else if (bRes)
					bRes = ReadNextHandle(Ar, nWaitingHandle);
			}
			if (Ar.nPos < Ar.nNum)
			{
				bRes = false;
			}
			if (bRes && Radar && m_bShootDir2D && m_bShootMomentMuzzlePos && m_bImpactActorPos)
			{
				Radar->ShootManager(m_fvImpactPos.X, m_fvImpactPos.Y, m_fvImpactPos.Z, m_fvMuzzlePos.X, m_fvMuzzlePos.Y, m_fvMuzzlePos.Z);
				bRes = bRes;
			}
		}
		if (Radar && (!Radar->user->m_nMyChannelIndex) && (Radar->user->m_nMyActorNameLen != 0) && (m_nPlayerNameLen != 0))
		{
			if (Radar->NameCmp(Radar->user->m_szMyActorName, Radar->user->m_nMyActorNameLen, m_szPlayerName, m_nPlayerNameLen))
			{
				Radar->user->m_nMyChannelIndex = m_nChannelIndex;
			}
		}
		actor.nActorChannelIndex = m_nChannelIndex;
		actor.nType = 2;
		if (Radar && Radar->user->m_channel[m_nChannelNo].bChannelOpen)
		{

			if ((Radar->user->g_bLoc) && (m_nChannelIndex != Radar->user->m_nMyChannelIndex))
			{
				if (Radar->user->m_channel[m_nChannelNo].pActor)
				{
					Radar->user->m_channel[m_nChannelNo].pActor->fXPos = actor.fXPos;
					Radar->user->m_channel[m_nChannelNo].pActor->fYPos = actor.fYPos;
					Radar->user->m_channel[m_nChannelNo].pActor->fZPos = actor.fZPos;
					Radar->user->m_channel[m_nChannelNo].pActor->fYaw = actor.fYaw;
					Radar->user->m_channel[m_nChannelNo].pActor->bDraw = true;

					/*if (strlen(actor.m_szPlayerName) > 0)
						strncpy(Radar->user->m_channel[m_nChannelNo].pActor->m_szPlayerName, actor.m_szPlayerName, strlen(actor.m_szPlayerName));
*/

					Radar->user->m_channel[m_nChannelNo].pActor->fVelX = actor.fVelX;
					Radar->user->m_channel[m_nChannelNo].pActor->fVelY = actor.fVelY;
					Radar->user->m_channel[m_nChannelNo].pActor->fVelZ = actor.fVelZ;
					Radar->user->m_channel[m_nChannelNo].pActor->dwReceiveDataTime = GetTickCountMs();
				}
				else if (Radar->user->m_channel[m_nChannelNo].pVehicle)
				{
					Radar->user->m_channel[m_nChannelNo].pVehicle->fXPos = actor.fXPos;
					Radar->user->m_channel[m_nChannelNo].pVehicle->fYPos = actor.fYPos;
					Radar->user->m_channel[m_nChannelNo].pVehicle->fZPos = actor.fZPos;
					Radar->user->m_channel[m_nChannelNo].pVehicle->fYaw = actor.fYaw;

					Radar->user->m_channel[m_nChannelNo].pVehicle->fVelX = actor.fVelX;
					Radar->user->m_channel[m_nChannelNo].pVehicle->fVelY = actor.fVelY;
					Radar->user->m_channel[m_nChannelNo].pVehicle->fVelZ = actor.fVelZ;
					Radar->user->m_channel[m_nChannelNo].pVehicle->dwReceiveDataTime = GetTickCountMs();
				}
			}
			if (bRes == true)
			{
				if ((m_nChannelIndex == Radar->user->m_nMyChannelIndex))
				{
					Radar->user->m_myActor.dwReceiveDataTime = GetTickCountMs();
					if ((Radar->user->m_myActor.nTeamID == 0x77777777))
					{
						if (actor.nInstigator != 0xAAAAAAAA)
						{
							Radar->user->m_myActor.nInstigator = Radar->user->m_channel[m_nChannelNo].nNetGUID;
						}
						if (actor.nTeamID != 0x77777777)
						{
							Radar->user->m_myActor.nTeamID = actor.nTeamID;
						}
					}
					if ((Radar->user->m_myActor.nStateID == -1) && (actor.nStateID != -1))
					{
						Radar->user->m_myActor.nStateID = actor.nStateID;
					}
					if (m_bReceiveYaw)
					{
						{
							Radar->user->m_fMyDirYaw = actor.fYaw;
						}
					}
				}
				{
					if (Radar->user->m_channel[m_nChannelNo].pActor)
					{
						if ((actor.nStateID != -1) && (Radar->user->m_channel[m_nChannelNo].pActor->nStateID == -1))
						{
							Radar->user->m_channel[m_nChannelNo].pActor->nStateID = actor.nStateID;
						}
						if (actor.nAttachParent != 0x77777777)
						{
							Radar->user->m_channel[m_nChannelNo].pActor->nAttachParent = actor.nAttachParent;
						}
						if ((actor.nTeamID != 0x77777777) && (Radar->user->m_channel[m_nChannelNo].pActor->nTeamID == 0x77777777))
						{
							Radar->user->m_channel[m_nChannelNo].pActor->nTeamID = actor.nTeamID;
							if (actor.nTeamID == Radar->user->m_myActor.nTeamID)
							{
								Radar->user->m_channel[m_nChannelNo].pActor->nType = 1;
								for (i = 0; i < Radar->user->m_nTeammateCnt; i++)
								{
									if (Radar->user->m_channel[m_nChannelNo].pActor->nStateID == Radar->user->m_nTeamRealID[i])
									{
										Radar->user->m_channel[m_nChannelNo].pActor->nTeamNo = Radar->user->m_nTeamNo[i];
										Radar->user->m_TeamActor[i].bVisible = false;
										break;
									}
								}
							}
							else
							{
								Radar->user->m_channel[m_nChannelNo].pActor->nType = 2;
							}
						}
						if (actor.nVehicleSeatIdx != 0x77777777)
						{
							BYTE nActorType = 0x77777777;
							if (m_nChannelIndex == Radar->user->m_nMyChannelIndex)
							{
								Radar->user->m_myActor.dwReceiveDataTime = GetTickCountMs();
								nActorType = 0;
							}
							else if (Radar->user->m_channel[m_nChannelNo].pActor->nTeamID == Radar->user->m_myActor.nTeamID)
							{
								nActorType = 1;
							}
							else
							{
								nActorType = 2;
							}
							Radar->VehicleSeatOperation(m_nChannelNo, Radar->user->m_channel[m_nChannelNo].pActor->nAttachParent, actor.nVehicleSeatIdx, nActorType);
						}

					}
				}
			}
		}
		if ((m_nPlayerNameLen != 0) && (Radar))
		{
			Radar->NameManage(m_szPlayerName, m_nPlayerNameLen, Radar->user->m_channel[m_nChannelNo].nNetGUID, m_nChannelIndex);
		}
		return bRes;
	}
	void ReceivedPacket_sub_218A5B8(CBitReader& Ar, user_container* radar = NULL)
	{
		DWORD dwPacketID;
		Ar.ReadBit();
		if (Ar.IsError())
			return;

		dwPacketID = Ar.ReadInt(MAX_PACKETID);

		while (!Ar.AtEnd())
		{
			DWORD StartPos = Ar.GetPosBits();
			bool IsAck = !!Ar.ReadBit();
			if (Ar.IsError())
				return;

			if (IsAck)
			{
				Ar.ReadInt(MAX_PACKETID);

				Ar.ReadBit();

				UINT32 RemoteInKBytesPerSecond = 0;
				Ar.SerializeIntPacked(RemoteInKBytesPerSecond);
			}
			else
			{
				FInBunch Bunch;

				DWORD IncomingStartPos = Ar.GetPosBits();
				BYTE bControl = Ar.ReadBit();


				Bunch.bOpen = bControl ? Ar.ReadBit() : 0;


				Bunch.bClose = bControl ? Ar.ReadBit() : 0;


				Bunch.bDormant = Bunch.bClose ? Ar.ReadBit() : 0;


				Bunch.bIsReplicationPaused = Ar.ReadBit();


				Bunch.bReliable = Ar.ReadBit();


				Bunch.ChIndex = Ar.ReadInt(0x2800);
				m_nChannelIndex = Bunch.ChIndex;


				Bunch.bHasPackageMapExports = Ar.ReadBit();


				Bunch.bHasMustBeMappedGUIDs = Ar.ReadBit();


				Bunch.bPartial = Ar.ReadBit();



				Bunch.ChSequence = Bunch.bReliable ? Ar.ReadInt(0x1000) : 0;


				Bunch.bPartialInitial = Bunch.bPartial ? Ar.ReadBit() : 0;


				Bunch.bPartialFinal = Bunch.bPartial ? Ar.ReadBit() : 0;


				Bunch.ChType = (Bunch.bReliable || Bunch.bOpen) ? Ar.ReadInt(CHTYPE_MAX) : CHTYPE_None;

				DWORD BunchDataBits = Ar.ReadInt(0x1000);

				Bunch.SetData(Ar, BunchDataBits);
				if (Ar.IsError())
				{
					return;
				}
				if (radar)
				{
					m_nChannelNo = radar->MainChannelManager(m_nChannelIndex);
					if (bControl)
					{
						radar->user->m_channel[m_nChannelNo].bChannelOpen = Bunch.bOpen;
						if (Bunch.bOpen)
						{
						}
						radar->user->m_channel[m_nChannelNo].bChannelClose = Bunch.bClose;
						if (Bunch.bClose == true)
						{
							radar->RemoveChannel(m_nChannelNo);
							continue;
						}
						radar->user->m_channel[m_nChannelNo].bDormant = Bunch.bDormant;
					}
				}
				if (Bunch.nNum > 0)
					UChannel_ReceivedRawBunch(Bunch, radar);
			}
		}
	}
};