/*#include "analog_led.h"
#include "esp_log.h"

// Initierar en AnalogLED_t struktur för att kontrollera en LED
void AnalogLedInit(AnalogLED_t *Aled, int Apin) {
    Aled->Apin = Apin; // Sätt vilken GPIO pin LED:n ska vara ansluten till
    Aled->Avalue = 0; // Sätt startvärde för ljusstyrkan (0 = av)
    Aled->IsSinWave = 0; // Också sätt om vi använder sinusvåg eller inte
    Aled->period = 0; // Period för sinusvåg

    // Konfigurera LEDC timer för PWM
    ledc_timer_config_t LedcTimer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };
    if (ledc_timer_config(&LedcTimer) != ESP_OK) {
        ESP_LOGE("AnalogLed", "Fel vid konfiguration av LEDC-timer");
        return;
    }

    // Konfigurera LEDC kanal för PWM
    ledc_channel_config_t LedcChannel = {
        .channel = LEDC_CHANNEL,
        .duty = 0, // Startvärde för ljusstyrka (0)
        .gpio_num = Apin,
        .speed_mode = LEDC_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER
    };
    if (ledc_channel_config(&LedcChannel) != ESP_OK) {
        ESP_LOGE("AnalogLed", "Fel vid konfiguration av LEDC-kanal");
        return;
    }
}

// Uppdaterar LEDns status baserat på ljusstyrka och eventuell sinusvåg
void AnalogLedUpdate(AnalogLED_t *Aled) {
    if (Aled->period <= 0) return; // Om perioden är 0, gör inget

    uint64_t CurrentTime = esp_timer_get_time(); // Hämtar aktuell tid
    int LedValue = Aled->Avalue; // Standard ljusstyrka

    if (Aled->IsSinWave) { // Om sinusvåg är aktiverad
        int64_t TimeInPeriod = (CurrentTime / 1000) % Aled->period; // Räkna ut tid i perioden
        double angle = (2.0 * M_PI * TimeInPeriod) / Aled->period; // Beräkna sinusvågens vinkel
        LedValue = (int)(Aled->Avalue * (0.5 + 0.5 * sin(angle))); // Beräkna ljusstyrkan baserat på sinusvågen
    }

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LedValue); // Sätt PWM-värdet för LED
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL); // Uppdatera PWM
}

// Sätt ljusstyrka för LED och stäng av sinusvåg
void Analog_set_Led(AnalogLED_t *Aled, int Avalue) {
    Aled->Avalue = Avalue; // Sätt ljusstyrka
    Aled->IsSinWave = 0; // Stäng av sinusvåg
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, Aled->Avalue); // Sätt konstant ljusstyrka
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL); // Uppdatera PWM
}

// Aktivera eller deaktivera sinusvåg för LED
void AnalogSinWave(AnalogLED_t *Aled, int enable, int period) {
    Aled->IsSinWave = enable; // Aktivera eller deaktivera sinusvåg
    if (enable) { // Om sinusvåg är aktiverad, sätt period
        Aled->period = (period <= 0) ? 1000 : period; // Standard till 1000 ms om period är 0
    } else {
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, Aled->Avalue); // Sätt ljusstyrkan när sinusvåg är av
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }
}
*/