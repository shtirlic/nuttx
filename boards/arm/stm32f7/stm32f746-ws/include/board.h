/****************************************************************************
 * boards/arm/stm32f7/stm32f746-ws/include/board.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_ARM_STM32F7_STM32F746_WS_INCLUDE_BOARD_H
#define __BOARDS_ARM_STM32F7_STM32F746_WS_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#endif

/* Do not include STM32 F7 header files here */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* The STM32F7 Discovery board provides the following clock sources:
 *
 *   X1:  24 MHz oscillator for USB OTG HS PHY and camera module
 *        (daughter board)
 *   X2:  25 MHz oscillator for STM32F746NGH6 microcontroller and
 *         Ethernet PHY.
 *   X3:  32.768 KHz crystal for STM32F746NGH6 embedded RTC
 *
 * So we have these clock source available within the STM32
 *
 *   HSI: 16 MHz RC factory-trimmed
 *   LSI: 32 KHz RC
 *   HSE: On-board crystal frequency is 25MHz
 *   LSE: 32.768 kHz
 */

#define STM32_BOARD_XTAL        8000000ul

#define STM32_HSI_FREQUENCY     16000000ul
#define STM32_LSI_FREQUENCY     32000
#define STM32_HSE_FREQUENCY     STM32_BOARD_XTAL
#define STM32_LSE_FREQUENCY     32768

/* Main PLL Configuration.
 *
 * PLL source is HSE = 8,000,000
 *
 * PLL_VCO = (STM32_HSE_FREQUENCY / PLLM) * PLLN
 * Subject to:
 *
 *     2 <= PLLM <= 63
 *   192 <= PLLN <= 432
 *   192 MHz <= PLL_VCO <= 432MHz
 *
 * SYSCLK  = PLL_VCO / PLLP
 * Subject to
 *
 *   PLLP = {2, 4, 6, 8}
 *   SYSCLK <= 216 MHz
 *
 * USB OTG FS, SDMMC and RNG Clock = PLL_VCO / PLLQ
 * Subject to
 *   The USB OTG FS requires a 48 MHz clock to work correctly. The SDMMC
 *   and the random number generator need a frequency lower than or equal
 *   to 48 MHz to work correctly.
 *
 * 2 <= PLLQ <= 15
 */

/* Highest SYSCLK with USB OTG FS clock <= 48MHz
 *
 * PLL_VCO = (8,000,000 / 8) * 432 = 432 MHz
 * SYSCLK  = 432 MHz / 2 = 216 MHz
 * USB OTG FS, SDMMC and RNG Clock = 432 MHz / 9 = 48 MHz
 */

#define STM32_PLLCFG_PLLM       RCC_PLLCFG_PLLM(8)
#define STM32_PLLCFG_PLLN       RCC_PLLCFG_PLLN(432)
#define STM32_PLLCFG_PLLP       RCC_PLLCFG_PLLP_2
#define STM32_PLLCFG_PLLQ       RCC_PLLCFG_PLLQ(9)

#define STM32_VCO_FREQUENCY     ((STM32_HSE_FREQUENCY / 8) * 432)
#define STM32_SYSCLK_FREQUENCY  (STM32_VCO_FREQUENCY / 2)
#define STM32_OTGFS_FREQUENCY   (STM32_VCO_FREQUENCY / 9)

/* Configure factors for  PLLSAI clock */

#define CONFIG_STM32F7_PLLSAI           1
#define STM32_RCC_PLLSAICFGR_PLLSAIN    RCC_PLLSAICFGR_PLLSAIN(192)
#define STM32_RCC_PLLSAICFGR_PLLSAIP    RCC_PLLSAICFGR_PLLSAIP(2)
#define STM32_RCC_PLLSAICFGR_PLLSAIQ    RCC_PLLSAICFGR_PLLSAIQ(2)
#define STM32_RCC_PLLSAICFGR_PLLSAIR    RCC_PLLSAICFGR_PLLSAIR(2)

