#include <stdint.h>
#include <stdbool.h>
#include "TIMER_DEAKIN.h"

// Base address of the TC registers
#define TC_BASE 0x42002000U

// Timer/Counter registers base address
#define TC_REG_ADDR(num) (TC_BASE + (0x400U * (num)))

// Register offsets
#define TC_CTRLA_OFFSET 0x00U
#define TC_CC0_OFFSET   0x44U
#define TC_COUNT_OFFSET 0x34U

// Access registers
#define TC_CTRLA(num) (*(volatile uint32_t *)(TC_REG_ADDR(num) + TC_CTRLA_OFFSET))
#define TC_CC0(num) (*(volatile uint32_t *)(TC_REG_ADDR(num) + TC_CC0_OFFSET))
#define TC_COUNT(num) (*(volatile uint32_t *)(TC_REG_ADDR(num) + TC_COUNT_OFFSET))

// Timer/Counter Control
#define TC_CTRLA_SWRST (1 << 0) // Software Reset
#define TC_CTRLA_ENABLE (1 << 1) // Enable
#define TC_CTRLA_PRESCALER_DIV1 (0x0U << 8) // Prescaler value: DIV1

bool TIMER_DEAKIN::config_timer(uint8_t timerNum, uint16_t startValue, uint16_t endValue) {
    if (timerNum > 1) return false;
    
    TC_CTRLA(timerNum) = TC_CTRLA_SWRST;
    while (TC_CTRLA(timerNum) & TC_CTRLA_SWRST);

    TC_CTRLA(timerNum) = TC_CTRLA_PRESCALER_DIV1
                       | TC_CTRLA_ENABLE;
    
    TC_CC0(timerNum) = endValue;
    TC_COUNT(timerNum) = startValue;

    TC_CTRLA(timerNum) |= TC_CTRLA_ENABLE;

    return true;
}

uint16_t TIMER_DEAKIN::getTC_count(uint8_t timerNum) {
    if (timerNum > 1) return 0; //
    return TC_COUNT(timerNum);
}

void TIMER_DEAKIN::wait(float period_ms) {
    uint16_t startValue = getTC_count(0);
    uint16_t elapsedTicks = (uint16_t)((period_ms / 0.1) + startValue);
    while (getTC_count(0) < elapsedTicks);
}
