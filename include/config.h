#ifndef LAMPCONFIG_H
#define LAMPCONFIG_H

#include <FastLED.h>

//BASIC LEDS
#define NUM_STRIPS 10
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define CHIPSET     WS2813
#define BRIGHTNESS  200
#define FRAMES_PER_SECOND 60

//LED EFFECTS
bool gReverseDirection = false;
CRGBPalette16 gPal;
CRGB leds[NUM_STRIPS][NUM_LEDS];
#define COOLING  55
#define SPARKING 120

//WEB SERVER
const char* ssid = "VivaElVino";
const char* password = "iJcrqf07";

enum TypeMode{
    FIRE, PLAIN, BEATING, RGBLOOP, STROBE, FADEINOUT, EYES, CYLONBOUNCE, NEWKITT, TWINKLE, TWINKLERANDOM, SPARKLE, SNOWSPARKLE, RUNNINGLIGHTS, COLORWIPE, RAINBOWCYCLE
};

typedef struct fireConfigType{
    uint8_t cooling;
    uint8_t sparking;
    CRGBPalette16 palette;
    String paletteName;
}fireConfigType;

bool enabled;
TypeMode mode;
fireConfigType fireConfig;

void loadDefaultConfig(){
    enabled = false;
    mode = TypeMode::FIRE;
    fireConfig = {55, 120, HeatColors_p,"HeatColors_p"};
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
    json+=tab+tab+"palette:"+(String)fireConfig.paletteName+ln;
    json+=tab+"}"+ln;
    json+="}";
    return json;
}


#endif