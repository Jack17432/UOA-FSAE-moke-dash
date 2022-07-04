#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led/led.h"

void task_change_led_colour(void *param);

void app_main(void)
{
    xTaskCreate(&task_change_led_colour, "change_led_colour", 2048, NULL, 3, NULL);
    xTaskCreate(&task_led_run, "main_led", 2048, NULL, 3, NULL);
}

void task_change_led_colour(void *param) {
    int led_val = 2;

    while(1) {
        switch (led_val) {
            case 0: 
                led[0].red = 255; 
                led[0].green = 0;
                led[0].blue = 0;

                printf("RED %d\n", led[0].red);
                break;
            
            case 1:
                led[0].red = 0; 
                led[0].green = 255;
                led[0].blue = 0;
                
                printf("GREEN %d\n", led[0].green);
                break;
            
            case 2:
                led[0].red = 0; 
                led[0].green = 0;
                led[0].blue = 255;
                
                printf("BLUE %d\n", led[0].blue);
                break;

        }

        led_val++;
        led_val %= 3;

        vTaskDelay(500);
    }

    vTaskDelete(NULL);
}