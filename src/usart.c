/**************************************************************************//**
 * @file
 * @brief USART example
 * @author Energy Micro AS
 * @version 1.13
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2013 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#include "em_device.h"
#include "usart.h"
#include "em_gpio.h"
#include "em_usart.h"



/******************************************************************************
 * @brief sends data using USART1
 * @param txBuffer points to data to transmit
 * @param bytesToSend bytes will be sent
 *****************************************************************************/
void USART1_sendBuffer(char* txBuffer, int bytesToSend)
{
  USART_TypeDef *uart = USART1;
  int           ii;

  /* Sending the data */
  for (ii = 0; ii < bytesToSend;  ii++)
  {
    /* Waiting for the usart to be ready */
    while (!(uart->STATUS & USART_STATUS_TXBL)) ;

    if (txBuffer != 0)
    {
      /* Writing next byte to USART */
      uart->TXDATA = *txBuffer;
      txBuffer++;
    }
    else
    {
      uart->TXDATA = 0;
    }
  }

  /*Waiting for transmission of last byte */
  while (!(uart->STATUS & USART_STATUS_TXC)) ;
}

void USART1_sendByte(uint8_t* txByte)
{
  USART_TypeDef *uart = USART1;

  /* Waiting for the usart to be ready */
  while (!(uart->STATUS & USART_STATUS_TXBL)) ;

  /* Write char to USART */
  uart->TXDATA = *txByte;

  /*Waiting for transmission of last byte */
  while (!(uart->STATUS & USART_STATUS_TXC)) ;
}

void USART1_send4Byte(uint8_t txData3, uint8_t txData2, uint8_t txData1, uint8_t txData0)
{
  USART_TypeDef *uart = USART1;

  uint8_t* tmp3;
  uint8_t* tmp2;
  uint8_t* tmp1;
  uint8_t* tmp0;

  tmp3 = &txData3;
  tmp2 = &txData2;
  tmp1 = &txData1;
  tmp0 = &txData0;

  /* Sending the data */

  /* Waiting for the usart to be ready */
  while (!(uart->STATUS & USART_STATUS_TXBL));

  /* Writing next byte to USART */
  uart->TXDATA = *tmp3;

  /* Waiting for the usart to be ready */
//  while (!(uart->STATUS & USART_STATUS_TXC));

  /* Writing next byte to USART */
  uart->TXDATA = *tmp2;

  /* Waiting for the usart to be ready */
//  while (!(uart->STATUS & USART_STATUS_TXC));

  /* Writing next byte to USART */
  uart->TXDATA = *tmp1;

  /* Waiting for the usart to be ready */
//  while (!(uart->STATUS & USART_STATUS_TXC));

  /* Writing next byte to USART */
  uart->TXDATA = *tmp0;

  /* Waiting for the usart to be ready */
  while (!(uart->STATUS & USART_STATUS_TXC));
}

void USART1_enable_interrupts()
{
	USART_TypeDef *usart = USART1;

	USART_IntEnable(usart, (1 << 2)); // set RXDATAV in IEN

	NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	NVIC_EnableIRQ(USART1_RX_IRQn);



}
