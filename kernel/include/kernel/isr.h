#ifndef _ISR_H
#define _ISR_H

#include <stdint.h>

typedef struct registers {
  uint32_t
    edi, esi, ebp, ebx, ecx, edx, eax,
    eip, cs, eflags, esp, ss;
} registers_t;

typedef void (*isr_handler_t)(registers_t *regs, int int_no, int err);

#endif
