#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void task_led_run(void *param) {

    init_led();

    while(1) {
        printf("Running LED driver \n");
        led_send_frame();

        // vTaskDelay(((1 / updateLEDsFreq) * 1000) / portTICK_PERIOD_MS);
        vTaskDelay(100);
    }

    vTaskDelete(NULL);
}

void init_led() {
    led[0].red = 0;
    led[0].green = 255;
    led[0].blue = 0;

    gpio_set_direction(PIN_NUM_LED_CLK, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_LED_DAT, GPIO_MODE_OUTPUT);

    gpio_set_level(PIN_NUM_LED_CLK, 0);
    gpio_set_level(PIN_NUM_LED_DAT, 0);
}

void led_send_frame() {
    write_led_start_frame();

    for (int i = 0; i < NUM_LEDS; i++){
        write_led(led[i].red, led[i].green, led[i].blue);
    }

    write_led_reset_end_frame();
}

void write_led_byte(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        gpio_set_level(PIN_NUM_LED_DAT, ((value >> i) & 0b1));

        gpio_set_level(PIN_NUM_LED_CLK, 1);
        gpio_set_level(PIN_NUM_LED_CLK, 0);
    }
}

void write_led(uint8_t red, uint8_t green, uint8_t blue) {
    write_led_byte((0xE0 | 31));    // Hardcoded to always have max brightness

    write_led_byte(blue);
    write_led_byte(green);
    write_led_byte(red);
}

void write_led_start_frame() {
    write_led_byte(0x00);
    write_led_byte(0x00);
    write_led_byte(0x00);
    write_led_byte(0x00);
}

void write_led_reset_end_frame() {
    // Reset frame
    write_led_byte(0x00);
    write_led_byte(0x00);
    write_led_byte(0x00);
    write_led_byte(0x00);


    // End frame
    for (int i = 0; i < (NUM_LEDS / 2); i++) {
        write_led_byte(0x00);
    }
}