#ifndef EFFECT_FIREWORKS_H
#define EFFECT_FIREWORKS_H

#include "ledEffects.h"
#include "firework_class.h"
#include <vector>

#define MAX_FIREWORKS 5

typedef firework* fireworkPtr;
fireworkPtr fartificial[MAX_FIREWORKS];
bool activeFireworks[MAX_FIREWORKS];

void initFireworks(){
    FastLED.setBrightness(MAX_BRIGHTNESS);
    fill_all_strips(CRGB::Black);

    for(uint8_t i=0; i<MAX_FIREWORKS; i++){
        activeFireworks[i] = false;
    }
}

uint8_t newFireworkProbability=5;

void addNewFirework(){
    for(uint8_t i=0; i<MAX_FIREWORKS; i++){
        if(activeFireworks[i]==false){
            activeFireworks[i] = true;
            fartificial[i] = new firework();
        }
    }    
}

///Plain color mode main run function
void RunFireworks(bool firstTime){
    if(firstTime){
        initFireworks();
    }

    if(random8()<=newFireworkProbability){
        addNewFirework();
    }

    for(uint8_t i=0; i<MAX_FIREWORKS; i++){
        if(activeFireworks[i]){
            fartificial[i]->run();
        }
    }
}

#endif