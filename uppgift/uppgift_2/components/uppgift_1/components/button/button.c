#include "button.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void init(Button_t *btn, int pin) {
    btn->pin = pin;
    btn->lastState = false;
    btn->isPressed = false;
    btn->onPressed = NULL;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE

    };

    gpio_config(&io_conf);

}

void button_update(Button_t *btn) {
    static uint32_t lastUpdateTime = 0;
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    if (currentTime - lastUpdateTime < DEBOUNCE_TIME_MS) {
        return;

    }

    lastUpdateTime = currentTime;
    bool currentState = (gpio_get_level(btn->pin) == 0);

    if (currentState != btn->lastState) {
        btn->lastState = currentState;

        if (currentState) {
          btn->isPressed = true;

            if (btn->onPressed) {
                btn->onPressed(btn->pin);
            }

        } else {
            btn->isPressed = false;

        }
    }

}


bool button_isPressed(Button_t *btn) {
    return btn->isPressed;
}

void button_setOnPressed(Button_t *btn, void (*onPressed)(int pin)) {
    btn->onPressed = onPressed;
}

void myButtonCallback(int pin) {
    printf("Button pressed on pin %d\n", pin);

}


