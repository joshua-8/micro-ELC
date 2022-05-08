#ifndef LOAD_ADJUST_RELAY_PARALLEL_BINARY_H
#define LOAD_ADJUST_RELAY_PARALLEL_BINARY_H
#include "../LoadAdjust.h"
#include "RelaysDriver.h"
#include <Arduino.h>
/**
 * @brief load adjustor that switches relays or other switches on and off in a binary pattern
 * @note  this is a template class, N is how many relays are used.
 */
template <byte N>
class LoadAdjustRelayParallelBinary : public LoadAdjust {
public:
    RelaysDriver& driver;
    LoadAdjustRelayParallelBinary(RelaysDriver& _relaysDriver)
        : driver(_relaysDriver)
    {
    }
    void setLoad(float load)
    {
        uint16_t setting = constrain(load, 0.0, 1.0) * ((1 << N) - 1); // convert [0.0, 1.0] to [0, 2^n-1]
        driver.set(setting);
    }
    void begin()
    {
        driver.begin();
    }
};
#endif