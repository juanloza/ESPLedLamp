#ifndef EFFECT_STARSPARKLE_H
#define EFFECT_STARSPARKLE_H

#include "../helpers.h"
#include "ledEffects.h"

#define MAX_MILIS_FALLING_SPEED 65000

void initStarSparkleEffect(){
    FastLED.setBrightness(MAX_BRIGHTNESS);
    fill_all_strips(applyBrightnessToRGB(starSparkleConfig.bgColor, starSparkleConfig.bgBrightness));
}

CRGB getStarColor(){
    if(starSparkleConfig.color == (CRGB)CRGB::Black){    //Assume that no color means to choose a random one from palette
        uint8_t colorindex = random8();
        return ColorFromPalette( *starSparkleConfig.palette, colorindex, starSparkleConfig.starBrightness, LINEARBLEND);
    }else{
        return applyBrightnessToRGB(starSparkleConfig.color, starSparkleConfig.starBrightness);
    }
}

void RunStarParkle(bool firstTime){
    if(firstTime){
        initStarSparkleEffect();
    }

    if(starSparkleConfig.fallStars){
        static CEveryNMilliseconds triggerFallStar(0);
        if(triggerFallStar){
            for(uint8_t s=0; s<NUM_STRIPS; s++){
                for(uint8_t i=0; i<NUM_LEDS-1; i++){
                leds[s][i] = leds[s][i+1];
                }
                leds[s][NUM_LEDS-1] = applyBrightnessToRGB(starSparkleConfig.bgColor, starSparkleConfig.bgBrightness);
            }
            triggerFallStar.setPeriod((256-starSparkleConfig.fallingSpeed)*(MAX_MILIS_FALLING_SPEED/255.0f));
            triggerFallStar.reset();
        }
    }
    

    fadeAllTowardColorBy(applyBrightnessToRGB(starSparkleConfig.bgColor, starSparkleConfig.bgBrightness), starSparkleConfig.fadeStar);
  
    for(uint8_t s=0; s<NUM_STRIPS; s++){
        if(random8() <= starSparkleConfig.starProbability){
            int Pixel = random(NUM_LEDS);
            leds[s][Pixel] = getStarColor();
        } 
    }
    
    FastLED.delay(1000 / FRAMES_PER_SECOND);

    FastLED.show();
}

#endif