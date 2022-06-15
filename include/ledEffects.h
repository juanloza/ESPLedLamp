#ifndef LEFEFFECTS_H
#define LEFEFFECTS_H

#include <FastLED.h>
#include "config.h"

float scale_to_palette = (255.0/NUM_LEDS);

CRGBPalette16* SelectPalette(u_int8_t p){
    switch (p)
    {
    case 0:
        return &LlamaRoja_p;
    case 1:
        return &LlamaVerdeAmarilla_p;
    case 2:
        return &LlamaVerdeAzul_p;
    case 3:
        return &LlamaAzul_p;
    case 4:
        return &LlamaVioleta_p;
    case 5:
        return &LlamaRosa_p;
    case 6:
        return &LlamaNaranjaButano_p;
    case 7:
        return &LlamaTest_p;
    // case 8:
    //     return &testPalette;
    /*
    case 4:
        return &(CRGBPalette16)ForestColors_p;
    case 5:
        return &(CRGBPalette16)RainbowColors_p;
    case 6:
        return &(CRGBPalette16)RainbowStripeColors_p;
    case 7:
        return &(CRGBPalette16)PartyColors_p;
    case 8:    
        return &CRGBPalette16(
            CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
            CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black,
            CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
            CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black );
    case 9:
        return &CRGBPalette16(
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black,
            CRGB::White, CRGB::Black, CRGB::Black,  CRGB::Black );
    case 10:
        return &CRGBPalette16(
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()),
            CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()), CHSV( random8(), 255, random8()),  CHSV( random8(), 255, random8()) );*/
    default:
        return &LlamaRoja_p;
        break;
    }
}

///Fill all leds of all stripes to black
void TurnOffLeds(){
    for (uint8_t s=0; s<NUM_STRIPS; s++)
    {
        fill_solid(leds[s], NUM_LEDS, CRGB::Black);
    }
    FastLED.show();
}

///Test mode main run function
void RunTestLeds(){
    for(int s=0; s<NUM_STRIPS;s++){
        for(int i=0; i<NUM_LEDS;i++){
            leds[s][i] = CRGB::Red;
            FastLED.show();
            FastLED.delay(100);
            leds[s][i] = CRGB::Green;
            FastLED.show();
            FastLED.delay(100);
            leds[s][i] = CRGB::Blue;
            FastLED.show();
            FastLED.delay(100);
            if(hasChanges){
                return;
            }
        }
    }
}

