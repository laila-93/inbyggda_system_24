/*#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "esp_timer.h"
#include "driver/ledc.h"
#include <math.h>

// LED-konfiguration och PWM
#define ANALOG_LED_PIN 2                // GPIO-pin som LED:n är ansluten till
#define LEDC_TIMER LEDC_TIMER_0         // Timer som används av LEDC
#define LEDC_MODE LEDC_LOW_SPEED_MODE   // Låg hastighet för LEDC
#define LEDC_CHANNEL LEDC_CHANNEL_0     // LEDC-kanal som används
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Upplösning av PWM (13 bitar)
#define LEDC_FREQUENCY 5000             // PWM-frekvens (5 kHz)

// Struktur för att hantera en analog LED
typedef struct {
    int Apin;           // GPIO för LED
    int Avalue;         // LED-ljusstyrka
    int IsSinWave;      // Om sinusvåg är aktiverad (1 = ja, 0 = nej)
    int period;         // Period för sinusvåg i millisekunder
} AnalogLED_t;

// Funktioner för att hantera LED
void AnalogLedInit(AnalogLED_t *Aled, int Apin);         // Initiera LED på en specifik GPIO
void AnalogLedUpdate(AnalogLED_t *Aled);                // Uppdatera LEDns status
void Analog_set_Led(AnalogLED_t *Aled, int Avalue); // Ställ in ljusstyrka och period
void AnalogSinWave(AnalogLED_t *Aled, int enable, int period); // Aktivera eller deaktivera sinusvåg

#endif
*/