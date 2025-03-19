#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "hal/adc_types.h"
#include "analog_led.h"

void app_main(void)
{
   
    AnalogLED_t Myled; // Skapa en instans för att styra LED
    AnalogLedInit(&Myled, ANALOG_LED_PIN); // Initiera LED med en specifik GPIO
    AnalogSetLed(&Myled, 1000, 4000); // Ställ in ljusstyrka (1000) och period till 4 sekunder
    AnalogSinWave(&Myled, 1, 400); // Aktivera sinusvåg på LED med en period på 4000 ms
   
    // Huvudloopen för att uppdatera LED-tillståndet regelbundet
    while (1) {
        AnalogLedUpdate(&Myled); // Uppdatera LED-tillståndet
        vTaskDelay(50 / portTICK_PERIOD_MS); // Fördröjning på 50 ms mellan uppdateringar
    }
}