/* Configure Dedicated Clock Configuration Register */

#define STM32_RCC_DCKCFGR1_PLLI2SDIVQ  RCC_DCKCFGR1_PLLI2SDIVQ(1)
#define STM32_RCC_DCKCFGR1_PLLSAIDIVQ  RCC_DCKCFGR1_PLLSAIDIVQ(1)
#define STM32_RCC_DCKCFGR1_PLLSAIDIVR  RCC_DCKCFGR1_PLLSAIDIVR(0)
#define STM32_RCC_DCKCFGR1_SAI1SRC     RCC_DCKCFGR1_SAI1SEL(0)
#define STM32_RCC_DCKCFGR1_SAI2SRC     RCC_DCKCFGR1_SAI2SEL(0)
#define STM32_RCC_DCKCFGR1_TIMPRESRC   0
#define STM32_RCC_DCKCFGR1_DFSDM1SRC   0
#define STM32_RCC_DCKCFGR1_ADFSDM1SRC  0

/* Configure factors for  PLLI2S clock */

#define CONFIG_STM32F7_PLLI2S          1
#define STM32_RCC_PLLI2SCFGR_PLLI2SN   RCC_PLLI2SCFGR_PLLI2SN(192)
#define STM32_RCC_PLLI2SCFGR_PLLI2SP   RCC_PLLI2SCFGR_PLLI2SP(2)
#define STM32_RCC_PLLI2SCFGR_PLLI2SQ   RCC_PLLI2SCFGR_PLLI2SQ(2)
#define STM32_RCC_PLLI2SCFGR_PLLI2SR   RCC_PLLI2SCFGR_PLLI2SR(2)

/* Configure Dedicated Clock Configuration Register 2 */

#define STM32_RCC_DCKCFGR2_USART1SRC  RCC_DCKCFGR2_USART1SEL_APB
#define STM32_RCC_DCKCFGR2_USART2SRC  RCC_DCKCFGR2_USART2SEL_APB
#define STM32_RCC_DCKCFGR2_UART4SRC   RCC_DCKCFGR2_UART4SEL_APB
#define STM32_RCC_DCKCFGR2_UART5SRC   RCC_DCKCFGR2_UART5SEL_APB
#define STM32_RCC_DCKCFGR2_USART6SRC  RCC_DCKCFGR2_USART6SEL_APB
#define STM32_RCC_DCKCFGR2_UART7SRC   RCC_DCKCFGR2_UART7SEL_APB
#define STM32_RCC_DCKCFGR2_UART8SRC   RCC_DCKCFGR2_UART8SEL_APB
#define STM32_RCC_DCKCFGR2_I2C1SRC    RCC_DCKCFGR2_I2C1SEL_HSI
#define STM32_RCC_DCKCFGR2_I2C2SRC    RCC_DCKCFGR2_I2C2SEL_HSI
#define STM32_RCC_DCKCFGR2_I2C3SRC    RCC_DCKCFGR2_I2C3SEL_HSI
#define STM32_RCC_DCKCFGR2_I2C4SRC    RCC_DCKCFGR2_I2C4SEL_HSI
#define STM32_RCC_DCKCFGR2_LPTIM1SRC  RCC_DCKCFGR2_LPTIM1SEL_APB
#define STM32_RCC_DCKCFGR2_CECSRC     RCC_DCKCFGR2_CECSEL_HSI
#define STM32_RCC_DCKCFGR2_CK48MSRC   RCC_DCKCFGR2_CK48MSEL_PLLSAI
#define STM32_RCC_DCKCFGR2_SDMMCSRC   RCC_DCKCFGR2_SDMMCSEL_48MHZ
#define STM32_RCC_DCKCFGR2_SDMMC2SRC  RCC_DCKCFGR2_SDMMC2SEL_48MHZ

