#include "pch.h"
#include "Sonic.h"
#include "Tails.h"
#include "Knuckles.h"

//Macros
#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

static bool EnableSonic = true;
static bool EnableTails = true;
static bool EnableKnux = true;

Trampoline* LoadRegObjTextures_b = nullptr;
Trampoline* FreeRegObjTexlists_b = nullptr;

static NJS_TEXNAME MSonGUI_TEXNAME[3] = {};
static NJS_TEXLIST MSonGUI_TEXLIST = { arrayptrandlengthT(MSonGUI_TEXNAME, int) };
static NJS_TEXNAME MMilesGUI_TEXNAME[3] = {};
static NJS_TEXLIST MMilesGUI_TEXLIST = { arrayptrandlengthT(MMilesGUI_TEXNAME, int) };
static NJS_TEXNAME MKnuxGUI_TEXNAME[2] = {};
static NJS_TEXLIST MKnuxGUI_TEXLIST = { arrayptrandlengthT(MKnuxGUI_TEXNAME, int) };

static void __cdecl LoadRegObjTextures_r(int a1)
{
	if (EnableSonic)
	{
		LoadPVM("MSonGUI", &MSonGUI_TEXLIST);
	}

	if (EnableTails)
	{
		LoadPVM("MMilesGUI", &MMilesGUI_TEXLIST);
	}

	if (EnableKnux)
	{
		LoadPVM("MKnuxGUI", &MKnuxGUI_TEXLIST);
	}
	((decltype(LoadRegObjTextures_r)*)LoadRegObjTextures_b->Target())(a1);
}

static void __cdecl FreeRegObjTexlists_r()
{
	njReleaseTexture(&MSonGUI_TEXLIST);
	njReleaseTexture(&MMilesGUI_TEXLIST);
	njReleaseTexture(&MKnuxGUI_TEXLIST);
	((decltype(FreeRegObjTexlists_r)*)FreeRegObjTexlists_b->Target())();
}

void MovieGUI_Init()
{
	LoadRegObjTextures_b = new Trampoline(0x4212E0, 0x4212E5, LoadRegObjTextures_r, false);
	FreeRegObjTexlists_b = new Trampoline(0x420F40, 0x420F45, FreeRegObjTexlists_r, false);
}

static void __cdecl EV_SetFace_r(task* tp, const char* str);
Trampoline EV_SetFace_t(0x4310D0, 0x4310D6, EV_SetFace_r);
static void __cdecl EV_SetFace_r(task* tp, const char* str)
{
	if (EnableSonic)
	{
		if (tp && tp->twp->counter.b[1] == Characters_Sonic)
		{
			return;
		}
	}
	
	if (EnableTails)
	{
		if (tp && tp->twp->counter.b[1] == Characters_Tails)
		{
			return;
		}
	}
	
	if (EnableKnux)
	{
		if (tp && tp->twp->counter.b[1] == Characters_Knuckles)
		{
			return;
		}
	}

	((decltype(EV_SetFace_r)*)EV_SetFace_t.Target())(tp, str);
}

uint16_t Sonic_UpperArmIndices_movie[] = {
	7, 4,
	4, 1,
	3, 0,
	5, 2,
	6, 3,
	20, 5,
	21, 6,
};

uint16_t Sonic_LowerArmIndices_movie[] = {
	10, 5,
	8, 1,
	9, 0,
	11, 2,
	7, 10,
	13, 12,
	12, 11,
};

uint16_t Sonic_KneeIndices_movie[] = {
	1, 1,
	11, 11,
	12, 12,
	13, 13,
	10, 10,
	9, 9,
	0, 0,
};

uint16_t Sonic_LegIndices_movie[] = {
	5, 5,
	8, 10,
	7, 9,
	6, 7,
	4, 2,
	2, 0,
	3, 1,
};

uint16_t Sonic_ShoeIndices_movie[] = {
	32, 15,
	24, 8,
	25, 13,
	14, 7,
	35, 17,
	40, 34,
	39, 33,
	33, 16,
	38, 31,
	30, 14,
};

uint16_t Sonic_HandIndices_movie[] = {
	7, 1,
	6, 0,
	10, 3,
	30, 81,
	25, 80,
	45, 117,
	24, 72,
	23, 71,
	31, 84,
	21, 70,
	20, 69,
	16, 21,
	8, 2,
};

uint16_t Tails_UpperArmIndices_movie[] = {
	48, 23,
	41, 9,
	40, 7,
	47, 21,
	38, 3,
	39, 5,
	46, 19,
	45, 17,
	37, 0,
	44, 14,
	43, 13,
	42, 10,
};

uint16_t Tails_LowerArmIndices_movie[] = {
	22, 95,
	8, 88,
	6, 87,
	20, 94,
	2, 85,
	4, 86,
	18, 93,
	16, 92,
	1, 84,
	15, 91,
	12, 90,
	11, 89,
};

uint16_t Tails_KneeIndices_movie[] = {
	19, 16,
	20, 18,
	14, 6,
	16, 11,
	17, 12,
	21, 20,
	15, 8,
	18, 14,
	11, 0,
	12, 2,
	13, 4,
};

uint16_t Tails_LegIndices_movie[] = {
	17, 116,
	19, 117,
	7, 111,
	10, 113,
	13, 114,
	21, 118,
	9, 112,
	15, 115,
	1, 108,
	3, 109,
	5, 110,
};

uint16_t Tails_HandIndices_movie[] = {
	36, 133,
	34, 130,
	33, 129,
	31, 126,
	32, 127,
	2, 0,
	3, 3,
	5, 4,
	6, 5,
	8, 8,
	10, 10,
	18, 11,
	19, 12,
	20, 13,
	22, 123,
	21, 122,
	23, 124,
	37, 134,
};

uint16_t Tails_ShoeIndices_movie[] = {
	45, 85,
	46, 86,
	40, 78,
	12, 5,
	10, 4,
	8, 3,
	5, 2,
	3, 1,
	1, 0,
	18, 14,
	15, 20,
	16, 26,
	18, 56,
	17, 55,
};

uint16_t Knuckles_UpperArmIndices_movie[] = {
	7, 8,
	6, 2,
	4, 1,
	3, 0,
	21, 16,
	18, 15,
	14, 14,
	12, 13,
	9, 12,
};

uint16_t Knuckles_LowerArmIndices_movie[] = {
	6, 11,
	5, 8,
	4, 6,
	3, 5,
	17, 20,
	11, 19,
	10, 17,
	9, 15,
	7, 13,
};

uint16_t Knuckles_KneeIndices_movie[] = {
	8, 6,
	9, 8,
	5, 10,
	6, 11,
	7, 9,
	10, 7,
};

uint16_t Knuckles_LegIndices_movie[] = {
	0, 176,
	2, 178,
	4, 180,
	5, 181,
	3, 179,
	1, 177,
};

uint16_t Knuckles_HandIndices_movie[] = {
	2, 136,
	3, 138,
	5, 139,
	6, 134,
	8, 131,
	10, 124,
	13, 130,
	11, 117,
	9, 123,
	7, 126,
	4, 133,
	1, 135,
	0, 137,
};

uint16_t Knuckles_ShoeIndices_movie[] = {
	187, 89,
	186, 88,
	98, 48,
	236, 90,
	106, 78,
	184, 79,
	185, 80,
	4, 36,
	44, 44,
	3, 31,
	92, 46,
	93, 47,
	71, 45,
	2, 6,
	1, 3,
	0, 1,
};

