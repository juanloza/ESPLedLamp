#ifndef FIREWORKS_CLASS_H
#define FIREWORKS_CLASS_H

#include "config.h"

#define NUM_SPARKS NUM_LEDS/2
class firework{
  float gravity, flareVel, flarePos, brightness;
  float sparkPos[NUM_SPARKS], sparkVel[NUM_SPARKS], sparkCol[NUM_SPARKS];
  uint8_t nSparks, flareStrip;
  float dying_gravity, c1, c2;
  

  void runFlare(){
    FastLED.clear();
    if(flareVel >= -.2){
      leds[flareStrip][int(flarePos)] = CHSV(0, 0, int(brightness * 255));
      FastLED.show();
      FastLED.clear();
      flarePos += flareVel;
      flareVel += gravity;
      brightness *= .995;
    }else{
      initializeSparks();
    }
  }

  void initializeSparks(){
    srand (millis());
    state = stateList::SPARK;
    FastLED.show();
    FastLED.clear();

    nSparks = flarePos/2;
    for (int i = 0; i < nSparks; i++) {
      sparkPos[i] = flarePos; 
      sparkVel[i] = (float(random16(0, 15000)) / 10000.0) - 1.0; // from -1 to 1 
      sparkCol[i] = abs(sparkVel[i]) * 500; // set colors before scaling velocity to keep them bright 
      sparkCol[i] = constrain(sparkCol[i], 0, 255); 
      sparkVel[i] *= flarePos / NUM_LEDS; // proportional to height 
    }
    sparkCol[0] = 255; // this will be our known spark 
    dying_gravity = gravity; 
    c1 = NUM_LEDS; 
    c2 = 50; 
  }

  void runSpark(){
    srand (millis());
    if(sparkCol[0] > c2/128){
      FastLED.clear();
      for (int i = 0; i < nSparks; i++) { 
        sparkPos[i] += sparkVel[i]; 
        sparkPos[i] = constrain(sparkPos[i], 0, NUM_LEDS-1); 
        sparkVel[i] += dying_gravity; 
        sparkCol[i] *= .99; 
        sparkCol[i] = constrain(sparkCol[i], 0, 255); // red cross dissolve 
        if(sparkCol[i] > c1) { // fade white to yellow
          leds[flareStrip][int(sparkPos[i])] = CRGB(255, 255, (255 * (sparkCol[i] - c1)) / (255 - c1));
        }
        else if (sparkCol[i] < c2) { // fade from red to black
          leds[flareStrip][int(sparkPos[i])] = CRGB((255 * sparkCol[i]) / c2, 0, 0);
        }
        else { // fade from yellow to red
          leds[flareStrip][int(sparkPos[i])] = CRGB(255, (255 * (sparkCol[i] - c2)) / (c1 - c2), 0);
        }
        //Serial.println(sparkPos[i]);
      }
      dying_gravity *= .995; // as sparks burn out they fall slower
      FastLED.show();
    }
    else{
      state = stateList::END;
      FastLED.clear();
      FastLED.show();
    }
  }



  public:
  enum stateList{
    FLARE, SPARK, END
  };
  stateList state;

  firework(){
    state = stateList::FLARE;
    flarePos = 0;
    flareVel = float(random16(55, 70)) / 100;
    brightness = 1;
    flareStrip = random(NUM_STRIPS);
    gravity = -.004;
  }

  ~firework(){}

  void run(){
    switch(state){
      case stateList::FLARE:
        runFlare();
        break;
      case stateList::SPARK:
        runSpark();
        break;
    }
  }
};

#endif