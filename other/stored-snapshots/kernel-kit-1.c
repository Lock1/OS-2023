int kmain(void) {
    int a;
    int b = 0x0000BABE;
    __asm__("mov $0xCAFE0000, %0" : "=r"(a));
    return a + b;
}