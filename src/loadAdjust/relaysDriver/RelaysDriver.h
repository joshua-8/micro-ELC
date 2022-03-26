#ifndef RELAYS_DRIVER_H
#define RELAYS_DRIVER_H
#include <Arduino.h>
/**
 * @brief  This class defines an interface for any class that can control an array of relays.
 */
class RelaysDriver {
public:
    /**
     * @brief activate relays corresponding to a bit that's 1.
     * @note 1 is the LSB, e.g. 0101 turns on the first and third relay.
     * @param  bits: Think of this number as an array of bits. Bits that there is no relay for are ignored.
     * @retval None
     */
    virtual void set(uint16_t bits) = 0;

    /**
     * @brief  this function should be called on startup. It sets up pinmodes.
     * @retval None
     */
    virtual void begin() = 0;
};
#endif
