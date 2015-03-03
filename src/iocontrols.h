/* iocontrols.h

Purpoose: Basic library to enable and disable pins on Gekko
Authors:
Dependencies:
*/
#ifndef IOCONTROLS_H_
#define IOCONTROLS_H_

//Pin Definitions



#define BSP_GPIO_pins
#define BSP_NO_OF_PINS  1
#define BSP_GPIO_pinArray_INIT {{gpioPortA,14}}


typedef struct
{
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} tPin;

//gpio array of tiny Gekko
static const tPin pinArray[ BSP_NO_OF_PINS ] = BSP_GPIO_pinArray_INIT;

volatile uint32_t msTicks; /* counts 1ms timeTicks */

/**************************************************************************//**
 * @brief clears the value of an input pin
 * @param pinNo - Number of pin you wish to clear
 * @return
 *****************************************************************************/
int clear_pin(int pinNo)
{
  GPIO_PinOutClear(pinArray[pinNo].port, pinArray[pinNo].pin);
  return BSP_STATUS_OK;
}


/**************************************************************************//**
 * @brief enables input pin
 * @param pinNo - Number of pin you wish to enable
 * @return
 *****************************************************************************/
int set_pin(int pinNo)
{
  GPIO_PinOutSet(pinArray[pinNo].port, pinArray[pinNo].pin);
  return BSP_STATUS_OK;
}

/**************************************************************************//**
 * @brief toggles input pin
 * @param pinNo - Number of pin you wish to toggle
 * @return
 *****************************************************************************/
int toggle_pin(int pinNo)
{
  if ((pinNo >= 0) && (pinNo < BSP_NO_OF_PINS))
  {
    GPIO_PinOutToggle(pinArray[pinNo].port, pinArray[pinNo].pin);
    return BSP_STATUS_OK;
  }
  return BSP_STATUS_ILLEGAL_PARAM;
}

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
//void delay(uint32_t dlyTicks)
//{
//  uint32_t curTicks;
//
//  curTicks = msTicks;
//  while ((msTicks - curTicks) < dlyTicks) ;
//}
////
void delay(uint32_t dlyTicks)
{
  volatile uint32_t i;
  for (i=1 ; i<dlyTicks ; i++);
}

/**************************************************************************//**
 * @brief Initialize Pins Driver
 *****************************************************************************/
int BSP_PinsInit(void)
{
  int i;

  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  for ( i=0; i<BSP_NO_OF_PINS; i++ )
  {
    GPIO_PinModeSet(pinArray[i].port, pinArray[i].pin, gpioModePushPull, 0);
  }
  return BSP_STATUS_OK;
}


#endif /* IOCONTROLS_H_ */
