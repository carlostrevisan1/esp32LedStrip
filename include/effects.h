
void setPixel(int Pixel, byte red, byte green, byte blue){
    leds[Pixel].setRGB(red, green, blue);
}

void setAll(byte red, byte green, byte blue) {
    for(int i = 0; i < NUM_LEDS; i++ ) {
        setPixel(i, red, green, blue);
    }
    FastLED.show();
}

void cleanUp(){
    setAll(0,0,0);
}

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
    for (int i = (NUM_LEDS/2)-1,back = NUM_LEDS/2; back < NUM_LEDS; i--, back++)
        {
            leds[i] = leds[i].setRGB(red, green,blue);
            leds[back] = leds[back].setRGB(red, green,blue);
            delay(15);
            FastLED.show();
        }
    
}

void FadeInOut(byte red, byte green, byte blue){
    float r, g, b;

    for(int k = 0; k < 256; k=k+1) {
        r = (k/256.0)*red;
        g = (k/256.0)*green;
        b = (k/256.0)*blue;
        setAll(r,g,b);
        delay(15);
    }
    
    for(int k = 255; k >= 0; k=k-2) {
        r = (k/256.0)*red;
        g = (k/256.0)*green;
        b = (k/256.0)*blue;
        setAll(r,g,b);
        delay(15);
    }
}

void HalloweenEyes(byte red, byte green, byte blue,
                    int EyeWidth, int EyeSpace,
                    boolean Fade, int Steps, int FadeDelay,
                    int EndPause){
    randomSeed(analogRead(0));

    int i;
    int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
    int Start2ndEye = StartPoint + EyeWidth + EyeSpace;

    for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
}
    FastLED.show();

    if(Fade==true) {
    float r, g, b;

    for(int j = Steps; j >= 0; j--) {
        r = j*(red/Steps);
        g = j*(green/Steps);
        b = j*(blue/Steps);

        for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
        }
    
        FastLED.show();
        delay(FadeDelay);
    }
}

  setAll(0,0,0); // Set all black

    delay(EndPause);
}

void startUp(){
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(90, 90, 90);
    }
    FastLED.show();
    delay(100);
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = leds[i].setRGB(90, 90, 90);
    }
    FastLED.show();
    delay(150);
    rainbow_loop(1);
    for (int i = 0; i < NUM_LEDS; i++){
        int randomNum = random(0,120);
        setPixel(randomNum, 90, 0, randomNum);
        delay(20);
        FastLED.show();
    }
    cleanUp();
    
    HalloweenEyes(0xff, 0x00, 0x00,
                1, 4,
                true, random(5,50), random(50,150),
                random(1000, 10000));
}