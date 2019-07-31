#pragma once

#include <cstdint>
#include "adc.h"

namespace System {

void analogRead(uint32_t channel, ADC_HandleTypeDef* ADC_handle, uint16_t *adc_data, uint8_t samples);

void print(const char *fmt, ...);

}
