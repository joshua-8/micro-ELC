#ifndef MEASUREMENT_H
#define MEASUREMENT_H
// Defines an interface for measuring the frequency, rotational speed, or voltage of a generator to use as the input to the control loop.
class Measurement {
public:
    /**
     * @brief Use this method to get the most recent measurement on the speed of the generator.
     * @retval measurement (float)
     */
    virtual float getMeasurement() = 0;
    /**
     * @brief  call this in loop() since some forms of measurement may need to be constantly polled
     */
    virtual void run() = 0;
};
#endif
