#include <stdio.h>
#include "esp_log.h"



//callback
const char *TAG = "CALLBACK";

void function_1();
void function_2();
void function_3();

void(*my_function_pointer_f)(void);

my_function_pointer_f my_function_pointer;


void app_main(void)
{
    printf("Starting Main\n");
    my_function_pointer = function_1;
    my_function_pointer();
    my_function_pointer = function_2;
    my_function_pointer();

    function_1();
    function_2();
    function_3();

}
