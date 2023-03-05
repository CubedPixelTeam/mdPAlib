#ifndef NITROBACKGROUNDSLIB_H_INCLUDED
#define NITROBACKGROUNDSLIB_H_INCLUDED

typedef struct{
	s8 Bgtype;
	char BGType[16], tempwidth[10];
	s16 width,height;
	u32 tilesize,mapsize;
	s8 Error;
}FAT_INFOBGFILE;

char* FatLoad(char *filename);
inline void ParseLine(char* line,char* dest, s16 startByte, s32 arraySize){
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
void FAT_BgLoad(s8 screen,s8 bg_select,s8 Bgtype,s16 width,s16 height,void *Tiles,u32 tilesize,void* Map,u32 mapsize,void *Pal);
FAT_INFOBGFILE FAT_LoadBgInfo(const char *name);
s8 FAT_LoadBackground(u8 screen, u8 bg_select, const char *name);

#endif