#include <stdio.h>
#include <stdint.h>

#define SET_BIT(reg, n)   ((reg) |= (1U << (n)))
#define CLEAR_BIT(reg, n) ((reg) &= ~(1U << (n)))
#define CHECK_BIT(reg, n) ((reg) & (1U << (n)))
#define READ_BIT(reg, n)  (((reg) >> (n)) & 1U)

void print_bits(uint8_t v) {
    for (int i = 7; i >= 0; i--) {
        putchar(((v >> i) & 1U) ? '1' : '0');
    }
    putchar('\n');
}

int main(void) {
    uint8_t t = 0x00; // 0000 0000

    // Operator Precedence in C language 
    // << >> bit shifts first before bitwise OR operation

    // In general when we run: t |= (1U << 2 | 1) the result would be 0000 0101 = 5 in decimal.
    // It could happen due to Operator Precedence in C language, << is evaluated before |
    // so the code is read as: t |= ((1U << 2) | 1).
    // But, i want it return 0000 1000 or 8 in decimal, which only sets bit 3 (2 | 1 = 3).
    // Using macros with parentheses, (2 | 1) is evaluated first before the shift.

    // t |= (1U << 2 | 1)
    // Step 1: 1U << 2 = 0000 0100   
    // Step 2: 0100 | 1:
    //         0000 0100
    //         0000 0001
    //         --------- |
    //         0000 0101       <- mask
    // Step 3: t |= mask:
    //         0000 0000
    //         0000 0101
    //         --------- |
    //         0000 0101
    t |= (1U << 2 | 1);
    print_bits(t);

    // t = 0000 0101
    // (1U << 2) = 0000 0100 XOR 1111 1011
    //           = 0000 0101
    //           = 1111 1011
    //             --------- &
    //           = 0000 0001
    CLEAR_BIT(t, 2);
    // t = 0000 0001
    // (1U << 0) = 0000 0001 XOR 1111 1110
    //           = 0000 0001
    //           = 1111 1110
    //             --------- &
    //           = 0000 0000
    CLEAR_BIT(t, 0);
    print_bits(t);

    // ((t) |= (1U << (2 | 1))) 
    // Step 1: (2 | 1) 
    //         0000 0010
    //         0000 0001
    //         --------- |
    //         0000 0011 (it means 3 in decimal)
    // Step 2: (1U << 3) or Shifted 1 to the left 3 times 
    //         0000 1000 <- mask
    // Step 3: t |= mask
    //         0000 0000
    //         0000 1000
    //         --------- |
    //         0000 1000
    SET_BIT(t, 2 | 1);
    print_bits(t);

    if (CHECK_BIT(t, 3)) {
        printf("ON\n");
    } else {
        printf("OFF\n");
    }

    CLEAR_BIT(t, 3);
    print_bits(t);

    if (CHECK_BIT(t, 3)) {
        printf("\nON\n");
    } else {
        printf("OFF\n");
    }

    return 0;
}