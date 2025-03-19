#include "Potentiometer.h" // Inkluderar header-fil för potentiometerhantering
#include "esp_log.h"       // Inkluderar ESP-loggningsbiblioteket

#define TAG "POTENTIOMETER" // Definierar en tagg för loggmeddelanden

// Initierar en mätanordning med tillhörande ADC-konfiguration
void init(MeasurementDevice *device, int adc_pin) {
    device->adc_pin = adc_pin;         // Sätt ADC-pinnumret
    device->current_value = 0;        // Sätt nuvarande värde till 0
    device->previous_value = 0;       // Sätt tidigare värde till 0
    device->threshold = 0;            // Sätt tröskelvärdet till 0
    device->is_rising = true;         // Ange om tröskeln ska vara stigande
    device->threshold_callback = NULL; // Ingen callback-funktion inställd ännu
    device->filter_index = 0;         // Initiera filterindex till 0
    device->is_active = false;        // Ange att enheten är inaktiv
    device->callback_args = NULL;     // Inga callback-argument inställda

    // Konfiguration av ADC-enheten
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1 // Använd ADC-enhet 1
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &device->adc_instance)); // Initiera ADC

    // Konfiguration av ADC-kanal
    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_12,      // Ange attenuering
        .bitwidth = ADC_BITWIDTH_12,  // Ange bitdjup till 12 bitar
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(device->adc_instance, device->adc_pin, &channel_config)); // Konfigurera kanal

    ESP_LOGI(TAG, "ADC initierad på pin: %d", device->adc_pin); // Logga initieringen
}

// Uppdaterar mätvärden för enheten
void updateMeasurementDevice(MeasurementDevice *device) {
    if (!device->is_active) { // Kontrollera om enheten är aktiv
        return; // Avsluta om den inte är aktiv
    }

    int new_value;
    ESP_ERROR_CHECK(adc_oneshot_read(device->adc_instance, device->adc_pin, &new_value)); // Läs nytt värde från ADC

    // Hantera filtervärden för medelvärdesbildning
    if (device->filter_index >= FILTER_SIZE) { 
        device->filter_index = 0; // Nollställ filterindex om det överstiger gränsen
    }
    device->filter_values[device->filter_index] = new_value; // Spara nytt värde i filter
    device->filter_index++;

    // Kontrollera om tröskelvärdet nås och anropa callback vid behov
    if (device->threshold_callback != NULL) {
        if (device->is_rising && device->previous_value < device->threshold && new_value >= device->threshold) {
            device->threshold_callback(device->adc_pin, new_value, device->callback_args);
        } else if (!device->is_rising && device->previous_value > device->threshold && new_value <= device->threshold) {
            device->threshold_callback(device->adc_pin, new_value, device->callback_args);
        }
    }

    // Uppdatera tidigare och nuvarande värden
    device->previous_value = new_value;
    device->current_value = new_value;
}

// Returnerar det senaste mätvärdet
int getValue(MeasurementDevice *device) {
    return device->previous_value; // Returnera det senaste värdet
}

// Konfigurerar tröskelvärde och callback
void setOnThreshold(MeasurementDevice *device, int threshold, bool is_rising, ThresholdCallback callback, void *args) {
    device->threshold = threshold;       // Ställ in tröskelvärdet
    device->is_rising = is_rising;       // Ställ in om det är stigande eller fallande
    device->threshold_callback = callback; // Sätt callback-funktionen
    device->callback_args = args;       // Sätt callback-argument
}

// Aktiverar eller inaktiverar mätanordningen
void activateDevice(MeasurementDevice *device, bool state) {
    device->is_active = state; // Sätt enhetens aktiveringstillstånd
}

// Callback-funktion som körs när tröskelvärdet nås
void threshold_callback(int adc_pin, int value, void *args) {
    printf("Threshold reached on pin %d with value %d\n", adc_pin, value); // Skriv ut meddelande
}
