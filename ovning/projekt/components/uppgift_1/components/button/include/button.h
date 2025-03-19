*#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#define BUTTON_PIN GPIO_NUM_2
#define DEBOUNCE_TIME_MS 50


typedef struct {
    int pin;
    bool lastState;
    bool isPressed;
    void (*onPressed)(int pin);

} Button_t;

void init(Button_t *btn, int pin);
void button_update(Button_t *btn);
bool button_isPressed(Button_t *btn);
void button_setOnPressed(Button_t *btn, void (*onPressed)(int pin));
void myButtonCallback(int pin);

#endif

