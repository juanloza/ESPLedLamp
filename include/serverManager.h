#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <ESPAsyncWebServer.h>
#include "config.h"

AsyncWebServer server = AsyncWebServer(80);

const char* p_param = "param";
const char* p_value = "value";
const char* p_enabled = "enabled";
const char* p_mode = "mode";
const char* p_cooling = "cooling";
const char* p_sparking = "sparking";
const char* p_palette = "palette";
const char* p_brightness = "brightness";
const char* p_bgBrightness = "bgbrightness";
const char* p_color = "color";
const char* p_bgColor = "bgcolor";
const char* p_numLeds = "numleds";
const char* p_size = "size";
const char* p_new_probability = "newprobability";
const char* p_random_decay = "randomdecay";
const char* p_decay_probability = "decayprobability";
const char* p_decay = "decay";
const char* p_max_total = "maxtotal";
const char* p_max_strip = "maxstrip";
const char* p_speed = "speed";
const char* p_fadeStar = "fadeStar";
const char* p_star_probability = "starprobability";
const char* p_fall_stars = "fallstars";
const char* p_gravity = "gravity";
const char* p_reverse = "reverse";
const char* p_scale = "scale";
const char* p_step = "step";
const char* p_strip_offset = "stripoffset";

///Connects to wifi with config SSID and password
bool connectToWIFI(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return false;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    return true;
}

