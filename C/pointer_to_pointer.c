#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t myNumbers[5] = {25, 50, 75, 100, 125};
    uint32_t *ptr = myNumbers;
    uint32_t **pptr = &ptr;

    printf("%u\n", *(ptr + 1));
    ptr += 4;
    printf("%u\n", **pptr);
    ptr -= 4;

    **pptr = 150;
    printf("%u\n", *ptr);

    size_t len = sizeof(myNumbers) / sizeof(myNumbers[0]);
    for (uint32_t i = 0; i < len; i++) {
        printf("\n%u", **pptr);
        ptr++;
        if (i == len - 1) {
            *(*pptr + 1) = 32;
            break;
        }
    }
    printf("\n%u", *(ptr + 1));

    return 0;
}