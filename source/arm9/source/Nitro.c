#include "PA9.h"
#include <stdio.h>
#include <filesystem.h>
PA_BgInfos FAT_Info[2][4];

unsigned char* SpriteCustom[128] _GFX_ALIGN;
unsigned short PaletteCustom[256] _GFX_ALIGN;

FILE* File;
u32 Size;
char* FatLoad(const char *filename)
{
	FILE* File = fopen (filename, "rb"); 
	if(File)// Make sure there is a file to load
	{ 
		fseek (File, 0 , SEEK_END);
		Size = ftell (File);
		rewind (File);
		char *buffer = (char*) malloc (sizeof(char)*Size);
		if(buffer!=NULL){
			fseek (File, 0 , SEEK_SET);
			fread (buffer, 1, Size, File);

			fclose (File);
			DC_FlushAll();
			return buffer;
			free(buffer);
		}
		else {//if this happens you're out of memory!
			fclose (File);
			free(buffer);
			return NULL;
		}
	}
	return NULL;
}

u8 GetPixelWBL(const char* bgmap,const char*bgtiles,u8 screen, u8 bg_number, s32 x, s32 y, int scrollx, int scrolly,int width, int height) {
	// Adjust X/Y values
	x += scrollx; x &= (width- 1);
	y += scrolly; y %= (height);
	s32 mappos;

	if ((x <= 256) && (y <= 256)) {// Normal default size
		mappos = (x >> 3) + ((y >> 3) * 32); // Adjust position in map
	} else if ((x > 256) && (y <= 256)) {
		mappos = 32 * 32 + ((x & 255) >> 3) + ((y >> 3) * 32); // Adjust position in map
	} else if ((x <= 256) && (y > 256)) { // Tall
		mappos = 64 * 32 + (x >> 3) + (((y - 256) >> 3) * 32); // Adjust position in map
	} else {
		mappos = 96 * 32 + ((x - 256) >> 3) + (((y - 256) >> 3) * 32); // Adjust position in map
	}

	u16 *Map = (u16*)bgmap;
	s32 tilepix = (Map[mappos] & 1023) << 6;
	u8 hflip = (Map[mappos] >> 10) & 1;
	u8 vflip = (Map[mappos] >> 11) & 1;
	x &= 7; y &= 7; // Adjust in tile...

	if (hflip) x = 7 - x;   
	if (vflip) y = 7 - y;   // Adjust flips...

	u8 *Tiles = (u8*)bgtiles;
	return Tiles[tilepix+x+(y<<3)];
}
char* FatLoadPal(const char *filename)
{
	FILE* File = fopen (filename, "rb"); 
	fseek (File, 0 , SEEK_END);
	Size = ftell (File);
	if(Size < 512) Size = 512;
	rewind (File);
	char *buffer = (char*) calloc (Size,sizeof(char));
	
	fread (buffer, 1, Size, File);

	fclose (File);
	return buffer;
	free(buffer);
	
	return 0;
}

