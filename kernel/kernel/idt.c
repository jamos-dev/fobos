#include <stdint.h>
#include <strings.h>

struct idt_ptr_struct {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

typedef struct idt_ptr_struct idt_ptr_t;

struct idt_entry_struct {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_high;
	
} __attribute__ ((packed));

typedef struct idt_entry_struct idt_entry_t;

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void idt_load(uint32_t);

void idt_set_gate(uint8_t number, idt_gate_t base, uint16_t selector, uint8_t flags) {

	idt_entries[number].offset_low = (uint16_t) base & 0xFFFF;
	idt_entries[number].offset_high = ((uint16_t) base >> 16) & 0xFFFF;	
	idt_entries[number].selector = selector;	
	idt_entries[number].zero = zero;
	idt_entries[number].flags = flags | 0x60;
}

void idt_init() {

	idt_ptr.limit = sizeof(idt_entries) - 1;
	idt_ptr.base = (uint32_t) &idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entries));

	idt_load(&idt_ptr);
}
