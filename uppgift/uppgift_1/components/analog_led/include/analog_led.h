#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Struktur som håller all information om LED:ns tillstånd
typedef struct {
    int pin;               // Pin-nummer där LED:en är kopplad
    int timer_channel;     // LED-timer kanal
    TickType_t last_update; // Tidpunkt för senaste uppdatering
    double period;         // Period för sinusvågen
    double duty_cycle;     // LED:ns nuvarande ljusstyrka (0 till 1)
    double target_duty_cycle; // Målvärde för fast ljusstyrka
    bool sinus_active;     // Om sinusvågen är aktiv eller inte
} AnalogLed_t;

// Funktionsprototyper
void init(int pin, AnalogLed_t *led);
void update(AnalogLed_t *led);
void setLed(double value, AnalogLed_t *led);
void set_sinus_wave(double period, AnalogLed_t *led);

#endif
