#ifndef ARCH_I386_ARCH_H
#define ARCH_I386_ARCH_H

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %1, %0" : : "dN"(port), "a"(val));
}

static inline void outw(uint16_t port, uint16_t val) {
	asm volatile("outw %1, %0" : : "dN"(port), "a"(val));
}

static inline void outl(uint16_t port, uint32_t val) {
	asm volatile("outl %1, %0" : : "dN"(port), "a"(val));
}

static inline uint8_t inb(uint16_t port) {
	uint8_t val;
	asm volatile("inb %%dx, %%al" : "=a"(val) : "dN"(port));
	return val;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t val;
	asm volatile("inw %%dx, %%ax" : "=a"(val) : "dN"(port));
	return val;
}

static inline uint32_t inl(uint16_t port) {
	uint32_t val;
	asm volatile("inl %%dx, %%eax" : "=a"(val) : "dN"(port));
	return val;
}

#endif