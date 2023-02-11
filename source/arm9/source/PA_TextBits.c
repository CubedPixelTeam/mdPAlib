#include "PA_TextBits.h"

extern u16 PA_BmpFont0_Map[];
extern u16 PA_BmpFont1_Map[];
extern u16 PA_BmpFont2_Map[];
extern u16 PA_BmpFont3_Map[];
extern u16 PA_BmpFont4_Map[];

extern u8 PA_BmpFont0_Tiles[];
extern u8 PA_BmpFont1_Tiles[];
extern u8 PA_BmpFont2_Tiles[];
extern u8 PA_BmpFont3_Tiles[];
extern u8 PA_BmpFont4_Tiles[];

extern u8 PA_BmpFont0_Sizes[];
extern u8 PA_BmpFont1_Sizes[];
extern u8 PA_BmpFont2_Sizes[];
extern u8 PA_BmpFont3_Sizes[];
extern u8 PA_BmpFont4_Sizes[];

u16 *bittext_maps[10] = {
	PA_BmpFont0_Map,
	PA_BmpFont1_Map,
	PA_BmpFont2_Map,
	PA_BmpFont3_Map,
	PA_BmpFont4_Map
};

u8 *bittext_tiles_blank[10] = {
	PA_BmpFont0_Tiles,
	PA_BmpFont1_Tiles,
	PA_BmpFont2_Tiles,
	PA_BmpFont3_Tiles,
	PA_BmpFont4_Tiles
};

u8 *pa_bittextdefaultsize[10] = {
	PA_BmpFont0_Sizes,
	PA_BmpFont1_Sizes,
	PA_BmpFont2_Sizes,
	PA_BmpFont3_Sizes,
	PA_BmpFont4_Sizes
};

// Will be filled later
u16 pa_bittextsizes[5];
u8 pa_bittextpoliceheight[10];

LetterPos PA_LetterPos;