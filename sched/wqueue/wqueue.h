/****************************************************************************
 * sched/wqueue/wqueue.h
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
 ****************************************************************************/

#ifndef __SCHED_WQUEUE_WQUEUE_H
#define __SCHED_WQUEUE_WQUEUE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <semaphore.h>
#include <sys/types.h>
#include <stdbool.h>

#include <nuttx/clock.h>
#include <nuttx/queue.h>
#include <nuttx/wqueue.h>
#include <nuttx/spinlock.h>

#ifdef CONFIG_SCHED_WORKQUEUE

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Kernel thread names */

#define HPWORKNAME "hpwork"
#define LPWORKNAME "lpwork"

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/

/* This represents one worker */

struct kworker_s
{
  pid_t             pid;       /* The task ID of the worker thread */
  FAR struct work_s *work;     /* The work structure */
  sem_t             wait;      /* Sync waiting for worker done */
  int16_t           wait_count;
};

/* This structure defines the state of one kernel-mode work queue */

struct kwork_wqueue_s
{
  struct dq_queue_s q;         /* The queue of pending work */
  sem_t             sem;       /* The counting semaphore of the wqueue */
  sem_t             exsem;     /* Sync waiting for thread exit */
  spinlock_t        lock;      /* Spinlock */
  uint8_t           nthreads;  /* Number of worker threads */
  bool              exit;      /* A flag to request the thread to exit */
  int16_t           wait_count;
  struct kworker_s  worker[0]; /* Describes a worker thread */
};

/* This structure defines the state of one high-priority work queue.  This
 * structure must be cast-compatible with kwork_wqueue_s.
 */

#ifdef CONFIG_SCHED_HPWORK
struct hp_wqueue_s
{
  struct dq_queue_s q;         /* The queue of pending work */
  sem_t             sem;       /* The counting semaphore of the wqueue */
  sem_t             exsem;     /* Sync waiting for thread exit */
  spinlock_t        lock;      /* Spinlock */
  uint8_t           nthreads;  /* Number of worker threads */
  bool              exit;      /* A flag to request the thread to exit */
  int16_t           wait_count;

  /* Describes each thread in the high priority queue's thread pool */

  struct kworker_s  worker[CONFIG_SCHED_HPNTHREADS];
};
#endif

/* This structure defines the state of one low-priority work queue.  This
 * structure must be cast compatible with kwork_wqueue_s
 */

#ifdef CONFIG_SCHED_LPWORK
struct lp_wqueue_s
{
  struct dq_queue_s q;         /* The queue of pending work */
  sem_t             sem;       /* The counting semaphore of the wqueue */
  sem_t             exsem;     /* Sync waiting for thread exit */
  spinlock_t        lock;      /* Spinlock */
  uint8_t           nthreads;  /* Number of worker threads */
  bool              exit;      /* A flag to request the thread to exit */
  int16_t           wait_count;

  /* Describes each thread in the low priority queue's thread pool */

  struct kworker_s  worker[CONFIG_SCHED_LPNTHREADS];
};
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef CONFIG_SCHED_HPWORK
/* The state of the kernel mode, high priority work queue. */

extern struct hp_wqueue_s g_hpwork;
#endif

#ifdef CONFIG_SCHED_LPWORK
/* The state of the kernel mode, low priority work queue(s). */

extern struct lp_wqueue_s g_lpwork;
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

static inline_function FAR struct kwork_wqueue_s *work_qid2wq(int qid)
{
#ifdef CONFIG_SCHED_HPWORK
  if (qid == HPWORK)
    {
      return (FAR struct kwork_wqueue_s *)&g_hpwork;
    }
  else
#endif
#ifdef CONFIG_SCHED_LPWORK
  if (qid == LPWORK)
    {
      return (FAR struct kwork_wqueue_s *)&g_lpwork;
    }
  else
#endif
    {
      return NULL;
    }
}

/****************************************************************************
 * Name: work_start_highpri
 *
 * Description:
 *   Start the high-priority, kernel-mode work queue.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Return zero (OK) on success.  A negated errno value is returned on
 *   errno value is returned on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_SCHED_HPWORK
int work_start_highpri(void);
#endif

/****************************************************************************
 * Name: work_start_lowpri
 *
 * Description:
 *   Start the low-priority, kernel-mode worker thread(s)
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Return zero (OK) on success.  A negated errno value is returned on
 *   errno value is returned on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_SCHED_LPWORK
int work_start_lowpri(void);
#endif

/****************************************************************************
 * Name: work_initialize_notifier
 *
 * Description:
 *   Set up the notification data structures for normal operation.
 *
 ****************************************************************************/

#ifdef CONFIG_WQUEUE_NOTIFIER
void work_initialize_notifier(void);
#endif

#endif /* CONFIG_SCHED_WORKQUEUE */
#endif /* __SCHED_WQUEUE_WQUEUE_H */
