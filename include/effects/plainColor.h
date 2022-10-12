#ifndef EFFECT_PLAINCOLOR_H
#define EFFECT_PLAINCOLOR_H

#include "ledEffects.h"

#define PLAINCONFIG_MAX_LEDS 7

void initPlainCollorEffect(){
    FastLED.setBrightness(MAX_BRIGHTNESS);
    fill_all_strips(CRGB::Black);
}

///Plain color mode main run function
void RunPlainColor(bool firstTime){
    if(firstTime){
        initPlainCollorEffect();
    }

    //Fill all leds with selected color
    uint8_t s;
    uint8_t i;
    bool onlyAddLeds = false; //If false, fill all strip with color and then turn off specific leds, if true only turn on specific leds
    uint8_t divisor = plainConfig.numLeds-1;
    uint8_t delta;

    if(plainConfig.numLeds < (PLAINCONFIG_MAX_LEDS-1)/2){
        divisor = PLAINCONFIG_MAX_LEDS - 2 - plainConfig.numLeds;
        onlyAddLeds = true;
    }
    delta = divisor/2;

    if(onlyAddLeds){
        fill_all_strips(CRGB::Black);
    }else{
        fill_all_strips(plainConfig.color);
    }
    
    if(plainConfig.numLeds<7){     
        for (i = 0; i < NUM_LEDS; i++){
            for (s = 0; s < NUM_STRIPS; s++){
                if((((s%2)*delta)+i)%(divisor)==0){
                    if(onlyAddLeds){
                        leds[s][i] = plainConfig.color;
                    }else{
                        leds[s][i] = CRGB::Black;
                    }
                }
            }
        }

        //Turn off some leds
        // if(plainConfig.numLeds==6){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%5==0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }
        //         if((i+2)%5==0){
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }else if(plainConfig.numLeds==5){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%4==0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }
        //         if((i+2)%4==0){
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }else if(plainConfig.numLeds==4){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%3==0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }
        //         if((i+1)%3==0){
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }else if(plainConfig.numLeds==3){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%2==0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }else{
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }else if(plainConfig.numLeds==2){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%3!=0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }
        //         if((i+1)%3!=0){
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }else if(plainConfig.numLeds==1){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%4!=0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }
        //         if((i+2)%4!=0){
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }else if(plainConfig.numLeds==0){
        //     for (i = 0; i < NUM_LEDS; i++){
        //         if((i)%5!=0){
        //             leds[1][i].setRGB(0,0,0);
        //             leds[3][i].setRGB(0,0,0);
        //             // leds[5][i].setRGB(0,0,0);
        //             // leds[7][i].setRGB(0,0,0);
        //             // leds[9][i].setRGB(0,0,0);
        //         }
        //         if((i+2)%5!=0){
        //             leds[0][i].setRGB(0,0,0);
        //             leds[2][i].setRGB(0,0,0);
        //             leds[4][i].setRGB(0,0,0);
        //             // leds[6][i].setRGB(0,0,0);
        //             // leds[8][i].setRGB(0,0,0);
        //         }
        //     }
        // }
    }
    
    //Show with selected brightness
    FastLED.setBrightness(plainConfig.brightness);
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}


#endif