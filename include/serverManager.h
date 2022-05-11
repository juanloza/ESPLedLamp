#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <ESPAsyncWebServer.h>
#include "config.h"

AsyncWebServer server = AsyncWebServer(80);

const char* p_mode = "mode";

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

void setModeHandler(AsyncWebServerRequest *request){
    if (!request->hasParam(p_mode)) {
        request->send(400, "text/plain", "Bad request: mandatory mode not sent");
        return;
    }

    int i_mode = std::stoi(request->getParam(p_mode)->value().c_str());
    mode = static_cast<TypeMode>(i_mode);
    String modoTexto;
    switch (mode)
    {
    case TypeMode::FIRE:
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
    server.on("/setMode", HTTP_ANY,  setModeHandler);

    server.begin();
}

#endif