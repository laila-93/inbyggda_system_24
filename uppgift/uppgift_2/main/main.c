#include <stdio.h>

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "hal/adc_types.h"

#include "configuration.h"


void app_main(void)
{   
     DeviceConfig config;
     ConfigResult result;
 
     // Initiera konfigurationen (inläsning från simulerad NVS)
     result = config_init(&config);
     if (result != CONFIG_OK) {
         printf("Fel vid initiering av konfiguration.\n"); // Skriv ut felmeddelande
         return; // Avsluta funktionen
     }
 
     // Visa den ursprungliga konfigurationen
     printf("Ursprungligt enhetsnamn: %s\n", getDeviceName(&config));
     printf("Ursprungligt serienummer: %s\n", getSerialNumber(&config));
 
     // Sätt nya värden för enhetsnamn och serienummer
     result = setDeviceName(&config, "MiDispositivo");
     if (result != CONFIG_OK) {
         printf("Fel vid inställning av enhetsnamn.\n");
         return;
     }
 
     result = setSerialNumber(&config, "SN123456");
     if (result != CONFIG_OK) {
         printf("Fel vid inställning av serienummer.\n");
         return;
     }
 
     // Visa den uppdaterade konfigurationen
     printf("Uppdaterat enhetsnamn: %s\n", getDeviceName(&config));
     printf("Uppdaterat serienummer: %s\n", getSerialNumber(&config));
   

}