#ifndef RELAYS_DRIVER_BASIC_H
#define RELAYS_DRIVER_BASIC_H
#include "relaysDriver.h"
#include <Arduino.h>
/**
 * @brief This class controls an array of relays in a simple way.
 * @note This is a template class, N is how many relays need to be controlled. N must be <=16
 * It uses GPIO pins, and has no compensation for switching time.
 */
template <uint8_t N>
class RelaysDriverBasic : public RelaysDriver {
    static_assert(N <= 16, "relaysDriverBasic only supports 16 or fewer relays."); // enforce number of relays

protected:
    uint8_t pin[N];
    bool activeHigh;

public:
    RelaysDriverBasic(bool _activeHigh, byte _pins[N])
    {
        activeHigh = _activeHigh;
        for (int i = 0; i < N; i++) {
            pin[i] = _pins[i];
        }
    }
    void begin()
    {
        for (int i = 0; i < N; i++) {
            pinMode(pin[i], OUTPUT);
            digitalWrite(pin[i], !activeHigh); // deactivate
        }
    }
    void set(uint16_t bits)
    {
        for (int relay = 0; relay < N; relay++) {
            bool setState = ((bits >> (relay)) & 1) == activeHigh;
            digitalWrite(pin[relay], setState);
        }
    }
};
#endif
