#include "analog_led.h"
#include <math.h>
#include "esp_log.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Om M_PI inte är definierat, definiera det
#endif


static const char *TAG = "analog_led";

// Funktion för att initiera LED:n på en viss pin
void init(int pin, AnalogLed_t *led) {
    led->pin = pin;
    led->timer_channel = 0;
    led->period = 3000; // Standardperiod för sinusvåg (3 sekunder)
    led->last_update = xTaskGetTickCount(); // Hämta nuvarande tid
    led->duty_cycle = 0.0;  // Startljusstyrka
    led->target_duty_cycle = 0.0; // Startvärde för fast ljusstyrka
    led->sinus_active = false; // Sinusvåg är inte aktiv vid start

    // Initiera timer för att styra LED:ns ljusstyrka
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000, // Frekvensen för timer
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Initiera kanal för att styra LED:ns ljusstyrka
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = led->timer_channel,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = pin,
        .duty = 0, // Startljusstyrka
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);

    ESP_LOGI(TAG, "LED initialized on pin %d", pin);
}

// Funktion för att sätta fast ljusstyrka
void setLed(double value, AnalogLed_t *led) {
    led->sinus_active = false; // Stäng av sinusvågen när vi sätter fast ljusstyrka
    led->target_duty_cycle = value; // Sätt den fasta ljusstyrkan
    led->duty_cycle = value / 255.0; // Omvandla till ett värde mellan 0 och 1
    ESP_LOGI(TAG, "LED brightness set to %f", value); // Logga för debugging
}

// Funktion för att uppdatera LED-ljusstyrkan, inklusive sinusvågseffekten
void update(AnalogLed_t *led) {
    TickType_t now = xTaskGetTickCount(); // Hämta nuvarande tid
    TickType_t elapsed = now - led->last_update; // Beräkna hur lång tid som har gått

    if (elapsed > pdMS_TO_TICKS(100)) { // Uppdatera var 100:e millisekund
        led->last_update = now; // Uppdatera senaste tid

        if (led->sinus_active) { // Om sinusvåg är aktiv
            // Beräkna sinusvärdet för LED:ns ljusstyrka
            double angle = (2.0 * M_PI * ((double)(now % pdMS_TO_TICKS(led->period)) / (double)pdMS_TO_TICKS(led->period)));
            double sinus_value = 0.5 * (1.0 + sin(angle)); // Värde mellan 0 och 1

            // Kombinera den fasta ljusstyrkan med sinusvågen
            led->duty_cycle = (led->target_duty_cycle / 255.0) * (1.0 - sinus_value) + sinus_value;

            ESP_LOGI(TAG, "Sinus wave duty cycle: %f", led->duty_cycle); // Logga sinusvågsljusstyrka
        }

        // Uppdatera LED:ns ljusstyrka
        ledc_set_duty(LEDC_LOW_SPEED_MODE, led->timer_channel, (uint32_t)(led->duty_cycle * 255));
        ledc_update_duty(LEDC_LOW_SPEED_MODE, led->timer_channel);

        ESP_LOGI(TAG, "LED duty cycle updated to %f", led->duty_cycle); // Logga uppdaterad ljusstyrka
    }
}

// Funktion för att aktivera sinusvågsläget
void set_sinus_wave(double period, AnalogLed_t *led) {
    led->sinus_active = true; // Aktivera sinusvågen
    led->period = period; // Sätt period för sinusvågen
    ESP_LOGI(TAG, "Sinus wave mode set with period %f ms", period); // Logga period
}
