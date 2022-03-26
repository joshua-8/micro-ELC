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
    bool active;

public:
    RelaysDriverBasic(bool _active, std::initializer_list<byte> pins)
    {
        // https://stackoverflow.com/a/4118050
        assert(pins.size() == N); // number of pins provided in constructor must equal Number of relays
        std::copy(pins.begin(), pins.end(), pin);
        active = _active;
    }
    void begin()
    {
        for (int i = 0; i < N; i++) {
            pinMode(pin[i], OUTPUT);
            digitalWrite(pin[i], !active); // deactivate
        }
    }
    void set(uint16_t bits)
    {
        for (byte relay = 0; relay < N; relay++) {
            bool setState = ((bits >> (relay)) & 1);
            digitalWrite(pin[relay], setState == active);
        }
    }
};
#endif
