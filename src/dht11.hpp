//用于实现DHT11传感器的相关功能
#pragma once
#include "DHT.h"
#define DHTPIN 16     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
void DHTinit()
{
  dht.begin();
}
float GetHumidity()
{
  return  dht.readHumidity();
  
}
float GetTemperature()
{
  return dht.readTemperature();
}
