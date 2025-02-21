#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "analog_led.h" // Inkludera analog_led-headerfilen

void app_main(void)
{
    AnalogLed led;
    AnalogLed_init(&led, 20); // Initiera LED på GPIO pin 20

    // Sätt ljusstyrkan för LED:en till 21
    

    // Ställ in perioden för sinusvåg för LED:en
    AnalogLed_setPeriod(&led, 1500);
    AnalogLed_setLed(&led, 55);

    while (1)
    {
        AnalogLed_update(&led); // Uppdatera LED för att hantera sinusvåg
        vTaskDelay(pdMS_TO_TICKS(10)); // Vänta för att undvika att utlösa watchdog-timern

    }
        

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