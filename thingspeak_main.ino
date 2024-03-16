#include <WiFi.h>
#include "DHT.h"
#include "ThingSpeak.h" 
#define dhttype DHT22
#define dhtpin 17

DHT dht(dhtpin,dhttype);


// always include thingspeak header file after other header files and custom macros

char ssid[] = "pranav";   // your network SSID (name) 
char pass[] = "123456789";   // your network password
         // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber =2472540;
const char * myWriteAPIKey = "R2T3H4JVXJHLUKJR";
//timer variables 
unsigned long lastTime=0;
unsigned long timerdelay=30000;

//temp
float tempC;
float humidity;

void setup() {
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client); 
  dht.begin(); // Initialize ThingSpeak
}

void loop() {
  if((millis()-lastTime)> timerdelay){
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
 
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  delay(2000);
          float h=dht.readHumidity();

          float t=dht.readTemperature();

          float f=dht.readTemperature(true);//reads temp in farenhiet
          if(isnan(h) || isnan(t) || isnan(f))
          {
            Serial.println(F("FAILED"));
            return;
          }
          else
          {
            ThingSpeak.setField(1,humidity);
ThingSpeak.setField(2,tempC);
  

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
   }
   
Serial.print("HUMIDITY:");

Serial.println(h);
Serial.print("TEMP IN C:");
Serial.println(t);
Serial.print("TEMP IN F:");
Serial.println(f);
          }
  lastTime = millis();
  }


  
  delay(20000); // Wait 20 seconds to update the channel again
}

          
          