void InitSonicWeldInfo_movie();
Trampoline InitSonicWeldInfo_t((int)InitSonicWeldInfo, (int)InitSonicWeldInfo + 0x5, InitSonicWeldInfo_movie);
void InitSonicWeldInfo_movie() {
	VoidFunc(original, InitSonicWeldInfo_t.Target());
	original(); // For Metal Sonic compatibility with other mods

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_movie) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_movie;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_movie) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_movie;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_movie) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_movie;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_movie;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_movie) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_movie) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_movie;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_movie) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_movie;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_movie;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_movie) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_movie) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_movie;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_movie) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_movie;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_movie;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_movie) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_movie) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_movie;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_movie) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_movie;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_movie) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices_movie;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_movie) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices_movie;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_movie) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_movie;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_movie) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_movie;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_movie) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_movie;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_movie) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_movie;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_movie) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_movie;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_movie) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_movie;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_movie) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LegIndices_movie;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_movie;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_movie) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_movie) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LegIndices_movie;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_movie) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_ShoeIndices_movie;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_movie) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_ShoeIndices_movie;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_movie) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_movie;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_movie;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_movie) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_movie) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_movie;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_movie;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_movie) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_movie()
{
	NJS_OBJECT* v0; // ebp
	NJS_OBJECT* v1; // ebp
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // ebp
	NJS_OBJECT* v4; // eax

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_movie;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = 4;
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = 4;
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_movie;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = 4;
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_movie;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_movie;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = 4;
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = 4;
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_movie;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = 4;
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = (unsigned __int16*)Sonic_LegIndices_movie;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = 4;
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_movie;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = (unsigned __int16*)Sonic_LegIndices_movie;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = 4;
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = 11;
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = (unsigned __int16*)Sonic_ShoeIndices_movie;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = (unsigned __int16*)Sonic_ShoeIndices_movie;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = 11;
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = 7;
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = (unsigned __int16*)Sonic_HandIndices_movie;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = 7;
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = (unsigned __int16*)Sonic_HandIndices_movie;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = 9;
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = (unsigned __int16*)Sonic_ShoeIndices_movie;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = (unsigned __int16*)Sonic_ShoeIndices_movie;
	NPCSonicWeldInfo[13].VertexPairCount = 9;
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	*(_DWORD*)&NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = 4;
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_movie;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void __cdecl InitTailsWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // edx@1
	NJS_OBJECT* v4; // edx@1
	NJS_OBJECT* v5; // eax@1

	TailsWeldInfo[0].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[0].ModelA = MILES_OBJECTS[20];
	TailsWeldInfo[0].ModelB = MILES_OBJECTS[21];
	TailsWeldInfo[0].anonymous_5 = 0;
	TailsWeldInfo[0].VertexBuffer = 0;
	TailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	TailsWeldInfo[0].WeldType = 2;
	TailsWeldInfo[0].VertIndexes = Tails_UpperArmIndices_movie;
	TailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
	TailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
	TailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	TailsWeldInfo[1].WeldType = 2;
	TailsWeldInfo[1].anonymous_5 = 0;
	TailsWeldInfo[1].VertexBuffer = 0;
	TailsWeldInfo[1].VertIndexes = Tails_LowerArmIndices_movie;
	TailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
	v0 = MILES_OBJECTS[24];
	TailsWeldInfo[2].VertIndexes = Tails_UpperArmIndices_movie;
	TailsWeldInfo[2].ModelB = v0;
	TailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	TailsWeldInfo[2].WeldType = 2;
	TailsWeldInfo[2].anonymous_5 = 0;
	TailsWeldInfo[2].VertexBuffer = 0;
	TailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
	TailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
	TailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	TailsWeldInfo[3].WeldType = 2;
	TailsWeldInfo[3].anonymous_5 = 0;
	TailsWeldInfo[3].VertexBuffer = 0;
	TailsWeldInfo[3].VertIndexes = Tails_LowerArmIndices_movie;
	TailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
	TailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
	TailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	TailsWeldInfo[4].WeldType = 2;
	TailsWeldInfo[4].anonymous_5 = 0;
	TailsWeldInfo[4].VertexBuffer = 0;
	TailsWeldInfo[4].VertIndexes = Tails_KneeIndices_movie;
	TailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
	TailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
	TailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	TailsWeldInfo[5].WeldType = 2;
	TailsWeldInfo[5].anonymous_5 = 0;
	TailsWeldInfo[5].VertexBuffer = 0;
	TailsWeldInfo[5].VertIndexes = Tails_LegIndices_movie;
	TailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
	TailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
	TailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	TailsWeldInfo[6].WeldType = 2;
	TailsWeldInfo[6].anonymous_5 = 0;
	TailsWeldInfo[6].VertexBuffer = 0;
	TailsWeldInfo[6].VertIndexes = Tails_KneeIndices_movie;
	TailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
	TailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
	TailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	TailsWeldInfo[7].WeldType = 2;
	TailsWeldInfo[7].anonymous_5 = 0;
	TailsWeldInfo[7].VertexBuffer = 0;
	TailsWeldInfo[7].VertIndexes = Tails_LegIndices_movie;
	TailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
	TailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
	TailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	TailsWeldInfo[8].WeldType = 2;
	TailsWeldInfo[8].anonymous_5 = 0;
	TailsWeldInfo[8].VertexBuffer = 0;
	TailsWeldInfo[8].VertIndexes = Tails_ShoeIndices_movie;
	TailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
	v1 = MILES_OBJECTS[35];
	TailsWeldInfo[9].VertIndexes = Tails_ShoeIndices_movie;
	TailsWeldInfo[9].ModelB = v1;
	TailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	TailsWeldInfo[9].WeldType = 2;
	TailsWeldInfo[9].anonymous_5 = 0;
	TailsWeldInfo[9].VertexBuffer = 0;
	TailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
	TailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
	TailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	TailsWeldInfo[10].WeldType = 2;
	TailsWeldInfo[10].anonymous_5 = 0;
	TailsWeldInfo[10].VertexBuffer = 0;
	TailsWeldInfo[10].VertIndexes = Tails_HandIndices_movie;
	TailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
	TailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
	TailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	TailsWeldInfo[11].WeldType = 2;
	TailsWeldInfo[11].anonymous_5 = 0;
	TailsWeldInfo[11].VertexBuffer = 0;
	TailsWeldInfo[11].VertIndexes = Tails_HandIndices_movie;
	TailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
	TailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
	TailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	TailsWeldInfo[12].WeldType = 2;
	TailsWeldInfo[12].anonymous_5 = 0;
	TailsWeldInfo[12].VertexBuffer = 0;
	TailsWeldInfo[12].VertIndexes = Tails_UpperArmIndices_movie;
	TailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
	TailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
	TailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	TailsWeldInfo[13].WeldType = 2;
	TailsWeldInfo[13].anonymous_5 = 0;
	TailsWeldInfo[13].VertexBuffer = 0;
	TailsWeldInfo[13].VertIndexes = Tails_LowerArmIndices_movie;
	TailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
	TailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
	TailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	TailsWeldInfo[14].WeldType = 2;
	TailsWeldInfo[14].anonymous_5 = 0;
	TailsWeldInfo[14].VertexBuffer = 0;
	TailsWeldInfo[14].VertIndexes = Tails_UpperArmIndices_movie;
	TailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
	TailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
	TailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	TailsWeldInfo[15].WeldType = 2;
	TailsWeldInfo[15].anonymous_5 = 0;
	TailsWeldInfo[15].VertexBuffer = 0;
	TailsWeldInfo[15].VertIndexes = Tails_LowerArmIndices_movie;
	TailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
	TailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
	TailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	TailsWeldInfo[16].WeldType = 2;
	TailsWeldInfo[16].anonymous_5 = 0;
	TailsWeldInfo[16].VertexBuffer = 0;
	TailsWeldInfo[16].VertIndexes = Tails_KneeIndices_movie;
	TailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
	TailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
	TailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	TailsWeldInfo[17].WeldType = 2;
	TailsWeldInfo[17].anonymous_5 = 0;
	TailsWeldInfo[17].VertexBuffer = 0;
	TailsWeldInfo[17].VertIndexes = Tails_LegIndices_movie;
	TailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
	TailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
	TailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	TailsWeldInfo[18].WeldType = 2;
	TailsWeldInfo[18].anonymous_5 = 0;
	TailsWeldInfo[18].VertexBuffer = 0;
	TailsWeldInfo[18].VertIndexes = Tails_KneeIndices_movie;
	TailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
	v2 = MILES_OBJECTS[51];
	TailsWeldInfo[19].VertIndexes = Tails_LegIndices_movie;
	TailsWeldInfo[19].ModelB = v2;
	TailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	TailsWeldInfo[19].WeldType = 2;
	TailsWeldInfo[19].anonymous_5 = 0;
	TailsWeldInfo[19].VertexBuffer = 0;
	TailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
	TailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
	TailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	TailsWeldInfo[20].WeldType = 2;
	TailsWeldInfo[20].anonymous_5 = 0;
	TailsWeldInfo[20].VertexBuffer = 0;
	TailsWeldInfo[20].VertIndexes = Tails_ShoeIndices_movie;
	TailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
	TailsWeldInfo[21].ModelB = MILES_OBJECTS[55];
	TailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	TailsWeldInfo[21].WeldType = 2;
	TailsWeldInfo[21].anonymous_5 = 0;
	TailsWeldInfo[21].VertexBuffer = 0;
	TailsWeldInfo[21].VertIndexes = Tails_ShoeIndices_movie;
	TailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
	TailsWeldInfo[22].ModelB = MILES_OBJECTS[57];
	TailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	TailsWeldInfo[22].WeldType = 2;
	TailsWeldInfo[22].anonymous_5 = 0;
	TailsWeldInfo[22].VertexBuffer = 0;
	TailsWeldInfo[22].VertIndexes = Tails_HandIndices_movie;
	TailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
	TailsWeldInfo[23].ModelB = MILES_OBJECTS[59];
	TailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	TailsWeldInfo[23].WeldType = 2;
	TailsWeldInfo[23].anonymous_5 = 0;
	TailsWeldInfo[23].VertexBuffer = 0;
	TailsWeldInfo[23].VertIndexes = Tails_HandIndices_movie;
	TailsWeldInfo[24].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[24].ModelA = MILES_OBJECTS[37];
	TailsWeldInfo[24].ModelB = 0;
	TailsWeldInfo[24].VertexPairCount = 2;
	TailsWeldInfo[24].WeldType = 4;
	TailsWeldInfo[24].anonymous_5 = 0;
	TailsWeldInfo[24].VertexBuffer = 0;
	TailsWeldInfo[24].VertIndexes = 0;
	TailsWeldInfo[25].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[25].ModelA = MILES_OBJECTS[39];
	TailsWeldInfo[25].ModelB = 0;
	TailsWeldInfo[25].VertexPairCount = 2;
	TailsWeldInfo[25].WeldType = 5;
	TailsWeldInfo[25].anonymous_5 = 0;
	TailsWeldInfo[25].VertexBuffer = 0;
	TailsWeldInfo[25].VertIndexes = 0;
	TailsWeldInfo[26].BaseModel = *MILES_OBJECTS;
	v3 = MILES_OBJECTS[33];
	TailsWeldInfo[26].ModelB = 0;
	TailsWeldInfo[26].VertexPairCount = 0;
	TailsWeldInfo[26].anonymous_5 = 0;
	TailsWeldInfo[26].VertexBuffer = 0;
	TailsWeldInfo[26].VertIndexes = 0;
	TailsWeldInfo[26].ModelA = v3;
	TailsWeldInfo[26].WeldType = 6;
	TailsWeldInfo[27].BaseModel = *MILES_OBJECTS;
	v4 = MILES_OBJECTS[35];
	TailsWeldInfo[27].ModelB = 0;
	TailsWeldInfo[27].VertexPairCount = 0;
	TailsWeldInfo[27].anonymous_5 = 0;
	TailsWeldInfo[27].VertexBuffer = 0;
	TailsWeldInfo[27].VertIndexes = 0;
	TailsWeldInfo[27].ModelA = v4;
	TailsWeldInfo[27].WeldType = 7;
	TailsWeldInfo[28].BaseModel = *MILES_OBJECTS;
	v5 = MILES_OBJECTS[4];
	TailsWeldInfo[28].ModelB = 0;
	TailsWeldInfo[28].VertexPairCount = 0;
	TailsWeldInfo[28].anonymous_5 = 0;
	TailsWeldInfo[28].VertexBuffer = 0;
	TailsWeldInfo[28].VertIndexes = 0;
	TailsWeldInfo[29].BaseModel = 0;
	TailsWeldInfo[29].ModelA = 0;
	TailsWeldInfo[29].ModelB = 0;
	TailsWeldInfo[29].VertexPairCount = 0;
	TailsWeldInfo[29].VertexBuffer = 0;
	TailsWeldInfo[28].ModelA = v5;
	TailsWeldInfo[28].WeldType = 8;
	TailsWeldInfo[29].VertIndexes = 0;
}

