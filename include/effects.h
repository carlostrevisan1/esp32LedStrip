byte * wheel(byte wheelPos) {
    static byte c[3];
    if(wheelPos < 85) {
    c[0]=wheelPos * 3;
    c[1]=255 - wheelPos * 3;
    c[2]=0;
    } else if(wheelPos < 170) {
    wheelPos -= 85;
    c[0]=255 - wheelPos * 3;
    c[1]=0;
    c[2]=wheelPos * 3;
    } else {
    wheelPos -= 170;
    c[0]=0;
    c[1]=wheelPos * 3;
    c[2]=255 - wheelPos * 3;
    }
    return c;
}

void rainbow_loop(int velocidade) {
    byte *c;
    uint16_t i, j;
    for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< NUM_LEDS; i++) {
            c=wheel(((i * 256 / NUM_LEDS) + j) & 255);
            leds[i].setRGB(*c, *(c+1), *(c+2));
        }
        FastLED.show();
        delay(velocidade);
    }
}

void fadeOff(){
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(0, 0, 0);
        delay(10);
        FastLED.show(); 
    }
}

void alertRED(){
    Serial.println("ALERTA VERMELHO FI");
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(90, 0, 0);
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(90, 0, 0);
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
}

void staticColor(int red, int green,int blue){
    for (int i = 0,back = NUM_LEDS; i < (NUM_LEDS/2)+1; i++, back--)
        {
            leds[i] = leds[i].setRGB(red, green,blue);
            leds[back] = leds[i].setRGB(red, green,blue);
            delay(15);
            FastLED.show();
        }
    
}

void startUp(){
    for (int i = 0; i < NUM_LEDS; i++){
        int randomNum = random(0,120);
        leds[randomNum] = leds[randomNum].setRGB(90, 0, randomNum);
        delay(20);
        FastLED.show();
    }
}