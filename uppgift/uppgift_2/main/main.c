#include "config.h"
#include <stdio.h>

int main() {
    initConfig(); // Ladda värden från NVS
    
    // Visa aktuella värden
    printf("Nuvarande Device Name: %s\n", getDeviceName());
    printf("Nuvarande Serial Number: %s\n", getSerialNumber());
    
    // Uppdatera värden
    setDeviceName("MinEnhet"); // Ändra device name
    setSerialNumber("987654321"); // Ändra serial number
    
    // Visa uppdaterade värden
    printf("Efter uppdatering:\n");
    printf("Device Name: %s\n", getDeviceName());
    printf("Serial Number: %s\n", getSerialNumber());
    
    return 0;
}