/*
    EasyOTA a library for easy implementation of OTA Updates on projects.
    Created by Carlos Trevisan, May 20, 2021.
    Released into the public domain.
*/
#include "Arduino.h"
#include <ArduinoOTA.h>
#include "EasyOTA.h"

void EasyOTA::StartingUpdate(){
    ArduinoOTA.onStart([]() {
        Serial.println("Starting");
        delay(10);
    });
}

void EasyOTA::EndingUpdate(){
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd updating");
        delay(1500);
    });
}

void EasyOTA::Updating(){
    ArduinoOTA.onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else 
                type = "filesystem";
            Serial.println("Start updating " + type);
            })
        .onEnd([]() {
            Serial.println("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR)
                Serial.println("End Failed");
        });
    ArduinoOTA.begin();
}

/**
    Handle OTA actions, needs to be inserted on loop(), otherwise wont work.
*/
void EasyOTA::handle(){
    ArduinoOTA.handle();
}

/**
    Setup OTA service parameters and callbacks, included on device setup().

    @param port configured port on device.
    @param password password to configured ota on device.
*/
void EasyOTA::beginSetup(int port, const char *password){
    ArduinoOTA.setPort(port); // Port defaults to 3232
    ArduinoOTA.setPassword(password);
    StartingUpdate();
    EndingUpdate();
    Updating();
}
EasyOTA::EasyOTA(){
    
}
