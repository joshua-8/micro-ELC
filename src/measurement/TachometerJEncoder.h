#ifndef TACHOMETER_JENCODER_H
#define TACHOMETER_JENCODER_H
#include "JEncoder/JEncoder.h" //from JMotor library
#include "Measurement.h"
#include <Arduino.h>
#include <RunningAverage.h>
/**
 * @brief  This class measures the speed of a generator using a tachometer.
 * @note you may use any of [these encoders](https://joshua-8.github.io/JMotor/class_j_encoder.html).
 **/
class TachometerJEncoder : public Measurement {
private:
    float vel = 0;
    RunningAverage smoother;

public:
    JEncoder& encoder;
    TachometerJEncoder(JEncoder& _encoder, uint16_t numSavedForSmoothing = 0)
        : smoother(numSavedForSmoothing + 1)
        , encoder(_encoder)
    {
    }

    float getMeasurement()
    {
        return smoother.getAverage();
    }
    void run()
    {
        encoder.run();
        smoother.addValue(encoder.getVel());
    }
};
#endif
