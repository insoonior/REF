/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

 
#include <raw_api.h>

#ifndef __RAW_ARCH_SYS_ARCH_H__
#define __RAW_ARCH_SYS_ARCH_H__

#define USE_WINDOWS_MEM   0

/* let sys.h use binary semaphores for mutexes */
#define LWIP_COMPAT_MUTEX 1


/* HANDLE is used for sys_sem_t but we won't include windows.h */
struct _sys_sem {
  RAW_SEMAPHORE *sem;
};

typedef struct _sys_sem sys_sem_t;
#define SYS_SEM_NULL NULL

#define sys_sem_valid(sema) (((sema) != NULL) && ((sema)->sem != NULL))
#define sys_sem_set_invalid(sema) ((sema)->sem = NULL)

struct lwip_mbox {
  RAW_QUEUE   *queue ;
};

typedef struct lwip_mbox sys_mbox_t;
#define SYS_MBOX_NULL NULL
#define sys_mbox_valid(mbox) ((mbox != NULL) && ((mbox)->queue != NULL))
#define sys_mbox_set_invalid(mbox) ((mbox)->queue = NULL)

typedef RAW_U32 sys_thread_t;


void *port_malloc(RAW_U32  size);
void   port_free(void *mem);


#endif /* __RAW_ARCH_SYS_ARCH_H__ */


