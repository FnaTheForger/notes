#include <stdio.h>
#include <stdint.h>

void print_bits(uint8_t v) {
    for (int i = 7; i >= 0; i--) {
        putchar(((v >> i) & 1U) ? '1' : '0');
    }
    putchar('\n');
}

int main(void) {
    uint8_t reg = 0x00; // 0000 0000
    print_bits(reg);

    // 1. SET bit 6 and bit 2
    reg |= (1U << 6) | (1U << 2); // 0100 0100
    printf("\n1. Set bit 6 and 2\n");
    print_bits(reg);

    // 2. CLEAR bit 2
    // reg   = 0100 0100
    // ~mask = 1111 1011
    //       = --------- &
    //       = 0100 0000
    reg &= ~(1U << 2);
    printf("2. Clear bit 2\n");
    print_bits(reg);

    // 2.1 CLEAR bit 2 again: the result must stay the same
    // reg   = 0100 0000
    // ~mask = 1111 1011
    //       = --------- &
    //       = 0100 0000
    reg &= ~(1U << 2);
    printf("2.1 Clear bit 2 again (must stay the same)\n");
    print_bits(reg);

    // 3. TOGGLE bit 6 twice
    // reg       = 0100 0000
    // (1U << 6) = 0100 0000
    //             --------- ^
    //           = 0000 0000 
    reg ^= (1U << 6);
    printf("3. Toggle bit 6\n");
    print_bits(reg);

    // reg       = 0000 0000
    // (1U << 6) = 0100 0000
    //             --------- ^
    //           = 0100 0000 
    reg ^= (1U << 6);
    printf("3.1 Toggle bit 6 again\n");
    print_bits(reg);

    // 4. CHECK bit 6: Program decided the result
    // reg       = 0100 0000
    // (1U << 6) = 0100 0000
    //             --------- &
    //           = 0100 0000 
    // In decimal 0100 0000 means 64, if statment in C doesn't always needs 1 to indicate true
    // 0        = False
    // non-zero = True
    printf("4. Check bit 6: ");
    if (reg & (1U << 6)) {
        printf("ON\n");
    } else {
        printf("OFF\n");
    }

    // Change the condition, then CHECK with the exact code
    // reg   = 0100 0000
    // ~mask = 1011 1111
    //         --------- &
    //       = 0000 0000
    reg &= ~(1U << 6);
    printf("4.1 After clearing bit 6, check again: ");
    if (reg & (1U << 6)) {
        printf("ON\n");
    } else {
        printf("OFF\n");
    }
    print_bits(reg);

    return 0;
}