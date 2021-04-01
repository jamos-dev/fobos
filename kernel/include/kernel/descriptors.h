#ifndef _DESCRIPTORS_H
#define _DESCRIPTORS_H

#include <stdint.h>

/*
 * GDT entry
 *
 * +------+------+------+------+------+------+------+------+
 * |31                       16|15                        0|
 * +------+------+------+------+------+------+------+------+
 * |          Base 0:15        |         Limit 0:15        |
 * +------+------+------+------+------+------+------+------+
 * |63         56|55  52|51  48|47         40|39         32|
 * +------+------+------+------+------+------+------+------+
 * | Base 24:31  |Flags |L16:19| Access byte |  Base 16:23 |
 * +------+------+------+------+-------------+-------------+
 *
 * The base is a 32 bit value containing the linear address where the
 * segment begins.
 *
 * The limit, a 20 bit value, tells the maximum addressable unit (either
 * in 1 byte units, or in pages). Hence, if you choose page granularity
 * (4 KiB) and set the limit value to 0xFFFFF the segment will span the
 * full 4 GiB address space.
 *
 * Access byte
 *
 * 7                       0
 * +--+--+--+--+--+--+--+--+
 * |Pr|Privl|S |Ex|Dc|Rw|Ac|
 * +--+--+--+--+--+--+--+--+
 *
 * Pr: Present bit. This must be 1 for all valid selectors.
 *
 * Privl: Privilege, 2 bits. Contains the ring level, 0 = highest (kernel),
 * 3 = lowest (user applications).
 *
 * S: Descriptor type. This bit should be set for code or data segments and
 * should be cleared for system segments (eg. a Task State Segment)
 *
 * Ex: Executable bit. If 1 code in this segment can be executed, ie. a code
 * selector. If 0 it is a data selector.
 *
 * DC: Direction bit/Conforming bit.
 *
 * RW: Readable bit/Writable bit.
 *
 * Ac: Accessed bit. Just set to 0. The CPU sets this to 1 when the segment is
 * accessed.
 *
 * Flags
 *
 * 7                   4
 * +----+----+----+----+
 * | Gr | Sz | 0  | 0  |
 * +----+----+----+----+
 *
 * Gr: Granularity bit. If 0 the limit is in 1 B blocks (byte granularity), if
 * 1 the limit is in 4 KiB blocks (page granularity).
 *
 * Sz: Size bit. If 0 the selector defines 16 bit protected mode. If 1 it
 * defines 32 bit protected mode. You can have both 16 bit and 32 bit selectors
 * at once
 *
 */
struct gdt_entry_struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__ ((packed));

typedef struct gdt_entry_struct gdt_entry_t;

/*
 * GTD descriptor
 *
 *   +----+----+
 * 0 |  Size   |
 *   +----+----+----+----+
 * 2 +       Offset      |
 *   +----+----+----+----+
 *
 * The offset is the linear address of the table itself, which means that
 * paging applies.
 *
 * The size is the size of the table subtracted by 1. This is because
 * the maximum value of size is 65535, while the GDT can be up to 65536
 * bytes (a maximum of 8192 entries). Further no GDT can have a size of 0.
 */
struct gdt_ptr_struct {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

void gdt_init();

#endif