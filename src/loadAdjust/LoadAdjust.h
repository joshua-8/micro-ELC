#ifndef _LOAD_ADJUST_H_
#define _LOAD_ADJUST_H_
#include <Arduino.h>
/**
 * @brief  This class defines an interface for any type of adjustable electrical load.
 */
class LoadAdjust {
public:
    /**
     * @brief  set a new value for the adjustable load
     * @param  load: between 0.0 and 1.0 where 1.0 is the highest load
     * @retval None
     */
    virtual void setLoad(float load) = 0;
    /**
     * @brief  set up pin states
     * @retval None
     */
    virtual void begin() = 0;
};
#endif