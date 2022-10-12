#ifndef EFFECT_BOUNCINGBALLS_H
#define EFFECT_BOUNCINGBALLS_H

#include "ledEffects.h"


#define MAX_STRIP_BALLS 5  //Maximun of balls per strip ever, ballsConfig max per strip config should be equal or lower

//float Gravity = -9.81;
int StartHeight = 1;
bool activeBalls[NUM_STRIPS][MAX_STRIP_BALLS];
CRGB ballsColor[NUM_STRIPS][MAX_STRIP_BALLS];
float Height[NUM_STRIPS][MAX_STRIP_BALLS];
float ImpactVelocity[NUM_STRIPS][MAX_STRIP_BALLS];
float TimeSinceLastBounce[NUM_STRIPS][MAX_STRIP_BALLS];
int   Position[NUM_STRIPS][MAX_STRIP_BALLS];
long  ClockTimeSinceLastBounce[NUM_STRIPS][MAX_STRIP_BALLS];
float Dampening[NUM_STRIPS][MAX_STRIP_BALLS];
int8_t totalActiveBalls;


void initBuncingBallsEffect(){
  FastLED.setBrightness(MAX_BRIGHTNESS);
  fill_all_strips(applyBrightnessToRGB(starSparkleConfig.bgColor, starSparkleConfig.bgBrightness));
}

CRGB getBallColor(){
  uint8_t colorindex = random8();
  return ColorFromPalette( *ballsConfig.palette, colorindex, ballsConfig.brightness, LINEARBLEND);
}

void addNewBall(){
  if(totalActiveBalls >= ballsConfig.maxTotalBalls){
    return;
  }

  uint8_t ballStrip = random(NUM_STRIPS);
  uint8_t a;

  for(a=0; a<ballsConfig.maxStripBalls; a++){
    if(!activeBalls[ballStrip][a]){
      break;
    }
  }
  if(a>=ballsConfig.maxStripBalls){
    return;
  }
  
  totalActiveBalls++;

  activeBalls[ballStrip][a] = true;
  ballsColor[ballStrip][a] = getBallColor();
  ClockTimeSinceLastBounce[ballStrip][a] = millis();
  Height[ballStrip][a] = StartHeight;
  Position[ballStrip][a] = 0; 
  ImpactVelocity[ballStrip][a] = sqrt( -2 * ballsConfig.gravity * StartHeight );
  TimeSinceLastBounce[ballStrip][a] = 0;
  Dampening[ballStrip][a] = (80 + random(20))/100.0f;
}

///Draw pallette mode main run function
void RunBouncingBalls(bool firstTime){  
  if(firstTime){
    initBuncingBallsEffect();
  }

  //Add new ball
  if(random8() <= ballsConfig.randomNewBall){
      addNewBall();
  }

  fill_all_strips(applyBrightnessToRGB(starSparkleConfig.bgColor, starSparkleConfig.bgBrightness));

  for(uint8_t s=0; s<NUM_STRIPS; s++){
    for(uint8_t a=0; a<MAX_STRIP_BALLS;a++){
      //Skip inactive balls
      if(!activeBalls[s][a]){
          continue;
      }

      TimeSinceLastBounce[s][a] =  (millis() - ClockTimeSinceLastBounce[s][a])/1000;
      Height[s][a] = 0.5 * ballsConfig.gravity * pow(TimeSinceLastBounce[s][a], 2.0 ) + ImpactVelocity[s][a] * TimeSinceLastBounce[s][a];
  
      if ( Height[s][a] < 0 ) {                      
        Height[s][a] = 0;
        ImpactVelocity[s][a] = Dampening[s][a] * ImpactVelocity[s][a];
        ClockTimeSinceLastBounce[s][a] = millis();
  
        if ( ImpactVelocity[s][a] < 0.05 ) {
          activeBalls[s][a] = false;
          continue;
        }
      }
      Position[s][a] = round(Height[s][a] * (NUM_LEDS - 1) / StartHeight);
      leds[s][Position[s][a]] = ballsColor[s][a];
    }
  }

  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);  
}

#endif