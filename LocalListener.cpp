#include "LocalListener.h"
#include "CBitReader.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>

void LocalListener::readfile(char* filename) {
	const int len = 1000, strings = 100;
	const char ch = '\n';
	char mass[len][strings];

	std::ifstream fs(filename, std::ios::in | std::ios::binary);

	if (!fs) return;

	for (int r = 0; r < strings; r++)
	{
		fs.getline(mass[r], len - 1, ch);
		std::cout << "String " << r + 1 << " = " << mass[r] << std::endl;
		SendPacketFilter((LPBYTE)(hexstr_to_char(mass[r])), (strlen(mass[r]) - 1)/2);
	}
	fs.close();
}

unsigned char* LocalListener::hexstr_to_char(const char* hexstr)
{
	size_t len = strlen(hexstr) - 1;
	std::cout << "String len" << " = " << len << std::endl;
	if (len % 2 != 0)
		return NULL;
	size_t final_len = len / 2;
	unsigned char* chrs = (unsigned char*)malloc((final_len + 1) * sizeof(*chrs));
	for (size_t i = 0, j = 0; j < final_len; i += 2, j++)
		chrs[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i + 1] % 32 + 9) % 25;
	chrs[final_len] = '\0';
	return chrs;
}

char* LocalListener::chartobin(unsigned char c)
{
	static char bin[CHAR_BIT + 1] = { 0 };
	int i;

	for (i = CHAR_BIT - 1; i >= 0; i--)
	{
		bin[i] = (c % 2) + '0';
		c /= 2;
	}

	return bin;
}



