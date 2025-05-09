/****************************************************************************
 * arch/arm/src/imx1/imx_boot.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

#include "chip.h"
#include "arm_internal.h"

#include <nuttx/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct section_mapping_s
{
  uint32_t physbase;   /* Physical address of the region to be mapped */
  uint32_t virtbase;   /* Virtual address of the region to be mapped */
  uint32_t mmuflags;   /* MMU settings for the region (e.g., cache-able) */
  uint32_t nsections;  /* Number of mappings in the region */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

extern uint8_t _vector_start; /* Beginning of vector block */
extern uint8_t _vector_end;   /* End+1 of vector block */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Mapping of the external memory regions will probably have to be made board
 * specific.
 */

static const struct section_mapping_s section_mapping[] =
{
  { IMX_PERIPHERALS_PSECTION, IMX_PERIPHERALS_VSECTION,
    IMX_PERIPHERALS_MMUFLAGS, IMX_PERIPHERALS_NSECTIONS},
  { IMX_FLASH_PSECTION,       IMX_FLASH_VSECTION,
    IMX_FLASH_MMUFLAGS,       IMX_FLASH_NSECTIONS},
  { IMX_CS1_PSECTION,         IMX_CS1_VSECTION,
    IMX_PERIPHERALS_MMUFLAGS, IMX_CS1_NSECTIONS},
  { IMX_CS2_PSECTION,         IMX_CS2_VSECTION,
    IMX_PERIPHERALS_MMUFLAGS, IMX_CS2_NSECTIONS},
  { IMX_CS3_PSECTION,         IMX_CS3_VSECTION,
    IMX_PERIPHERALS_MMUFLAGS, IMX_CS3_NSECTIONS},
  { IMX_CS4_PSECTION,         IMX_CS4_VSECTION,
    IMX_PERIPHERALS_MMUFLAGS, IMX_CS4_NSECTIONS},
  { IMX_CS5_PSECTION,         IMX_CS5_VSECTION,
    IMX_PERIPHERALS_MMUFLAGS, IMX_CS5_NSECTIONS},
};

#define NMAPPINGS (sizeof(section_mapping) / sizeof(struct section_mapping_s))

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/* All i.MX architectures must provide the following entry point.
 * This entry point is called early in the initialization -- after all memory
 * has been configured and mapped but before any devices have been
 * initialized.
 */

void imx_board_initialize(void);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_setlevel1entry
 ****************************************************************************/

static inline void up_setlevel1entry(uint32_t paddr,
                                     uint32_t vaddr, uint32_t mmuflags)
{
  uint32_t *pgtable = (uint32_t *)PGTABLE_BASE_VADDR;
  uint32_t  index   = vaddr >> 20;

  /* Save the page table entry */

  pgtable[index]  = (paddr | mmuflags);
}

/****************************************************************************
 * Name: up_setupmappings
 ****************************************************************************/

static void up_setupmappings(void)
{
  int i;
  int j;

  for (i = 0; i < NMAPPINGS; i++)
    {
      uint32_t sect_paddr = section_mapping[i].physbase;
      uint32_t sect_vaddr = section_mapping[i].virtbase;
      uint32_t mmuflags   = section_mapping[i].mmuflags;

      for (j = 0; j < section_mapping[i].nsections; j++)
        {
          up_setlevel1entry(sect_paddr, sect_vaddr, mmuflags);
          sect_paddr += SECTION_SIZE;
          sect_vaddr += SECTION_SIZE;
        }
    }
}

/****************************************************************************
 * Name: up_copyvectorblock
 ****************************************************************************/

static void up_copyvectorblock(void)
{
  /* There are three operational memory configurations:
   *
   * 1. We execute in place in FLASH (CONFIG_BOOT_RUNFROMFLASH=y).
   *    In this case:
   *
   *    - Our vectors must be located at the beginning of FLASH and will
   *      also be mapped to address zero (because of the i.MX's
   *     "double map image."
   *    - There is nothing to be done here in this case.
   *
   * 2. We boot in FLASH but copy ourselves to DRAM from better performance.
   *    (CONFIG_BOOT_RUNFROMFLASH=n && CONFIG_BOOT_COPYTORAM=y).
   *    In this case:
   *
   *    - Our code image is in FLASH and we boot to FLASH initially,
   *      then copy ourself to DRAM, and
   *    - DRAM will be mapped to address zero.
   *    - There is nothing to be done here in this case.
   *
   * 3. There is bootloader that copies us to DRAM, but probably not to the
   *    beginning of DRAM (say to 0x0900:0000)
   *   (CONFIG_BOOT_RUNFROMFLASH=n && CONFIG_BOOT_COPYTORAM=n).
   *    In this case:
   *
   *    - DRAM will be mapped to address zero.
   *    - Interrupt vectors will be copied to address zero in this function.
   */

#if !defined(CONFIG_BOOT_RUNFROMFLASH) && !defined(CONFIG_BOOT_COPYTORAM)
  uint32_t *src  = (uint32_t *)_vector_start;
  uint32_t *end  = (uint32_t *)_vector_end;
  uint32_t *dest = (uint32_t *)VECTOR_BASE;

  while (src < end)
    {
      *dest++ = *src++;
    }
#endif
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void arm_boot(void)
{
  /* __start provided the basic MMU mappings for SDRAM.  Now provide
   * mappings for all IO regions (Including the vector region).
   */

  up_setupmappings();

  /* Setup up vector block.  _vector_start and _vector_end are exported from
   * up_vector.S
   */

  up_copyvectorblock();

  /* Perform board-specific initialization */

  imx_board_initialize();

  /* Set up the board-specific LEDs */

#ifdef CONFIG_ARCH_LEDS
  board_autoled_initialize();
#endif

  /* Perform early serial initialization */

#ifdef USE_EARLYSERIALINIT
  arm_earlyserialinit();
#endif
}
