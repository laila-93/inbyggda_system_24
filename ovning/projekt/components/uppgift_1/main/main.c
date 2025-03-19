
#include <stdio.h>
#include "Potentiometer.h"

void app_main(void) {
    MeasurementDevice sensor;

    init(&sensor, ADC_CHANNEL_4); 
    setOnThreshold(&sensor, 2000, false, threshold_callback, NULL); //tröskelvärde och callback.
    activateDevice(&sensor, true); // Aktiveras enheten.

    while (1) {
        updateMeasurementDevice(&sensor); // Uppdatera sensorns status.
        printf("Nuvarande värde: %d\n", getValue(&sensor)); // Skriv ut det aktuella värdet.
        vTaskDelay(pdMS_TO_TICKS(100)); // Vänta i 100 ms innan nästa iteration.
    }


/* #include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "hal/adc_types.h"
#include "esp_mac.h"
#include "analog_led.h" // Inkluderar headerfilen för analog LED-styrning

void app_main(void)
{
    AnalogLED_t Myled; // Skapa en instans för att kontrollera LED-ljuset
    AnalogLedInit(&Myled, ANALOG_LED_PIN); // Initiera LED med en specifik GPIO
    Analog_set_Led(&Myled, 5000); // Sätt ljusstyrka (1000) och period (4000 ms = 4 sekunder)
    AnalogSinWave(&Myled, 1, 4000); // Aktivera sinusvåg med LEDn och sätt period till 400 ms
    Analog_set_Led(&Myled, 1000);

    // Huvudloop för att uppdatera LED:n kontinuerligt
    while (1) {
        AnalogLedUpdate(&Myled); // Uppdatera LED:n baserat på sinusvåg eller fast ljusstyrka
        vTaskDelay(50 / portTICK_PERIOD_MS); // Fördröjning på 50 ms mellan uppdateringarna
    }*/
 
    
    /* LED_t led;

    led_init(&led, 20);
    //setLed(&led,0);
    //setLed(&led,1);
    blink(&led, 500, 500);
    setLed(&led,1);
    blink(&led, 500, 500);

    while (1)
    {
       // button_update(&btn);
       update(&led);
       vTaskDelay(pdMS_TO_TICKS(10));
    } */


    /* #include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "button.h" // Inkludera din knappheaderfil

// Callback-funktion för knapptryckning
void myButtonCallback() {
    printf("Knappen trycktes ned!\n");
}

void app_main() {

    Button_t btn;

    init(&btn, 2);  // Initiera knappen på GPIO pin 2
    button_setOnPressed(&btn, myButtonCallback);

    while (1)
    {
        button_update(&btn);
        vTaskDelay(pdMS_TO_TICKS(10));
    } */

    
    
} 