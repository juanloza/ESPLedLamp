#ifndef LAMPCONFIG_H
#define LAMPCONFIG_H

#include <iostream>
#include <EEPROM.h>
#include <FastLED.h>
#include "customPalettes.h"

//BASIC LEDS
#define NUM_STRIPS 10
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define CHIPSET     WS2813
#define FRAMES_PER_SECOND 80
#define MAX_BRIGHTNESS 255

//LED EFFECTS
bool gReverseDirection = false;
CRGB leds[NUM_STRIPS][NUM_LEDS];
// CRGBArray<NUM_STRIPS*NUM_LEDS> all_leds;
// CRGBSet leds1(all_leds(0,NUM_LEDS-1));
// CRGBSet leds2(all_leds(NUM_LEDS,NUM_LEDS*2-1));
// CRGBSet leds[NUM_STRIPS] ={
//     all_leds(0*NUM_LEDS,NUM_LEDS*1-1), 
//     all_leds(1*NUM_LEDS,NUM_LEDS*2-1)
// }; 
//CRGBSet leds[NUM_STRIPS];
//leds[0] = CRGBSet(0, NUM_LEDS);


//WEB SERVER
const char* ssid = "VivaElVino";
const char* password = "iJcrqf07";

//Mode types
enum TypeMode{
    TEST, PLAIN, DRAWPALETTE, FIRE, COMET, STARSPARKLE, BOUNCINGBALLS
};

typedef struct plainConfigType{
    CRGB color;
    uint8_t brightness;
    uint8_t numLeds;
}plainConfigType;

typedef struct paletteConfigType{
    CRGBPalette16 *palette;
    uint8_t paletteIndex;
    uint8_t brightness;
    bool reverse;
    uint16_t scale;
    uint8_t speed;
    uint8_t step; //How much advance the color every frame
    uint8_t stripOffset;    //Hot much advance the color from previous strip
}paletteConfigType;

typedef struct fireConfigType{
    uint8_t cooling;
    uint8_t sparking;
    uint8_t brightness;
    CRGBPalette16 *palette;
    uint8_t paletteIndex;
}fireConfigType;

typedef struct cometConfigType{
    CRGB bgColor;
    uint8_t bgBrightness;
    CRGB color;
    CRGBPalette16 *palette; //Color can be a single color, or a palette to randomly choose from
    uint8_t paletteIndex;
    uint8_t brightness;
    uint8_t maxTotalComets;
    uint8_t maxStripComets;
    uint8_t size;
    uint8_t randomNewComet;
    bool randomDecay;
    uint8_t decayProbability;
    uint8_t trailDecay;
    uint8_t speedDelay;
}cometConfigType;

typedef struct starSparkleConfigType{
    CRGB bgColor;
    uint8_t bgBrightness;
    CRGB color;
    CRGBPalette16 *palette; //Sparkle color can be a single color, or a palette to randomly choose from
    uint8_t paletteIndex;
    uint8_t starBrightness;
    uint8_t starProbability;
    uint8_t fadeStar;
    bool fallStars;
    uint8_t fallingSpeed;
}starSparkleConfigType;

typedef struct ballsConfigType{
    CRGB bgColor;
    uint8_t bgBrightness;
    uint8_t brightness;
    CRGB color;
    CRGBPalette16 *palette;
    uint8_t paletteIndex;
    float gravity;
    uint8_t randomNewBall;
    uint8_t maxTotalBalls;
    uint8_t maxStripBalls;
}ballsConfigType;


//Mode configs
bool enabled;
enum TypeMode mode;
plainConfigType plainConfig;
paletteConfigType paletteConfig;
fireConfigType fireConfig;
cometConfigType cometConfig;
starSparkleConfigType starSparkleConfig;
ballsConfigType ballsConfig;

//Run control
bool needRestartEffect = false;
bool modeHasChanged = false;

