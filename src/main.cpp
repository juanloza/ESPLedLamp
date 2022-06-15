


#include <Arduino.h>
#include <pgmspace.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include "config.h"
#include "ledEffects.h"
#include "serverManager.h"

void setup() {
    Serial.begin(115200);
    Serial.println("SETUP");

    if(!connectToWIFI()){
      return;
    }
    
    addServerHandlers();

    loadDefaultConfig();

    FastLED.addLeds<CHIPSET,13, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,12, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,27, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,25, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,32, COLOR_ORDER>(leds[4], NUM_LEDS).setCorrection( TypicalLEDStrip );  
    FastLED.addLeds<CHIPSET,4, COLOR_ORDER>(leds[5], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,18, COLOR_ORDER>(leds[6], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,19, COLOR_ORDER>(leds[7], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,21, COLOR_ORDER>(leds[8], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET,22, COLOR_ORDER>(leds[9], NUM_LEDS).setCorrection( TypicalLEDStrip );
    // FastLED.setBrightness( brightness );
}

void loop() {
    if(!enabled){
        delay(2000);
        return;
    }
    
    RunLedEffects();
}