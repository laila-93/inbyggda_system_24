#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freetors/task.h"
#include "driver/gpio.h"


#define BLINK_GPIO GPIO_NUM_2


void app_main(void)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1){
        
    }


}