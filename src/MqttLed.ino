#include <Arduino.h>
#include <WiFi.h>
#include <EasyOTA.h>
#include "time.h"
#include <FastLED.h>
#include <PubSubClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include <effects.h>
#include <utils.h>
#include <wifiMqttfunc.h>

void setup()
{
  Serial.begin(115200);
  Serial.println(NUM_LEDS);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  wifi_connect();
  OTA.beginSetup(OTAport, OTApass);
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback_mqtt);
  while (!client.connected())
  {
    conect_mosquitto();
  }
  client.subscribe("ledStrip_1");
  client.subscribe("ledStrips");
  startUp();
}

void loop()
{
  if (!client.connected())
  {
    reconTries +=1;
    delay(2000);
    conect_mosquitto();
    if(reconTries > 10){
      alertRED();
      esp_restart();
    }
  }
  isRainbow();
  keepOnline();
  OTA.handle();
  client.loop();
}
