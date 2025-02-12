
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"

void app_main(void)
{
    gpio_config_t buttonConfig;
    buttonConfig.mode = GPIO_MODE_INPUT;
    buttonConfig.intr_type = GPIO_INTR_DISABLE;
    buttonConfig.pull_down_en = 0;
    buttonConfig.pull_up_en = 0;
    buttonConfig.pin_bit_mask = 1ULL << GPIO_NUM_12;
    esp_err_t error = gpio_config(&buttonConfig);
