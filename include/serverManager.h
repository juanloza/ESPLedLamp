#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <ESPAsyncWebServer.h>
#include "config.h"

AsyncWebServer server = AsyncWebServer(80);

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

void addServerHandlers(){
    server.onNotFound(notFoundHandler);
    server.on("/ping", HTTP_GET, pingHanlder);
    server.on("/getConfig", HTTP_GET,  getConfigHanlder);

    server.begin();
}

#endif