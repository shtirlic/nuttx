/****************************************************************************
 * arch/arm64/include/a527/chip.h
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

#ifndef __ARCH_ARM64_INCLUDE_A527_CHIP_H
#define __ARCH_ARM64_INCLUDE_A527_CHIP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Number of bytes in x kibibytes/mebibytes/gibibytes */

#define KB(x)           ((x) << 10)
#define MB(x)           (KB(x) << 10)
#define GB(x)           (MB(UINT64_C(x)) << 10)

/* Generic Interrupt Controller v3: Distributor and Redistributor */

#define CONFIG_GICD_BASE           0x3400000
#define CONFIG_GICR_BASE           0x3460000
#define CONFIG_GICR_OFFSET         0x20000

/* Memory Map: RAM and I/O Memory */

#define CONFIG_RAMBANK1_ADDR       0x40000000
#define CONFIG_RAMBANK1_SIZE       MB(128)

#define CONFIG_DEVICEIO_BASEADDR   0x00000000
#define CONFIG_DEVICEIO_SIZE       MB(1024)

/* Bootloader loads NuttX at this address */

#define CONFIG_LOAD_BASE           0x40800000

/* GIC Cluster Mapping */

#define MPID_TO_CLUSTER_ID(mpid)   ((mpid) & ~0xff)

/****************************************************************************
 * Assembly Macros
 ****************************************************************************/

#ifdef __ASSEMBLY__

.macro  get_cpu_id xreg0
  mrs    \xreg0, mpidr_el1
  ubfx   \xreg0, \xreg0, #0, #8
.endm

#endif /* __ASSEMBLY__ */

#endif /* __ARCH_ARM64_INCLUDE_A527_CHIP_H */
