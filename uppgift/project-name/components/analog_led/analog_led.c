#include "analog_led.h"
#include "esp_log.h"


// Initierar en struktur av typen AnalogLED_t för att styra en LED
void AnalogLedInit(AnalogLED_t *Aled, int Apin) {
    Aled->Apin = Apin;
    Aled->Avalue = 0;
    Aled->IsSinWave = 0;
    Aled->period = 0;

    // Konfigurera LEDC Timer
    ledc_timer_config_t LedcTimer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };
    if (ledc_timer_config(&LedcTimer) != ESP_OK) {
        ESP_LOGE("AnalogLed", "Fel vid konfigurering av LEDC Timer");
        return;
    }

    // Konfigurera LEDC-kanal
    ledc_channel_config_t LedcChannel = {
        .channel = LEDC_CHANNEL,
        .duty = 0,
        .gpio_num = Apin,
        .speed_mode = LEDC_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER
    };
    if (ledc_channel_config(&LedcChannel) != ESP_OK) {
        ESP_LOGE("AnalogLed", "Fel vid konfigurering av LEDC-kanal");
        return;
    }
}

// Uppdaterar LED-status
void AnalogLedUpdate(AnalogLED_t *Aled) {
    if (Aled->period <= 0) return;

    uint64_t CurrentTime = esp_timer_get_time();
    int LedValue = Aled->Avalue;

    if (Aled->IsSinWave) {
        int64_t TimeInPeriod = (CurrentTime / 1000) % Aled->period;
        double angle = (2.0 * M_PI * TimeInPeriod) / Aled->period;
        LedValue = (int)(Aled->Avalue * (0.5 + 0.5 * sin(angle)));
    }

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LedValue);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

// Ställer in ljusstyrka och period för LED
void AnalogSetLed(AnalogLED_t *Aled, int Avalue) {
    Aled->Avalue = Avalue;
    Aled->IsSinWave = 0; // Stänger av sinusvåg
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, Aled->Avalue); // Ställer in konstant ljusstyrka
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

// Aktiverar/inaktiverar sinusvåg
void AnalogSinWave(AnalogLED_t *Aled, int enable, int period) {
    Aled->IsSinWave = enable;
    if (enable) {
        Aled->period = (period <= 0) ? 1000 : period;
    } else {
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, Aled->Avalue);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }
}
