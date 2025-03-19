
#include <stdio.h>
#include "potentiometer.h"        // Vi hämtar funktionerna för att läsa av potentiometern
#include "hal/adc_types.h"        
#include "esp_adc/adc_oneshot.h"  // Bibliotek för att läsa analogt värde
#include "freertos/FreeRTOS.h"    
#include "freertos/task.h"        

#define ADC_PIN ADC_CHANNEL_4      // Vi säger att vi använder kanal 4 för att läsa värdet

// Detta är huvuddelen av programmet
void app_main() {
    adc_sensor_t sensor;  // Skapar en "låda" (variabel) där vi sparar infon om potentiometern
    adc_init(&sensor, ADC_PIN);  // Startar och kopplar sensorn till rätt pin
    adc_set_on_threshold(&sensor, 2000, 1, threshold_handler);  // Om värdet går över 2000 körs en funktion

    while (1) {  // En loop som aldrig slutar, så att programmet körs hela tiden
        adc_update(&sensor);  // Kollar vad värdet är just nu
        vTaskDelay(pdMS_TO_TICKS(500));  // Väntar en halv sekund innan vi kollar igen
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