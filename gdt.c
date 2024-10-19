#include "gdt.h"
#include "types.h"

u64 gdt_entries[3];

u64 create_entry(u32 base, u32 limit, u8 access_byte, u8 flags){
    u64 rv = 0;
    rv |= (u64)(limit && 0x00FFFF);
    rv |= (u64)(base && 0x00FFFFFF) << 16;
    rv |= (u64)(access_byte && 0xFF) << 40;
    rv |= (u64)(limit && 0xFF0000) << 48;
    rv |= (u64)(flags && 0xF) << 52;
    rv |= (u64)(base && 0xFF000000) << 56;
    return rv;
}

void init_gdt(){
    gdt_entries[0] = create_entry(0, 0, 0, 0);
    gdt_entries[1] = create_entry(0, 0xFFFFFFFF, KERNEL_CODE_ACCESS_BYTE, FLAGS);
    gdt_entries[2] = create_entry(0, 0xFFFFFFFF, KERNEL_DATA_ACCESS_BYTE, FLAGS);
    //load_gdt(sizeof(gdt_entries)-1, (u32)&gdt_entries);
    //reloadSegments();
}