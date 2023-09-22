#include <PA9.h>

u8 PA_ExtPal[2][2]; // 0 si pas �tendu, 1 sinon

void PA_InitSpriteExtPal(void) {
	// Palettes �tendus pour les 256 couleurs...
	vramSetBankG(VRAM_G_SPRITE_EXT_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
	PA_ExtPal[0][0] = 1;
	PA_ExtPal[0][1] = 1;
	REG_DISPCNT |= DISPLAY_SPR_EXT_PALETTE;
	REG_DISPCNT_SUB |= DISPLAY_SPR_EXT_PALETTE;
	PA_LoadSpritePal(0, 0, (void*)PAL_SPRITE0);
	PA_LoadSpritePal(1, 0, (void*)PAL_SPRITE1);
}

void PA_LoadSpriteExtPal(u8 screen, u16 palette_number, void* palette) {
	if (screen == 0) {
		vramSetBankG(VRAM_G_LCD);  // On passe en mode LCD pour pouvoir ecrire dessus, on reviendre en palette apres
		//DMA_Copy(palette, VRAM_G + (palette_number << 9), 256, DMA_16NOW);
		dmaCopy(palette,VRAM_G_EXT_SPR_PALETTE[palette_number],256);
		vramSetBankG(VRAM_G_SPRITE_EXT_PALETTE);
	} else {
		vramSetBankI(VRAM_I_LCD);  // On passe en mode LCD pour pouvoir ecrire dessus, on reviendre en palette apres
		//DMA_Copy(palette, VRAM_I + (palette_number << 9), 256, DMA_16NOW);
		dmaCopy(palette,VRAM_I_EXT_SPR_PALETTE[palette_number],256);
		vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
	}
}

void PA_InitBgExtPal(void) {
	// Palettes �tendus pour les 256 couleurs...
	vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	PA_ExtPal[1][0] = 1;
	PA_ExtPal[1][1] = 1;
	
	bgExtPaletteEnable();
	bgExtPaletteEnableSub();
	u8 i;

	for (i = 0; i < 4; i++) { // On copie la palette partout
		PA_LoadBgExtPal(0, i, (void*)PAL_BG0);
		PA_LoadBgExtPal(1, i, (void*)PAL_BG0);
	}
}

void PA_LoadBgPalN(u8 screen, u8 bg_number, u8 pal_number, void* palette) {
	if (screen == 0) {
		vramSetBankE(VRAM_E_LCD);  // On passe en mode LCD pour pouvoir ecrire dessus, on reviendre en palette apres
		//DMA_Copy(palette, VRAM_E + (bg_number << 13) + (pal_number << 9), 256, DMA_16NOW);
		dmaCopy(palette,&VRAM_E_EXT_PALETTE[bg_number][pal_number],256);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	} else {
		vramSetBankH(VRAM_H_LCD);  // On passe en mode LCD pour pouvoir ecrire dessus, on reviendre en palette apres
		//DMA_Copy(palette, VRAM_H + (bg_number << 13) + (pal_number << 9), 256, DMA_16NOW);
		dmaCopy(palette,&VRAM_H_EXT_PALETTE[bg_number][pal_number],256);
		vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	}
}