void __cdecl InitNPCTailsWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebx@1
	NJS_OBJECT* v4; // esi@1
	NJS_OBJECT* v5; // eax@1

	NPCTailsWeldInfo[0].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[0].ModelA = MILES_OBJECTS[20];
	NPCTailsWeldInfo[0].ModelB = MILES_OBJECTS[21];
	NPCTailsWeldInfo[0].anonymous_5 = 0;
	NPCTailsWeldInfo[0].VertexBuffer = 0;
	NPCTailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	NPCTailsWeldInfo[0].WeldType = 2;
	NPCTailsWeldInfo[0].VertIndexes = Tails_UpperArmIndices_movie;
	NPCTailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
	NPCTailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
	NPCTailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	NPCTailsWeldInfo[1].WeldType = 2;
	NPCTailsWeldInfo[1].anonymous_5 = 0;
	NPCTailsWeldInfo[1].VertexBuffer = 0;
	NPCTailsWeldInfo[1].VertIndexes = Tails_LowerArmIndices_movie;
	NPCTailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
	v0 = MILES_OBJECTS[24];
	NPCTailsWeldInfo[2].VertIndexes = Tails_UpperArmIndices_movie;
	NPCTailsWeldInfo[2].ModelB = v0;
	NPCTailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	NPCTailsWeldInfo[2].WeldType = 2;
	NPCTailsWeldInfo[2].anonymous_5 = 0;
	NPCTailsWeldInfo[2].VertexBuffer = 0;
	NPCTailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
	NPCTailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
	NPCTailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	NPCTailsWeldInfo[3].WeldType = 2;
	NPCTailsWeldInfo[3].anonymous_5 = 0;
	NPCTailsWeldInfo[3].VertexBuffer = 0;
	NPCTailsWeldInfo[3].VertIndexes = Tails_LowerArmIndices_movie;
	NPCTailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
	NPCTailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
	NPCTailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	NPCTailsWeldInfo[4].WeldType = 2;
	NPCTailsWeldInfo[4].anonymous_5 = 0;
	NPCTailsWeldInfo[4].VertexBuffer = 0;
	NPCTailsWeldInfo[4].VertIndexes = Tails_KneeIndices_movie;
	NPCTailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
	NPCTailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
	NPCTailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	NPCTailsWeldInfo[5].WeldType = 2;
	NPCTailsWeldInfo[5].anonymous_5 = 0;
	NPCTailsWeldInfo[5].VertexBuffer = 0;
	NPCTailsWeldInfo[5].VertIndexes = Tails_LegIndices_movie;
	NPCTailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
	NPCTailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
	NPCTailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	NPCTailsWeldInfo[6].WeldType = 2;
	NPCTailsWeldInfo[6].anonymous_5 = 0;
	NPCTailsWeldInfo[6].VertexBuffer = 0;
	NPCTailsWeldInfo[6].VertIndexes = Tails_KneeIndices_movie;
	NPCTailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
	NPCTailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
	NPCTailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	NPCTailsWeldInfo[7].WeldType = 2;
	NPCTailsWeldInfo[7].anonymous_5 = 0;
	NPCTailsWeldInfo[7].VertexBuffer = 0;
	NPCTailsWeldInfo[7].VertIndexes = Tails_LegIndices_movie;
	NPCTailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
	NPCTailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
	NPCTailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	NPCTailsWeldInfo[8].WeldType = 2;
	NPCTailsWeldInfo[8].anonymous_5 = 0;
	NPCTailsWeldInfo[8].VertexBuffer = 0;
	NPCTailsWeldInfo[8].VertIndexes = Tails_ShoeIndices_movie;
	NPCTailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
	v1 = MILES_OBJECTS[35];
	NPCTailsWeldInfo[9].VertIndexes = Tails_ShoeIndices_movie;
	NPCTailsWeldInfo[9].ModelB = v1;
	NPCTailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	NPCTailsWeldInfo[9].WeldType = 2;
	NPCTailsWeldInfo[9].anonymous_5 = 0;
	NPCTailsWeldInfo[9].VertexBuffer = 0;
	NPCTailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
	NPCTailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
	NPCTailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	NPCTailsWeldInfo[10].WeldType = 2;
	NPCTailsWeldInfo[10].anonymous_5 = 0;
	NPCTailsWeldInfo[10].VertexBuffer = 0;
	NPCTailsWeldInfo[10].VertIndexes = Tails_HandIndices_movie;
	NPCTailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
	NPCTailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
	NPCTailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	NPCTailsWeldInfo[11].WeldType = 2;
	NPCTailsWeldInfo[11].anonymous_5 = 0;
	NPCTailsWeldInfo[11].VertexBuffer = 0;
	NPCTailsWeldInfo[11].VertIndexes = Tails_HandIndices_movie;
	NPCTailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
	NPCTailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
	NPCTailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	NPCTailsWeldInfo[12].WeldType = 2;
	NPCTailsWeldInfo[12].anonymous_5 = 0;
	NPCTailsWeldInfo[12].VertexBuffer = 0;
	NPCTailsWeldInfo[12].VertIndexes = Tails_UpperArmIndices_movie;
	NPCTailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
	NPCTailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
	NPCTailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	NPCTailsWeldInfo[13].WeldType = 2;
	NPCTailsWeldInfo[13].anonymous_5 = 0;
	NPCTailsWeldInfo[13].VertexBuffer = 0;
	NPCTailsWeldInfo[13].VertIndexes = Tails_LowerArmIndices_movie;
	NPCTailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
	NPCTailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
	NPCTailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_movie) / 2);
	NPCTailsWeldInfo[14].WeldType = 2;
	NPCTailsWeldInfo[14].anonymous_5 = 0;
	NPCTailsWeldInfo[14].VertexBuffer = 0;
	NPCTailsWeldInfo[14].VertIndexes = Tails_UpperArmIndices_movie;
	NPCTailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
	NPCTailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
	NPCTailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_movie) / 2);
	NPCTailsWeldInfo[15].WeldType = 2;
	NPCTailsWeldInfo[15].anonymous_5 = 0;
	NPCTailsWeldInfo[15].VertexBuffer = 0;
	NPCTailsWeldInfo[15].VertIndexes = Tails_LowerArmIndices_movie;
	NPCTailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
	NPCTailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
	NPCTailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	NPCTailsWeldInfo[16].WeldType = 2;
	NPCTailsWeldInfo[16].anonymous_5 = 0;
	NPCTailsWeldInfo[16].VertexBuffer = 0;
	NPCTailsWeldInfo[16].VertIndexes = Tails_KneeIndices_movie;
	NPCTailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
	NPCTailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
	NPCTailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	NPCTailsWeldInfo[17].WeldType = 2;
	NPCTailsWeldInfo[17].anonymous_5 = 0;
	NPCTailsWeldInfo[17].VertexBuffer = 0;
	NPCTailsWeldInfo[17].VertIndexes = Tails_LegIndices_movie;
	NPCTailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
	NPCTailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
	NPCTailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_KneeIndices_movie) / 2);
	NPCTailsWeldInfo[18].WeldType = 2;
	NPCTailsWeldInfo[18].anonymous_5 = 0;
	NPCTailsWeldInfo[18].VertexBuffer = 0;
	NPCTailsWeldInfo[18].VertIndexes = Tails_KneeIndices_movie;
	NPCTailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
	v2 = MILES_OBJECTS[51];
	NPCTailsWeldInfo[19].anonymous_5 = 0;
	NPCTailsWeldInfo[19].VertexBuffer = 0;
	NPCTailsWeldInfo[19].VertIndexes = Tails_LegIndices_movie;
	NPCTailsWeldInfo[19].ModelB = v2;
	NPCTailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_movie) / 2);
	NPCTailsWeldInfo[19].WeldType = 2;
	NPCTailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
	NPCTailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
	NPCTailsWeldInfo[20].anonymous_5 = 0;
	NPCTailsWeldInfo[20].VertexBuffer = 0;
	NPCTailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	NPCTailsWeldInfo[20].WeldType = 2;
	NPCTailsWeldInfo[20].VertIndexes = Tails_ShoeIndices_movie;
	NPCTailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
	v3 = MILES_OBJECTS[55];
	NPCTailsWeldInfo[21].anonymous_5 = 0;
	NPCTailsWeldInfo[21].VertexBuffer = 0;
	NPCTailsWeldInfo[21].ModelB = v3;
	NPCTailsWeldInfo[21].VertIndexes = Tails_ShoeIndices_movie;
	NPCTailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_movie) / 2);
	NPCTailsWeldInfo[21].WeldType = 2;
	NPCTailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
	v4 = MILES_OBJECTS[57];
	NPCTailsWeldInfo[22].anonymous_5 = 0;
	NPCTailsWeldInfo[22].VertexBuffer = 0;
	NPCTailsWeldInfo[22].ModelB = v4;
	NPCTailsWeldInfo[22].VertIndexes = Tails_HandIndices_movie;
	NPCTailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	NPCTailsWeldInfo[22].WeldType = 2;
	NPCTailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
	v5 = MILES_OBJECTS[59];
	NPCTailsWeldInfo[23].anonymous_5 = 0;
	NPCTailsWeldInfo[23].VertexBuffer = 0;
	NPCTailsWeldInfo[24].BaseModel = 0;
	NPCTailsWeldInfo[24].ModelA = 0;
	NPCTailsWeldInfo[23].VertIndexes = Tails_HandIndices_movie;
	NPCTailsWeldInfo[24].ModelB = 0;
	NPCTailsWeldInfo[24].VertexPairCount = 0;
	NPCTailsWeldInfo[24].VertexBuffer = 0;
	NPCTailsWeldInfo[23].ModelB = v5;
	NPCTailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_movie) / 2);
	NPCTailsWeldInfo[23].WeldType = 2;
	NPCTailsWeldInfo[24].VertIndexes = 0;
}

