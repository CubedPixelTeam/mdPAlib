#include "PA9.h"
#include <stdio.h>
#include <filesystem.h>

char *TileBuffer;
char *MapBuffer;
char *PalBuffer;

FAT_INFOBGFILE Fat_BgInfo;	

unsigned char* SpriteCustom[128] _GFX_ALIGN;
unsigned short PaletteCustom[256] _GFX_ALIGN;
FILE* File;
u32 Size;
void ParseLine(char* line,char* dest, s16 startByte, s32 arraySize){
	memset(dest,0,arraySize);
	int i=0;
	s16 firstbyte=0,lastbyte=0, difference=0;
	for(i=startByte;i<arraySize;i++)
	{
		if(firstbyte==0 && line[i]!=PA_TAB &&line[i]!='{' )firstbyte=i;
		if(lastbyte==0 && (line[i]==',' ||line[i]=='}') )lastbyte=i;
		if(firstbyte>0 && lastbyte>0)
		{
			difference=lastbyte-firstbyte;
			break;
		}
	}
	memcpy (dest,line+firstbyte,difference);
}
char* FatLoad(char *filename)
{
	FILE* File = fopen (filename, "rb"); 
	if(File)// Make sure there is a file to load
	{ 
		u32 Size;
		fseek (File, 0 , SEEK_END);
		Size = ftell (File);
		rewind (File);
		char *buffer = (char*) malloc (sizeof(char)*Size);
		if(buffer!=NULL){
			fread (buffer, 1, Size, File);

			fclose (File);
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
FAT_INFOBGFILE FAT_LoadBgInfo(const char *name){
	FAT_INFOBGFILE tempstruct;
	
	char tempwidth[10];
	char InfoStruct[4][32];
	FILE* cfile = fopen (name, "rb"); //rb = read
	if(cfile)
	{
		//scan the important lines in the .c file into the memory for easy parsing
		s8 TextBlock=0,LineCount=0;
		while(!feof (cfile))
		{
			if(LineCount==7 || LineCount==8 || LineCount==14 || LineCount==15){
				fgets ((char*)InfoStruct[TextBlock],32,cfile);
				TextBlock++;
				LineCount++;
			}
			else if(fgetc (cfile)=='\n')LineCount++;
		}
		fclose(cfile);
		
		char TempBuf[256];
		
		ParseLine((char*)InfoStruct[0],TempBuf,0,255);
		sprintf(tempstruct.BGType,"%s",TempBuf);
		
		ParseLine((char*)InfoStruct[1],TempBuf,0,255);
		tempstruct.width=atoi(TempBuf);
		
		ParseLine((char*)InfoStruct[1],TempBuf,sprintf(tempwidth,"%d",tempstruct.width)+2,255);
		tempstruct.height=atoi(TempBuf);	
		
		ParseLine((char*)InfoStruct[2],TempBuf,0,255);
		tempstruct.tilesize=atoi(TempBuf);	
		
		ParseLine((char*)InfoStruct[3],TempBuf,0,255);
		tempstruct.mapsize=atoi(TempBuf);	

		tempstruct.Error=0;

		//determine background type
		if(!strcmp(tempstruct.BGType, "PA_BgNormal"))tempstruct.Bgtype=PA_BgNormal;
		else if(!strcmp(tempstruct.BGType, "PA_BgLarge"))tempstruct.Bgtype=PA_BgLarge;
		else if(!strcmp(tempstruct.BGType, "PA_BgUnlimited"))tempstruct.Bgtype=PA_BgUnlimited;
		else if(!strcmp(tempstruct.BGType, "PA_BgRot"))tempstruct.Bgtype=PA_BgRot;
		else tempstruct.Error=1;

		return tempstruct;
	}
	else{
		tempstruct.Error=2;
		return tempstruct;
	}
}
s8 FAT_LoadBackground(u8 screen, u8 bg_select, const char *name)
{
	char TempName[256];
	//Load the binary data first
	TileBuffer=NULL;
	//load the tiles
	sprintf(TempName,"%s_Tiles.bin",name);
	TileBuffer=FatLoad(TempName);
	//load the map
	MapBuffer=NULL;
	sprintf(TempName,"%s_Map.bin",name);
	MapBuffer=FatLoad(TempName);
	//load the pal
	PalBuffer=NULL;
	sprintf(TempName,"%s_Pal.bin",name);
	PalBuffer=FatLoad(TempName);
	
	sprintf(TempName,"%s.c",name);
	Fat_BgInfo=FAT_LoadBgInfo(TempName);
	if(Fat_BgInfo.Error){
		PA_Print(0,"error %d\n",Fat_BgInfo.Error);
		return 0; //failed in loading info
	}

	FAT_BgLoad(screen,bg_select,Fat_BgInfo.Bgtype,Fat_BgInfo.width,Fat_BgInfo.height,(char*)TileBuffer,Fat_BgInfo.tilesize,(char*)MapBuffer,Fat_BgInfo.mapsize,(char*)PalBuffer);
	free(TileBuffer);
	free(MapBuffer);
	free(PalBuffer);
	return 1;
}

void FAT_LoadSprite(u8 ID, char* spritename, char* palname){
	File = fopen (palname, "rb"); 
	fread (PaletteCustom, 1, sizeof(PaletteCustom), File);
	fclose (File);
	File = fopen (spritename, "rb");
	fseek (File, 0 , SEEK_END);
	Size = ftell (File);
	rewind (File);
	SpriteCustom[ID] = malloc(Size); 
	fread (SpriteCustom[ID], 1, Size, File);
	fclose (File);	
}
