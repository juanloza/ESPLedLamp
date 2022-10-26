#ifndef EFFECT_COMET_H
#define EFFECT_COMET_H

#include "../helpers.h"
#include "ledEffects.h"

#define MAX_STRIP_COMETS 5  //Maximun of comets per strip ever, cometrConfig max per strip config should be equal or lower
#define MAX_MILIS_COMET_SPEED 1500

int8_t totalRunningComets;
bool activeComets[NUM_STRIPS][MAX_STRIP_COMETS];
int8_t cometPosition[NUM_STRIPS][MAX_STRIP_COMETS];
int8_t cometDirection[NUM_STRIPS][MAX_STRIP_COMETS];
CRGB cometColor[NUM_STRIPS][MAX_STRIP_COMETS];

void initCometEffect(){
    FastLED.setBrightness(MAX_BRIGHTNESS);
    totalRunningComets=0;
    fill_all_strips(applyBrightnessToRGB(cometConfig.bgColor, cometConfig.bgBrightness));
    for(uint8_t s=0; s<NUM_STRIPS;s++){
        for(uint8_t a=0; a<MAX_STRIP_COMETS;a++){
            activeComets[s][a]=false;
        }
    }
}

void checkEndComet(uint8_t s, uint8_t a){
  if(
    (cometDirection[s][a]>0 && cometPosition[s][a]-cometConfig.size > NUM_LEDS)
    ||
    (cometDirection[s][a]<0 && cometPosition[s][a]+cometConfig.size < 0)){
    activeComets[s][a] = false;
    totalRunningComets--;
  }
}

CRGB getCometColor(){
    if(cometConfig.color == (CRGB)CRGB::Black){    //Assume that no color means to choose a random one from palette
        uint8_t colorindex = random8();
        return ColorFromPalette( *cometConfig.palette, colorindex, cometConfig.brightness, LINEARBLEND);
    }else{
        return applyBrightnessToRGB(cometConfig.color, cometConfig.brightness);
    }
}

void addComet(){
  if(totalRunningComets >= cometConfig.maxTotalComets){
    return;
  }

  uint8_t cometStrip = random(NUM_STRIPS);
  uint8_t a;

  for(a=0; a<cometConfig.maxStripComets; a++){
    if(!activeComets[cometStrip][a]){
      break;
    }
  }
  if(a>=cometConfig.maxStripComets){
    return;
  }
  
  totalRunningComets++;

  activeComets[cometStrip][a] = true;
  cometColor[cometStrip][a] = getCometColor();
  if(random(10)<5){    //random(10) generates numbers from 0 to 9
    cometPosition[cometStrip][a] = NUM_LEDS-1;
    cometDirection[cometStrip][a] = -1;
  }else{
    cometPosition[cometStrip][a] = 0;
    cometDirection[cometStrip][a] = 1;
  }
}

void RunComet(bool firstTime){
    if(firstTime){
        initCometEffect();
    }

    //Add new comet
    if(random8() <= cometConfig.randomNewComet){
        addComet();
    }

    static CEveryNMilliseconds triggerCometWalk(0);
    if(triggerCometWalk){
        for(uint8_t s=0; s<NUM_STRIPS; s++){
            for(uint8_t a=0; a<MAX_STRIP_COMETS;a++){
                //Skip inactive comets
                if(!activeComets[s][a]){
                    continue;
                }

                //Update comet position
                if(cometDirection[s][a]>0){
                    cometPosition[s][a]++;
                    for(uint8_t m=0; m<cometConfig.size; m++){
                        uint8_t pos = cometPosition[s][a]-m;
                        if(pos<0 || pos>= NUM_LEDS){
                            continue;
                        }
                        leds[s][pos] += cometColor[s][a];
                    }
                }else if(cometDirection[s][a]<0){
                    cometPosition[s][a]--;
                    for(uint8_t m=0; m<cometConfig.size; m++){
                        uint8_t pos = cometPosition[s][a]+m;
                        if(pos<0 || pos>= NUM_LEDS){
                            continue;
                        }
                        leds[s][pos] += cometColor[s][a];
                    }
                }
                checkEndComet(s, a);
            }
        }
        

        triggerCometWalk.setPeriod((255-cometConfig.speed)*(MAX_MILIS_COMET_SPEED/255.0f));
        triggerCometWalk.reset();
    }

    //Fade to background color all pixels
    for(uint8_t s=0; s<NUM_STRIPS; s++) {
        for(uint8_t j=0; j<NUM_LEDS; j++) {
            if( (!cometConfig.randomDecay) || (random8()<=cometConfig.decayProbability) ) {
                if(leds[s][j] != applyBrightnessToRGB(cometConfig.bgColor, cometConfig.bgBrightness)){
                    fadeTowardColorBy(&leds[s][j],1, applyBrightnessToRGB(cometConfig.bgColor, cometConfig.bgBrightness),cometConfig.trailDecay);
                }
                //fadeToBlackBy(&leds[s][j], 1, cometConfig.trailDecay);
            }
        }
    }
    
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

#endif