void __cdecl InitKnucklesWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // edx@1
	NJS_OBJECT* v4; // edx@1
	NJS_OBJECT* v5; // eax@1

	KnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
	KnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[0].anonymous_5 = 0;
	KnucklesWeldInfo[0].VertexBuffer = 0;
	KnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	KnucklesWeldInfo[0].WeldType = 2;
	KnucklesWeldInfo[0].VertIndexes = Knuckles_UpperArmIndices_movie;
	KnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	KnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	KnucklesWeldInfo[1].WeldType = 2;
	KnucklesWeldInfo[1].anonymous_5 = 0;
	KnucklesWeldInfo[1].VertexBuffer = 0;
	KnucklesWeldInfo[1].VertIndexes = Knuckles_LowerArmIndices_movie;
	KnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[2].VertIndexes = Knuckles_UpperArmIndices_movie;
	KnucklesWeldInfo[2].ModelB = v0;
	KnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	KnucklesWeldInfo[2].WeldType = 2;
	KnucklesWeldInfo[2].anonymous_5 = 0;
	KnucklesWeldInfo[2].VertexBuffer = 0;
	KnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	KnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	KnucklesWeldInfo[3].WeldType = 2;
	KnucklesWeldInfo[3].anonymous_5 = 0;
	KnucklesWeldInfo[3].VertexBuffer = 0;
	KnucklesWeldInfo[3].VertIndexes = Knuckles_LowerArmIndices_movie;
	KnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	KnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	KnucklesWeldInfo[4].WeldType = 2;
	KnucklesWeldInfo[4].anonymous_5 = 0;
	KnucklesWeldInfo[4].VertexBuffer = 0;
	KnucklesWeldInfo[4].VertIndexes = Knuckles_KneeIndices_movie;
	KnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	KnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	KnucklesWeldInfo[5].WeldType = 2;
	KnucklesWeldInfo[5].anonymous_5 = 0;
	KnucklesWeldInfo[5].VertexBuffer = 0;
	KnucklesWeldInfo[5].VertIndexes = Knuckles_LegIndices_movie;
	KnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	KnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	KnucklesWeldInfo[6].WeldType = 2;
	KnucklesWeldInfo[6].anonymous_5 = 0;
	KnucklesWeldInfo[6].VertexBuffer = 0;
	KnucklesWeldInfo[6].VertIndexes = Knuckles_KneeIndices_movie;
	KnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	KnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	KnucklesWeldInfo[7].WeldType = 2;
	KnucklesWeldInfo[7].anonymous_5 = 0;
	KnucklesWeldInfo[7].VertexBuffer = 0;
	KnucklesWeldInfo[7].VertIndexes = Knuckles_LegIndices_movie;
	KnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	KnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	KnucklesWeldInfo[8].WeldType = 2;
	KnucklesWeldInfo[8].anonymous_5 = 0;
	KnucklesWeldInfo[8].VertexBuffer = 0;
	KnucklesWeldInfo[8].VertIndexes = Knuckles_ShoeIndices_movie;
	KnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[9].VertIndexes = Knuckles_ShoeIndices_movie;
	KnucklesWeldInfo[9].ModelB = v1;
	KnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	KnucklesWeldInfo[9].WeldType = 2;
	KnucklesWeldInfo[9].anonymous_5 = 0;
	KnucklesWeldInfo[9].VertexBuffer = 0;
	KnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	KnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	KnucklesWeldInfo[10].WeldType = 2;
	KnucklesWeldInfo[10].anonymous_5 = 0;
	KnucklesWeldInfo[10].VertexBuffer = 0;
	KnucklesWeldInfo[10].VertIndexes = Knuckles_HandIndices_movie;
	KnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	KnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	KnucklesWeldInfo[11].WeldType = 2;
	KnucklesWeldInfo[11].anonymous_5 = 0;
	KnucklesWeldInfo[11].VertexBuffer = 0;
	KnucklesWeldInfo[11].VertIndexes = Knuckles_HandIndices_movie;
	KnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	KnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	KnucklesWeldInfo[12].WeldType = 2;
	KnucklesWeldInfo[12].anonymous_5 = 0;
	KnucklesWeldInfo[12].VertexBuffer = 0;
	KnucklesWeldInfo[12].VertIndexes = Knuckles_UpperArmIndices_movie;
	KnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	KnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	KnucklesWeldInfo[13].WeldType = 2;
	KnucklesWeldInfo[13].anonymous_5 = 0;
	KnucklesWeldInfo[13].VertexBuffer = 0;
	KnucklesWeldInfo[13].VertIndexes = Knuckles_LowerArmIndices_movie;
	KnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	KnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	KnucklesWeldInfo[14].WeldType = 2;
	KnucklesWeldInfo[14].anonymous_5 = 0;
	KnucklesWeldInfo[14].VertexBuffer = 0;
	KnucklesWeldInfo[14].VertIndexes = Knuckles_UpperArmIndices_movie;
	KnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	KnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	KnucklesWeldInfo[15].WeldType = 2;
	KnucklesWeldInfo[15].anonymous_5 = 0;
	KnucklesWeldInfo[15].VertexBuffer = 0;
	KnucklesWeldInfo[15].VertIndexes = Knuckles_LowerArmIndices_movie;
	KnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	KnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	KnucklesWeldInfo[16].WeldType = 2;
	KnucklesWeldInfo[16].anonymous_5 = 0;
	KnucklesWeldInfo[16].VertexBuffer = 0;
	KnucklesWeldInfo[16].VertIndexes = Knuckles_KneeIndices_movie;
	KnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	KnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	KnucklesWeldInfo[17].WeldType = 2;
	KnucklesWeldInfo[17].anonymous_5 = 0;
	KnucklesWeldInfo[17].VertexBuffer = 0;
	KnucklesWeldInfo[17].VertIndexes = Knuckles_LegIndices_movie;
	KnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	KnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	KnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	KnucklesWeldInfo[18].WeldType = 2;
	KnucklesWeldInfo[18].anonymous_5 = 0;
	KnucklesWeldInfo[18].VertexBuffer = 0;
	KnucklesWeldInfo[18].VertIndexes = Knuckles_KneeIndices_movie;
	KnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	KnucklesWeldInfo[19].VertIndexes = Knuckles_LegIndices_movie;
	KnucklesWeldInfo[19].ModelB = v2;
	KnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	KnucklesWeldInfo[19].WeldType = 2;
	KnucklesWeldInfo[19].anonymous_5 = 0;
	KnucklesWeldInfo[19].VertexBuffer = 0;
	KnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	KnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	KnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	KnucklesWeldInfo[20].WeldType = 2;
	KnucklesWeldInfo[20].anonymous_5 = 0;
	KnucklesWeldInfo[20].VertexBuffer = 0;
	KnucklesWeldInfo[20].VertIndexes = Knuckles_ShoeIndices_movie;
	KnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	KnucklesWeldInfo[21].ModelB = KNUCKLES_OBJECTS[41];
	KnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	KnucklesWeldInfo[21].WeldType = 2;
	KnucklesWeldInfo[21].anonymous_5 = 0;
	KnucklesWeldInfo[21].VertexBuffer = 0;
	KnucklesWeldInfo[21].VertIndexes = Knuckles_ShoeIndices_movie;
	KnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	KnucklesWeldInfo[22].ModelB = KNUCKLES_OBJECTS[27];
	KnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	KnucklesWeldInfo[22].WeldType = 2;
	KnucklesWeldInfo[22].anonymous_5 = 0;
	KnucklesWeldInfo[22].VertexBuffer = 0;
	KnucklesWeldInfo[22].VertIndexes = Knuckles_HandIndices_movie;
	KnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	KnucklesWeldInfo[23].ModelB = KNUCKLES_OBJECTS[31];
	KnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	KnucklesWeldInfo[23].WeldType = 2;
	KnucklesWeldInfo[23].anonymous_5 = 0;
	KnucklesWeldInfo[23].VertexBuffer = 0;
	KnucklesWeldInfo[23].VertIndexes = Knuckles_HandIndices_movie;
	KnucklesWeldInfo[24].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[24].ModelA = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[24].ModelB = 0;
	KnucklesWeldInfo[24].VertexPairCount = 2;
	KnucklesWeldInfo[24].WeldType = 4;
	KnucklesWeldInfo[24].anonymous_5 = 0;
	KnucklesWeldInfo[24].VertexBuffer = 0;
	KnucklesWeldInfo[24].VertIndexes = 0;
	KnucklesWeldInfo[25].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[25].ModelA = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[25].ModelB = 0;
	KnucklesWeldInfo[25].VertexPairCount = 2;
	KnucklesWeldInfo[25].WeldType = 5;
	KnucklesWeldInfo[25].anonymous_5 = 0;
	KnucklesWeldInfo[25].VertexBuffer = 0;
	KnucklesWeldInfo[25].VertIndexes = 0;
	KnucklesWeldInfo[26].BaseModel = *KNUCKLES_OBJECTS;
	v3 = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[26].ModelB = 0;
	KnucklesWeldInfo[26].VertexPairCount = 0;
	KnucklesWeldInfo[26].anonymous_5 = 0;
	KnucklesWeldInfo[26].VertexBuffer = 0;
	KnucklesWeldInfo[26].VertIndexes = 0;
	KnucklesWeldInfo[26].ModelA = v3;
	KnucklesWeldInfo[26].WeldType = 6;
	KnucklesWeldInfo[27].BaseModel = *KNUCKLES_OBJECTS;
	v4 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[27].ModelB = 0;
	KnucklesWeldInfo[27].VertexPairCount = 0;
	KnucklesWeldInfo[27].anonymous_5 = 0;
	KnucklesWeldInfo[27].VertexBuffer = 0;
	KnucklesWeldInfo[27].VertIndexes = 0;
	KnucklesWeldInfo[27].ModelA = v4;
	KnucklesWeldInfo[27].WeldType = 7;
	KnucklesWeldInfo[28].BaseModel = *KNUCKLES_OBJECTS;
	v5 = KNUCKLES_OBJECTS[54];
	KnucklesWeldInfo[28].ModelB = 0;
	KnucklesWeldInfo[28].VertexPairCount = 0;
	KnucklesWeldInfo[28].anonymous_5 = 0;
	KnucklesWeldInfo[28].VertexBuffer = 0;
	KnucklesWeldInfo[28].VertIndexes = 0;
	KnucklesWeldInfo[29].BaseModel = 0;
	KnucklesWeldInfo[29].ModelA = 0;
	KnucklesWeldInfo[29].ModelB = 0;
	KnucklesWeldInfo[29].VertexPairCount = 0;
	KnucklesWeldInfo[29].VertexBuffer = 0;
	KnucklesWeldInfo[28].ModelA = v5;
	KnucklesWeldInfo[28].WeldType = 8;
	KnucklesWeldInfo[29].VertIndexes = 0;
}

