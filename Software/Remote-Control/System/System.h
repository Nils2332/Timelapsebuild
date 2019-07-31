#pragma once

#include <cstdint>

namespace System {

void sendcheck(uint8_t *pData, uint8_t len);

void sendrecieve(uint8_t *pDatain, uint8_t len_i, uint8_t *pDataout, uint8_t len_o);


void print(const char *fmt, ...);

}
