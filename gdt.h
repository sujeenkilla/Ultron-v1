#include "stdint.h"

struct gdt_entry_struct
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
}__attribute__((packed));


struct  gdt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

typedef struct tss_entry {
    uint32_t prev_tss;   // Previous task link
    uint32_t esp0;       // Kernel stack pointer (Ring 0)
    uint32_t ss0;        // Kernel stack segment (Ring 0)
    uint32_t esp1;       // Ring 1 stack pointer (unused)
    uint32_t ss1;        // Ring 1 stack segment
    uint32_t esp2;       // Ring 2 stack pointer
    uint32_t ss2;        // Ring 2 stack segment
    uint32_t cr3;        // Page directory base
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp;
    uint32_t esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;        // LDT selector
    uint16_t trap;
    uint16_t iomap_base; // I/O permission bitmap offset
} __attribute__((packed));

void initGdt();
void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0);