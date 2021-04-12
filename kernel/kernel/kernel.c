#include <stdint.h>
#include <stdio.h>

#include <kernel/descriptors.h>
#include <kernel/tty.h>

static void debug() {

	uint32_t cr0;
	asm volatile("movl %%cr0, %%eax" : "=a"(cr0));

	if (cr0 & 1) {
		printf("Protected mode\n");
	} else {
		printf("Real mode\n");
	}
}

void kernel_main(void) {
	terminal_initialize();
	printf("Fobos v0.0.1\n");

	printf("Initializing GDT..");
	gdt_init();
	printf("OK\n");

	printf("Initializing IDT..");
	idt_init();
	printf("OK\n");

	asm volatile("int $0x3");
}
