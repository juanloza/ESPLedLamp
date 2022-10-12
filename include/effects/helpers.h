#ifndef EFFECT_HELPERS_H
#define EFFECT_HELPERS_H

#include "config.h"

float scale_to_palette = (255.0/(NUM_LEDS-1));

float scaleNumber(float number, float receivedMin=0.0f, float receivedMax=NUM_LEDS-1, float scaleToMin=0.0f, float scaleToMax=255.0f){
    //       (b-a)(x - min)
    //f(x) = --------------  + a
    //          max - min
  
    //Serial.print(number);
    //Serial.print(": ");
    //Serial.println( ((b - a) * (number - valMin)) / (valMax - valMin) + a);
    return ((scaleToMax - scaleToMin) * (number - receivedMin)) / (receivedMax - receivedMin) + scaleToMin;
}

CRGBPalette16* SelectFirePalette(u_int8_t p){
    switch (p)
    {
    case 0:
        return &LlamaRoja_p;
    case 1:
        return &LlamaVerdeAmarilla_p;
    case 2:
        return &LlamaVerdeAzul_p;
    case 3:
        return &LlamaAzul_p;
    case 4:
        return &LlamaVioleta_p;
    case 5:
        return &LlamaRosa_p;
    case 6:
        return &LlamaNaranjaButano_p;
    case 7:
        return &LlamaTest_p;
    // case 8:
    //     return &testPalette;
    /*
    case 4:
        return &(CRGBPalette16)ForestColors_p;
    case 5:
        return &(CRGBPalette16)RainbowColors_p;
    case 6:
        return &(CRGBPalette16)RainbowStripeColors_p;
    case 7:
        return &(CRGBPalette16)PartyColors_p;
    case 8:    
        return &CRGBPalette16(
            CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
            CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black,
            CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
            CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black );
    case 9:
        return &CRGBPalette16(
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black );
    case 10:
        return &CRGBPalette16(
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()) );*/
    default:
        return &LlamaRoja_p;
        break;
    }
}

CRGBPalette16* SelectCometPalette(u_int8_t p){
    switch (p)
    {
    case 0:
        return &rainbowPalette;
    case 1:
        return &LlamaRoja_p;
    case 2:
        return &LlamaVerdeAmarilla_p;
    case 3:
        return &LlamaVerdeAzul_p;
    case 4:
        return &LlamaAzul_p;
    case 5:
        return &LlamaVioleta_p;
    case 6:
        return &LlamaRosa_p;
    case 7:
        return &LlamaNaranjaButano_p;
    case 8:
        return &LlamaTest_p;
    default:
        return &rainbowPalette;
        break;
    }
}

#endif