void FAT_BgLoad(s8 screen,s8 bg_select,s8 Bgtype,s16 width,s16 height,void *Tiles,u32 tilesize,void* Map,u32 mapsize,void *Pal){
	int tempsize=0;
	switch(Bgtype){
		case PA_BgNormal:
			PA_StoreEasyBgInfos(screen, bg_select, BG_TILEDBG,width,
				height,(void*)Tiles,tilesize >> 1,
				(void*)Map,mapsize>> 1, (void*)Pal);

			PA_LoadBgPal(screen, bg_select, (void*)Pal);

			tempsize = PA_GetPAGfxBgSize(width,height);

			PA_DeleteBg(screen, bg_select);
			PA_LoadBgTilesEx(screen, bg_select, (void*)Tiles,tilesize >> 1);
			PA_LoadBgMap(screen, bg_select, (void*)Map, tempsize);

			PA_InitBg(screen, bg_select, tempsize, 0, 1);
			PA_BGScrollXY(screen, bg_select, 0, 0);
			break;
			
		case PA_BgLarge:
			PA_StoreEasyBgInfos(screen, bg_select, BG_LARGEMAP,width,
				height,(void*)Tiles,tilesize >> 1,
				(void*)Map,mapsize >> 1, (void*)Pal);

			PA_LoadBgPal(screen, bg_select, (void*)Pal);

			PA_BgInfo[screen][bg_select].NTiles = tilesize >> 6;

			PA_DeleteBg(screen, bg_select);
			PA_LoadBgTilesEx(screen, bg_select, (void*) Tiles, tilesize >> 1);
			PA_LoadBgMap(screen, bg_select, NULL, BG_512X256);

			PA_InitBg(screen, bg_select, BG_512X256, 0, 1);
			PA_BGScrollXY(screen, bg_select, 0, 0);

			PA_InitLargeBg(screen, bg_select,width>> 3,height >> 3, (void*) Map);
			break;

		case PA_BgUnlimited:
			PA_StoreEasyBgInfos(screen, bg_select, BG_INFINITEMAP,width,
				height,(void*)Tiles,tilesize >> 1,
				(void*)Map,mapsize >> 1, (void*)Pal);

			PA_LoadBgPal(screen, bg_select, (void*)Pal);

			PA_BgInfo[screen][bg_select].NTiles = tilesize >> 6;

			PA_DeleteBg(screen, bg_select);
			PA_LoadBgTilesEx(screen, bg_select, (void*)NULL, (1008<<5));
			PA_BgInfo[screen][bg_select].Tiles = (void*) Tiles;
			PA_LoadBgMap(screen, bg_select, NULL, BG_512X256);
			PA_InitBg(screen, bg_select, BG_512X256, 0, 1);
			PA_BGScrollXY(screen, bg_select, 0, 0);

			PA_InitLargeBg(screen, bg_select, width >> 3,height >> 3, (void*) Map);
			break;

		case PA_BgRot:
			PA_Load8bitBgPal(screen, (void*)Pal);

			tempsize = PA_GetPAGfxRotBgSize(width);

			PA_DeleteBg(screen, bg_select);
			PA_LoadBgTilesEx(screen, bg_select, (void*) Tiles,tilesize >> 1);
			PA_LoadRotBgMap(screen, bg_select, (void*) Map, tempsize);

			PA_InitBg(screen, bg_select, tempsize, 0, 1);
			PA_SetBgRot(screen, bg_select, 0, 0, 0, 0, 0, 256);
			break;
	}
}
s8 FAT_LoadBackground(u8 screen, u8 bg_select, int width, int height, u8 type,const char *name){
	FAT_INFOBGFILE Fat_BgInfo;
	char TempName[256];
	//empty this shit
	free(FAT_Info[screen][bg_select].Infos.Tiles);
	free(FAT_Info[screen][bg_select].Infos.Map);
	free(FAT_Info[screen][bg_select].Infos.Palette);

	FAT_Info[screen][bg_select].Infos.Tiles=NULL;
	FAT_Info[screen][bg_select].Infos.Map=NULL;
	FAT_Info[screen][bg_select].Infos.Palette=NULL;
	
	//Load the binary data first
	//load the tiles
	sprintf(TempName,"%s_Tiles.bin",name);
	FAT_Info[screen][bg_select].Infos.Tiles = FatLoad(TempName);
	FAT_Info[screen][bg_select].Infos.TileSize = Size;

	sprintf(TempName,"%s_Map.bin",name);

	FAT_Info[screen][bg_select].Infos.Map=FatLoad(TempName);
	FAT_Info[screen][bg_select].Infos.MapSize=Size;
	//load the pal
	sprintf(TempName,"%s_Pal.bin",name);
	FAT_Info[screen][bg_select].Infos.Palette = FatLoadPal(TempName);
	DC_FlushAll();
	FAT_BgLoad(screen,bg_select,type,width,height,
	(char*)FAT_Info[screen][bg_select].Infos.Tiles,
	FAT_Info[screen][bg_select].Infos.TileSize,
	(char*)FAT_Info[screen][bg_select].Infos.Map,
	FAT_Info[screen][bg_select].Infos.MapSize,
	(char*)FAT_Info[screen][bg_select].Infos.Palette);

	return 1;
}