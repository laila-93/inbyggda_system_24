
#include "analog_led.h"

AnalogLED_t my_led;

void app_main(void) {

    analog_led_init(&my_led, ANALOG_LED_PIN);
    analog_set_led(&my_led, 500, 4000); //ljusstyrka (0-1023), ...sek period, vid 500, 0 lyser hela tiden, ingen sinVåg
    analog_sin_wave(&my_led, 1); // Sinusvågen: slå på 1; stäng av 0

    while (1) {

        analog_led_update(&my_led);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }



 /*
 #include <stdio.h>
#include "potentiometer.h"        
#include "hal/adc_types.h"        
#include "esp_adc/adc_oneshot.h"  
#include "freertos/FreeRTOS.h"    
#include "freertos/task.h"        
#define ADC_PIN ADC_CHANNEL_4      

void app_main() {
    adc_sensor_t sensor;  // Skapar en sensor (en "variabel" som lagrar information om ADC)
    adc_init(&sensor, ADC_PIN);  // Anropar funktionen som sätter upp ADC-sensorn på den pinnen
    adc_set_on_threshold(&sensor, 2000, 2, threshold_handler);  // Sätter tröskelvärdet till 2000 och anger en funktion (callback) som körs när tröskeln passeras

    while (1) {  // Startar en evig loop som aldrig slutar
        adc_update(&sensor);  // Uppdaterar sensorvärdet (läser det nya ADC-värdet)
        vTaskDelay(pdMS_TO_TICKS(500));  // Väntar 500 millisekunder innan nästa uppdatering
    }
 */ 

        
    /*
    LED_t led;

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
    }
    */


    /*
 #include <stdio.h>
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
    }
    */
    
}