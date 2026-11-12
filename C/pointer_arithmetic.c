#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    uint32_t myNumbers[5] = {25, 50, 75, 100, 125};
    uint32_t *p = myNumbers; // uint pointer

    // Increment & Decrement
    // move a pointer with ++ and -- (and with += / -=)
    printf("%d\n", *p); // 25
    p++;
    printf("%d\n", *p); // 50
    p--;
    printf("%d\n", *p); // 25

    p += 3;
    printf("%d\n", *p); // 100

    // Pointer substraction (distance)
    uint32_t *start   = &myNumbers[1];
    uint32_t *end     = &myNumbers[4];

    uint32_t distance = end - start; // 3 elements apart
    printf("\n%d\n", distance);

    // How pointer moves
    char letters[] = "Hi"; // 'H', 'i', '\0'
    char *pc = letters; // char pointer

    // Pointer moves based on the data type size (pointer arithmetic)
    // For uint32_t, each increment moves the address by 4 bytes
    // Conclusion, each moves depends on the data type size

    // For example pointers start at memory address 1000:
    // p + 1  = 1004 <- uint32_t (4 byte)
    // pc + 1 = 1001 <- char     (1 byte)
    // memory address variable name == memory address first element

    printf("\n%p", p); 
    printf("\n%p", p + 1);
    printf("\n%p\n", p + 2);
    p -= 3;

    printf("\n%p", pc);
    printf("\n%p\n", pc + 1);
    pc--;
    
    uint32_t i;
    size_t len = sizeof(myNumbers) / sizeof(myNumbers[0]);
    // looping with a pointer
    for (i = 0; i < len; i++) {
        printf("%d\n", *p);
        p++;
    }

    return 0;
}