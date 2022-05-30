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
//uint8_t brightness = 200;
TBlendType currentBlending = LINEARBLEND;

//LED EFFECTS
bool gReverseDirection = false;
CRGB leds[NUM_STRIPS][NUM_LEDS];
#define COOLING  55
#define SPARKING 120

//WEB SERVER
const char* ssid = "VivaElVino";
const char* password = "iJcrqf07";

typedef enum TypeMode{
    FIRE, PLAIN, BEATING, RGBLOOP, STROBE, FADEINOUT, EYES, CYLONBOUNCE, NEWKITT, TWINKLE, TWINKLERANDOM, SPARKLE, SNOWSPARKLE, RUNNINGLIGHTS, COLORWIPE, RAINBOWCYCLE
}TypeMode;

typedef struct fireConfigType{
    uint8_t cooling;
    uint8_t sparking;
    uint8_t brightness;
    CRGBPalette16 *palette;
    uint8_t paletteIndex;
}fireConfigType;

CRGBPalette16 *firePaletteList[5] = {
    &(CRGBPalette16)HeatColors_p,
    &(CRGBPalette16)CloudColors_p,
    &(CRGBPalette16)LlamaAzul_p,
    &(CRGBPalette16)LlamaVerde_p,
    &(CRGBPalette16)LlamaVioleta_p,
};

bool hasChanges = false;
bool enabled;
TypeMode mode;
fireConfigType fireConfig;

void loadDefaultConfig(){
    enabled = false;
    mode = TypeMode::FIRE;
    fireConfig = {55, 120, 255, &(CRGBPalette16)HeatColors_p, 0};
}

String getJsonConfig(){
    String ln = "\n";
    String tab = "\t";
    String json = "{"+ln;
    json+=tab+"enabled:"+(String)enabled+','+ln;
    json+=tab+"mode:" + mode + ','+ln;
    json+=tab+"fireconfig:{"+ln;
    json+=tab+tab+"cooling:"+(String)fireConfig.cooling+','+ln;
    json+=tab+tab+"sparking:"+(String)fireConfig.sparking+','+ln;
    json+=tab+tab+"brightness:"+(String)fireConfig.brightness+','+ln;
    json+=tab+tab+"palette:"+(String)fireConfig.paletteIndex+ln;
    json+=tab+"}"+ln;
    json+="}";
    return json;
}


#endif