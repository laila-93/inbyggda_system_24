#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

// Definiera olika typer av kanter: stigande, fallande eller båda
#define EDGE_RISING  0  // Stigande kant
#define EDGE_FALLING 1  // Fallande kant
#define EDGE_BOTH 2    // Både stigande och fallande kant

#include "esp_adc/adc_oneshot.h"  // Inkluderar ADC-relaterade funktioner
#include <stdbool.h>  // Inkluderar en typ för booleska värden (sant/falskt)

// Definierar en funktionstyp som ska användas som callback när tröskeln överskrids
typedef void (*threshold_callback_t)(int adc_pin, int value, int edge_type);

// Struktur som representerar en ADC-sensor
typedef struct {
    int adc_pin;           // Vilken pin (kanal) som används för att läsa ADC-värden
    int threshold;         // Tröskelvärdet
    int edge_type;         // Typ av kant (stigande eller fallande)
    int previous_value;    // Det senaste lästa värdet från ADC
    bool threshold_crossed;  // Om tröskeln har överskridits
    threshold_callback_t on_threshold;  // Funktion som anropas när tröskeln överskrids
    adc_oneshot_unit_handle_t adc_handle;  // Handtag för ADC-enheten
} adc_sensor_t;

// Funktioner som ska användas för att hantera ADC
void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
int adc_get_value(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, int edge_type, threshold_callback_t callback);
void threshold_handler(int pin, int value, int edge_type);

#endif
