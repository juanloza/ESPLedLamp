#ifndef CUSTOMPALETTES_H
#define CUSTOMPALETTES_H

#include <FastLED.h>

CRGBPalette16 LlamaRoja_p =
{
    0x000000, 0xFF0000, 0xFFFF00, 0xFFFFFF
};

CRGBPalette16 LlamaVerdeAmarilla_p =
{
    0x000000, 0x00FF00, 0xFFFF00, 0xFFFFFF
};

CRGBPalette16 LlamaVerdeAzul_p =
{
    0x000000, 0x00FF00, 0x00FFFF, 0xFFFFFF
};

CRGBPalette16 LlamaAzul_p =
{
    0x000000, 0x0000FF, 0x00FFFF, 0xFFFFFF
};

CRGBPalette16 LlamaVioleta_p =
{
    0x000000, 0x8800FF, 0xFF00FF, 0xFFFFFF
};

CRGBPalette16 LlamaRosa_p =
{
    0x000000, 0xFF00FF, 0xFF8800, 0xFFFFFF
};

CRGBPalette16 LlamaNaranjaButano_p =
{
    0x000000,
    0x00324A, 0x016594, 0x0297DC, 0x91645D, 0xDF4D1F,
    0xEC5120, 0xF95521, 0xFF621F, 0xFF761A, 0xFF8A15,
    0xFF9F10, 0xFFB30B, 0xFFCA2A, 0xFFE495, 0xFFFFFF
};

CRGBPalette16 LlamaTest_p = 
{
    0, 255, 0, 0,
    64, 0, 255, 0,
    128, 0, 0, 255,
    255, 255, 0, 0
};

DEFINE_GRADIENT_PALETTE(testGradient) {
0, 33, 55, 153,
25, 80, 119, 197,
89, 153, 215, 250,
95, 199, 233, 252,
102, 255, 255, 255,
120, 197, 219, 240,
147, 150, 187, 223,
200, 159, 171, 172,
255, 169, 154, 128
};
CRGBPalette16 testPalette = testGradient;

CRGBPalette16 rainbowPalette = Rainbow_gp;


#endif