/* Several prescalers allow the configuration of the two AHB buses, the
 * high-speed APB (APB2) and the low-speed APB (APB1) domains. The maximum
 * frequency of the two AHB buses is 216 MHz while the maximum frequency of
 * the high-speed APB domains is 108 MHz. The maximum allowed frequency of
 * the low-speed APB domain is 54 MHz.
 */

/* AHB clock (HCLK) is SYSCLK (216 MHz) */

#define STM32_RCC_CFGR_HPRE     RCC_CFGR_HPRE_SYSCLK  /* HCLK  = SYSCLK / 1 */
#define STM32_HCLK_FREQUENCY    STM32_SYSCLK_FREQUENCY

/* APB1 clock (PCLK1) is HCLK/4 (54 MHz) */

#define STM32_RCC_CFGR_PPRE1    RCC_CFGR_PPRE1_HCLKd4     /* PCLK1 = HCLK / 4 */
#define STM32_PCLK1_FREQUENCY   (STM32_HCLK_FREQUENCY/4)

/* Timers driven from APB1 will be twice PCLK1 */

#define STM32_APB1_TIM2_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM12_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM13_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM14_CLKIN  (2*STM32_PCLK1_FREQUENCY)

/* APB2 clock (PCLK2) is HCLK/2 (108MHz) */

#define STM32_RCC_CFGR_PPRE2    RCC_CFGR_PPRE2_HCLKd2     /* PCLK2 = HCLK / 2 */
#define STM32_PCLK2_FREQUENCY   (STM32_HCLK_FREQUENCY/2)

/* Timers driven from APB2 will be twice PCLK2 */

#define STM32_APB2_TIM1_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM9_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM10_CLKIN  (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM11_CLKIN  (2*STM32_PCLK2_FREQUENCY)

/* FLASH wait states
 *
 *  --------- ---------- -----------
 *  VDD       MAX SYSCLK WAIT STATES
 *  --------- ---------- -----------
 *  1.7-2.1 V   180 MHz    8
 *  2.1-2.4 V   216 MHz    9
 *  2.4-2.7 V   216 MHz    8
 *  2.7-3.6 V   216 MHz    7
 *  --------- ---------- -----------
 */

#define BOARD_FLASH_WAITSTATES 7

/* SDIO dividers.  Note that slower clocking is required when DMA is disabled
 * in order to avoid RX overrun/TX underrun errors due to delayed responses
 * to service FIFOs in interrupt driven mode.  These values have not been
 * tuned!!!
 *
 * SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(118+2)=400 KHz
 */

#define STM32_SDMMC_INIT_CLKDIV      (118 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)

/* DMA ON:  SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(1+2)=16 MHz
 * DMA OFF: SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(2+2)=12 MHz
 */

#ifdef CONFIG_SDIO_DMA
#  define STM32_SDMMC_MMCXFR_CLKDIV  (1 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#else
#  define STM32_SDMMC_MMCXFR_CLKDIV  (2 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#endif

/* DMA ON:  SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(1+2)=16 MHz
 * DMA OFF: SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(2+2)=12 MHz
 */

#ifdef CONFIG_SDIO_DMA
#  define STM32_SDMMC_SDXFR_CLKDIV   (1 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#else
#  define STM32_SDMMC_SDXFR_CLKDIV   (2 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#endif

/* DMA channels *************************************************************/

/* SDMMC */

/* Stream selections are arbitrary for now but might become important in the
 * future if we set aside more DMA channels/streams.
 *
 * SDIO DMA
 *   DMAMAP_SDMMC1_1 = Channel 4, Stream 3
 *   DMAMAP_SDMMC1_2 = Channel 4, Stream 6
 */

#define DMAMAP_SDMMC1  DMAMAP_SDMMC1_1

/* Alternate function pin selections ****************************************/

/* ADC1 */

