#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "esp_adc/adc_oneshot.h"

typedef void (*threshold_callback_t)(int adc_pin, int value);

typedef struct {
    int adc_pin;
    int threshold;
    bool rising_edge;
    threshold_callback_t on_threshold;
    adc_oneshot_unit_handle_t adc_handle;
} adc_sensor_t;

void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
int adc_get_value(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, bool risingEdge, threshold_callback_t callback);
void threshold_handler(int pin, int value);
#endif

