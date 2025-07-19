#include "gdt.h"
#include "util.h"
extern void gdt_flush(uint32_t);
extern void tss_flush();
struct gdt_entry_struct gdt_entries[6];
struct gdt_ptr_struct gdt_ptr;
struct tss_entry tss_entry;

void initGdt()
{
    gdt_ptr.limit=(sizeof(struct gdt_entry_struct)*6)-1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    setGdtGate(0,0,0,0,0);
    setGdtGate(1,0,0xFFFFFFFF,0x9A,0xCF); //kernel code seg
    setGdtGate(2,0,0xFFFFFFFF,0x92,0xCF); //kernel data seg
    setGdtGate(3,0,0xFFFFFFFF,0xFA,0xCF); //User Code Seg
    setGdtGate(4,0,0xFFFFFFFF,0xF2,0xCF); //USer Data Seg
    writeTSS(5,0x10,0x0);

    //9A= 1001 1010
    //92= 1001 0010
    //FA= 1111 1010
    //F2= 1111 0010

    gdt_flush((uint32_t)&gdt_ptr);
    tss_flush();
}

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0){
    uint32_t base=(uint32_t) &tss_entry;
    uint32_t limit=base-sizeof(tss_entry);

    setGdtGate(num,base,limit,0xE9,0x00);
    memset(&tss_entry , 0 , sizeof(tss_entry));

    tss_entry.ss0=ss0;
    tss_entry.esp0=esp0;

    tss_entry.cs=0x00 | 0x03;
    tss_entry.ss=tss_entry.ds=tss_entry.es=tss_entry.fs=tss_entry.gs=0x10 | 0x3;

}


void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
 gdt_entries[num].base_low=(base& 0xFFFF);
 gdt_entries[num].base_middle=(base >> 16) & 0xFF;
 gdt_entries[num].base_high=(base>>24) & 0xFF;

 gdt_entries[num].limit=(limit& 0xFFFF);
 gdt_entries[num].flags=(limit>>16)&0x0F;
 gdt_entries[num].flags |=(gran&0xF0);

 gdt_entries[num].access=access;
}
