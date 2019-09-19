#include <SPI.h>
#include <LoRa.h>
#include <SimpleDHT.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


int pinDHT22 = 3;
SimpleDHT22 dht22(pinDHT22);
static const int RXPin = 6, TXPin = 5;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  Serial.print((float)temperature);
  Serial.print("  ");
  Serial.println((float)humidity);
  TinyGPSDate &d=gps.date;
  TinyGPSTime &t=gps.time;
  char dates[32];
  sprintf(dates, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
  Serial.print(dates);

  char times[32];
    sprintf(times, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(times);
    Serial.print(gps.altitude.meters());
//  // send packet
  LoRa.beginPacket();
  LoRa.print((float)temperature);
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.print((float)humidity);
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.print((char)dates);
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.print((char)times);
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.print((float)gps.location.lat());
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.print((float)gps.location.lng());
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.print((float)gps.altitude.meters());
  LoRa.endPacket();
  delay(5000);
}
