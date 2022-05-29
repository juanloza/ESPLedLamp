#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <ESPAsyncWebServer.h>
#include "config.h"

AsyncWebServer server = AsyncWebServer(80);

const char* p_enabled = "enabled";
const char* p_mode = "mode";
const char* p_fire_cooling = "cooling";
const char* p_fire_sparking = "sparking";
const char* p_fire_palette = "palette";

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

void getConfigHanlder(AsyncWebServerRequest *request){
    request->send(200, "application/json", getJsonConfig());
}

void turnOnOffHandler(AsyncWebServerRequest *request){
    if (!request->hasParam(p_enabled)) {
        request->send(400, "text/plain", "Bad request: mandatory enabled param not sent");
        return;
    }
    bool new_enabled = (bool)request->getParam(p_mode)->value().toInt();
    if(new_enabled!=enabled){
        hasChanges = true;
        enabled = new_enabled;
    }
    request->send(200, "text/plain", new_enabled?"1":"0");
}

void setFireModeConfig(AsyncWebServerRequest *request){
    fireConfig.cooling=request->getParam(p_fire_cooling)->value().toInt();
    fireConfig.sparking=request->getParam(p_fire_sparking)->value().toInt();
    fireConfig.paletteIndex=request->getParam(p_fire_palette)->value().toInt();
    fireConfig.palette = firePaletteList[fireConfig.paletteIndex];
}

void setModeConfigHandler(AsyncWebServerRequest *request){
    if (!request->hasParam(p_mode)) {
        request->send(400, "text/plain", "Bad request: mandatory mode param not sent");
        return;
    }

    int i_mode = std::stoi(request->getParam(p_mode)->value().c_str());
    mode = static_cast<TypeMode>(i_mode);
    String modoTexto;
    switch (mode)
    {
    case TypeMode::FIRE:
        setFireModeConfig(request);
        modoTexto = "Fuego";
        break;
    case TypeMode::PLAIN :
        modoTexto = "Color plano";
        break;
    case TypeMode::BEATING:
        modoTexto = "Beating";
        break;
    case TypeMode::RGBLOOP:
        modoTexto = "RGB Loop";
        break;
    case TypeMode::STROBE:
        modoTexto = "Strobe";
        break;
    case TypeMode::FADEINOUT:
        modoTexto = "Fade InOut";
        break;
    case TypeMode::EYES:
        modoTexto = "Eyes";
        break;
    case TypeMode::CYLONBOUNCE:
        modoTexto = "Cyclon bounce";
        break;
    case TypeMode::NEWKITT:
        modoTexto = "New KITT";
        break;
    case TypeMode::TWINKLE:
        modoTexto = "Twinkle";
        break;
    case TypeMode::TWINKLERANDOM:
        modoTexto = "Twinkle Random";
        break;
    case TypeMode::SPARKLE:
        modoTexto = "Sparkle";
        break;
    case TypeMode::SNOWSPARKLE:
        modoTexto = "Strobe";
        break;
    case TypeMode::RUNNINGLIGHTS:
        modoTexto = "Strobe";
        break;
    case TypeMode::COLORWIPE:
        modoTexto = "Strobe";
        break;
    case TypeMode::RAINBOWCYCLE:
        modoTexto = "Strobe";
        break;
    
    default:
        break;
    }
    request->send(200, "application/json", modoTexto);
    //request->send(200, "application/json", getJsonConfig());
}

void addServerHandlers(){
    server.onNotFound(notFoundHandler);
    server.on("/ping", HTTP_GET, pingHanlder);
    server.on("/getConfig", HTTP_GET,  getConfigHanlder);
    server.on("/turnOnOff", HTTP_GET, turnOnOffHandler);
    server.on("/setModeConfig", HTTP_ANY,  setModeConfigHandler);

    server.begin();
}

#endif