void apiNotFoundHandler(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void apiPingHanlder(AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK");
}

///Returns json response with all config params
void apiGetAllConfigHanlder(AsyncWebServerRequest *request){
    request->send(200, "application/json", getJsonConfig());
}

///Returns json response with all common params and only current mode options
void apiGetModeConfigHanlder(AsyncWebServerRequest *request){
    request->send(200, "application/json", getJsonConfig(true));
}

///gets enabled config from request and set into config options
///@param request Incoming request
///@param singleParam True if endpoint is setSingleParam, false otherwise
void handleEnabledConfig(AsyncWebServerRequest *request, bool singleParam){
    bool new_enabled;
    if(singleParam){
        if(request->getParam(p_param)->value()!=p_enabled){
            return; //Its single param but no for enabled option
        }
        new_enabled = (bool)request->getParam(p_value)->value().toInt();
    }else{
        new_enabled = (bool)request->getParam(p_enabled)->value().toInt();
    }
    if(new_enabled!=enabled){
        enabled = new_enabled;
    }
}

///gets mode config from request and set into config options
///@param request Incoming request
///@param singleParam True if endpoint is setSingleParam, false otherwise
void handleModeConfig(AsyncWebServerRequest *request, bool singleParam){
    uint8_t i_new_mode;    
    if(singleParam){
        if(request->getParam(p_param)->value()!=p_mode){
            return; //Its single param but no for mode option
        }
        i_new_mode = (uint8_t)request->getParam(p_value)->value().toInt();
    }else{
        i_new_mode = (uint8_t)request->getParam(p_mode)->value().toInt();
    }
    TypeMode new_mode = static_cast<TypeMode>(i_new_mode);
    if(new_mode!=mode){
        modeHasChanged = true;
        mode = new_mode;
    }
}

///gets all plain mode config from request and set into config options
///if its called from setSingleParam endpoint handler, it only gets given parameter
///@param request Incoming request
///@param param param name if comes from setSingleParam, empty otherwise
///@param value param value if comes from setSingleParam, empty otherwise
void handlePlainModeConfig(AsyncWebServerRequest *request, String param=""){
    if(param==p_color || request->hasParam(p_color)){
        uint32_t colorInt = request->getParam(param!=""?p_value:p_color)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        plainConfig.color = CRGB(colorInt);
        if(param==p_color){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        plainConfig.brightness=request->getParam(param!=""?p_value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }
    if(param==p_numLeds || request->hasParam(p_numLeds)){
        plainConfig.numLeds=request->getParam(param!=""?p_value:p_numLeds)->value().toInt();
        if(param==p_numLeds){
            return;
        }
    }
}

void handlePaletteModeConfig(AsyncWebServerRequest *request, String param=""){
    if(param==p_palette || request->hasParam(p_palette)){
        paletteConfig.paletteIndex=request->getParam(param!=""?p_value:p_palette)->value().toInt();
        paletteConfig.palette = SelectCometPalette(paletteConfig.paletteIndex);
        if(param==p_palette){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        paletteConfig.brightness=request->getParam(param!=""?p_value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }
    if(param==p_reverse || request->hasParam(p_reverse)){
        paletteConfig.reverse=(bool)request->getParam(param!=""?p_value:p_reverse)->value().toInt();
        if(param==p_reverse){
            return;
        }
    }
    if(param==p_scale || request->hasParam(p_scale)){
        paletteConfig.scale=request->getParam(param!=""?p_value:p_scale)->value().toInt();
        if(param==p_scale){
            return;
        }
    }
    if(param==p_speed || request->hasParam(p_speed)){
        paletteConfig.speed=request->getParam(param!=""?p_value:p_speed)->value().toInt();
        if(param==p_speed){
            return;
        }
    }
    if(param==p_step || request->hasParam(p_step)){
        paletteConfig.step=request->getParam(param!=""?p_value:p_step)->value().toInt();
        if(param==p_step){
            return;
        }
    }
    if(param==p_strip_offset || request->hasParam(p_strip_offset)){
        paletteConfig.stripOffset=request->getParam(param!=""?p_value:p_strip_offset)->value().toInt();
        if(param==p_strip_offset){
            return;
        }
    }
}

///gets all fire mode config from request and set into config options
///if its called from setSingleParam endpoint handler, it only gets given parameter
///@param request Incoming request
///@param param param name if comes from setSingleParam, empty otherwise
///@param value param value if comes from setSingleParam, empty otherwise
void handleFireModeConfig(AsyncWebServerRequest *request, String param=""){
    if(param==p_cooling || request->hasParam(p_cooling)){
        fireConfig.cooling=request->getParam(param!=""?p_value:p_cooling)->value().toInt();
        if(param==p_cooling){
            return;
        }
    }
    if(param==p_sparking || request->hasParam(p_sparking)){
        fireConfig.sparking=request->getParam(param!=""?p_value:p_sparking)->value().toInt();
        if(param==p_sparking){
            return;
        }
    }
    if(param==p_palette || request->hasParam(p_palette)){
        fireConfig.paletteIndex=request->getParam(param!=""?p_value:p_palette)->value().toInt();
        fireConfig.palette = SelectFirePalette(fireConfig.paletteIndex);
        if(param==p_palette){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        fireConfig.brightness=request->getParam(param!=""?p_value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }
        
}

void handleCometModeConfig(AsyncWebServerRequest *request, String param=""){
    if(param==p_bgColor || request->hasParam(p_bgColor)){
        uint32_t colorInt = request->getParam(param!=""?p_value:p_bgColor)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        cometConfig.bgColor = CRGB(colorInt);
        if(param==p_bgColor){
            return;
        }
    }
    if(param==p_bgBrightness || request->hasParam(p_bgBrightness)){
        cometConfig.bgBrightness=request->getParam(param!=""?p_value:p_bgBrightness)->value().toInt();
        if(param==p_bgBrightness){
            return;
        }
    }
    if(param==p_color || request->hasParam(p_color)){
        uint32_t colorInt = request->getParam(param!=""?p_value:p_color)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        cometConfig.color = CRGB(colorInt);
        if(param==p_color){
            return;
        }
    }
    if(param==p_palette || request->hasParam(p_palette)){
        cometConfig.paletteIndex=request->getParam(param!=""?p_value:p_palette)->value().toInt();
        cometConfig.palette = SelectCometPalette(cometConfig.paletteIndex);
        if(param==p_palette){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        cometConfig.brightness=request->getParam(param!=""?p_value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }
    if(param==p_size || request->hasParam(p_size)){
        cometConfig.size=request->getParam(param!=""?p_value:p_size)->value().toInt();
        if(param==p_size){
            return;
        }
    }

    if(param==p_new_probability || request->hasParam(p_new_probability)){
        cometConfig.randomNewComet=request->getParam(param!=""?p_value:p_new_probability)->value().toInt();
        if(param==p_new_probability){
            return;
        }
    }

    if(param==p_random_decay || request->hasParam(p_random_decay)){
        cometConfig.randomDecay=(bool)request->getParam(param!=""?p_value:p_random_decay)->value().toInt();
        if(param==p_random_decay){
            return;
        }
    }

    if(cometConfig.randomDecay){
        if(param==p_decay_probability || request->hasParam(p_decay_probability)){
            cometConfig.decayProbability=request->getParam(param!=""?p_value:p_decay_probability)->value().toInt();
            if(param==p_decay_probability){
                return;
            }
        }
    }

    if(cometConfig.randomNewComet){
        if(param==p_new_probability || request->hasParam(p_new_probability)){
            cometConfig.randomNewComet=request->getParam(param!=""?p_value:p_new_probability)->value().toInt();
            if(param==p_new_probability){
                return;
            }
        }
    }

    if(param==p_decay || request->hasParam(p_decay)){
        cometConfig.trailDecay=request->getParam(param!=""?p_value:p_decay)->value().toInt();
        if(param==p_decay){
            return;
        }
    }

    if(param==p_max_total || request->hasParam(p_max_total)){
        cometConfig.maxTotalComets=request->getParam(param!=""?p_value:p_max_total)->value().toInt();
        if(param==p_max_total){
            return;
        }
    }

    if(param==p_max_strip || request->hasParam(p_max_strip)){
        cometConfig.maxStripComets=request->getParam(param!=""?p_value:p_max_strip)->value().toInt();
        if(param==p_max_strip){
            return;
        }
    }

    if(param==p_speed || request->hasParam(p_speed)){
        cometConfig.speed=request->getParam(param!=""?p_value:p_speed)->value().toInt();
        if(param==p_speed){
            return;
        }
    }
}

void handleStarSparkleModeConfig(AsyncWebServerRequest *request, String param=""){
    if(param==p_bgColor || request->hasParam(p_bgColor)){
        uint32_t colorInt = request->getParam(param!=""?p_value:p_bgColor)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        starSparkleConfig.bgColor = CRGB(colorInt);
        if(param==p_bgColor){
            return;
        }
    }
    if(param==p_bgBrightness || request->hasParam(p_bgBrightness)){
        starSparkleConfig.bgBrightness=request->getParam(param!=""?p_value:p_bgBrightness)->value().toInt();
        if(param==p_bgBrightness){
            return;
        }
    }
    if(param==p_color || request->hasParam(p_color)){
        uint32_t colorInt = request->getParam(param!=""?p_value:p_color)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        starSparkleConfig.color = CRGB(colorInt);
        if(param==p_color){
            return;
        }
    }
    if(param==p_palette || request->hasParam(p_palette)){
        starSparkleConfig.paletteIndex=request->getParam(param!=""?p_value:p_palette)->value().toInt();
        starSparkleConfig.palette = SelectCometPalette(starSparkleConfig.paletteIndex);
        if(param==p_palette){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        starSparkleConfig.starBrightness=request->getParam(param!=""?p_value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }
    if(param==p_fadeStar || request->hasParam(p_fadeStar)){
        starSparkleConfig.fadeStar=request->getParam(param!=""?p_value:p_fadeStar)->value().toInt();
        if(param==p_fadeStar){
            return;
        }
    }
    if(param==p_star_probability || request->hasParam(p_star_probability)){
        starSparkleConfig.starProbability=request->getParam(param!=""?p_value:p_star_probability)->value().toInt();
        if(param==p_star_probability){
            return;
        }
    }
    if(param==p_fall_stars || request->hasParam(p_fall_stars)){
        starSparkleConfig.fallStars=(bool)request->getParam(param!=""?p_value:p_fall_stars)->value().toInt();
        if(param==p_fall_stars){
            return;
        }
    }
    if(param==p_speed || request->hasParam(p_speed)){
        starSparkleConfig.fallingSpeed=request->getParam(param!=""?p_value:p_speed)->value().toInt();
        if(param==p_speed){
            return;
        }
    }
}

void handleBouncingBallsModeConfig(AsyncWebServerRequest *request, String param=""){
    if(param==p_bgColor || request->hasParam(p_bgColor)){
        uint32_t colorInt = request->getParam(param!=""?p_value:p_bgColor)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        ballsConfig.bgColor = CRGB(colorInt);
        if(param==p_bgColor){
            return;
        }
    }
    if(param==p_bgBrightness || request->hasParam(p_bgBrightness)){
        ballsConfig.bgBrightness=request->getParam(param!=""?p_value:p_bgBrightness)->value().toInt();
        if(param==p_bgBrightness){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        ballsConfig.brightness=request->getParam(param!=""?p_value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }

    if(param==p_palette || request->hasParam(p_palette)){
        ballsConfig.paletteIndex=request->getParam(param!=""?p_value:p_palette)->value().toInt();
        ballsConfig.palette = SelectCometPalette(ballsConfig.paletteIndex);
        if(param==p_palette){
            return;
        }
    }

    if(param==p_gravity || request->hasParam(p_gravity)){
        int tmpGravity=request->getParam(param!=""?p_value:p_gravity)->value().toInt();
        ballsConfig.gravity = tmpGravity*-0.1f;
        if(param==p_gravity){
            return;
        }
    }
    
    if(param==p_new_probability || request->hasParam(p_new_probability)){
        ballsConfig.randomNewBall=request->getParam(param!=""?p_value:p_new_probability)->value().toInt();
        if(param==p_new_probability){
            return;
        }
    }

    if(param==p_max_total || request->hasParam(p_max_total)){
        ballsConfig.maxTotalBalls=request->getParam(param!=""?p_value:p_max_total)->value().toInt();
        if(param==p_max_total){
            return;
        }
    }

    if(param==p_max_strip || request->hasParam(p_max_strip)){
        ballsConfig.maxStripBalls=request->getParam(param!=""?p_value:p_max_strip)->value().toInt();
        if(param==p_max_strip){
            return;
        }
    }
}

///endpoint handler for setSingleParam
///if param is one from specific mode config, it will get it only for current mode
///@param request Incoming request
void apiSetSingleParamHandler(AsyncWebServerRequest *request){
    if (!request->hasParam(p_param)) {
        request->send(400, "text/plain", "Bad request: mandatory param \"param\" not sent");
        return;
    }
    if (!request->hasParam(p_value)) {
        request->send(400, "text/plain", "Bad request: mandatory param \"value\" not sent");
        return;
    }
    String param = request->getParam(p_param)->value();
    String value = request->getParam(p_value)->value();

    if(param == p_enabled){
        handleEnabledConfig(request, true);
        request->send(200, "text/plain", "OK");
        return;
    }
    if(param == p_mode){
        handleModeConfig(request, true);
        request->send(200, "text/plain", "OK");
        return;
    }
    
    switch (mode)
    {
    case TypeMode::FIRE:
        handleFireModeConfig(request, param);
        break;
    case TypeMode::PLAIN :
        handlePlainModeConfig(request, param);
        break;
    case TypeMode::DRAWPALETTE:
        handlePaletteModeConfig(request, param);
    case TypeMode::COMET:
        handleCometModeConfig(request, param);
        break;
    case TypeMode::STARSPARKLE:
        handleStarSparkleModeConfig(request, param);
        break;
    case TypeMode::BOUNCINGBALLS:
        handleBouncingBallsModeConfig(request, param);
        break;
    default:
        break;
    }
    
    request->send(200, "text/plain", "OK");
}

///endpoint handler for setModeConfig
///gets all common config + current mode config from request and set into config options
///@param request Incoming request
void apiSetModeConfigHandler(AsyncWebServerRequest *request){
    if (!request->hasParam(p_enabled,false,false)) {
        request->send(400, "text/plain", "Bad request: mandatory param \"enabled\" not sent");
        return;
    }
    if (!request->hasParam(p_mode,false,false)) {
        request->send(400, "text/plain", "Bad request: mandatory param \"mode\" not sent");
        return;
    }
    
    handleEnabledConfig(request, false);
    handleModeConfig(request, false);
    
    switch (mode)
    {
    case TypeMode::TEST :
        break;
    case TypeMode::PLAIN:
        handlePlainModeConfig(request);
        break;
    case TypeMode::DRAWPALETTE:
        handlePaletteModeConfig(request);
        break;
    case TypeMode::FIRE:
        handleFireModeConfig(request);
        break;
    case TypeMode::COMET:
        handleCometModeConfig(request);
        break;
    case TypeMode::STARSPARKLE:
        handleStarSparkleModeConfig(request);
        break;    
    case TypeMode::BOUNCINGBALLS:
        handleBouncingBallsModeConfig(request);
        break;
    default:
        break;
    }

    request->send(200, "text/plain", "OK");
    //request->send(200, "application/json", getJsonConfig());
}

///Set all endpoints and its handler functions
void addServerHandlers(){
    server.onNotFound(apiNotFoundHandler);
    server.on("/ping", HTTP_GET, apiPingHanlder);
    server.on("/getAllConfig", HTTP_GET,  apiGetAllConfigHanlder);
    server.on("/getModeConfig", HTTP_GET,  apiGetModeConfigHanlder);
    server.on("/setSingleParam", HTTP_GET, apiSetSingleParamHandler);
    server.on("/setModeConfig", HTTP_GET,  apiSetModeConfigHandler);

    server.begin();
}

#endif