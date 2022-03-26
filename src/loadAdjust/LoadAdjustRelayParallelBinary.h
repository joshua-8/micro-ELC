#ifndef _LOAD_ADJUST_RELAY_H_
#define _LOAD_ADJUST_RELAY_H_
#include "loadAdjust.h"
#include <Arduino.h>
/**
 * @brief
 * @note  this is a template class, N is how many relays are used.
 * @retval None
 */
template <byte N>
class LoadAdjustRelayParallelBinary : public loadAdjust {
public:
    LoadAdjustRelayParallelBinary()
    {
    }
    void adjustLoad(float load)
    {
        load = constrain(load, 0.0, 1.0);
    }
};
#endif