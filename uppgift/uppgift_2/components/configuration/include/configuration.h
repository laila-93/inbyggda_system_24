#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

// Struktur för att lagra konfigurationsdata
typedef struct {
    char deviceName[64];     // Enhetsnamn med max 64 tecken
    char serialNumber[32];   // Serienummer med max 32 tecken
} DeviceConfig;

// Enum för att representera resultat av operationer
typedef enum {
    CONFIG_OK,          // Operationen lyckades
    CONFIG_ERROR,       // Fel vid operation
    CONFIG_NVS_ERROR    // Fel med NVS (ej relevant i simulering)
} ConfigResult;

// Funktioner för att hantera konfiguration
ConfigResult config_init(DeviceConfig *config);
char* getDeviceName(DeviceConfig *config);
char* getSerialNumber(DeviceConfig *config);
ConfigResult setDeviceName(DeviceConfig *config, const char *deviceName);
ConfigResult setSerialNumber(DeviceConfig *config, const char *serialNumber);

#endif // CONFIG_H