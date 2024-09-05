#ifndef TIMER_DEAKIN_H
#define TIMER_DEAKIN_H

#include <stdbool.h>
#include <stdint.h>
#include <samd.h>

class TIMER_DEAKIN {
public:
    bool config_timer(uint8_t timer_num, uint16_t start_count, uint16_t end_count, uint16_t resolution);
    uint16_t getTC0_count();
    // Add other timer count getter methods as needed
    void wait(uint16_t period); // Period in 0.1ms
};

#endif // TIMER_DEAKIN_H