#define GPIO_ADC1_IN0   GPIO_ADC1_IN0_0   /* PA0 */
#define GPIO_ADC1_IN1   GPIO_ADC1_IN1_0   /* PA1 */
#define GPIO_ADC1_IN2   GPIO_ADC1_IN2_0   /* PA2 */
#define GPIO_ADC1_IN3   GPIO_ADC1_IN3_0   /* PA3 */
#define GPIO_ADC1_IN4   GPIO_ADC1_IN4_0   /* PA4 */
#define GPIO_ADC1_IN5   GPIO_ADC1_IN5_0   /* PA5 */
#define GPIO_ADC1_IN6   GPIO_ADC1_IN6_0   /* PA6 */
#define GPIO_ADC1_IN7   GPIO_ADC1_IN7_0   /* PA7 */
#define GPIO_ADC1_IN8   GPIO_ADC1_IN8_0   /* PB0 */
#define GPIO_ADC1_IN9   GPIO_ADC1_IN9_0   /* PB1 */
#define GPIO_ADC1_IN10  GPIO_ADC1_IN10_0  /* PC0 */
#define GPIO_ADC1_IN11  GPIO_ADC1_IN11_0  /* PC1 */
#define GPIO_ADC1_IN12  GPIO_ADC1_IN12_0  /* PC2 */
#define GPIO_ADC1_IN13  GPIO_ADC1_IN13_0  /* PC3 */
#define GPIO_ADC1_IN14  GPIO_ADC1_IN14_0  /* PC4 */
#define GPIO_ADC1_IN15  GPIO_ADC1_IN15_0  /* PC5 */

/* USART6:
 *
 * These configurations assume that you are using a standard Arduio RS-232
 * shield with the serial interface with RX on pin D0 and TX on pin D1:
 *
 *   -------- ---------------
 *               STM32F7
 *   ARDUIONO FUNCTION  GPIO
 *   -- ----- --------- -----
 *   DO RX    USART6_RX PC7
 *   D1 TX    USART6_TX PC6
 *   -- ----- --------- -----
 */

#define GPIO_USART6_RX (GPIO_USART6_RX_1|GPIO_SPEED_100MHz)
#define GPIO_USART6_TX (GPIO_USART6_TX_1|GPIO_SPEED_100MHz)

#define GPIO_SPI1_SCK  (GPIO_SPI1_SCK_1|GPIO_SPEED_50MHz)
#define GPIO_SPI1_MISO (GPIO_SPI1_MISO_1|GPIO_SPEED_50MHz)
#define GPIO_SPI1_MOSI (GPIO_SPI1_MOSI_1|GPIO_SPEED_50MHz)

#define GPIO_I2C1_SCL  (GPIO_I2C1_SCL_1|GPIO_SPEED_50MHz)
#define GPIO_I2C1_SDA  (GPIO_I2C1_SDA_1|GPIO_SPEED_50MHz)

/* SDMMC1 */

#define GPIO_SDMMC1_CK  (GPIO_SDMMC1_CK_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_CMD (GPIO_SDMMC1_CMD_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D0  (GPIO_SDMMC1_D0_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D1  (GPIO_SDMMC1_D1_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D2  (GPIO_SDMMC1_D2_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D3  (GPIO_SDMMC1_D3_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D4  (GPIO_SDMMC1_D4_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D5  (GPIO_SDMMC1_D5_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D6  (GPIO_SDMMC1_D6_0|GPIO_SPEED_50MHz)
#define GPIO_SDMMC1_D7  (GPIO_SDMMC1_D7_0|GPIO_SPEED_50MHz)

/* OTGFS */

#define GPIO_OTGFS_DM  (GPIO_OTGFS_DM_0|GPIO_SPEED_100MHz)
#define GPIO_OTGFS_DP  (GPIO_OTGFS_DP_0|GPIO_SPEED_100MHz)
#define GPIO_OTGFS_ID  (GPIO_OTGFS_ID_0|GPIO_SPEED_100MHz)

#endif /* __BOARDS_ARM_STM32F7_STM32F746_WS_INCLUDE_BOARD_H */
