/**
 * This software is for making an Electronic Load Controller.
 *
 * It uses an array of relays to keep the frequency of a synchronous generator constant.
 *
 * https://github.com/joshua-8/relay-ELC
 *
 * Use PlatformIO to upload to an esp32 dev module
 *
 * by Joshua, spring 2022
 *
 * */

// include libraries and header files here:
#include "loadAdjust/LoadAdjustRelayParallelBinary.h"
#include "loadAdjust/relaysDriver/relaysDriverBasic.h"
#include "measurement/TachometerJEncoder.h"
#include <Arduino.h>

// constants
const byte numRelays = 8;

// declare instances of objects here:
RelaysDriverBasic<numRelays> relayDriver = RelaysDriverBasic<numRelays>(LOW, { 16, 17, 18, 19, 21, 22, 23, 26 });
LoadAdjustRelayParallelBinary<numRelays> loadAdjust = LoadAdjustRelayParallelBinary<numRelays>(relayDriver);

TachometerJEncoder tach = TachometerJEncoder(new JEncoderSingleAttachInterrupt(27, 1.0));

/**
 * @brief  called once on startup by Arduino
 */
void setup()
{
    Serial.begin(115200);
    loadAdjust.begin();
}

/**
 * @brief  called repeatedly by Arduino
 */
void loop()
{
    loadAdjust.setLoad((millis() - 6000.0) / 30000.0);
}