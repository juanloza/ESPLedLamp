#ifndef LEFEFFECTS_H
#define LEFEFFECTS_H

#include <FastLED.h>
#include "config.h"

void Fire2012WithPalette()
{
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
      CRGB color = ColorFromPalette( gPal, colorindex);
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