#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "esp_timer.h"
#include "driver/ledc.h"
#include <math.h>

// Konfiguration för LED och PWM
#define ANALOG_LED_PIN 3                // GPIO som LED är ansluten till
#define LEDC_TIMER LEDC_TIMER_0         // Timer som används av LEDC
#define LEDC_MODE LEDC_LOW_SPEED_MODE   // Låg hastighetsläge för LEDC
#define LEDC_CHANNEL LEDC_CHANNEL_0     // LEDC-kanalen som används
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Upplösning för duty cycle (13 bitar)
#define LEDC_FREQUENCY 5000             // PWM-frekvens (5 kHz)

// Struktur för att hantera en analog LED
typedef struct {
    int Apin;           // GPIO för LED
    int Avalue;         // Ljusstyrka för LED
    int IsSinWave;      // Indikator för sinusvåg (1 aktiverad, 0 inaktiverad)
    int period;         // Period för sinusvåg i millisekunder
} AnalogLED_t;

// Funktioner för att hantera LED
void AnalogLedInit(AnalogLED_t *Aled, int Apin);         // Initiera en LED på en GPIO
void AnalogLedUpdate(AnalogLED_t *Aled);                // Uppdatera LED:s tillstånd
void AnalogSetLed(AnalogLED_t *Aled, int Avalue, int period); // Ställ in ljusstyrka och period
void AnalogSinWave(AnalogLED_t *Aled, int enable, int period); // Aktivera eller inaktivera sinusvåg

#endif
