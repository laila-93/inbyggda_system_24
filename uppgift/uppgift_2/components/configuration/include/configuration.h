#ifndef CONFIG_H
#define CONFIG_H

#define MAX_LEN 50  // Max längd för strängar

// Funktioner för att hantera konfiguration
void initConfig(); // Initiera och ladda från NVS
char* getDeviceName(); // Hämta device name
char* getSerialNumber(); // Hämta serial number
void setDeviceName(char *newName); // Uppdatera device name
void setSerialNumber(char *newSerial); // Uppdatera serial number

#endif