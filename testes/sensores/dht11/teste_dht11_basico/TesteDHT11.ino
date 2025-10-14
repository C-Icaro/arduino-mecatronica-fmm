#include <dht11.h>
#define DHT11PIN 13

dht11 DHT11;

void  setup()
{
  Serial.begin(115200);
 
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  float Hum = DHT11.humidity;
  Serial.println(Hum);

  Serial.print("Temperature  (C): ");
  float Temp = DHT11.temperature;
  Serial.println(Temp);

  delay(2000);

}


