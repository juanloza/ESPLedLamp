#ifndef HELPERS_H
#define HELPERS_H

#include <FastLED.h>
#include "config.h"

#define TOTAL_LEDS 600

byte coordsX[TOTAL_LEDS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
byte coordsY[TOTAL_LEDS] = { 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255, 0, 4, 9, 13, 17, 22, 26, 30, 35, 39, 43, 48, 52, 56, 61, 65, 69, 73, 78, 82, 86, 91, 95, 99, 104, 108, 112, 117, 121, 125, 130, 134, 138, 143, 147, 151, 156, 160, 164, 169, 173, 177, 182, 186, 190, 194, 199, 203, 207, 212, 216, 220, 225, 229, 233, 238, 242, 246, 251, 255 };
byte angles[TOTAL_LEDS] = { 46, 45, 45, 44, 44, 43, 42, 42, 41, 40, 39, 38, 37, 36, 35, 33, 32, 30, 29, 27, 25, 23, 21, 19, 16, 14, 11, 9, 6, 3, 0, 252, 249, 246, 244, 241, 239, 236, 234, 232, 230, 228, 226, 225, 223, 222, 220, 219, 218, 217, 216, 215, 214, 213, 213, 212, 211, 211, 210, 210, 49, 49, 49, 48, 48, 47, 46, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 35, 34, 32, 30, 28, 26, 23, 20, 17, 14, 11, 7, 4, 0, 251, 248, 244, 241, 238, 235, 232, 229, 227, 225, 223, 221, 220, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 209, 208, 207, 207, 206, 206, 53, 53, 52, 52, 52, 51, 51, 50, 50, 49, 48, 48, 47, 46, 45, 44, 43, 41, 40, 38, 36, 34, 32, 29, 26, 23, 19, 15, 10, 5, 0, 250, 245, 240, 236, 232, 229, 226, 223, 221, 219, 217, 215, 214, 212, 211, 210, 209, 208, 207, 207, 206, 205, 205, 204, 204, 203, 203, 203, 202, 57, 57, 57, 56, 56, 56, 55, 55, 55, 54, 54, 53, 53, 52, 51, 51, 50, 49, 48, 46, 45, 43, 41, 39, 36, 32, 27, 22, 15, 8, 0, 247, 240, 233, 228, 223, 219, 216, 214, 212, 210, 209, 207, 206, 205, 204, 204, 203, 202, 202, 201, 201, 200, 200, 200, 199, 199, 199, 198, 198, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 59, 59, 59, 59, 58, 58, 58, 57, 56, 56, 55, 54, 52, 51, 48, 45, 40, 32, 19, 0, 236, 223, 215, 210, 207, 204, 203, 201, 200, 199, 199, 198, 197, 197, 197, 196, 196, 196, 196, 195, 195, 195, 195, 195, 194, 194, 194, 194, 194, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 68, 68, 69, 70, 70, 72, 74, 77, 83, 96, 128, 159, 172, 178, 181, 183, 185, 185, 186, 187, 187, 188, 188, 188, 188, 189, 189, 189, 189, 189, 189, 189, 189, 189, 190, 190, 190, 190, 190, 190, 69, 69, 70, 70, 70, 70, 70, 71, 71, 71, 72, 72, 73, 73, 74, 74, 75, 76, 77, 78, 79, 81, 83, 85, 88, 91, 96, 101, 109, 118, 128, 137, 146, 154, 159, 164, 167, 170, 172, 174, 176, 177, 178, 179, 180, 181, 181, 182, 182, 183, 183, 184, 184, 184, 185, 185, 185, 185, 185, 186, 73, 73, 74, 74, 74, 75, 75, 76, 76, 77, 77, 78, 79, 80, 80, 81, 83, 84, 85, 87, 89, 91, 93, 96, 99, 102, 106, 111, 116, 122, 128, 133, 139, 144, 149, 153, 156, 159, 162, 164, 166, 168, 170, 171, 172, 174, 175, 175, 176, 177, 178, 178, 179, 179, 180, 180, 181, 181, 181, 182, 77, 77, 78, 78, 79, 79, 80, 80, 81, 82, 83, 83, 84, 85, 86, 88, 89, 90, 92, 94, 96, 98, 100, 103, 106, 109, 112, 116, 119, 123, 128, 132, 136, 139, 143, 146, 149, 152, 155, 157, 159, 161, 163, 165, 166, 167, 169, 170, 171, 172, 172, 173, 174, 175, 175, 176, 176, 177, 177, 178, 80, 81, 81, 82, 83, 83, 84, 85, 85, 86, 87, 88, 89, 90, 91, 93, 94, 96, 97, 99, 101, 103, 105, 107, 110, 113, 115, 118, 121, 124, 128, 131, 134, 137, 140, 142, 145, 148, 150, 152, 154, 156, 158, 159, 161, 162, 164, 165, 166, 167, 168, 169, 170, 170, 171, 172, 172, 173, 174, 174 };
byte radii[TOTAL_LEDS] = { 255, 248, 241, 234, 227, 221, 214, 207, 201, 194, 188, 182, 176, 170, 164, 158, 153, 147, 142, 137, 133, 128, 124, 121, 117, 115, 112, 110, 109, 108, 108, 108, 109, 110, 112, 115, 117, 121, 124, 128, 133, 137, 142, 147, 153, 158, 164, 170, 176, 182, 188, 194, 201, 207, 214, 221, 227, 234, 241, 248, 246, 239, 232, 225, 217, 210, 203, 196, 189, 183, 176, 169, 162, 156, 150, 143, 137, 131, 125, 120, 115, 109, 105, 100, 97, 93, 90, 88, 86, 85, 85, 85, 86, 88, 90, 93, 97, 100, 105, 109, 115, 120, 125, 131, 137, 143, 150, 156, 162, 169, 176, 183, 189, 196, 203, 210, 217, 225, 232, 239, 239, 232, 224, 217, 210, 202, 195, 188, 180, 173, 166, 159, 152, 145, 138, 131, 124, 118, 111, 105, 99, 93, 87, 82, 77, 73, 69, 66, 64, 62, 62, 62, 64, 66, 69, 73, 77, 82, 87, 93, 99, 105, 111, 118, 124, 131, 138, 145, 152, 159, 166, 173, 180, 188, 195, 202, 210, 217, 224, 232, 234, 227, 219, 212, 204, 196, 189, 181, 174, 166, 159, 151, 144, 136, 129, 122, 115, 107, 100, 93, 86, 79, 73, 66, 60, 54, 49, 45, 41, 39, 39, 39, 41, 45, 49, 54, 60, 66, 73, 79, 86, 93, 100, 107, 115, 122, 129, 136, 144, 151, 159, 166, 174, 181, 189, 196, 204, 212, 219, 227, 232, 224, 216, 209, 201, 193, 186, 178, 170, 162, 155, 147, 139, 132, 124, 117, 109, 101, 94, 86, 79, 71, 64, 56, 49, 41, 34, 28, 22, 17, 15, 17, 22, 28, 34, 41, 49, 56, 64, 71, 79, 86, 94, 101, 109, 117, 124, 132, 139, 147, 155, 162, 170, 178, 186, 193, 201, 209, 216, 224, 231, 224, 216, 208, 200, 193, 185, 177, 170, 162, 154, 147, 139, 131, 123, 116, 108, 100, 93, 85, 77, 70, 62, 54, 47, 39, 32, 24, 17, 11, 8, 11, 17, 24, 32, 39, 47, 54, 62, 70, 77, 85, 93, 100, 108, 116, 123, 131, 139, 147, 154, 162, 170, 177, 185, 193, 200, 208, 216, 224, 233, 225, 218, 210, 203, 195, 187, 180, 172, 165, 157, 150, 142, 135, 127, 120, 112, 105, 97, 90, 83, 76, 69, 62, 56, 49, 44, 39, 34, 32, 31, 32, 34, 39, 44, 49, 56, 62, 69, 76, 83, 90, 97, 105, 112, 120, 127, 135, 142, 150, 157, 165, 172, 180, 187, 195, 203, 210, 218, 225, 237, 230, 222, 215, 207, 200, 193, 185, 178, 171, 163, 156, 149, 142, 135, 127, 121, 114, 107, 100, 94, 88, 82, 76, 71, 66, 62, 59, 56, 54, 54, 54, 56, 59, 62, 66, 71, 76, 82, 88, 94, 100, 107, 114, 121, 127, 135, 142, 149, 156, 163, 171, 178, 185, 193, 200, 207, 215, 222, 230, 244, 236, 229, 222, 215, 207, 200, 193, 186, 179, 172, 165, 159, 152, 145, 139, 133, 126, 120, 115, 109, 104, 99, 94, 90, 86, 83, 80, 79, 77, 77, 77, 79, 80, 83, 86, 90, 94, 99, 104, 109, 115, 120, 126, 133, 139, 145, 152, 159, 165, 172, 179, 186, 193, 200, 207, 215, 222, 229, 236, 252, 245, 238, 231, 224, 217, 210, 203, 197, 190, 184, 177, 171, 165, 159, 153, 147, 142, 136, 131, 126, 122, 118, 114, 110, 107, 105, 103, 101, 100, 100, 100, 101, 103, 105, 107, 110, 114, 118, 122, 126, 131, 136, 142, 147, 153, 159, 165, 171, 177, 184, 190, 197, 203, 210, 217, 224, 231, 238, 245 };

void fill_all_strips(CRGB color, int numToFill=NUM_LEDS){
    for(uint8_t s=0; s<NUM_STRIPS; s++){
        fill_solid(leds[s], numToFill, color);
    }
}

void fadeAllToBlackBy(uint8_t fadeBy){
    for(uint8_t s=0; s<NUM_STRIPS; s++){
        fadeToBlackBy(leds[s], NUM_LEDS, fadeBy);
    }
}

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount){
  if( cur == target) return;
  
  if( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}

void fadeTowardColorBy(CRGB* leds, uint8_t num_leds, CRGB target, uint8_t fadeBy){
    for(uint8_t i=0; i<num_leds;i++){
        nblendU8TowardU8( leds[i].red,   target.red,   fadeBy);
        nblendU8TowardU8( leds[i].green, target.green, fadeBy);
        nblendU8TowardU8( leds[i].blue,  target.blue,  fadeBy);
    }
}

void fadeAllTowardColorBy(const CRGB target, uint8_t fadeBy){
    for(uint8_t s=0; s<NUM_STRIPS; s++){
        fadeTowardColorBy(leds[s], NUM_LEDS, target, fadeBy);
    }
}

CRGB applyBrightnessToRGB(CRGB color, uint8_t brightness){
    return color.nscale8(brightness);

    if( brightness != 255) {
        if( brightness ) {
            ++brightness; // adjust for rounding
            // Now, since brightness is nonzero, we don't need the full scale8_video logic;
            // we can just to scale8 and then add one (unless scale8 fixed) to all nonzero inputs.
            if( color.red )   {
                color.red = scale8_LEAVING_R1_DIRTY( color.red, brightness);
            #if !(FASTLED_SCALE8_FIXED==1)
                            ++red1;
            #endif
            }
            if( color.green ) {
                color.green = scale8_LEAVING_R1_DIRTY( color.green, brightness);
            #if !(FASTLED_SCALE8_FIXED==1)
                            ++green1;
            #endif
            }
            if( color.blue )  {
                color.blue = scale8_LEAVING_R1_DIRTY( color.blue, brightness);
            #if !(FASTLED_SCALE8_FIXED==1)
                            ++blue1;
            #endif
            }
            cleanup_R1();
        } else {
            color.red = 0;
            color.green = 0;
            color.blue = 0;
        }
    }
    
    return color;
}

int coordinateToFlattenedLed(uint8_t stripIdx, uint8_t ledIdx){
    return (stripIdx*NUM_LEDS) + ledIdx;
}

uint8_t stripFromFlattenLed(int flattenedIdx){
    return flattenedIdx/NUM_LEDS;
}

uint8_t ledFromFlattenLed(int flattenedIdx){
    return flattenedIdx%NUM_LEDS;
}

CRGB FlattenedToCoordinateLed(int flattenedIdx){
    return leds[flattenedIdx/NUM_LEDS][flattenedIdx%NUM_LEDS];
}

#endif