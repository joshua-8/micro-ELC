#ifndef RELAYS_DRIVER_BASIC_H
#define RELAYS_DRIVER_BASIC_H
#include "RelaysDriver.h"
#include <Arduino.h>
/**
 * @brief This class controls an array of relays in a simple way.
 * @note This class could also work with transistors or MOSFETs, which are better than mechanical relays in terms of switching time and lifetime.
 * It uses GPIO pins, and has no compensation for switching time.
 * @param N how many relays need to be controlled. N must be <=16 (because set() uses a 16 bit variable).
 */
template <uint8_t N>
class RelaysDriverBasic : public RelaysDriver {
    static_assert(N <= 16, "relaysDriverBasic only supports 16 or fewer relays."); // enforce number of relays

protected:
    uint8_t pin[N];
    bool active;

public:
    /**
     * @brief  constructor.
     * @param  _active: do the switches activate on a HIGH or LOW output?
     * @param  pins: {list, of, pins}
     */
    template <typename T, size_t n>
    RelaysDriverBasic(bool _active, const T (&pins)[n])
    {
        // https://stackoverflow.com/a/38679907
        static_assert(n == N, "error: please provide the correct number of pins");
        for (int pinNumber = 0; pinNumber < N; pinNumber++) {
            pin[pinNumber] = pins[pinNumber];
        }

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
            write(relay, setState);
        }
    }
    void write(byte relay, bool setState)
    {
        digitalWrite(pin[relay], setState == active);
    }
};
#endif
