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

bool connectToWIFI(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return false;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void notFoundHandler(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void pingHanlder(AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK");
}

void getAllConfigHanlder(AsyncWebServerRequest *request){
    request->send(200, "application/json", getJsonConfig());
}
void getModeConfigHanlder(AsyncWebServerRequest *request){
    request->send(200, "application/json", getJsonConfig(true));
}

void setEnabledConfig(AsyncWebServerRequest *request, bool singleParam){
    bool new_enabled;
    if(singleParam){
        new_enabled = (bool)request->getParam(p_value)->value().toInt();
    }else{
        new_enabled = (bool)request->getParam(p_enabled)->value().toInt();
    }
    if(new_enabled!=enabled){
        hasChanges = true;
        enabled = new_enabled;
    }
}

void setPlainModeConfig(AsyncWebServerRequest *request, String param="", String value=""){
    if(param==p_color || request->hasParam(p_color)){
        uint32_t colorInt = request->getParam(param!=""?value:p_color)->value().toInt();
        //remove alpha
        colorInt-=0xFF000000;
        plainConfig.color = CRGB(colorInt);
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        plainConfig.brightness=request->getParam(param!=""?value:p_brightness)->value().toInt();
    }
    if(param==p_numLeds || request->hasParam(p_numLeds)){
        plainConfig.numLeds=request->getParam(param!=""?value:p_numLeds)->value().toInt();
    }
}

void setFireModeConfig(AsyncWebServerRequest *request, String param="", String value=""){
    if(param==p_cooling || request->hasParam(p_cooling)){
        fireConfig.cooling=request->getParam(param!=""?value:p_cooling)->value().toInt();
    }
    if(param==p_sparking || request->hasParam(p_sparking)){
        
        fireConfig.sparking=request->getParam(param!=""?value:p_sparking)->value().toInt();
    }
    if(param==p_palette || request->hasParam(p_palette)){
        fireConfig.paletteIndex=request->getParam(param!=""?value:p_palette)->value().toInt();
        fireConfig.palette = SelectPalette(fireConfig.paletteIndex);
    }
    if(param==p_brightness || request->hasParam(p_brightness)){
        fireConfig.brightness=request->getParam(param!=""?value:p_brightness)->value().toInt();
    }
        
}

void setSingleParamHandler(AsyncWebServerRequest *request){
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

    setEnabledConfig(request, true);
    
    switch (mode)
    {
    case TypeMode::FIRE:
        setFireModeConfig(request, param, value);
        break;
    case TypeMode::PLAIN :
        setPlainModeConfig(request, param, value);
        break;
    
    default:
        break;
    }
    
    request->send(200, "text/plain", "OK");
}

void setModeConfigHandler(AsyncWebServerRequest *request){
    if (!request->hasParam(p_enabled,false,false)) {
        request->send(400, "text/plain", "Bad request: mandatory param \"enabled\" not sent");
        return;
    }
    if (!request->hasParam(p_mode,false,false)) {
        request->send(400, "text/plain", "Bad request: mandatory param \"mode\" not sent");
        return;
    }
    
    setEnabledConfig(request, false);

    int i_mode = request->getParam(p_mode)->value().toInt();
    mode = static_cast<TypeMode>(i_mode);
    String modoTexto;
    switch (mode)
    {
    case TypeMode::TEST :
        break;
    case TypeMode::PLAIN:
        setPlainModeConfig(request);
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

void addServerHandlers(){
    server.onNotFound(notFoundHandler);
    server.on("/ping", HTTP_GET, pingHanlder);
    server.on("/getAllConfig", HTTP_GET,  getAllConfigHanlder);
    server.on("/getModeConfig", HTTP_GET,  getModeConfigHanlder);
    server.on("/setSingleParam", HTTP_GET, setSingleParamHandler);
    server.on("/setModeConfig", HTTP_GET,  setModeConfigHandler);

    server.begin();
}

#endif