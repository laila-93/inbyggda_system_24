#include "hal/adc_types.h"        
#include "potentiometer.h"         
#include "esp_adc/adc_oneshot.h"    
#include "esp_log.h"               
static const char *TAG = "ADC_SENSOR";  // Definierar en etikett för loggar (för felsökning)

// Funktion som sätter upp ADC-sensorn
void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;  // Säger vilken pin (kanal) som ska användas
    sensor->threshold = 2000;   // Sätter ett tröskelvärde på 2000
    sensor->on_threshold = NULL; // Ingen funktion för tröskel hantering än
    sensor->edge_type = EDGE_BOTH;  // Både stigande och fallande kant kan upptäckas

    // Konfiguration för ADC-enheten
    adc_oneshot_unit_init_cfg_t adc_config = {
        .unit_id = ADC_UNIT_1,      // Sätter ADC-enhetens ID till 1
        .clk_src = ADC_DIGI_CLK_SRC_DEFAULT  // Sätter klockkällan till standard
    };
    adc_oneshot_new_unit(&adc_config, &sensor->adc_handle);  // Skapar en ny ADC-enhet

    // Konfiguration för ADC-kanalen (kanalens inställningar)
    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,  // Sätter standard bitdjup
        .atten = ADC_ATTEN_DB_12  // Sätter förstärkning till 12 dB
    };
    adc_oneshot_config_channel(sensor->adc_handle, sensor->adc_pin, &channel_config);  // Konfigurerar kanalen på ADC

    ESP_LOGI(TAG, "ADC initialized on pin %d", adc_pin);  // Skriver ut logginformation om att ADC är initialiserad
}

// Funktion som uppdaterar ADC-värdet och kollar om tröskeln överskrids
void adc_update(adc_sensor_t *sensor) {
    int value;  // Variabel för att spara det lästa värdet från ADC
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);  // Läser ADC-värdet från den definierade pinnen

    if (sensor->previous_value == -1) {  // Om det är första gången sensorn läser ett värde
        sensor->previous_value = value;  // Spara det första värdet
        return;  // Avsluta utan att göra mer
    }

    // Om en funktion har definierats för att hantera när tröskeln överskrids
    if (sensor->on_threshold) {
        // Om värdet är större än tröskeln och vi inte redan har passerat den
        if (value > sensor->threshold && !sensor->threshold_crossed) {
            sensor->on_threshold(sensor->adc_pin, value, EDGE_RISING);  // Anropar funktionen för stigande kant
            sensor->threshold_crossed = true;  // Markerar att tröskeln har överskridits
        } 
        // Om värdet är mindre än tröskeln och vi tidigare passerade den
        else if (value < sensor->threshold && sensor->threshold_crossed) {
            sensor->on_threshold(sensor->adc_pin, value, EDGE_FALLING);  // Anropar funktionen för fallande kant
            sensor->threshold_crossed = false;  // Markerar att tröskeln inte längre är överskriden
        }
    }

    sensor->previous_value = value;  // Uppdatera det tidigare värdet med det nya värdet
}

// Hämtar det senaste värdet från ADC
int adc_get_value(adc_sensor_t *sensor) {
    int value;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);  // Läser det senaste ADC-värdet
    return value;  // Returnerar värdet
}

// Sätter tröskelvärdet och definierar en funktion som körs när tröskeln överskrids
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, int edge_type, threshold_callback_t callback) {
    sensor->threshold = threshold;  // Sätt tröskelvärdet
    sensor->edge_type = edge_type;  // Sätt om vi ska kolla för stigande eller fallande kant
    sensor->on_threshold = callback;  // Sätt den funktion som ska anropas när tröskeln överskrids
}

// Funktion som körs när tröskeln överskrids
void threshold_handler(int pin, int value, int edge_type) {
    // Om tröskeln passeras vid stigande kant
    if (edge_type == EDGE_RISING) {
        printf("Rising Edge Reached on ADC pin %d! Value: %d\n", pin, value);
    } 
    // Om tröskeln passeras vid fallande kant
    else if (edge_type == EDGE_FALLING) {
        printf("Falling Edge Reached on ADC pin %d! Value: %d\n", pin, value);
    }
}
