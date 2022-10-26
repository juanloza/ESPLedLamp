#ifndef EFFECT_DRAWPALETTE_H
#define EFFECT_DRAWPALETTE_H

#define MAX_MILIS_PALETTE_SPEED 2000

#include "ledEffects.h"

uint8_t colorindex;

///Draw pallette mode main run function
void RunDrawPalette(bool firstTime){
    static float runningOffset; //Its important to be a float, cause scale may cause float offsets and it must be valids (rounded to int colorIndex  later)
    if(firstTime){
        runningOffset = 0;
    }

    static CEveryNMilliseconds triggerpaletteWalk(0);
    if(triggerpaletteWalk){
        if(paletteConfig.speed>0){
            //runningOffset+= paletteConfig.step;
            runningOffset+=float(paletteConfig.step) * float(paletteConfig.scale/255.0f);
            if(runningOffset > 256){
                runningOffset -= 256;   //Only to avoid toooooo large numbers
            }
        }
        triggerpaletteWalk.setPeriod((255-paletteConfig.speed)*(MAX_MILIS_PALETTE_SPEED/255));
        triggerpaletteWalk.reset();
    }

    uint8_t colorIndex;
    for( int s = 0; s < NUM_STRIPS; s++) {
        for( int i = 0; i < NUM_LEDS; i++) {
            colorIndex = scaleNumber(i, 0, NUM_LEDS-1, 0, paletteConfig.scale);
            colorIndex += s*paletteConfig.stripOffset + runningOffset;
            CRGB color = ColorFromPalette(*paletteConfig.palette, colorIndex, paletteConfig.brightness, LINEARBLEND);
            leds[s][i] = color;
        }
    }
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

#endif