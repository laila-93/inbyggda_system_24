#include "analog_led.h"
#include <math.h> // För matematiska funktioner

#define PI 3.14159265

// Funktion för att initiera LED
void AnalogLed_init(AnalogLed *led, int gpio_pin) {
    // Konfigurera timer för LEDC
    ledc_timer_config_t ledcTimerConfig = {
        .duty_resolution = LEDC_TIMER_12_BIT,
        .freq_hz = 1000, // Frekvens på PWM-signalen
        .speed_mode = LEDC_LOW_SPEED_MODE, // Låg hastighetsläge
        .timer_num = LEDC_TIMER_0, // Timer nummer
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledcTimerConfig);

    // Konfigurera kanal för LEDC
    ledc_channel_config_t ledcChannelConfig = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0, // Start duty cycle på 0
        .gpio_num = gpio_pin, // GPIO-pinne för LED
        .hpoint = 0,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .flags.output_invert = 0
    };
    ledc_channel_config(&ledcChannelConfig);

    led->ledc_channel = ledcChannelConfig;
    led->period = 0;
    led->angle = 0.0;
    led->last_update = xTaskGetTickCount();
}

// Funktion för att uppdatera LED (används för sinusvåg)
void AnalogLed_update(AnalogLed *led) {
    if (led->period > 0) {
        TickType_t current_time = xTaskGetTickCount();
        if ((current_time - led->last_update) >= pdMS_TO_TICKS(led->period / 100)) {
            led->last_update = current_time;
            led->angle += 2 * PI / 100; // Öka vinkeln för att skapa sinusvåg
            if (led->angle >= 2 * PI) {
                led->angle -= 2 * PI; // Återställ vinkeln om den överstiger 2*PI
            }
            int duty = (int)((sin(led->angle) * 2048) + 2048); // Beräkna ljusstyrkan med hjälp av sinusvåg
            AnalogLed_setLed(led, duty);
        }
    }
}

// Funktion för att sätta LED-ljusstyrka
void AnalogLed_setLed(AnalogLed *led, int value) {
    ledc_set_duty(led->ledc_channel.speed_mode, led->ledc_channel.channel, value);
    ledc_update_duty(led->ledc_channel.speed_mode, led->ledc_channel.channel);
}

// Funktion för att ställa in perioden för sinusvåg för LED
void AnalogLed_setPeriod(AnalogLed *led, int period) {
    led->period = period; // Ställ in perioden för sinusvågen
    led->angle = 0.0; // Återställ vinkeln
}
