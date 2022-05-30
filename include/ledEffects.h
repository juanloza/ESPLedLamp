#ifndef LEFEFFECTS_H
#define LEFEFFECTS_H

#include <FastLED.h>
#include "config.h"

const CRGBPalette16 SelectPalette(u_int8_t p){
    switch (p)
    {
    case 0:
        return HeatColors_p;
    case 1:
        return CloudColors_p;
    case 2:
        return LavaColors_p;
    case 3:
        return OceanColors_p;
    case 4:
        return ForestColors_p;
    case 5:
        return RainbowColors_p;
    case 6:
        return RainbowStripeColors_p;
    case 7:
        return PartyColors_p;
    case 8:    
        return CRGBPalette16(
            CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
            CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black,
            CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
            CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black );
    case 9:
        return CRGBPalette16(
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black );
    case 10:
        return CRGBPalette16(
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()) );
    default:
        return HeatColors_p;
        break;
    }
}

CRGBPalette16 setCustomPalette(const CRGB& c1, const CRGB& c2, const CRGB& c3, const CRGB& c4){
    return CRGBPalette16(c1, c2, c3, c4);
}

void Fire2012WithPalette()
{
    random16_add_entropy(random());
    // Array of temperature readings at each simulation cell
    static uint8_t heat[NUM_STRIPS][NUM_LEDS];

    for( int s = 0; s < NUM_STRIPS; s++) {
    // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS; i++) {
            heat[s][i] = qsub8( heat[s][i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
        }
  
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS - 1; k >= 2; k--) {
            heat[s][k] = (heat[s][k - 1] + heat[s][k - 2] + heat[s][k - 2] ) / 3;
        }
    
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < SPARKING ) {
            int y = random8(7);
            heat[s][y] = qadd8( heat[s][y], random8(160,255) );
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < NUM_LEDS; j++) {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            uint8_t colorindex = scale8( heat[s][j], 240);
            CRGB color = ColorFromPalette( *fireConfig.palette, colorindex, fireConfig.brightness, currentBlending);
            int pixelnumber;
            if( gReverseDirection ) {
                pixelnumber = (NUM_LEDS-1) - j;
            } else {
                pixelnumber = j;
            }
            leds[s][pixelnumber] = color;
        }
    }
}

void RunLedEffects(){
    switch (mode)
    {
    case TypeMode::FIRE:
        Fire2012WithPalette();
        break;
    
    default:
        char buffer [50];
        Serial.println(sprintf (buffer, "ERROR!! Modo '%s' no soportado", mode ));
        break;
    }
}
#endif