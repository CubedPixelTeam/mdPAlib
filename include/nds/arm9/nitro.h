#ifndef NITROBACKGROUNDSLIB_H_INCLUDED
#define NITROBACKGROUNDSLIB_H_INCLUDED

typedef struct{
	s8 Bgtype;
	char BGType[16], tempwidth[10];
	s16 width,height;
	u32 tilesize,mapsize;
	s8 Error;
}FAT_INFOBGFILE;
#include <PA9.h>

extern unsigned char* SpriteCustom[128] _GFX_ALIGN;
extern unsigned short PaletteCustom[256] _GFX_ALIGN;
u8 GetPixelWBL(const char* bgmap,const char*bgtiles,u8 screen, u8 bg_number, s32 x, s32 y, int scrollx, int scrolly,int width, int height);
void FAT_LoadSprite(u8 ID, const char* spritename, const char* palname);
char* FatLoad(const char *filename);
void ParseLine(char* line,char* dest, s16 startByte, s32 arraySize);
void FAT_BgLoad(s8 screen,s8 bg_select,s8 Bgtype,s16 width,s16 height,void *Tiles,u32 tilesize,void* Map,u32 mapsize,void *Pal);
FAT_INFOBGFILE FAT_LoadBgInfo(const char *name);
s8 FAT_LoadBackground(u8 screen, u8 bg_select, int width, int height, u8 type,const char *name);

#endif
