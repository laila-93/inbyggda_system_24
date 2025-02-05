#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_task_wdt.h>
#include <esp_err.h>
#include <nvs_flash.h>
#include <esp_system.h>
#include <stdio.h>

// Definiera knappens GPIO pin
const gpio_num_t button_pin = GPIO_NUM_12;

// Funktion för att hantera knappen
void buttonTask(void *pvParameter)
{
    // Initiera knappens GPIO pin som ingång
    gpio_set_direction(button_pin, GPIO_MODE_INPUT);
    while (1)
    {
        // Läser knappens tillstånd
        int buttonState = gpio_get_level(button_pin);
        if (buttonState == 0)
        {
            printf("Knapp tryckt\n");
        }
        else
        {
            printf("Knapp inte tryckt\n");
        }
        // Paus för att undvika överbelastning
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
// Funktion för att hantera watchdog-timer
void watchdogTask(void *pvParameter)
{
    esp_task_wdt_config_t wdtConfig = {
        .timeout_ms = 3000
    };
    // Initiera Watchdog Timer med timeout på 3 sekunder
    ESP_ERROR_CHECK(esp_task_wdt_init(&wdtConfig));

    // Lägg till aktuell task till Watchdog Timer
    esp_task_wdt_add(NULL);

    while (1)
    {
        // Mata Watchdog
        esp_task_wdt_reset();
        printf("Watchdog matas\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS); // Matas var 2:a sekund
    }
}
void app_main()
{
    // Initiera NVS (Non-Volatile Storage)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    esp_task_wdt_config_t WDtime;
    // Initiera Watchdog Timer
    ESP_ERROR_CHECK(esp_task_wdt_init(&WDtime));

    // Skapa och starta uppgifter
    xTaskCreate(&buttonTask, "buttonTask", 2048, NULL, 5, NULL);
    xTaskCreate(&watchdogTask, "watchdogTask", 2048, NULL, 5, NULL);
}