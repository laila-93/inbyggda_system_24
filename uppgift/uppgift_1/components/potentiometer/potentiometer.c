#include "potentiometer.h"

// Funktion för att initiera potentiometern
void Potentiometer_init(Potentiometer *pot, adc1_channel_t adc_channel) {
    pot->adc_channel = adc_channel;
    pot->threshold = 0;
    pot->threshold_reached = false; // Initialisera flaggan till false
    pot->onThreshold = NULL;

    // Konfigurera ADC-kanalen
    adc1_config_width(ADC_WIDTH_BIT_12); // 12-bitars bredd
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_0); // Ingen dämpning
}

// Funktion för att uppdatera potentiometerns värde
void Potentiometer_update(Potentiometer *pot) {
    int raw_value = adc1_get_raw(pot->adc_channel); // Läs råvärdet från ADC-kanalen
    int scaled_value = raw_value % 4096; // Skala värdet till 0-4095 (12-bitars upplösning)

    if (pot->onThreshold != NULL) {
        if (!pot->threshold_reached && scaled_value >= pot->threshold) {
            pot->onThreshold((int)pot->adc_channel, scaled_value);
            pot->threshold_reached = true; // Sätt flaggan till true
        } else if (pot->threshold_reached && scaled_value < pot->threshold) {
            pot->threshold_reached = false; // Återställ flaggan till false när värdet går under tröskeln
        }
    }
}

// Funktion för att hämta potentiometerns värde
int Potentiometer_getValue(Potentiometer *pot) {
    int raw_value = adc1_get_raw(pot->adc_channel); // Läs råvärdet från ADC-kanalen
    return raw_value % 4096; // Skala värdet till 0-4095 (12-bitars upplösning)
}

// Funktion för att sätta tröskelvärde och callback-funktion
void Potentiometer_setOnThreshold(Potentiometer *pot, int threshold, void (*onThreshold)(int adc, int value)) {
    pot->threshold = threshold;
    pot->onThreshold = onThreshold;
    pot->threshold_reached = false; // Initialisera flaggan till false
}
