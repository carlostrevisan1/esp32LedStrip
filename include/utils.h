int set_red(char * color){
    int value = atoi(color);
    if (value < 0) value = 0;
    if (value > 255) value = 255;
    return value;
}

int set_green(char * color){
    int value = atoi(color);
    if (value < 0) value = 0;
    if (value > 255) value = 255;
    return value;
}

int set_blue(char * color){
    int value = atoi(color);
    if (value < 0) value = 0;
    if (value > 255) value = 255;
    return value;
}

boolean validateRainbowValue(String msg){
    for (int i = 0; i< msg.length(); i++){
        if (!(msg[i] >= '0' && msg[i] <= '9')){
                    return false;
                }        
    }
    return true;
}

boolean validateNumber(char validateNum){
    if (!(validateNum >= '0' && validateNum <= '9')){
            return false;
        }        
    return true;
}

boolean validateRGBMessageFormat(String msg){
    if(msg.length() < 5 || msg.length() > 11)
        return false;
    if(msg.indexOf(",") < 0)
        return false;
    
    for (int i = 0; i< msg.length(); i++){
        if(!validateNumber(msg[i])){
            if(msg[i] != ','){
                return false;
            }
            else{
                if(msg[i+1] == ',')
                    return false;
            }
        }
    }
    return true;
    
}

void remove_spaces(char * p){
    Serial.println("Removing Spaces");
    if (p == NULL)
        return;
    int n = 0;
    for (int i = 0; i<strlen(p); i++){
        if (p[i] != ' '){
            p[n++] = p[i];
        }
    }
    p[n] = '\0';
}

boolean split_colors_values(char *red, char *green, char *blue, char *msg){
    char * message = strdup(msg);

    remove_spaces(message);
    if(validateRGBMessageFormat(message)){
        strncpy(red, strtok(message, ","), 4);
        strncpy(green, strtok(NULL, ","), 4);
        strncpy(blue, strtok(NULL, ","), 4);
        return true;
    }
    else
        return false;
}

char *byte_message_to_char(byte* message, unsigned int length){
    char *msg =(char*) malloc(length * sizeof(char));

    for(int x=0; x<length; x++){
        msg[x] = message[x];
    }
    msg[length] = '\0';

    return msg;
}

int getModeValue(char* mode){
    // 0 - rainbow, 1 - rgb
    if(strcmp(mode, "rainbow") == 0){
        return 0;
    }

    if(strcmp(mode, "rgb") == 0){
        return 1;
    }
    else
        return -1;
}

void handleModeTransition(int modeNum, char* value, char* params){
    rainbowMode = 0;
    switch (modeNum){
        case 0:
            if(validateRainbowValue(value)){
                if(atoi(value)==0){
                    fadeOff();
                }
                else{
                    rainbowMode = 1;
                    rainbowSpeed = atoi(value);
                }
            }
            else{
                alertRED();
            }
            break;

        case 1:
            char r[4], g[4], b[4];
            if(split_colors_values(r, g, b, value)){
                staticColor(set_red(r), set_green(g), set_blue(b));
            }
            else
                alertRED();
            break;

        case -1:
            alertRED();
            break;

        default:
            fadeOff();
            break;
    }
}

void isRainbow(){
    if(rainbowMode == 1){
        rainbow_loop(rainbowSpeed);
    }
}

