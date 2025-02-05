#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_task_wdt.h"
#include "driver/gpio.h"
#include "esp_log.h"


#define BUTTON_GPIO 12
#define WDT_TIMEOUT 3 //Timeout i sekunder

void app_main(void)
{
   
    esp_task_wdt_delete(NULL);

   
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&button_config);

   

    esp_err_t ret = esp_task_wdt_init(WDT_TIMEOUT);
    if (ret == ESP_OK) {
        esp_task_wdt_add(NULL);
    } else {
        ESP_LOGE("Watchdog", "Failed to initialize watchdog: %s", esp_err_to_name(ret));
        return;
    }

   
    esp_reset_reason_t reason = esp_reset_reason();
    ESP_LOGI("Boot", "Reset/Boot Reason was: %d", reason);

    switch (reason) {
        case ESP_RST_UNKNOWN:
            ESP_LOGI("Boot", "Reset reason cannot be determined");
            break;
        case ESP_RST_POWERON:
            ESP_LOGI("Boot", "Reset due to power-on event");
            break;
        case ESP_RST_EXT:
            ESP_LOGI("Boot", "Reset by external pin (not applicable for ESP32)");
            break;
        case ESP_RST_SW:
            ESP_LOGI("Boot", "Software reset via esp_restart");
            break;
        case ESP_RST_PANIC:
            ESP_LOGI("Boot", "Software reset due to exception/panic");
            break;
        case ESP_RST_INT_WDT:
            ESP_LOGI("Boot", "Reset (software or hardware) due to interrupt watchdog");
            break;
        case ESP_RST_TASK_WDT:
            ESP_LOGI("Boot", "Reset due to task watchdog");
            break;
        case ESP_RST_WDT:
            ESP_LOGI("Boot", "Reset due to other watchdogs");
            break;                                
        case ESP_RST_DEEPSLEEP:
            ESP_LOGI("Boot", "Reset after exiting deep sleep mode");
            break;
        case ESP_RST_BROWNOUT:
            ESP_LOGI("Boot", "Brownout reset (software or hardware)");
            break;
        case ESP_RST_SDIO:
            ESP_LOGI("Boot", "Reset over SDIO");
            break;
        default:
            break;
    }

    while (true) {
       
        if (gpio_get_level(BUTTON_GPIO) == 0) {
           
            esp_task_wdt_reset();
            ESP_LOGI("Watchdog", "Watchdog kicked!");
        }
       
       
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
