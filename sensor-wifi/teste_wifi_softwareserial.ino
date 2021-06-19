#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define D7 13
#define D8 15

HTTPClient http;

int fsrReading = 0;
char charFsrReading = 'z';

int cooldownTime = 5;
int delayCount = 100;
int rotationPerSecond = 1000 / delayCount;
int cooldownWait = -1;

void setup() {
  Serial.begin(9600); //Serial connection
  
  WiFi.begin("2G APT 1012", "B38C4C0F");   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    // Serial.println("Waiting for connection");
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    // fsrReading = analogRead(FSR_PIN);
    if(Serial.available()){
      fsrReading = Serial.read();
      charFsrReading = fsrReading;
    }else{
      fsrReading = -1;
      charFsrReading = 'z';
    }

    if (fsrReading != 255 & fsrReading > 10 && cooldownWait < 0) {

      HTTPClient http;    //Declare object of class HTTPClient

      //http.begin("http://vtuber-api.herokuapp.com/");      //Specify request destination
      http.addHeader("Content-Type", "text/plain");  //Specify content-type header

      if (charFsrReading == 'w') {
        Serial.println("weak");
        http.begin("http://vtuber-api.herokuapp.com/weak");

      } else if (charFsrReading == 's') {
        Serial.println("strong");
        http.begin("http://vtuber-api.herokuapp.com/strong");

      } else if (charFsrReading == 'h') {
        http.begin("http://vtuber-api.herokuapp.com/hulk");
        Serial.println("hulk");

      } else if (charFsrReading == 'g'){
        Serial.println("goku");
        http.begin("http://vtuber-api.herokuapp.com/goku");
      }else{
        cooldownWait = rotationPerSecond * cooldownTime;
        delay(10);
        delay(delayCount);
      }

/*
      if (fsrReading < 50) {
        Serial.println("weak");
        http.begin("http://vtuber-api.herokuapp.com/weak");

      } else if (fsrReading < 200) {
        Serial.println("strong");
        http.begin("http://vtuber-api.herokuapp.com/strong");

      } else if (fsrReading < 450) {
        http.begin("http://vtuber-api.herokuapp.com/hulk");
        Serial.println("hulk");

      } else {
        Serial.println("goku");
        http.begin("http://vtuber-api.herokuapp.com/goku");
      }
      */

      String payload = http.getString(); //Get the response payload
      int httpCode = http.POST("");
      http.end();  //Close connection

      cooldownWait = rotationPerSecond * cooldownTime ;
    }
  } else {
    // Serial.println("Error in WiFi connection");
  }

  if ( cooldownWait >= 0 ) {
    cooldownWait--;
  }

  delay(10);
  delay(delayCount);

}
