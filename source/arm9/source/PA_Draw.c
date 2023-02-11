#include <PA9.h>

//////////////////////////////////////////////////////////////////////
// Buffer mode
//////////////////////////////////////////////////////////////////////

u16 PA_oldx[2], PA_oldy[2];
s16 PA_olddowntime[2];
u8 PA_drawsize[2];
u16 *PA_DrawBg[2];
u32 *PA_DrawBg32[2];
u8 PA_nBit[2]; // 8 or 16 on each screen...

u16 PA_temppal[256];


u16 tempvar;