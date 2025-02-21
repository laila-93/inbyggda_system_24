#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/ledc.h" // Inkludera LEDC-drivrutinen för PWM
#include "freertos/FreeRTOS.h" // Inkludera FreeRTOS
#include "freertos/task.h" // Inkludera FreeRTOS-tasks

typedef struct {
    ledc_channel_config_t ledc_channel; // LEDC-konfiguration för PWM-kanal
    int period; // Period för sinusvåg
    float angle; // Aktuell vinkel för sinusvåg
    TickType_t last_update; // Tidpunkt för senaste uppdatering
} AnalogLed;

// Funktion för att initiera LED
void AnalogLed_init(AnalogLed *led, int gpio_pin);

// Funktion för att uppdatera LED (används för sinusvåg)
void AnalogLed_update(AnalogLed *led);

// Funktion för att sätta LED-ljusstyrka
void AnalogLed_setLed(AnalogLed *led, int value);

// Funktion för att ställa in sinusvåg för LED
void AnalogLed_setPeriod(AnalogLed *led, int period);

#endif // ANALOG_LED_H
