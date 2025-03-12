#include "config.h"
#include <stdio.h>
#include <string.h>

// Kontrollera att MAX_LEN är definierad
#ifndef MAX_LEN
#define MAX_LEN 50
#endif


// Arbetsminne för att lagra namn och serienummer
char deviceName[MAX_LEN] = "";
char serialNumber[MAX_LEN] = "";

// Simulerat NVS-minne (icke-flyktigt minne)
char nvs_deviceName[MAX_LEN] = "StandardDevice";
char nvs_serialNumber[MAX_LEN] = "123456789";

// Laddar data från NVS till arbetsminne
void initConfig() {
    strcpy(deviceName, nvs_deviceName); // Kopiera från NVS
    strcpy(serialNumber, nvs_serialNumber); // Kopiera från NVS
}

// Hämtar device name från arbetsminnet
char* getDeviceName() {
    return deviceName;
}

// Hämtar serial number från arbetsminnet
char* getSerialNumber() {
    return serialNumber;
}

// Uppdaterar device name i arbetsminnet och sparar i NVS
void setDeviceName(char *newName) {
    strncpy(deviceName, newName, MAX_LEN); // Uppdatera arbetsminnet
    strcpy(nvs_deviceName, newName); // Spara i "NVS"
}

// Uppdaterar serial number i arbetsminnet och sparar i NVS
void setSerialNumber(char *newSerial) {
    strncpy(serialNumber, newSerial, MAX_LEN); // Uppdatera arbetsminnet
    strcpy(nvs_serialNumber, newSerial); // Spara i "NVS"
}