///Plain color mode main run function
void RunPlainColor(){
    //Fill all leds with selected color
    uint8_t s;
    uint8_t i;

    for (s = 0; s < NUM_STRIPS; s++){
        fill_solid(leds[s], NUM_LEDS, plainConfig.color);
        if(hasChanges){
            return;
        }
    }
    
    if(plainConfig.numLeds<5){
        for (s = 0; s < NUM_STRIPS; s++)
        {        
            //Turn off some leds
            if(plainConfig.numLeds==4){
                /*
                o  o  o  o  o  o  o  6
                o  -  o  -  o  -  o  5
                o  o  o  o  o  o  o  4
                -  o  -  o  -  o  -  3
                o  o  o  o  o  o  o  2
                o  -  o  -  o  -  o  1
                o  o  o  o  o  o  o  0
                */
                for (i = 0; i < NUM_LEDS; i+=2){
                    if((i-1)%4==0){
                        leds[1][i].setRGB(0,0,0);
                        leds[3][i].setRGB(0,0,0);
                        leds[5][i].setRGB(0,0,0);
                        leds[7][i].setRGB(0,0,0);
                        leds[9][i].setRGB(0,0,0);
                    }else if((i+1)%4==0){
                        leds[0][i].setRGB(0,0,0);
                        leds[2][i].setRGB(0,0,0);
                        leds[4][i].setRGB(0,0,0);
                        leds[6][i].setRGB(0,0,0);
                        leds[8][i].setRGB(0,0,0);
                    }
                }
            }else if(plainConfig.numLeds==3){
                /*
                -  o  -  o  -  o  -  6
                o  -  o  -  o  -  o  5
                o  o  o  o  o  o  o  4
                -  o  -  o  -  o  -  3
                o  -  o  -  o  -  o  2
                o  o  o  o  o  o  o  1
                -  o  -  o  -  o  -  0
                */
                for (i = 0; i < NUM_LEDS; i++){
                    if((i)%3==0){
                        leds[1][i].setRGB(0,0,0);
                        leds[3][i].setRGB(0,0,0);
                        leds[5][i].setRGB(0,0,0);
                        leds[7][i].setRGB(0,0,0);
                        leds[9][i].setRGB(0,0,0);
                    }
                    if((i+1)%3==0){
                        leds[0][i].setRGB(0,0,0);
                        leds[2][i].setRGB(0,0,0);
                        leds[4][i].setRGB(0,0,0);
                        leds[6][i].setRGB(0,0,0);
                        leds[8][i].setRGB(0,0,0);
                    }
                }
            }else if(plainConfig.numLeds==2){
                /*
                o  -  o  -  o  -  o  6
                -  o  -  o  -  o  -  5
                o  -  o  -  o  -  o  4
                -  o  -  o  -  o  -  3
                o  -  o  -  o  -  o  2
                -  o  -  o  -  o  -  1
                o  -  o  -  o  -  o  0
                */
            for (i = 0; i < NUM_LEDS; i++){
                    if((i)%2==0){
                        leds[1][i].setRGB(0,0,0);
                        leds[3][i].setRGB(0,0,0);
                        leds[5][i].setRGB(0,0,0);
                        leds[7][i].setRGB(0,0,0);
                        leds[9][i].setRGB(0,0,0);
                    }else{
                        leds[0][i].setRGB(0,0,0);
                        leds[2][i].setRGB(0,0,0);
                        leds[4][i].setRGB(0,0,0);
                        leds[6][i].setRGB(0,0,0);
                        leds[8][i].setRGB(0,0,0);
                    }
                }
            }else if(plainConfig.numLeds==1){
                /*
                o  -  o  -  o  -  o  6
                -  o  -  o  -  o  -  5
                -  -  -  -  -  -  -  4
                o  -  o  -  o  -  o  3
                -  o  -  o  -  o  -  2
                -  -  -  -  -  -  -  1
                o  -  o  -  o  -  o  0
                */
                for (i = 0; i < NUM_LEDS; i++){
                    if((i)%3!=0){
                        leds[1][i].setRGB(0,0,0);
                        leds[3][i].setRGB(0,0,0);
                        leds[5][i].setRGB(0,0,0);
                        leds[7][i].setRGB(0,0,0);
                        leds[9][i].setRGB(0,0,0);
                    }
                    if((i+1)%3!=0){
                        leds[0][i].setRGB(0,0,0);
                        leds[2][i].setRGB(0,0,0);
                        leds[4][i].setRGB(0,0,0);
                        leds[6][i].setRGB(0,0,0);
                        leds[8][i].setRGB(0,0,0);
                    }
                }
            }else if(plainConfig.numLeds==0){
                /*
                -  -  -  -  -  -  -  6
                -  o  -  o  -  o  -  5
                -  -  -  -  -  -  -  4
                o  -  o  -  o  -  o  3
                -  -  -  -  -  -  -  2
                -  o  -  o  -  o  -  1
                -  -  -  -  -  -  -  0
                */
                for (i = 0; i < NUM_LEDS; i+=2){
                    if((i-1)%4!=0){
                        leds[1][i].setRGB(0,0,0);
                        leds[3][i].setRGB(0,0,0);
                        leds[5][i].setRGB(0,0,0);
                        leds[7][i].setRGB(0,0,0);
                        leds[9][i].setRGB(0,0,0);
                    }else if((i+1)%4!=0){
                        leds[0][i].setRGB(0,0,0);
                        leds[2][i].setRGB(0,0,0);
                        leds[4][i].setRGB(0,0,0);
                        leds[6][i].setRGB(0,0,0);
                        leds[8][i].setRGB(0,0,0);
                    }
                }
            }
            if(hasChanges){
                return;
            }
        }
    }
    
    //Show with selected brightness
    FastLED.setBrightness(plainConfig.brightness);
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

///Fire mode main run function
void RunFire2012WithPalette()
{
    random16_add_entropy(random());
    // Array of temperature readings at each simulation cell
    static uint8_t heat[NUM_STRIPS][NUM_LEDS];

    for( int s = 0; s < NUM_STRIPS; s++) {
    // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS; i++) {
            heat[s][i] = qsub8( heat[s][i],  random8(0, ((fireConfig.cooling * 10) / NUM_LEDS) + 2));
        }
  
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS - 1; k >= 2; k--) {
            heat[s][k] = (heat[s][k - 1] + heat[s][k - 2] + heat[s][k - 2] ) / 3;
        }
    
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < fireConfig.sparking ) {
            int y = random8(7);
            heat[s][y] = qadd8( heat[s][y], random8(160,255) );
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < NUM_LEDS; j++) {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            uint8_t colorindex = scale8( heat[s][j], 240);
            CRGB color = ColorFromPalette( *fireConfig.palette, colorindex, fireConfig.brightness, LINEARBLEND);
            int pixelnumber;
            if( gReverseDirection ) {
                pixelnumber = (NUM_LEDS-1) - j;
            } else {
                pixelnumber = j;
            }
            leds[s][pixelnumber] = color;
        }
    }
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

///Draw pallette mode main run function
void RunDrawPalette(){

    for( int s = 0; s < NUM_STRIPS; s++) {
        for( int i = 0; i < NUM_LEDS; i++) {
            uint8_t colorindex = ( i+1 ) * scale_to_palette;
            CRGB color = ColorFromPalette(*fireConfig.palette, colorindex);
            leds[s][i] = color;
        }
    }
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

///Main effects run function, it calls current mode specific run function
void RunLedEffects(){
    switch (mode)
    {
    case TypeMode::TEST:
        RunTestLeds();
        break;
    case TypeMode::PLAIN:
        RunPlainColor();
        break;
    case TypeMode::FIRE:
        RunFire2012WithPalette();
        break;
    case TypeMode::BEATING:
        RunDrawPalette();
        break;
    default:
        char buffer [50];
        Serial.println(sprintf (buffer, "ERROR!! Modo '%s' no soportado", mode ));
        break;
    }

    //If lamp was disabled or mode changed, we need to turn off leds and reset modeHasChanged state
    if(!enabled || modeHasChanged){
        modeHasChanged=false;
        TurnOffLeds();
    }

    //All functions must use current settings and hasChanges are only used to interrumpt current effect
    if(hasChanges){
        hasChanges=false;
    }
}
#endif