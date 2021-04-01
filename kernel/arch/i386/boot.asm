; Declare constants for the multiboot header.
ALIGN 		equ 1<<0				; align loaded modules on page boundaries
MEMINFO 	equ 1<<1				; provide memory map
FLAGS 		equ ALIGN | MEMINFO		; this is the Multiboot 'flag' field
MAGIC 		equ 0x1BADB002      	; 'magic number' lets bootloader find the header
CHECKSUM 	equ -(MAGIC + FLAGS) 	; checksum of above, to prove we are multiboot

; Declare a header as in the Multiboot Standard.
section .multiboot
align 4

dd	MAGIC
dd	FLAGS
dd	CHECKSUM

; Reserve a stack for the initial thread.
section .bss
align 16

stack_bottom: 
resb 16384 # 16 KiB
stack_top:

; The kernel entry point.
section .text
S.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
