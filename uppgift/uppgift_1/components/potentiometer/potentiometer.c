#include "hal/adc_types.h"        
#include "potentiometer.h"         
#include "esp_adc/adc_oneshot.h"    
#include "esp_log.h"               

static const char *TAG = "ADC_SENSOR";  // Namn för att logga meddelanden i terminalen

// Funktion som sätter upp vår sensor
void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;  // Vi sparar vilken pin vi använder
    sensor->threshold = 2000;   // Vi säger att tröskeln är 2000
    sensor->on_threshold = NULL; // Ingen funktion används än
    sensor->edge_type = EDGE_BOTH;  // Vi vill upptäcka både när värdet går upp och ner

    // Skapa en ADC-enhet
    adc_oneshot_unit_init_cfg_t adc_config = {
        .unit_id = ADC_UNIT_1,   // Vi använder ADC-enhet nummer 1
        .clk_src = ADC_DIGI_CLK_SRC_DEFAULT  // Standardklocka för att läsa värdet
    };
    adc_oneshot_new_unit(&adc_config, &sensor->adc_handle);  // Startar ADC-enheten

    // Ställer in hur vi ska läsa värdet
    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,  // Hur noggrant vi läser värdet
        .atten = ADC_ATTEN_DB_12  // Hur känsligt det ska vara
    };
    adc_oneshot_config_channel(sensor->adc_handle, sensor->adc_pin, &channel_config);
    
    ESP_LOGI(TAG, "ADC initialized on pin %d", adc_pin);  // Skriver ut i terminalen att vi är redo
}

// Funktion som läser av värdet
void adc_update(adc_sensor_t *sensor) {
    int value;  // Skapar en plats att spara värdet i
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);  // Läser värdet från potentiometern

    // Första gången vi läser, sparar vi bara värdet och gör inget mer
    if (sensor->previous_value == -1) {
        sensor->previous_value = value;
        return;
    }

    // Om vi har sagt att vi ska reagera på tröskelvärden
    if (sensor->on_threshold) {
        if (value > sensor->threshold && !sensor->threshold_crossed) {
            sensor->on_threshold(sensor->adc_pin, value, EDGE_RISING);  // Om värdet går över tröskeln
            sensor->threshold_crossed = true;
        } else if (value < sensor->threshold && sensor->threshold_crossed) {
            sensor->on_threshold(sensor->adc_pin, value, EDGE_FALLING);  // Om värdet går under tröskeln
            sensor->threshold_crossed = false;
        }
    }
    sensor->previous_value = value;  // Sparar det nya värdet
}

// Hämtar det senaste värdet från sensorn
int adc_get_value(adc_sensor_t *sensor) {
    int value;  // Skapar en plats för att spara sensorns värde
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);  // Läser av värdet från sensorn
    return value;  // Skickar tillbaka värdet så att det kan användas någon annanstans
}

// Funktion för att sätta ett nytt tröskelvärde och koppla en funktion till det
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, int edge_type, threshold_callback_t callback) {
    sensor->threshold = threshold;  // Sätter en gräns för när något ska hända, t.ex. 2000
    sensor->edge_type = edge_type;  // Väljer om vi ska reagera på stigande eller fallande värde
    sensor->on_threshold = callback;  // Sparar funktionen som ska köras när gränsen passeras
}

// Funktion som körs när värdet passerar tröskeln
void threshold_handler(int pin, int value, int edge_type) {
    if (edge_type == EDGE_RISING) {  // Om värdet har gått upp över tröskeln
        printf("Värdet på pin %d ökade! Nytt värde: %d\n", pin, value);  // Skriver ut ett meddelande
    } else if (edge_type == EDGE_FALLING) {  // Om värdet har gått ner under tröskeln
        printf("Värdet på pin %d minskade! Nytt värde: %d\n", pin, value);  // Skriver ut ett meddelande
    }
}
