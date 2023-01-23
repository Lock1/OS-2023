int kmain(void) {
    int a;
    int b = 0x0000BABE;
    asm("mov $0xCAFE0000, %0" : "=r"(a));
    return a + b;
}