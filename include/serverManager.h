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
const char* p_color = "color";
const char* p_numLeds = "numleds";

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
        hasChanges = true;
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
        i_new_mode = (bool)request->getParam(p_value)->value().toInt();
    }else{
        i_new_mode = (bool)request->getParam(p_mode)->value().toInt();
    }
   TypeMode new_mode = static_cast<TypeMode>(i_new_mode);

    if(new_mode!=mode){
        hasChanges = true;
        modeHasChanged = true;
        mode = new_mode;
    }
}

///gets all plain mode config from request and set into config options
///if its called from setSingleParam endpoint handler, it only gets given parameter
///@param request Incoming request
///@param param param name if comes from setSingleParam, empty otherwise
///@param value param value if comes from setSingleParam, empty otherwise
void handlePlainModeConfig(AsyncWebServerRequest *request, String param="", String value=""){
    if(param==p_color || request->hasParam(p_color)){
        uint32_t colorInt = request->getParam(param!=""?value:p_color)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        plainConfig.color = CRGB(colorInt);
        if(param==p_color){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        plainConfig.brightness=request->getParam(param!=""?value:p_brightness)->value().toInt();
        if(param==p_brightness){
            return;
        }
    }
    if(param==p_numLeds || request->hasParam(p_numLeds)){
        plainConfig.numLeds=request->getParam(param!=""?value:p_numLeds)->value().toInt();
        if(param==p_numLeds){
            return;
        }
    }
}

///gets all fire mode config from request and set into config options
///if its called from setSingleParam endpoint handler, it only gets given parameter
///@param request Incoming request
///@param param param name if comes from setSingleParam, empty otherwise
///@param value param value if comes from setSingleParam, empty otherwise
void setFireModeConfig(AsyncWebServerRequest *request, String param="", String value=""){
    if(param==p_cooling || request->hasParam(p_cooling)){
        fireConfig.cooling=request->getParam(param!=""?value:p_cooling)->value().toInt();
        if(param==p_cooling){
            return;
        }
    }
    if(param==p_sparking || request->hasParam(p_sparking)){
        fireConfig.sparking=request->getParam(param!=""?value:p_sparking)->value().toInt();
        if(param==p_sparking){
            return;
        }
    }
    if(param==p_palette || request->hasParam(p_palette)){
        fireConfig.paletteIndex=request->getParam(param!=""?value:p_palette)->value().toInt();
        fireConfig.palette = SelectPalette(fireConfig.paletteIndex);
        if(param==p_palette){
            return;
        }
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        fireConfig.brightness=request->getParam(param!=""?value:p_brightness)->value().toInt();
        if(param==p_brightness){
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
        setFireModeConfig(request, param, value);
        break;
    case TypeMode::PLAIN :
        handlePlainModeConfig(request, param, value);
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
    case TypeMode::FIRE:
        setFireModeConfig(request);
        break;
    case TypeMode::BEATING:
        break;
    case TypeMode::RGBLOOP:
        break;
    case TypeMode::STROBE:
        break;
    case TypeMode::FADEINOUT:
        break;
    case TypeMode::EYES:
        break;
    case TypeMode::CYLONBOUNCE:
        break;
    case TypeMode::NEWKITT:
        break;
    case TypeMode::TWINKLE:
        break;
    case TypeMode::TWINKLERANDOM:
        break;
    case TypeMode::SPARKLE:
        break;
    case TypeMode::SNOWSPARKLE:
        break;
    case TypeMode::RUNNINGLIGHTS:
        break;
    case TypeMode::COLORWIPE:
        break;
    case TypeMode::RAINBOWCYCLE:
        break;
    
    default:
        break;
    }
    hasChanges = true;
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