
void wifi_connect(){
   //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
}

boolean conect_mosquitto(){
  if (client.connect("ESP32Client", mqttUser, mqttPassword )){     
    Serial.println("Conectado ao broker!");  
    return true;
    }    
  else{      
    Serial.print("Falha na conexao ao broker - Estado: ");      
    Serial.print(client.state());      
    delay(2000);   
    return false;
    }
}
void keepOnline(){
  if(millis() - lastMillis > 1000)
    client.publish("OnlineDevices", "LedStrip_1 - Online");
}

//message format <mode>/<value>/<params> 
// ex : "rgb/2,5,5/" , "rainbow/1/5", reset/1/1, demon/1/1, fade/1/1
void callback_mqtt(char* topic, byte* message, unsigned int length){
  char *msg, *mode,*value, *params;
  int modeNum = -1;

  msg = {byte_message_to_char(message, length)};
  mode =strtok(msg,"/");
  value = strtok(NULL,"/");
  params = strtok(NULL,"/");
  modeNum = getModeValue(mode);
  Serial.print(mode);
  Serial.print(" ");
  Serial.print(value);
  Serial.print(" ");
  Serial.print(params);
  Serial.print(" ");
  Serial.println(modeNum);
  handleModeTransition(modeNum, value, params);
  
}
