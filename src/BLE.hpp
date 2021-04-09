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
#include <string>
namespace BLE
{
    #define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
    #define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
    #define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

    BLECharacteristic *pCharacteristic;
    bool deviceConnected = false;
    uint32_t cnt = 0;

    BLEServer *pServer;
    BLEService *pService;

    void HandleReceive(std::string);
    void InitBLE(const char *);
    void ResetBLE();
    class MyCallbacks : public BLECharacteristicCallbacks
    {
        void onWrite(BLECharacteristic *pCharacteristic)
        {
            std::string rxValue = pCharacteristic->getValue();

            if (rxValue.length() > 0)
            {
                Serial.print("------>Received Value: ");
                for (int i = 0; i < rxValue.length(); i++)
                {
                    Serial.print(rxValue[i]);
                }
                Serial.print("\n");
                HandleReceive(rxValue);
            }
        }
    };

    class MyServerCallbacks : public BLEServerCallbacks
    {
        void onConnect(BLEServer *pServer)
        {
            Serial.print("connected!\n");
            deviceConnected = true;
        };

        void onDisconnect(BLEServer *pServer)
        {
            Serial.print("disconnected!\n");
            ResetBLE();
            Serial.print("reset ble\n");
            deviceConnected = false;
        }
    };

    void InitBLE(const char *name = "SmartBag")
    {
        // Create the BLE Device
        BLEDevice::init(name);

        // Create the BLE Server
        BLEServer *pServer = BLEDevice::createServer();
        pServer->setCallbacks(new MyServerCallbacks());

        // Create the BLE Service
        BLEService *pService = pServer->createService(SERVICE_UUID);

        // Create a BLE Characteristic
        pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);

        pCharacteristic->addDescriptor(new BLE2902());

        BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);

        pCharacteristic->setCallbacks(new MyCallbacks());

        // Start the service
        pService->start();

        // Start advertising
        pServer->getAdvertising()->start();
        Serial.println("Waiting a client connection to notify...");
    }

    void ResetBLE()
    {
        // Start advertising
        pServer->getAdvertising()->start();
        Serial.println("Waiting a client connection to notify...");
    }
    void HandleReceive(std::string value)
    {
    }

    void Send(std::string value)
    {
        if (deviceConnected)
        {
            pCharacteristic->setValue(value.data());
            pCharacteristic->notify(); // Send the value to the app!
            Serial.print("*** Sent Value: ");
            Serial.print(value.data());
            Serial.printf("\n");
        }
        else
        {
            Serial.print("not connected,can't send");
        }
    }

}
