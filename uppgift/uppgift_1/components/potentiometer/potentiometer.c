#include "hal/adc_types.h"
#include "potentiometer.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

static const char *TAG = "ADC_SENSOR";

void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;
    sensor->threshold = 0;
    sensor->on_threshold = NULL;
    sensor->rising_edge = true;

    adc_oneshot_unit_init_cfg_t adc_config = {
        .unit_id = ADC_UNIT_1,
        .clk_src = ADC_DIGI_CLK_SRC_DEFAULT
    };
    adc_oneshot_new_unit(&adc_config, &sensor->adc_handle);

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12
    };
    adc_oneshot_config_channel(sensor->adc_handle, sensor->adc_pin, &channel_config);

    ESP_LOGI(TAG, "ADC initialized on pin %d", adc_pin);
}

void adc_update(adc_sensor_t *sensor) {
    int value;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);

    ESP_LOGI(TAG, "ADC Value: %d", value);

    if (sensor->on_threshold) {
        if (sensor->rising_edge && value > sensor->threshold) {
            sensor->on_threshold(sensor->adc_pin, value);
        } else if (!sensor->rising_edge && value < sensor->threshold) {
            sensor->on_threshold(sensor->adc_pin, value);
        }
    }
}

int adc_get_value(adc_sensor_t *sensor) {
    int value;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);
    return value;
}

void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, bool risingEdge, threshold_callback_t callback) {
    sensor->threshold = threshold;
    sensor->rising_edge = risingEdge;
    sensor->on_threshold = callback;
}
void threshold_handler(int pin, int value) {
    printf(" Threshold reached on ADC pin %d! Value: %d\n", pin, value);
}