String getJsonConfig(bool onlyCurrentMode=false){
    const String ln = "\n";
    const String tab = "\t";
    String json = "{"+ln;
    json+=tab+"enabled:"+(String)enabled+','+ln;
    json+=tab+"mode:" + mode + ','+ln;
    if(!onlyCurrentMode || mode == TypeMode::PLAIN){
        json+=tab+"plainConfig:{"+ln;
        char colorbuffer [8];
        sprintf (colorbuffer, "%02X%02X%02X", plainConfig.color.r,plainConfig.color.g,plainConfig.color.b);
        json+=tab+tab+"color:"+(String)colorbuffer+','+ln;
        json+=tab+tab+"brightness:"+(String)plainConfig.brightness+','+ln;
        json+=tab+tab+"numLeds:"+(String)plainConfig.numLeds+','+ln;
        json+=tab+"}"+ln;
        json+="}";
    }
    if(!onlyCurrentMode || mode == TypeMode::FIRE){
        json+=tab+"fireConfig:{"+ln;
        json+=tab+tab+"cooling:"+(String)fireConfig.cooling+','+ln;
        json+=tab+tab+"sparking:"+(String)fireConfig.sparking+','+ln;
        json+=tab+tab+"brightness:"+(String)fireConfig.brightness+','+ln;
        json+=tab+tab+"palette:"+(String)fireConfig.paletteIndex+ln;
        json+=tab+"}"+ln;
    }
    if(!onlyCurrentMode || mode == TypeMode::COMET){
        json+=tab+"cometConfig:{"+ln;
        if(cometConfig.color == (CRGB)CRGB::Black){
            json+=tab+tab+"palette:"+(String)cometConfig.paletteIndex+ln;
        }else{
            char colorbuffer [8];
            sprintf (colorbuffer, "%02X%02X%02X", cometConfig.color.r,cometConfig.color.g,cometConfig.color.b);
            json+=tab+tab+"color:"+(String)colorbuffer+','+ln;
        }
        json+=tab+tab+"brightness:"+(String)cometConfig.brightness+','+ln;
        json+=tab+tab+"size:"+(String)cometConfig.size+','+ln;
        json+=tab+tab+"randomDecay:"+(String)cometConfig.randomDecay+','+ln;
        json+=tab+tab+"decayProbability:"+(String)cometConfig.decayProbability+ln;
        json+=tab+tab+"trailDecay:"+(String)cometConfig.trailDecay+ln;
        json+=tab+tab+"speedDelay:"+(String)cometConfig.speedDelay+ln;
        json+=tab+tab+"maxTotalComets:"+(String)cometConfig.maxTotalComets+ln;
        json+=tab+tab+"maxStripComets:"+(String)cometConfig.maxStripComets+ln;
        json+=tab+"}"+ln;
    }
    if(!onlyCurrentMode || mode == TypeMode::STARSPARKLE){
        json+=tab+"starSparkleConfig:{"+ln;
        char colorbuffer [8];
        sprintf (colorbuffer, "%02X%02X%02X", starSparkleConfig.bgColor.r,starSparkleConfig.bgColor.g,starSparkleConfig.bgColor.b);
        json+=tab+tab+"bgcolor:"+(String)colorbuffer+','+ln;
        json+=tab+tab+"bgbrightness:"+(String)starSparkleConfig.bgBrightness+','+ln;
        if(starSparkleConfig.color == (CRGB)CRGB::Black){
            json+=tab+tab+"palette:"+(String)starSparkleConfig.paletteIndex+ln;
        }else{
            sprintf (colorbuffer, "%02X%02X%02X", starSparkleConfig.color.r,starSparkleConfig.color.g,starSparkleConfig.color.b);
            json+=tab+tab+"color:"+(String)colorbuffer+','+ln;
        }
        json+=tab+tab+"brightness:"+(String)starSparkleConfig.starBrightness+','+ln;
        json+=tab+tab+"starProbability:"+(String)starSparkleConfig.starProbability+','+ln;
        json+=tab+tab+"fadeStar:"+(String)starSparkleConfig.fadeStar+','+ln;
        json+=tab+tab+"fallStars:"+(String)starSparkleConfig.fallStars+ln;
        json+=tab+tab+"fallingSpeed:"+(String)starSparkleConfig.fallingSpeed+ln;
        json+=tab+"}"+ln;
    }
    json+=tab+"}"+ln;
    return json;
}

size_t getConfigSize(){
    size_t totalSize;
    totalSize = sizeof(bool);
    totalSize+= sizeof(TypeMode);
    // totalSize+= sizeof(plainConfigType);
    // totalSize+= sizeof(fireConfigType);

    // Serial.print("FireConfig size:");
    // Serial.println(sizeof(fireConfigType));
    Serial.print("Total config size:");
    Serial.println(totalSize);

    return totalSize*2;
}

void loadDefaultConfig(){
    enabled = false;
    mode = TypeMode::PLAIN;
    plainConfig = {{150,100,255}, 200, 4};
    paletteConfig = {&rainbowPalette, 0, 200, false, 255, 128, 1, 15};
    fireConfig = {55, 120, 255, &LlamaRoja_p, 0};
    cometConfig = {{0,0,0}, 128, {0,0,0}, &rainbowPalette, 0, 200, 8, 3, 5, 5, true, 128, 64, 255};
    starSparkleConfig = {{0,0,0}, 128, {255,255,255}, &rainbowPalette, 0, 255, 15, 8, false, 100};
    ballsConfig = {{0,0,0}, 128, 255, {0,0,0}, &rainbowPalette, 0, -9.81, 127, 20, 3};
}

#endif