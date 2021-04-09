#pragma once
#include "DHT.h"
#define DHTPIN 16     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
void dht11()
{
  delay(2000);                      // 等一段时间给传感器检测，一般温度和湿度各需要250毫秒
  float h = dht.readHumidity();    //读湿度        int
  float t = dht.readTemperature(); //读温度
}