#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

StaticJsonDocument<200> doc;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

HTTPClient http;
WiFiClient client;
const char* ssid = "POCO M3";
const char* password = "Pass1234";
void setup () {
   // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    
    http.begin(client, "http://192.168.43.15:8000/lcd_display/");  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
          Serial.println(httpCode);

    
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); 
      
      Serial.println(payload);
      
       
      DeserializationError Error = deserializeJson(doc, payload); 
      if(Error){
        Serial.print("deserializejson() failed");
        Serial.println(Error.c_str());
        
        return;
      }
      const char* m = doc["message"];
      long s = doc["count"];
      Serial.println(m);
      Serial.println(s);
       lcd.setCursor(0, 0);
  // print message
  lcd.print(m);
  
  
  
  lcd.setCursor(0,1);
  lcd.print(s);
  delay(5000);
  lcd.clear(); 
      
     
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(3000);    //Send a request every 30 seconds
}
