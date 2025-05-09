/****************************************************************************
 * arch/arm/src/samv7/sam_serial.h
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

#ifndef __ARCH_ARM_SRC_SAMV7_SAM_SERIAL_H
#define __ARCH_ARM_SRC_SAMV7_SAM_SERIAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>

#include "chip.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Is RS-485 used? */

#undef SERIAL_HAVE_RS485
#if defined(CONFIG_SAMV7_USART0_RS485MODE) || \
    defined(CONFIG_SAMV7_USART1_RS485MODE) || \
    defined(CONFIG_SAMV7_USART2_RS485MODE)
#  define SERIAL_HAVE_RS485 1
#endif

/* Is RX/TX DMA used on the console UART? */

#undef SERIAL_HAVE_CONSOLE_DMA
#if defined(CONFIG_USART0_SERIAL_CONSOLE) && \
    (defined(CONFIG_USART0_RXDMA) || defined(CONFIG_USART0_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_USART1_SERIAL_CONSOLE) && \
    (defined(CONFIG_USART1_RXDMA) || defined(CONFIG_USART1_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_USART2_SERIAL_CONSOLE) && \
    (defined(CONFIG_USART2_RXDMA) || defined(CONFIG_USART2_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_UART0_SERIAL_CONSOLE) && \
    (defined(CONFIG_UART0_RXDMA) || defined(CONFIG_UART0_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_UART1_SERIAL_CONSOLE) && \
    (defined(CONFIG_UART1_RXDMA) || defined(CONFIG_UART1_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_UART2_SERIAL_CONSOLE) && \
    (defined(CONFIG_UART2_RXDMA) || defined(CONFIG_UART2_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_UART3_SERIAL_CONSOLE) && \
    (defined(CONFIG_UART3_RXDMA) || defined(CONFIG_UART3_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#elif defined(CONFIG_UART4_SERIAL_CONSOLE) && \
    (defined(CONFIG_UART4_RXDMA) || defined(CONFIG_UART4_TXDMA))
#  define SERIAL_HAVE_CONSOLE_DMA
#endif

/* RX/TX DMA ops */

#undef SERIAL_HAVE_NORXDMA_OPS
#if !defined(CONFIG_USART0_RXDMA) && defined(CONFIG_SAMV7_USART0)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_USART1_RXDMA) && defined(CONFIG_SAMV7_USART1)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_USART2_RXDMA) && defined(CONFIG_SAMV7_USART2)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_UART0_RXDMA) && defined(CONFIG_SAMV7_UART0)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_UART1_RXDMA) && defined(CONFIG_SAMV7_UART1)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_UART2_RXDMA) && defined(CONFIG_SAMV7_UART2)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_UART3_RXDMA) && defined(CONFIG_SAMV7_UART3)
#  define SERIAL_HAVE_NORXDMA_OPS
#elif !defined(CONFIG_UART4_RXDMA) && defined(CONFIG_SAMV7_UART4)
#  define SERIAL_HAVE_NORXDMA_OPS
#endif

#undef SERIAL_HAVE_NOTXDMA_OPS
#if !defined(CONFIG_USART0_TXDMA) && defined(CONFIG_SAMV7_USART0)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_USART1_TXDMA) && defined(CONFIG_SAMV7_USART1)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_USART2_TXDMA) && defined(CONFIG_SAMV7_USART2)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_UART0_TXDMA) && defined(CONFIG_SAMV7_UART0)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_UART1_TXDMA) && defined(CONFIG_SAMV7_UART1)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_UART2_TXDMA) && defined(CONFIG_SAMV7_UART2)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_UART3_TXDMA) && defined(CONFIG_SAMV7_UART3)
#  define SERIAL_HAVE_NOTXDMA_OPS
#elif !defined(CONFIG_UART4_TXDMA) && defined(CONFIG_SAMV7_UART4)
#  define SERIAL_HAVE_NOTXDMA_OPS
#endif

#undef SERIAL_HAVE_RXTXDMA_OPS
#if defined(CONFIG_USART0_TXDMA) && defined(CONFIG_USART0_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_USART0_TXDMA) && !defined(CONFIG_USART0_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_USART0_TXDMA) && defined(CONFIG_USART0_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_USART1_TXDMA) && defined(CONFIG_USART1_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_USART1_TXDMA) && !defined(CONFIG_USART1_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_USART1_TXDMA) && defined(CONFIG_USART1_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_USART2_TXDMA) && defined(CONFIG_USART2_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_USART2_TXDMA) && !defined(CONFIG_USART2_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_USART2_TXDMA) && defined(CONFIG_USART2_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_UART0_TXDMA) && defined(CONFIG_UART0_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_UART0_TXDMA) && !defined(CONFIG_UART0_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_UART0_TXDMA) && defined(CONFIG_UART0_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_UART1_TXDMA) && defined(CONFIG_UART1_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_UART1_TXDMA) && !defined(CONFIG_UART1_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_UART1_TXDMA) && defined(CONFIG_UART1_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_UART2_TXDMA) && defined(CONFIG_UART2_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_UART2_TXDMA) && !defined(CONFIG_UART2_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_UART2_TXDMA) && defined(CONFIG_UART2_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_UART0_TXDMA) && defined(CONFIG_UART3_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_UART3_TXDMA) && !defined(CONFIG_UART3_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_UART3_TXDMA) && defined(CONFIG_UART3_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif
#if defined(CONFIG_UART4_TXDMA) && defined(CONFIG_UART4_RXDMA)
#  define SERIAL_HAVE_RXTXDMA_OPS
#elif defined(CONFIG_UART4_TXDMA) && !defined(CONFIG_UART4_RXDMA)
#  define SERIAL_HAVE_TXDMA_OPS
#elif !defined(CONFIG_UART4_TXDMA) && defined(CONFIG_UART4_RXDMA)
#  define SERIAL_HAVE_RXDMA_OPS
#endif

/* No DMA ops */

#undef SERIAL_HAVE_NODMA_OPS
#if !defined(CONFIG_USART0_TXDMA) && !defined(CONFIG_USART0_RXDMA) && \
    defined(CONFIG_SAMV7_USART0)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_USART1_TXDMA) && !defined(CONFIG_USART1_RXDMA) && \
    defined(CONFIG_SAMV7_USART1)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_USART2_TXDMA) && !defined(CONFIG_USART2_RXDMA) && \
    defined(CONFIG_SAMV7_USART2)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_UART0_TXDMA) && !defined(CONFIG_UART0_RXDMA) && \
    defined(CONFIG_SAMV7_UART0)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_UART1_TXDMA) && !defined(CONFIG_UART1_RXDMA) && \
    defined(CONFIG_SAMV7_UART1)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_UART2_TXDMA) && !defined(CONFIG_UART2_RXDMA) && \
    defined(CONFIG_SAMV7_UART2)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_UART3_TXDMA) && !defined(CONFIG_UART3_RXDMA) && \
    defined(CONFIG_SAMV7_UART3)
#  define SERIAL_HAVE_NODMA_OPS
#endif
#if !defined(CONFIG_UART4_TXDMA) && !defined(CONFIG_UART4_RXDMA) && \
    defined(CONFIG_SAMV7_UART4)
#  define SERIAL_HAVE_NODMA_OPS
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: sam_serial_dma_poll
 *
 * Description:
 *   Checks receive DMA buffers for received bytes that have not accumulated
 *   to the point where the DMA half/full interrupt has triggered.
 *
 *   This function should be called from a timer or other periodic context.
 *
 ****************************************************************************/

#if defined(SERIAL_HAVE_RXDMA_OPS) || defined(SERIAL_HAVE_RXTXDMA_OPS)
void sam_serial_dma_poll(void);
#endif

#endif /* __ARCH_ARM_SRC_SAMV7_SAM_SERIAL_H */
