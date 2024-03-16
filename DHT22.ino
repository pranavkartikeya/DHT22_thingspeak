
#include "DHT.h"
#define dhttype DHT22
#define dhtpin 17

DHT dht(dhtpin,dhttype);

void setup()
    {
      Serial.begin(9600);
      dht.begin();
    }
void loop()
{
  delay(2000);
  float h=dht.readHumidity();

  float t=dht.readTemperature();

  float f=dht.readTemperature(true);//reads temp in farenhiet
if(isnan(h) || isnan(t) || isnan(f)){
  Serial.println(F("FAILED"));
  return;
}
Serial.print("HUMIDITY:");

Serial.println(h);
Serial.print("TEMP IN C:");
Serial.println(t);
Serial.print("TEMP IN F:");
Serial.println(f);



}