void LocalListener::SendPacketFilter(LPBYTE pBuf, int nBufLen)
{
	CBitReader reader;
	CReceiveDataParsing parser;
	ACTOR actor;
	BYTE byteFilterHeader = 0;
	int i = 0;
	int j = 0;
	float fTimes = 0;
	BYTE bReadNext = 0;
	FVECTOR Fv, fvVel;
	FROTATOR FR;
	UINT32 nTemp;
	UINT32 nPosTemp = 0;
	BOOL bLocationValid = FALSE;
	UINT32 nBunchLen = 0;
	UINT32 nPosTemp2 = 0;
	UINT32 nIncorrectID = 0;


	memcpy(reader.Buffer, pBuf, nBufLen);
	reader.nNum = 8 * nBufLen;
	for (j = 6 * 8; j < (nBufLen) * 8; j++)
	{
		reader.nPos = j;
		Fv.X = 0;
		Fv.Y = 0;
		Fv.Z = 0;

		reader.ReadByteData(&byteFilterHeader, 1);
		if (byteFilterHeader == 0x80)
		{
			reader.SerializeIntPacked(nBunchLen);
			nPosTemp = reader.nPos;
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				fTimes = reader.ReadFloat();
				if ((fTimes < 0) || (fTimes > 10000))
				{
					goto LABEL1;
				}
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				fTimes = reader.ReadFloat();
				if ((fTimes < 0) || (fTimes > 10000))
				{
					goto LABEL1;
				}
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				parser.ReadPackedVector<100, 30>(Fv, reader);
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				fTimes = reader.ReadFloat();
				if ((fTimes < 0) || (fTimes > 800000))
				{
					goto LABEL1;
				}
			}
			if ((reader.nPos - nPosTemp) == nBunchLen)
			{
				if ((Fv.X > 10000) && (Fv.X < 800000) && (Fv.Y > 10000) && (Fv.Y < 800000) && (Fv.Z > -1000) && (Fv.Z < 150001))
				{

					/*if (container->user->m_myActor.dwReceiveDataTime != 0x00)
					{
						memcpy(&container->user->m_myActorTemp, &(container->user->m_myActor), sizeof(container->user->m_myActorTemp));
					}
					if (container->user->m_myActor.bDraw == false)
					{
						container->user->m_myActor.bDraw = true;
					}
					if (ChangeMyActorPlace(container, container->user->m_myActor.fXPos, container->user->m_myActor.fYPos, container->user->m_myActor.fZPos, Fv.X, Fv.Y, Fv.Z))
					{
						container->user->m_myActor.fXPos = Fv.X;
						container->user->m_myActor.fYPos = Fv.Y;
						container->user->m_myActor.fZPos = Fv.Z;
					}
					if (container->user->m_nChangeCnt > 3)
					{
						container->user->m_myActor.fXPos = Fv.X;
						container->user->m_myActor.fYPos = Fv.Y;
						container->user->m_myActor.fZPos = Fv.Z;
					}
					container->user->m_myActor.dwReceiveDataTime = GetTickCountMs();*/
					continue;
				}
			}


		}
	LABEL1:
		reader.nPos = j;
		reader.ReadByteData(&byteFilterHeader, 1);
		if ((byteFilterHeader == 0x80) || (byteFilterHeader == 0xa0))
		{
			reader.SerializeIntPacked(nBunchLen);
			nPosTemp = reader.nPos;
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				reader.ReadByteData((BYTE*)& nIncorrectID, 4);
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				fTimes = reader.ReadFloat();
				if ((fTimes < 0) || (fTimes > 10000))
				{
					goto LABEL2;
				}
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				parser.ReadPackedVector<100, 30>(Fv, reader);
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				parser.ReadPackedVector<1, 24>(fvVel, reader);
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				reader.ReadByteData((BYTE*)& nTemp, 2);
				reader.ReadByteData((BYTE*)& nTemp, 4);
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				parser.ReadPackedVector<1, 24>(fvVel, reader);
			}
			if (((reader.nPos - nPosTemp + 1) == nBunchLen) || ((reader.nPos - nPosTemp) == nBunchLen))
			{
				if ((Fv.X > 10000) && (Fv.X < 800000) && (Fv.Y > 10000) && (Fv.Y < 800000) && (Fv.Z > -1000) && (Fv.Z < 150001))
				{
					/*if (container->user->m_myActor.bDraw == false)
					{
						container->user->m_myActor.bDraw = true;
					}*/
					/*if (ChangeMyActorPlace(container, container->user->m_myActor.fXPos, container->user->m_myActor.fYPos, container->user->m_myActor.fZPos, Fv.X, Fv.Y, Fv.Z))
					{
						container->user->m_myActor.fXPos = Fv.X;
						container->user->m_myActor.fYPos = Fv.Y;
						container->user->m_myActor.fZPos = Fv.Z;
					}
					if (container->user->m_nChangeCnt > 3)
					{
						container->user->m_myActor.fXPos = Fv.X;
						container->user->m_myActor.fYPos = Fv.Y;
						container->user->m_myActor.fZPos = Fv.Z;
					}*/
					//container->user->m_myActor.nType = 0;
					//container->user->m_myActor.dwReceiveDataTime = GetTickCountMs();
					continue;
				}
			}
		}
	LABEL2:
		reader.nPos = j;
		reader.ReadByteData(&byteFilterHeader, 1);
		if ((byteFilterHeader == 0x4C))
		{
			reader.SerializeIntPacked(nBunchLen);
			if (nBunchLen == 102)
			{
				nBunchLen = nBunchLen;
			}
			nPosTemp = reader.nPos;
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				parser.ReadPackedVector<1, 27>(Fv, reader);
			}
			bReadNext = reader.ReadBit();
			if (bReadNext)
			{
				reader.ReadByteData((BYTE*)& nTemp, 2);
				nTemp = nTemp & 0xFFFF;
				reader.ReadByteData((BYTE*)& nTemp, 2);
				nTemp = nTemp & 0xFFFF;
			}
			if (((reader.nPos - nPosTemp) == nBunchLen))
			{
				if ((Fv.X > 10000) && (Fv.X < 800000) && (Fv.Y > 10000) && (Fv.Y < 800000) && (Fv.Z > -10000) && (Fv.Z < 150001))
				{
					//container->user->m_fMyDirYaw = (float)(nTemp) / (65535.0) * 360;
				}
			}
		}

	}
}
