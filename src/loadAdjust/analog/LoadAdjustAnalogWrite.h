#ifndef LOAD_ADJUST_ANALOG_WRITE_H
#define LOAD_ADJUST_ANALOG_WRITE_H
#include "../LoadAdjust.h"
#include <Arduino.h>
/**
 * @brief load adjustor that uses analogWrite() to adjust a PWMable load
 */
class LoadAdjustAnalogWrite : public LoadAdjust {
public:
    byte pin;
    bool invert;
    LoadAdjustAnalogWrite(byte _pin, bool _invert = false)
    {
        pin = _pin;
        invert = _invert;
    }
    void setLoad(float load)
    {
        load = constrain(load, 0.0, 1.0);
        if (invert) {
            load = 1.0 - load;
        }
        analogWrite(pin, 255 * load);
    }
    void begin()
    {
        pinMode(pin, OUTPUT);
    }
};

#endif
