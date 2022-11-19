// do not use platformio included avrdude!!
// avrdude -v -p attiny10 -C C:\Users\[home]\.platformio\packages\tool-avrdude\avrdude.conf -c usbasp -U flash:w:.pio\build\attiny10\firmware.hex:i

#define F_CPU 8000000UL
#include <avr/io.h>

#define sbi(PORT, BIT) PORT |= _BV(BIT)
#define cbi(PORT, BIT) PORT &= ~_BV(BIT)

uint32_t xorshift()
{
    static uint32_t v = 2463534242;
    v ^= v << 13;
    v ^= v >> 17;
    v ^= v << 5;
    return v;
}
int main()
{

    // https://electronut.in/attiny10-hello/
    // Set CPU speed by setting clock prescalar:
    // CCP register must first be written with the correct signature - 0xD8
    CCP = 0xD8;
    //  CLKPS[3:0] sets the clock division factor
    CLKPSR = 0; // 0000 (1)

    DDRB |= _BV(PB2); // set PB2 output

    for (;;) {
        const auto random = xorshift() & 0x01;
        if (random) {
            sbi(PORTB, PB2);
        } else {
            cbi(PORTB, PB2);
        }
    }
    return 0;
}