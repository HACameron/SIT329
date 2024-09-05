#ifndef GPIO_DEAKIN_H
#define GPIO_DEAKIN_H

#include <stdbool.h>
#include <sam.h>

// Define GPIO modes
#define INPUT  0
#define OUTPUT 1

// Define GPIO states
#define LOW  0
#define HIGH 1

// GPIO_DEAKIN class-like structure
class GPIO_DEAKIN{
public:
    bool config_GPIO(char PortNum, char PinNum, char Mode);
    bool write_GPIO(char PortNum, char PinNum, bool State);
    bool read_GPIO(char PortNum, char PinNum);
};

#endif // GPIO_DEAKIN_H
