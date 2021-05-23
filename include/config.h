
#define LED_PIN 4 //signal pin 
#define NUM_LEDS 120 //number of LEDs in your strip


CRGB leds[NUM_LEDS];
const char* ssid       = "<YOUR SSID>";
const char* password   = "<YOUR PASSWORD>";

int reconTries = 0;
const char* mqttServer = "<ADRESS>";
const int mqttPort = 0;//YOUR PORT;
const char* mqttUser = "MQTT USER";
const char* mqttPassword = "MQTT PASS";
unsigned long lastMillis = millis();

int rainbowMode = 0;
int rainbowSpeed = 0;

WiFiClient espClient;
EasyOTA OTA;
const char* OTApass = "YOUR OTAPASS";
int OTAport = 00; // OTA PORt
PubSubClient client(espClient);

