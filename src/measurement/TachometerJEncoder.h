#ifndef TACHOMETER_JENCODER_H
#define TACHOMETER_JENCODER_H
#include "JEncoder/JEncoder.h"
#include "Measurement.h"
#include <Arduino.h>
/**
 * @brief  This class measures the speed of a generator using a tachometer.
 * @note you may use any of [these encoders](https://joshua-8.github.io/JMotor/class_j_encoder.html).
 **/
class TachometerJEncoder : public Measurement {
public:
    JEncoder* encoder;
    TachometerJEncoder(JEncoder* _encoder)
        : encoder(_encoder)
    {
    }

    float getMeasurement()
    {
        return encoder->getVel();
    }
    void run()
    {
        encoder->run();
    }
};
#endif