void __cdecl InitNPCKnucklesWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebx@1
	NJS_OBJECT* v4; // esi@1
	NJS_OBJECT* v5; // eax@1

	NPCKnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
	NPCKnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[0].anonymous_5 = 0;
	NPCKnucklesWeldInfo[0].VertexBuffer = 0;
	NPCKnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[0].WeldType = 2;
	NPCKnucklesWeldInfo[0].VertIndexes = Knuckles_UpperArmIndices_movie;
	NPCKnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	NPCKnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[1].WeldType = 2;
	NPCKnucklesWeldInfo[1].anonymous_5 = 0;
	NPCKnucklesWeldInfo[1].VertexBuffer = 0;
	NPCKnucklesWeldInfo[1].VertIndexes = Knuckles_LowerArmIndices_movie;
	NPCKnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[2].VertIndexes = Knuckles_UpperArmIndices_movie;
	NPCKnucklesWeldInfo[2].ModelB = v0;
	NPCKnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[2].WeldType = 2;
	NPCKnucklesWeldInfo[2].anonymous_5 = 0;
	NPCKnucklesWeldInfo[2].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	NPCKnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[3].WeldType = 2;
	NPCKnucklesWeldInfo[3].anonymous_5 = 0;
	NPCKnucklesWeldInfo[3].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].VertIndexes = Knuckles_LowerArmIndices_movie;
	NPCKnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	NPCKnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	NPCKnucklesWeldInfo[4].WeldType = 2;
	NPCKnucklesWeldInfo[4].anonymous_5 = 0;
	NPCKnucklesWeldInfo[4].VertexBuffer = 0;
	NPCKnucklesWeldInfo[4].VertIndexes = Knuckles_KneeIndices_movie;
	NPCKnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	NPCKnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	NPCKnucklesWeldInfo[5].WeldType = 2;
	NPCKnucklesWeldInfo[5].anonymous_5 = 0;
	NPCKnucklesWeldInfo[5].VertexBuffer = 0;
	NPCKnucklesWeldInfo[5].VertIndexes = Knuckles_LegIndices_movie;
	NPCKnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	NPCKnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	NPCKnucklesWeldInfo[6].WeldType = 2;
	NPCKnucklesWeldInfo[6].anonymous_5 = 0;
	NPCKnucklesWeldInfo[6].VertexBuffer = 0;
	NPCKnucklesWeldInfo[6].VertIndexes = Knuckles_KneeIndices_movie;
	NPCKnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	NPCKnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	NPCKnucklesWeldInfo[7].WeldType = 2;
	NPCKnucklesWeldInfo[7].anonymous_5 = 0;
	NPCKnucklesWeldInfo[7].VertexBuffer = 0;
	NPCKnucklesWeldInfo[7].VertIndexes = Knuckles_LegIndices_movie;
	NPCKnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	NPCKnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	NPCKnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	NPCKnucklesWeldInfo[8].WeldType = 2;
	NPCKnucklesWeldInfo[8].anonymous_5 = 0;
	NPCKnucklesWeldInfo[8].VertexBuffer = 0;
	NPCKnucklesWeldInfo[8].VertIndexes = Knuckles_ShoeIndices_movie;
	NPCKnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	NPCKnucklesWeldInfo[9].VertIndexes = Knuckles_ShoeIndices_movie;
	NPCKnucklesWeldInfo[9].ModelB = v1;
	NPCKnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	NPCKnucklesWeldInfo[9].WeldType = 2;
	NPCKnucklesWeldInfo[9].anonymous_5 = 0;
	NPCKnucklesWeldInfo[9].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	NPCKnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	NPCKnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	NPCKnucklesWeldInfo[10].WeldType = 2;
	NPCKnucklesWeldInfo[10].anonymous_5 = 0;
	NPCKnucklesWeldInfo[10].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].VertIndexes = Knuckles_HandIndices_movie;
	NPCKnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	NPCKnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	NPCKnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	NPCKnucklesWeldInfo[11].WeldType = 2;
	NPCKnucklesWeldInfo[11].anonymous_5 = 0;
	NPCKnucklesWeldInfo[11].VertexBuffer = 0;
	NPCKnucklesWeldInfo[11].VertIndexes = Knuckles_HandIndices_movie;
	NPCKnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	NPCKnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[12].WeldType = 2;
	NPCKnucklesWeldInfo[12].anonymous_5 = 0;
	NPCKnucklesWeldInfo[12].VertexBuffer = 0;
	NPCKnucklesWeldInfo[12].VertIndexes = Knuckles_UpperArmIndices_movie;
	NPCKnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	NPCKnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[13].WeldType = 2;
	NPCKnucklesWeldInfo[13].anonymous_5 = 0;
	NPCKnucklesWeldInfo[13].VertexBuffer = 0;
	NPCKnucklesWeldInfo[13].VertIndexes = Knuckles_LowerArmIndices_movie;
	NPCKnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	NPCKnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[14].WeldType = 2;
	NPCKnucklesWeldInfo[14].anonymous_5 = 0;
	NPCKnucklesWeldInfo[14].VertexBuffer = 0;
	NPCKnucklesWeldInfo[14].VertIndexes = Knuckles_UpperArmIndices_movie;
	NPCKnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	NPCKnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_movie) / 2);
	NPCKnucklesWeldInfo[15].WeldType = 2;
	NPCKnucklesWeldInfo[15].anonymous_5 = 0;
	NPCKnucklesWeldInfo[15].VertexBuffer = 0;
	NPCKnucklesWeldInfo[15].VertIndexes = Knuckles_LowerArmIndices_movie;
	NPCKnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	NPCKnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	NPCKnucklesWeldInfo[16].WeldType = 2;
	NPCKnucklesWeldInfo[16].anonymous_5 = 0;
	NPCKnucklesWeldInfo[16].VertexBuffer = 0;
	NPCKnucklesWeldInfo[16].VertIndexes = Knuckles_KneeIndices_movie;
	NPCKnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	NPCKnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	NPCKnucklesWeldInfo[17].WeldType = 2;
	NPCKnucklesWeldInfo[17].anonymous_5 = 0;
	NPCKnucklesWeldInfo[17].VertexBuffer = 0;
	NPCKnucklesWeldInfo[17].VertIndexes = Knuckles_LegIndices_movie;
	NPCKnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	NPCKnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	NPCKnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_KneeIndices_movie) / 2);
	NPCKnucklesWeldInfo[18].WeldType = 2;
	NPCKnucklesWeldInfo[18].anonymous_5 = 0;
	NPCKnucklesWeldInfo[18].VertexBuffer = 0;
	NPCKnucklesWeldInfo[18].VertIndexes = Knuckles_KneeIndices_movie;
	NPCKnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	NPCKnucklesWeldInfo[19].anonymous_5 = 0;
	NPCKnucklesWeldInfo[19].VertexBuffer = 0;
	NPCKnucklesWeldInfo[19].VertIndexes = Knuckles_LegIndices_movie;
	NPCKnucklesWeldInfo[19].ModelB = v2;
	NPCKnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_movie) / 2);
	NPCKnucklesWeldInfo[19].WeldType = 2;
	NPCKnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	NPCKnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	NPCKnucklesWeldInfo[20].anonymous_5 = 0;
	NPCKnucklesWeldInfo[20].VertexBuffer = 0;
	NPCKnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	NPCKnucklesWeldInfo[20].WeldType = 2;
	NPCKnucklesWeldInfo[20].VertIndexes = Knuckles_ShoeIndices_movie;
	NPCKnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	v3 = KNUCKLES_OBJECTS[41];
	NPCKnucklesWeldInfo[21].anonymous_5 = 0;
	NPCKnucklesWeldInfo[21].VertexBuffer = 0;
	NPCKnucklesWeldInfo[21].ModelB = v3;
	NPCKnucklesWeldInfo[21].VertIndexes = Knuckles_ShoeIndices_movie;
	NPCKnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_movie) / 2);
	NPCKnucklesWeldInfo[21].WeldType = 2;
	NPCKnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	v4 = KNUCKLES_OBJECTS[27];
	NPCKnucklesWeldInfo[22].anonymous_5 = 0;
	NPCKnucklesWeldInfo[22].VertexBuffer = 0;
	NPCKnucklesWeldInfo[22].ModelB = v4;
	NPCKnucklesWeldInfo[22].VertIndexes = Knuckles_HandIndices_movie;
	NPCKnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	NPCKnucklesWeldInfo[22].WeldType = 2;
	NPCKnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	v5 = KNUCKLES_OBJECTS[31];
	NPCKnucklesWeldInfo[23].anonymous_5 = 0;
	NPCKnucklesWeldInfo[23].VertexBuffer = 0;
	NPCKnucklesWeldInfo[24].BaseModel = 0;
	NPCKnucklesWeldInfo[24].ModelA = 0;
	NPCKnucklesWeldInfo[23].VertIndexes = Knuckles_HandIndices_movie;
	NPCKnucklesWeldInfo[24].ModelB = 0;
	NPCKnucklesWeldInfo[24].VertexPairCount = 0;
	NPCKnucklesWeldInfo[24].VertexBuffer = 0;
	NPCKnucklesWeldInfo[23].ModelB = v5;
	NPCKnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_movie) / 2);
	NPCKnucklesWeldInfo[23].WeldType = 2;
	NPCKnucklesWeldInfo[24].VertIndexes = 0;
}

