#include <stdint.h>
#include <stdbool.h>
#include "TIMER_DEAKIN.h"

void enable_timer_clock(uint8_t timer_num) {
  if (timer_num == 0) {
    PM->APBCMASK.reg |= PM_APBCMASK_TCC0;
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_TCC0_TCC1_Val) | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
    while (GCLK->STATUS.bit.SYNCBUSY);
  }
}

uint32_t calculate_ticks(float period, float resolution) {
  return (uint32_t)((period / resolution) * (SystemCoreClock / 1000));
}

bool TIMER_DEAKIN::config_timer(uint8_t timer_num, uint16_t start_count, uint16_t end_count, uint16_t resolution) {
  if (timer_num > 7) return false;
  
  enable_timer_clock(timer_num);

  if (timer_num == 0) {
    TCC0->CTRLA.reg = TCC_CTRLA_PRESCALER_DIV1 | TCC_CTRLA_ENABLE;
    TCC0->PER.reg = calculate_ticks(end_count - start_count, resolution);
    
    TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE;
    while(TCC0->SYNCBUSY.bit.ENABLE);
    return true;
  }
}

uint16_t TIMER_DEAKIN::getTC0_count() {
  return TCC0->COUNT.reg;
}

void TIMER_DEAKIN::wait(uint16_t period) {
  config_timer(0, 0, calculate_ticks(period, 0.1), 0.1);

  while(TCC0->COUNT.reg < TCC0->PER.reg);
}


