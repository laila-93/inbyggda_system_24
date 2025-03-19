#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "esp_err.h" // Inkluderar ESP-IDF-specifik felbibliotek

// Definiera konstanter för NVS (icke-flyktigt minne)
#define NVS_NAMESPACE "storage"        // Namnrymd som används i NVS
#define DEVICE_NAME_KEY "device_name"  // Nyckel för att lagra enhetens namn
#define SERIAL_NUMBER_KEY "serial_number" // Nyckel för att lagra serienumret
#define MAX_STR_LEN 100                // Maximal längd för strängar (namn och serienummer)

// Strukturen för enhetskonfiguration
typedef struct {
    char deviceName[MAX_STR_LEN];      // Lagrar enhetens namn
    char serialNumber[MAX_STR_LEN];   // Lagrar enhetens serienummer
} Configuration;

// Deklaration av funktioner relaterade till enhetskonfiguration
void initConfiguration(Configuration* config);      // Initierar enhetskonfigurationen
const char* getDeviceName(Configuration* config);   // Returnerar enhetens namn
const char* getSerialNumber(Configuration* config); // Returnerar enhetens serienummer
esp_err_t setDeviceName(Configuration* config, const char* newName); // Ställer in ett nytt namn för enheten
esp_err_t setSerialNumber(Configuration* config, const char* newSerial); // Ställer in ett nytt serienummer
esp_err_t saveToNVS(const char* key, const char* value); // Sparar en nyckel och ett värde i NVS

#endif 