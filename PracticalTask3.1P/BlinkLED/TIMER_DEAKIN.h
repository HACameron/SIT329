#ifndef TIMER_DEAKIN_H
#define TIMER_DEAKIN_H

#include <stdbool.h>
#include <stdint.h>

class TIMER_DEAKIN {
public:
    bool config_timer(uint8_t timerNum, uint16_t startValue, uint16_t endValue);
    uint16_t getTC_count(uint8_t timerNum);
    void wait(float period_ms);
};

#endif // TIMER_DEAKIN_H
