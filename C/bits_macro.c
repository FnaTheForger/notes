#include <stdio.h>
#include <stdint.h>

#define SET_BIT(reg, n)   ((reg) |= (1U << (n)))
#define TOGGLE_BIT(reg, n) ((reg) ^= (1U << (n)))
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
    print_bits(t);

    // Operator Precedence in C language 
    // << >> bit shifts first before bitwise OR operation

    // In general when we run: t |= (1U << 2 | 1) the result would be 0000 0101 = 5 in decimal.
    // It could happen due to Operator Precedence in C language, << is evaluated before |
    // so the code is read as: t |= ((1U << 2) | 1).
    // But, i want it return 0000 1000 or 8 in decimal, which only sets bit 3 (2 | 1 = 3).
    // Using macros with parentheses, (2 | 1) is evaluated first before the shift.

    // 1. t |= (1U << 2 | 1)
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
    printf("\n1. Set without macro: t |= (1U << 2 | 1) (precedence pitfall)\n");
    print_bits(t);

    // 2. CLEAR bit 2
    // t = 0000 0101
    // (1U << 2) = 0000 0100 NOT 1111 1011
    //           = 0000 0101
    //           = 1111 1011
    //             --------- &
    //           = 0000 0001
    CLEAR_BIT(t, 2);
    printf("2. Clear bit 2\n");
    print_bits(t);

    // 2.1 CLEAR bit 0
    // t = 0000 0001
    // (1U << 0) = 0000 0001 NOT 1111 1110
    //           = 0000 0001
    //           = 1111 1110
    //             --------- &
    //           = 0000 0000
    CLEAR_BIT(t, 0);
    printf("2.1 Clear bit 0\n");
    print_bits(t);

    // 3. SET bit 3 using SET_BIT(t, 2 | 1)
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
    printf("3. Set bit 3 with macro: SET_BIT(t, 2 | 1)\n");
    print_bits(t);

    // 4. CLEAR bit 3
    // ((t) &= ~(1U << (2 | 1)))
    // Step 1: (2 | 1) = 0000 0011 (3 in decimal)
    // Step 2: (1U << 3) = 0000 1000
    // Step 3: ~(1U << 3) = 1111 0111 <- mask (inverted)
    // Step 4: t &= mask
    //         0000 1000
    //         1111 0111
    //         --------- &
    //         0000 0000
    CLEAR_BIT(t, 2 | 1);
    printf("4. Clear bit 3: CLEAR_BIT(t, 2 | 1)\n");
    print_bits(t);

    // 5. TOGGLE bit 3 twice
    // ((t) ^= (1U << (2 | 1)))
    // Step 1: (2 | 1) = 0000 0011 (3 in decimal)
    // Step 2: (1U << 3) = 0000 1000 <- mask
    // Step 3: t ^= mask
    //         0000 0000
    //         0000 1000
    //         --------- ^
    //         0000 1000 (bit 3 flipped from 0 to 1)
    TOGGLE_BIT(t, 2 | 1);
    printf("5. Toggle bit 3\n");
    print_bits(t);
    
    // Same mask, t = 0000 1000
    // Step 1: (2 | 1) = 0000 0011 (3 in decimal)
    // Step 2: (1U << 3) = 0000 1000 <- mask
    // Step 3: t ^= mask
    //         0000 1000
    //         0000 1000
    //         --------- ^
    //         0000 0000 (bit 3 flipped from 1 back to 0)
    TOGGLE_BIT(t, 2 | 1);
    printf("5.1 Toggle bit 3 again\n");
    print_bits(t);

    // 6. CHECK bit 3
    // ((t) & (1U << (3)))
    // t = 0000 0000
    // (1U << 3) = 0000 1000 <- mask
    //             0000 0000
    //             0000 1000
    //             --------- &
    //             0000 0000 = 0 (false), so the else branch runs
    printf("6. Check bit 3: ");
    if (CHECK_BIT(t, 3)) {
        printf("ON\n");
    } else {
        printf("OFF\n"); // <- this one runs
    }

    // 7. SET bit 3 again
    // ((t) |= (1U << (3)))
    // t = 0000 0000
    // (1U << 3) = 0000 1000 <- mask
    //             0000 0000
    //             0000 1000
    //             --------- |
    //             0000 1000
    SET_BIT(t, 3);
    printf("7. Set bit 3\n");
    print_bits(t);

    // 7.1 CHECK bit 3 again
    // ((t) & (1U << (3)))
    // t = 0000 1000
    // (1U << 3) = 0000 1000 <- mask
    //             0000 1000
    //             0000 1000
    //             --------- &
    //             0000 1000 = 8 (not zero, so true), the if branch runs
    printf("7.1 Check bit 3 again: ");
    if (CHECK_BIT(t, 3)) {
        printf("ON\n"); // <- this one runs
    } else {
        printf("OFF\n");
    }

    return 0;
}
