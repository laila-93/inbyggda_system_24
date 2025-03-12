#include <stdio.h>
#include "configuration.h"
#include <string.h>
#include <stdio.h>

// Simulerad NVS (icke-flyktigt minne)
static DeviceConfig simulatedNVS = {
    .deviceName = "DefaultDevice", // Standardvärde för enhetsnamn
    .serialNumber = "DefaultSN"   // Standardvärde för serienummer
};

ConfigResult config_init(DeviceConfig *config) {
    // Initiera från simulerad NVS
    *config = simulatedNVS; // Kopiera data från simulerad NVS till config
    return CONFIG_OK; // Returnera OK om allt är korrekt
}

char* getDeviceName(DeviceConfig *config) {
    return config->deviceName; // Returnera enhetsnamn
}

char* getSerialNumber(DeviceConfig *config) {
    return config->serialNumber; // Returnera serienummer
}

ConfigResult setDeviceName(DeviceConfig *config, const char *deviceName) {
    if (strlen(deviceName) >= sizeof(config->deviceName) - 1) {
        return CONFIG_ERROR; // Fel om namnet är för långt
    }
    strcpy(config->deviceName, deviceName); // Kopiera namnet till strukturen
    simulatedNVS = *config; // Spara till simulerad NVS
    return CONFIG_OK; // Returnera OK om namnet är inställt
}

ConfigResult setSerialNumber(DeviceConfig *config, const char *serialNumber) {
    if (strlen(serialNumber) >= sizeof(config->serialNumber) - 1) {
        return CONFIG_ERROR; // Fel om serienumret är för långt
    }
    strcpy(config->serialNumber, serialNumber); // Kopiera serienumret till strukturen
    simulatedNVS = *config; // Spara till simulerad NVS
    return CONFIG_OK; // Returnera OK om serienumret är inställt
}

