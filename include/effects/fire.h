#ifndef EFFECT_FIRE_H
#define EFFECT_FIRE_H

#include "ledEffects.h"

void initFireEffect(){
    FastLED.setBrightness(MAX_BRIGHTNESS);
}

///Fire mode main run function
void RunFire2012WithPalette(bool firstTime)
{
    if(firstTime){
        initFireEffect();
    }
    random16_add_entropy(random());
    // Array of temperature readings at each simulation cell
    static uint8_t heat[NUM_STRIPS][NUM_LEDS];

    for( int s = 0; s < NUM_STRIPS; s++) {
    // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS; i++) {
            heat[s][i] = qsub8( heat[s][i],  random8(0, ((fireConfig.cooling * 10) / NUM_LEDS) + 2));
        }
  
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS - 1; k >= 2; k--) {
            heat[s][k] = (heat[s][k - 1] + heat[s][k - 2] + heat[s][k - 2] ) / 3;
        }
    
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < fireConfig.sparking ) {
            int y = random8(7);
            heat[s][y] = qadd8( heat[s][y], random8(160,255) );
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < NUM_LEDS; j++) {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            uint8_t colorindex = scale8( heat[s][j], 240);
            CRGB color = ColorFromPalette( *fireConfig.palette, colorindex, fireConfig.brightness, LINEARBLEND);
            int pixelnumber;
            if( gReverseDirection ) {
                pixelnumber = (NUM_LEDS-1) - j;
            } else {
                pixelnumber = j;
            }
            leds[s][pixelnumber] = color;
        }
    }
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

#endif