void Init_Sonic()
{
	SONIC_OBJECTS[0] = &object_0056AF50;
	SONIC_OBJECTS[1] = &object_00563B7C;
	SONIC_OBJECTS[2] = &object_00563D0C;
	SONIC_OBJECTS[3] = &object_005654EC;
	SONIC_OBJECTS[4] = &object_00564CD0;
	SONIC_OBJECTS[5] = &object_005647B8;
	SONIC_OBJECTS[6] = &object_00564A78;
	SONIC_OBJECTS[7] = &object_00561F14;
	SONIC_OBJECTS[8] = &object_005620A4;
	SONIC_OBJECTS[9] = &object_005638CC;
	SONIC_OBJECTS[10] = &object_005630B0;
	SONIC_OBJECTS[11] = &object_00562B80;
	SONIC_OBJECTS[12] = &object_0056044C;
	SONIC_OBJECTS[13] = &object_005605DC;
	SONIC_OBJECTS[14] = &object_00561C68;
	SONIC_OBJECTS[15] = &object_005613F8;
	SONIC_OBJECTS[16] = &object_00560DD0;
	SONIC_OBJECTS[17] = &object_0055E99C;
	SONIC_OBJECTS[18] = &object_0055EB2C;
	SONIC_OBJECTS[19] = &object_005601B8;
	SONIC_OBJECTS[20] = &object_0055F948;
	SONIC_OBJECTS[21] = &object_0055F330;
	SONIC_OBJECTS[22] = &object_0062DE88;
	SONIC_OBJECTS[23] = &object_00626AB4;
	SONIC_OBJECTS[24] = &object_00626C44;
	SONIC_OBJECTS[25] = &object_0062840C;
	SONIC_OBJECTS[26] = &object_00627BF0;
	SONIC_OBJECTS[27] = &object_006276D8;
	SONIC_OBJECTS[28] = &object_00624E3C;
	SONIC_OBJECTS[29] = &object_00624FCC;
	SONIC_OBJECTS[30] = &object_006267F4;
	SONIC_OBJECTS[31] = &object_00625FD8;
	SONIC_OBJECTS[32] = &object_00625AA8;
	SONIC_OBJECTS[33] = &object_00623474;
	SONIC_OBJECTS[34] = &object_00623604;
	SONIC_OBJECTS[35] = &object_00624B78;
	SONIC_OBJECTS[36] = &object_00624308;
	SONIC_OBJECTS[37] = &object_00623C14;
	SONIC_OBJECTS[38] = &object_00621AC4;
	SONIC_OBJECTS[39] = &object_00621C54;
	SONIC_OBJECTS[40] = &object_006231E0;
	SONIC_OBJECTS[41] = &object_00622970;
	SONIC_OBJECTS[42] = &object_00622254;
	SONIC_OBJECTS[45] = &object_0056998C;
	SONIC_OBJECTS[46] = &object_00569594;
	SONIC_OBJECTS[48] = &object_00569DEC;
	SONIC_OBJECTS[49] = &object_00569594;
	SONIC_OBJECTS[50] = &object_00569E20;
	SONIC_OBJECTS[51] = &object_00569CE8;
	SONIC_OBJECTS[52] = &object_005698F0;
	SONIC_OBJECTS[55] = &object_00682EF4;
	SONIC_OBJECTS[62] = &object_00565520;
	SONIC_OBJECTS[66] = &object_005729CC;
	SONIC_ACTIONS[0]->object = &object_0056AF50;
	SONIC_ACTIONS[1]->object = &object_0056AF50;
	SONIC_ACTIONS[2]->object = &object_0056AF50;
	SONIC_ACTIONS[3]->object = &object_0056AF50;
	SONIC_ACTIONS[4]->object = &object_0056AF50;
	SONIC_ACTIONS[5]->object = &object_0056AF50;
	SONIC_ACTIONS[6]->object = &object_0056AF50;
	SONIC_ACTIONS[7]->object = &object_0056AF50;
	SONIC_ACTIONS[8]->object = &object_0056AF50;
	SONIC_ACTIONS[9]->object = &object_0056AF50;
	SONIC_ACTIONS[10]->object = &object_0056AF50;
	SONIC_ACTIONS[11]->object = &object_0056AF50;
	SONIC_ACTIONS[12]->object = &object_0056AF50;
	SONIC_ACTIONS[13]->object = &object_0056AF50;
	SONIC_ACTIONS[14]->object = &object_005729CC;
	SONIC_ACTIONS[15]->object = &object_0056AF50;
	SONIC_ACTIONS[16]->object = &object_0056AF50;
	SONIC_ACTIONS[17]->object = &object_0056AF50;
	SONIC_ACTIONS[18]->object = &object_0056AF50;
	SONIC_ACTIONS[19]->object = &object_0056AF50;
	SONIC_ACTIONS[20]->object = &object_0056AF50;
	SONIC_ACTIONS[22]->object = &object_0056AF50;
	SONIC_ACTIONS[23]->object = &object_0056AF50;
	SONIC_ACTIONS[27]->object = &object_0056AF50;
	SONIC_ACTIONS[28]->object = &object_0056AF50;
	SONIC_ACTIONS[29]->object = &object_0056AF50;
	SONIC_ACTIONS[30]->object = &object_0056AF50;
	SONIC_ACTIONS[31]->object = &object_0056AF50;
	SONIC_ACTIONS[32]->object = &object_0056AF50;
	SONIC_ACTIONS[33]->object = &object_0056AF50;
	SONIC_ACTIONS[34]->object = &object_0056AF50;
	SONIC_ACTIONS[35]->object = &object_0056AF50;
	SONIC_ACTIONS[36]->object = &object_0056AF50;
	SONIC_ACTIONS[37]->object = &object_0056AF50;
	SONIC_ACTIONS[38]->object = &object_0056AF50;
	SONIC_ACTIONS[39]->object = &object_0056AF50;
	SONIC_ACTIONS[40]->object = &object_0056AF50;
	SONIC_ACTIONS[41]->object = &object_0056AF50;
	SONIC_ACTIONS[42]->object = &object_0056AF50;
	SONIC_ACTIONS[43]->object = &object_0056AF50;
	SONIC_ACTIONS[44]->object = &object_0056AF50;
	SONIC_ACTIONS[45]->object = &object_0056AF50;
	SONIC_ACTIONS[46]->object = &object_0056AF50;
	SONIC_ACTIONS[47]->object = &object_0056AF50;
	SONIC_ACTIONS[48]->object = &object_0056AF50;
	SONIC_ACTIONS[49]->object = &object_0056AF50;
	SONIC_ACTIONS[50]->object = &object_0056AF50;
	SONIC_ACTIONS[51]->object = &object_0056AF50;
	SONIC_ACTIONS[52]->object = &object_0056AF50;
	SONIC_ACTIONS[53]->object = &object_0056AF50;
	SONIC_ACTIONS[54]->object = &object_0056AF50;
	SONIC_ACTIONS[55]->object = &object_0056AF50;
	SONIC_ACTIONS[56]->object = &object_0056AF50;
	SONIC_ACTIONS[57]->object = &object_0056AF50;
	SONIC_ACTIONS[58]->object = &object_0056AF50;
	SONIC_ACTIONS[59]->object = &object_0056AF50;
	SONIC_ACTIONS[60]->object = &object_0056AF50;
	SONIC_ACTIONS[61]->object = &object_0056AF50;
	SONIC_ACTIONS[62]->object = &object_0056AF50;
	SONIC_ACTIONS[63]->object = &object_0056AF50;
	SONIC_ACTIONS[64]->object = &object_0056AF50;
	SONIC_ACTIONS[65]->object = &object_0056AF50;
	SONIC_ACTIONS[66]->object = &object_0056AF50;
	SONIC_ACTIONS[67]->object = &object_0056AF50;
	SONIC_ACTIONS[68]->object = &object_0056AF50;
	SONIC_ACTIONS[69]->object = &object_0056AF50;
	SONIC_ACTIONS[70]->object = &object_0056AF50;
	SONIC_ACTIONS[71]->object = &object_0056AF50;
	SONIC_ACTIONS[72]->object = &object_0056AF50;
	SONIC_ACTIONS[87]->object = &object_0056AF50;
	SONIC_ACTIONS[88]->object = &object_0056AF50;
	SONIC_ACTIONS[89]->object = &object_0056AF50;
	SONIC_ACTIONS[90]->object = &object_0056AF50;
	SONIC_ACTIONS[91]->object = &object_0056AF50;
	SONIC_ACTIONS[92]->object = &object_0056AF50;
	SONIC_ACTIONS[93]->object = &object_0056AF50;
	SONIC_ACTIONS[94]->object = &object_0056AF50;
	SONIC_ACTIONS[95]->object = &object_0056AF50;
	SONIC_ACTIONS[96]->object = &object_0056AF50;
	SONIC_ACTIONS[97]->object = &object_0056AF50;
	SONIC_ACTIONS[98]->object = &object_0056AF50;
	SONIC_ACTIONS[99]->object = &object_0056AF50;
	SONIC_ACTIONS[100]->object = &object_0056AF50;
	SONIC_ACTIONS[101]->object = &object_0056AF50;
	SONIC_ACTIONS[102]->object = &object_0056AF50;
	SONIC_ACTIONS[103]->object = &object_0056AF50;
	SONIC_ACTIONS[104]->object = &object_0056AF50;
	SONIC_ACTIONS[105]->object = &object_0056AF50;
	SONIC_ACTIONS[106]->object = &object_0056AF50;
	SONIC_ACTIONS[107]->object = &object_0056AF50;
	SONIC_ACTIONS[108]->object = &object_0056AF50;
	SONIC_ACTIONS[109]->object = &object_0056AF50;
	SONIC_ACTIONS[113]->object = &object_0056AF50;
	SONIC_ACTIONS[114]->object = &object_0056AF50;
	SONIC_ACTIONS[115]->object = &object_0056AF50;
	SONIC_ACTIONS[116]->object = &object_0056AF50;
	SONIC_ACTIONS[117]->object = &object_0056AF50;
	SONIC_ACTIONS[118]->object = &object_0056AF50;
	SONIC_ACTIONS[119]->object = &object_0056AF50;
	SONIC_ACTIONS[120]->object = &object_0056AF50;
	SONIC_ACTIONS[121]->object = &object_0056AF50;
	SONIC_ACTIONS[122]->object = &object_0056AF50;
	SONIC_ACTIONS[123]->object = &object_0056AF50;
	SONIC_ACTIONS[124]->object = &object_0056AF50;
	SONIC_ACTIONS[125]->object = &object_0056AF50;
	SONIC_ACTIONS[126]->object = &object_0056AF50;
	SONIC_ACTIONS[127]->object = &object_0056AF50;
	SONIC_ACTIONS[128]->object = &object_0056AF50;
	SONIC_ACTIONS[129]->object = &object_0056AF50;
	SONIC_ACTIONS[130]->object = &object_0062DE88;
	SONIC_ACTIONS[131]->object = &object_0062DE88;
	SONIC_ACTIONS[132]->object = &object_0062DE88;
	SONIC_ACTIONS[133]->object = &object_0062DE88;
	SONIC_ACTIONS[134]->object = &object_0056AF50;
	SONIC_ACTIONS[135]->object = &object_0056AF50;
	SONIC_ACTIONS[136]->object = &object_0056AF50;
	SONIC_ACTIONS[137]->object = &object_0056AF50;
	SONIC_ACTIONS[138]->object = &object_0062DE88;
	SONIC_ACTIONS[139]->object = &object_0062DE88;
	SONIC_ACTIONS[140]->object = &object_0062DE88;
	SONIC_ACTIONS[141]->object = &object_0062DE88;
	SONIC_ACTIONS[143]->object = &object_0062DE88;
	SONIC_ACTIONS[144]->object = &object_0062DE88;
	SONIC_ACTIONS[145]->object = &object_0056AF50;
	SONIC_ACTIONS[146]->object = &object_0056AF50;
	SONIC_ACTIONS[147]->object = &object_0056AF50;
	SONIC_ACTIONS[148]->object = &object_0056AF50;
	SONIC_MODELS[0] = &attach_0055F304;
	SONIC_MODELS[1] = &attach_00560DA4;
	SONIC_MODELS[8] = &attach_00569568;
	SONIC_MODELS[9] = &attach_00579C68;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_movie);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_movie);
	WriteData((char*)0x49BE2B, (char)0xEBu);
	WriteJump((void*)0x49BE68, (void*)0x49BE87);
	WriteJump((void*)0x49BE2D, (void*)0x49BE68);
}

