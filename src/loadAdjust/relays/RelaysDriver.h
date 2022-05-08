#ifndef RELAYS_DRIVER_H
#define RELAYS_DRIVER_H
#include <Arduino.h>
/**
 * @brief  This class defines an interface for any class that can control an array of relays.
 * @note I use the term "relay," loosely. Solid-state components that can switch power (transistors, triacs and mosfets) are actually better since they can switch faster and last longer.
 */
class RelaysDriver {
public:
    /**
     * @brief activate relays corresponding to a bit that's 1.
     * @note 1 is the LSB, e.g. 001 turns on the first relay.
     * @param  bits: Think of this number as an array of bits. Bits that there is no relay for are ignored.
     */
    virtual void set(uint16_t bits) = 0;

    /**
     * @brief  this function should be called on startup. It sets up pinmodes.
     */
    virtual void begin() = 0;
};
#endif
