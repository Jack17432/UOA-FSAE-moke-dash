#ifndef LED_
#define LED_

#include <stdint.h>

// All defined verables to do with the LEDS
#define LED_GLV_LED                     1
#define LED_SHUTDOWN                    2
#define LED_TRACTIVE_SYSTEM             3
#define LED_READY_TO_DRIVE              4

#define LED_ERROR_1                     5
#define LED_ACCUMULATOR_WARN            6
#define LED_INVERTER_WARN               7

#define LED_MOTOR_REAR_LEFT             8
#define LED_MOTOR_FRONT_LEFT            9
#define LED_MOTOR_FRONT_RIGHT           10
#define LED_MOTOR_REAR_RIGHT            11

#define LED_CONTROL_1                   12
#define LED_CONTROL_2                   13
#define LED_ERROR_2                     14

#define LED_BSPD_ERROR                  15
#define LED_AMS_ERROR                   16
#define LED_IMD_ERROR                   17
#define LED_PDOC_ERROR                  18

#define NUM_LEDS                        19

#define PIN_NUM_LED_DAT                 GPIO_NUM_23
#define PIN_NUM_LED_CLK                 GPIO_NUM_22

#define updateLEDsFreq                  60.0

// Structs
struct Led {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led[NUM_LEDS];

// Main task for running LEDs
void task_led_run(void *param);

void init_led();

void led_send_frame();

void write_led_byte(uint8_t);

void write_led(uint8_t, uint8_t, uint8_t);

void write_led_start_frame();

void write_led_reset_end_frame();

#endif