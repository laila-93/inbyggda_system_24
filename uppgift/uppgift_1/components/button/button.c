
#include "button.h"

#define BUTTON_PIN GPIO_NUM_4

void init();
void update();
bool ispressed();

void setOnPressed ( void (*onPressed)(int pin) );