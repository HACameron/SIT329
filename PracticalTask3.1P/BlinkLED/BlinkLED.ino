#include "GPIO_DEAKIN.h"
#include "TIMER_DEAKIN.h"

// Create instances of GPIO_DEAKIN and TIMER_DEAKIN
GPIO_DEAKIN gpio;
TIMER_DEAKIN timer;

const char LED1_PORT = 'A';
const char LED1_PIN = 21;

const char LED2_PORT = 'A';
const char LED2_PIN = 20;

const char LED3_PORT = 'A';
const char LED3_PIN = 18;

const char DHT_PORT = 'B';
const char DHT_PIN = 10;


void setup() {
    Serial.begin(9600);

    Serial.println("Starting setup...");

    gpio.config_GPIO(LED1_PORT, LED1_PIN, OUTPUT);
    gpio.config_GPIO(LED2_PORT, LED2_PIN, OUTPUT);
    gpio.config_GPIO(LED3_PORT, LED3_PIN, OUTPUT);
    
    timer.config_timer(0, 0, 1000, 0.1);
}

void loop() {
    // Turn the LED on
    gpio.write_GPIO(LED1_PORT, LED1_PIN, HIGH);
    gpio.write_GPIO(LED2_PORT, LED2_PIN, HIGH);
    gpio.write_GPIO(LED3_PORT, LED3_PIN, HIGH);
    Serial.println("All 3 LED to HIGH");

    timer.wait(1000);


    // Turn the LED off
    gpio.write_GPIO(LED1_PORT, LED1_PIN, LOW);
    gpio.write_GPIO(LED2_PORT, LED2_PIN, LOW);
    gpio.write_GPIO(LED3_PORT, LED3_PIN, LOW);
    Serial.println("All 3 LED to LOW");

    timer.wait(1000);
    
}
