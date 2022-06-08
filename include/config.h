#ifndef LAMPCONFIG_H
#define LAMPCONFIG_H

#include <FastLED.h>
#include "customPalettes.h"

//BASIC LEDS
#define NUM_STRIPS 10
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define CHIPSET     WS2813
#define FRAMES_PER_SECOND 60

//LED EFFECTS
bool gReverseDirection = false;
CRGB leds[NUM_STRIPS][NUM_LEDS];

//WEB SERVER
const char* ssid = "VivaElVino";
const char* password = "iJcrqf07";

typedef enum TypeMode{
    TEST, PLAIN, FIRE, BEATING, RGBLOOP, STROBE, FADEINOUT, EYES, CYLONBOUNCE, NEWKITT, TWINKLE, TWINKLERANDOM, SPARKLE, SNOWSPARKLE, RUNNINGLIGHTS, COLORWIPE, RAINBOWCYCLE
}TypeMode;

typedef struct fireConfigType{
    uint8_t cooling;
    uint8_t sparking;
    uint8_t brightness;
    CRGBPalette16 *palette;
    uint8_t paletteIndex;
}fireConfigType;
typedef struct plainConfigType{
    CRGB color;
    uint8_t brightness;
    uint8_t numLeds;
}plainConfigType;

bool hasChanges = false;
bool enabled;
TypeMode mode;
fireConfigType fireConfig;
plainConfigType plainConfig;

void loadDefaultConfig(){
    enabled = false;
    mode = TypeMode::FIRE;
    fireConfig = {55, 120, 255, &LlamaRoja_p, 0};
    plainConfig = {{150,100,255}, 4};
}

String getJsonConfig(bool onlyCurrentMode=false){
    const String ln = "\n";
    const String tab = "\t";
    String json = "{"+ln;
    json+=tab+"enabled:"+(String)enabled+','+ln;
    json+=tab+"mode:" + mode + ','+ln;
    if(!onlyCurrentMode || mode == TypeMode::FIRE){
        json+=tab+"fireConfig:{"+ln;
        json+=tab+tab+"cooling:"+(String)fireConfig.cooling+','+ln;
        json+=tab+tab+"sparking:"+(String)fireConfig.sparking+','+ln;
        json+=tab+tab+"brightness:"+(String)fireConfig.brightness+','+ln;
        json+=tab+tab+"palette:"+(String)fireConfig.paletteIndex+ln;
        json+=tab+"}"+ln;
    }
    if(!onlyCurrentMode || mode == TypeMode::PLAIN){
        json+=tab+"plainConfig:{"+ln;
        char colorbuffer [8];
        sprintf (colorbuffer, "%X%X%X", plainConfig.color.r,plainConfig.color.g,plainConfig.color.b);
        json+=tab+tab+"color:"+(String)colorbuffer+','+ln;
        json+=tab+tab+"brightness:"+(String)plainConfig.brightness+','+ln;
        json+=tab+tab+"numLeds:"+(String)plainConfig.numLeds+','+ln;
        json+=tab+"}"+ln;
        json+="}";
    }
    return json;
}

#endif