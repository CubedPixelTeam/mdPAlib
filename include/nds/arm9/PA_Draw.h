#ifndef _PA_Buffer
#define _PA_Buffer

#ifdef __cplusplus
extern "C" {
#endif

/*! \file PA_Draw.h
    \brief Bitmap mode, for drawing, loading images in 8 or 16 bit mode...

    Draw on screen, either a pixel or a line, or anything ! Load a Bitmap, a Jpeg...
*/

#include "PA9.h"

#include "PA_Interrupt.h"
#include "PA_Palette.h"

extern u8 PA_nBit[2]; // 8 or 16 bit Bg

extern u16 tempvar;

#define PA_RGB8(r,g,b)	((((b)>>3)<<10)|(((g)>>3)<<5)|((r)>>3)|(1 << 15))

#define __PACKED __attribute__ ((__packed__))

typedef struct{
	u16 Id; // ?
	u32 Length;
	u16 Nothing1, Nothing2; // ?
	u16 ImageStart1, ImageStart2; // Offset of start of image, start at position 0x0A, which can only be 2-byte aligined
} __PACKED BMPHeader0;

typedef struct{
	u32 SizeofHeader; // 40
	u32 Width, Height;
	u16 Colorplanes; // Usually 1
	u16 BitsperPixel; //1, 2, 4, 8, 16, 24, 32
	u32 Compression;  // 0 for none, 1...
	u32 SizeofData; // Not reliable
	u32 WidthperMeter, HeightperMeter; // Don't care
	u32 NColors, ImportantColors; // Number of colors used, important colors ?
} BMP_Headers;

extern u16 PA_oldx[2];
extern u16 PA_oldy[2];
extern s16 PA_olddowntime[2];
extern u8 PA_drawsize[2];
extern u16 *PA_DrawBg[2];
extern u32 *PA_DrawBg32[2];
extern u8 PA_nBit[2]; // 8 or 16 bit Bg

extern u16 PA_temppal[256];
void PA_LoadBmpToBuffer(u16 *Buffer, s16 x, s16 y, void *bmp, s16 SWidth);


/*! \fn static inline void PA_LoadBmpEx(u8 screen, s16 x, s16 y, void *bmp)
    \brief
         \~english Load a BMP on a 16 bit background... Don't forget to Init the background !
         \~french Charger un BMP sur un fond de 16 bits... Faut pas oublier de charger ce fond avant !
    \~\param screen
         \~english Chose de screen (0 or 1)
         \~french Choix de l'écran (0 ou 1)	
    \~\param x
         \~english X position of the top left corner
         \~french Position X du coin supérieur gauche	
    \~\param y
         \~english Y position of the top left corner
         \~french Position Y du coin supérieur gauche		 
    \~\param bmp
         \~english BMP image...
         \~french image au format BMP...	 
*/
static inline void PA_LoadBmpEx(u8 screen, s16 x, s16 y, void *bmp){
	PA_LoadBmpToBuffer(PA_DrawBg[screen], x, y, bmp, 256);
}



/*! \fn static inline void PA_LoadBmp(u8 screen, void *bmp)
    \brief
         \~english Load a BMP on a 16 bit background... Don't forget to Init the background !
         \~french Charger un BMP sur un fond de 16 bits... Faut pas oublier de charger ce fond avant !
    \~\param screen
         \~english Chose de screen (0 or 1)
         \~french Choix de l'écran (0 ou 1)		 
    \~\param bmp
         \~english BMP image...
         \~french image au format BMP...	 
*/
static inline void PA_LoadBmp(u8 screen, void *bmp){
	PA_LoadBmpEx(screen, 0, 0, bmp);
}

/*! \fn static inline u16 PA_GetBmpWidth(void *bmp)
    \brief
         \~english Get a BMP's width in pixels
         \~french Récupérer la largeur d'un BMP en pixels
    \~\param bmp
         \~english BMP image...
         \~french image au format BMP...	 
*/
static inline u16 PA_GetBmpWidth(void *bmpdata){
	u8 *temp = (u8*)bmpdata;
	BMP_Headers *Bmpinfo = (BMP_Headers*)(temp+14);
	return Bmpinfo->Width;
}


/*! \fn static inline u16 PA_GetBmpHeight(void *bmp)
    \brief
         \~english Get a BMP's height in pixels
         \~french Récupérer la hauteur d'un BMP en pixels
    \~\param bmp
         \~english BMP image...
         \~french image au format BMP...	 
*/
static inline u16 PA_GetBmpHeight(void *bmpdata){
	u8 *temp = (u8*)bmpdata;
	BMP_Headers *Bmpinfo = (BMP_Headers*)(temp+14);
	return Bmpinfo->Height;
}
/** @} */ // end of Draw

#ifdef __cplusplus
}
#endif

#endif
