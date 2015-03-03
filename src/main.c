/**************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for EFM32TG_STK3300
 * @version 3.20.5
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"
#include "bsp.h"
#include "bsp_trace.h"
#include "spi.h"
#include "usart.h"
#include "frequency.h"
#include "iocontrols.h"
#include "em_int.h"

#define LED1_INDEX  13
#define LED2_INDEX  5

volatile uint32_t msTicks; // counts 1ms timeTicks

void Delay(uint32_t dlyTicks);

USART_TypeDef *uart = USART1;

// Buffers
char transmitBuffer[] = "TEST";

//#define            BUFFERSIZE    (sizeof(transmitBuffer) / sizeof(char))
#define BUFFERSIZE 	17
char receiveBuffer[BUFFERSIZE];
char receiveBuffer2[BUFFERSIZE];
char bit_ready2[BUFFERSIZE];

int spo2 = 1;

int bitz[3] = {0};
char* bit_readyptr;

volatile int got_afe_ready = 0;
volatile int entered_gpio_callback = 0;
volatile int led1_val = 0;
volatile int led2_val = 0;

/*************************v*************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 *****************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       // increment counter necessary in Delay()
}

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}
void init_afe() {
	USART1_send4Byte(0x00, 0x00, 0x00, 0x08);  	// CONTROL0				=			D[23:4]=0 SW_RST[3]=1 DIAG_EN[2]=0 TIM_COUNT_RST[1]=0 SPI_READ[0]=0
	Delay(500); // Delay after reset

	USART1_send4Byte(0x01, 0x00, 0x17, 0xA2);  	// LED2STC[15:0]		=	6050	Sample LED2 Start Count (RED)
	USART1_send4Byte(0x01, 0xAA, 0x17, 0xA2);
	USART1_send4Byte(0x02, 0x00, 0x1F, 0x3E);  	// LED2ENDC[15:0]		=	7998	Sample LED2 End Count
	USART1_send4Byte(0x03, 0x00, 0x17, 0x70);  	// LED2LEDSTC[15:0]		=	6000	LED2 LED Start Count
	USART1_send4Byte(0x04, 0x00, 0x1F, 0x3F);  	// LED2LEDENDC[15:0]	=	7999	LED2 LED End Count
	USART1_send4Byte(0x05, 0x00, 0x00, 0x32);  	// ALED2STC[15:0]		=	  50	Sample Ambient LED2 Start Count
	USART1_send4Byte(0x06, 0x00, 0x07, 0xCE);  	// ALED2ENDC[15:0]		=	1998	Sample Ambient LED2 End Count
	USART1_send4Byte(0x07, 0x00, 0x08, 0x02);  	// LED1STC[15:0]		=	2050	Sample LED1 Start Count (IR)
	USART1_send4Byte(0x08, 0x00, 0x0F, 0x9E);  	// LED1ENDC[15:0]		=	3998	Sample LED1 End Count
	USART1_send4Byte(0x09, 0x00, 0x07, 0xD0);  	// LED1LEDSTC[15:0]		=	2000	LED1 LED Start Count
	USART1_send4Byte(0x0A, 0x00, 0x0F, 0x9F);  	// LED1LEDENDC[15:0]	=	3999	LED1 LED End Count
	USART1_send4Byte(0x0B, 0x00, 0x0F, 0xD2);  	// ALED1STC[15:0]		=	4050	Sample Ambient LED1 Start Count
	USART1_send4Byte(0x0C, 0x00, 0x17, 0x6E);  	// ALED1ENDC[15:0]		=	5998	Sample Ambient LED1 End Count
	USART1_send4Byte(0x0D, 0x00, 0x00, 0x04);  	// LED2CONVST[15:0]		=	   4	LED2 Convert Start Count
	USART1_send4Byte(0x0E, 0x00, 0x07, 0xCF);  	// LED2CONVEND[15:0]	=	1999	LED2 Convert End Count
	USART1_send4Byte(0x0F, 0x00, 0x07, 0xD4);  	// ALED2CONVST[15:0]	=	2004	LED2 Ambient Convert Start Count
	USART1_send4Byte(0x10, 0x00, 0x0F, 0x9F);  	// ALED2CONVEND[15:0]	=	3999	LED2 Ambient Convert End Count
	USART1_send4Byte(0x11, 0x00, 0x0F, 0xA4);  	// LED1CONVST[15:0]		=	4004	LED1 Convert Start Count
	USART1_send4Byte(0x12, 0x00, 0x17, 0x6F);		// LED1CONVEND[15:0]	=	5999	LED1 Convert End Count
	USART1_send4Byte(0x13, 0x00, 0x17, 0x74);  	// ALED1CONVST[15:0]	=	6004	LED1 Ambient Convert Start Count
	USART1_send4Byte(0x14, 0x00, 0x1F, 0x3F);  	// ALED1CONVEND[15:0]	=	7999	LED1 Ambient Convert End Count
	USART1_send4Byte(0x15, 0x00, 0x00, 0x00);		// ADCRSTSTCT0[15:0]	=	   0	ADC Reset 0 Start Count
	USART1_send4Byte(0x16, 0x00, 0x00, 0x03);  	// ADCRSTENDCT0[15:0]	=	   3	ADC Reset 0 End Count
	USART1_send4Byte(0x17, 0x00, 0x07, 0xD0);  	// ADCRSTSTCT1[15:0]	=	2000	ADC Reset 1 Start Count
	USART1_send4Byte(0x18, 0x00, 0x07, 0xD3);  	// ADCRSTENDCT1[15:0]	=	2003	ADC Reset 1 End Count
	USART1_send4Byte(0x19, 0x00, 0x0F, 0xA0);  	// ADCRSTSTCT2[15:0]	=	4000	ADC Reset 2 Start Count
	USART1_send4Byte(0x1A, 0x00, 0x0F, 0xA3);  	// ADCRSTENDCT2[15:0]	=	4003	ADC Reset 2 End Count
	USART1_send4Byte(0x1B, 0x00, 0x17, 0x70);  	// ADCRSTSTCT3[15:0]	=	6000	ADC Reset 3 Start Count
	USART1_send4Byte(0x1C, 0x00, 0x17, 0x73);  	// ADCRSTENDCT3[15:0]	=	6003	ADC Reset 3 End Count
	USART1_send4Byte(0x1D, 0x00, 0x1F, 0x3F);  	// PRPCOUNT[15:0]		=	7999	Pulse Repetition Period Count
	USART1_send4Byte(0x1E, 0x00, 0x07, 0x08);  	// CONTROL1				=			D[23:12]=0 CLKALMPIN[11:9]="111" TIMEREN[8]=1 NUMAV[7:0]=0x08
	USART1_send4Byte(0x1F, 0x00, 0x00, 0x00);  	// SPARE1				=	   0	SPARE1 Register For Future Use
	USART1_send4Byte(0x20, 0x00, 0x00, 0x00);  	// TIAGAIN				=	   		D[23:1]=0 ENSEPGAIN[15]=0 STAGE2EN1[14]=0 D[13:11]=0 STG2GAIN1[10:8]=0 CF_LED1[7:3]=0 RF_LED1[2:0]=0
	USART1_send4Byte(0x21, 0x00, 0x00, 0xFD);  	// TIA_AMB_GAIN			=			D[23:20]=0 AMBDAC[19:16]=0 FLTRCNRSEL[15]=0 STAGE2EN[14]=0 D[13:11]=0 STG2GAIN2[10:8] CF_LED2[7:3]="11111" RF_LED2[2:0]="101"
	USART1_send4Byte(0x22, 0x01, 0x20, 0x20);		// LEDCNTRL				=			D[23:18]=0 LED_RANGE[17:16]="01" LED1[15:8]=0x20 LED2[7:0]=0x20
	USART1_send4Byte(0x23, 0x02, 0x01, 0x00); 	// CONTROL2				=			D[23:19]=0 TX_REF[18:17]="01" RST_CLK_ON_PD_ALM[16]=0 EN_ADC_BYP[15]=0 D[14:12]=0 TXBRGMOD[11]=0 DIGOUT_TRISTATE[10] XTALDIS[9] EN_SLOW_DIAG[8]=1 D[7:3]=0 PDNTX[2]=0 PDNRX[1]=0 PDNAFE[0]=0
	USART1_send4Byte(0x24, 0x00, 0x00, 0x00); 	// SPARE2				=	   0	SPARE2 Register For Future Use
	USART1_send4Byte(0x25, 0x00, 0x00, 0x00); 	// SPARE3				=	   0	SPARE3 Register For Future Use
	USART1_send4Byte(0x26, 0x00, 0x00, 0x00); 	// SPARE4				=	   0	SPARE4 Register For Future Use
	USART1_send4Byte(0x27, 0x00, 0x00, 0x00); 	// RESERVED1			=	   0	RESERVED1 Register For Factory Use Only
	USART1_send4Byte(0x28, 0x00, 0x00, 0x00); 	// RESERVED2			=	   0	RESERVED2 Register For Factory Use Only
	USART1_send4Byte(0x29, 0x00, 0x00, 0x00); 	// ALARM				=	   		D[23:8]=0 ALMPINCLKEN[7]=0 D[6:0]=0
	// read only registers
	//	  USART1_send4Byte(0x2A, 0x00, 0x00, 0x00); 	// LED2VAL[23:0]		=	   0	LED2 Digital Sample Value Register
	//	  USART1_send4Byte(0x2B, 0x00, 0x00, 0x00); 	// ALED2VAL[23:0]		=	   0	Ambient LED2 Digital Sample Value
	//	  USART1_send4Byte(0x2C, 0x00, 0x00, 0x00); 	// LED1VAL[23:0]		=	   0	LED1 Digital Sample Value
	//	  USART1_send4Byte(0x2D, 0x00, 0x00, 0x00); 	// ALED1VAL[23:0]		=	   0	Ambient LED1 Digital Sample Value
	//	  USART1_send4Byte(0x2E, 0x00, 0x00, 0x00); 	// LED2-ALED2VAL[23:0]	=	   0	LED2-Ambient LED2 Digital Sample Value
	//	  USART1_send4Byte(0x2F, 0x00, 0x00, 0x00); 	// LED1-ALED1VAL[23:0]	=	   0	LED1-Ambient LED1 Digital Sample Value
	//	  USART1_send4Byte(0x30, 0x00, 0x00, 0x00); 	// DIAG					=			D[23:13]=0 PD_ALM[12] LED_ALM[11] LED1OPEN[10] LED2OPEN[9] LEDSC[8] OUTPSHGND[7] OUTNSHGND[6] PDOC[5] PDSC[4] INNSCGND[3] INPSCGND[2] INNSCLED[1] INPSCLED[0]
	Delay(100); // Deay after register update
}

/**************************************************************************//**
 * @brief  Gpio callback
 * @param  pin - pin which triggered interrupt
 *****************************************************************************/
