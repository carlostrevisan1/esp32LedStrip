/*
    EasyOTA a library for easy implementation of OTA Updates on projects.
    Created by Carlos Trevisan, May 20, 2021.
    Released into the public domain.
*/
#ifndef EasyOTA_h
#define EasyOTA_h

#include "Arduino.h"
#include <ArduinoOTA.h>

class EasyOTA{
    public:
        EasyOTA();
        void beginSetup(int port, const char *password);
        void handle();
    private:
        void StartingUpdate();
        void EndingUpdate();
        void Updating();

};





#endif