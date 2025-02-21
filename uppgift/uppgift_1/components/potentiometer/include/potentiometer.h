#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "driver/adc.h" // Inkluderar ADC-drivrutinen

typedef struct {
    adc1_channel_t adc_channel; // ADC-kanal för potentiometern
    int threshold; // Tröskelvärde
    bool threshold_reached; // Flagga för att indikera om tröskeln har uppnåtts
    void (*onThreshold)(int adc, int value); // Funktion som kallas vid tröskelvärde
} Potentiometer;

// Funktion för att initiera potentiometern
void Potentiometer_init(Potentiometer *pot, adc1_channel_t adc_channel);

// Funktion för att uppdatera potentiometerns värde
void Potentiometer_update(Potentiometer *pot);

// Funktion för att hämta potentiometerns värde
int Potentiometer_getValue(Potentiometer *pot);

// Funktion för att sätta tröskelvärde och callback-funktion
void Potentiometer_setOnThreshold(Potentiometer *pot, int threshold, void (*onThreshold)(int adc, int value));

#endif // POTENTIOMETER_H
