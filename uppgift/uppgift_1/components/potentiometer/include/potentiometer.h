#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#define EDGE_RISING  0  // När värdet går upp
#define EDGE_FALLING 1  // När värdet går ner
#define EDGE_BOTH 2     // När det ändras åt båda hållen

#include "esp_adc/adc_oneshot.h"
#include <stdbool.h>

typedef void (*threshold_callback_t)(int adc_pin, int value, int edge_type);

// Vår struktur som håller koll på potentiometerns värde
typedef struct {
    int adc_pin;
    int threshold;
    int edge_type;
    int previous_value;
    bool threshold_crossed;
    threshold_callback_t on_threshold;
    adc_oneshot_unit_handle_t adc_handle;
} adc_sensor_t;

// Funktioner vi kan använda
void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
int adc_get_value(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, int edge_type, threshold_callback_t callback);
void threshold_handler(int pin, int value, int edge_type);

#endif
