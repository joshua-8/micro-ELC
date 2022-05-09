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
    bool activeRelaysIncreaseLoad;
    /**
     * @brief  load adjustor that switches relays or other switches on and off in a binary pattern
     * @param  _relaysDriver: RelaysDriver for controlling relays or other switches
     * @param  _activeRelaysIncreaseLoad: (bool)
     */
    LoadAdjustRelayParallelBinary(RelaysDriver& _relaysDriver, bool _activeRelaysIncreaseLoad = false)
        : driver(_relaysDriver)
    {
        activeRelaysIncreaseLoad = _activeRelaysIncreaseLoad;
    }
    void setLoad(float load)
    {
        uint16_t setting = constrain(load, 0.0, 1.0) * ((1 << N) - 1); // convert [0.0, 1.0] to [0, 2^n-1]
        if (!activeRelaysIncreaseLoad) { // if active relays decrease the load (open the circuit to a resistor)
            setting = ~setting; // then a load of 1 should turn off all relays, and a load of 0 should activate all the relays
        }
        driver.set(setting);
    }
    void begin()
    {
        driver.begin();
    }
};
#endif