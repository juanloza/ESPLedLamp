#include <Arduino.h>
#include <EEPROM.h>
#include <pgmspace.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include "config.h"
#include "helpers.h"
#include "ledEffects.h"
#include "serverManager.h"

void setup() {
    Serial.begin(115200);
    Serial.println("SETUP");

    EEPROM.begin(getConfigSize());

    loadDefaultConfig();

    // loadConfigEEPROM();

    if(!connectToWIFI()){
       return;
    }
    
     addServerHandlers();

    //ORIGINAL PINS
    //13,12,27,25,32
    //4,18,19,21,22
    //27 fails when send signal to 25
    //TEST PINS
    //14,26,33, 15,2,0,16,17,5,1,3,23


    pinMode(13, OUTPUT);
    FastLED.addLeds<CHIPSET,13, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(12, OUTPUT);
    FastLED.addLeds<CHIPSET,12, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(27, OUTPUT);
    FastLED.addLeds<CHIPSET,27, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(25, OUTPUT);
    FastLED.addLeds<CHIPSET,25, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(32, OUTPUT);
    FastLED.addLeds<CHIPSET,32, COLOR_ORDER>(leds[4], NUM_LEDS).setCorrection( UncorrectedColor );  

    pinMode(4, OUTPUT);
    FastLED.addLeds<CHIPSET,4, COLOR_ORDER>(leds[5], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(18, OUTPUT);
    FastLED.addLeds<CHIPSET,18, COLOR_ORDER>(leds[6], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(19, OUTPUT);
    FastLED.addLeds<CHIPSET,19, COLOR_ORDER>(leds[7], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(21, OUTPUT);
    FastLED.addLeds<CHIPSET,21, COLOR_ORDER>(leds[8], NUM_LEDS).setCorrection( UncorrectedColor );
    pinMode(22, OUTPUT);
    FastLED.addLeds<CHIPSET,22, COLOR_ORDER>(leds[9], NUM_LEDS).setCorrection( UncorrectedColor );
    //FastLED.setBrightness( brightness );

    FastLED.setMaxPowerInMilliWatts(199000);
}

void loop() {
    if(!enabled){
        fill_all_strips(CRGB::Black);
        FastLED.show();
        delay(2000);
        return;
    }
    
    RunLedEffects();
}