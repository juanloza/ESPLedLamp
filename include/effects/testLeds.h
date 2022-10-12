#ifndef EFFECT_TESTLEDS_H
#define EFFECT_TESTLEDS_H

#include "ledEffects.h"

///Test mode main run function
void RunTestLeds(bool firstTime){
    CRGB testColors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Pink, CRGB::Yellow, CRGB::Cyan};
    for(int s=0; s<NUM_STRIPS;s++){
        for(int i=0; i<NUM_LEDS;i++){
            leds[s][i] = testColors[i%(sizeof(testColors)/sizeof(*testColors))];
            FastLED.show();
            FastLED.delay(100);
            if(modeHasChanged){
                return;
            }
        }
    }
}

#endif