#ifndef LOAD_ADJUST_COARSE_FINE_H
#define LOAD_ADJUST_COARSE_FINE_H
#include "LoadAdjust.h"
#include <Arduino.h>
class LoadAdjustCoarseFine : public LoadAdjust {
public:
    LoadAdjust& coarse;
    LoadAdjust& fine;

private:
    uint8_t numRelays;
    float minRelayResistance;
    float fineResistance;

    uint16_t relayValue = 1;

    float relayStepsInFine = pow(2, numRelays) / fineResistance;

public:
    LoadAdjustCoarseFine(LoadAdjust& _coarse, LoadAdjust& _fine)
        : coarse(_coarse)
        , fine(_fine)
    {
    }
    void setLoad(float load)
    {
        load = constrain(load, 0.0, 1.0);
        // if relays could be turned on fractionally ideally we'd want this value
        float fractionalRelayValue = (float)load * pow(2, numRelays);

        // change relayValue if necessary
        while (relayValue >= fractionalRelayValue && relayValue > 0) {
            // the relays would be too much resistance
            relayValue--;
        }
        while (relayValue + relayStepsInFine <= fractionalRelayValue && relayValue < pow(2, numRelays)) {
            // the fine control + the relays can't reach high enough
            relayValue++;
        }
        float leftover = fractionalRelayValue - relayValue; // the fine adjust needs to make up for this much
        coarse.setLoad(relayValue);
        fine.setLoad(leftover / relayStepsInFine);
    }
    void begin()
    {
        coarse.begin();
        fine.begin();
    }
};
#endif
