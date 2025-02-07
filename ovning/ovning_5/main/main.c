#include <stdio.h>
#include "driver/uart.h"
#include "hal/uart_types.h"
#include "soc/uart_channel.h"


void app_main(void)
{ 
    const uart_port_t uart_num = UART_NUM_1;
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,  
    .rx_flow_ctrl_thresh = 122,

    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));


    do{
         // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, 2, 3, 16, 18)); 

    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, uart_buffer_size,
                                            uart_buffer_size, 10, &uart_queue, 0));

    } while (1); 


}