#include <stdio.h>

#include <kernel/isr.h>

#define ISR_COUNT 32

static isr_handler_t isr_routines[256] = { 0 };

static const char *exception_messages[32] = {
	"Division by zero",
	"Debug exception",
	"Non maskable interrupt",
	"Breakpoint exception",
	"Detected overflow",
	"Out of bounds exception",
	"Invalid opcode exception",
	"No coprocessor exception",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt exception",
	"Coprocessor fault",
	"Alignment check exception",
	"Machine check exception"
	"Interrupt 19",
	"Interrupt 20",
	"Interrupt 21",
	"Interrupt 22",
	"Interrupt 23",
	"Interrupt 24",
	"Interrupt 25",
	"Interrupt 26",
	"Interrupt 27",
	"Interrupt 28",
	"Interrupt 29",
	"Interrupt 30",
	"Interrupt 31",
};

void isr_handler(registers_t regs) {
  printf("Received interrupt: %d\n", regs.int_no);
  //  printf("  %s\n", exception_messages[regs.int_no]);
}
