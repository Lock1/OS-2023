#include "libc-header/stdint.h"

/** out:
 *  Sends the given data to the given I/O port
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
void out(uint16_t port, uint8_t data) {
    // TODO: Test I/O function
    /** x86 inb/outb:
     * @param dx target port 
     * @param al input/output byte
     */
    __asm__(
        "outb %0, %1"
        : // <Empty output operand>
        : "a"(data), "Nd"(port)
    );
}

/** in:
 *  Read data from the given I/O port
 *
 *  @param port The I/O port to request the data
 *  @return Recieved data from the corresponding I/O port
 */
uint8_t in(uint16_t port) {
    uint8_t result;
    __asm__ volatile(
        "inb %1, %0" 
        : "=a"(result) 
        : "Nd"(port)
    );
    return result;
}