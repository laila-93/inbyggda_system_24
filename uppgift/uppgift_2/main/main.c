#include <stdio.h>
#include "Configuration.h"

void app_main() {
    Configuration config;

    // Initiera konfigurationen (initialisering av NVS)
    initConfiguration(&config);

    // Visa initiala värden från NVS
    printf("NVS initialized and values loaded into RAM.\n");
    printf("Device Name: %s\n", getDeviceName(&config));
    printf("Serial Number: %s\n", getSerialNumber(&config));

    // Uppdatera värden
    setDeviceName(&config, "ESP32_DevKit");
    setSerialNumber(&config, "1234567890");

    // Visa uppdaterade värden
    printf("Updated Device Name: %s\n", getDeviceName(&config));
    printf("Updated Serial Number: %s\n", getSerialNumber(&config));
}