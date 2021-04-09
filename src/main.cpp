#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <HardwareSerial.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <soc/rmt_struct.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include "dht11.hpp"
#include <string>
#include <iostream>   
#include <string> 
#include <sstream>
#include <common.hpp>
#include "BLE.hpp"
#include "Myhardware.hpp"
void setup()
{
  Serial.begin(115200);
  BLE::InitBLE("SmartBag");
  DHTinit();
  //xTaskCreate(change_mode, "change_mode", 10000, NULL, 1, NULL);
}

void loop()
{
  delay(2000);
  if(BLE::deviceConnected)
  {
    float tem = GetTemperature();
    float hum = GetHumidity();
    Serial.print(tem);
    Serial.print(hum);
    BLE::Send("{"+HWID::temprater+ ":"+ to_string(tem) + "}");
    BLE::Send("{"+HWID::humidity+ ":"+ to_string(hum) + "}");
  }
}