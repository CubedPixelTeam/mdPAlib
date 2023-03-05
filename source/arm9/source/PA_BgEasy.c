#include <PA9.h>

void PA_EasyBgScrollX(u8 screen, u8 bg_number, s32 x) {
	if ((PA_BgInfo[screen][bg_number].BgMode == BG_TILEDBG) || (PA_BgInfo[screen][bg_number].BgMode == 0))
		PA_BGScrollX(screen, bg_number, x&511);
	else PA_InfLargeScrollX(screen, bg_number, x);
}

void PA_EasyBgScrollY(u8 screen, u8 bg_number, s32 y) {
	if ((PA_BgInfo[screen][bg_number].BgMode == BG_TILEDBG) || (PA_BgInfo[screen][bg_number].BgMode == 0))
		PA_BGScrollY(screen, bg_number, y&511);
	else PA_InfLargeScrollY(screen, bg_number, y);
}

void PA_StoreEasyBgInfos(u8 screen, u8 bg_number, u32 Type, u32 Width, u32 Height, void *Tiles, u32 TileSize, void *Map, u32 MapSize, void *Palette) {
	PA_BgInfo[screen][bg_number].Infos.Type = Type;
	PA_BgInfo[screen][bg_number].Infos.Width = Width;
	PA_BgInfo[screen][bg_number].Infos.Height = Height;
	PA_BgInfo[screen][bg_number].Infos.Tiles = Tiles;
	PA_BgInfo[screen][bg_number].Infos.TileSize = TileSize;
	PA_BgInfo[screen][bg_number].Infos.Map = Map;
	PA_BgInfo[screen][bg_number].Infos.MapSize = MapSize;
	PA_BgInfo[screen][bg_number].Infos.Palette = Palette;
	PA_BgInfo[screen][bg_number].BgMode = Type;
}