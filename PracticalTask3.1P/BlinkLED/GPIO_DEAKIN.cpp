#include "GPIO_DEAKIN.h"
#include <stdint.h>

// Base address of the PORT registers
#define PORT_BASE 0x41004400U

// Calculate PORT register base address for a specific group
#define PORT_GROUP_ADDR(group) (PORT_BASE + (0x80U * (group)))

// Register offsets
#define PORT_OUT_OFFSET  0x10U
#define PORT_IN_OFFSET   0x20U
#define PORT_DIR_OFFSET  0x00U

// Access registers
#define PORT_OUT(group)   (*(volatile uint32_t *)(PORT_GROUP_ADDR(group) + PORT_OUT_OFFSET))
#define PORT_IN(group)    (*(volatile uint32_t *)(PORT_GROUP_ADDR(group) + PORT_IN_OFFSET))
#define PORT_DIR(group)   (*(volatile uint32_t *)(PORT_GROUP_ADDR(group) + PORT_DIR_OFFSET))

// Convert port character to group index
static int get_port_group(char PortNum) {
    switch (PortNum) {
        case 'A': return 0;
        case 'B': return 1;
        default: return -1; // Invalid port
    }
}

// Implementation of the Config_GPIO method
bool GPIO_DEAKIN::config_GPIO(char PortNum, char PinNum, char Mode) {
    int group = get_port_group(PortNum);
    if (group < 0 || PinNum > 31) return false; // Invalid port or pin number

    // Configure pin direction
    if (Mode == OUTPUT) {
        PORT_DIR(group) |= (1 << PinNum); // Set bit to 1 for output
    } else if (Mode == INPUT) {
        PORT_DIR(group) &= ~(1 << PinNum); // Clear bit to 0 for input
    } else {
        return false; // Invalid mode
    }

    return true;
}

// Implementation of the Write_GPIO method
bool GPIO_DEAKIN::write_GPIO(char PortNum, char PinNum, bool State) {
    int group = get_port_group(PortNum);
    if (group < 0 || PinNum > 31) return false; // Invalid port or pin number

    // Set or clear pin
    if (State == HIGH) {
        PORT_OUT(group) |= (1 << PinNum); // Set bit to 1
    } else if (State == LOW) {
        PORT_OUT(group) &= ~(1 << PinNum); // Clear bit to 0
    } else {
        return false; // Invalid state
    }

    return true;
}

// Implementation of the Read_GPIO method
bool GPIO_DEAKIN::read_GPIO(char PortNum, char PinNum) {
    int group = get_port_group(PortNum);
    if (group < 0 || PinNum > 31) return false; // Invalid port or pin number

    // Read pin state
    return (PORT_IN(group) & (1 << PinNum)) ? HIGH : LOW;
}
