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
    } */

    
    
} 