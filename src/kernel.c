int kmain(void) {
    unsigned int a;
    unsigned int b = 0x0000BABE;
    asm("mov $0xCAFE0000, %0" : "=r"(a));
    return a + b;
}