void Init_Tails()
{
	MILES_OBJECTS[0] = &object_0042AD54;
	MILES_OBJECTS[1] = &object_00437C44;
	MILES_OBJECTS[2] = &object_0043F4B4;
	MILES_OBJECTS[3] = &object_0044148C;
	MILES_OBJECTS[4] = &object_0042ABE8;
	MILES_OBJECTS[5] = &object_00437AD8;
	MILES_OBJECTS[6] = &object_0042AC84;
	MILES_OBJECTS[7] = &object_00437B74;
	MILES_OBJECTS[8] = &object_00426ED0;
	MILES_OBJECTS[9] = &object_00426B90;
	MILES_OBJECTS[10] = &object_00433DC0;
	MILES_OBJECTS[11] = &object_00433A80;
	MILES_OBJECTS[12] = &object_0041E548;
	MILES_OBJECTS[13] = &object_0041EC90;
	MILES_OBJECTS[14] = &object_0041ED2C;
	MILES_OBJECTS[15] = &object_0041E5E4;
	MILES_OBJECTS[16] = &object_0042BC1C;
	MILES_OBJECTS[17] = &object_0042B4D4;
	MILES_OBJECTS[18] = &object_0042BBE8;
	MILES_OBJECTS[19] = &object_0042B4A0;
	MILES_OBJECTS[20] = &object_00424D00;
	MILES_OBJECTS[21] = &object_00424E94;
	MILES_OBJECTS[22] = &object_0042674C;
	MILES_OBJECTS[23] = &object_00422FD8;
	MILES_OBJECTS[24] = &object_0042316C;
	MILES_OBJECTS[25] = &object_00424A14;
	MILES_OBJECTS[26] = &object_0042182C;
	MILES_OBJECTS[27] = &object_004219BC;
	MILES_OBJECTS[28] = &object_00422CF0;
	MILES_OBJECTS[29] = &object_004200CC;
	MILES_OBJECTS[30] = &object_0042025C;
	MILES_OBJECTS[31] = &object_00421598;
	MILES_OBJECTS[32] = &object_004225C8;
	MILES_OBJECTS[33] = &object_00421FE4;
	MILES_OBJECTS[34] = &object_00420E70;
	MILES_OBJECTS[35] = &object_00420884;
	MILES_OBJECTS[36] = &object_00425E88;
	MILES_OBJECTS[37] = &object_00425C40;
	MILES_OBJECTS[38] = &object_00424158;
	MILES_OBJECTS[39] = &object_00423F10;
	MILES_OBJECTS[40] = &object_00431BF0;
	MILES_OBJECTS[41] = &object_00431D84;
	MILES_OBJECTS[42] = &object_0043363C;
	MILES_OBJECTS[43] = &object_0042FEC8;
	MILES_OBJECTS[44] = &object_0043005C;
	MILES_OBJECTS[45] = &object_00431904;
	MILES_OBJECTS[46] = &object_0042E71C;
	MILES_OBJECTS[47] = &object_0042E8AC;
	MILES_OBJECTS[48] = &object_0042FBE0;
	MILES_OBJECTS[49] = &object_0042CFBC;
	MILES_OBJECTS[50] = &object_0042D14C;
	MILES_OBJECTS[51] = &object_0042E488;
	MILES_OBJECTS[52] = &object_0042F4B8;
	MILES_OBJECTS[53] = &object_0042EED4;
	MILES_OBJECTS[54] = &object_0042DD60;
	MILES_OBJECTS[55] = &object_0042D774;
	MILES_OBJECTS[56] = &object_00432D78;
	MILES_OBJECTS[57] = &object_00432B30;
	MILES_OBJECTS[58] = &object_00431048;
	MILES_OBJECTS[59] = &object_00430E00;
	MILES_OBJECTS[62] = &object_0041FE04;
	MILES_OBJECTS[63] = &object_0042CCF4;
	MILES_OBJECTS[66] = &object_0042AC1C;
	MILES_OBJECTS[67] = &object_0042ABE8;
	MILES_OBJECTS[68] = &object_00437B0C;
	MILES_OBJECTS[69] = &object_00437AD8;
	MILES_ACTIONS[0]->object = &object_00437C44;
	MILES_ACTIONS[1]->object = &object_00437C44;
	MILES_ACTIONS[2]->object = &object_00437C44;
	MILES_ACTIONS[3]->object = &object_00437C44;
	MILES_ACTIONS[4]->object = &object_00437C44;
	MILES_ACTIONS[5]->object = &object_00437C44;
	MILES_ACTIONS[6]->object = &object_00437C44;
	MILES_ACTIONS[7]->object = &object_00437C44;
	MILES_ACTIONS[8]->object = &object_00437C44;
	MILES_ACTIONS[9]->object = &object_00437C44;
	MILES_ACTIONS[10]->object = &object_00437C44;
	MILES_ACTIONS[11]->object = &object_0042AD54;
	MILES_ACTIONS[12]->object = &object_0042AD54;
	MILES_ACTIONS[13]->object = &object_0042AD54;
	MILES_ACTIONS[14]->object = &object_0042AD54;
	MILES_ACTIONS[15]->object = &object_0042AD54;
	MILES_ACTIONS[16]->object = &object_0042AD54;
	MILES_ACTIONS[17]->object = &object_00437C44;
	MILES_ACTIONS[18]->object = &object_00437C44;
	MILES_ACTIONS[19]->object = &object_00437C44;
	MILES_ACTIONS[20]->object = &object_00437C44;
	MILES_ACTIONS[21]->object = &object_0042AD54;
	MILES_ACTIONS[22]->object = &object_0042AD54;
	MILES_ACTIONS[23]->object = &object_0042AD54;
	MILES_ACTIONS[24]->object = &object_0042AD54;
	MILES_ACTIONS[25]->object = &object_0042AD54;
	MILES_ACTIONS[26]->object = &object_0042AD54;
	MILES_ACTIONS[27]->object = &object_0042AD54;
	MILES_ACTIONS[28]->object = &object_0042AD54;
	MILES_ACTIONS[29]->object = &object_0042AD54;
	MILES_ACTIONS[30]->object = &object_0042AD54;
	MILES_ACTIONS[31]->object = &object_0042AD54;
	MILES_ACTIONS[32]->object = &object_0042AD54;
	MILES_ACTIONS[33]->object = &object_0042AD54;
	MILES_ACTIONS[34]->object = &object_0042AD54;
	MILES_ACTIONS[35]->object = &object_0042AD54;
	MILES_ACTIONS[36]->object = &object_0042AD54;
	MILES_ACTIONS[37]->object = &object_0042AD54;
	MILES_ACTIONS[38]->object = &object_0042AD54;
	MILES_ACTIONS[39]->object = &object_0042AD54;
	MILES_ACTIONS[40]->object = &object_0042AD54;
	MILES_ACTIONS[41]->object = &object_0042AD54;
	MILES_ACTIONS[42]->object = &object_0042AD54;
	MILES_ACTIONS[43]->object = &object_0042AD54;
	MILES_ACTIONS[44]->object = &object_0042AD54;
	MILES_ACTIONS[45]->object = &object_0042AD54;
	MILES_ACTIONS[46]->object = &object_0042AD54;
	MILES_ACTIONS[47]->object = &object_0042AD54;
	MILES_ACTIONS[48]->object = &object_0042AD54;
	MILES_ACTIONS[49]->object = &object_0042AD54;
	MILES_ACTIONS[50]->object = &object_0042AD54;
	MILES_ACTIONS[51]->object = &object_0042AD54;
	MILES_ACTIONS[52]->object = &object_0042AD54;
	MILES_ACTIONS[53]->object = &object_00437C44;
	MILES_ACTIONS[54]->object = &object_00437C44;
	MILES_ACTIONS[55]->object = &object_0042AD54;
	MILES_ACTIONS[56]->object = &object_0042AD54;
	MILES_ACTIONS[57]->object = &object_0042AD54;
	MILES_ACTIONS[58]->object = &object_0042AD54;
	MILES_ACTIONS[59]->object = &object_0042AD54;
	MILES_ACTIONS[60]->object = &object_0042AD54;
	MILES_ACTIONS[61]->object = &object_0042AD54;
	MILES_ACTIONS[62]->object = &object_0042AD54;
	MILES_ACTIONS[63]->object = &object_0042AD54;
	MILES_ACTIONS[64]->object = &object_0043F4B4;
	MILES_ACTIONS[65]->object = &object_0044148C;
	MILES_ACTIONS[66]->object = &object_0042AD54;
	MILES_ACTIONS[67]->object = &object_0042AD54;
	MILES_ACTIONS[68]->object = &object_0042AD54;
	MILES_ACTIONS[69]->object = &object_0042AD54;
	MILES_ACTIONS[70]->object = &object_0042AD54;
	MILES_ACTIONS[71]->object = &object_0042AD54;
	MILES_ACTIONS[72]->object = &object_0042AD54;
	MILES_ACTIONS[73]->object = &object_0042AD54;
	MILES_ACTIONS[74]->object = &object_0042AD54;
	MILES_ACTIONS[75]->object = &object_0042AD54;
	MILES_ACTIONS[76]->object = &object_0042AD54;
	MILES_ACTIONS[77]->object = &object_0042AD54;
	MILES_ACTIONS[78]->object = &object_0042AD54;
	MILES_ACTIONS[79]->object = &object_0042AD54;
	MILES_ACTIONS[80]->object = &object_0042AD54;
	MILES_ACTIONS[81]->object = &object_0042AD54;
	MILES_ACTIONS[82]->object = &object_0042AD54;
	MILES_ACTIONS[83]->object = &object_0042AD54;
	MILES_ACTIONS[85]->object = &object_0042AD54;
	MILES_ACTIONS[86]->object = &object_0042AD54;
	MILES_ACTIONS[87]->object = &object_0042AD54;
	MILES_ACTIONS[88]->object = &object_0042AD54;
	MILES_ACTIONS[91]->object = &object_0042AD54;
	MILES_ACTIONS[92]->object = &object_0042AD54;
	MILES_ACTIONS[93]->object = &object_0042AD54;
	MILES_ACTIONS[94]->object = &object_0042AD54;
	MILES_ACTIONS[95]->object = &object_0042AD54;
	MILES_ACTIONS[96]->object = &object_0042AD54;
	MILES_ACTIONS[97]->object = &object_0042AD54;
	MILES_ACTIONS[110]->object = &object_0042AD54;
	MILES_ACTIONS[111]->object = &object_0042AD54;
	MILES_ACTIONS[112]->object = &object_0042AD54;
	MILES_ACTIONS[113]->object = &object_0042AD54;
	MILES_MODELS[0] = &attach_0041FDD8;
	MILES_MODELS[1] = &attach_0042CCC8;
	MILES_MODELS[2] = &attach_0042ABBC;
	MILES_MODELS[3] = &attach_00437AAC;
	MILES_MODELS[4] = &attach_0044517C;
	MILES_MODELS[5] = &attach_0041E51C;
	MILES_MODELS[6] = &attach_0041EC64;
	MILES_MODELS[7] = &attach_0042B40C;
	MILES_MODELS[8] = &attach_0042BB54;
	WriteJump((void*)0x4618B0, (void*)0x46193B);
	WriteJump((void*)0x46220F, (void*)0x4622FE);
	WriteJump((void*)0x46220F, (void*)0x46229A);
	WriteJump((void*)0x46229A, (void*)0x4622FE);
	WriteData<3>((void*)0x45BED3, 0x90u);
	WriteData<3>((void*)0x45DAB1, 0x90u);
	WriteData<3>((void*)0x461389, 0x90u);
	WriteData<3>((void*)0x461325, 0x90u);
	WriteData<3>((void*)0x45BEE7, 0x90u);
	WriteData<3>((void*)0x45DACA, 0x90u);
	WriteData<3>((void*)0x4613A1, 0x90u);
	WriteData<3>((void*)0x461339, 0x90u);
	WriteJump((void*)0x007C6D80, InitTailsWeldInfo_mod);
	WriteJump((void*)0x007C7560, InitNPCTailsWeldInfo_mod);
}

