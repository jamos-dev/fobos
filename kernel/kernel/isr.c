
#define ISR_COUNT 32

static struct {
	size_t	index;
	void	(*stub)(void);
} isrs[ISR_COUNT + 1] __attribute__((used));

static irq_handler_t isr_routines[256] = { 0 };

void isr_install_handler(size_t isr, irq_handler_t handler) {
	isr_routines[isr] = handler;
}

void isr_uninstall_handler(size_t isr) {
	isr_routines[isr] = 0;
}

void isr_init(void) {

	for (int i = 0; i < ISR_COUNT; i++) {
		isrs[i].index = i;
		isrs[i].stub = (void *) 0;
	}

	// Add syscall

	for (int i = 0; i < ISR_COUNT; i++) {
		idt_set_gate(isrs[i].index, isrs[i].stub, 0x08, 0x8E);
	}
}

static const char *exception_messages[32] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present"
};

void fault_handler(struct regs *r) {

	irq_handler_t handler = isr_routines[t->int_no];

	if (handler) {
		handler(r);
	} else {
		// unhandled exception
		// todo
	}
}