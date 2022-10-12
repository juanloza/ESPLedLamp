#ifndef LEDEFFECTS_H
#define LEDEFFECTS_H

#include <FastLED.h>
#include "config.h"
#include "effects/effectsList.h"

///Fill all leds of all stripes to black
void TurnOffLeds(){
    fill_all_strips(CRGB::Black);
    FastLED.show();
}

///Main effects run function, it calls current mode specific run function
void RunLedEffects(){
    bool firstTimeMode = modeHasChanged || needRestartEffect;
    if(modeHasChanged){
        modeHasChanged = false;
    }
    if(needRestartEffect){
        needRestartEffect = false;
    }
    switch (mode)
    {
    case TypeMode::TEST:
        RunTestLeds(firstTimeMode);
        Serial.print("Modo: TEST");
        break;
    case TypeMode::PLAIN:
        RunPlainColor(firstTimeMode);
        Serial.print("Modo: PLAIN");
        break;
    case TypeMode::DRAWPALETTE:
        RunDrawPalette(firstTimeMode);
        Serial.print("Modo: DRAWPALETTE");
        break;
    case TypeMode::FIRE:
        RunFire2012WithPalette(firstTimeMode);
        Serial.print("Modo: FIRE");
        break;
    case TypeMode::COMET:
        RunComet(firstTimeMode);
        Serial.print("Modo: COMET");
        break;
    case TypeMode::STARSPARKLE:
        RunStarParkle(firstTimeMode);
        Serial.print("Modo: STAR SPARKLE");
        break;
    default:
        char buffer [50];
        Serial.println(sprintf (buffer, "ERROR!! Modo '%s' no soportado", mode ));
        break;
    }

    //If lamp was disabled, we need to turn off leds
    // if(!enabled){
    //     TurnOffLeds();
    // }
}
#endif