void gpioCallback(uint8_t pin)
{

  if (pin == 4)
  {
	  entered_gpio_callback = 1;
  }


}
int entered_read_data = 0;
void read_data() {
	entered_read_data++;
	// read registers

      USART1_send4Byte(0, 0, 0, 0x01);
	  USART1_send4Byte(0x2E, 0, 0, 0);
	  USART1_send4Byte(0, 0, 0, 0x01);
	  USART1_send4Byte(0x2F, 0, 0, 0);

}

int entered_read_byte = 0;
int read_byte(int index) {
	entered_read_byte++;

	// Wait for bit to be ready
	while(bit_ready2[index] == 0);
	bit_ready2[index] = 0;
	return receiveBuffer[index];

}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  // Chip errata
  CHIP_Init();


     // If first word of user data page is non-zero, enable eA Profiler trace
    BSP_TraceProfilerSetup();

    // Enable General purpose input/output clock.
    CMU_ClockEnable(cmuClock_GPIO, true);

    // Configure PD7 as a push pull with pull up (RESETn) TP32
    GPIO_PinModeSet(gpioPortD,7,gpioModePushPullDrive,1);

    // Drive low PD7 (RESETn) TP32
    GPIO_PinOutClear(gpioPortD, 7);

    // Configure PB12 as a push pull with pull down (EN_RUNn) TP28
    GPIO_PinModeSet(gpioPortB,12,gpioModePushPullDrive,0);

    // Drive low PB12 Regulator (EN_RUNn) TP28
    GPIO_PinOutClear(gpioPortB, 12);

    // Enable Universal sync/async receiver/transmitter 1 clock
    CMU_ClockEnable(cmuClock_USART1 , true);

    // Setup UART
    SPI_setup(USART1_NUM, GPIO_POS1, true);

    // Setting up RX interrupt for master
  //  SPI1_setupRXInt(NO_RX, NO_RX);

  // Setup SysTick Timer for 1 msec interrupts
  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

  // HERE
  Delay(500);

   // Configure GPIO interrupt PC4 (ADC_RDY) TP8
   GPIO_IntConfig(gpioPortC,4,true,false,true);

   // Initialize GPIO interrupt dispatcher
   GPIOINT_Init();

   // Configure input PC4 (ADC_RDY) TP8
   GPIO_PinModeSet(gpioPortC, 4, gpioModeInput, 0);

   // Disable PC5 (CLKOUT) TP12
   GPIO_PinModeSet(gpioPortC,5,gpioModeDisabled,0);

   // Disable PC12 (DIAG_END) TP16
   GPIO_PinModeSet(gpioPortC,12,gpioModeDisabled,0);

   // Disable PC13 (PD_ALM) TP20
   GPIO_PinModeSet(gpioPortC,13,gpioModeDisabled,0);

   // Disable PB11 (PGOOD) TP24
   GPIO_PinModeSet(gpioPortB,11,gpioModeDisabled,0);

   // Disable PC6 (LED_ALM) TP36
   GPIO_PinModeSet(gpioPortC,6,gpioModeDisabled,0);

   // Configure PD5 as a push pull with a pull up (AFE_PDNn) TP30
   GPIO_PinModeSet(gpioPortD,5,gpioModePushPullDrive,0);

   // Drive high PD5 (AFE_PDNn) TP30
   GPIO_PinOutSet(gpioPortD, 5);

   Delay(200);

   // Drive high PD7 (RESETn) TP32
   GPIO_PinOutSet(gpioPortD, 7);

   // Disable PD4 (LEFT_MCU) TP26
 //  GPIO_PinModeSet(gpioPortD,4,gpioModeDisabled,1);

   // Disable PD6 (MIC_MCU) TP34
   GPIO_PinModeSet(gpioPortD,6,gpioModeDisabled,1);

   Delay(200);

   init_afe();
   // configure registers for on board sensor and LED

 	  // Configure interrupts for TX and RX
 	    SPI1_setupSlaveInt(receiveBuffer, 256, transmitBuffer, BUFFERSIZE, bit_ready2);

 	  // Register callbacks before setting up and enabling pin interrupt.
 	  // remove line comment below to enable interrupt driven adc register requests
 	  GPIOINT_CallbackRegister(4, gpioCallback);

   //1) SPI_READ set to 1
 //  USART1_send4Byte(0x00, 0x00, 0x00, 0x01);
   // Infinite loop

  // USART1_send4Byte(0, 0, 0, 0x01);
  // USART1_send4Byte(0x01, 0, 0, 0);

   // set some interrupt prioties
 	  NVIC_SetPriority(USART1_RX_IRQn, 0);
 	  NVIC_SetPriority(GPIO_ODD_IRQn, 1);
 	  NVIC_SetPriority(GPIO_EVEN_IRQn, 1);

  // Initialize LED driver
  BSP_PinsInit();
  // Infinite blink loop
  spo2 = 965;
  int tmp[3] = {0};
  int i = 0;
  int count = 0;
  while (1)
  {

//	  send_byte(spo2);

	  	 if( (entered_gpio_callback = 1)) {
	  		 led2_val = 0;
	  		 led1_val = 0;
	  		slaveRxBufferIndex = 0;

	  		 read_data();

	  		 for(i = LED2_INDEX; i < (LED2_INDEX+3); i++) {
	  			 tmp[i-LED2_INDEX] = read_byte(i);
	  		 }

	  		 led2_val = (tmp[0] << 16);
	  		 led2_val |= (tmp[1] << 8);
	  		 led2_val |= tmp[2];

	  		 for(i = LED1_INDEX; i < (LED1_INDEX+3); i++) {
	  		 		 tmp[i-LED1_INDEX] = read_byte(i);
	  		 }
	  		 led1_val = (tmp[0] << 16);
	  		 led1_val |= (tmp[1] << 8);
	  		 led1_val |= tmp[2];

	  		 spo2 = 1000*led2_val/led1_val;


  			 send_byte(spo2);

/*
	  		 for(i = 0; i < 200; i++) {
	  			 send_byte(spo2);
	  		 }*/
//	  		 send_byte(spo2);
	  		 entered_gpio_callback = 0;
//	  		 count++;
	  	 }

  }
}
