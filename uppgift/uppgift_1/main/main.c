#include <stdio.h>
#include "potentiometer.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
 #include "freertos/FreeRTOS.h"
 #include "freertos/task.h"
 


 void app_main(){
    AnalogLed_t led;
    analog_led_init(20, &led); // Justerat till AnalogLed_init och GPIO pin 20

    while (1) {
        // För att blinka: setAnalogLed(true, 1.00, 1.0, &led);
        // För att släcka: setAnalogLed(false, 0.0, 0.0, &led);
        // För att lysa jämt: setAnalogLed(true, 1.00, 0.0, &led);
        
        // Justeringar för att bestämma om LED:en ska lysa maximalt eller sluta lysa helt
        setAnalogLed(true, 1.00, 1.0, &led); // För att blinka
        // setAnalogLed(false, 0.0, 0.0, &led); // För att släcka
        // setAnalogLed(true, 1.00, 0.0, &led); // För att lysa jämt

        update_analog(&led);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

 

 /*
 #define ADC_PIN ADC_CHANNEL_3  // GPIO3
 
 
 void app_main() {
     adc_sensor_t sensor;
     adc_init(&sensor, ADC_PIN);
     adc_set_on_threshold(&sensor, 2000, true, threshold_handler);
 
     while (1) {
         adc_update(&sensor);
         vTaskDelay(pdMS_TO_TICKS(500)); 
     }
 
 
 */
 
        
    /*
     AnalogLed_t led;
    analog_led_init(20, &led); // Justerat till AnalogLed_init och GPIO pin 20

    while (1) {
        // För att blinka: setAnalogLed(true, 1.00, 1.0, &led);
        // För att släcka: setAnalogLed(false, 0.0, 0.0, &led);
        // För att lysa jämt: setAnalogLed(true, 1.00, 0.0, &led);
        
        // Justeringar för att bestämma om LED:en ska lysa maximalt eller sluta lysa helt
        setAnalogLed(true, 1.00, 1.0, &led); // För att blinka
        // setAnalogLed(false, 0.0, 0.0, &led); // För att släcka
        // setAnalogLed(true, 1.00, 0.0, &led); // För att lysa jämt

        update_analog(&led);
        vTaskDelay(pdMS_TO_TICKS(10));
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