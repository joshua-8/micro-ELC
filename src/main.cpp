/**
 * This software is for making an Electronic Load Controller.
 *
 * It controls an array of resistors to keep the frequency of a synchronous generator constant.
 *
 * https://github.com/joshua-8/micro-ELC
 *
 * Use PlatformIO to upload to an esp32 dev module
 *
 * started by Joshua in spring 2022
 *
 * */

// include libraries and header files here:
#include "loadAdjust/LoadAdjustCoarseFine.h"
#include "loadAdjust/analog/LoadAdjustAnalogWrite.h"
#include "loadAdjust/relays/LoadAdjustRelayParallelBinary.h"
#include "loadAdjust/relays/RelaysDriverBasic.h"
#include "measurement/TachometerJEncoder.h"
#include <Arduino.h>
#include <QuickPID.h>

// constants
/**
 * @brief  how many relays are in your array?
 * */
const byte numRelays = 5;

// declare instances of objects here:
RelaysDriverBasic<numRelays> relayDriver = RelaysDriverBasic<numRelays>(LOW, { 21, 22, 19, 23, 26 }); // { 16, 17, 18, 19, 21, 22, 23, 26 });
LoadAdjustRelayParallelBinary<numRelays> coarseLoadAdjust = LoadAdjustRelayParallelBinary<numRelays>(relayDriver, false); //driver, activeRelaysIncreaseLoad (true if resistors are through NO, false if through NC)
LoadAdjustAnalogWrite fineLoadAdjust = LoadAdjustAnalogWrite(18);
LoadAdjustCoarseFine loadAdjust = LoadAdjustCoarseFine(coarseLoadAdjust, fineLoadAdjust, pow(2, numRelays), 32, 10); // numCoarseSteps maxResistance fineResistance
JEncoderAS5048bI2C tachEncoder = JEncoderAS5048bI2C(); // JEncoderSingleAttachInterrupt(27, 1.0, false, 100000, 10000); // pin, dist per count, reverse, slowest interval us, switchbounce us
// jENCODER_MAKE_ISR_MACRO(tachEncoder);
TachometerJEncoder tach = TachometerJEncoder(tachEncoder, 3); // num to average

float setpoint = .5;
float input = 0;
float output = 0;
QuickPID pidControl = QuickPID(&input, &output, &setpoint);

/**
 * @brief  called once on startup by Arduino
 */
void setup()
{
    Serial.begin(115200);
    loadAdjust.begin();
    // tachEncoder.setUpInterrupts(tachEncoder_jENCODER_ISR);
    Wire.begin(32, 33);
    pidControl.SetOutputLimits(-.5, .5);
    pidControl.SetSampleTimeUs(20000);
    pidControl.SetTunings(1.80, 4.0, 0);
    pidControl.SetControllerDirection(QuickPID::Action::reverse); // increasing the load slows down the motor
    pidControl.SetMode(QuickPID::Control::automatic); // turn on pid
}

/**
 * @brief  called repeatedly by Arduino
 */
void loop()
{
    tach.run();
    input = tach.getMeasurement();
    pidControl.Compute();
    loadAdjust.setLoad(output + .5);

    Serial.print(input / setpoint);
    Serial.print(",");
    Serial.print(output + .5);
    Serial.print(",");
    Serial.print(1.0);
    Serial.print(",");

    Serial.println();
    delay(25);
}