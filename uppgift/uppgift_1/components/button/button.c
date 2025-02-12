
#include "button.h"

#define BUTTON_PIN GPIO_NUM_12

void init();
void update();
bool ispressed();

void setOnPressed ( void (*onPressed)(int pin) );