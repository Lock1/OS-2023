typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef struct gdt {
    uint16 limit_low;
    uint16 base_low;
    uint8 base_mid;
    uint8 accessed: 1;
    uint8 writable_readable: 1; // data (writable), code (readable)
    uint8 expansion_conforming: 1; // data (expansion direction): 1 = up / 0 = down, code (conforming): 1 = yes, 0 = no
    uint8 type: 1; // data = 0, code = 1
    uint8 non_system: 1; // system = 0, non system (code/data) = 1
    uint8 dpl: 2; // descriptor level privilege, PL0 = kernel/most privilege, PL3 = user/least privilege
    uint8 present: 1;
    uint8 limit_up: 4;
    uint8 reserved: 1; // always 0
    uint8 long_mode: 1;
    uint8 db_size: 1;
    uint8 granularity: 1;
    uint8 base_hi;
} __attribute__((packed)) gdt;


typedef struct gdtr {
    uint16 size;
    gdt* address;
} __attribute__((packed)) gdtr;

int check() {
    gdt a;
    return sizeof(a);
}
gdt gdt_records[3] = {
    {0},
    { // kernel code
        .limit_up = 0xf, .limit_low = 0xffff,
        .base_hi = 0, .base_mid = 0, .base_low = 0,
        .granularity = 1, .non_system = 1,
        .type = 1, .accessed = 0, .writable_readable = 1, .expansion_conforming = 0,
        .dpl = 0,
        .present = 1, .db_size = 1 /* op size 32 bit */, .long_mode = 0
    },
    { // kernel data
        .limit_up = 0xf, .limit_low = 0xffff,
        .base_hi = 0, .base_mid = 0, .base_low = 0,
        .granularity = 1, .non_system = 1,
        .type = 0, .accessed = 0, .writable_readable = 1, .expansion_conforming = 1,
        .dpl = 0,
        .present = 1, .db_size = 1 /* upper bound 64gb */, .long_mode = 0
    }
};

extern void enter_protected_mode(gdtr* gdt_r);

gdtr gdtreg = {
    .size = sizeof(gdt_records),
    .address = gdt_records,
};
int kmain() {
    enter_protected_mode(&gdtreg);
    check();
    while (1);
    return 0xdeadbeef;
}
