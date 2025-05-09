/****************************************************************************
 * boards/arm/stm32/b-g474e-dpow1/src/stm32_autoleds.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.  The
 *  ASF licenses this file to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance with the
 *  License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "stm32.h"
#include "b-g474e-dpow1.h"

#if defined(CONFIG_ARCH_LEDS)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_autoled_initialize
 ****************************************************************************/

void board_autoled_initialize(void)
{
  /* Configure LED GPIOs for output */

  stm32_configgpio(GPIO_LED1);
  stm32_configgpio(GPIO_LED2);
  stm32_configgpio(GPIO_LED3);
  stm32_configgpio(GPIO_LED4);
}

/****************************************************************************
 * Name: board_autoled_on
 ****************************************************************************/

void board_autoled_on(int led)
{
  switch (led)
    {
      case BOARD_LED1:
        stm32_gpiowrite(GPIO_LED1, true);
        break;

      case BOARD_LED2:
        stm32_gpiowrite(GPIO_LED2, true);
        break;

      case BOARD_LED3:
        stm32_gpiowrite(GPIO_LED3, true);
        break;

      case BOARD_LED4:
        stm32_gpiowrite(GPIO_LED4, true);
        break;
    }
}

/****************************************************************************
 * Name: board_autoled_off
 ****************************************************************************/

void board_autoled_off(int led)
{
  switch (led)
    {
      case BOARD_LED1:
        stm32_gpiowrite(GPIO_LED1, false);
        break;

      case BOARD_LED2:
        stm32_gpiowrite(GPIO_LED2, false);
        break;

      case BOARD_LED3:
        stm32_gpiowrite(GPIO_LED3, false);
        break;

      case BOARD_LED4:
        stm32_gpiowrite(GPIO_LED4, false);
        break;
    }
}

#endif /* CONFIG_ARCH_LEDS */
