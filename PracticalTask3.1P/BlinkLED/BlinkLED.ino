#include "GPIO_DEAKIN.h"
#include "TIMER_DEAKIN.h"

// Create instances of GPIO_DEAKIN and TIMER_DEAKIN
GPIO_DEAKIN gpio;
TIMER_DEAKIN timer;

const char LED_PORT = 'A';
const char LED_PIN = 21;

void setup() {
    Serial.begin(9600);

    Serial.println("Starting setup...");

    gpio.config_GPIO(LED_PORT, LED_PIN, OUTPUT);
    
    timer.config_timer(0, 0, 500);
}

void loop() {
    // Turn the LED on
    gpio.write_GPIO(LED_PORT, LED_PIN, HIGH);
    Serial.println("Set PA21 to HIGH");

    // Wait for 500ms (500 * 10 * 0.1ms)
    timer.wait(500);

    // Turn the LED off
    gpio.write_GPIO(LED_PORT, LED_PIN, LOW);
    Serial.println("Set PA21 to LOW");

    // Wait for 500ms
    timer.wait(500);
}
