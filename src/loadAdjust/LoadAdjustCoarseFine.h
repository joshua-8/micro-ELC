#ifndef LOAD_ADJUST_COARSE_FINE_H
#define LOAD_ADJUST_COARSE_FINE_H
#include "LoadAdjust.h"
#include <Arduino.h>
/**
 * @brief  combines a LoadAdjust that has discrete steps with another LoadAdjust to get more precision
 */
class LoadAdjustCoarseFine : public LoadAdjust {
public:
    LoadAdjust& coarse;
    LoadAdjust& fine;

protected:
    uint16_t numCoarseSteps;
    float maxResistance;
    float fineResistance;

    uint16_t relayValue = 0;
    float relayStepsInFine;

public:
    /**
     * @brief  combines a LoadAdjust that has discrete steps with another LoadAdjust to get more precision
     * @param  _coarse: reference to LoadAdjust object that has discrete steps (the coarse adjust)
     * @param  _fine: reference to LoadAdjust object that can be used for a fine adjust
     * @param  _numCoarseSteps: number of discrete steps the coarse adjust can make
     * @param  _maxResistance: max resistance / lowest load, the value of the first step
     * @param  _fineResistance: max resistance of fine adjust, used to find how many coarse steps the fine adjust can cover
     */
    LoadAdjustCoarseFine(LoadAdjust& _coarse, LoadAdjust& _fine, uint8_t _numCoarseSteps, float _maxResistance, float _fineResistance)
        : coarse(_coarse)
        , fine(_fine)
    {
        numCoarseSteps = _numCoarseSteps;
        maxResistance = _maxResistance;
        fineResistance = _fineResistance;
        relayStepsInFine = maxResistance / fineResistance;
    }
    void setLoad(float load)
    {
        // the fine adjust adds extra load capability, so load is adjusted from [0,1] to a range that exceeds 1.0 to use full capacity
        load = constrain(load, 0.0, 1.0) * (1.0 + relayStepsInFine / numCoarseSteps);
        // if relays could be turned on fractionally ideally we'd want this value
        float fractionalRelayValue = (float)load * numCoarseSteps;

        // change relayValue if necessary
        while (relayValue >= fractionalRelayValue && relayValue > 0) {
            // the relays would be too much resistance
            relayValue--;
        }
        while (relayValue + relayStepsInFine <= fractionalRelayValue && relayValue < numCoarseSteps - 1) {
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
