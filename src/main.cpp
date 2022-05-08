/**
 * This software is for making an Electronic Load Controller.
 *
 * It controlls an array of resistors to keep the frequency of a synchronous generator constant.
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
LoadAdjustRelayParallelBinary<numRelays> coarseLoadAdjust = LoadAdjustRelayParallelBinary<numRelays>(relayDriver);
LoadAdjustAnalogWrite fineLoadAdjust = LoadAdjustAnalogWrite(18);
LoadAdjustCoarseFine loadAdjust = LoadAdjustCoarseFine(coarseLoadAdjust, fineLoadAdjust, 1, 1, 1);
JEncoderSingleAttachInterrupt tachEncoder = JEncoderSingleAttachInterrupt(27, 1.0, false, 300000, 1000); // pin, dist per count, reverse, slowest interval us, switchbounce us
jENCODER_MAKE_ISR_MACRO(tachEncoder);
TachometerJEncoder tach = TachometerJEncoder(tachEncoder, 4);

float setpoint = 40;
float input = 0;
float output = 0;
QuickPID pidControl = QuickPID(&input, &output, &setpoint);

/**
 * @brief  called once on startup by Arduino
 */
void setup()
{
    Serial.begin(115200);
    coarseLoadAdjust.begin();
    tachEncoder.setUpInterrupts(tachEncoder_jENCODER_ISR);
    pidControl.SetOutputLimits(-.5, .5);
    pidControl.SetSampleTimeUs(20000);
    pidControl.SetTunings(.015, .025, 0);
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
    coarseLoadAdjust.setLoad(output + .5);

    Serial.print(input / setpoint);
    Serial.print(",");
    Serial.print(output + .5);
    Serial.print(",");
    Serial.print(1.0);
    Serial.print(",");

    Serial.println();
    delay(25);
}