void Init_Knuckles()
{
	KNUCKLES_OBJECTS[0] = &object_002E23B0;
	KNUCKLES_OBJECTS[1] = &object_002EEE50;
	KNUCKLES_OBJECTS[2] = &object_002DB8A4;
	KNUCKLES_OBJECTS[3] = &object_002DBA34;
	KNUCKLES_OBJECTS[4] = &object_002DD0AC;
	KNUCKLES_OBJECTS[5] = &object_002DC244;
	KNUCKLES_OBJECTS[6] = &object_002D9E5C;
	KNUCKLES_OBJECTS[7] = &object_002D9FEC;
	KNUCKLES_OBJECTS[8] = &object_002DB5F4;
	KNUCKLES_OBJECTS[9] = &object_002DAB34;
	KNUCKLES_OBJECTS[10] = &object_002D876C;
	KNUCKLES_OBJECTS[11] = &object_002D88FC;
	KNUCKLES_OBJECTS[12] = &object_002D9BB0;
	KNUCKLES_OBJECTS[13] = &object_002D6FE4;
	KNUCKLES_OBJECTS[14] = &object_002D7174;
	KNUCKLES_OBJECTS[15] = &object_002D8438;
	KNUCKLES_OBJECTS[16] = &object_002D9754;
	KNUCKLES_OBJECTS[17] = &object_002D9088;
	KNUCKLES_OBJECTS[18] = &object_002D7FDC;
	KNUCKLES_OBJECTS[19] = &object_002D7900;
	KNUCKLES_OBJECTS[20] = &object_002DC94C;
	KNUCKLES_OBJECTS[21] = &object_002DC244;
	KNUCKLES_OBJECTS[22] = &object_002DAEE4;
	KNUCKLES_OBJECTS[23] = &object_002DAB34;
	KNUCKLES_OBJECTS[24] = &object_002E8324;
	KNUCKLES_OBJECTS[25] = &object_002E84B4;
	KNUCKLES_OBJECTS[26] = &object_002E9B2C;
	KNUCKLES_OBJECTS[27] = &object_002E8CC4;
	KNUCKLES_OBJECTS[28] = &object_002E68DC;
	KNUCKLES_OBJECTS[29] = &object_002E6A6C;
	KNUCKLES_OBJECTS[30] = &object_002E8074;
	KNUCKLES_OBJECTS[31] = &object_002E75B4;
	KNUCKLES_OBJECTS[32] = &object_002E51EC;
	KNUCKLES_OBJECTS[33] = &object_002E537C;
	KNUCKLES_OBJECTS[34] = &object_002E6630;
	KNUCKLES_OBJECTS[35] = &object_002E3A64;
	KNUCKLES_OBJECTS[36] = &object_002E3BF4;
	KNUCKLES_OBJECTS[37] = &object_002E4EB8;
	KNUCKLES_OBJECTS[38] = &object_002E61D4;
	KNUCKLES_OBJECTS[39] = &object_002E5B08;
	KNUCKLES_OBJECTS[40] = &object_002E4A5C;
	KNUCKLES_OBJECTS[41] = &object_002E4380;
	KNUCKLES_OBJECTS[42] = &object_002E93CC;
	KNUCKLES_OBJECTS[43] = &object_002E8CC4;
	KNUCKLES_OBJECTS[44] = &object_002E7964;
	KNUCKLES_OBJECTS[45] = &object_002E75B4;
	KNUCKLES_OBJECTS[49] = &object_002E191C;
	KNUCKLES_OBJECTS[50] = &object_002EE3BC;
	KNUCKLES_OBJECTS[51] = &object_002E21A8;
	KNUCKLES_OBJECTS[52] = &object_002E2070;
	KNUCKLES_OBJECTS[53] = &object_002E1C78;
	KNUCKLES_OBJECTS[54] = &object_002E1D14;
	KNUCKLES_OBJECTS[55] = &object_002E191C;
	KNUCKLES_OBJECTS[58] = &object_002DB5F4;
	KNUCKLES_OBJECTS[59] = &object_002DAEE4;
	KNUCKLES_OBJECTS[60] = &object_002DAB34;
	KNUCKLES_OBJECTS[61] = &object_002DA324;
	KNUCKLES_OBJECTS[62] = &object_002DD0AC;
	KNUCKLES_OBJECTS[63] = &object_002DC94C;
	KNUCKLES_OBJECTS[64] = &object_002DC244;
	KNUCKLES_OBJECTS[65] = &object_002DC59C;
	KNUCKLES_OBJECTS[66] = &object_002E8074;
	KNUCKLES_OBJECTS[67] = &object_002E7964;
	KNUCKLES_OBJECTS[68] = &object_002E75B4;
	KNUCKLES_OBJECTS[69] = &object_002E6DA4;
	KNUCKLES_OBJECTS[70] = &object_002E9B2C;
	KNUCKLES_OBJECTS[71] = &object_002E93CC;
	KNUCKLES_OBJECTS[72] = &object_002E8CC4;
	KNUCKLES_OBJECTS[73] = &object_002E901C;
	KNUCKLES_ACTIONS[0]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[1]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[2]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[3]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[4]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[5]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[6]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[7]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[9]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[10]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[11]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[12]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[13]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[14]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[15]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[16]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[17]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[18]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[19]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[20]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[21]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[22]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[23]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[24]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[25]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[26]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[27]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[28]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[29]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[30]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[31]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[32]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[33]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[34]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[35]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[36]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[37]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[38]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[39]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[40]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[41]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[42]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[43]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[44]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[45]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[46]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[47]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[48]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[49]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[50]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[51]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[52]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[53]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[54]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[55]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[56]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[57]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[58]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[59]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[60]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[61]->object = &object_002F8530;
	KNUCKLES_ACTIONS[63]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[64]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[65]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[66]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[67]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[68]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[69]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[70]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[71]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[72]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[73]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[74]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[75]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[76]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[77]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[78]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[79]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[80]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[81]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[82]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[83]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[84]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[85]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[86]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[87]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[88]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[89]->object = &object_002E23B0;
	KNUCKLES_MODELS[4] = &attach_002E18F0;
	KNUCKLES_MODELS[5] = &attach_002EE390;
	KNUCKLES_MODELS[6] = &attach_002FC558;
	KNUCKLES_MODELS[7] = &attach_002DB5C8;
	KNUCKLES_MODELS[8] = &attach_002DAEB8;
	KNUCKLES_MODELS[9] = &attach_002DAB08;
	KNUCKLES_MODELS[10] = &attach_002DA2F8;
	KNUCKLES_MODELS[11] = &attach_002DD080;
	KNUCKLES_MODELS[12] = &attach_002DC920;
	KNUCKLES_MODELS[13] = &attach_002DC218;
	KNUCKLES_MODELS[14] = &attach_002DC570;
	WriteData<5>((void*)0x47B460, 0x90u);
	WriteData((char*)0x4726A6, (char)Upgrades_ShovelClaw);
	WriteData((char*)0x4726A6, (char)Upgrades_FightingGloves);
	WriteJump((void*)0x007C94D0, InitKnucklesWeldInfo_mod);
	WriteJump((void*)0x007C9C80, InitNPCKnucklesWeldInfo_mod);
	WriteData((uint16_t**)0x0472B2C, (uint16_t*)&Knuckles_HandIndices_movie);
	WriteData((uint16_t**)0x0472835, (uint16_t*)&Knuckles_HandIndices_movie);
}

extern "C" __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions & helperFunctions)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	EnableSonic = config->getBool("Characters", "EnableSonic", true);
	EnableTails = config->getBool("Characters", "EnableTails", true);
	EnableKnux = config->getBool("Characters", "EnableKnux", true);

	HMODULE handle = GetModuleHandle(L"CHRMODELS_orig");
	NJS_OBJECT** ___SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___SONIC_OBJECTS");
	NJS_ACTION** ___SONIC_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___SONIC_ACTIONS");
	NJS_MODEL_SADX** ___SONIC_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___SONIC_MODELS");
	NJS_OBJECT** ___MILES_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___MILES_OBJECTS");
	NJS_ACTION** ___MILES_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___MILES_ACTIONS");
	NJS_MODEL_SADX** ___MILES_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___MILES_MODELS");
	NJS_OBJECT** ___KNUCKLES_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___KNUCKLES_OBJECTS");
	NJS_ACTION** ___KNUCKLES_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___KNUCKLES_ACTIONS");
	NJS_MODEL_SADX** ___KNUCKLES_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___KNUCKLES_MODELS");

	MovieGUI_Init();

	if (EnableSonic)
	{
		Init_Sonic();
		ReplacePVM("sonic", "MovieSonic");
		ReplacePVM("supersonic", "MovieSSonic");
		ReplacePVM("hypersonic", "MovieHSonic");
		ReplacePVM("hypersonic_g", "MovieHSonic");
		ReplacePVM("DXR_HYPER", "MovieHSonic");
		ReplacePVM("hypersonic_dc", "MovieHSonic");
		ReplacePVM("hypersonic_dc_a", "MovieHSonic");
		ReplacePVM("HYPERSONIC_G_DC", "MovieHSonic");
		ReplacePVM("HYPERSONIC_V_DC", "MovieHSonic");
		ReplacePVM("HYPERSONIC_V_P_DC", "MovieHSonic");
	}

	if (EnableTails)
	{
		Init_Tails();
		ReplacePVM("miles", "MovieMiles");
	}
	
	if (EnableKnux)
	{
		Init_Knuckles();
		ReplacePVM("knuckles", "MovieKnux");
	}
}

extern "C" __declspec(dllexport) const ModInfo SADXModInfo = { ModLoaderVer };