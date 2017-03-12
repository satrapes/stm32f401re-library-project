#ifndef UTILS_H
#define UTILS_H
#include "stm32f4xx.h"
#include "IO.h"

#include <stdbool.h>
#include <assert.h>

/**
 * @brief Set a bitmask in a register
 * @param reg_address Address of register that we want to set a bit on
 * @param bit_mask Bitmask that we want to set
 * @return bool 0 if set bit failed and 1 if it succeeded
 */
bool __setBitMask(ioAddress *reg_address, uint32_t bit_mask);

#endif /* UTILS_H */
